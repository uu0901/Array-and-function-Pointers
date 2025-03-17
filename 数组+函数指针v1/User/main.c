/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-19
 * @brief       �������� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
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
    uint8_t index;              //UI������
    void (*cb)(void);       //ui��ִ�к���
} UI_LIST;
enum
{
    E_MENU,                  //�˵�����
    E_CAT,                   //ͼƬ����
    E_PIC,                   //ͼƬ����
    E_SETTING,               //���ý���
    E_LED,                   //LED����
    E_ADVALUE,
    E_BAT,
    E_MPU6050,
    E_ABOUT,
    E_UI_MAX,                //�������ֵ
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
UI_LIST ui_list[10] = //UI��
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
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
    delay_init(72);                         /* ��ʱ��ʼ�� */
    led_init();                             /* ��ʼ��LED */
    key_init();                             /* ��ʼ������ */
    beep_init();                            /* ��ʼ�������� */
    LED0(0);                                /* �ȵ���LED0 */
    usart_init(115200);
    ui_index = E_MENU;
    while(1)
    {
        int i;
        for (i = 0 ; i < E_UI_MAX ; i++)            //E_UI_MAX=3        E_MENU=0    E_PIC=1      E_SETTING=2
        {
            if (ui_index == ui_list[i].index)       //�����ǰ��������UI���е�����
            {
                ui_list[i].cb();              //ִ�ж�Ӧ�Ļص������������밴����Ϣ��Ϊ�β�
            }
        }
    }
}
uint8_t key = 0;
void menu_proc()
{
    printf("menu_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_CAT;
                break;
        }
    }
}
void cat_proc()
{
    printf("cat_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_PIC;
                break;
        }
    }
}
void pic_proc()
{
    printf("pic_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_SETTING;
                break;
        }
    }
}
void setting_proc()
{
    printf("setting_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_LED;
                break;
        }
    }
}
void led_proc()
{
    printf("led_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_ADVALUE;
                break;
        }
    }
}
void advalue_proc()
{
    printf("advalue_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_BAT;
                break;
        }
    }
}
void bat_proc()
{
    printf("bat_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_MPU6050;
                break;
        }
    }
}
void mpu6050_proc()
{
    printf("mpu6050_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_ABOUT;
                break;
        }
    }
}
void about_proc()
{
    printf("about_proc\r\n");
    key = key_scan(0);                  /* �õ���ֵ */
    if (key)
    {
        switch (key)
        {
            case WKUP_PRES:             /* ���Ʒ����� */
                BEEP_TOGGLE();          /* BEEP״̬ȡ�� */
                break;

            case KEY2_PRES:             /* ����LED0(RED)��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                break;

            case KEY1_PRES:             /* ����LED1(GREEN)��ת */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                break;

            case KEY0_PRES:             /* ͬʱ����LED0, LED1��ת */
                LED0_TOGGLE();          /* LED0״̬ȡ�� */
                LED1_TOGGLE();          /* LED1״̬ȡ�� */
                ui_index = E_MENU;
                break;
        }
    }
}


