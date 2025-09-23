// includes
#include <Wire.h>

void setup() {
  Wire.begin(); 
  Serial.begin(115200); 

  // accel setup
  Wire.beginTransmission(0x68); // addr = 0b1101000 bc AD0 low
  // check WHO_AM_I
  // should return 0x68=0b01101000=0d104
  Wire.write(0x75);
  while(Wire.endTransmission(false) != 0); 
  Wire.requestFrom(0x68, 1, false);
  Serial.println(Wire.read()); 
  
  // reg 6B,6C = power management
  // 6B = rst[1], sleep[1], cycle[1], X, temp[1], clksel[3]
  // CLKSEL = 0 (internal oscillator) 
  Wire.write(0x6B); 
  Wire.write(0xA8); // 0b10101000
  while(Wire.endTransmission(false) != 0); 
  // 6C = wake[2], xa[1], ya[1], za[1], xg[1], yg[1], zg[1] 
  // LP_WAKE_CTRL = 0 (1.25 HZ)
  Wire.write(0x6C); 
  Wire.write(0x07); // 0b00000111
  while(Wire.endTransmission(false) != 0); 
  // reg 1C = accel config 
  // 1C = x[1], y[1], z[1], full scale range [2], XXX
   Wire.write(0x1C); 
   Wire.write(0xE0); // 0b11100000
   while(Wire.endTransmission(false) != 0); 
  // reg 6A = enables 
  // 6A = X, fifo_en[1], I2C master[1], i2c if dis[1], X, fifo_rst[1], I2C master rst[1], I2c if dis rst [1]
  Wire.write(0x6A); 
  Wire.write(0x44); // 0b01000100
  while(Wire.endTransmission(false) != 0); 
  // reg 23 = FIFO
  // 23 = temp[1], xg[1], yg[1], zg[1], accel[1], slv2[1], slv1[1], slv0[1]
  Wire.write(0x23); 
  Wire.write(0x08); // 0b00001000
  while(Wire.endTransmission(false) != 0); 

}

// check if data is ready 
bool fifo_count() {
  
  static uint16_t fifo_count; 

  // top 8 bits
  Wire.write(0x72);
  Wire.endTransmission(false); 
  Wire.requestFrom(0x68, 1, false);
  fifo_count = Wire.read(); 
  fifo_count = fifo_count << 8; 
  // bottom 8 bits 
  Wire.write(0x73);
  Wire.endTransmission(false); 
  Wire.requestFrom(0x68, 1, false);
  fifo_count = fifo_count & Wire.read(); 

  // check 
  Serial.println(fifo_count); 

  if (fifo_count == 6) return true; 
  else return false; 
  
}

void loop() {

  static uint16_t accel_x; 
  static uint16_t accel_y; 
  static uint16_t accel_z; 

  // get FIFO data 
  if (fifo_count()) {

    Serial.println("huzzah"); 
  
  } 
  else {
    
    Wire.write(0x3E);
    Wire.endTransmission(false); 
    Wire.requestFrom(0x68, 1, false);
    Serial.println(Wire.read()); 

    // TODO: 
    // fifo not working 
    // weird readings from accel measurement (mostly 0s) 

    
  }

  // delay 
  delay(500); 
  
}
