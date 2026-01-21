#include "myAPP_display.h"
#include "ltx.h"
#include "ltx_app.h"
#include "ltx_log.h"
#include "ltx_script.h"
#include "ST7305.h"
#include "myAPP_device_init.h"
#include "myAPP_system.h"

// 时间跳动偏移定时任务
struct ltx_Task_stu task_tick_dance;
void task_cb_tick_dance(void *param);
// 时间跳动需要更新显示话题
// struct ltx_Topic_stu topic_time_need_dance = _LTX_TOPIC_DEAFULT_CONFIG(topic_time_need_dance);
struct ltx_Topic_stu *topic_time_need_dance = &(task_tick_dance.timer.topic); // 不额外创建话题，直接用 task 自己的 topic

// 单帧发送完成话题
struct ltx_Topic_stu topic_draw_frame_over = _LTX_TOPIC_DEAFULT_CONFIG(topic_draw_frame_over);

// 时间显示脚本
struct ltx_Script_stu script_time_display;
void script_cb_time_display(struct ltx_Script_stu *script);

// APP 相关
int myAPP_display_init(struct ltx_App_stu *app){
    // 创建时间跳动定时器
    ltx_Task_init(&task_tick_dance, task_cb_tick_dance, 300, 0);
    ltx_Task_add_to_app(&task_cb_tick_dance, app, "tick_dance");


    // 创建时间跳动脚本
    ltx_Script_init(&script_time_display, script_cb_time_display, 0);
    
    return 0;
}

int myAPP_display_pause(struct ltx_App_stu *app){

    ltx_Script_pause(&script_time_display);

    return 0;
}

int myAPP_display_resume(struct ltx_App_stu *app){

    ltx_Script_resume(&script_time_display);

    return 0;
}

int myAPP_display_destroy(struct ltx_App_stu *app){

    ltx_Script_pause(&script_time_display);

    // free...

    return 0;
}

struct ltx_App_stu app_display = {
    .is_initialized = 0,
    .status = ltx_App_status_pause,
    .name = "display",

    .init = myAPP_display_init,
    .pause = myAPP_display_pause,
    .resume = myAPP_display_resume,
    .destroy = myAPP_display_destroy,

    .task_list = NULL,
    
    .next = NULL,
};

uint8_t dance_offset = 0;
// 时间跳动定时任务
void task_cb_tick_dance(void *param){
    // 每 300ms 自增一次偏移
    dance_offset = (dance_offset+1)%3;
    // 时间需要跳动，发布话题要求更新显示
    // ltx_Topic_publish(&topic_time_need_dance);
    // 不额外创建话题发布，直接用 task 自己的 topic
}

// 时间显示脚本
void script_cb_time_display(struct ltx_Script_stu *script){
    // if(ltx_Script_get_triger_type(script) == SC_TRIGER_RESET){ // 外部要求此脚本复位，可在此处做释放资源等操作

    //     return ;
    // }

    switch(script->step_now){
        case 0:

            break;

        default:

            break;
    }
}
