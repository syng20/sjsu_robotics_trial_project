// includes
#include <Wire.h>

// addr = 0b1101000 bc AD0 low
byte dev_addr = 0x68; 

void setup() {
  Wire.begin(); 
  Wire.setClock(400000);
  Serial.begin(115200); 

  // accel setup
  // check WHO_AM_I
  // should return 0x68=0b01101000=0d104
  byte message[10];
  message[0] = 0; 
  read_from_reg(0x75, 1, message); 
  Serial.print("m1 "); 
  Serial.println(message[0]); 
  message[0] = 0; 
  read_from_reg(0x75, 1, message); 
  Serial.print("m2 "); 
  Serial.println(message[0]); 
 
//  Wire.beginTransmission(0x68);
//  Wire.write(0x75);
//  while(Wire.endTransmission(false) != 0); 
//  Wire.requestFrom(0x68, 1, true);
//  Serial.print(",read"); 
//  Serial.println(Wire.read()); 

  // reg 6B,6C = power management
  // 6B = rst[1], sleep[1], cycle[1], X, temp[1], clksel[3]
  // CLKSEL = 0 (internal oscillator) 
  write_no_read(0x6B, 0x08); // 0b00001000
//  // 6C = wake[2], xa[1], ya[1], za[1], xg[1], yg[1], zg[1] 
//  // LP_WAKE_CTRL = 0 (1.25 HZ)
//  Wire.write(0x6C); 
//  Wire.write(0x07); // 0b00000111
//  while(Wire.endTransmission(false) != 0); 
  // reg 1C = accel config 
  // 1C = x[1], y[1], z[1], full scale range [2], XXX
  write_no_read(0x1C, 0x00); // 0b00000000 
//  // reg 6A = enables 
//  // 6A = X, fifo_en[1], I2C master[1], i2c if dis[1], X, fifo_rst[1], I2C master rst[1], I2c if dis rst [1]
//  Wire.write(0x6A); 
//  Wire.write(0x44); // 0b01000100
//  while(Wire.endTransmission(false) != 0); 
//  // reg 23 = FIFO
//  // 23 = temp[1], xg[1], yg[1], zg[1], accel[1], slv2[1], slv1[1], slv0[1]
//  Wire.write(0x23); 
//  Wire.write(0x08); // 0b00001000
//  while(Wire.endTransmission(true) != 0); 

}



void write_no_read(byte reg_addr, byte data) {

  Wire.beginTransmission(0x68); 
  Wire.write(reg_addr); 
  Wire.write(data); 
  int err = Wire.endTransmission(true);
  if (err) Serial.println(err);  
  
}


void read_from_reg(byte reg_addr, byte rec_num, byte* message) {

  // throwaway
  byte c = 0; 
  int i = 0; 

  // get transmission
  Wire.beginTransmission(dev_addr); 
  Wire.write(reg_addr);
  int err = Wire.endTransmission(false);
  if(err != 0) {
    Serial.print("err"); 
    Serial.println(err);
    return; 
    }
  Wire.requestFrom(dev_addr, rec_num, true);
  
  // write to message 
  while (Wire.available()) {
    c = Wire.read(); 
    Serial.println(c,HEX); 
    message[i++] = c; 
  }

  Serial.println(dev_addr,HEX); 
  Serial.println(reg_addr,HEX); 

  
  Serial.print(",HEYNTHERE"); 
  
}


// check if data is ready 
bool fifo_count() {
  
  static uint16_t fifo_count; 

  // top 8 bits
  Wire.beginTransmission(0x68); 
  Wire.write(0x72);
  Wire.endTransmission(false); 
  Wire.requestFrom(0x68, 1, true);
  fifo_count = Wire.read(); 
  fifo_count = fifo_count << 8; 
  // bottom 8 bits 
  Wire.beginTransmission(0x68); 
  Wire.write(0x73);
  Wire.endTransmission(false); 
  Wire.requestFrom(0x68, 1, true);
  fifo_count = fifo_count | Wire.read(); 

  // check 
  Serial.println(fifo_count); 

  if (fifo_count == 6) return true; 
  else return false; 
  
}

void loop() {


  static uint16_t accel_x; 
  static uint16_t accel_y; 
  static uint16_t accel_z; 

  

  // delay 
  delay(500); 
  
}
