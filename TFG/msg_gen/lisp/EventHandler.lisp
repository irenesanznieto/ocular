; Auto-generated. Do not edit!


(cl:in-package TFG-msg)


;//! \htmlinclude EventHandler.msg.html

(cl:defclass <EventHandler> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (hand
    :reader hand
    :initarg :hand
    :type cl:string
    :initform "")
   (event
    :reader event
    :initarg :event
    :type cl:string
    :initform "")
   (last_event
    :reader last_event
    :initarg :last_event
    :type cl:string
    :initform ""))
)

(cl:defclass EventHandler (<EventHandler>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <EventHandler>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'EventHandler)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name TFG-msg:<EventHandler> is deprecated: use TFG-msg:EventHandler instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <EventHandler>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader TFG-msg:header-val is deprecated.  Use TFG-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'hand-val :lambda-list '(m))
(cl:defmethod hand-val ((m <EventHandler>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader TFG-msg:hand-val is deprecated.  Use TFG-msg:hand instead.")
  (hand m))

(cl:ensure-generic-function 'event-val :lambda-list '(m))
(cl:defmethod event-val ((m <EventHandler>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader TFG-msg:event-val is deprecated.  Use TFG-msg:event instead.")
  (event m))

(cl:ensure-generic-function 'last_event-val :lambda-list '(m))
(cl:defmethod last_event-val ((m <EventHandler>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader TFG-msg:last_event-val is deprecated.  Use TFG-msg:last_event instead.")
  (last_event m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <EventHandler>) ostream)
  "Serializes a message object of type '<EventHandler>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'hand))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'hand))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'event))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'event))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'last_event))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'last_event))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <EventHandler>) istream)
  "Deserializes a message object of type '<EventHandler>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'hand) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'hand) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'event) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'event) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'last_event) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'last_event) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<EventHandler>)))
  "Returns string type for a message object of type '<EventHandler>"
  "TFG/EventHandler")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'EventHandler)))
  "Returns string type for a message object of type 'EventHandler"
  "TFG/EventHandler")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<EventHandler>)))
  "Returns md5sum for a message object of type '<EventHandler>"
  "fa3dfe829c08e3650e3e356e080b85ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'EventHandler)))
  "Returns md5sum for a message object of type 'EventHandler"
  "fa3dfe829c08e3650e3e356e080b85ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<EventHandler>)))
  "Returns full string definition for message of type '<EventHandler>"
  (cl:format cl:nil "Header header~%string hand~%string event~%string last_event~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'EventHandler)))
  "Returns full string definition for message of type 'EventHandler"
  (cl:format cl:nil "Header header~%string hand~%string event~%string last_event~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <EventHandler>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'hand))
     4 (cl:length (cl:slot-value msg 'event))
     4 (cl:length (cl:slot-value msg 'last_event))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <EventHandler>))
  "Converts a ROS message object to a list"
  (cl:list 'EventHandler
    (cl:cons ':header (header msg))
    (cl:cons ':hand (hand msg))
    (cl:cons ':event (event msg))
    (cl:cons ':last_event (last_event msg))
))
