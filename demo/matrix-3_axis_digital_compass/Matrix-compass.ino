#include <Wire.h>

#define ADDRESS_HMC5583 0x1E

#define HMC5583_REGISTER_TOTAL 13

#define HMC5583_AXIS_XYZ 3

// #define

void setup() {
    // Initial I2C.
    Wire.begin();

    Serial.begin(115200);
    while (!Serial)
        ;  // wait for serial monitor
    Serial.print("\n\nMatrix-compass\n");

    delay(100);

    Serial.print("positive_self_test\n");
    if (positive_self_test()) {
        delay(3000);

        continuous_measurement_mode();
        // single_measurement_mode();
    } else {
        Serial.print(" --- End ---\n");
    }
}

void loop() {
}

// Below is an example of a (power-on) initialization process for “continuous-measurement mode”
void continuous_measurement_mode(void) {
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
    while (1) {
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

        delay(300);  // For human read.
    }
}

// Below is an example of a (power-on) initialization process for “single-measurement mode”
void single_measurement_mode(void) {
    // 1. Write CRA (0x00) – value 0x70 (8-average, 15 Hz default or any other rate, normal measurement)
    // 2. Write CRB (0x01) – value 0xA0 (Gain=5, or any other desired gain)
    uint8_t ary_cmd[] = {
        0x70,
        0xA0,
    };
    const int len = sizeof(ary_cmd) / sizeof(ary_cmd[0]);

    // Point to first data register CRA (0x00).
    I2C_WriteMultiBytesOneReg(ADDRESS_HMC5583, 0x00, ary_cmd, len);

    // 3. For each measurement query:
    uint8_t read_data[6] = {};
    int16_t data_X = 0;
    int16_t data_Y = 0;
    int16_t data_Z = 0;
    while (1) {
        //   Write Mode (0x02) – value 0x01 (Single-measurement mode)
        // Point to first data register CRA (0x02).
        I2C_WriteMultiBytesOneReg(ADDRESS_HMC5583, 0x02, 0x01, 1);

        //   Wait 6 ms or monitor status register or DRDY hardware interrupt pin
        delay(6);

        // Read all 6 bytes. If gain is changed then this data set is using previous gain.
        I2C_ReadMultiBytesOneReg(ADDRESS_HMC5583, 0x03, read_data, 6);

        // print
        // print_hex(read_data, 6);

        //   Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively.
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

        delay(300);  // For human read.
    }
}

// Below is an example of a “positive self test” process using continuous-measurement mode
bool positive_self_test(void) {
    // 1. Write CRA (0x00) – value 0x71 (8-average, 15 Hz default, positive self test measurement)
    // 2. Write CRB (0x01) – value 0xA0 (Gain=5)
    // 3. Write Mode (0x02) – value 0x00 (Continuous-measurement mode)
    uint8_t ary_cmd[] = {
        0x71,
        0xA0,
        0x00,
    };
    const int len = sizeof(ary_cmd) / sizeof(ary_cmd[0]);

    // Point to first data register CRA (0x00).
    I2C_WriteMultiBytesOneReg(ADDRESS_HMC5583, 0x00, ary_cmd, len);

    // 4. Wait 6 ms or monitor status register or DRDY hardware interrupt pin
    delay(6);

    // 5.  Loop
    const int avg_time = 8;
    int avg_data[HMC5583_AXIS_XYZ] = {};
    uint8_t read_data[6] = {};
    int16_t data_X = 0;
    int16_t data_Y = 0;
    int16_t data_Z = 0;
    for (int i = 0; i < avg_time; i++) {
        // Point to first data register DXRA (0x03).
        // Read all 6 bytes. If gain is changed then this data set is using previous gain.
        I2C_ReadMultiBytesOneReg(ADDRESS_HMC5583, 0x03, read_data, 6);

        // Convert three 16-bit 2’s compliment hex values to decimal values and assign to X, Z, Y, respectively.
        data_X = ((read_data[0] << 8) | read_data[1]);
        data_Z = ((read_data[2] << 8) | read_data[3]);
        data_Y = ((read_data[4] << 8) | read_data[5]);

        avg_data[0] += data_X;
        avg_data[1] += data_Y;
        avg_data[2] += data_Z;

        // Wait about 67 ms (if 15 Hz rate) or monitor status register or DRDY hardware interrupt pin.
        delay(67);
    }

    bool bPass[HMC5583_AXIS_XYZ] = {};
    bool bPass_All = true;

    const int limit_low = 243;
    const int limit_high = 575;

    // 6. Check if all 3 axes (X, Y, and Z) are within reasonable limits (243 to 575 for Gain=5, adjust these limits basing on the gain setting used. See an example below.)
    for (int i = 0; i < HMC5583_AXIS_XYZ; i++) {
        avg_data[i] /= avg_time;
        bPass[i] = IsWithinRange(abs(avg_data[i]), limit_low, limit_high);
        bPass_All &= bPass[i];

        Serial.print(avg_data[i]);
        Serial.print(", ");
        bPass[i] ? Serial.print("pass") : Serial.print("fail");
        Serial.print("\n");
    }

    if (bPass_All) {
        Serial.print("[ OK ] positive_self_test: pass.\n");
    } else {
        Serial.print("[ NG ] positive_self_test: fail.\n");
    }

    return bPass_All;
}

inline bool IsWithinRange(int val, int min, int max) {
    return ((val > min) && (val < max));
}

void print_hex(uint8_t data[], uint32_t len) {
    for (uint8_t i = 0; i < len; i++) {
        int val = data[i];
        if (val < 0x10) {
            Serial.print("0");  // print leading zeroe
        }
        Serial.print(val, HEX);  // print the character
        Serial.print(" ");
    }
    Serial.print("\n");
}

void I2C_WriteMultiBytesOneReg(uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t data[], uint32_t u32wLen) {
    Wire.beginTransmission(u8SlaveAddr);  // transmit start
    Wire.write(u8DataAddr);               // sends one byte
    Wire.write(data, u32wLen);            // sends bytes
    Wire.endTransmission();               // transmit stop
}

void I2C_ReadMultiBytesOneReg(uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t rdata[], uint32_t u32rLen) {
    int count = 0;

    Wire.beginTransmission(u8SlaveAddr);     // transmit to device #8
    Wire.write(u8DataAddr);                  // sends one byte
    Wire.requestFrom(u8SlaveAddr, u32rLen);  // request 6 bytes from slave device #8

    while (Wire.available()) {         // slave may send less than requested
        rdata[count++] = Wire.read();  // receive a byte as character
    }

    Wire.endTransmission();  // stop transmitting
}
