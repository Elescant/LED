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

typedef uint8_t BOOL ;

void inc_sys_time(void);
uint32_t get_sys_time(void);
void reset_sys_time(void);
void clr_time_out(uint8_t index);
BOOL is_time_out(uint8_t index,uint32_t value);
uint32_t get_interval_ms(uint32_t value);

//NOTE:�˴�IS_TIME_OUT(index, ms)��һ���������
//1.�����Ȼ�ȡget_sys_time()��ֵ
//2.�����жϣ��ж��е���CLR_TIME_OUT(index),��ʱ��get_sys_time()ֵ����1�е�ֵ
//3.��ɵĽ����timecnt[index] > get_sys_time()
//#define IS_TIME_OUT(index, ms) ((get_sys_time() - timecnt[(index)]) > (ms) ? TRUE : FALSE)
//#define CLR_TIME_OUT(index) (timecnt[index] = get_sys_time())

void test_pin(void);

#define TASK_5MS (1)
#define TASK_10MS (TASK_5MS*2)
#define TASK_20MS (TASK_5MS*4)
#define TASK_100MS (TASK_5MS*20)
#define TASK_500MS (TASK_5MS*100)

typedef void (*pTaskFun)(void);

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
#endif
