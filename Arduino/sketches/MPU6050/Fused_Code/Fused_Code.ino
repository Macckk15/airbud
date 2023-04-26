#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>

//Initialize Servo Commands
Servo myServo;
unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 0;
int stopAngle = 0;



/*            ax    ay    az    gx    gy    gz
 * offsets: -0.76  0.02  1.89  0.08  0.04  0.01
 */


Adafruit_MPU6050 mpu;

std_msgs::String imu_msg;
std_msgs::String camAngle_msg;
ros::Publisher imu("imu", &imu_msg);
ros::Publisher camAngle("CamAngle", &camAngle_msg);
ros::NodeHandle nh;

////////////////// Tick Data Publishing Variables and Constants ///////////////
 
// Encoder output to Arduino Interrupt pin. Tracks the tick count.
#define ENC_IN_LEFT_A 2
#define ENC_IN_RIGHT_A 3
#define SDA = 20
#define SCL = 21
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_LEFT_B 4
#define ENC_IN_RIGHT_B 5    
 
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
const int PWM_INCREMENT = 1;
 
// Number of ticks per wheel revolution. We won't use this in this code.
const int TICKS_PER_REVOLUTION = 142;
 
// Wheel radius in meters
const double WHEEL_RADIUS = 0.033;
 
// Distance from center of the left tire to the center of the right tire in m
const double WHEEL_BASE = 0.17;
 
// Number of ticks a wheel makes moving a linear distance of 1 meter
// This value was measured manually.
const double TICKS_PER_METER = 686; // Originally 3100
 
// Proportional constant, which was measured by measuring the 
// PWM-Linear Velocity relationship for the robot.
const int K_P = 278;
 
// Y-intercept for the PWM-Linear Velocity relationship for the robot
const int b = 52;
 
// Correction multiplier for drift. Chosen through experimentation.
const int DRIFT_MULTIPLIER = 75;
 
// Turning PWM output (0 = min, 255 = max for PWM values)
const int PWM_TURN = 80;
 
// Set maximum and minimum limits for the PWM values
const int PWM_MIN = 80; // about 0.1 m/s
const int PWM_MAX = 200; // about 0.172 m/s
 
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
bool forward, backward;
int c;

/////////////////////// Servo Functions ////////////////////////////////////////

void pandown(){
  startAngle = 180;
  stopAngle = 90;
  unsigned long progress = millis() - moveStartTime;
  if (progress <= MOVING_TIME) {
  long angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
  myServo.write(angle);
  }
}

void panup(){
  startAngle = 90;
  stopAngle = 180;
  unsigned long progress = millis() - moveStartTime;
  if (progress <= MOVING_TIME) {
  long angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
  myServo.write(angle);
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
      RightTickCount++;
      right_wheel_tick_count.data++;  
    }    
  }
  else {
    if (right_wheel_tick_count.data == encoder_minimum) {
      right_wheel_tick_count.data = encoder_maximum;
    }
    else {
      RightTickCount--;
      right_wheel_tick_count.data--;  
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
      LeftTickCount++;
      left_wheel_tick_count.data++;   
    }  
  }
  else {
    if (left_wheel_tick_count.data == encoder_minimum) {
      left_wheel_tick_count.data = encoder_maximum;
    }
    else {
      LeftTickCount--;
      left_wheel_tick_count.data--;   
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
 
  prevRightCount = right_wheel_tick_count.data;
   
  prevTime = (millis()/1000);
 
}
int time_since_cmd;
double velocity, angvelocity;
double prev_velocity;
double last_cmd_recv;
double last_last_cmd_recv;
int FadeStopForward, Fade, FadeStopTurning;
// Take the velocity command as input and set the PWM values.
void calc_pwm_values(const geometry_msgs::Twist& cmdVel) {
    if (cmdVel.linear.x != 0)
    {
      last_cmd_recv = (millis()/1000); 
      FadeStopForward = 155;
      velocity = cmdVel.linear.x;
    }
    if (cmdVel.angular.z != 0)
    {
      last_cmd_recv = (millis()/1000);
      FadeStopTurning = 155;
      angvelocity = cmdVel.angular.z;
    }
  }

String Roll;
void receive_imu_data(const std_msgs::String& chatter){
    Roll = chatter.data;
  }


void set_pwm_values() {
  
  // These variables will hold our desired PWM values
  static int pwmLeftOut = 0;
  static int pwmRightOut = 0;
 
  // If the required PWM is of opposite sign as the output PWM, we want to
  // stop the car before switching direction
  /*
  static bool stopped = false;
  if ((pwmLeftReq * velLeftWheel < 0 && pwmLeftOut != 0) ||
      (pwmRightReq * velRightWheel < 0 && pwmRightOut != 0)) {
    pwmLeftReq = 0;
    pwmRightReq = 0;
    }
   */
 
  // Set the direction of the motors
  if (velocity > 0 || angvelocity > 0) { // Left wheel forward
    forward = true;
    backward = false;
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if (velocity < 0 || angvelocity < 0) { // Left wheel reverse
    backward = true;
    forward = false;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else if (velocity == 0 && angvelocity == 0 ) { // Left wheel stop
    forward = false;
    backward = false;
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } else { // Left wheel stop
    forward = false;
    backward = false;
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
 
  if (velocity > 0 || angvelocity > 0) { // Right wheel forward
    forward = true;
    backward = false;
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(velocity < 0 || angvelocity < 0) { // Right wheel reverse
    backward = true;
    forward = false;
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (velocity == 0 && angvelocity == 0) { // Right wheel stop
    forward = false;
    backward = false;
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } else { // Right wheel stop
    forward = false;
    backward = false;
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

 
  // Set the PWM value DRIVING FORWARD
  if(FadeStopForward != 0 && isdriving == false && forward == true && backward == false)// && abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER)
  {
     targetGyro = 0;
     fadeValue = 205;
      fadeValueR = fadeValue;
      fadeValueL = fadeValue - 20;
      analogWrite(enA, fadeValueR); 
      analogWrite(enB, fadeValueL);
      //delay(100);
       Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        Serial.print("(Give PWM values Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        gyroAngleZ = 0;
        isdriving = true;
  }
  else if(isdriving == true && forward == true && backward == false){
    targetGyro = 0;
      if (targetGyro == gyroAngleZ) //&& abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER)
      {
        Serial.print("(Keep Same Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        fadeValueR = fadeValueR;
        fadeValueL = fadeValueL;
        analogWrite(enA, fadeValueL); 
        analogWrite(enB, fadeValueR);
        RightTickCount = LeftTickCount; 
      } else if (targetGyro > gyroAngleZ){ //&& abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER) {
        /*
          if (fadeValueR > 150){
            fadeValueR = fadeValueR - 3;
        } else if (fadeValueL < 255){
            fadeValueL = fadeValueL + 2;
        } 
        */
        Serial.print("(Decrease R Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enB, fadeValueR);
        analogWrite(enA, fadeValueL);
      } else if (targetGyro < gyroAngleZ){ //&& abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER) {
        /*
        if (fadeValueL > 150){
          fadeValueL = fadeValueL - 3;
        } else if (fadeValueR < 255){
          fadeValueR = fadeValueR + 2;
        } 
        */
        Serial.print("(Decrease L Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enB, fadeValueR);
        analogWrite(enA, fadeValueL); 
      } 
      if (FadeStopForward == 0 )//|| (abs(RightTickCount) > TICKS_PER_METER || abs(LeftTickCount) > TICKS_PER_METER))
      {
        analogWrite(enA, 0);
        delay(10); 
        analogWrite(enB, 0);
        FadeStopForward = 0;
        isdriving = false;
      }
  }
  

  // Set the PWM value DRIVING BACKWARDS
  else if(FadeStopForward != 0 && isdriving == false && backward == true && forward == false)// && abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER)
  {
     targetGyro = 0;
     fadeValue = 255;
      fadeValueR = fadeValue;
      fadeValueL = fadeValue;
      analogWrite(enA, fadeValueL); 
      delay(50);
      analogWrite(enB, fadeValueR);
      //delay(100);
       Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        Serial.print("(Give PWM values Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        gyroAngleZ = 0;
        isdriving = true;
  }
  else if(isdriving == true && backward == true && forward == false){
    targetGyro = 0;
      if (targetGyro == gyroAngleZ)// && abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER)
      {
        Serial.print("(Keep Same Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        fadeValueR = fadeValueR;
        fadeValueL = fadeValueL;
        analogWrite(enA, fadeValueL); 
        analogWrite(enB, fadeValueR);
        RightTickCount = LeftTickCount; 
      } else if (targetGyro < gyroAngleZ){ //&& abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER) {
        /*
          if (fadeValueR > 150){
            fadeValueR = fadeValueR - 3;
        } else if (fadeValueL < 255){
            fadeValueL = fadeValueL + 2;
        } 
        */
        Serial.print("(Decrease R Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enB, fadeValueR);
        analogWrite(enA, fadeValueL);
      } else if (targetGyro > gyroAngleZ){ //&& abs(RightTickCount) < TICKS_PER_METER && abs(LeftTickCount) < TICKS_PER_METER) {
        /*
        if (fadeValueL > 150){
          fadeValueL = fadeValueL - 3;
        } else if (fadeValueR < 255){
          fadeValueR = fadeValueR + 2;
        } 
        */
        Serial.print("(Decrease L Loop) gyroAngleZ: ");
        Serial.print(gyroAngleZ);
        Serial.println("");
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enB, fadeValueR);
        analogWrite(enA, fadeValueL); 
      } 
      if (FadeStopForward == 0)//&& (abs(RightTickCount) > TICKS_PER_METER || abs(LeftTickCount) > TICKS_PER_METER))
      {
        analogWrite(enA, 0);
        delay(10); 
        analogWrite(enB, 0);
        isdriving = false;
      }
      
 } 


 // Set the PWM value TURNING
 
 if (FadeStopTurning != 0 && isturning == false && forward == true){
        fadeValueL = 205;
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enA, fadeValueL);
        analogWrite(enB, 0);
        isturning = true;
 } else if(isturning == true){
      targetGyro = 90;
      if (angvelocity < 0){
        fadeValueL = 205;
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enA, fadeValueL);
        analogWrite(enB, 0);
        isturning = true;
      }else if(angvelocity > 0){
        fadeValueR = 205;
        Serial.print("Left Fade Value: ");
        Serial.print(fadeValueL);
        Serial.println("");
        Serial.print("Right Fade Value: ");
        Serial.print(fadeValueR);
        Serial.println("");
        analogWrite(enB, fadeValueR);
        analogWrite(enA, 0);
        isturning = true;
      }else if(FadeStopTurning == 0){
        analogWrite(enA, 0);
        analogWrite(enB, 0);
        isturning = false;
      }
 }
}
 
// Set up ROS subscriber to the velocity command
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &calc_pwm_values );
ros::Subscriber<std_msgs::String> subChatter("chatter", &receive_imu_data );

void readAcceleration(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    XAccel = a.acceleration.x + -0.57;
    YAccel = a.acceleration.y + 0.17;
    ZAccel = a.acceleration.z + 1.76;
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
void setup(void) {
  
  myServo.attach(7);
  moveStartTime = millis();
  
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
  nh.subscribe(subChatter);
  calcError();
}

long publisher_timer;

void loop() {

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
  
  /*
  Serial.print("Current Angle X = ");
  Serial.print(gyroAngleX);
  Serial.println("");
  Serial.print("Current Angle Y = ");
  Serial.print(gyroAngleY);
  Serial.println("");
  Serial.print("Current Angle Z = ");
  Serial.print(gyroAngleZ);
  Serial.println("");
  */

  
 
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

  // If the time interval has passed, publish the number of ticks,
  // and calculate the velocities.
  if (currentMillis - previousMillis > interval) {
     
    previousMillis = currentMillis;
 
    // Publish tick counts to topics
    leftPub.publish( &left_wheel_tick_count );
    rightPub.publish( &right_wheel_tick_count );

    // Publish IMU Data
    
 
    // Calculate the velocity of the right and left wheels
    calc_vel_right_wheel();
    calc_vel_left_wheel();
     
  }
    double time_diff = 0;
    last_last_cmd_recv = (millis()/1000);

    time_diff = last_last_cmd_recv - last_cmd_recv;
    /*
    Serial.println("TIME DIFFERENCE = ");
    Serial.println(time_diff);
    Serial.println(" ");
    */

    if (time_diff > 1) {
      isdriving = false;
      isturning = false;
      FadeStopForward = 0;
      FadeStopTurning = 0;
      RightTickCount = 0;
      LeftTickCount = 0;
      velocity = 0;
      angvelocity = 0;
    }
    /*
    Serial.print("DATA BEING RECEIVED");
    Serial.println(Roll);
    Serial.println("");
    Serial.print("IS CAR DRIVING?");
    Serial.print(isdriving);
    Serial.println("");
    Serial.print("IS CAR TURNING?");
    Serial.print(isturning);
    Serial.println("");
    Serial.print("Forward?");
    Serial.print(forward);
    Serial.println("");
    Serial.print("Backward?");
    Serial.print(backward);
    Serial.println("");
    Serial.print("FadeStopForward???");
    Serial.print(FadeStopForward);
    Serial.println("");
    Serial.print("RightTickCount?");
    Serial.print(RightTickCount);
    Serial.println("");
     Serial.print("LeftTickCount?");
    Serial.print(LeftTickCount);
    Serial.println("");
    */
    set_pwm_values();
    nh.spinOnce();
    delay(1);
}
