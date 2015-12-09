#include <EEPROM.h>
#include <Wire.h>
#include <UF_uArm_Metal_new.h>
#include <Servo.h>
#include <stdlib.h>

String incomingString="";
UF_uArm uarm;

void setup() {
      Serial.begin(9600);  // start serial port at 9600 bps
      Serial.setTimeout(100);
      uarm.init();
}
void loop() {
  
  /*uarm.writeAngle(60.45,100.22,30.55,85.370);
  delay(3000);
  uarm.writeAngle(60.45,135.22,50.55,85.370);*/
  
  //readSignalFromComp();
  float angles[4];
  int number1 = 0;
  int number2 = 0;
  
  if(Serial.find("D")){
    number1 = Serial.parseInt();
    number2 = Serial.parseInt();
    angles[0] = angleOfMotor(number1, number2);
  }
  if(Serial.find("L")){
    number1 = Serial.parseInt();
    number2 = Serial.parseInt();
    angles[1] = angleOfMotor(number1, number2);
  }
  if(Serial.find("R")){
    number1 = Serial.parseInt();
    number2 = Serial.parseInt();
    angles[2] = angleOfMotor(number1, number2);
  }
  if(Serial.find("K")){
    number1 = Serial.parseInt();
    number2 = Serial.parseInt();
    angles[3] = angleOfMotor(number1, number2);
  }
  uarm.writeAngle(angles[0],angles[1],angles[2],angles[3]);
  
  Serial.println(angles[0]);
  Serial.println(angles[1]);
  Serial.println(angles[2]);
  Serial.println(angles[3]);
  
  delay(1000);
}

void readSignalFromComp() {
  if (Serial.available() > 0)
      incomingString = "";
  while (Serial.available() > 0){
     incomingString += Serial.read(); 
  }
  if (!incomingString.equals(""))
    Serial.print(incomingString);
}

float angleOfMotor(int number1, int number2){
  
  int lenVal = 0;
  float number = 0.0;
  
  number = float(number2);

  if(number2 > 9999)
    lenVal = 5;
  else if(number2 > 999)
    lenVal = 4;
  else if(number2 > 99)
    lenVal = 3;
  else if(number2 > 9)
    lenVal = 2;
  else
    lenVal = 1;
    
  for(int i=1;i<=lenVal;i++){
    number = number/10;
  }
  
  number = float(number1) + number;
  //Serial.println(number,3);
  return number;
}


