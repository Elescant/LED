#ifndef M_KEY_H_H
#define M_KEY_H_H

#include "sys.h"

typedef enum
{
    KEY_FR_AUTO_UP,
    KEY_FR_AUTO_DOWN,
    KEY_FR_MANUAL_UP,
    KEY_FR_MANUAL_DOWN,
    KEY_RL_AUTO_UP,
    KEY_RL_AUTO_DOWN,
    KEY_RL_MANUAL_UP,
    KEY_RL_MANUAL_DOWN,
    KEY_RR_AUTO_UP,
    KEY_RR_AUTO_DOWN,
    KEY_RR_MANUAL_UP,
    KEY_RR_MANUAL_DOWN,
    KEY_FL_AUTO_UP,
    KEY_FL_AUTO_DOWN,
    KEY_FL_MANUAL_UP,
    KEY_FL_MANUAL_DOWN,
    MAX_KEY,
}key_types_t;

#define KEY_DOWN 1
#define KEY_UP 0

void key_update(void);
BOOL key_is_down(key_types_t type);
BOOL key_is_up(key_types_t type);
BOOL key_is_longer(key_types_t type,uint32_t val);
#endif
