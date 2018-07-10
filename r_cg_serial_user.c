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
* File Name    : r_cg_serial_user.c
* Version      : CodeGenerator for RL78/F12 V2.04.01.06 [10 Nov 2017]
* Device(s)    : R5F1096C
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Serial module.
* Creation Date: 2018/7/9
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
#include "lin_bus.h"
#include "lin_driver.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_uartf0_interrupt_receive(vect=INTLR)
#pragma interrupt r_uartf0_interrupt_send(vect=INTLT)
#pragma interrupt r_uartf0_interrupt_error(vect=INTLS)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t  * gp_uartf0_tx_address;    /* uartf0 transmit buffer address */
extern volatile uint8_t  * gp_uartf0_tx_bf_address; /* uartf0 transmit buffer address in buffer mode */
extern volatile uint16_t   g_uartf0_quotient;       /* uartf0 transmit buffer data count */
extern volatile uint16_t   g_uartf0_remainder;      /* uartf0 transmit buffer data remainer */
extern volatile uint16_t   g_uartf0_tx_cnt;         /* uartf0 transmit data number */
extern volatile uint8_t  * gp_uartf0_rx_address;    /* uartf0 receive data address */
extern volatile uint16_t   g_uartf0_rx_cnt;         /* uartf0 receive data number */
extern volatile uint16_t   g_uartf0_rx_len;         /* uartf0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_uartf0_interrupt_receive
* Description  : This function is INTLR interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
/*
static void __near r_uartf0_interrupt_receive(void)
{
    volatile uint8_t rx_data_8;
    
    rx_data_8 = UF0RXB;
    
    if (g_uartf0_rx_len > g_uartf0_rx_cnt)
    {
        *gp_uartf0_rx_address = rx_data_8;
        gp_uartf0_rx_address++;
        g_uartf0_rx_cnt++;
    }
}
*/
/***********************************************************************************************************************
* Function Name: r_uartf0_interrupt_send
* Description  : This function is INTLT interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uartf0_interrupt_send(void)
{
    volatile uint16_t w_count;
    
    UF0STC |= _0400_UARTF_BUC_CLEAR;
    gp_uartf0_tx_bf_address = (uint8_t*)UARTF0_BUFFER_ADDRESSS;
    
    if (g_uartf0_quotient > 0U)
    {
        for (w_count = 0U; w_count < 9U; w_count++)
        {
            *gp_uartf0_tx_bf_address = *gp_uartf0_tx_address;
            gp_uartf0_tx_bf_address++;
            gp_uartf0_tx_address++;
        }
        
        g_uartf0_quotient--;
        UF0BUCTL = _0010_UARTF_BUFFER_TRAN_START_REQUEST | 9U;
    }
    else
    {
        if (g_uartf0_remainder != 0U)
        {
            for (w_count = 0U; w_count < g_uartf0_remainder; w_count++)
            {
                *gp_uartf0_tx_bf_address = *gp_uartf0_tx_address;
                gp_uartf0_tx_bf_address++;
                gp_uartf0_tx_address++;
            }
            
            UF0BUCTL = _0010_UARTF_BUFFER_TRAN_START_REQUEST | g_uartf0_remainder;
            g_uartf0_remainder = 0U;
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_uartf0_interrupt_error
* Description  : This function is INTLS interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uartf0_interrupt_error(void)
{
    volatile uint8_t  err_type;

    *gp_uartf0_rx_address = UF0RXB;
    err_type = (uint8_t)(UF0STR & 0x07U);
    UF0STC |= _0007_UARTF_COMMONERROE_CLEAR;
}

/* Start user code for adding. Do not edit comment generated here */
static void __near r_uartf0_interrupt_receive(void)
{
    volatile uint8_t rx_data_8;
    
    rx_data_8 = UF0RXB;
    rec_hanlde();
}
/* End user code. Do not edit comment generated here */
