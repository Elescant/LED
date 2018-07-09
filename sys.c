#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include "sys.h"

const uint32_t MAX_TICK_VALUE = 0xFFFFFFFF;

volatile uint32_t timecnt[MAX_TIM] = {
    0,
};

#define MAX_TASKS 10
struct TaskInfo task_data[MAX_TASKS] = {
    {0, 0, 0, 0},
};

void inc_sys_time(void)
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
    while ((index < MAX_TASKS) && (task_data[index].p_task != 0))
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
    return index;
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

BOOL is_time_out(uint8_t index,uint32_t value)
{
    uint32_t cnt_shade,sys_shade;//防止比较前，其他程序再次修改
    if(index >= MAX_TIM)
    {
        return FALSE;
    }
    cnt_shade = timecnt[index];
    sys_shade = get_sys_time();
    if(sys_shade > cnt_shade)
    {
        if(sys_shade-cnt_shade > value)
         return TRUE;
    }else
    {
       if(MAX_TICK_VALUE - cnt_shade + sys_shade > value)
       {
           return TRUE;
       }
    }
    return FALSE;
}

void clr_time_out(uint8_t index)
{
    if(index >= MAX_TIM)
        return;
    timecnt[index] = get_sys_time();
}

uint32_t get_interval_ms(uint32_t value)
{
    uint32_t sys_shade;
    sys_shade = get_sys_time();
    if(sys_shade > value)
    {
        return sys_shade - value;
    }else
    {
        return (MAX_TICK_VALUE - value) + sys_shade;
    }
}