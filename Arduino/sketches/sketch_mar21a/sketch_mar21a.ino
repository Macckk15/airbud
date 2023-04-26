/*******************************************************************************/
#include <ros.h>
#include <Wire.h>
#include <sensor_msgs/Imu.h>

ros::NodeHandle  nh;

sensor_msgs::Imu msg_imu;
ros::Publisher pub_imu("imu", &msg_imu);

/*******************************************************************************/
#include "ICM_20948.h" // https://github.com/sparkfun/SparkFun_ICM-20948_ArduinoLibrary

#define DEBUG
#define TEST

#define SERIAL_PORT Serial

#define WIRE_PORT Wire
#define AD0_VAL 9

ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object

unsigned long timestamp;

float q0;
float q1;
float q2;
float q3;

float roll;
float pitch;
float yaw;

float acc_x;
float acc_y;
float acc_z;
const float acc_cov = (1 / (8.192 * 1000.0))  * (9.80665); // 4 mili g's to m/s^2

float gyr_x;
float gyr_y;
float gyr_z;
const float gyr_cov = (1 / 16.4) * (PI / 180); // 2000 dps to rad/s
/*******************************************************************************/

unsigned long t_clock;
unsigned long t1_next;
unsigned long t1_period = 20; // ms - 50 Hz

/*******************************************************************************/
void setup()
{
#ifdef DEBUG
  SERIAL_PORT.begin(115200); // Start the serial console

  while (!SERIAL_PORT);

  SERIAL_PORT.println(F("ICM-20948 Example"));
  
#endif

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

#ifdef DEBUG
  
  myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial
  
#endif

  bool initialized = false;
  while (!initialized)
  {
      
    // Initialize the ICM-20948
    // If the DMP is enabled, .begin performs a minimal startup. We need to configure the sample mode etc. manually.
    myICM.begin(WIRE_PORT, AD0_VAL, 20);
    SERIAL_PORT.print(F("BING BONG: "));

#ifdef DEBUG
    
    SERIAL_PORT.print(F("Initialization of the sensor returned: "));
    SERIAL_PORT.println(myICM.statusString());
#endif
    if (myICM.status != ICM_20948_Stat_Ok)
    {
#ifdef DEBUG
      SERIAL_PORT.println(F("Trying again..."));
#endif
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }

#ifdef DEBUG
  SERIAL_PORT.println(F("Device connected!"));
#endif

  bool success = true; // Use success to show if the DMP configuration was successful

  // Initialize the DMP. initializeDMP is a weak function. You can overwrite it if you want to e.g. to change the sample rate
  success &= (myICM.initializeDMP() == ICM_20948_Stat_Ok);

  // DMP sensor options are defined in ICM_20948_DMP.h
  //    INV_ICM20948_SENSOR_ACCELEROMETER               (16-bit accel)
  //    INV_ICM20948_SENSOR_GYROSCOPE                   (16-bit gyro + 32-bit calibrated gyro)
  //    INV_ICM20948_SENSOR_RAW_ACCELEROMETER           (16-bit accel)
  //    INV_ICM20948_SENSOR_RAW_GYROSCOPE               (16-bit gyro + 32-bit calibrated gyro)
  //    INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED (16-bit compass)
  //    INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED      (16-bit gyro)
  //    INV_ICM20948_SENSOR_STEP_DETECTOR               (Pedometer Step Detector)
  //    INV_ICM20948_SENSOR_STEP_COUNTER                (Pedometer Step Detector)
  //    INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR        (32-bit 6-axis quaternion)
  //    INV_ICM20948_SENSOR_ROTATION_VECTOR             (32-bit 9-axis quaternion + heading accuracy)
  //    INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR (32-bit Geomag RV + heading accuracy)
  //    INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD           (32-bit calibrated compass)
  //    INV_ICM20948_SENSOR_GRAVITY                     (32-bit 6-axis quaternion)
  //    INV_ICM20948_SENSOR_LINEAR_ACCELERATION         (16-bit accel + 32-bit 6-axis quaternion)
  //    INV_ICM20948_SENSOR_ORIENTATION                 (32-bit 9-axis quaternion + heading accuracy)

  // Enable the DMP orientation sensor
  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_ORIENTATION) == ICM_20948_Stat_Ok);
  // Enable the DMP accelerometer
  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_ACCELEROMETER) == ICM_20948_Stat_Ok);
  // Enable the DMP gyroscope
  success &= (myICM.enableDMPSensor(INV_ICM20948_SENSOR_GYROSCOPE) == ICM_20948_Stat_Ok);

  // Configuring DMP to output data at multiple ODRs:
  // DMP is capable of outputting multiple sensor data at different rates to FIFO.
  // Setting value can be calculated as follows:
  // Value = (DMP running rate / ODR ) - 1
  // E.g. For a 5Hz ODR rate when DMP is running at 55Hz, value = (55/5) - 1 = 10.
  success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Quat9, 0) == ICM_20948_Stat_Ok); // Set to the maximum
  success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Accel, 0) == ICM_20948_Stat_Ok); // Set to the maximum
  success &= (myICM.setDMPODRrate(DMP_ODR_Reg_Gyro, 0) == ICM_20948_Stat_Ok); // Set to the maximum

  // Enable the FIFO
  success &= (myICM.enableFIFO() == ICM_20948_Stat_Ok);

  // Enable the DMP
  success &= (myICM.enableDMP() == ICM_20948_Stat_Ok);

  // Reset DMP
  success &= (myICM.resetDMP() == ICM_20948_Stat_Ok);

  // Reset FIFO
  success &= (myICM.resetFIFO() == ICM_20948_Stat_Ok);

  // Check success
  if (success)
  {
#ifdef DEBUG
    SERIAL_PORT.println(F("DMP enabled!"));
#endif
  }
  else
  {
#ifdef DEBUG
    SERIAL_PORT.println(F("Enable DMP failed!"));
    SERIAL_PORT.println(F("Please check that you have uncommented line 29 (#define ICM_20948_USE_DMP) in ICM_20948_C.h..."));
#endif
    while (1)
      ; // Do nothing more
  }

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(pub_imu);

  // Set static information of the package
  msg_imu.header.frame_id =  "/imu";
  // msg_imu.orientation_covariance[9]
  // msg_imu.angular_velocity_covariance[9]
  // msg_imu.linear_acceleration_covariance[9]
  t_clock = millis();
  t1_next = t_clock + t1_period;
}

/*******************************************************************************/

void loop()
{
  // Read any DMP data waiting in the FIFO
  // Note:
  //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFONoDataAvail if no data is available.
  //    If data is available, readDMPdataFromFIFO will attempt to read _one_ frame of DMP data.
  //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFOIncompleteData if a frame was present but was incomplete
  //    readDMPdataFromFIFO will return ICM_20948_Stat_Ok if a valid frame was read.
  //    readDMPdataFromFIFO will return ICM_20948_Stat_FIFOMoreDataAvail if a valid frame was read _and_ the FIFO contains more (unread) data.
  icm_20948_DMP_data_t data;
  myICM.readDMPdataFromFIFO(&data);

  if ((myICM.status == ICM_20948_Stat_Ok) || (myICM.status == ICM_20948_Stat_FIFOMoreDataAvail)) // Was valid data available?
  {
    //SERIAL_PORT.print(F("Received data! Header: 0x")); // Print the header in HEX so we can see what data is arriving in the FIFO
    //if ( data.header < 0x1000) SERIAL_PORT.print( "0" ); // Pad the zeros
    //if ( data.header < 0x100) SERIAL_PORT.print( "0" );
    //if ( data.header < 0x10) SERIAL_PORT.print( "0" );
    //SERIAL_PORT.println( data.header, HEX );

    if ((data.header & DMP_header_bitmap_Quat9) > 0) // We have asked for orientation data so we should receive Quat9
    {
      // Q0 value is computed from this equation: Q0^2 + Q1^2 + Q2^2 + Q3^2 = 1.
      // In case of drift, the sum will not add to 1, therefore, quaternion data need to be corrected with right bias values.
      // The quaternion data is scaled by 2^30.

      //SERIAL_PORT.printf("Quat9 data is: Q1:%ld Q2:%ld Q3:%ld Accuracy:%d\r\n", data.Quat9.Data.Q1, data.Quat9.Data.Q2, data.Quat9.Data.Q3, data.Quat9.Data.Accuracy);

      // Scale to +/- 1
      q1 = ((float)data.Quat9.Data.Q1) / 1073741824.0; // Convert to double. Divide by 2^30
      q2 = ((float)data.Quat9.Data.Q2) / 1073741824.0; // Convert to double. Divide by 2^30
      q3 = ((float)data.Quat9.Data.Q3) / 1073741824.0; // Convert to double. Divide by 2^30
      q0 = ((float)sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3))));

      float q2sqr = q2 * q2;

      // roll (x-axis rotation)
      float t0 = +2.0 * (q0 * q1 + q2 * q3);
      float t1 = +1.0 - 2.0 * (q1 * q1 + q2sqr);
      roll = (float) atan2(t0, t1); // rad/s

      // pitch (y-axis rotation)
      float t2 = +2.0 * (q0 * q2 - q3 * q1);
      t2 = t2 > 1.0 ? 1.0 : t2;
      t2 = t2 < -1.0 ? -1.0 : t2;
      pitch = (float) asin(t2); // rad/s

      // yaw (z-axis rotation)
      float t3 = +2.0 * (q0 * q3 + q1 * q2);
      float t4 = +1.0 - 2.0 * (q2sqr + q3 * q3);
      yaw = (float) atan2(t3, t4); // rad/s

#ifdef DEBUG
      timestamp = millis();
      SERIAL_PORT.print(timestamp);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(q0, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(q1, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(q2, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(q3, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(roll, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(pitch, 3);
      //      SERIAL_PORT.print(F(","));
      //      SERIAL_PORT.print(yaw, 3);
      //SERIAL_PORT.println();
#endif
    }

    if ((data.header & DMP_header_bitmap_Accel) > 0) // Check the packet contains Accel data
    {
      acc_x = ((float)data.Raw_Accel.Data.X) * acc_cov; // Extract the raw accelerometer data
      acc_y = ((float)data.Raw_Accel.Data.Y) * acc_cov;
      acc_z = ((float)data.Raw_Accel.Data.Z) * acc_cov;

#ifdef DEBUG
            SERIAL_PORT.print(F(","));
            SERIAL_PORT.print(acc_x);
            SERIAL_PORT.print(F(","));
            SERIAL_PORT.print(acc_y);
            SERIAL_PORT.print(F(","));
            SERIAL_PORT.print(acc_z);
      //SERIAL_PORT.println();
#endif
    }

    if ((data.header & DMP_header_bitmap_Gyro) > 0) // Check the packet contains Accel data
    {
      gyr_x = ((float)data.Raw_Gyro.Data.X - data.Raw_Gyro.Data.BiasX) * gyr_cov; // Extract the raw accelerometer data
      gyr_y = ((float)data.Raw_Gyro.Data.Y - data.Raw_Gyro.Data.BiasY) * gyr_cov;
      gyr_z = ((float)data.Raw_Gyro.Data.Z - data.Raw_Gyro.Data.BiasZ) * gyr_cov;

#ifdef DEBUG
      SERIAL_PORT.print(F(","));
      SERIAL_PORT.print(gyr_x);
      SERIAL_PORT.print(F(","));
      SERIAL_PORT.print(gyr_y);
      SERIAL_PORT.print(F(","));
      SERIAL_PORT.print(gyr_z);
      SERIAL_PORT.println();
#endif
    }
  }

  if (myICM.status != ICM_20948_Stat_FIFOMoreDataAvail) // If more data is available then we should read it right away - and not delay
  {
    delay(10);
  }

#ifndef TEST
  t_clock = millis();
  if (t1_next <= t_clock) {
    msg_imu.header.stamp = nh.now();

    msg_imu.orientation.w = q0;
    msg_imu.orientation.x = q1;
    msg_imu.orientation.y = q2;
    msg_imu.orientation.z = q3;

    msg_imu.angular_velocity.x = gyr_x;
    msg_imu.angular_velocity.y = gyr_y;
    msg_imu.angular_velocity.z = gyr_z;

    msg_imu.linear_acceleration.x = acc_x;
    msg_imu.linear_acceleration.y = acc_y;
    msg_imu.linear_acceleration.z = acc_z;
    
    pub_imu.publish(&msg_imu);
    
    nh.spinOnce();

    t1_next = t1_next + t1_period;
  }
#endif
}
