#include "Camera.h"

namespace stereye {

Camera::Camera() {
}

Camera::Camera(const std::string& path) {
    if (!path.empty()) {
        init(path);
    }
}

/**
 * \brief  Init camera parameters with file
 *
 * \param path (path of file)
 */
void Camera::init(const std::string& path) {
    std::ifstream config(path);
    if(!config.is_open()) {
        std::cerr << "ERROR: Wrong path to camera config!" << std::endl;
        std::abort();
    }
    CameraModel model = PINHOLE;// default pinhole
    int w, h;
    std::vector<double> vIntrinsic;
    std::vector<double> vDistortion;
    std::vector<double> vExtrinsic;
    double temp;
    int scale = 1;
    while (!config.eof())
    {
        std::string item;
        config >> item;
        if (item == "camera_model") {
            std::string modelStr;
            config >> modelStr;
            if (modelStr == "fisheye") model = FISHEYE;
            else if (modelStr == "pinhole") model = PINHOLE;
            else printf("No such camera model: %s, supported models are pinhole and fisheye!\n", modelStr.c_str());
        }
        else if (item == "image_size") {
            config >> w >> h;
        }
        else if (item == "resize_scale") {
            config >> scale;
        }
        else if (item == "intrinsic") {
            int row, col;
            config >> row >> col;
            assert(row * col == 9);
            for (int i = 0; i < row * col; ++i) {
                config >> temp;
                vIntrinsic.push_back(temp);
            }
        }
        else if (item == "distortion") {
            int row, col;
            config >> row >> col;
            for (int i = 0; i < row * col; ++i) {
                config >> temp;
                vDistortion.push_back(temp);
            }
        }
        else if (item == "cam_to_pose") {
            int row, col;
            config >> row >> col;
            assert(row * col == 16);
            for (int i = 0; i < row * col; ++i) {
                config >> temp;
                vExtrinsic.push_back(temp);
            }
        }
    }
    mScale = scale;
    cv::Mat intrinsic(3, 3, CV_64FC1, vIntrinsic.data());
    cv::Mat distortion(1, vDistortion.size(), CV_64FC1, vDistortion.data());
    cv::Mat extrinsic(4, 4, CV_64FC1, vExtrinsic.data());
    init(model, w, h, intrinsic, distortion, extrinsic);
}

/**
 * \brief  Init camera parameters with data
 *
 * \param model (camera model, canbe pinhole or fisheye)
 * \param w (image width)
 * \param h (image height)
 * \param intrinsic (3x3 cv::Mat)
 * \param distortion (1x4 or 1x5 cv::Mat, depends on the distortion model you use)
 */
void Camera::init(CameraModel model, int w, int h, const cv::Mat& intrinsic,
                                     const cv::Mat& distortion, const cv::Mat& extrinsic) {
    // make sure the input is legal
    assert(intrinsic.rows == 3 && intrinsic.cols == 3);
    assert(extrinsic.rows == 4 && extrinsic.cols == 4);
    assert(w > 0 && h > 0);
    if (model == FISHEYE) {
        assert(distortion.rows == 1 && distortion.cols == 4);
        printf("Using camera model: Camera::FISHEYE\n");
    }
    else if (model == PINHOLE) {
        assert(distortion.rows == 1 && (distortion.cols == 4 || distortion.cols == 5 || distortion.cols == 8));
        printf("Using camera model: Camera::PINHOLE\n");
    }
    else {
        assert(model == FISHEYE || model == PINHOLE);
    }

    mModel = model;
    mFx = intrinsic.at<double>(0, 0);
    mFy = intrinsic.at<double>(1, 1);
    mCx = intrinsic.at<double>(0, 2);
    mCy = intrinsic.at<double>(1, 2);
    mIntrinsic = intrinsic.clone();
    mDistortion = distortion.clone();
    mExtrinsic = extrinsic.clone();
    mW = w;
    mH = h;
    std::cout << "intrinsic:\n" << intrinsic << std::endl;
    std::cout << "distortion:\n" << distortion << std::endl;
    std::cout << "extrinsic:\n" << extrinsic << std::endl;
    // UDEBUG("width: %d", mW);
    // UDEBUG("height: %d", mH);
}

std::shared_ptr<Camera> Camera::rescale(int scale) {
    auto cam = std::make_shared<Camera>();
    cam->init(mModel, mW/mScale, mH/mScale, mIntrinsic/mScale, mDistortion, mExtrinsic);
    return cam;
}

void Camera::writeConfig(const std::string& path) {
    std::ofstream config(path);
    if(!config.is_open()) {
        std::cerr << "ERROR: Couldnot write camera config!" << std::endl;
        std::abort();
    }
    if (mModel == PINHOLE) config << "camera_model pinhole\n\n";
    else if (mModel == FISHEYE) config << "camera_model fisheye\n\n";
    config << "image_size " << mW << " " << mH << "\n\n";
    config << "intrinsic " << mIntrinsic.rows<< " " << mIntrinsic.cols << "\n";
    for (int row = 0; row < mIntrinsic.rows; ++row) {
        for (int col = 0; col < mIntrinsic.cols; ++col) {
            config << mIntrinsic.at<double>(row, col) << " ";
        }
    }
    config << "\n\n";
    config << "distortion " << mDistortion.rows<< " " << mDistortion.cols << "\n";
    for (int row = 0; row < mDistortion.rows; ++row) {
        for (int col = 0; col < mDistortion.cols; ++col) {
            config << mDistortion.at<double>(row, col) << " ";
        }
    }
    config << "\n\n";
    config << "cam_to_pose " << mExtrinsic.rows<< " " << mExtrinsic.cols << "\n";
    for (int row = 0; row < mExtrinsic.rows; ++row) {
        for (int col = 0; col < mExtrinsic.cols; ++col) {
            config << mExtrinsic.at<double>(row, col) << " ";
        }
    }
    config << "\n\n";
    config << "resize_scale " << mScale << "\n";
}

/**
 * \brief Undistort color image
 *
 * \param input (image to be undistorted)
 * \param flag (cv::InterpolationFlags, use cv::INTER_LINEAR by default if not specified)
 * \return Already undistorted image
 */
cv::Mat Camera::undistortImage(const cv::Mat& input, int flag) {
    assert(input.rows==mH && input.cols==mW);

    if (!mInitUndistortRectifyMap) {
        initUndistortRectifyMap();
    }
    cv::Mat output;
    cv::remap(input, output, this->mMapX, this->mMapY, flag);
    return output;
}

/**
 * \brief Init undistort rectify map (map_x and map_y)
 *
 * \param newCameraMatrix (new camera matrix, same as intrinsic by default)
 */
void Camera::initUndistortRectifyMap(const cv::Mat& newCameraMatrix) {
    cv::Mat_<double> intrinsic = (cv::Mat_<double>(3, 3) << mFx, 0, mCx, 0, mFy, mCy, 0, 0, 1);
    cv::Mat new_camera_matrix_used = intrinsic;
    if (!newCameraMatrix.empty()) {
        assert(newCameraMatrix.rows==3 && newCameraMatrix.cols==3);
        new_camera_matrix_used = newCameraMatrix;
    }
    // create undistort map
    if (mModel == FISHEYE) {
        cv::fisheye::initUndistortRectifyMap(intrinsic, mDistortion, cv::Mat(),
                new_camera_matrix_used, cv::Size(mW, mH),
                CV_32FC1, this->mMapX, this->mMapY);
    }
    else if (mModel == PINHOLE) {
        cv::initUndistortRectifyMap(intrinsic, mDistortion, cv::Mat(),
                new_camera_matrix_used, cv::Size(mW, mH),
                CV_32FC1, this->mMapX, this->mMapY);
    }
    else {
        printf("Camera model not supported, exit.\n");
        exit(-1);
    }
    
    mInitUndistortRectifyMap = true;
}

cv::Mat Camera::undistortDepth(const cv::Mat & input) {
    if (!mInitUndistortRectifyMap) {
        initUndistortRectifyMap();
    }
	if(!mMapX.empty() && !mMapY.empty())
	{
		cv::Mat output = cv::Mat::zeros(mMapX.rows, mMapX.cols, input.type());
		for(int y=0; y<mMapX.rows; ++y)
		{
			for(int x=0; x<mMapX.cols; ++x)
			{
				cv::Point2f pt(mMapX.at<float>(y,x), mMapY.at<float>(y,x));
				int xL = (int)floor(pt.x);
				int xH = (int)ceil(pt.x);
				int yL = (int)floor(pt.y);
				int yH = (int)ceil(pt.y);
				if(xL >= 0 && yL >= 0 && xH < input.cols && yH < input.rows)
				{
					const unsigned short & pLT = input.at<unsigned short>(yL, xL);
					const unsigned short & pRT = input.at<unsigned short>(yL, xH);
					const unsigned short & pLB = input.at<unsigned short>(yH, xL);
					const unsigned short & pRB = input.at<unsigned short>(yH, xH);
					if(pLT > 0 && pRT > 0 && pLB > 0 && pRB > 0)
					{
						unsigned short avg = (pLT + pRT + pLB + pRB) / 4;
						unsigned short thres = 0.01 * avg;
						if( abs(pLT - avg) < thres &&
							abs(pRT - avg) < thres &&
							abs(pLB - avg) < thres &&
							abs(pRB - avg) < thres)
						{
							//bilinear interpolation
							float a = pt.x - (float)xL;
							float c = pt.y - (float)yL;

							//http://stackoverflow.com/questions/13299409/how-to-get-the-image-pixel-at-real-locations-in-opencv
							output.at<unsigned short>(y,x) =
									(pLT * (1.f - a) + pRT * a) * (1.f - c) +
									(pLB * (1.f - a) + pRB * a) * c;
						}
					}
				}
			}
		}
		return output;
	}
	else
	{
		printf("Cannot rectify image because the rectify map is not initialized.\n");
		return input.clone();
	}
}

} // namespace stereye