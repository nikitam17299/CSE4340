// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include "Wire.h" // This library allows you to communicate with I2C devices.

//#include SoftwareSerial.h

//import processing.serial.*;
//Serial myPort; //creates a software serial port on which you will listen to Arduino
//Table dataTable; //table where we will read in and store values. You can name it something more creative!
 
//int numReadings = 500; //keeps track of how many readings you'd like to take before writing the file. 
//int readingCounter = 0; //counts each reading to compare to numReadings. 
// 
//String fileName;
//float sensorVals[] = {0,0,0}

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z,rms_acc; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z,rms_gyro; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
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

  
  
  // print out data
////Serial.print("aX = "); 
//  Serial.print(convert_int16_to_str(accelerometer_x));
//  Serial.print(" ");
//  //Serial.print(" | aY = ");
//  Serial.print(convert_int16_to_str(accelerometer_y));
//  Serial.print(" ");
//  //Serial.print(" | aZ = ");
//  Serial.print(convert_int16_to_str(accelerometer_z));
//  Serial.print(" ");
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
//  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
 // Serial.print("gX"); 
 Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(",");
 //Serial.print("gY"); 
 Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(",");
 // Serial.print("gZ"); 
 Serial.print(convert_int16_to_str(gyro_z));
  Serial.print(",");
  //Serial.println("rms_g"); 
  Serial.print(convert_int16_to_str(rms_gyro));
  Serial.print(",");
  Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(",");
  Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(",");
  Serial.print(convert_int16_to_str(accelerometer_z));
  Serial.print(",");
  Serial.println(convert_int16_to_str(rms_acc));
  //Serial.print(" ");
//  Serial.print(" | rms_acc = "); Serial.print(convert_int16_to_str(rms_acc));
//  Serial.print(" ");
 // Serial.println();

  //serialEvent();
  // delay
  delay(100);


  
}
