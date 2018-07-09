#include "lin_driver.h"
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"

uint8_t testdata[8] = {1, 2, 3, 4, 5, 6, 7, 8};
uint8_t test_rxdata[8] = {0};

static void clr_buf(void);
static void lin_slave_noresponse(void);
static uint8_t get_rxdata(uint8_t *buf);
static void lin_slave_receive(uint16_t len);
static void lin_slave_transmit(uint8_t *txdata, uint16_t len);

void lin_send_test(void)
{
    lin_slave_transmit(testdata, 8);
}

void rec_hanlde(void)
{
    uint16_t headfg;
    uint16_t buffg;
    uint8_t pid;

    headfg = UF0STR & 0x0800;
    buffg = UF0STR & 0x0400;

    if (headfg != 0)
    {
        UF0STR |= 0x0800;
        pid = UF0ID;
        switch (pid)
        {
        case 0x08:
            lin_slave_receive(8);
            break;
        case 0xC1:
            lin_slave_transmit(testdata, 8);
            break;
        default:
            break;
        }
    }
    if (buffg != 0)
    {
        pid = UF0ID;
        switch (pid)
        {
        case 0x08:
            get_rxdata(test_rxdata);
            break;
        default:
            lin_slave_noresponse();
            break;
        }
        UF0STC |= 0x0400; //clr buf recv/transmit complete flag
    }
}

void lin_slave_receive(uint16_t len)
{
    clr_buf();
    UF0BUCTL = 0x00A0; //UF0ECS=1:Enhanced checksum;UF0RRQ=1:Reception start
    UF0BUCTL |= len;
}

uint8_t get_rxdata(uint8_t *buf)
{
    uint16_t i, num;
    uint16_t data_addr;

    num = UF0BUCTL & 0x000F;
    for (i = 0; i < num; i++)
    {
        buf[i] = (*((uint8_t *)(UF0BUF0 + i)));
    }
    return buf[2];
}

void lin_slave_transmit(uint8_t *txdata, uint16_t len)
{
    uint16_t i;
    uint16_t data_addr;
    data_addr = UF0BUF0;
    for (i = 0; i < len; i++)
    {
        *((uint8_t *)data_addr + i) = txdata[i];
    }
    UF0BUCTL = 0x0290; //UF0TW=1,UF0ECS=1,Enhanced checksum UF0TRQ=1:start
    UF0BUCTL |= len;
    UF0BUCTL |= _0010_UARTF_BUFFER_TRAN_START_REQUEST;
}

void lin_slave_noresponse(void)
{
    UF0BUCTL |= 0x00C0; //UF0NO No Response
}

void clr_buf(void)
{
    uint8_t i;
    for (i = 0; i < 9; i++)
    {
       *((uint8_t *)(UF0BUF0 + i)) = 0U;
    }
}