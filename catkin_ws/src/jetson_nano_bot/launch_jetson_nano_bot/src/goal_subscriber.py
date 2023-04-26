#!/usr/bin/env python

import rospy

from std_msgs.msg import String
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
from nav_msgs.msg import Path


def callback(data):
    for pose_stamped in data.poses:
        PX = str(pose_stamped.pose.position.x)
        PY = str(pose_stamped.pose.position.y)
        PZ = str(pose_stamped.pose.position.z)
        OX = str(pose_stamped.pose.orientation.x)
        OY = str(pose_stamped.pose.orientation.y)
        OZ = str(pose_stamped.pose.orientation.z)
        OW = str(pose_stamped.pose.orientation.w)

    msg = "A" + PX + "B" + PY + "C" + PZ + "D" + OX + "E" + OY + "F" + OZ + "G" + OW + "H"
    imupub.publish(msg)


if __name__ == '__main__':
    rospy.init_node('goal_listener', anonymous=True)

    rospy.Subscriber('/move_base/DWAPlannerROS/local_plan', Path, callback)

    imupub = rospy.Publisher('goalString', String, queue_size=10)

    rospy.spin()