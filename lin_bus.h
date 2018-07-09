#ifndef LIN_BUS_H_H
#define LIN_BUS_H_H

#include "r_cg_macrodriver.h"
#include "sys.h"

#define SYNC_BYTE 0x55

void slave_rec_byte_cb(uint8_t byte);

#endif
