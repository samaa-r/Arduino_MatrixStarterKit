/****************************************************************************
 * @file     hmc5883.h
 * @version  V1.00
 * @brief    HMC5883 driver source file
 *****************************************************************************/
#ifndef __HMC5883_H__
#define __HMC5883_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HMC5883_Driver HMC5883 Driver
  @{
*/

/** @addtogroup HMC5883_EXPORTED_CONSTANTS HMC5883 Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 CRA MA number of samples averaged (1 to 8) per measurement output                               */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_CRA_MA_1_AVG (0x00 << HMC5883_CRA_MA_Pos)
#define HMC5883_CRA_MA_2_AVG (0x01 << HMC5883_CRA_MA_Pos)
#define HMC5883_CRA_MA_4_AVG (0x02 << HMC5883_CRA_MA_Pos)
#define HMC5883_CRA_MA_8_AVG (0x03 << HMC5883_CRA_MA_Pos)

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 CRA DO Data Output Rate                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_CRA_DO_0_75_HZ (0x00 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_1_5_HZ  (0x01 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_3_HZ    (0x02 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_7_5_HZ  (0x03 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_15_HZ   (0x04 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_30_HZ   (0x05 << HMC5883_CRA_DO_Pos)
#define HMC5883_CRA_DO_75_HZ   (0x06 << HMC5883_CRA_DO_Pos)

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 CRA MS Measurement Configuration                                                                */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_CRA_MS_NORMAL   (0x00 << HMC5883_CRA_MS_Pos)
#define HMC5883_CRA_MS_POSITIVE (0x01 << HMC5883_CRA_MS_Pos)
#define HMC5883_CRA_MS_NEGATIVE (0x02 << HMC5883_CRA_MS_Pos)

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 CRB GN Gain Configuration                                                                       */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_CRB_GN_1370 (0x00 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_1090 (0x01 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_820  (0x02 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_660  (0x03 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_440  (0x04 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_390  (0x05 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_330  (0x06 << HMC5883_CRB_GN_Pos)
#define HMC5883_CRB_GN_230  (0x07 << HMC5883_CRB_GN_Pos)

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 MR HS enable High Speed I2C, 3400kHz                                                            */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_MR_HS_DISABLE (0x00 << HMC5883_MR_HS_Pos)
#define HMC5883_MR_HS_ENABLE  (0x01 << HMC5883_MR_HS_Pos)

/*---------------------------------------------------------------------------------------------------------*/
/* HMC5883 MR MD elect the operation mode of this device                                                   */
/*---------------------------------------------------------------------------------------------------------*/

#define HMC5883_MR_MD_CONTINUOUS_MEASUREMENT_MODE (0x00 << HMC5883_MR_MD_Pos)
#define HMC5883_MR_MD_SINGLE_MEASUREMENT_MODE     (0x01 << HMC5883_MR_MD_Pos)

/*@}*/ /* end of group HMC5883_EXPORTED_CONSTANTS */

/** @addtogroup HMC5883_EXPORTED_FUNCTIONS HMC5883 Exported Functions
  @{
*/

//TODO function

/*@}*/ /* end of group HMC5883_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HMC5883_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /*__HMC5883_H__*/
