; Auto-generated. Do not edit!


(cl:in-package drone_controller-srv)


;//! \htmlinclude SetRefPose-request.msg.html

(cl:defclass <SetRefPose-request> (roslisp-msg-protocol:ros-message)
  ((x_ref_w
    :reader x_ref_w
    :initarg :x_ref_w
    :type cl:float
    :initform 0.0)
   (y_ref_w
    :reader y_ref_w
    :initarg :y_ref_w
    :type cl:float
    :initform 0.0)
   (alt_ref_w
    :reader alt_ref_w
    :initarg :alt_ref_w
    :type cl:float
    :initform 0.0)
   (yaw_ref_w
    :reader yaw_ref_w
    :initarg :yaw_ref_w
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetRefPose-request (<SetRefPose-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRefPose-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRefPose-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drone_controller-srv:<SetRefPose-request> is deprecated: use drone_controller-srv:SetRefPose-request instead.")))

(cl:ensure-generic-function 'x_ref_w-val :lambda-list '(m))
(cl:defmethod x_ref_w-val ((m <SetRefPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:x_ref_w-val is deprecated.  Use drone_controller-srv:x_ref_w instead.")
  (x_ref_w m))

(cl:ensure-generic-function 'y_ref_w-val :lambda-list '(m))
(cl:defmethod y_ref_w-val ((m <SetRefPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:y_ref_w-val is deprecated.  Use drone_controller-srv:y_ref_w instead.")
  (y_ref_w m))

(cl:ensure-generic-function 'alt_ref_w-val :lambda-list '(m))
(cl:defmethod alt_ref_w-val ((m <SetRefPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:alt_ref_w-val is deprecated.  Use drone_controller-srv:alt_ref_w instead.")
  (alt_ref_w m))

(cl:ensure-generic-function 'yaw_ref_w-val :lambda-list '(m))
(cl:defmethod yaw_ref_w-val ((m <SetRefPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:yaw_ref_w-val is deprecated.  Use drone_controller-srv:yaw_ref_w instead.")
  (yaw_ref_w m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRefPose-request>) ostream)
  "Serializes a message object of type '<SetRefPose-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x_ref_w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y_ref_w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'alt_ref_w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'yaw_ref_w))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRefPose-request>) istream)
  "Deserializes a message object of type '<SetRefPose-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_ref_w) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y_ref_w) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'alt_ref_w) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_ref_w) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRefPose-request>)))
  "Returns string type for a service object of type '<SetRefPose-request>"
  "drone_controller/SetRefPoseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRefPose-request)))
  "Returns string type for a service object of type 'SetRefPose-request"
  "drone_controller/SetRefPoseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRefPose-request>)))
  "Returns md5sum for a message object of type '<SetRefPose-request>"
  "a121ec35e34f22c1f30911ae51c46c9f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRefPose-request)))
  "Returns md5sum for a message object of type 'SetRefPose-request"
  "a121ec35e34f22c1f30911ae51c46c9f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRefPose-request>)))
  "Returns full string definition for message of type '<SetRefPose-request>"
  (cl:format cl:nil "float64 x_ref_w~%float64 y_ref_w~%float64 alt_ref_w~%float64 yaw_ref_w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRefPose-request)))
  "Returns full string definition for message of type 'SetRefPose-request"
  (cl:format cl:nil "float64 x_ref_w~%float64 y_ref_w~%float64 alt_ref_w~%float64 yaw_ref_w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRefPose-request>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRefPose-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRefPose-request
    (cl:cons ':x_ref_w (x_ref_w msg))
    (cl:cons ':y_ref_w (y_ref_w msg))
    (cl:cons ':alt_ref_w (alt_ref_w msg))
    (cl:cons ':yaw_ref_w (yaw_ref_w msg))
))
;//! \htmlinclude SetRefPose-response.msg.html

(cl:defclass <SetRefPose-response> (roslisp-msg-protocol:ros-message)
  ((update_status
    :reader update_status
    :initarg :update_status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetRefPose-response (<SetRefPose-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetRefPose-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetRefPose-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drone_controller-srv:<SetRefPose-response> is deprecated: use drone_controller-srv:SetRefPose-response instead.")))

(cl:ensure-generic-function 'update_status-val :lambda-list '(m))
(cl:defmethod update_status-val ((m <SetRefPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:update_status-val is deprecated.  Use drone_controller-srv:update_status instead.")
  (update_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetRefPose-response>) ostream)
  "Serializes a message object of type '<SetRefPose-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'update_status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetRefPose-response>) istream)
  "Deserializes a message object of type '<SetRefPose-response>"
    (cl:setf (cl:slot-value msg 'update_status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetRefPose-response>)))
  "Returns string type for a service object of type '<SetRefPose-response>"
  "drone_controller/SetRefPoseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRefPose-response)))
  "Returns string type for a service object of type 'SetRefPose-response"
  "drone_controller/SetRefPoseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetRefPose-response>)))
  "Returns md5sum for a message object of type '<SetRefPose-response>"
  "a121ec35e34f22c1f30911ae51c46c9f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetRefPose-response)))
  "Returns md5sum for a message object of type 'SetRefPose-response"
  "a121ec35e34f22c1f30911ae51c46c9f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetRefPose-response>)))
  "Returns full string definition for message of type '<SetRefPose-response>"
  (cl:format cl:nil "bool  update_status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetRefPose-response)))
  "Returns full string definition for message of type 'SetRefPose-response"
  (cl:format cl:nil "bool  update_status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetRefPose-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetRefPose-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetRefPose-response
    (cl:cons ':update_status (update_status msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetRefPose)))
  'SetRefPose-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetRefPose)))
  'SetRefPose-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetRefPose)))
  "Returns string type for a service object of type '<SetRefPose>"
  "drone_controller/SetRefPose")