#ifndef SYS_H_H
#define SYS_H_H

#include "r_cg_macrodriver.h"

enum
{
    SYS_TIM = 0,
    INTERVAL,
    MAX_TIM
};
extern volatile uint32_t timecnt[MAX_TIM];
#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

void set_sys_time(void);
uint32_t get_sys_time(void);
void reset_sys_time(void);

#define IS_TIME_OUT(index, ms) ((get_sys_time() - timecnt[(index)]) > (ms) ? TRUE : FALSE)
#define CLR_TIME_OUT(index) (timecnt[index] = get_sys_time())

void test_pin(void);

#define TASK_5MS (1)
#define TASK_10MS (TASK_5MS*2)
#define TASK_100MS (TASK_5MS*20)
#define TASK_500MS (TASK_5MS*100)

typedef (*pTaskFun)(void);

struct TaskInfo
{
    pTaskFun p_task;
    uint32_t delay;
    uint32_t period;
    uint8_t runflag;
};

uint8_t sys_add_task(pTaskFun fun, uint32_t delay, uint32_t period);
void sys_del_task(uint8_t index);
void sys_run_task(void);
void sys_task_update(void);
void test_task(void);
#endif
