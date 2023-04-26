#!/usr/bin/env python


import rospy
import math
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String


scanpub = rospy.Publisher('scan_listener', String, queue_size=10)
angle_sum = 0.0
count = 0
total_distance = 0


def callback(data):     
    # Define the indices of the relevant angle range
    # Get real values during practice round of competition
    min_index1 = 510
    max_index1 = 530
    min_index2 = 610
    max_index2 = 640
    global angle_sum, count, total_distance
    

    # Extract the relevant ranges from the LaserScan message
    ranges = data.ranges

    # Print the ranges within the relevant angle range
    for i in range(min_index1, max_index1+1):
        if not math.isinf(ranges[i]):
            if 1.09 < ranges[i] < 1.63:
                total_distance += ranges[i]
                angle_sum += data.angle_min + i*data.angle_increment
                count += 1
                Avg = total_distance / count
                msg = str(Avg)
                scanpub.publish(msg)               
                if (count > 150):
                    total_distance = Avg
                    count = 1

    for j in range(min_index2, max_index2+1):
        if not math.isinf(ranges[j]):
            if 1.09 < ranges[j] < 1.63:
                total_distance += ranges[j]
                angle_sum += data.angle_min + j*data.angle_increment
                count += 1
                Avg = total_distance / count
                msg = str(Avg)
                scanpub.publish(msg)               
                if (count > 150):
                    total_distance = Avg
                    count = 1


if __name__ == '__main__':
    rospy.init_node('scan_listener', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, callback)
    rospy.spin()

