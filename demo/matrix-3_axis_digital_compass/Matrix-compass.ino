#include <Wire.h>

#define ADDRESS_HMC5583 0x1E

// #define

void setup()
{
  Wire.begin(ADDRESS_HMC5583);

  Serial.begin(115200);
  while (!Serial)
    ; // Leonardo: wait for serial monitor
  Serial.print("\n\nMatrix-compass\n");

  // Chk_I2C_Address(ADDRESS_HMC5583);

  delay(1000);
  hmc5883Init(ADDRESS_HMC5583);

  delay(1000);
  I2C_Read(ADDRESS_HMC5583);
}

void loop()
{
  delay(1000);
  I2C_Read(ADDRESS_HMC5583);
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

void I2C_Read(byte address)
{
  int count = 0;

  Wire.beginTransmission(address); // transmit to device #8
  Wire.write(0x00);                // sends one byte
  Wire.requestFrom(address, 13);   // request 6 bytes from slave device #8

  while (Wire.available())
  {                        // slave may send less than requested
    int val = Wire.read(); // receive a byte as character
    if (val < 0x10)
    {
      Serial.print("0"); // print leading zeroe
    }
    Serial.print(val, HEX); // print the character
    Serial.print(" ");
    count++;
  }

  Wire.endTransmission(); // stop transmitting

  Serial.print("\ncount: ");
  Serial.println(count);
  Serial.print("I2C_Read done\n");
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

void xxx_loop()
{
  int nDevices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address)
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
      Serial.println("  !");

      ++nDevices;
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
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
  delay(5000); // Wait 5 seconds for next scan
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
