#!/usr/bin/env python

import rospy

from std_msgs.msg import String
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import Pose


def callback(data):
    currpose = data.pose.pose
    PX = str(currpose.position.x)
    PY = str(currpose.position.y)
    PZ = str(currpose.position.z)
    OX = str(currpose.orientation.x)
    OY = str(currpose.orientation.y)
    OZ = str(currpose.orientation.z)
    OW = str(currpose.orientation.w)

    msg = "A" + PX + "B" + PY + "C" + PZ + "D" + OX + "E" + OY + "F" + OZ + "G" + OW + "H"
    imupub.publish(msg)


if __name__ == '__main__':
    rospy.init_node('pose_listener', anonymous=True)

    rospy.Subscriber('/robot_pose_ekf/odom_combined', PoseWithCovarianceStamped, callback)

    imupub = rospy.Publisher('poseString', String, queue_size=10)

    rospy.spin()