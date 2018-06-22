#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include "sys.h"

volatile uint32_t timecnt[MAX_TIM] = {
    0,
};

#define MAX_TASKS 10
struct TaskInfo task_data[MAX_TASKS] = {
    {0, 0, 0, 0},
};

void set_sys_time(void)
{
    timecnt[SYS_TIM]++;
}

void reset_sys_time(void)
{
    timecnt[SYS_TIM] = 0;
}

uint32_t get_sys_time(void)
{
    return timecnt[SYS_TIM];
}

void test_pin(void)
{
    P1_bit.no0 = !P1_bit.no0;
}

uint8_t sys_add_task(pTaskFun fun, uint32_t delay, uint32_t period)
{
    uint8_t index = 0;
    while ((task_data[index].p_task != 0) && (index < MAX_TASKS))
    {
        index++;
    }
    if (MAX_TASKS == index)
    {
        return MAX_TASKS;
    }
    task_data[index].p_task = fun;
    task_data[index].delay = delay;
    task_data[index].period = period;
    task_data[index].runflag = 0;
}

void sys_del_task(uint8_t index)
{
    if(index<MAX_TASKS)
    {
        task_data[index].p_task = 0;
        task_data[index].delay = 0;
        task_data[index].period = 0;
        task_data[index].runflag = 0;
    }
}

void sys_run_task(void)
{
    uint8_t index = 0;
    
    for(index=0;index<MAX_TASKS;index++)
    {
        if(task_data[index].runflag>0 && task_data[index].p_task!=0)
        {
            (task_data[index].p_task)();
            task_data[index].runflag -=1;
            if(0==task_data[index].period)
            {
                sys_del_task(index);
            }
        }
    }
}

void sys_task_update(void)
{
    uint8_t index=0;

    for(index=0;index<MAX_TASKS;index++)
    {
        if(task_data[index].p_task!=0)
        {
            task_data[index].delay--;
            if(task_data[index].delay == 0)
            {
                task_data[index].runflag +=1;
                if(task_data[index].period)
                {
                    task_data[index].delay = task_data[index].period;
                }
            }
        }
    }
}


void test_task(void)
{
    P1_bit.no0 = !P1_bit.no0;
}