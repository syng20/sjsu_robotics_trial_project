// includes
#include<Servo.h>

// servo pins
#define YZ_SP 9 // D9
#define XZ_SP 10 // D10

Servo YZ; 
Servo XZ; 


void motor_setup() {
  
  YZ.attach(YZ_SP, 580, 2600);
  XZ.attach(XZ_SP, 580, 2600); 

  YZ.write(90); 
  XZ.writeMicroseconds(1500); 

  
}


void turret_position(int x_pos, int y_pos) {

  YZ.write(y_pos); 
  XZ.write(x_pos);   
 
}
