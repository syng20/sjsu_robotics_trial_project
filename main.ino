// includes

// addr = 0b1101000 bc AD0 low
byte dev_addr = 0x68; 
int scale = 4096; 

void setup() {
  
  accel_setup(dev_addr); 


  
}


void loop() {

  accel_loop(dev_addr, scale); 
  
}
