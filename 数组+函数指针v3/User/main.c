/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-19
 * @brief       按键输入 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
/* 新增头文件 */
#include <string.h>  // 添加字符串操作支持
typedef struct
{
    const char* name;       // 使用字符串作为UI标识符
    void (*cb)(void);       //ui的执行函数
} UI_LIST;

UI_LIST ui_list[10] = {0};
/* 修改add函数，参数改为字符串 */
void add(const char* name, void (*cb)(void))//默认会将你添加的字符串，也就是形参1，默认对齐到ui_list[i] 也就是会按顺序1234567~50添加对应的字符串（索引）和函数指针            ui_list[i].name = name;ui_list[i].cb = cb;
{
    for (int i = 0; i < sizeof(ui_list)/sizeof(ui_list[0]); i++)
    {
        if (ui_list[i].name == NULL)  // 找到第一个空位
        {
            ui_list[i].name = name;
            ui_list[i].cb = cb;
            break;
        }
    }
}

/* 修改全局变量为字符串指针 */
const char* ui_index = "menu";  // 初始界面设置为菜单

void menu_proc(void);
void cat_proc(void);
void pic_proc(void);
void setting_proc(void);
void led_proc(void);
void advalue_proc(void);
void bat_proc(void);
void mpu6050_proc(void);
void about_proc(void);
int main(void)
{
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟, 72Mhz */
    delay_init(72);                         /* 延时初始化 */
    led_init();                             /* 初始化LED */
    key_init();                             /* 初始化按键 */
    beep_init();                            /* 初始化蜂鸣器 */
    LED0(0);                                /* 先点亮LED0 */
    usart_init(115200);

    /* 手动注册UI界面（直观的字符串标识） */
    add("menu",    menu_proc);
    add("cat",     cat_proc);
    add("pic",     pic_proc);
    add("setting", setting_proc);
    add("led",     led_proc);  // 使用有意义的字符串代替数字4;
    add("advalue", advalue_proc); 
    add("bat",     bat_proc); 
    add("mpu6050", mpu6050_proc); 
    add("about",   about_proc); 
    printf("sizeof(ui_list) = %d\r\n", sizeof(ui_list));
    printf("sizeof(ui_list[0]) = %d\r\n", sizeof(ui_list[0]));
    printf("sizeof(ui_list)/sizeof(ui_list[0]) = %d\r\n", (sizeof(ui_list)/sizeof(ui_list[0]))); 
    while(1)
    {
        for (int i = 0; i < sizeof(ui_list)/sizeof(ui_list[0]); i++)
        {
            if (ui_list[i].name != NULL &&  strcmp(ui_index, ui_list[i].name) == 0)  // 字符串比对
            {
                if (ui_list[i].cb)
                {
                    ui_list[i].cb();
                }
                break;  // 找到后退出循环提高效率
            }
        }
    }
}
uint8_t key = 0;
void menu_proc()
{
    printf("menu_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "cat";
                break;
        }
    }
}
void cat_proc()
{
    printf("cat_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "pic";
                break;
        }
    }
}
void pic_proc()
{
    printf("pic_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "setting";
                break;
        }
    }
}
void setting_proc()
{
    printf("setting_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "led";
                break;
        }
    }
}
void led_proc()
{
    printf("led_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "advalue";
                break;
        }
    }
}
void advalue_proc()
{
    printf("advalue_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "bat";
                break;
        }
    }
}
void bat_proc()
{
    printf("bat_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "mpu6050";
                break;
        }
    }
}
void mpu6050_proc()
{
    printf("mpu6050_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "about";
                break;
        }
    }
}
void about_proc()
{
    printf("about_proc\r\n");
    key = key_scan(0);                  /* 得到键值 */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* 控制蜂鸣器 */
                BEEP_TOGGLE();          /* BEEP状态取反 */
                break;

            case KEY2_PRES:             /* 控制LED0(RED)翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                break;

            case KEY1_PRES:             /* 控制LED1(GREEN)翻转 */
                LED1_TOGGLE();          /* LED1状态取反 */
                break;

            case KEY0_PRES:             /* 同时控制LED0, LED1翻转 */
                LED0_TOGGLE();          /* LED0状态取反 */
                LED1_TOGGLE();          /* LED1状态取反 */
                ui_index = "menu";
                break;
        }
    }
}


