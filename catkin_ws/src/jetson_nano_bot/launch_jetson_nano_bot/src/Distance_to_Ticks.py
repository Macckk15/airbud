#!/usr/bin/env python

import rospy
from nav_msgs.msg import Path
from geometry_msgs.msg import Twist
from std_msgs.msg import Int64
import math

class TicksCalculator:
    def __init__(self, ticks_per_rev, wheel_distance, wheel_radius):
        self.ticks_per_rev = ticks_per_rev
        self.wheel_distance = wheel_distance
        self.wheel_radius = wheel_radius
        self.left_ticks_pub = rospy.Publisher('left_encoder_ticks', Int64, queue_size=10)
        self.right_ticks_pub = rospy.Publisher('right_encoder_ticks', Int64, queue_size=10)
        rospy.Subscriber('move_base/GlobalPlanner/plan', Path, self.path_callback)
        rospy.spin()

    def path_callback(self, msg):
        path = msg.poses
        left_ticks = 0
        right_ticks = 0
        for i in range(len(path) - 1):
            x1 = path[i].pose.position.x
            y1 = path[i].pose.position.y
            x2 = path[i+1].pose.position.x
            y2 = path[i+1].pose.position.y
            distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
            angle = math.atan2(y2 - y1, x2 - x1)
            linear_vel = 0.1 
            angular_vel = 0 
            if i == len(path) - 2:
                goal_distance = math.sqrt((x2 - path[0].pose.position.x)**2 + (y2 - path[0].pose.position.y)**2)
                linear_vel = goal_distance / distance * linear_vel
            left_ticks += (linear_vel - angular_vel * self.wheel_distance/2) / (2 * math.pi * self.wheel_radius) * self.ticks_per_rev
            right_ticks += (linear_vel + angular_vel * self.wheel_distance/2) / (2 * math.pi * self.wheel_radius) * self.ticks_per_rev
            self.left_ticks_pub.publish(left_ticks)
            self.right_ticks_pub.publish(right_ticks)

if __name__ == '__main__':
    rospy.init_node('ticks_calculator_node')
    ticks_per_rev = 142
    wheel_distance = 0.17
    wheel_radius = 0.033
    TicksCalculator(ticks_per_rev, wheel_distance, wheel_radius)