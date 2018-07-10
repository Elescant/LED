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
* File Name    : r_cg_serial.c
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
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define _06_LIN_UF0MD (0x06U)
#define _01_LIN_UF0DCS (0x01U)
#define _10_LIN_UFOIPCS (0x10)
#define _08_LIN_UF0ACE (0x08)
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t  * gp_uartf0_tx_address;       /* uartf0 transmit data address */
volatile uint8_t  * gp_uartf0_tx_bf_address;    /* uartf0 transmit buffer address in buffer mode */
volatile uint16_t   g_uartf0_quotient;          /* uartf0 transmit buffer data count */
volatile uint16_t   g_uartf0_remainder;         /* uartf0 transmit buffer data remainer */
volatile uint16_t   g_uartf0_tx_cnt;            /* uartf0 transmit data number */
volatile uint8_t  * gp_uartf0_rx_address;       /* uartf0 receive data address */
volatile uint16_t   g_uartf0_rx_cnt;            /* uartf0 receive data number */
volatile uint16_t   g_uartf0_rx_len;            /* uartf0 receive data length */
/* Start user code for global. Do not edit comment generated here */
void R_UARTF0_Create(void)
{
    UF0EN = 1U;
    UF0CTL0 &= (uint8_t)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);    /* disable UARTF0 operation */
    LTMK0 = 1U;  /* disable INTLT interrupt */
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LRMK0 = 1U;  /* disable INTLR interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LSMK0 = 1U;  /* disable INTLS interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
    /* Set INTLT low priority */
    LTPR10 = 1U;
    LTPR00 = 1U;
    /* Set INTLR low priority */
    LRPR10 = 1U;
    LRPR00 = 1U;
    /* Set INTLS low priority */
    LSPR10 = 1U;
    LSPR00 = 1U;
    UF0CTL1 = _0000_UARTF_BASECLK_1 | _0341_UARTF0_K_VALUE;
    UF0OPT0 = _14_UARTF_UFNOPT0_INITIALVALUE | _00_UARTF_TRAN_DATALEVEL_NORMAL | _00_UARTF_REC_DATALEVEL_NORMAL;
    //UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _00_UARTF_NORMAL_MODE;
    UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _06_LIN_UF0MD | _01_LIN_UF0DCS | _10_LIN_UFOIPCS;
    UF0OPT1 |= _08_LIN_UF0ACE;
    UF0OPT2 = _00_UARTF_LT_INT_GENTIME_0 | _02_UARTF_DATA_NOISE_FILTER_UNUSED;
    UF0CTL0 = _10_UARTF_TRANSFDIR_LSB | _00_UARTF_PARITY_NONE | _02_UARTF_DATALENGTH_8BIT | _00_UARTF_STOPLENGTH_1BIT;
    /* Set LTXD0 pin */
    PM5 |= 0x02U;
    PMX2 = 0xFEU;
    /* Set LRXD0 pin */
    PM5 |= 0x01U;
}
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_UARTF0_Create
* Description  : This function initializes the UARTF0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
// void R_UARTF0_Create(void)
// {
//     UF0EN = 1U;
//     UF0CTL0 &= (uint8_t)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);    /* disable UARTF0 operation */
//     LTMK0 = 1U;  /* disable INTLT interrupt */
//     LTIF0 = 0U;  /* clear INTLT interrupt flag */
//     LRMK0 = 1U;  /* disable INTLR interrupt */
//     LRIF0 = 0U;  /* clear INTLR interrupt flag */
//     LSMK0 = 1U;  /* disable INTLS interrupt */
//     LSIF0 = 0U;  /* clear INTLS interrupt flag */
//     /* Set INTLT low priority */
//     LTPR10 = 1U;
//     LTPR00 = 1U;
//     /* Set INTLR low priority */
//     LRPR10 = 1U;
//     LRPR00 = 1U;
//     /* Set INTLS low priority */
//     LSPR10 = 1U;
//     LSPR00 = 1U;
//     UF0CTL1 = _0000_UARTF_BASECLK_1 | _0341_UARTF0_K_VALUE;
//     UF0OPT0 = _14_UARTF_UFNOPT0_INITIALVALUE | _00_UARTF_TRAN_DATALEVEL_NORMAL | _00_UARTF_REC_DATALEVEL_NORMAL;
//     UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _00_UARTF_NORMAL_MODE;
//     UF0OPT2 = _00_UARTF_LT_INT_GENTIME_0 | _02_UARTF_DATA_NOISE_FILTER_UNUSED;
//     UF0CTL0 = _10_UARTF_TRANSFDIR_LSB | _00_UARTF_PARITY_NONE | _02_UARTF_DATALENGTH_8BIT | _00_UARTF_STOPLENGTH_1BIT;
//     /* Set LTXD0 pin */
//     PM5 |= 0x02U;
//     PMX2 = 0xFEU;
//     /* Set LRXD0 pin */
//     PM5 |= 0x01U;
// }

/***********************************************************************************************************************
* Function Name: R_UARTF0_Start
* Description  : This function starts the UARTF0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTF0_Start(void)
{
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LTMK0 = 0U;  /* enable INTLT interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LRMK0 = 0U;  /* enable INTLR interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
    LSMK0 = 0U;  /* enable INTLS interrupt */
    UF0CTL0 |= _40_UARTF_TRANSMISSION_ENABLE | _20_UARTF_RECEPTION_ENABLE; /* enable UARTF0 operation */
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Stop
* Description  : This function stops the UARTF0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTF0_Stop(void)
{
    UF0CTL0 &= (uint8_t)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);    /* disable UARTF0 operation */
    LTMK0 = 1U;  /* disable INTLT interrupt */
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LRMK0 = 1U;  /* disable INTLR interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LSMK0 = 1U;  /* disable INTLS interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Receive
* Description  : This function receives UARTF0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UARTF0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        if ((UF0STR & 0x0040U) == 0U)
        {
            g_uartf0_rx_cnt = 0U;
            g_uartf0_rx_len = rx_num;
            gp_uartf0_rx_address = rx_buf;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Send
* Description  : This function sends UARTF0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK, MD_ARGERROR or MD_DATAEXISTS
***********************************************************************************************************************/
MD_STATUS R_UARTF0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;
    volatile uint16_t w_count;
    
    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {   
        gp_uartf0_tx_bf_address = (uint8_t*)UARTF0_BUFFER_ADDRESSS;
        gp_uartf0_tx_address = tx_buf;
        g_uartf0_tx_cnt = tx_num;
        
        if ((UF0STR & 0x0080U) == 0U)
        {
            g_uartf0_quotient = (tx_num / 9U);
            g_uartf0_remainder = (uint8_t)(tx_num % 9U);
            
            if (g_uartf0_quotient == 0U)
            {
                /* Less than 9 bytes */
                for (w_count = 0U; w_count < g_uartf0_remainder; w_count++)
                {
                    *gp_uartf0_tx_bf_address = *gp_uartf0_tx_address;
                    gp_uartf0_tx_bf_address++;
                    gp_uartf0_tx_address++;
                }
                
                UF0BUCTL = _0010_UARTF_BUFFER_TRAN_START_REQUEST | g_uartf0_remainder;
                g_uartf0_remainder = 0U;
            }
            else
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
        }
        else
        {
            status = MD_DATAEXISTS;
        }
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
void lin_config(void)
{
    UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _06_LIN_UF0MD | _01_LIN_UF0DCS | _10_LIN_UFOIPCS;
    UF0OPT1 |= _08_LIN_UF0ACE;
}
/* End user code. Do not edit comment generated here */
