;; Auto-generated. Do not edit!


(when (boundp 'drone_controller::SetRefPose)
  (if (not (find-package "DRONE_CONTROLLER"))
    (make-package "DRONE_CONTROLLER"))
  (shadow 'SetRefPose (find-package "DRONE_CONTROLLER")))
(unless (find-package "DRONE_CONTROLLER::SETREFPOSE")
  (make-package "DRONE_CONTROLLER::SETREFPOSE"))
(unless (find-package "DRONE_CONTROLLER::SETREFPOSEREQUEST")
  (make-package "DRONE_CONTROLLER::SETREFPOSEREQUEST"))
(unless (find-package "DRONE_CONTROLLER::SETREFPOSERESPONSE")
  (make-package "DRONE_CONTROLLER::SETREFPOSERESPONSE"))

(in-package "ROS")





(defclass drone_controller::SetRefPoseRequest
  :super ros::object
  :slots (_x_ref_w _y_ref_w _alt_ref_w _yaw_ref_w ))

(defmethod drone_controller::SetRefPoseRequest
  (:init
   (&key
    ((:x_ref_w __x_ref_w) 0.0)
    ((:y_ref_w __y_ref_w) 0.0)
    ((:alt_ref_w __alt_ref_w) 0.0)
    ((:yaw_ref_w __yaw_ref_w) 0.0)
    )
   (send-super :init)
   (setq _x_ref_w (float __x_ref_w))
   (setq _y_ref_w (float __y_ref_w))
   (setq _alt_ref_w (float __alt_ref_w))
   (setq _yaw_ref_w (float __yaw_ref_w))
   self)
  (:x_ref_w
   (&optional __x_ref_w)
   (if __x_ref_w (setq _x_ref_w __x_ref_w)) _x_ref_w)
  (:y_ref_w
   (&optional __y_ref_w)
   (if __y_ref_w (setq _y_ref_w __y_ref_w)) _y_ref_w)
  (:alt_ref_w
   (&optional __alt_ref_w)
   (if __alt_ref_w (setq _alt_ref_w __alt_ref_w)) _alt_ref_w)
  (:yaw_ref_w
   (&optional __yaw_ref_w)
   (if __yaw_ref_w (setq _yaw_ref_w __yaw_ref_w)) _yaw_ref_w)
  (:serialization-length
   ()
   (+
    ;; float64 _x_ref_w
    8
    ;; float64 _y_ref_w
    8
    ;; float64 _alt_ref_w
    8
    ;; float64 _yaw_ref_w
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x_ref_w
       (sys::poke _x_ref_w (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y_ref_w
       (sys::poke _y_ref_w (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _alt_ref_w
       (sys::poke _alt_ref_w (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw_ref_w
       (sys::poke _yaw_ref_w (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x_ref_w
     (setq _x_ref_w (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y_ref_w
     (setq _y_ref_w (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _alt_ref_w
     (setq _alt_ref_w (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw_ref_w
     (setq _yaw_ref_w (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass drone_controller::SetRefPoseResponse
  :super ros::object
  :slots (_update_status ))

(defmethod drone_controller::SetRefPoseResponse
  (:init
   (&key
    ((:update_status __update_status) nil)
    )
   (send-super :init)
   (setq _update_status __update_status)
   self)
  (:update_status
   (&optional __update_status)
   (if __update_status (setq _update_status __update_status)) _update_status)
  (:serialization-length
   ()
   (+
    ;; bool _update_status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _update_status
       (if _update_status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _update_status
     (setq _update_status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass drone_controller::SetRefPose
  :super ros::object
  :slots ())

(setf (get drone_controller::SetRefPose :md5sum-) "a121ec35e34f22c1f30911ae51c46c9f")
(setf (get drone_controller::SetRefPose :datatype-) "drone_controller/SetRefPose")
(setf (get drone_controller::SetRefPose :request) drone_controller::SetRefPoseRequest)
(setf (get drone_controller::SetRefPose :response) drone_controller::SetRefPoseResponse)

(defmethod drone_controller::SetRefPoseRequest
  (:response () (instance drone_controller::SetRefPoseResponse :init)))

(setf (get drone_controller::SetRefPoseRequest :md5sum-) "a121ec35e34f22c1f30911ae51c46c9f")
(setf (get drone_controller::SetRefPoseRequest :datatype-) "drone_controller/SetRefPoseRequest")
(setf (get drone_controller::SetRefPoseRequest :definition-)
      "float64 x_ref_w
float64 y_ref_w
float64 alt_ref_w
float64 yaw_ref_w
---
bool  update_status
")

(setf (get drone_controller::SetRefPoseResponse :md5sum-) "a121ec35e34f22c1f30911ae51c46c9f")
(setf (get drone_controller::SetRefPoseResponse :datatype-) "drone_controller/SetRefPoseResponse")
(setf (get drone_controller::SetRefPoseResponse :definition-)
      "float64 x_ref_w
float64 y_ref_w
float64 alt_ref_w
float64 yaw_ref_w
---
bool  update_status
")



(provide :drone_controller/SetRefPose "a121ec35e34f22c1f30911ae51c46c9f")


