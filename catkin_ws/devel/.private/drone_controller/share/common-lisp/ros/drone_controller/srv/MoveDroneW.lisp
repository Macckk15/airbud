; Auto-generated. Do not edit!


(cl:in-package drone_controller-srv)


;//! \htmlinclude MoveDroneW-request.msg.html

(cl:defclass <MoveDroneW-request> (roslisp-msg-protocol:ros-message)
  ((dx
    :reader dx
    :initarg :dx
    :type cl:float
    :initform 0.0)
   (dy
    :reader dy
    :initarg :dy
    :type cl:float
    :initform 0.0)
   (dalt
    :reader dalt
    :initarg :dalt
    :type cl:float
    :initform 0.0)
   (dyaw
    :reader dyaw
    :initarg :dyaw
    :type cl:float
    :initform 0.0))
)

(cl:defclass MoveDroneW-request (<MoveDroneW-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveDroneW-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveDroneW-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drone_controller-srv:<MoveDroneW-request> is deprecated: use drone_controller-srv:MoveDroneW-request instead.")))

(cl:ensure-generic-function 'dx-val :lambda-list '(m))
(cl:defmethod dx-val ((m <MoveDroneW-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:dx-val is deprecated.  Use drone_controller-srv:dx instead.")
  (dx m))

(cl:ensure-generic-function 'dy-val :lambda-list '(m))
(cl:defmethod dy-val ((m <MoveDroneW-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:dy-val is deprecated.  Use drone_controller-srv:dy instead.")
  (dy m))

(cl:ensure-generic-function 'dalt-val :lambda-list '(m))
(cl:defmethod dalt-val ((m <MoveDroneW-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:dalt-val is deprecated.  Use drone_controller-srv:dalt instead.")
  (dalt m))

(cl:ensure-generic-function 'dyaw-val :lambda-list '(m))
(cl:defmethod dyaw-val ((m <MoveDroneW-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:dyaw-val is deprecated.  Use drone_controller-srv:dyaw instead.")
  (dyaw m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveDroneW-request>) ostream)
  "Serializes a message object of type '<MoveDroneW-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dalt))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dyaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveDroneW-request>) istream)
  "Deserializes a message object of type '<MoveDroneW-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dx) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dy) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dalt) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dyaw) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveDroneW-request>)))
  "Returns string type for a service object of type '<MoveDroneW-request>"
  "drone_controller/MoveDroneWRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveDroneW-request)))
  "Returns string type for a service object of type 'MoveDroneW-request"
  "drone_controller/MoveDroneWRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveDroneW-request>)))
  "Returns md5sum for a message object of type '<MoveDroneW-request>"
  "07cc5e7856beb68b29432db43546cf40")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveDroneW-request)))
  "Returns md5sum for a message object of type 'MoveDroneW-request"
  "07cc5e7856beb68b29432db43546cf40")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveDroneW-request>)))
  "Returns full string definition for message of type '<MoveDroneW-request>"
  (cl:format cl:nil "float64 dx~%float64 dy~%float64 dalt~%float64 dyaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveDroneW-request)))
  "Returns full string definition for message of type 'MoveDroneW-request"
  (cl:format cl:nil "float64 dx~%float64 dy~%float64 dalt~%float64 dyaw~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveDroneW-request>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveDroneW-request>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveDroneW-request
    (cl:cons ':dx (dx msg))
    (cl:cons ':dy (dy msg))
    (cl:cons ':dalt (dalt msg))
    (cl:cons ':dyaw (dyaw msg))
))
;//! \htmlinclude MoveDroneW-response.msg.html

(cl:defclass <MoveDroneW-response> (roslisp-msg-protocol:ros-message)
  ((command_status
    :reader command_status
    :initarg :command_status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass MoveDroneW-response (<MoveDroneW-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveDroneW-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveDroneW-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name drone_controller-srv:<MoveDroneW-response> is deprecated: use drone_controller-srv:MoveDroneW-response instead.")))

(cl:ensure-generic-function 'command_status-val :lambda-list '(m))
(cl:defmethod command_status-val ((m <MoveDroneW-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader drone_controller-srv:command_status-val is deprecated.  Use drone_controller-srv:command_status instead.")
  (command_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveDroneW-response>) ostream)
  "Serializes a message object of type '<MoveDroneW-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'command_status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveDroneW-response>) istream)
  "Deserializes a message object of type '<MoveDroneW-response>"
    (cl:setf (cl:slot-value msg 'command_status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveDroneW-response>)))
  "Returns string type for a service object of type '<MoveDroneW-response>"
  "drone_controller/MoveDroneWResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveDroneW-response)))
  "Returns string type for a service object of type 'MoveDroneW-response"
  "drone_controller/MoveDroneWResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveDroneW-response>)))
  "Returns md5sum for a message object of type '<MoveDroneW-response>"
  "07cc5e7856beb68b29432db43546cf40")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveDroneW-response)))
  "Returns md5sum for a message object of type 'MoveDroneW-response"
  "07cc5e7856beb68b29432db43546cf40")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveDroneW-response>)))
  "Returns full string definition for message of type '<MoveDroneW-response>"
  (cl:format cl:nil "bool    command_status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveDroneW-response)))
  "Returns full string definition for message of type 'MoveDroneW-response"
  (cl:format cl:nil "bool    command_status~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveDroneW-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveDroneW-response>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveDroneW-response
    (cl:cons ':command_status (command_status msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'MoveDroneW)))
  'MoveDroneW-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'MoveDroneW)))
  'MoveDroneW-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveDroneW)))
  "Returns string type for a service object of type '<MoveDroneW>"
  "drone_controller/MoveDroneW")