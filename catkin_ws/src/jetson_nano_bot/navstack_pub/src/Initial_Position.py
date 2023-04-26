#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped

def talker():
    while not rospy.is_shutdown():
        rospy.init_node('set_initial_pose')
        pub = rospy.Publisher('/initial_2d', PoseStamped, queue_size=10)
        initial_pose = PoseStamped()
        initial_pose.header.stamp = rospy.Time.now()
        initial_pose.header.frame_id = 'map'
        initial_pose.pose.position.x = 0.0
        initial_pose.pose.position.y = 0.0
        initial_pose.pose.position.z = 0.0
        initial_pose.pose.orientation.x = 0.0
        initial_pose.pose.orientation.y = 0.0
        initial_pose.pose.orientation.z = 0.0
        initial_pose.pose.orientation.w = 1.0
        pub.publish(initial_pose)
        rospy.sleep(1)

if __name__ == '__main__':
    try:
        talker()			
    except rospy.ROSInterruptException:
        pass