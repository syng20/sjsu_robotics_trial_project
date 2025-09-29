// includes


// global variables
#define DEV_ADDR 0x68 // addr = 0b1101000 bc AD0 low
#define SCALE 4096 

void setup() {

  Serial.begin(115200); 
  
  accel_setup(DEV_ADDR); 

  motor_setup(); 

  
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
