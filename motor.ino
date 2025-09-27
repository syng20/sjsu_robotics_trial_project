// includes
#include<Servo.h>

// servo pins
#define YZ_SP 9 // D9
#define XY_SP 10 // D10

Servo YZ; 
Servo XY; 


void motor_setup() {
  
//  pinMode(YZ_SP, OUTPUT); 
//  pinMode(XY_SP, OUTPUT); 
//
//  Serial.begin(115200); 

  YZ.attach(YZ_SP);
  XY.attach(XY_SP); 

  
}


void motor_loop() {

//  analogWrite(YZ_SP, 

  YZ.writeMicroseconds(1500); 
  XY.writeMicroseconds(1500); 
  delay(500); 

  YZ.writeMicroseconds(1000); 
  XY.writeMicroseconds(1000); 
  delay(500); 

  YZ.writeMicroseconds(2000); 
  XY.writeMicroseconds(2000); 
  delay(500); 

  
}
