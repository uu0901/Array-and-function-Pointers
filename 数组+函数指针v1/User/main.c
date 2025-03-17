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

typedef struct
{
    uint8_t index;              //UI的索引
    void (*cb)(void);       //ui的执行函数
} UI_LIST;
enum
{
    E_MENU,                  //菜单界面
    E_CAT,                   //图片界面
    E_PIC,                   //图片界面
    E_SETTING,               //设置界面
    E_LED,                   //LED界面
    E_ADVALUE,
    E_BAT,
    E_MPU6050,
    E_ABOUT,
    E_UI_MAX,                //界面最大值
} E_UI;
void menu_proc(void);
void cat_proc(void);
void pic_proc(void);
void setting_proc(void);
void led_proc(void);
void advalue_proc(void);
void bat_proc(void);
void mpu6050_proc(void);
void about_proc(void);
UI_LIST ui_list[10] = //UI表
{
    {E_MENU,    menu_proc},
    {E_CAT,     cat_proc  },
    {E_PIC,     pic_proc  },
    {E_SETTING, setting_proc},
    {E_LED,     led_proc},
    {E_ADVALUE, advalue_proc},
    {E_BAT,     bat_proc},
    {E_MPU6050, mpu6050_proc},
    {E_ABOUT,   about_proc},
};
// void add(uint8_t index, void (*cb)(void) )
// {
//     ui_list[index].index = index;
//     ui_list[index].cb = cb;
// }
uint8_t ui_index;
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
    ui_index = E_MENU;
    while(1)
    {
        int i;
        for (i = 0 ; i < E_UI_MAX ; i++)            //E_UI_MAX=3        E_MENU=0    E_PIC=1      E_SETTING=2
        {
            if (ui_index == ui_list[i].index)       //如果当前索引等于UI表中的索引
            {
                ui_list[i].cb();              //执行对应的回调函数，并传入按键信息作为形参
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
                ui_index = E_CAT;
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
                ui_index = E_PIC;
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
                ui_index = E_SETTING;
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
                ui_index = E_LED;
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
                ui_index = E_ADVALUE;
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
                ui_index = E_BAT;
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
                ui_index = E_MPU6050;
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
                ui_index = E_ABOUT;
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
                ui_index = E_MENU;
                break;
        }
    }
}


