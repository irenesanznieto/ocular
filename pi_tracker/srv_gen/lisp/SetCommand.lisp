; Auto-generated. Do not edit!


(cl:in-package pi_tracker-srv)


;//! \htmlinclude SetCommand-request.msg.html

(cl:defclass <SetCommand-request> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type cl:string
    :initform ""))
)

(cl:defclass SetCommand-request (<SetCommand-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCommand-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCommand-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pi_tracker-srv:<SetCommand-request> is deprecated: use pi_tracker-srv:SetCommand-request instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <SetCommand-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pi_tracker-srv:command-val is deprecated.  Use pi_tracker-srv:command instead.")
  (command m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCommand-request>) ostream)
  "Serializes a message object of type '<SetCommand-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'command))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'command))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCommand-request>) istream)
  "Deserializes a message object of type '<SetCommand-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'command) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCommand-request>)))
  "Returns string type for a service object of type '<SetCommand-request>"
  "pi_tracker/SetCommandRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCommand-request)))
  "Returns string type for a service object of type 'SetCommand-request"
  "pi_tracker/SetCommandRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCommand-request>)))
  "Returns md5sum for a message object of type '<SetCommand-request>"
  "cba5e21e920a3a2b7b375cb65b64cdea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCommand-request)))
  "Returns md5sum for a message object of type 'SetCommand-request"
  "cba5e21e920a3a2b7b375cb65b64cdea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCommand-request>)))
  "Returns full string definition for message of type '<SetCommand-request>"
  (cl:format cl:nil "string command~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCommand-request)))
  "Returns full string definition for message of type 'SetCommand-request"
  (cl:format cl:nil "string command~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCommand-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'command))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCommand-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCommand-request
    (cl:cons ':command (command msg))
))
;//! \htmlinclude SetCommand-response.msg.html

(cl:defclass <SetCommand-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetCommand-response (<SetCommand-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCommand-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCommand-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pi_tracker-srv:<SetCommand-response> is deprecated: use pi_tracker-srv:SetCommand-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCommand-response>) ostream)
  "Serializes a message object of type '<SetCommand-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCommand-response>) istream)
  "Deserializes a message object of type '<SetCommand-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCommand-response>)))
  "Returns string type for a service object of type '<SetCommand-response>"
  "pi_tracker/SetCommandResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCommand-response)))
  "Returns string type for a service object of type 'SetCommand-response"
  "pi_tracker/SetCommandResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCommand-response>)))
  "Returns md5sum for a message object of type '<SetCommand-response>"
  "cba5e21e920a3a2b7b375cb65b64cdea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCommand-response)))
  "Returns md5sum for a message object of type 'SetCommand-response"
  "cba5e21e920a3a2b7b375cb65b64cdea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCommand-response>)))
  "Returns full string definition for message of type '<SetCommand-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCommand-response)))
  "Returns full string definition for message of type 'SetCommand-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCommand-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCommand-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCommand-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetCommand)))
  'SetCommand-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetCommand)))
  'SetCommand-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCommand)))
  "Returns string type for a service object of type '<SetCommand>"
  "pi_tracker/SetCommand")