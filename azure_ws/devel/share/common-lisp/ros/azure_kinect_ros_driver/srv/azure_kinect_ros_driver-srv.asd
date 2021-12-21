
(cl:in-package :asdf)

(defsystem "azure_kinect_ros_driver-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetExposureGain" :depends-on ("_package_SetExposureGain"))
    (:file "_package_SetExposureGain" :depends-on ("_package"))
  ))