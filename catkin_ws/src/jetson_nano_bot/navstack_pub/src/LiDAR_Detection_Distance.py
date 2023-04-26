#!/usr/bin/env python


import rospy
import math
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String


scanpub = rospy.Publisher('scan_listener', String, queue_size=10)
angle_sum = 0.0
count = 0

def callback(data):     
    # Define the indices of the relevant angle range
    min_index = 520
    max_index = 620
    global angle_sum, count
    total_distance = 0

    # Extract the relevant ranges from the LaserScan message
    ranges = data.ranges

    # Print the ranges within the relevant angle range
    for i in range(min_index, max_index+1):
        if not math.isinf(ranges[i]):
            if ranges[i] < 10:
                '''print("Range at angle {:.2f}: {:.2f} meters".format(data.angle_min + i*data.angle_increment, ranges[i]))'''
                total_distance += ranges[i]
                angle_sum += data.angle_min + i*data.angle_increment
                count += 1
                Avg = total_distance / count

if __name__ == '__main__':
    rospy.init_node('scan_listener', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, callback)
    rospy.spin()
