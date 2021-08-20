#include <Wire.h>

#define ADDRESS_HMC5583 0x1E

#define HMC5583_REGISTER_TOTAL 13

// #define

void setup()
{
  // Initial I2C.
  Wire.begin();

  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial monitor
  Serial.print("\n\nMatrix-compass\n");

  delay(100);

  continuous_measurement_mode();
}

void loop()
{
}

/*
Below is an example of a (power-on) initialization process for “continuous-measurement mode”:
  1. Write CRA (00) – send 0x3C 0x00 0x70 (8-average, 15 Hz default, normal measurement)
  2. Write CRB (01) – send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain)
  3. Write Mode (02) – send 0x3C 0x02 0x00 (Continuous-measurement mode)
  4. Wait 6 ms or monitor status register or DRDY hardware interrupt pin
  5.  Loop
        Send 0x3D 0x06 (Read all 6 bytes. If gain is changed then this data set is using previous gain)
        Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively.
        Send 0x3C 0x03 (point to first data register 03)
        Wait about 67 ms (if 15 Hz rate) or monitor status register or DRDY hardware interrupt pin
      End_loop
*/

// Below is an example of a (power-on) initialization process for “continuous-measurement mode”
void continuous_measurement_mode(void)
{
  // 1. Write CRA (0x00) – value 0x70 (8-average, 15 Hz default, normal measurement)
  // 2. Write CRB (0x01) – value 0xA0 (Gain=5, or any other desired gain)
  // 3. Write Mode (0x02) – value 0x00 (Continuous-measurement mode)
  uint8_t ary_cmd[] = {
      0x70,
      0xA0,
      0x00,
  };
  const int len = sizeof(ary_cmd) / sizeof(ary_cmd[0]);

  // Point to first data register CRA (0x00).
  I2C_WriteMultiBytesOneReg(ADDRESS_HMC5583, 0x00, ary_cmd, len);

  // 4. Wait 6 ms or monitor status register or DRDY hardware interrupt pin
  delay(6);

  // 5.  Loop
  uint8_t read_data[6] = {};
  int16_t data_X = 0;
  int16_t data_Y = 0;
  int16_t data_Z = 0;
  while (1)
  {
    // Point to first data register DXRA (0x03).
    // Read all 6 bytes. If gain is changed then this data set is using previous gain.
    I2C_ReadMultiBytesOneReg(ADDRESS_HMC5583, 0x03, read_data, 6);

    // print
    // print_hex(read_data, 6);

    // Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively.
    data_X = ((read_data[0] << 8) | read_data[1]);
    data_Z = ((read_data[2] << 8) | read_data[3]);
    data_Y = ((read_data[4] << 8) | read_data[5]);

    Serial.print("x: ");
    Serial.print(data_X);
    Serial.print(", y: ");
    Serial.print(data_Y);
    Serial.print(", z: ");
    Serial.print(data_Z);
    Serial.print("\n");

    // Wait about 67 ms (if 15 Hz rate) or monitor status register or DRDY hardware interrupt pin.
    delay(67);

    delay(300); // For human read.
  }
}

void print_hex(uint8_t data[], uint32_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    int val = data[i];
    if (val < 0x10)
    {
      Serial.print("0"); // print leading zeroe
    }
    Serial.print(val, HEX); // print the character
    Serial.print(" ");
  }
  Serial.print("\n");
}

void hmc5883Init(byte address)
{
  Wire.beginTransmission(address); // transmit to device #8
  Wire.write(0x00);                // sends one byte
  Wire.write(0x70);                // sends one byte
  Wire.write(0xA0);                // sends one byte
  Wire.write(0x00);                // sends one byte
  Wire.endTransmission();          // stop transmitting
}

void I2C_WriteMultiBytesOneReg(uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t data[], uint32_t u32wLen)
{
  Wire.beginTransmission(u8SlaveAddr); // transmit start
  Wire.write(u8DataAddr);              // sends one byte
  Wire.write(data, u32wLen);           // sends bytes
  Wire.endTransmission();              // transmit stop
}

void I2C_ReadMultiBytesOneReg(uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t rdata[], uint32_t u32rLen)
{
  int count = 0;

  Wire.beginTransmission(u8SlaveAddr);    // transmit to device #8
  Wire.write(u8DataAddr);                 // sends one byte
  Wire.requestFrom(u8SlaveAddr, u32rLen); // request 6 bytes from slave device #8

  while (Wire.available())
  {                             // slave may send less than requested
    rdata[count] = Wire.read(); // receive a byte as character
    count++;
  }

  Wire.endTransmission(); // stop transmitting

  // // print
  // for (uint8_t i = 0; i < count; i++)
  // {
  //   int val = rdata[i];
  //   if (val < 0x10)
  //   {
  //     Serial.print("0"); // print leading zeroe
  //   }
  //   Serial.print(val, HEX); // print the character
  //   Serial.print(" ");
  // }

  // Serial.print("\ncount: ");
  // Serial.println(count);
  // Serial.print("I2C_Read done\n");
}

void Chk_I2C_Address(byte address)
{

  // The i2c_scanner uses the return value of
  // the Write.endTransmisstion to see if
  // a device did acknowledge to the address.
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();

  if (error == 0)
  {
    Serial.print("I2C device found at address 0x");
    if (address < 16)
    {
      Serial.print("0");
    }
    Serial.print(address, HEX);
    Serial.print("  !\n");
  }
  else if (error == 4)
  {
    Serial.print("Unknown error at address 0x");
    if (address < 16)
    {
      Serial.print("0");
    }
    Serial.println(address, HEX);
  }

  Serial.print("Chk_I2C_Address done\n");
}

// #include <stdio.h>
// #include <stdlib.h>
// #include "libfahw.h"

// int main(int argc, char ** argv)
// {
//     int devFD;
//     double angle;
//     int i2cDev = 0;

//     if (boardInit() < 0) {
//         printf("Fail to init board\n");
//         return -1;
//     }

//     if (argc == 2)
//         i2cDev = atoi(argv[1]);
//     if ((devFD = hmc5883Init(i2cDev)) == -1) {
//         printf("Fail to init hmc5883\n");
//         return -1;
//     }
//     if ((angle = hmc5883Read(devFD)) != -1) {
//         printf("The angle is %.1f\n", angle);
//     } else {
//         printf("Fail to read hmc5883\n");
//     }
//     hmc5883DeInit(devFD);

//     return 0;
// }
