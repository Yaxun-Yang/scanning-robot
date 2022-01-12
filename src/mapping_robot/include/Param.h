#pragma once
#include <QString>
#include <string>

namespace stereye {
class Param {
public:
    std::string mJpgTopic, mDepthTopic, mLidarTopic;
    QString mCalibrationPath;
    QString mLidarBash, mLidarRemoteIp, mLidarHostIp;
    QString mCameraBash;
    QString mWorkerBash;
    QString mRecorderPath, mExportPath;
};
} // namespace stereye