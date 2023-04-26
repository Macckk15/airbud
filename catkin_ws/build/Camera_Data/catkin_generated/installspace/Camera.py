#!/usr/bin/env python2
import fileinput

# license removed for brevity
import rospy
from sensor_msgs.msg import MagneticField


def talker():
    counter = 0
    XMag = 0
    pub = rospy.Publisher('imu/mag', MagneticField, queue_size=40)
    msg = MagneticField()
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(25) # 10hz
    while not rospy.is_shutdown():
        for line in fileinput.input():
            hello_str = line.rstrip()
            if (counter > 3):
                XMagPos = hello_str.find("I")
                YMagPos = hello_str.find("J")
                ZMagPos = hello_str.find("K")
                EndPos = hello_str.find("Z")
                XMag = float(hello_str[XMagPos+2:YMagPos])
                YMag = float(hello_str[YMagPos+2:ZMagPos])
                ZMag = float(hello_str[ZMagPos+2:EndPos])
                msg.header.stamp = rospy.get_rostime()
                msg.magnetic_field.x = XMag
                msg.magnetic_field.y = YMag
                msg.magnetic_field.z = ZMag
                pub.publish(msg)
                rate.sleep()
            counter = counter + 1

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass