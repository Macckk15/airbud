
(cl:in-package :asdf)

(defsystem "drone_controller-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MoveDroneW" :depends-on ("_package_MoveDroneW"))
    (:file "_package_MoveDroneW" :depends-on ("_package"))
    (:file "SetRefPose" :depends-on ("_package_SetRefPose"))
    (:file "_package_SetRefPose" :depends-on ("_package"))
  ))