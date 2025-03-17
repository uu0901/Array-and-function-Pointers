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
/* ����ͷ�ļ� */
#include <string.h>  // ����ַ�������֧��
typedef struct
{
    const char* name;       // ʹ���ַ�����ΪUI��ʶ��
    void (*cb)(void);       //ui��ִ�к���
} UI_LIST;

UI_LIST ui_list[10] = {0};
/* �޸�add������������Ϊ�ַ��� */
void add(const char* name, void (*cb)(void))//Ĭ�ϻὫ����ӵ��ַ�����Ҳ�����β�1��Ĭ�϶��뵽ui_list[i] Ҳ���ǻᰴ˳��1234567~50��Ӷ�Ӧ���ַ������������ͺ���ָ��            ui_list[i].name = name;ui_list[i].cb = cb;
{
    for (int i = 0; i < sizeof(ui_list)/sizeof(ui_list[0]); i++)
    {
        if (ui_list[i].name == NULL)  // �ҵ���һ����λ
        {
            ui_list[i].name = name;
            ui_list[i].cb = cb;
            break;
        }
    }
}

/* �޸�ȫ�ֱ���Ϊ�ַ���ָ�� */
const char* ui_index = "menu";  // ��ʼ��������Ϊ�˵�

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
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
    delay_init(72);                         /* ��ʱ��ʼ�� */
    led_init();                             /* ��ʼ��LED */
    key_init();                             /* ��ʼ������ */
    beep_init();                            /* ��ʼ�������� */
    LED0(0);                                /* �ȵ���LED0 */
    usart_init(115200);

    /* �ֶ�ע��UI���棨ֱ�۵��ַ�����ʶ�� */
    add("menu",    menu_proc);
    add("cat",     cat_proc);
    add("pic",     pic_proc);
    add("setting", setting_proc);
    add("led",     led_proc);  // ʹ����������ַ�����������4;
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
            if (ui_list[i].name != NULL &&  strcmp(ui_index, ui_list[i].name) == 0)  // �ַ����ȶ�
            {
                if (ui_list[i].cb)
                {
                    ui_list[i].cb();
                }
                break;  // �ҵ����˳�ѭ�����Ч��
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
                ui_index = "cat";
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
                ui_index = "pic";
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
                ui_index = "setting";
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
                ui_index = "led";
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
                ui_index = "advalue";
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
                ui_index = "bat";
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
                ui_index = "mpu6050";
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
                ui_index = "about";
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
                ui_index = "menu";
                break;
        }
    }
}


