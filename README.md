# airbud
This github is a project done by Team 61 for the IEEE Region 5 Robot Competition. The project consists of a ground robot and a drone collaborating to maneuver around an obstacle course.

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
4. The robot_pose_ekf Node
5. rviz_click_to_2d (Original Creator: Automatic Addison)
6. The RP Lidar Node
7. The python files
8. The Map loading files
9. Move base node


The transform publisher consists of: 
- a robot description that loads the urdf file of the ground robot.
- The joint state publisher that publishes the joints of the urdf file
- The robot state publisher which publishes the current positions of all of the components of the robot. It most notably transforms the wheels to the base_link
- and the static publishers which transform the base_link to the laser, and imu. They also transform the base footprint to the base link. 


The rosserial python node consists of:
- The port and baud that is needed to connect to the arduino board (adjust port and baud rate if necessary)

The ekf_data_pub node consists of:
- The subscriber that subscribes to the left and right tick data
- The subscriber that subscribes to the initial_2d position
- Publishes the current odometry in euler form and quat form

