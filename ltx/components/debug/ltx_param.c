#include "ltx_param.h"
#include "ltx_app.h"
#include "myAPP_system.h"
#include "myAPP_display.h"
#include "ltx_log.h"

// 心拍频率
uint16_t heart_beat_Hz = 1;
void param_read_heart_beat(struct param_stu *param){
    LTX_LOG_INFO("Heart beat: %d Hz\n", heart_beat_Hz);
}
void param_write_heart_beat(struct param_stu *param, const char *new_val){
    uint16_t new_Hz;

    sscanf(new_val, "%hd", &new_Hz);

    if(new_Hz > 1000 || new_Hz < 1){
        LTX_LOG_WARN("New value(%d) not in range(1~1000)!\n", new_Hz);
        return ;
    }

    heart_beat_Hz = new_Hz;
    
    task_heart_beat.timer.tick_reload = 1000/heart_beat_Hz;
    task_heart_beat.timer.tick_counts = 1000/heart_beat_Hz;

    LTX_LOG_INFO("Set heart beat to %d Hz\n", heart_beat_Hz);
}

void param_read_tick_dance_period(struct param_stu *param){
    LTX_LOG_INFO("tick dance period: %d ms\n", task_tick_dance.timer.tick_reload);
}

void param_write_tick_dance_period(struct param_stu *param, const char *new_val){

    uint32_t new_period;

    sscanf(new_val, "%d", &new_period);
    task_tick_dance.timer.tick_reload = new_period;
    task_tick_dance.timer.tick_counts = new_period;

    LTX_LOG_INFO("Set tick dance period to %d ms\n", task_tick_dance.timer.tick_reload);
}

struct param_stu param_list[] = {
    { // 心拍任务频率
        .param_name = "heart_beat_Hz",
        .param_read = param_read_heart_beat,
        .param_write = param_write_heart_beat,
    },

    { // 时间跳动周期
        .param_name = "tick_dance_period",
        .param_read = param_read_tick_dance_period,
        .param_write = param_write_tick_dance_period,
    },

    // 末尾项
    {
        .param_name = " ",
    },
};
