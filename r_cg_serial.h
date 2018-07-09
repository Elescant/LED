/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial.h
* Version      : CodeGenerator for RL78/F12 V2.04.01.06 [10 Nov 2017]
* Device(s)    : R5F1096C
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Serial module.
* Creation Date: 2018/7/9
***********************************************************************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Serial Clock Select Register m (SPSm)
*/
/* Section of operation clock (CKm0) (PRSm03 - PRSm00) */
#define _0000_SAU_CK00_FCLK_0                    (0x0000U) /* ck00 - fCLK */
#define _0001_SAU_CK00_FCLK_1                    (0x0001U) /* ck00 - fCLK/2^1 */
#define _0002_SAU_CK00_FCLK_2                    (0x0002U) /* ck00 - fCLK/2^2 */
#define _0003_SAU_CK00_FCLK_3                    (0x0003U) /* ck00 - fCLK/2^3 */
#define _0004_SAU_CK00_FCLK_4                    (0x0004U) /* ck00 - fCLK/2^4 */
#define _0005_SAU_CK00_FCLK_5                    (0x0005U) /* ck00 - fCLK/2^5 */
#define _0006_SAU_CK00_FCLK_6                    (0x0006U) /* ck00 - fCLK/2^6 */
#define _0007_SAU_CK00_FCLK_7                    (0x0007U) /* ck00 - fCLK/2^7 */
#define _0008_SAU_CK00_FCLK_8                    (0x0008U) /* ck00 - fCLK/2^8 */
#define _0009_SAU_CK00_FCLK_9                    (0x0009U) /* ck00 - fCLK/2^9 */
#define _000A_SAU_CK00_FCLK_10                   (0x000AU) /* ck00 - fCLK/2^10 */
#define _000B_SAU_CK00_FCLK_11                   (0x000BU) /* ck00 - fCLK/2^11 */
/* Section of operation clock (CKm1) (PRSm13 - PRSm10) */
#define _0000_SAU_CK01_FCLK_0                    (0x0000U) /* ck01 - fCLK */
#define _0010_SAU_CK01_FCLK_1                    (0x0010U) /* ck01 - fCLK/2^1 */
#define _0020_SAU_CK01_FCLK_2                    (0x0020U) /* ck01 - fCLK/2^2 */
#define _0030_SAU_CK01_FCLK_3                    (0x0030U) /* ck01 - fCLK/2^3 */
#define _0040_SAU_CK01_FCLK_4                    (0x0040U) /* ck01 - fCLK/2^4 */
#define _0050_SAU_CK01_FCLK_5                    (0x0050U) /* ck01 - fCLK/2^5 */
#define _0060_SAU_CK01_FCLK_6                    (0x0060U) /* ck01 - fCLK/2^6 */
#define _0070_SAU_CK01_FCLK_7                    (0x0070U) /* ck01 - fCLK/2^7 */
#define _0080_SAU_CK01_FCLK_8                    (0x0080U) /* ck01 - fCLK/2^8 */
#define _0090_SAU_CK01_FCLK_9                    (0x0090U) /* ck01 - fCLK/2^9 */
#define _00A0_SAU_CK01_FCLK_10                   (0x00A0U) /* ck01 - fCLK/2^10 */
#define _00B0_SAU_CK01_FCLK_11                   (0x00B0U) /* ck01 - fCLK/2^11 */

/*
    Serial Mode Register mn (SMRmn)
*/
#define _0020_SAU_SMRMN_INITIALVALUE             (0x0020U)
/* Selection of macro clock (MCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CK00              (0x0000U) /* operation clock CK0 set by PRS register */ 
#define _8000_SAU_CLOCK_SELECT_CK01              (0x8000U) /* operation clock CK1 set by PRS register */
/* Selection of transfer clock (TCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS                 (0x0000U) /* divided operation clock MCK specified by CKSmn bit */  
#define _4000_SAU_CLOCK_MODE_TI0N                (0x4000U) /* clock input from SCK pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE               (0x0000U) /* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD                    (0x0100U) /* valid edge of RXD pin */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALL                      (0x0000U) /* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING                    (0x0040U) /* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MDmn2, MDmn1) */
#define _0000_SAU_MODE_CSI                       (0x0000U) /* CSI mode */
#define _0002_SAU_MODE_UART                      (0x0002U) /* UART mode */
#define _0004_SAU_MODE_IIC                       (0x0004U) /* simplified IIC mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END                   (0x0000U) /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY                   (0x0001U) /* buffer empty interrupt */

/*
    Serial Communication Operation Setting Register mn (SCRmn)
*/
/* Setting of operation mode of channel n (TXEmn, RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION              (0x0000U) /* does not start communication */
#define _4000_SAU_RECEPTION                      (0x4000U) /* reception only */
#define _8000_SAU_TRANSMISSION                   (0x8000U) /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION         (0xC000U) /* reception and transmission */
/* Selection of data and clock phase in CSI mode (DAPmn, CKPmn) */
#define _0000_SAU_TIMING_1                       (0x0000U) /* type 1 */
#define _1000_SAU_TIMING_2                       (0x1000U) /* type 2 */
#define _2000_SAU_TIMING_3                       (0x2000U) /* type 3 */
#define _3000_SAU_TIMING_4                       (0x3000U) /* type 4 */
/* Selection of masking of error interrupt signal (EOCmn) */
#define _0000_SAU_INTSRE_MASK                    (0x0000U) /* masks error interrupt INTSREx */
#define _0400_SAU_INTSRE_ENABLE                  (0x0400U) /* enables generation of error interrupt INTSREx */
/* Setting of parity bit in UART mode (PTCmn1 - PTCmn0) */
#define _0000_SAU_PARITY_NONE                    (0x0000U) /* none parity */
#define _0100_SAU_PARITY_ZERO                    (0x0100U) /* zero parity */
#define _0200_SAU_PARITY_EVEN                    (0x0200U) /* even parity */
#define _0300_SAU_PARITY_ODD                     (0x0300U) /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB                            (0x0000U) /* MSB */
#define _0080_SAU_LSB                            (0x0080U) /* LSB */
/* Setting of stop bit in UART mode (SLCmn1, SLCmn0) */
#define _0000_SAU_STOP_NONE                      (0x0000U) /* none stop bit */
#define _0010_SAU_STOP_1                         (0x0010U) /* 1 stop bit */
#define _0020_SAU_STOP_2                         (0x0020U) /* 2 stop bits */
/* Setting of data length in CSI and UART modes (DLSmn1 - DLSmn0) (m = 0, 1) */
#define _0005_SAU_LENGTH_9                       (0x0005U) /* 9-bit data length */
#define _0006_SAU_LENGTH_7                       (0x0006U) /* 7-bit data length */
#define _0007_SAU_LENGTH_8                       (0x0007U) /* 8-bit data length */
/* Setting of data length in CSI and UART modes (DLSmn3 - DLSmn0) (m = S) */
#define _0006_SAU_LENGTH_07                      (0x0006U) /* 07-bit data length */
#define _0007_SAU_LENGTH_08                      (0x0007U) /* 08-bit data length */
#define _0008_SAU_LENGTH_09                      (0x0008U) /* 09-bit data length */
#define _0009_SAU_LENGTH_10                      (0x0009U) /* 10-bit data length */
#define _000A_SAU_LENGTH_11                      (0x000AU) /* 11-bit data length */
#define _000B_SAU_LENGTH_12                      (0x000BU) /* 12-bit data length */
#define _000C_SAU_LENGTH_13                      (0x000CU) /* 13-bit data length */
#define _000D_SAU_LENGTH_14                      (0x000DU) /* 14-bit data length */
#define _000E_SAU_LENGTH_15                      (0x000EU) /* 15-bit data length */
#define _000F_SAU_LENGTH_16                      (0x000FU) /* 16-bit data length */

/*
    Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel n in UART mode */
#define _0000_SAU_CHANNEL0_NORMAL                (0x0000U) /* normal bit level */
#define _0001_SAU_CHANNEL0_INVERTED              (0x0001U) /* inverted bit level */
#define _0000_SAU_CHANNEL2_NORMAL                (0x0000U) /* normal bit level */
#define _0004_SAU_CHANNEL2_INVERTED              (0x0004U) /* inverted bit level */

/*
    Noise Filter Enable Register 0 (NFEN0)
*/
/* Use of noise filter */
#define _00_SAU_RXD2_FILTER_OFF                  (0x00U)   /* noise filter off */
#define _10_SAU_RXD2_FILTER_ON                   (0x10U)   /* noise filter on */
#define _00_SAU_RXD1_FILTER_OFF                  (0x00U)   /* noise filter off */
#define _04_SAU_RXD1_FILTER_ON                   (0x04U)   /* noise filter on */
#define _00_SAU_RXD0_FILTER_OFF                  (0x00U)   /* noise filter off */
#define _01_SAU_RXD0_FILTER_ON                   (0x01U)   /* noise filter on */

/*
    Noise Filter Enable Register X (NFENX)
*/
/* Use of noise filter */
#define _00_SAU_RXDS0_FILTER_OFF                 (0x00U)   /* noise filter off */
#define _01_SAU_RXDS0_FILTER_ON                  (0x01U)   /* noise filter on */

/*
    Format of Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSFmn) */
#define _0040_SAU_UNDER_EXECUTE                  (0x0040U) /* communication is under execution */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0020_SAU_VALID_STORED                   (0x0020U) /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0004_SAU_FRAM_ERROR                     (0x0004U) /* a framing error occurs during UART reception */
/* Parity error detection flag of channel n (PEFmn) */
#define _0002_SAU_PARITY_ERROR                   (0x0002U) /* a parity error occurs or ACK is not detected */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0001_SAU_OVERRUN_ERROR                  (0x0001U) /* an overrun error occurs */

/*
    Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SAU_CH0_START_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON               (0x0001U) /* sets SEm0 to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SAU_CH1_START_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON               (0x0002U) /* sets SEm1 to 1 and enters the communication wait status */
/* Operation start trigger of channel 2 (SSm2) */
#define _0000_SAU_CH2_START_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_SAU_CH2_START_TRG_ON               (0x0004U) /* sets SEm2 to 1 and enters the communication wait status */
/* Operation start trigger of channel 3 (SSm3) */
#define _0000_SAU_CH3_START_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_SAU_CH3_START_TRG_ON               (0x0008U) /* sets SEm3 to 1 and enters the communication wait status */

/*
    Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON                (0x0001U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON                (0x0002U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (STm2) */
#define _0000_SAU_CH2_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0004_SAU_CH2_STOP_TRG_ON                (0x0004U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 (STm3) */
#define _0000_SAU_CH3_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0008_SAU_CH3_STOP_TRG_ON                (0x0008U) /* operation is stopped (stop trigger is generated) */

/*
    Format of Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0001_SAU_SIRMN_OVCTMN                   (0x0001U)
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0002_SAU_SIRMN_PECTMN                   (0x0002U)
/* Clear trigger of framing error of channel n (FECTMN) */
#define _0004_SAU_SIRMN_FECTMN                   (0x0004U)

/*
    Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 0 (SOEm0) */
#define _0001_SAU_CH0_OUTPUT_ENABLE              (0x0001U) /* enables output by serial communication operation */
#define _0000_SAU_CH0_OUTPUT_DISABLE             (0x0000U) /* stops output by serial communication operation */
/* Serial output enable/disable of channel 1 (SOEm1) */
#define _0002_SAU_CH1_OUTPUT_ENABLE              (0x0002U) /* enables output by serial communication operation */
#define _0000_SAU_CH1_OUTPUT_DISABLE             (0x0000U) /* stops output by serial communication operation */
/* Serial output enable/disable of channel 2 (SOEm2) */
#define _0004_SAU_CH2_OUTPUT_ENABLE              (0x0004U) /* enables output by serial communication operation */
#define _0000_SAU_CH2_OUTPUT_DISABLE             (0x0000U) /* stops output by serial communication operation */
/* Serial output enable/disable of channel 3 (SOEm3) */
#define _0008_SAU_CH3_OUTPUT_ENABLE              (0x0008U) /* enables output by serial communication operation */
#define _0000_SAU_CH3_OUTPUT_DISABLE             (0x0000U) /* stops output by serial communication operation */

/*
    Serial Output Register m (SOm)
*/
/* Serial data output of channel 0 (SOm0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0              (0x0000U) /* Serial data output value is "0" */
#define _0001_SAU_CH0_DATA_OUTPUT_1              (0x0001U) /* Serial data output value is "1" */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0              (0x0000U) /* Serial data output value is "0" */
#define _0002_SAU_CH1_DATA_OUTPUT_1              (0x0002U) /* Serial data output value is "1" */
/* Serial data output of channel 2 (SOm2) */
#define _0000_SAU_CH2_DATA_OUTPUT_0              (0x0000U) /* Serial data output value is "0" */
#define _0004_SAU_CH2_DATA_OUTPUT_1              (0x0004U) /* Serial data output value is "1" */
/* Serial data output of channel 3 (SOm3) */
#define _0000_SAU_CH3_DATA_OUTPUT_0              (0x0000U) /* Serial data output value is "0" */
#define _0008_SAU_CH3_DATA_OUTPUT_1              (0x0008U) /* Serial data output value is "1" */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0             (0x0000U) /* Serial clock output value is "0" */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1             (0x0100U) /* Serial clock output value is "1" */
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0             (0x0000U) /* Serial clock output value is "0" */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1             (0x0200U) /* Serial clock output value is "1" */
/* Serial clock output of channel 2 (CKOm2) */
#define _0000_SAU_CH2_CLOCK_OUTPUT_0             (0x0000U) /* Serial clock output value is "0" */
#define _0400_SAU_CH2_CLOCK_OUTPUT_1             (0x0400U) /* Serial clock output value is "1" */
/* Serial clock output of channel 3 (CKOm3) */
#define _0000_SAU_CH3_CLOCK_OUTPUT_0             (0x0000U) /* Serial clock output value is "0" */
#define _0800_SAU_CH3_CLOCK_OUTPUT_1             (0x0800U) /* Serial clock output value is "1" */

/*
    SAU Standby Control Register m (SSCm)
*/
/* SAU Standby Wakeup Control Bit (SWC) */
#define _0000_SAU_CH0_SNOOZE_OFF                 (0x0000U) /* disable start function from STOP state of chip */
#define _0001_SAU_CH0_SNOOZE_ON                  (0x0001U) /* enable start function from STOP state of chip */

/* SAU used flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR            (0x00U)
#define _01_SAU_IIC_SEND_FLAG                    (0x01U)
#define _02_SAU_IIC_RECEIVE_FLAG                 (0x02U)
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG          (0x04U)

/*
    UARTFn control register 0 (UFnCTL0)
*/
#define _10_UARTF_UFNCTL0_INITIALVALUE           (0x10U)
/* Transmission operation enable (UFnTXE) */
#define _00_UARTF_TRANSMISSION_DISABLE           (0x00U)   /* disable transmission operation */
#define _40_UARTF_TRANSMISSION_ENABLE            (0x40U)   /* enable transmission operation */
/* Reception operation enable (UFnRXE) */
#define _00_UARTF_RECEPTION_DISABLE              (0x00U)   /* disable reception operation */
#define _20_UARTF_RECEPTION_ENABLE               (0x20U)   /* enable reception operation */
/* Transfer direction selection (UFnDIR) */
#define _00_UARTF_TRANSFDIR_MSB                  (0x00U)   /* MSB-first transfer */
#define _10_UARTF_TRANSFDIR_LSB                  (0x10U)   /* LSB-first transfer */
/* Parity selection during transmission/reception (UFnPS1, UFnPS0) */
#define _00_UARTF_PARITY_NONE                    (0x00U)   /* no parity */
#define _04_UARTF_PARITY_ZREO                    (0x04U)   /* 0 parity */
#define _08_UARTF_PARITY_ODD                     (0x08U)   /* odd parity */
#define _0C_UARTF_PARITY_EVEN                    (0x0CU)   /* even parity */
/* Specification of data character length of 1 frame of transmit/receive data (UFnCL) */
#define _00_UARTF_DATALENGTH_7BIT                (0x00U)   /* 7 bits */
#define _02_UARTF_DATALENGTH_8BIT                (0x02U)   /* 8 bits */
/* Specification of length of stop bit for transmit data (UFnSL) */
#define _00_UARTF_STOPLENGTH_1BIT                (0x00U)   /* 1 bit */
#define _01_UARTF_STOPLENGTH_2BIT                (0x01U)   /* 2 bits */

/*
    UARTFn control register (UFnCTL1)
*/
/* Prescaler clock frequency division value (UFnPRS2 - UFnPRS0)*/
#define _0000_UARTF_BASECLK_1                    (0x0000U) /* fXX */
#define _2000_UARTF_BASECLK_2                    (0x2000U) /* fXX/2^1 */
#define _4000_UARTF_BASECLK_4                    (0x4000U) /* fXX/2^2 */
#define _6000_UARTF_BASECLK_8                    (0x6000U) /* fXX/2^3 */
#define _8000_UARTF_BASECLK_16                   (0x8000U) /* fXX/2^4 */
#define _A000_UARTF_BASECLK_32                   (0xA000U) /* fXX/2^5 */
#define _C000_UARTF_BASECLK_64                   (0xC000U) /* fXX/2^6 */
#define _E000_UARTF_BASECLK_128                  (0xE000U) /* fXX/2^7 */

/*
    UARTFn option control register 0 (UFnOPT0)
*/
#define _14_UARTF_UFNOPT0_INITIALVALUE           (0x14U)
/* Transmit data level bit (UFnTDL) */
#define _00_UARTF_TRAN_DATALEVEL_NORMAL          (0x00U)   /* normal output of transfer data */
#define _02_UARTF_TRAN_DATALEVEL_INVERTED        (0x02U)   /* inverted output of transfer data */
/* Receive data level bit (UFnRDL) */
#define _00_UARTF_REC_DATALEVEL_NORMAL           (0x00U)   /* normal input of transfer data */
#define _01_UARTF_REC_DATALEVEL_INVERTED         (0x01U)   /* inverted input of transfer data */

/*
    UARTFn option control register 1 (UFnOPT1)
*/
/* Transmit data expansion bit enable bit (UFnEBE) */
#define _00_UARTF_EXPANSIONBIT_UNUSE             (0x00U)   /* disable expansion bit */
#define _80_UARTF_EXPANSIONBIT_USE               (0x80U)   /* enable expansion bit */
/* Transmit data expansion bit detection level (UFnEBL) */
#define _00_UARTF_EXPANSIONBIT_VALUE_0           (0x00U)   /* expansion value 0 */
#define _40_UARTF_EXPANSIONBIT_VALUE_1           (0x40U)   /* expansion value 1 */
/* Transmit data expansion bit data comparsion enable bit (UFnEBC) */
#define _00_UARTF_EXPANSIONBIT_COMP_UNUSE        (0x00U)   /* disable expansion bit with comparsion */
#define _20_UARTF_EXPANSIONBIT_COMP_USE          (0x20U)   /* enable expansion bit with comparsion */
/* Communication mode (UFnMD1, UFnMD0) */
#define _00_UARTF_NORMAL_MODE                    (0x00U)   /* normal mode */

/*
    UARTFn option control register 1 (UFnSTC)
*/
/* Normal error flag clear trigger (UFnOVE, UFnFE, UFnPE) */
#define _0007_UARTF_COMMONERROE_CLEAR            (0x0007U) /* clear commom error flag bit */
/* Buffer transmission/reception completion flag clear trigger (UFnCLBUC) */
#define _0400_UARTF_BUC_CLEAR                    (0x0400U) /* clear buffer transmit/reception completion flag bit */
/* Expansion bit detection flag clear trigger (UFnCLEBD) */
#define _0100_UARTF_EBD_CLEAR                    (0x0100U) /* clear EBD flag */
/* ID match flag clear trigger (UFnCLIDM) */
#define _0200_UARTF_IDM_CLEAR                    (0x0200U) /* clear IDM flag */

/*
    UARTFn option control register 2 (UFnOPT2)
*/
/* Bit to select use of receive data noise filter (UFnRXFL) */
#define _00_UARTF_DATA_NOISE_FILTER_USED         (0x00U)   /* enables noise filter */
#define _02_UARTF_DATA_NOISE_FILTER_UNUSED       (0x02U)   /* disables noise filter */
/* Transmission interrupt (INTLTn) generation timing select bit (UFnITS) */
#define _00_UARTF_LT_INT_GENTIME_0               (0x00U)   /* output INTTn upon transmit start */
#define _01_UARTF_LT_INT_GENTIME_1               (0x01U)   /* output INTTn upon transmit completion */

/*
    UARTFn buffer control register (UFnBUCTL)
*/
/* Buffer length bits (UFnBUL3~UFnBUL0) */
#define _0001_UARTF_BUFFER_LENGTH_1              (0x0001U) /* buffer length 1 byte */
#define _0002_UARTF_BUFFER_LENGTH_2              (0x0002U) /* buffer length 2 bytes */
#define _0003_UARTF_BUFFER_LENGTH_3              (0x0003U) /* buffer length 3 bytes */
#define _0004_UARTF_BUFFER_LENGTH_4              (0x0004U) /* buffer length 4 bytes */
#define _0005_UARTF_BUFFER_LENGTH_5              (0x0005U) /* buffer length 5 bytes */
#define _0006_UARTF_BUFFER_LENGTH_6              (0x0006U) /* buffer length 6 bytes */
#define _0007_UARTF_BUFFER_LENGTH_7              (0x0007U) /* buffer length 7 bytes */
#define _0008_UARTF_BUFFER_LENGTH_8              (0x0008U) /* buffer length 8 bytes */
#define _0009_UARTF_BUFFER_LENGTH_9              (0x0009U) /* buffer length 9 bytes */
/* Buffer transmission request bit (UFnTRQ) */
#define _0000_UARTF_BUFFER_TRAN_START_NOREQUEST  (0x0000U) /* no transmission start request */
#define _0010_UARTF_BUFFER_TRAN_START_REQUEST    (0x0010U) /* transmission start request */

/* Buffer address */
#define UARTF0_BUFFER_ADDRESSS                   (0x052FU) /* UARTF0 transmit buffer address in buffer mode */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Selection of 16-bit counter output clock (UF0BRS7 - UF0BRS0) */
#define _0341_UARTF0_K_VALUE                     (0x0341U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_UARTF0_Create(void);
void R_UARTF0_Start(void);
void R_UARTF0_Stop(void);
MD_STATUS R_UARTF0_Send(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS R_UARTF0_Receive(uint8_t * const rx_buf, uint16_t rx_num);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
