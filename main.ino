// includes


// global variables
#define DEV_ADDR 0x68 // addr = 0b1101000 bc AD0 low
#define SCALE 4096 

void setup() {
  
  accel_setup(DEV_ADDR); 

  motor_setup(); 

  
}


void loop() {

  accel_loop(DEV_ADDR, SCALE); 

  motor_loop(); 
  
}
