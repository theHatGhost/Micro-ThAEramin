/*************************************************** 
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602
  
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
/****************************************************
Micro - ThÆramin CV controller Project for AE Modular by theHatGhost https://www.thehatghost.com -2021
Adapted from products and libraries created by Adafruit Industries - Thanks Adafruit! https://www.Adafruit.com
Developed for the excellent AE modular synth system - Thanks Tangible Waves! https://www.tangiblewaves.com/

Designed to be used with Adafruits M0 line of boards, such as the Metro/Feather/ItsyBitsy M0 Expresss 
or other ATSAMD21 Cortex M0 processor boards with a DAC, but will also work with the Arduino Nano/uno with some tweaking
*******************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

Adafruit_CAP1188 cap = Adafruit_CAP1188();

void setup() {
  //initializes the sensor
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
}

void loop() {
  //here is the main loop
  
  uint8_t raw_sensor1 = cap.readRegister(0x10);  // reads raw value for cap1188 input 1
  int CV_outPin = A0; // select CV output pin, "A0" for M0 boards 
  int note1 = 51; // these set the cv out values to controlo the notes, values from 1-256, output range is 0-3.3V
  int note2 = 102;
  int note3 = 153;
  int note4 = 204;
  int note5 = 256;


  // these just cut down on glitching / unnecessary noise
  if (raw_sensor1 < 5) {
    analogWrite(CV_outPin,0);
    return;
  }
  
  if (raw_sensor1 > 128) {
    analogWrite(CV_outPin,0);
    return;
  }
  
  // These control when each note is triggered in response to the raw value reading from the capacitance sensor / distance from sensor
  // Values range from 0-127 and seem to have a logrhythmic relationship to distance - tweak to accomodate playing style or number of notes
  
  if ((raw_sensor1 > 5 && raw_sensor1 < 25)) {
    Serial.print(raw_sensor1); analogWrite(CV_outPin,note1);}
    
  if ((raw_sensor1 > 25 && raw_sensor1 < 50)) {
    Serial.print(raw_sensor1); analogWrite(CV_outPin,note2);}
    
  if ((raw_sensor1 > 50 && raw_sensor1 < 75)) {
    Serial.print(raw_sensor1); analogWrite(CV_outPin,note3);}
    
  if ((raw_sensor1 > 75 && raw_sensor1 < 100)) {
    Serial.print(raw_sensor1); analogWrite(CV_outPin,note4);}
    
  if ((raw_sensor1 > 100 && raw_sensor1 > 125)) {
    Serial.print(raw_sensor1); analogWrite(CV_outPin,note5);}
  
    
  Serial.println();
  delay(25);
}
