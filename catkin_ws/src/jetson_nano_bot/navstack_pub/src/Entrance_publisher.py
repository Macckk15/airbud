#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
import numpy as np
import cv2
from start_cameras import Start_Cameras
import qr_funcs
import time


def talker():
                # may need a way to tell if camera not opened
    err_bound =[[0, 0], 
                [0, 0]]

    left_camera = Start_Cameras(0).start()
    while not rospy.is_shutdown():

        while True:
            # Capture frame-by-frame
            left_grabbed, left_frame = left_camera.read()

            # Our operations on the frame come here

            blur = cv2.GaussianBlur(left_frame,(15,15),0)

            cv2.imshow('Frame', left_frame)
            cv2.waitKey(1)

            detected, entrance = qr_funcs.detectEntrance(blur)

            if (detected):
                entrace_detected = "Found Entrance"
                cv2.imshow("Detected Lines (in green) - Probabilistic Line Transform", entrance) 
                cv2.waitKey(1)
            
            else:
                entrace_detected = "No Entrance"

            if cv2.waitKey(1) == ord('q'):
                break 

            # When everything done, release the capture

            pub = rospy.Publisher('Entrance_msg', String, queue_size=10)
            rospy.init_node('detected_entrance', anonymous=True)
            rate = rospy.Rate(10) # 10hz 
            rospy.loginfo(entrace_detected)
            pub.publish(entrace_detected)
            rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        left_camera.stop()
        left_camera.release()
        cv2.destroyAllWindows()
        pass
        