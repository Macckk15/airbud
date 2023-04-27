
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <Servo.h>

//Initialize Servo Variables
Servo myServo;
unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 0;
int stopAngle = 0;

Adafruit_MPU6050 mpu;

std_msgs::String imu_msg;
std_msgs::String camAngle_msg;
ros::Publisher imu("imu", &imu_msg);
 
// Handles startup and shutdown of ROS
ros::NodeHandle nh;
 
////////////////// Tick Data Publishing Variables and Constants ///////////////
 
// Encoder output to Arduino Interrupt pin. Tracks the tick count.
#define ENC_IN_LEFT_A 3
#define ENC_IN_RIGHT_A 2
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_LEFT_B 5
#define ENC_IN_RIGHT_B 4
 
// True = Forward; False = Reverse
boolean Direction_left = true;
boolean Direction_right = true;
 
// Minumum and maximum values for 16-bit integers
// Range of 65,535
const int encoder_minimum = -32768;
const int encoder_maximum = 32767;
 
// Keep track of the number of wheel ticks
std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);
 
std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);
 
// Time interval for measurements in milliseconds
const int interval = 30;
long previousMillis = 0;
long currentMillis = 0;


////////////////// Motor Controller Variables and Constants ///////////////////
 
// Motor A connections
const int enA = 9;
const int in1 = 10;
const int in2 = 8;
  
// Motor B connections
const int enB = 13; 
const int in3 = 11;
const int in4 = 12;
 
// How much the PWM value can change each cycle
const int PWM_INCREMENT = 14;
 
// Number of ticks per wheel revolution. We won't use this in this code.
const int TICKS_PER_REVOLUTION = 142;
 
// Wheel radius in meters
const double WHEEL_RADIUS = 0.033;
 
// Distance from center of the left tire to the center of the right tire in m
const double WHEEL_BASE = 0.17;
 
// Number of ticks a wheel makes moving a linear distance of 1 meter
// This value was measured manually.
const double TICKS_PER_METER = 686; // Originally 2880
 
// Proportional constant, which was measured by measuring the 
// PWM-Linear Velocity relationship for the robot.
const int K_P = 278;
 
// Y-intercept for the PWM-Linear Velocity relationship for the robot
const int b = 52;
 
// Correction multiplier for drift. Chosen through experimentation.
const int DRIFT_MULTIPLIER = 200;
 
// Turning PWM output (0 = min, 255 = max for PWM values)
const int PWM_TURN = 125; 
 
// Set maximum and minimum limits for the PWM values
const int PWM_MIN = 125; // about 0.3 m/s
const int PWM_MAX = 225; // about 0.172 m/s
 
// Set linear velocity and PWM variable values for each wheel
double velLeftWheel = 0;
double velRightWheel = 0;
double pwmLeftReq = 0;
double pwmRightReq = 0;
 
// Record the time that the last velocity command was received
double lastCmdVelReceived = 0;
 
float Temp;
float previousTime, currentTime, elapsedTime;
float XAccel, YAccel, ZAccel, XGyro, YGyro, ZGyro, gyroAngleX, gyroAngleY, gyroAngleZ;
float GyroErrorZ;
float targetGyro, fadeValueL, fadeValueR; 
bool isdriving = false;
bool isturning = false;
float angleMin = -360; 
float angleMax = 360;
int fadeValue = 255;
int LeftTickCount = 0; 
int RightTickCount = 0; 
int CurrentTicks = 0;
unsigned long startTime = 0; 
unsigned long startTime2 = 0;
bool forward, backward, ismoving;
int pos;
int c;
double currVelX = 0;
double currAngZ = 0;

/////////////////////// Servo Functions ////////////////////////////////////////

void pandown(){
  if (pos >= 100)
  {
    for(pos = 180; pos >= 90; pos-=1){
      myServo.write(pos);
      delay(56);
    }
  }
}

void panup(){
  if (pos <= 180)
  {
    for(pos = 90; pos <= 190; pos+=1){
      myServo.write(pos);
      delay(56);
    }
  }
}

/////////////////////// Tick Data Publishing Functions ////////////////////////
 
// Increment the number of ticks
void right_wheel_tick() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if (val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
     
    if (right_wheel_tick_count.data == encoder_maximum) {
      right_wheel_tick_count.data = encoder_minimum;
    }
    else {
      RightTickCount--;
      right_wheel_tick_count.data--;  
    }    
  }
  else {
    if (right_wheel_tick_count.data == encoder_minimum) {
      right_wheel_tick_count.data = encoder_maximum;
    }
    else {
      RightTickCount++;
      right_wheel_tick_count.data++;  
    }   
  }
}
 
// Increment the number of ticks
void left_wheel_tick() {
   
  // Read the value for the encoder for the left wheel
  int val = digitalRead(ENC_IN_LEFT_B);
 
  if (val == LOW) {
    Direction_left = true; // Reverse
  }
  else {
    Direction_left = false; // Forward
  }
   
  if (Direction_left) {
    if (left_wheel_tick_count.data == encoder_maximum) {
      left_wheel_tick_count.data = encoder_minimum;
    }
    else {
      LeftTickCount--;
      left_wheel_tick_count.data--;  
    }  
  }
  else {
    if (left_wheel_tick_count.data == encoder_minimum) {
      left_wheel_tick_count.data = encoder_maximum;
    }
    else {
      LeftTickCount++;
      left_wheel_tick_count.data++;  
    }   
  }
}
 
/////////////////////// Motor Controller Functions ////////////////////////////
 
// Calculate the left wheel linear velocity in m/s every time a 
// tick count message is rpublished on the /left_ticks topic. 
void calc_vel_left_wheel(){
   
  // Previous timestamp
  static double prevTime = 0;
   
  // Variable gets created and initialized the first time a function is called.
  static int prevLeftCount = 0;
 
  // Manage rollover and rollunder when we get outside the 16-bit integer range 
  int numOfTicks = (65535 + left_wheel_tick_count.data - prevLeftCount) % 65535;
 
  // If we have had a big jump, it means the tick count has rolled over.
  if (numOfTicks > 10000) {
        numOfTicks = 0 - (65535 - numOfTicks);
  }
 
  // Calculate wheel velocity in meters per second
  velLeftWheel = numOfTicks/TICKS_PER_METER/((millis()/1000)-prevTime);
  if (currVelX != 0 && currAngZ == 0){
    if (prevLeftCount + 3 < left_wheel_tick_count.data)
    {
      Serial.println("Left Wheel is moving");
      ismoving = true;
    } else {
      Serial.println("Left Wheel is not moving");
      ismoving = false;
    }
  }
  /*
  else if (currAngZ != 0 && currVelX == 0){
      if (velLeftWheel > 0)
      {
        Serial.println("Left Wheel is moving");
        ismoving = true;
      } else {
        Serial.println("Left Wheel is not moving");
        ismoving = false;
      }
  }
*/
    
 
  // Keep track of the previous tick count
  prevLeftCount = left_wheel_tick_count.data;
 
  // Update the timestamp
  prevTime = (millis()/1000);
 
}
 
// Calculate the right wheel linear velocity in m/s every time a 
// tick count message is published on the /right_ticks topic. 
void calc_vel_right_wheel(){
   
  // Previous timestamp
  static double prevTime = 0;
   
  // Variable gets created and initialized the first time a function is called.
  static int prevRightCount = 0;
 
  // Manage rollover and rollunder when we get outside the 16-bit integer range 
  int numOfTicks = (65535 + right_wheel_tick_count.data - prevRightCount) % 65535;
 
  if (numOfTicks > 10000) {
        numOfTicks = 0 - (65535 - numOfTicks);
  }
 
  // Calculate wheel velocity in meters per second
  velRightWheel = numOfTicks/TICKS_PER_METER/((millis()/1000)-prevTime);
  if (currVelX != 0 && ismoving == false && currAngZ == 0){
    if (prevRightCount + 3 < right_wheel_tick_count.data && ismoving == false)
    {
      Serial.println("Left Wheel is moving");
      ismoving = true;
    } else {
      Serial.println("Left Wheel is not moving");
      ismoving = false;
    }
} 

/*
else if (currAngZ != 0 && ismoving == false && currVelX == 0){
      if (velRightWheel > 0)
      {
        Serial.println("Left Wheel is moving");
        ismoving = true;
      } else {
        Serial.println("Left Wheel is not moving");
        ismoving = false;
      }
  }

*/

 
  prevRightCount = right_wheel_tick_count.data;
   
  prevTime = (millis()/1000);
 
}
 
// Take the velocity command as input and calculate the PWM values.
void calc_pwm_values(const geometry_msgs::Twist& cmdVel) {
   
  // Record timestamp of last velocity command received
  lastCmdVelReceived = (millis()/1000);
  currVelX = cmdVel.linear.x;
  currAngZ = cmdVel.angular.z;
   
  // Calculate the PWM value given the desired velocity 
  pwmLeftReq = K_P * cmdVel.linear.x + b;
  pwmRightReq = K_P * cmdVel.linear.x + b;
 
  // Check if we need to turn 
  if (cmdVel.angular.z != 0.0) {
 
    // Turn left
    if (cmdVel.angular.z > 0.0) {
      pwmLeftReq = PWM_TURN;
      pwmRightReq = -PWM_TURN;
    }
    // Turn right    
    else {
      pwmLeftReq = -PWM_TURN;
      pwmRightReq = PWM_TURN;
    }
  }
  // Go straight
  else {
     
    // Remove any differences in wheel velocities 
    // to make sure the robot goes straight
    static double prevDiff = 0;
    static double prevPrevDiff = 0;
    double currDifference = velLeftWheel - velRightWheel; 
    double avgDifference = (prevDiff+prevPrevDiff+currDifference)/3;
    prevPrevDiff = prevDiff;
    prevDiff = currDifference;
 
    // Correct PWM values of both wheels to make the vehicle go straight
    pwmLeftReq -= (int)(avgDifference * DRIFT_MULTIPLIER);
    pwmRightReq += (int)(avgDifference * DRIFT_MULTIPLIER);
  }

  // Handle low PWM values
  if (abs(pwmLeftReq) < PWM_MIN) {
    pwmLeftReq = 0;
  }
  if (abs(pwmRightReq) < PWM_MIN) {
    pwmRightReq = 0;  
  }  
}
ros::Subscriber<std_msgs::String> subChatter("chatter", &receive_imu_data );
ros::Subscriber<std_msgs::String> subCamCommand("camCommand_msg", &receive_cam_command);
ros::Subscriber<std_msgs::String> subPose("poseString", &receive_odom_data );
ros::Subscriber<std_msgs::String> subGoal("goalString", &receive_goal_data);

void readAcceleration(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    XAccel = a.acceleration.x + -0.80;
    YAccel = a.acceleration.y + 0.31;
    ZAccel = a.acceleration.z + 1.72;
    XGyro = g.gyro.x + 0.07;
    YGyro = g.gyro.y + 0.04;
    ZGyro = g.gyro.z + 0.00;
    Temp = temp.temperature;
}

void calcError(){
  c = 0;
  while (c < 200){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    ZGyro = g.gyro.z + 0.01;
    GyroErrorZ += ZGyro;
    c++;
  }
  GyroErrorZ = GyroErrorZ / 200;
}

String Roll;
double currentPositionx, currentPositiony, currentPositionz, currentOrientationx, currentOrientationy, currentOrientationz, currentOrientationw; 
double desiredPosition;
void receive_imu_data(const std_msgs::String& chatter){
    Roll = chatter.data;
  }

String Cam;
void receive_cam_command(const std_msgs::String& camCommand_msg){
    Cam = camCommand_msg.data;
  }
double XPose, YPose, ZPose, XOrien, YOrien, ZOrien, WOrien, CurrYaw;
String Pose, XPosestr, YPosestr, ZPosestr, XPoseOrienstr, YPoseOrienstr, ZPoseOrienstr, WPoseOrienstr;
int XPoseIndex, YPoseIndex, ZPoseIndex, XOrienIndex, YOrienIndex, ZOrienIndex, WOrienIndex, EndPoseIndex;
void receive_odom_data(const std_msgs::String& current_odom_msg){
    Pose = current_odom_msg.data;
    XPoseIndex = Pose.indexOf("A");
    YPoseIndex = Pose.indexOf("B");
    ZPoseIndex = Pose.indexOf("C");
    XOrienIndex = Pose.indexOf("D");
    YOrienIndex = Pose.indexOf("E");
    ZOrienIndex = Pose.indexOf("F");
    WOrienIndex = Pose.indexOf("G");
    EndPoseIndex = Pose.indexOf("H");
    XPosestr = Pose.substring(XPoseIndex+1, YPoseIndex);
    YPosestr = Pose.substring(YPoseIndex+1, ZPoseIndex);
    ZPosestr = Pose.substring(ZPoseIndex+1, XOrienIndex);
    XPoseOrienstr = Pose.substring(XOrienIndex+1, YOrienIndex);
    YPoseOrienstr = Pose.substring(YOrienIndex+1, ZOrienIndex);
    ZPoseOrienstr = Pose.substring(ZOrienIndex+1, WOrienIndex);
    WPoseOrienstr = Pose.substring(WOrienIndex+1, EndPoseIndex);
    XPose = XPosestr.toDouble();
    YPose = YPosestr.toDouble();
    ZPose = ZPosestr.toDouble();
    XOrien = XPoseOrienstr.toDouble();
    YOrien = YPoseOrienstr.toDouble();
    ZOrien = ZPoseOrienstr.toDouble();
    WOrien = XPoseOrienstr.toDouble();
    CurrYaw = atan2(2 * (XOrien * WOrien + YOrien * ZOrien), 1 - (2 * (ZOrien * ZOrien + WOrien * WOrien)));
  }
String Goal, XGoalstr, YGoalstr, ZGoalstr, XGoalOrienstr, YGoalOrienstr, ZGoalOrienstr, WGoalOrienstr;
double XGoal, YGoal, ZGoal, XGoalOrien, YGoalOrien, ZGoalOrien, WGoalOrien, GoalYaw, Sine, Cosine;
int XGoalIndex, YGoalIndex, ZGoalIndex, XGoalOrienIndex, YGoalOrienIndex, ZGoalOrienIndex, WGoalOrienIndex, EndGoalIndex;
void receive_goal_data(const std_msgs::String& move_base_goal_msg){
    Goal = move_base_goal_msg.data;
    XGoalIndex = Goal.indexOf("A");
    YGoalIndex = Goal.indexOf("B");
    ZGoalIndex = Goal.indexOf("C");
    XGoalOrienIndex = Goal.indexOf("D");
    YGoalOrienIndex = Goal.indexOf("E");
    ZGoalOrienIndex = Goal.indexOf("F");
    WGoalOrienIndex = Goal.indexOf("G");
    EndGoalIndex = Goal.indexOf("H");
    XGoalstr = Goal.substring(XGoalIndex+1, YGoalIndex);
    YGoalstr = Goal.substring(YGoalIndex+1, ZGoalIndex);
    ZGoalstr = Goal.substring(ZGoalIndex+1, XGoalOrienIndex);
    XGoalOrienstr = Goal.substring(XGoalOrienIndex+1, YGoalOrienIndex);
    YGoalOrienstr = Goal.substring(YGoalOrienIndex+1, ZGoalOrienIndex);
    ZGoalOrienstr = Goal.substring(ZGoalOrienIndex+1, WGoalOrienIndex);
    WGoalOrienstr = Goal.substring(WGoalOrienIndex+1, EndGoalIndex);
    XGoal = XGoalstr.toDouble();
    YGoal = YGoalstr.toDouble();
    ZGoal = ZGoalstr.toDouble();
    XGoalOrien = XGoalOrienstr.toDouble();
    YGoalOrien = YGoalOrienstr.toDouble();
    ZGoalOrien = ZGoalOrienstr.toDouble();
    WGoalOrien = XGoalOrienstr.toDouble();
    GoalYaw = atan2(2 * (XGoalOrien * WGoalOrien + YGoalOrien * ZGoalOrien), 1 - (2 *(ZGoalOrien * ZGoalOrien + WGoalOrien * WGoalOrien)));
  }

float XDistance, YDistance, ZOrientation, WOrientation, Distance, Yaw, Ticks;
void set_pwm_values() {
 
  // These variables will hold our desired PWM values
  static int pwmLeftOut = 0;
  static int pwmRightOut = 0;
 
  // If the required PWM is of opposite sign as the output PWM, we want to
  // stop the car before switching direction
  static bool stopped = false;
  if ((pwmLeftReq * velLeftWheel < 0 && pwmLeftOut != 0) ||
      (pwmRightReq * velRightWheel < 0 && pwmRightOut != 0)) {
    pwmLeftReq = 0;
    pwmRightReq = 0;
  }
 
  // Set the direction of the motors
  if (currVelX > 0 || currAngZ > 0) { // Left wheel forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if (currVelX < 0 || currAngZ < 0) { // Left wheel reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else if (currVelX == 0 && currAngZ == 0) { // Left wheel stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  else { // Left wheel stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  }
 
  if (currVelX > 0 || currAngZ < 0) { // Right wheel forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(currVelX < 0) { // Right wheel reverse
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (currVelX == 0 && currAngZ == 0) { // Right wheel stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else { // Right wheel stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
  }
 
  // Increase the required PWM if the robot is not moving
  if (pwmLeftReq != 0 && ismoving == false) {
    Serial.print("Not Moving");
    pwmLeftReq *= 1.5;
  }
  if (pwmRightReq != 0 && ismoving == false) {
    pwmRightReq *= 1.5;
  }
 
  // Calculate the output PWM value by making slow changes to the current value
  if (abs(pwmLeftReq) > pwmLeftOut && currVelX != 0) {
    pwmLeftOut += PWM_INCREMENT;
  }
  else if (abs(pwmLeftReq) < pwmLeftOut && currVelX != 0) {
    pwmLeftOut -= PWM_INCREMENT;
  }
  else{}
   
  if (abs(pwmRightReq) > pwmRightOut && currVelX != 0) {
    pwmRightOut += PWM_INCREMENT;
  }
  else if(abs(pwmRightReq) < pwmRightOut && currVelX != 0) {
    pwmRightOut -= PWM_INCREMENT;
  }
  else{}
 
  // Conditional operator to limit PWM output at the maximum 
  pwmLeftOut = (pwmLeftOut > PWM_MAX) ? PWM_MAX : pwmLeftOut;
  pwmRightOut = (pwmRightOut > PWM_MAX) ? PWM_MAX : pwmRightOut;
 
  // PWM output cannot be less than 0
  pwmLeftOut = (pwmLeftOut < 0) ? 0 : pwmLeftOut;
  pwmRightOut = (pwmRightOut < 0) ? 0 : pwmRightOut;

  //Set the distance needed to travel (sent by path planner)
  
  CurrentTicks = (LeftTickCount + RightTickCount) / 2;
  /*
  XDistance = (XGoal - XPose);
  YDistance = (YGoal - YPose);
  Distance = (sqrt(pow(XDistance, 2) + pow(YDistance, 2))) * TICKS_PER_METER;
  */
  XDistance = XGoal;
  Distance = XDistance * TICKS_PER_METER;  
  Ticks = Distance - CurrentTicks;

  Serial.println("Current Ticks Left is: ");
  Serial.println(Ticks);
  Serial.println("");

  /*
  Yaw = GoalYaw - CurrYaw;
  */
  
 
  // Set the PWM value on the pins
  unsigned long currentMillis = millis();

  if (currVelX != 0 /*&& (Ticks > 5)*/){
    panup();
    analogWrite(enA, pwmLeftOut);
    analogWrite(enB, pwmRightOut);
  } else if (currAngZ != 0 /*&& (Yaw > 0.1)*/){
    if (currentMillis - startTime >= 450) {
      startTime = currentMillis; 
      if (ismoving == false){
          pandown();
          LeftTickCount = 0; 
          RightTickCount = 0;
          analogWrite(enA, 235); 
          analogWrite(enB, 0);
        ismoving = true;
      } else {
        LeftTickCount = 0; 
        RightTickCount = 0;
        analogWrite(enA, 0); 
        analogWrite(enB, 0);
        ismoving = false;
      }
    }
  } else {
    LeftTickCount = 0; 
    RightTickCount = 0;
    analogWrite(enA, 0); 
    analogWrite(enB, 0);
  }
  Serial.print("PWM LEFT = ");
  Serial.println(pwmLeftOut); 
  Serial.println("");
  Serial.print("PWM RIGHT = ");
  Serial.println(pwmRightOut);
  Serial.println("");
}
 
// Set up ROS subscriber to the velocity command
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &calc_pwm_values );
 
void setup() {
  nh.initNode();
  nh.advertise(imu);
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println(""); 

  // Set pin states of the encoder
  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
 
  // Every time the pin goes high, this is a tick
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_tick, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_tick, RISING);
   
  // Motor control pins are outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  // Set the motor speed
  analogWrite(enA, 0); 
  analogWrite(enB, 0);
 
  // ROS Setup
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  nh.subscribe(subCmdVel);
  nh.subscribe(subCamCommand);
  nh.subscribe(subPose);
  nh.subscribe(subGoal);
  calcError();

  myServo.attach(7);
}

long publisher_timer;

void loop() {
  
  /*
  Serial.print("Current Pose ");
  Serial.print(Pose);
  Serial.println("");
  Serial.print("Current Goal ");
  Serial.print(Goal);
  Serial.println("");
  Serial.println(XGoal);
  Serial.println(YGoal);
  Serial.println(ZGoal);
 
  moveStartTime = millis();
  if (Cam == "Up"){
      panup();
  } else if (Cam == "Down") {
    pandown();
  }
 Serial.print(Cam);
 */
  nh.spinOnce();
  readAcceleration();
  previousTime = currentTime;
  /*
  Serial.print("Previous Time = ");
  Serial.print(previousTime);
  Serial.println("");
  */

  currentTime = millis()/1000;
  /*
  Serial.print("Current Time = ");
  Serial.print(currentTime);
  Serial.println("");
  */
  elapsedTime = (currentTime - previousTime);
  /*
  Serial.print("Elapsed Time = ");
  Serial.print(elapsedTime);
  Serial.println("");
  */

  //ZGyro -= GyroErrorZ;
  gyroAngleZ += (ZGyro * (180/PI)) * elapsedTime;
  if (gyroAngleZ > angleMax)
  {
    gyroAngleZ = 0;
  }
  else if(gyroAngleZ < angleMin)
  {
    gyroAngleZ = 0;
  }
  
  String AX =String(XAccel);
  String AY = String(YAccel);
  String AZ = String(ZAccel);
  String GX = String(XGyro);
  String GY = String(YGyro);
  String GZ = String(ZGyro);
  String Tmp = String(Temp);

  String data = "A" + AX + "B" + AY + "C" + AZ + "D" + GX + "E" + GY + "F" + GZ + "G" ;
  // Serial.println(data);
  int length = data.indexOf("G") + 2;
  char data_final[length+1];
  data.toCharArray(data_final, length+1);
  currentMillis = millis();
    imu_msg.data = data_final;
    imu.publish(&imu_msg);
    publisher_timer = currentMillis + 100;  

  // Record the time
  currentMillis = millis();
 
  // If the time interval has passed, publish the number of ticks,
  // and calculate the velocities.
  if (currentMillis - previousMillis > interval) {
     
    previousMillis = currentMillis;
 
    // Publish tick counts to topics
    leftPub.publish( &left_wheel_tick_count );
    rightPub.publish( &right_wheel_tick_count );
 
    // Calculate the velocity of the right and left wheels
    calc_vel_right_wheel();
    calc_vel_left_wheel();
    
     
  }
    if((millis()/1000) - lastCmdVelReceived > 1) {
    pwmLeftReq = 0;
    pwmRightReq = 0;
    analogWrite(enA, 0); 
    analogWrite(enB, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    currAngZ == 0;
    currVelX == 0;
    CurrentTicks = 0;
    LeftTickCount = 0; 
    RightTickCount = 0;
  }
   
  // Stop the car if there are no cmd_vel messages
  
  set_pwm_values();


}
