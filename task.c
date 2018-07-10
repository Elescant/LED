#include "task.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "lin_driver.h"

uint8_t test_data[8]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};

void test_task(void)
{
   P1_bit.no0 = !P1_bit.no0;
   //R_UARTF0_Send(test_data,8);
   //lin_send_test();
}

