// includes
#include"RunAvg.h"

// global variables
#define DEV_ADDR 0x68 // addr = 0b1101000 bc AD0 low
#define SCALE 4096 
RunAvg x_runavg; 
RunAvg y_runavg; 
#define X_OS 300 
#define Y_OS 0

void setup() {

  Serial.begin(115200); 

  // peripherals setup
  accel_setup(DEV_ADDR); 
  motor_setup(); 

  // load running average 
  float x_temp = 0; 
  float y_temp = 0; 
  for (int i=0; i<10; i++) {
    accel_loop(DEV_ADDR, SCALE, &x_temp, &y_temp); 
    x_runavg.update_avg(x_temp); 
    y_runavg.update_avg(y_temp); 
  }
  
}


void loop() {

  // variables 
  float x_pos; 
  float y_pos; 
  float x_pos_prev = 0; 
  float y_pos_prev = 0; 
  bool change_x = false; 
  bool change_y = false; 

  // new running average 
  accel_loop(DEV_ADDR, SCALE, &x_pos, &y_pos); 
  x_runavg.update_avg(x_pos); 
  y_runavg.update_avg(y_pos); 

  // apply offset, convert to angle 
  x_pos = constrain(x_runavg.get_avg()-X_OS, -1*SCALE, SCALE); 
  x_pos = constrain(trig_math(x_pos, SCALE)+90, 0, 180); 
  y_pos = constrain(y_runavg.get_avg()-Y_OS, -1*SCALE, SCALE); 
  y_pos = constrain(trig_math(y_pos, SCALE)+90, 0, 180); 

  // check
//  Serial.println("---"); 
//  Serial.println(x_pos); 
//  Serial.println(y_pos); 
//  Serial.println("---"); 

  // send to motors
  if (x_pos == x_pos_prev) {
    x_pos_prev = x_pos; 
    change_x = true; 
  }
  else change_x = false; 
  if (y_pos == y_pos_prev) {
    y_pos_prev = y_pos; 
    change_y = true; 
  }
  else change_y = false; 
  turret_position(x_pos, y_pos, change_x, change_y); 
  

  // delay 
//  delay(500); 
  
}
