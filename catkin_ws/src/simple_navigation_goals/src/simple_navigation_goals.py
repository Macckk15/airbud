#!/usr/bin/env python
# license removed for brevity

import rospy
import actionlib
import numpy as np
import cv2
from start_cameras import Start_Cameras
import qr_funcs
from tf.transformations import euler_from_quaternion, quaternion_from_euler
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Twist
from actionlib import SimpleActionClient
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_msgs.msg import String

distance = 0
Entrance = False

'''
def ScanQRCode():
    left_camera = Start_Cameras(0).start()

    print("mason")

    # may need a way to tell if camera not opened
    err_bound =[[0, 0], 
                [0, 0]]

    while True:

        # Capture frame-by-frame
        left_grabbed, left_frame = left_camera.read()

        # if frame is read correctly ret is True
        if not (left_grabbed):
            print("Can't receive frame (stream end?). Exiting ...")
        # Our operations on the frame come here
        
        cv2.imshow('frame', left_frame)
        cv2.waitKey(1)

        gray_qr = cv2.cvtColor(left_frame, cv2.COLOR_BGR2GRAY)

        qr_funcs.postprocess(gray_qr)
        #pt1, pt2, pt3, pt4, bound, rect_w, rect_h = qr_funcs.paperBound(left_frame)
        #if (bound != err_bound):
            
            #qr_funcs.findCorners(pt1, pt2, pt3, pt4, bound, left_frame, rect_w, rect_h)
        # Display the resulting frame
        if cv2.waitKey(1) == ord('q'):
            break

        # When everything done, release the capture
    left_camera.stop()
    left_camera.release()
    cv2.destroyAllWindows()
'''
def entrance_callback(msg):
    if msg.data == "Found Entrance":
        Entrance = True
    else:
        Entrance = False
    print(Entrance)

def scan_callback(data):
    global distance
    distance_msg = data.data
    distance_whole = float(distance_msg)
    distance = round(distance_whole, 2)
    print(distance)
	
    

def movebase_client():
    global distance
   # Create an action client called "move_base" with action definition file "MoveBaseAction"
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
 
   # Waits until the action server has started up and started listening for goals.
    client.wait_for_server()

    # Use the distance from data.data in order to send the command to maneuver towards the box
    # After robot is in front of the box, move another 10 in to be inside of the box


   # Creates a new goal with the MoveBaseGoal constructor
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "base_link"
    goal.target_pose.header.stamp = rospy.Time.now()

    goal.target_pose.pose.position.x = distance + .254 #<-- Set the distance variable here that is calculated
    goal.target_pose.pose.position.y = 0.0
    roll = 0
    pitch = 0
    yaw = 0
    (xr, yr, zr, w) = quaternion_from_euler(roll, pitch, yaw)
    goal.target_pose.pose.orientation.x = xr
    goal.target_pose.pose.orientation.y = yr
    goal.target_pose.pose.orientation.z = zr
    goal.target_pose.pose.orientation.w = w
   # No rotation of the mobile base frame w.r.t. map frame

   # Sends the goal to the action server.
    client.send_goal(goal)
   # Waits for the server to finish performing the action.


    client.wait_for_result()
   # If the result doesn't arrive, assume the Server is not available
    # Result of executing the action
    return client.get_result()   

'''
def movebase_client_outisde_box():
    global distance
   # Create an action client called "move_base" with action definition file "MoveBaseAction"
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
 
   # Waits until the action server has started up and started listening for goals.
    client.wait_for_server()

    # Use the distance from data.data in order to send the command to maneuver towards the box
    # After robot is in front of the box, move another 10 in to be inside of the box


   # Creates a new goal with the MoveBaseGoal constructor
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()

    goal.target_pose.pose.position.x = distance + .65 #<-- Set the distance variable here that is calculated
    goal.target_pose.pose.position.y = 0.0
    roll = 0
    pitch = 0
    yaw = 0
    (xr, yr, zr, w) = quaternion_from_euler(roll, pitch, yaw)
    goal.target_pose.pose.orientation.x = xr
    goal.target_pose.pose.orientation.y = yr
    goal.target_pose.pose.orientation.z = zr
    goal.target_pose.pose.orientation.w = w
   # No rotation of the mobile base frame w.r.t. map frame

   # Sends the goal to the action server.
    client.send_goal(goal)
   # Waits for the server to finish performing the action.


    client.wait_for_result()
   # If the result doesn't arrive, assume the Server is not available
    # Result of executing the action
    return client.get_result() 

'''


    
# If the python node is executed as main process (sourced directly)
if __name__ == '__main__':
    try:
        # Initializes a rospy node to let the SimpleActionClient publish and subscribe
        rospy.init_node('movebase_client_py')
        rospy.Subscriber('/scan_listener', String,  scan_callback)
        rospy.Subscriber('/Entrance_msg', String,  entrance_callback)
        if Entrance == True:
            result = movebase_client()
            if result:
                    rospy.loginfo("Goal execution done!")
                    #ScanQRCode()
                    #result2 = movebase_client_outisde_box()
    except rospy.ROSInterruptException:
                rospy.loginfo("Navigation test finished.")
