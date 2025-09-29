// includes
#include"RunAvg.h"

// global variables
#define DEV_ADDR 0x68 // addr = 0b1101000 bc AD0 low
#define SCALE 4096 
RunAvg x_runavg; 
RunAvg y_runavg; 

void setup() {

  Serial.begin(115200); 

  // peripherals setup
  accel_setup(DEV_ADDR); 
  motor_setup(); 

  // load running average 
  int x_temp = 0; 
  int y_temp = 0; 
  for (int i=0; i<10; i++) {
    accel_loop(DEV_ADDR, SCALE, &x_temp, &y_temp); 
    x_runavg.update_avg(x_temp); 
    y_runavg.update_avg(y_temp); 
  }
  Serial.println(x_runavg.get_avg()); 
  Serial.println(y_runavg.get_avg()); 
  
}


void loop() {

  static int x_pos; 
  static int y_pos; 

  accel_loop(DEV_ADDR, SCALE, &x_pos, &y_pos); 
  
  Serial.println(x_pos); 
  Serial.println(y_pos);

  x_pos+=90; 
  y_pos+=90;
  
//  turret_position(x_pos, y_pos); 
  
}
