# airbud
This github is a project done by Team 61 for the IEEE Region 5 Robot Competition. The project consists of a ground robot and a drone collaborating to maneuver around an obstacle course.
The ground robot needed to be able to read the red reflective tape on the entrance of a box and determine the distance to that respective box to move inside of it
Next, it needed to scan the QR code on the ceiling of the box to determine the next box to drive inside of.
The locations of these boxes are determined by the drone scanning the QR codes on the tops of the boxes and sending the location back to the ground robot

This project was created in order to be run autonomously with the press of a button on the ground robot and drone.

The drone used was the DJI Tello Drone with 720p video feed and 5 MP image quality.

The microcontroller used was the NVIDIA Jetson Nano 4GB.

In order to run the code automatically, the following steps need to be taken.

1. Make sure the ground robot automatically connects to the drone on startup.
2. Make sure that the correct ports have the correct permissions off of boot (ex: dev/ttyACM0 has the permissions 777 for arduino to operate)
3. Create a ROS program to run a certain ros launch file off of startup. (Use this link for setting it up https://roboticsbackend.com/make-ros-launch-start-on-boot-with-robot_upstart/)
4. Set the launch file that is to be run off of startup to be the jetson_nano_bot in the navstack_pub ros package
5. Restart and the file should be able to run.

To run the code manualy, enter in this command into the terminal:
roslaunch navstack_pub jetson_nano_bot

The main launch file has a lot of parts in it, but I will break it down by sections those being:
1. The transform publishers
2. The rosserial_python node (Original Creator: Automatic Addison)
3. ekf_data_pub node (Original Creator: Automatic Addison)
4. The robot_pose_ekf Node (Author: Wim Meeussen)
5. rviz_click_to_2d (Original Creator: Automatic Addison)
6. The RP Lidar Node
7. The python files
8. The Map loading files
9. The AMCL Node (Author: Brian P. Gerkey, contradict@gmail.com)
10. Move base node


The transform publishers consists of: 
- a robot description that loads the urdf file of the ground robot.
- The joint state publisher that publishes the joints of the urdf file
- The robot state publisher which publishes the current positions of all of the components of the robot. It most notably transforms the wheels to the base_link
- and the static publishers which transform the base_link to the laser, and imu. They also transform the base footprint to the base link. 
- Use this link for help with transforms http://wiki.ros.org/tf

The rosserial python node consists of:
- The port and baud that is needed to connect to the arduino board (adjust port and baud rate if necessary)


The ekf_data_pub node consists of:
- The subscriber that subscribes to the left and right tick data
- The subscriber that subscribes to the initial_2d position
- Publishes the current odometry in euler form and quat form


The robot_pose_ekf Node consists of:
- The subscriber that subscribes to the current odometry, imu_data, and visual odometry (if used)
- Publishes the updated and more accurate odometry of the ground robot
- To read more on this Node, check here for the author and the parameters for it http://wiki.ros.org/robot_pose_ekf


The rviz_click_to_2d node consists of:
- The publisher that publishes the initial position of the robot if the set location is clicked on RVIZ manually (only used for testing)
- The publisher that publishes the goal position of the robot if clicked on RVIZ (also used only for testing)


The RP LiDAR Node consists of:
- The port and baud rate for your respective LiDAR. The one that was used in this project is the RP LIDAR A1M8
- For help with params, use this website http://wiki.ros.org/rplidar


The main python files consist of:
- The file that subscribes to the current odometry message and publishes the odometry as a string to be parsed by the arduino file
- The file that subscribes to the current goal message and publishes the goal as a string to be parsed by the arduino file
- The file that parses the imu data sent by the arduino and publishes it as an Imu message type (Original creator: Ahmad Said, https://atadiat.com/en/e-ros-imu-and-arduino-how-to-send-to-ros/)
- The file that uses the LiDAR scans to calculate the distance from it's current position to the box in front of it and publishes that message
- The file that uses the camera to detect the entrance of the box and send that message as a string
- The file that that sets the original position of the ground robot as a string
- The file that uses the distance calculated by the LiDAR after the entrace message is sent to send a goal message for the ground robot to move to
- The file that launches the drone in the air before the other commands are sent

The map loading files consist of:
- The Node that loads the map file to the ground robot
- The map server node that launches the map

The AMCL Node consists of:
- The node that uses the LiDAR scans in order to localize the ground robot in the map and publish the transform from the odometry to the map frame
- for help with parameters, look here: (http://wiki.ros.org/amcl)

The move base node consists of:
- The node that handles the sending of the planning, obstacle avoidance, and the movement to the ground robot
- For help with parameters, look here: (http://wiki.ros.org/move_base)
- You can change these to use any local planner and global planner you would like to use

