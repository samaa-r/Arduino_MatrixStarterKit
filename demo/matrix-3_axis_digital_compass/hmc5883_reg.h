/**************************************************************************/ /**
 * @file     hmc5883_reg.h
 * @version  V1.00
 * @brief    HMC5883 register definition header file
 *****************************************************************************/
#ifndef __HMC5883_REG_H__
#define __HMC5883_REG_H__

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

#define ADDRESS_HMC5583 0x1E

#define HMC5583_REGISTER_TOTAL 13

#define HMC5583_AXIS_XYZ 3

/**
    @addtogroup HMC5883 Controller
    Memory Mapped Structure for HMC5883 Controller
@{ */

// typedef struct
// {
/**
     * @var HMC5883::CRA
     * Offset: 0x00  Configuration Register A
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |MS        |Measurement Configuration Bits
     * |        |          |These bits define the measurement flow of the device, specifically whether or not to incorporate an applied bias into the measurement.
     * |        |          |00 = Normal measurement configuration (Default). In normal measurement configuration the device follows normal measurement flow.  The positive and negative pins of the resistive load are left floating and high impedance.
     * |        |          |01 = Positive bias configuration for X, Y, and Z axes. In this configuration, a positive current is forced across the resistive load for all three axes.
     * |        |          |10 = Negative bias configuration for X, Y and Z axes. In this configuration, a negative current is forced across the resistive load for all three axes.
     * |        |          |11 = This configuration is reserved.
     * |[4:2]   |DO        |Data Output Rate Bits (Hz)
     * |        |          |These bits set the rate at which data is written to all three data output registers.
     * |        |          |000 = 0.75
     * |        |          |001 = 1.5
     * |        |          |010 = 3
     * |        |          |011 = 7.5
     * |        |          |100 = 15 (default)
     * |        |          |101 = 30
     * |        |          |110 = 75
     * |        |          |111 = Reserved.
     * |[6:5]   |MA        |Select number of samples averaged (1 to 8) per measurement output
     * |        |          |00 = 1 (default)
     * |        |          |01 = 2
     * |        |          |10 = 4
     * |        |          |11 = 8
     * @var HMC5883::CRB
     * Offset: 0x01  Configuration Register B
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:5]   |GN        |Gain Configuration Bits
     * |        |          |These bits configure the gain for the device.  The gain configuration is common for all channels.
     * |        |          |000 = //TODO
     * |        |          |001 = 
     * |        |          |010 = 
     * |        |          |011 = 
     * |        |          |100 = 
     * |        |          |101 = 
     * |        |          |110 = 
     * |        |          |111 = 
     * @var HMC5883::MR
     * Offset: 0x02  Mode Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |MD        |Mode Select Bits
     * |        |          |These bits select the operation mode of this device.
     * |        |          |00 = Continuous-Measurement Mode.  In continuous-measurement mode, the device continuously performs measurements and places the result in the data register.  RDY goes high when new data is placed in all three registers.  After a power-on or a write to the mode or configuration register, the first measurement set is available from all three data output registers after a period of 2/fDO and subsequent measurements are available at a frequency of fDO, where fDO is the frequency of data output. 
     * |        |          |01 = Single-Measurement Mode (Default).  When single-measurement mode is selected, device performs a single measurement, sets RDY high and returned to idle mode.  Mode register returns to idle mode bit values.  The measurement remains in the data output register and RDY remains high until the data output register is read or another measurement is performed.
     * |        |          |10 = Idle Mode.  Device is placed in idle mode.
     * |        |          |11 = Idle Mode.  Device is placed in idle mode.
     * |[7]     |HS        |Set this pin to enable High Speed I2C, 3400kHz.
     * @var HMC5883::DXRA
     * Offset: 0x03  Data Output X Registers A
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DXRA      |MSB of the measurement result from channel X.
     * @var HMC5883::DXRB
     * Offset: 0x04  Data Output X Registers B
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DXRB      |LSB of the measurement result from channel X.
     * @var HMC5883::DXRA
     * Offset: 0x05  Data Output Z Registers A
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DZRA      |MSB of the measurement result from channel Z.
     * @var HMC5883::DZRB
     * Offset: 0x06  Data Output Z Registers B
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DZRB      |LSB of the measurement result from channel Z.
     * @var HMC5883::DYRA
     * Offset: 0x07  Data Output Y Registers A
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DYRA      |MSB of the measurement result from channel Y.
     * @var HMC5883::DYRB
     * Offset: 0x08  Data Output Y Registers B
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DYRB      |LSB of the measurement result from channel Y.
     * @var HMC5883::SR
     * Offset: 0x09  Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RDY       |Ready Bit
     * |        |          |Set when data is written to all six data registers. Cleared when device initiates a write to the data output registers and after one or more of the data output registers are written to.  When RDY bit is clear it shall remain cleared for a 250 μs.  DRDY pin can be used as an alternative to the status register for monitoring the device for measurement data. 
     * |[1]     |LOCK      |Data output register lock
     * |        |          |This bit is set when: 
     * |        |          |1. Some but not all for of the six data output registers have been read. 
     * |        |          |2. Mode register has been read.   
     * |        |          |When this bit is set, the six data output registers are locked and any new data will not be placed in these register until one of these conditions are met: 
     * |        |          |1. All six bytes have been read.
     * |        |          |2. The mode register is changed.
     * |        |          |3. The measurement configuration (CRA) is changed.
     * |        |          |4. Power is reset.
     * @var HMC5883::IRA
     * Offset: 0x0A  Identification Register A
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IRA       |ASCII value H 
     * @var HMC5883::IRB
     * Offset: 0x0B  Identification Register B
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IRB       |ASCII value 4 
     * @var HMC5883::IRC
     * Offset: 0x0C  Identification Register C
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |IRC       |ASCII value 3 
     */
//     __IO uint8_t CRA; /*!< [0x00] HMC5883 Configuration Register A                                   */
//     __IO uint8_t CRB; /*!< [0x01] HMC5883 Configuration Register B                                   */
//     __IO uint8_t MR;  /*!< [0x02] HMC5883 Mode Register                                              */
//     __O uint8_t DXRA; /*!< [0x03] HMC5883 Data Output X MSB Register                                 */
//     __O uint8_t DXRB; /*!< [0x04] HMC5883 Data Output X LSB Register                                 */
//     __O uint8_t DZRA; /*!< [0x05] HMC5883 Data Output Z MSB Register                                 */
//     __O uint8_t DZRB; /*!< [0x06] HMC5883 Data Output Z LSB Register                                 */
//     __O uint8_t DYRA; /*!< [0x07] HMC5883 Data Output Y MSB Register                                 */
//     __O uint8_t DYRB; /*!< [0x08] HMC5883 Data Output Y LSB Register                                 */
//     __O uint8_t SR;   /*!< [0x09] HMC5883 Status Register                                            */
//     __O uint8_t IRA;  /*!< [0x0A] HMC5883 Identification Register A                                  */
//     __O uint8_t IRB;  /*!< [0x0B] HMC5883 Identification Register B                                  */
//     __O uint8_t IRC;  /*!< [0x0C] HMC5883 Identification Register C                                  */
// } HMC5883_T;

/**
    @addtogroup HMC5883_CONST HMC5883 Bit Field Definition
    Constant Definitions for HMC5883 Controller
@{ */

#define HMC5883_ADDR_CRA  0x00 /*!< HMC5883::ADDR: CRA                     */
#define HMC5883_ADDR_CRB  0x01 /*!< HMC5883::ADDR: CRB                     */
#define HMC5883_ADDR_MR   0x02 /*!< HMC5883::ADDR: MR                      */
#define HMC5883_ADDR_DXRA 0x03 /*!< HMC5883::ADDR: DXRA                    */
#define HMC5883_ADDR_DXRB 0x04 /*!< HMC5883::ADDR: DXRB                    */
#define HMC5883_ADDR_DZRA 0x05 /*!< HMC5883::ADDR: DZRA                    */
#define HMC5883_ADDR_DZRB 0x06 /*!< HMC5883::ADDR: DZRB                    */
#define HMC5883_ADDR_DYRA 0x07 /*!< HMC5883::ADDR: DYRA                    */
#define HMC5883_ADDR_DYRB 0x08 /*!< HMC5883::ADDR: DYRB                    */
#define HMC5883_ADDR_SR   0x09 /*!< HMC5883::ADDR: SR                      */
#define HMC5883_ADDR_IRA  0x0A /*!< HMC5883::ADDR: IRA                     */
#define HMC5883_ADDR_IRB  0x0B /*!< HMC5883::ADDR: IRB                     */
#define HMC5883_ADDR_IRC  0x0C /*!< HMC5883::ADDR: IRC                     */

#define HMC5883_CRA_MS_Pos (0)                          /*!< HMC5883::CRA: MS Position              */
#define HMC5883_CRA_MS_Msk (0x03 << HMC5883_CRA_MS_Pos) /*!< HMC5883::CRA: MS Mask                  */

#define HMC5883_CRA_DO_Pos (2)                          /*!< HMC5883::CRA: DO Position              */
#define HMC5883_CRA_DO_Msk (0x07 << HMC5883_CRA_DO_Pos) /*!< HMC5883::CRA: DO Mask                  */

#define HMC5883_CRA_MA_Pos (5)                          /*!< HMC5883::CRA: MA Position              */
#define HMC5883_CRA_MA_Msk (0x03 << HMC5883_CRA_MA_Pos) /*!< HMC5883::CRA: MA Mask                  */

#define HMC5883_CRB_GN_Pos (5)                          /*!< HMC5883::CRB: GN Position              */
#define HMC5883_CRB_GN_Msk (0x07 << HMC5883_CRB_GN_Pos) /*!< HMC5883::CRB: GN Mask                  */

#define HMC5883_MR_MD_Pos (0)                         /*!< HMC5883::MR: MD Position               */
#define HMC5883_MR_MD_Msk (0x03 << HMC5883_MR_MD_Pos) /*!< HMC5883::MR: MD Mask                   */

#define HMC5883_MR_HS_Pos (7)                         /*!< HMC5883::MR: HS Position               */
#define HMC5883_MR_HS_Msk (0x01 << HMC5883_MR_HS_Pos) /*!< HMC5883::MR: HS Mask                   */

#define HMC5883_DXRA_Pos (0)                        /*!< HMC5883::DXRA: Position                */
#define HMC5883_DXRA_Msk (0xFF << HMC5883_DXRA_Pos) /*!< HMC5883::DXRA: Mask                    */

#define HMC5883_DXRB_Pos (0)                        /*!< HMC5883::DXRB: Position                */
#define HMC5883_DXRB_Msk (0xFF << HMC5883_DXRB_Pos) /*!< HMC5883::DXRB: Mask                    */

#define HMC5883_DZRA_Pos (0)                        /*!< HMC5883::DZRA: Position                */
#define HMC5883_DZRA_Msk (0xFF << HMC5883_DZRA_Pos) /*!< HMC5883::DZRA: Mask                    */

#define HMC5883_DZRB_Pos (0)                        /*!< HMC5883::DZRB: Position                */
#define HMC5883_DZRB_Msk (0xFF << HMC5883_DZRB_Pos) /*!< HMC5883::DZRB: Mask                    */

#define HMC5883_DYRA_Pos (0)                        /*!< HMC5883::DYRA: Position                */
#define HMC5883_DYRA_Msk (0xFF << HMC5883_DYRA_Pos) /*!< HMC5883::DYRA: Mask                    */

#define HMC5883_DYRB_Pos (0)                        /*!< HMC5883::DYRB: Position                */
#define HMC5883_DYRB_Msk (0xFF << HMC5883_DYRB_Pos) /*!< HMC5883::DYRB: Mask                    */

#define HMC5883_SR_RDY_Pos (0)                          /*!< HMC5883::SR: RDY Position              */
#define HMC5883_SR_RDY_Msk (0x01 << HMC5883_SR_RDY_Pos) /*!< HMC5883::SR: RDY Mask                  */

#define HMC5883_SR_LOCK_Pos (1)                           /*!< HMC5883::SR: LOCK Position             */
#define HMC5883_SR_LOCK_Msk (0x01 << HMC5883_SR_LOCK_Pos) /*!< HMC5883::SR: LOCK Mask                 */

#define HMC5883_IRA_Pos (0)                       /*!< HMC5883::IRA: Position                 */
#define HMC5883_IRA_Msk (0xFF << HMC5883_IRA_Pos) /*!< HMC5883::IRA: Mask                     */

#define HMC5883_IRB_Pos (0)                       /*!< HMC5883::IRB: Position                 */
#define HMC5883_IRB_Msk (0xFF << HMC5883_IRB_Pos) /*!< HMC5883::IRB: Mask                     */

#define HMC5883_IRC_Pos (0)                       /*!< HMC5883::IRC: Position                 */
#define HMC5883_IRC_Msk (0xFF << HMC5883_IRC_Pos) /*!< HMC5883::IRC: Mask                     */

/**@}*/ /* HMC5883_CONST */
/**@}*/ /* end of HMC5883 register group */
/**@}*/ /* end of REGISTER group */

#if defined(__CC_ARM)
#pragma no_anon_unions
#endif

#endif /* __HMC5883_REG_H__ */
