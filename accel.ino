// includes
#include <Wire.h>
#include <Math.h> 


void accel_setup(byte dev_addr) {
  Wire.begin(); 
  Wire.setClock(400000);
  Serial.begin(115200); 

  // accel setup
  // check WHO_AM_I
  // should return 0x68=0b01101000=0d104
  byte verify[1];
  verify[0] = 0; 
  read_from_reg(dev_addr, 0x75, 1, verify); 
  Serial.print("WHO_AM_I: 0x"); 
  Serial.println(verify[0], HEX); 

  // reg 6B,6C = power management
  // 6B = rst[1], sleep[1], cycle[1], X, temp[1], clksel[3]
  // CLKSEL = 0 (internal oscillator) 
  write_no_read(0x6B, 0x08); // 0b00001000
  // reg 1C = accel config 
  // 1C = x[1], y[1], z[1], full scale range [2], XXX
  write_no_read(0x1C, 0x10); // 0b00010000 
  // reg 1A = config 
  // 1A = XX, ext sync [3], dig lpf [3] 
  write_no_read(0x1A, 0x03); // 0b00000011
}



void write_no_read(byte reg_addr, byte data) {

  Wire.beginTransmission(0x68); 
  Wire.write(reg_addr); 
  Wire.write(data); 
  int err = Wire.endTransmission(true);
  if (err) Serial.println(err);  
  
}


void read_from_reg(byte dev_addr, byte reg_addr, byte rec_num, byte* message) {

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
  Wire.requestFrom(dev_addr, rec_num, (uint8_t)true);
  
  // write to message 
  while (Wire.available()) {
    c = Wire.read(); 
    message[i++] = c; 
  }
  
}

// print initial accelerometer data
void print_accel(byte* accel) {
  Serial.print("X="); 
  Serial.print(accel[0], HEX); 
  Serial.println(accel[1], HEX); 
  Serial.print("Y="); 
  Serial.print(accel[2], HEX); 
  Serial.println(accel[3], HEX); 
  Serial.print("Z="); 
  Serial.print(accel[4], HEX); 
  Serial.println(accel[5], HEX); 
}

// from hex to int
int16_t gravity_math(byte high, byte low, int scale) {
  int16_t t = (int16_t)((high << 8) + low); 
  t = constrain(t, scale*-1, scale); 
  return t; 
}

// get angle 
float trig_math(int16_t grav, int scale) {
  return (float)(asin((float)grav/scale) * 180 / 3.1415926);
}

void accel_loop(byte dev_addr, int scale) {

  // var
  static byte accel[6]; 
  static float accel_x; 
  static float accel_y; 
  static float accel_z; 

  read_from_reg(dev_addr, 0x3B, 6, accel); 
  accel_x = trig_math(gravity_math(accel[0], accel[1], scale), scale); 
  accel_y = trig_math(gravity_math(accel[2], accel[3], scale), scale); 
  accel_z = trig_math(gravity_math(accel[4], accel[5], scale), scale); 

  Serial.print("X="); 
  Serial.println(accel_x); 
  Serial.print("Y="); 
  Serial.println(accel_y); 
  Serial.print("Z="); 
  Serial.println(accel_z); 
  
//  print_accel(accel); 

  // delay 
  delay(500); 
  
}
