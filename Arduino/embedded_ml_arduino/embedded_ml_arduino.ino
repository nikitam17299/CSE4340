// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <model.h>
#define NUM_SAMPLES 20
#define NUM_AXES 3
int drinking =0;
int eating =0;
int drinking_f =0;
int eating_f =0;
double features[NUM_SAMPLES * NUM_AXES];
Eloquent::ML::Port::SVM classifier;

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z,rms_acc; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z,rms_gyro; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void imu_read()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
// "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
 accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)

 if(accelerometer_x<0)
  {
    accelerometer_x = -accelerometer_x;
  }
 
 accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)

if(accelerometer_y<0)
  {
    accelerometer_y = -accelerometer_y;
  }
 
 accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

if(accelerometer_z<0)
  {
    accelerometer_z = -accelerometer_z;
  }
 
//  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)

  if(gyro_x<0)
  {
    gyro_x = -gyro_x;
  }
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
   if(gyro_y<0)
  {
    gyro_y = -gyro_y;
  }
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
   if(gyro_z<0)
  {
    gyro_z = -gyro_z;
  }

  rms_acc = sqrt((accelerometer_x*accelerometer_x)+(accelerometer_y*accelerometer_y)+(accelerometer_z*accelerometer_z));
  rms_gyro = sqrt((gyro_x*gyro_x)+(gyro_y*gyro_y)+(gyro_z*gyro_z));
}



void recordIMU() {
  //  float ax, ay, az;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        imu_read();

       
        features[i * NUM_AXES + 0] = accelerometer_x;
        features[i * NUM_AXES + 1] = accelerometer_y;
        features[i * NUM_AXES + 2] = accelerometer_z;

          delay(1000);
    }
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);
    
    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? 'n' : ',');
    }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  

  
}
void loop() {
  


//printFeatures();
  //delay(100);
recordIMU();
//printFeatures();

    if(drinking == 0) 
    {
      Serial.println("Activity Recognized: Drinking ");
      drinking = 1;
      drinking_f =1;
      
    }

    else 
    {
      classify();
    }
delay(1000);

  
}

void classify() {
 float x_sample[] = { /* fill this vector with sample values */ };

    if(drinking_f == 1)
    {
    Serial.print("Activity Recognized: ");
    Serial.println(classifier.predictLabel(x_sample));
    }
}
