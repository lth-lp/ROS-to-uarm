#include <EEPROM.h>
#include <Wire.h>
#include <UF_uArm_Metal_new.h>
#include <Servo.h>
#include <stdlib.h>

char chr_servo[64] = {3};
UF_uArm uarm;

void setup() {
      Serial.begin(9600);  // start serial port at 9600 bps
      uarm.init();
}

void loop() {
  chr_servo[0] = '%';
  for (int i=0; i<4; i++)
  {
    dtostrf(uarm.readAngle(i+1), 3, 4, &chr_servo[i*7+1]);
    chr_servo[(i+1)*7] = ';';
  }
  
  Serial.println(chr_servo);
  delay(100);
}
