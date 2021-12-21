; Auto-generated. Do not edit!


(cl:in-package azure_kinect_ros_driver-srv)


;//! \htmlinclude SetExposureGain-request.msg.html

(cl:defclass <SetExposureGain-request> (roslisp-msg-protocol:ros-message)
  ((exposure
    :reader exposure
    :initarg :exposure
    :type cl:integer
    :initform 0)
   (gain
    :reader gain
    :initarg :gain
    :type cl:integer
    :initform 0))
)

(cl:defclass SetExposureGain-request (<SetExposureGain-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetExposureGain-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetExposureGain-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name azure_kinect_ros_driver-srv:<SetExposureGain-request> is deprecated: use azure_kinect_ros_driver-srv:SetExposureGain-request instead.")))

(cl:ensure-generic-function 'exposure-val :lambda-list '(m))
(cl:defmethod exposure-val ((m <SetExposureGain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader azure_kinect_ros_driver-srv:exposure-val is deprecated.  Use azure_kinect_ros_driver-srv:exposure instead.")
  (exposure m))

(cl:ensure-generic-function 'gain-val :lambda-list '(m))
(cl:defmethod gain-val ((m <SetExposureGain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader azure_kinect_ros_driver-srv:gain-val is deprecated.  Use azure_kinect_ros_driver-srv:gain instead.")
  (gain m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetExposureGain-request>) ostream)
  "Serializes a message object of type '<SetExposureGain-request>"
  (cl:let* ((signed (cl:slot-value msg 'exposure)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'gain)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetExposureGain-request>) istream)
  "Deserializes a message object of type '<SetExposureGain-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'exposure) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gain) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetExposureGain-request>)))
  "Returns string type for a service object of type '<SetExposureGain-request>"
  "azure_kinect_ros_driver/SetExposureGainRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetExposureGain-request)))
  "Returns string type for a service object of type 'SetExposureGain-request"
  "azure_kinect_ros_driver/SetExposureGainRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetExposureGain-request>)))
  "Returns md5sum for a message object of type '<SetExposureGain-request>"
  "118f5ae9e1aacf44af9d676470ddbbdf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetExposureGain-request)))
  "Returns md5sum for a message object of type 'SetExposureGain-request"
  "118f5ae9e1aacf44af9d676470ddbbdf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetExposureGain-request>)))
  "Returns full string definition for message of type '<SetExposureGain-request>"
  (cl:format cl:nil "int32 exposure~%int32 gain~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetExposureGain-request)))
  "Returns full string definition for message of type 'SetExposureGain-request"
  (cl:format cl:nil "int32 exposure~%int32 gain~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetExposureGain-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetExposureGain-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetExposureGain-request
    (cl:cons ':exposure (exposure msg))
    (cl:cons ':gain (gain msg))
))
;//! \htmlinclude SetExposureGain-response.msg.html

(cl:defclass <SetExposureGain-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetExposureGain-response (<SetExposureGain-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetExposureGain-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetExposureGain-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name azure_kinect_ros_driver-srv:<SetExposureGain-response> is deprecated: use azure_kinect_ros_driver-srv:SetExposureGain-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetExposureGain-response>) ostream)
  "Serializes a message object of type '<SetExposureGain-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetExposureGain-response>) istream)
  "Deserializes a message object of type '<SetExposureGain-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetExposureGain-response>)))
  "Returns string type for a service object of type '<SetExposureGain-response>"
  "azure_kinect_ros_driver/SetExposureGainResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetExposureGain-response)))
  "Returns string type for a service object of type 'SetExposureGain-response"
  "azure_kinect_ros_driver/SetExposureGainResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetExposureGain-response>)))
  "Returns md5sum for a message object of type '<SetExposureGain-response>"
  "118f5ae9e1aacf44af9d676470ddbbdf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetExposureGain-response)))
  "Returns md5sum for a message object of type 'SetExposureGain-response"
  "118f5ae9e1aacf44af9d676470ddbbdf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetExposureGain-response>)))
  "Returns full string definition for message of type '<SetExposureGain-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetExposureGain-response)))
  "Returns full string definition for message of type 'SetExposureGain-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetExposureGain-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetExposureGain-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetExposureGain-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetExposureGain)))
  'SetExposureGain-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetExposureGain)))
  'SetExposureGain-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetExposureGain)))
  "Returns string type for a service object of type '<SetExposureGain>"
  "azure_kinect_ros_driver/SetExposureGain")