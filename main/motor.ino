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
  XZ.write(90); 

  
}


void turret_position(int x_pos, int y_pos, bool change_x, bool change_y) {

  YZ.write(y_pos); 
  XZ.write(x_pos);   
 
}
