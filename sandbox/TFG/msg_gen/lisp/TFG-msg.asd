
(cl:in-package :asdf)

(defsystem "TFG-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "HandPointCloud" :depends-on ("_package_HandPointCloud"))
    (:file "_package_HandPointCloud" :depends-on ("_package"))
    (:file "Features2D" :depends-on ("_package_Features2D"))
    (:file "_package_Features2D" :depends-on ("_package"))
    (:file "HandLoc" :depends-on ("_package_HandLoc"))
    (:file "_package_HandLoc" :depends-on ("_package"))
  ))