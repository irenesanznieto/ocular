
(cl:in-package :asdf)

(defsystem "TFG-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "EventHandler" :depends-on ("_package_EventHandler"))
    (:file "_package_EventHandler" :depends-on ("_package"))
    (:file "HandPointCloud" :depends-on ("_package_HandPointCloud"))
    (:file "_package_HandPointCloud" :depends-on ("_package"))
    (:file "HandLoc" :depends-on ("_package_HandLoc"))
    (:file "_package_HandLoc" :depends-on ("_package"))
    (:file "Features2D" :depends-on ("_package_Features2D"))
    (:file "_package_Features2D" :depends-on ("_package"))
    (:file "HandImage" :depends-on ("_package_HandImage"))
    (:file "_package_HandImage" :depends-on ("_package"))
    (:file "HandLocPx" :depends-on ("_package_HandLocPx"))
    (:file "_package_HandLocPx" :depends-on ("_package"))
  ))