#ifndef __LTX_ARCH_ARM_CORTEX_M_H__
#define __LTX_ARCH_ARM_CORTEX_M_H__

#define _LTX_ARCH_SELECTED

#include "ltx_config.h"

// 开关中断宏
#define _LTX_IRQ_ENABLE()                       __enable_irq()
#define _LTX_IRQ_DISABLE()                      __disable_irq()

// 开启空闲任务的话
#ifdef ltx_cfg_USE_IDLE_TASK
    // 设置为置位 PendSV 标志位，触发其运行
    #define _LTX_SET_SCHEDULE_FLAG()            (SCB->ICSR = SCB_ICSR_PENDSVSET_Msk)
    // 设置为读 PendSV 标志位
    #define _LTX_GET_SCHEDULE_FLAG              (SCB->ICSR & SCB_ICSR_PENDSVSET_Msk)
    // 设置为清除 PendSV 标志位
    #define _LTX_CLEAR_SCHEDULE_FLAG()          (SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk)
#endif

// 开启 tickless 的话（使用 TIM1 替代 SysTick）
#ifdef ltx_cfg_USE_TICKLESS
    // 暂停 TIM1（停止计数）并禁用更新中断，清除 NVIC pending，减少竞态窗口
    #define _ltx_Sys_systick_pause()            do{ TIM1->CR1 &= ~TIM_CR1_CEN; TIM1->DIER &= ~TIM_DIER_UIE; NVIC_ClearPendingIRQ(TIM1_BRK_UP_TRG_COM_IRQn); }while(0)
    // 恢复 TIM1（启动计数）并启用更新中断
    #define _ltx_Sys_systick_resume()           do{ TIM1->DIER |= TIM_DIER_UIE; TIM1->CR1 |= TIM_CR1_CEN; }while(0)
    // 设置 TIM1 重载值（ARR）
    #define _ltx_Sys_systick_set_reload(reload) (TIM1->ARR = (uint32_t)(reload))
    // #define _ltx_Sys_systick_set_reload(reload) do{_HAL_TIM_SET_AUTORELOAD(&htim1_handler, (uint32_t)(reload));}while(0)
    // 获取 TIM1 重载值
    #define _ltx_Sys_systick_get_reload()       (TIM1->ARR)
    // 清除 TIM1 计数值为 重载值并更新
    #define _ltx_Sys_systick_clr_val()          do{TIM1->CNT = TIM1->ARR; TIM1->EGR = TIM_EGR_UG;}while(0)
    // 获取 TIM1 计数值
    #define _ltx_Sys_systick_get_val()          (TIM1->CNT)
    // 获取 TIM1 更新中断标志位（UIF）用于判断是否发生过一次更新
    #define _ltx_Sys_systick_get_flag()         (TIM1->SR & TIM_SR_UIF)
    // #define _ltx_Sys_systick_get_flag()         (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE))
    // 清除 TIM1 中断标志位：写 0 清除所有中断标志
    #define _ltx_Sys_systick_clr_flag()         (TIM1->SR = 0U)


    // 告知调度器 TIM1 的计数频率（将 TIM1 预分频为 800）
    #define _SYSTICK_FREQ                       10000U
    
    // TIM1 的 ARR 寄存器为 16 位
    #define _SYSTICK_MAX_RELOAD                 0xFFFFU
    // TIM1 一个 tick 的计数值（以 1ms 为一个 tick）
    #define _SYSTICK_COUNT_PER_TICK             (_SYSTICK_FREQ/1000U)
    // TIM1 最大 tick 计数值，预留一个，避免溢出
    #define _SYSTICK_MAX_TICK                   (_SYSTICK_MAX_RELOAD/_SYSTICK_COUNT_PER_TICK - 1U)
#endif

#endif // __LTX_ARCH_ARM_CORTEX_M_H__
