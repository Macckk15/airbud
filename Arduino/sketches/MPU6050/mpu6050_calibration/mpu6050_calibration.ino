// Arduino sketch that returns calibration offsets for MPU6050 
//   Version 1.1  (31th January 2014)
//   Version 1.2 (25th August 2019)
// Done by Luis Ródenas <luisrodenaslorda@gmail.com> and improved by Shakeel <blinkmaker.com>
// Based on the I2Cdev library and previous work by Jeff Rowberg <jeff@rowberg.net>
// Updates (of the library) should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib

// These offsets were meant to calibrate MPU6050's internal DMP, but can be also useful for reading sensors. 
// The effect of temperature has not been taken into account so I can't promise that it will work if you 
// calibrate indoors and then use it outdoors. Best is to calibrate and use at the same room temperature.

/* ==========  LICENSE  ==================================
 I2Cdev device library code is placed under the MIT license
 Copyright (c) 2011 Jeff Rowberg
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 =========================================================
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

///////////////////////////////////   CONFIGURATION   /////////////////////////////
//Change this 3 variables if you want to fine tune the skecth to your needs.
int buffersize=1000;     //Amount of readings used to average, make it higher to get more precision but sketch will be slower  (default:1000)
int acel_deadzone=8;     //Acelerometer error allowed, make it lower to get more precision, but sketch may not converge  (default:8)
int gyro_deadzone=1;     //Gyro error allowed, make it lower to get more precision, but sketch may not converge  (default:1)

// default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;

Adafruit_MPU6050 mpu;

double ax, ay, az,gx, gy, gz;

double mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz,state=0;
int ax_offset,ay_offset,az_offset,gx_offset,gy_offset,gz_offset;

int mpuConnection;

///////////////////////////////////   SETUP   ////////////////////////////////////
void setup() {
 Serial.begin(115200);
  while (!Serial){
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  while (Serial.available() && Serial.read()); // empty buffer
  
  Serial.println("Place the MPU-6050 breakout board in a flat or horizontal position, with SMD components facing up.\n");
  Serial.println(F("Type in any character and press Enter/Send to start MPU-6050 calibration..."));
  
  while (Serial.available() == 0){ } //wait for character to be entered               
  while (Serial.available() && Serial.read()); // empty buffer again

  // start message
  Serial.println("\n--------------------------------------------------------------");
  Serial.println("\nStarting MPU-6050 Calibration Sketch.");
  delay(1000);
  Serial.println("\nDon't touch the MPU-6050 until you see a \"FINISHED!\" message.");
  delay(2000);
  // initialize MPU-6050
   // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("\nMPU-6050 connection SUCCESSFUL!");
  delay(500);
  Serial.println("\n--------------------------------------------------------------");
  delay(500);
}

///////////////////////////////////   LOOP   ////////////////////////////////////
void loop() {
  if (state==0){
    Serial.println("\nReading accelerometer and gyroscope sensors for first time.");
    meansensors();
    state++;
    delay(1000);
  }

  if (state==1) {
    Serial.println("\nCalculating offsets");
    state++;
    delay(1000);
  }

  if (state==2) {
    meansensors();
    Serial.println("\nFINISHED!");
    Serial.println("\n==============================================================");
    Serial.println("\nRESULTS:");
    Serial.println("\nSensor data is listed in the format:\tacelX\tacelY\tacelZ\tgyroX\tgyroY\tgyroZ");
    Serial.print("\nSensor readings INCLUDING offsets:\t");
    Serial.print(-mean_ax); 
    Serial.print("\t");
    Serial.print(-mean_ay); 
    Serial.print("\t");
    Serial.print(9.81-mean_az); 
    Serial.print("\t");
    Serial.print(-mean_gx); 
    Serial.print("\t");
    Serial.print(-mean_gy); 
    Serial.print("\t");
    Serial.println(-mean_gz);
    
    while (1);
  }
}

///////////////////////////////////   FUNCTIONS   ////////////////////////////////////
void meansensors(){
  double i=0,buff_ax=0,buff_ay=0,buff_az=0,buff_gx=0,buff_gy=0,buff_gz=0;

  while (i<(buffersize+101)){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // read raw accel/gyro measurements from device

    ax = a.acceleration.x;
    ay = a.acceleration.y;
    az = a.acceleration.z;

    gx = g.gyro.x;
    gy = g.gyro.y;
    gz = g.gyro.z;
    
    if (i>100 && i<=(buffersize+100)){ //First 100 measures are discarded
      buff_ax=buff_ax+ax;
      buff_ay=buff_ay+ay;
      buff_az=buff_az+az;
      buff_gx=buff_gx+gx;
      buff_gy=buff_gy+gy;
      buff_gz=buff_gz+gz;
    }
    if (i==(buffersize+100)){
      mean_ax=buff_ax/buffersize;
      mean_ay=buff_ay/buffersize;
      mean_az=buff_az/buffersize;
      mean_gx=buff_gx/buffersize;
      mean_gy=buff_gy/buffersize;
      mean_gz=buff_gz/buffersize;
    }
    i++;
    delay(2); //Needed so we don't get repeated measures
  }
}
