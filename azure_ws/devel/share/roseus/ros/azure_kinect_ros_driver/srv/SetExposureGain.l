;; Auto-generated. Do not edit!


(when (boundp 'azure_kinect_ros_driver::SetExposureGain)
  (if (not (find-package "AZURE_KINECT_ROS_DRIVER"))
    (make-package "AZURE_KINECT_ROS_DRIVER"))
  (shadow 'SetExposureGain (find-package "AZURE_KINECT_ROS_DRIVER")))
(unless (find-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAIN")
  (make-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAIN"))
(unless (find-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAINREQUEST")
  (make-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAINREQUEST"))
(unless (find-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAINRESPONSE")
  (make-package "AZURE_KINECT_ROS_DRIVER::SETEXPOSUREGAINRESPONSE"))

(in-package "ROS")





(defclass azure_kinect_ros_driver::SetExposureGainRequest
  :super ros::object
  :slots (_exposure _gain ))

(defmethod azure_kinect_ros_driver::SetExposureGainRequest
  (:init
   (&key
    ((:exposure __exposure) 0)
    ((:gain __gain) 0)
    )
   (send-super :init)
   (setq _exposure (round __exposure))
   (setq _gain (round __gain))
   self)
  (:exposure
   (&optional __exposure)
   (if __exposure (setq _exposure __exposure)) _exposure)
  (:gain
   (&optional __gain)
   (if __gain (setq _gain __gain)) _gain)
  (:serialization-length
   ()
   (+
    ;; int32 _exposure
    4
    ;; int32 _gain
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _exposure
       (write-long _exposure s)
     ;; int32 _gain
       (write-long _gain s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _exposure
     (setq _exposure (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _gain
     (setq _gain (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass azure_kinect_ros_driver::SetExposureGainResponse
  :super ros::object
  :slots ())

(defmethod azure_kinect_ros_driver::SetExposureGainResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass azure_kinect_ros_driver::SetExposureGain
  :super ros::object
  :slots ())

(setf (get azure_kinect_ros_driver::SetExposureGain :md5sum-) "118f5ae9e1aacf44af9d676470ddbbdf")
(setf (get azure_kinect_ros_driver::SetExposureGain :datatype-) "azure_kinect_ros_driver/SetExposureGain")
(setf (get azure_kinect_ros_driver::SetExposureGain :request) azure_kinect_ros_driver::SetExposureGainRequest)
(setf (get azure_kinect_ros_driver::SetExposureGain :response) azure_kinect_ros_driver::SetExposureGainResponse)

(defmethod azure_kinect_ros_driver::SetExposureGainRequest
  (:response () (instance azure_kinect_ros_driver::SetExposureGainResponse :init)))

(setf (get azure_kinect_ros_driver::SetExposureGainRequest :md5sum-) "118f5ae9e1aacf44af9d676470ddbbdf")
(setf (get azure_kinect_ros_driver::SetExposureGainRequest :datatype-) "azure_kinect_ros_driver/SetExposureGainRequest")
(setf (get azure_kinect_ros_driver::SetExposureGainRequest :definition-)
      "int32 exposure
int32 gain
---

")

(setf (get azure_kinect_ros_driver::SetExposureGainResponse :md5sum-) "118f5ae9e1aacf44af9d676470ddbbdf")
(setf (get azure_kinect_ros_driver::SetExposureGainResponse :datatype-) "azure_kinect_ros_driver/SetExposureGainResponse")
(setf (get azure_kinect_ros_driver::SetExposureGainResponse :definition-)
      "int32 exposure
int32 gain
---

")



(provide :azure_kinect_ros_driver/SetExposureGain "118f5ae9e1aacf44af9d676470ddbbdf")


