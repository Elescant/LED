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
* File Name    : r_cg_adc_user.c
* Version      : CodeGenerator for RL78/F12 V2.04.01.06 [10 Nov 2017]
* Device(s)    : R5F1096C
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 2018/7/9
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"
/* Start user code for include. Do not edit comment generated here */
#include "sys.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_adc_interrupt(vect=INTAD)
/* Start user code for pragma. Do not edit comment generated here */
void adc_vol_sample(void);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
static BOOL filter(uint16_t *buf, uint16_t *val);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_adc_interrupt
* Description  : This function is INTAD interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_adc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    adc_vol_sample();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
#define ADC_BUF_SIZE 10
#define ADC_THRESHOLD 100

static uint16_t adc_value[WIN_MAX] = {0,};

static uint16_t adc0_data[ADC_BUF_SIZE] = {
    0,
};
static uint16_t adc1_data[ADC_BUF_SIZE] = {
    0,
};
static uint16_t adc2_data[ADC_BUF_SIZE] = {
    0,
};
static uint16_t adc16_data[ADC_BUF_SIZE] = {
    0,
};

void adc_vol_sample(void)
{
    static ad_channel_t channel = ADCHANNEL0;
    static uint8_t ad_data_index = 0;
    uint16_t *buf_indictor;

    switch (channel)
    {
    case ADCHANNEL0:
        channel = ADCHANNEL1;
        buf_indictor = adc0_data;
        R_ADC_Get_Result(&(buf_indictor[ad_data_index]));
        if (ad_data_index + 1 == ADC_BUF_SIZE)
        {
            filter(buf_indictor, &adc_value[WIN_FR]);
        }
        ADS = _01_AD_INPUT_CHANNEL_1;
        break;
    case ADCHANNEL1:
        channel = ADCHANNEL2;
        buf_indictor = adc1_data;
        R_ADC_Get_Result(&(buf_indictor[ad_data_index]));
        if (ad_data_index + 1 == ADC_BUF_SIZE)
        {
            filter(buf_indictor, &adc_value[WIN_RL]);
        }
        ADS = _02_AD_INPUT_CHANNEL_2;
        break;
    case ADCHANNEL2:
        channel = ADCHANNEL16;
        buf_indictor = adc2_data;
        R_ADC_Get_Result(&(buf_indictor[ad_data_index]));
        if (ad_data_index + 1 == ADC_BUF_SIZE)
        {
            filter(buf_indictor, &adc_value[WIN_RR]);
        }
        ADS = _10_AD_INPUT_CHANNEL_16;
        break;
    case ADCHANNEL16:
        channel = ADCHANNEL0;
        buf_indictor = adc16_data;
        R_ADC_Get_Result(&(buf_indictor[ad_data_index]));
        if (ad_data_index + 1 == ADC_BUF_SIZE)
        {
            filter(buf_indictor, &adc_value[WIN_FL]);
        }
        ad_data_index++;
        if (ad_data_index == ADC_BUF_SIZE)
        {
            ad_data_index = 0;
        }
        ADS = _00_AD_INPUT_CHANNEL_0;
        break;
    default:
        break;
    }
    ADIF = 0U; //Clean AD INT Flag
}

BOOL filter(uint16_t *buf, uint16_t *val)
{
    uint16_t i, sum = 0;
    uint16_t max, min;
    max = buf[0];
    min = buf[0];
    for (i = 0; i < ADC_BUF_SIZE; i++)
    {
        sum += buf[i];
        if (buf[i] > max)
        {
            max = buf[i];
        }
        if (buf[i] < min)
        {
            min = buf[i];
        }
    }
    if (max - min > ADC_THRESHOLD)
    {
        NOP();
        return FALSE;
    }
    sum = sum - max - min;
    *val = sum / (ADC_BUF_SIZE - 2);
    return TRUE;
}

BOOL get_win_sample_value(win_num_t num,uint16_t *val)
{
    if(num<WIN_MAX)
    {
        *val = adc_value[num];
        return TRUE;
    }
    return FALSE;
}
/* End user code. Do not edit comment generated here */
