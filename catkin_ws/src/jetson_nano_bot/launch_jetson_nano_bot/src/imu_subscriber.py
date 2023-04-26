#!/usr/bin/env python

import rospy

from std_msgs.msg import String
from sensor_msgs.msg import Imu
from std_msgs.msg import Header



def callback(data):
    AX = (float(data.data[data.data.index("A")+1:data.data.index("B")]))
    AY = (float(data.data[data.data.index("B")+1:data.data.index("C")]))
    AZ = (float(data.data[data.data.index("C")+1:data.data.index("D")]))
    GX = (float(data.data[data.data.index("D")+1:data.data.index("E")]))
    GY = (float(data.data[data.data.index("E")+1:data.data.index("F")]))
    GZ = (float(data.data[data.data.index("F")+1:data.data.index("G")]))

    msg = Imu()
    header = Header()
    header.frame_id = "imu"
    msg.header = header
    msg.header.stamp = rospy.Time.now()
    msg.orientation_covariance[0] = -1
    msg.orientation_covariance[4] = .01
    msg.orientation_covariance[8] = .01
    msg.linear_acceleration_covariance[0] = 0.01
    msg.linear_acceleration_covariance[4] = 0.01
    msg.linear_acceleration_covariance[8] = 0.01
    msg.angular_velocity_covariance[0] = .05
    msg.angular_velocity_covariance[4] = .05
    msg.angular_velocity_covariance[8] = .05

    msg.orientation.x = 0
    msg.orientation.y = 0
    msg.orientation.z = 0
    msg.orientation.w = 1
    msg.angular_velocity.x = GX
    msg.angular_velocity.y = GY
    msg.angular_velocity.z = GZ
    msg.linear_acceleration.x = AX
    msg.linear_acceleration.y = AY
    msg.linear_acceleration.z = AZ

    imupub.publish(msg)


if __name__ == '__main__':
    rospy.init_node('imu', anonymous=True)

    rospy.Subscriber('/imu', String, callback)

    imupub = rospy.Publisher('imu/data', Imu, queue_size=10)

    rospy.spin()
