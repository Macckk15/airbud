;; Auto-generated. Do not edit!


(when (boundp 'drone_controller::MoveDroneW)
  (if (not (find-package "DRONE_CONTROLLER"))
    (make-package "DRONE_CONTROLLER"))
  (shadow 'MoveDroneW (find-package "DRONE_CONTROLLER")))
(unless (find-package "DRONE_CONTROLLER::MOVEDRONEW")
  (make-package "DRONE_CONTROLLER::MOVEDRONEW"))
(unless (find-package "DRONE_CONTROLLER::MOVEDRONEWREQUEST")
  (make-package "DRONE_CONTROLLER::MOVEDRONEWREQUEST"))
(unless (find-package "DRONE_CONTROLLER::MOVEDRONEWRESPONSE")
  (make-package "DRONE_CONTROLLER::MOVEDRONEWRESPONSE"))

(in-package "ROS")





(defclass drone_controller::MoveDroneWRequest
  :super ros::object
  :slots (_dx _dy _dalt _dyaw ))

(defmethod drone_controller::MoveDroneWRequest
  (:init
   (&key
    ((:dx __dx) 0.0)
    ((:dy __dy) 0.0)
    ((:dalt __dalt) 0.0)
    ((:dyaw __dyaw) 0.0)
    )
   (send-super :init)
   (setq _dx (float __dx))
   (setq _dy (float __dy))
   (setq _dalt (float __dalt))
   (setq _dyaw (float __dyaw))
   self)
  (:dx
   (&optional __dx)
   (if __dx (setq _dx __dx)) _dx)
  (:dy
   (&optional __dy)
   (if __dy (setq _dy __dy)) _dy)
  (:dalt
   (&optional __dalt)
   (if __dalt (setq _dalt __dalt)) _dalt)
  (:dyaw
   (&optional __dyaw)
   (if __dyaw (setq _dyaw __dyaw)) _dyaw)
  (:serialization-length
   ()
   (+
    ;; float64 _dx
    8
    ;; float64 _dy
    8
    ;; float64 _dalt
    8
    ;; float64 _dyaw
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _dx
       (sys::poke _dx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dy
       (sys::poke _dy (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dalt
       (sys::poke _dalt (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dyaw
       (sys::poke _dyaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _dx
     (setq _dx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dy
     (setq _dy (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dalt
     (setq _dalt (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dyaw
     (setq _dyaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass drone_controller::MoveDroneWResponse
  :super ros::object
  :slots (_command_status ))

(defmethod drone_controller::MoveDroneWResponse
  (:init
   (&key
    ((:command_status __command_status) nil)
    )
   (send-super :init)
   (setq _command_status __command_status)
   self)
  (:command_status
   (&optional __command_status)
   (if __command_status (setq _command_status __command_status)) _command_status)
  (:serialization-length
   ()
   (+
    ;; bool _command_status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _command_status
       (if _command_status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _command_status
     (setq _command_status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass drone_controller::MoveDroneW
  :super ros::object
  :slots ())

(setf (get drone_controller::MoveDroneW :md5sum-) "07cc5e7856beb68b29432db43546cf40")
(setf (get drone_controller::MoveDroneW :datatype-) "drone_controller/MoveDroneW")
(setf (get drone_controller::MoveDroneW :request) drone_controller::MoveDroneWRequest)
(setf (get drone_controller::MoveDroneW :response) drone_controller::MoveDroneWResponse)

(defmethod drone_controller::MoveDroneWRequest
  (:response () (instance drone_controller::MoveDroneWResponse :init)))

(setf (get drone_controller::MoveDroneWRequest :md5sum-) "07cc5e7856beb68b29432db43546cf40")
(setf (get drone_controller::MoveDroneWRequest :datatype-) "drone_controller/MoveDroneWRequest")
(setf (get drone_controller::MoveDroneWRequest :definition-)
      "float64 dx
float64 dy
float64 dalt
float64 dyaw
---
bool    command_status

")

(setf (get drone_controller::MoveDroneWResponse :md5sum-) "07cc5e7856beb68b29432db43546cf40")
(setf (get drone_controller::MoveDroneWResponse :datatype-) "drone_controller/MoveDroneWResponse")
(setf (get drone_controller::MoveDroneWResponse :definition-)
      "float64 dx
float64 dy
float64 dalt
float64 dyaw
---
bool    command_status

")



(provide :drone_controller/MoveDroneW "07cc5e7856beb68b29432db43546cf40")


