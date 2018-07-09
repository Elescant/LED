#include "m_key.h"
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"

#define VAL_MANUAL_UP_TOP 650 //633 634
#define VAL_MANUAL_UP_LOW 1
#define VAL_MANUAL_DOWN_TOP 1
#define VAL_MANUAL_DOWN_LOW 600
#define VAL_AUTO_UP_TOP 500 //458 459
#define VAL_AUTO_UP_LOW 1
#define VAL_AUTO_DOWN_TOP 1
#define VAL_AUTO_DOWN_LOW 400
#define VAL_RELEASE_LOW 1000

#define MANUAL_ENSURE_TIME 100 //100ms
#define UPDATE_CIRCLE 50       //50 ms
#define MAX_VALUE (0xFFFF - UPDATE_CIRCLE)

struct Key_Info_st
{
    uint8_t pre;
    uint32_t ms;
};

struct Key_Info_st key_info[MAX_KEY];

static void update_key_state(key_types_t type);

void key_init(void)
{
    uint8_t num;
    for (num = 0; num < MAX_KEY; num++)
    {
        key_info[num].pre = KEY_UP;
        key_info[num].ms = 0;
    }
}

//每 UPDATE_CIRCLE ms 调用一次
void key_update(void)
{
    key_types_t num = KEY_FR_AUTO_UP;
    for (num = KEY_FR_AUTO_UP; num < MAX_KEY; num++)
    {
        update_key_state(num);
    }
}

void update_key_state(key_types_t type)
{
    uint16_t val=0;
    win_num_t win_num=WIN_FR;

    get_win_sample_value(win_num, &val);
    switch (win_num)
    {
    case WIN_FR:
        if (val < VAL_MANUAL_DOWN_TOP && val > VAL_MANUAL_DOWN_LOW)
        {
            if (key_info[KEY_FR_MANUAL_DOWN].pre == KEY_UP)
            {
                key_info[KEY_FR_MANUAL_DOWN].ms = 0;
                key_info[KEY_FR_MANUAL_DOWN].pre = KEY_DOWN;
            }
            else if (key_info[KEY_FR_MANUAL_DOWN].ms < MAX_VALUE)
            {
                key_info[KEY_FR_MANUAL_DOWN].ms += UPDATE_CIRCLE;
            }
        }
        else if(val > VAL_AUTO_DOWN_LOW && val < VAL_AUTO_DOWN_TOP)
        {
            if (key_info[KEY_FR_AUTO_DOWN].pre == KEY_UP)
            {
                key_info[KEY_FR_AUTO_DOWN].ms = 0;
                key_info[KEY_FR_AUTO_DOWN].pre = KEY_DOWN;
            }
            else if (key_info[KEY_FR_AUTO_DOWN].ms < MAX_VALUE)
            {
                key_info[KEY_FR_AUTO_DOWN].ms += UPDATE_CIRCLE;
            }
        }else if(val > VAL_MANUAL_UP_LOW && val < VAL_MANUAL_UP_TOP)
        {
            if (key_info[KEY_FR_MANUAL_UP].pre == KEY_UP)
            {
                key_info[KEY_FR_MANUAL_UP].ms = 0;
                key_info[KEY_FR_MANUAL_UP].pre = KEY_DOWN;
            }
            else if (key_info[KEY_FR_MANUAL_UP].ms < MAX_VALUE)
            {
                key_info[KEY_FR_MANUAL_UP].ms += UPDATE_CIRCLE;
            }
        }else if(val > VAL_AUTO_UP_LOW && val < VAL_AUTO_UP_TOP)
        {
            if (key_info[KEY_FR_AUTO_DOWN].pre == KEY_UP)
            {
                key_info[KEY_FR_AUTO_DOWN].ms = 0;
                key_info[KEY_FR_AUTO_DOWN].pre = KEY_DOWN;
            }
            else if (key_info[KEY_FR_AUTO_DOWN].ms < MAX_VALUE)
            {
                key_info[KEY_FR_AUTO_DOWN].ms += UPDATE_CIRCLE;
            }
        }else
        {
            key_info[KEY_FR_MANUAL_DOWN].ms = 0;
            key_info[KEY_FR_MANUAL_DOWN].pre = KEY_UP;
        }
        break;
    case WIN_RL:
        break;
    case WIN_RR:
        break;
    case WIN_FL:
        break;
    }
}

BOOL key_is_down(key_types_t type)
{
    if (type < MAX_KEY)
    {
        if (key_info[type].ms == 0 && key_info[type].pre == KEY_DOWN)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL key_is_up(key_types_t type)
{
    if (type < MAX_KEY)
    {
        if (key_info[type].ms == 0 && key_info[type].pre == KEY_UP)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL key_is_longer(key_types_t type, uint32_t val)
{
    if (type < MAX_KEY)
    {
        if (key_info[type].ms > val)
        {
            return TRUE;
        }
    }
    return FALSE;
}