/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
�������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�
��ע�����
-------------------------------------------------------------------------------------------------------*/
#include "include.h"

/*------------------------------------------------------------------------------------------------------
����    ����LED_Init
����    �ܡ���ʼ�����İ��ĸ���ϵ�LED
����    ������
���� �� ֵ����
��ʵ    ����LED_Init(); //��ʼ��LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
uint8_t LED_Init(void)
{
    /* ��ʼ�����İ��ϵ�LED */
   GPIO_PinInit(PTA17, GPO, 1);
   GPIO_PinInit(PTC0 , GPO, 1);
   GPIO_PinInit(PTD15, GPO, 1);
   GPIO_PinInit(PTE26, GPO, 1);
   
   /* ��ʼ��ĸ���ϵ�LED */
   GPIO_PinInit(PTC18, GPO, 1);
   GPIO_PinInit(PTC19, GPO, 1);
   
   return 0;
}

/*------------------------------------------------------------------------------------------------------
����    ����LED_ON
����    �ܡ�����
����    ����led   :  LED��
���� �� ֵ����
��ʵ    ����LED_ON(1); //��LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void LED_ON(uint8_t led)
{
    switch(led)
    {
      case 0:
        GPIO_PinInit(PTA17, GPO, 0);
        break;
        
      case 1:
        GPIO_PinInit(PTC0 , GPO, 0);
        break;
        
      case 2:
        GPIO_PinInit(PTD15, GPO, 0);
        break;
        
      case 3:
        GPIO_PinInit(PTE26, GPO, 0);
        break;
        
      case 4:
        GPIO_PinInit(PTC18, GPO, 0);
        break;
        
      case 5:
        GPIO_PinInit(PTC19, GPO, 0);
        break;
        
      default:
        break;
    }
}


/*------------------------------------------------------------------------------------------------------
����    ����LED_OFF
����    �ܡ��ص�
����    ����led   :  LED��
���� �� ֵ����
��ʵ    ����LED_OFF(1); //��LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void LED_OFF(uint8_t led)
{

    switch(led)
    {
      case 0:
        GPIO_PinInit(PTA17, GPO, 1);
        break;
        
      case 1:
        GPIO_PinInit(PTC0 , GPO, 1);
        break;
        
      case 2:
        GPIO_PinInit(PTD15, GPO, 1);
        break;
        
      case 3:
        GPIO_PinInit(PTE26, GPO, 1);
        break;
        
      case 4:
        GPIO_PinInit(PTC18, GPO, 1);
        break;
        
      case 5:
        GPIO_PinInit(PTC19, GPO, 1);
        break;
        
      default:
        break;
    }
}
/*------------------------------------------------------------------------------------------------------
����    ����LED_Reverse
����    �ܡ���תLED
����    ����led   :  LED��
���� �� ֵ����
��ʵ    ����LED_Reverse(1); //��תLED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void LED_Reverse(uint8_t led)
{
    /* ��¼LED״̬ */
    static uint8_t led_state[6];
    led_state[led]++;
    
    if(0 == led_state[led]%2)
    {
        LED_ON(led);
    }
    else
    {
        LED_OFF(led);
    }
}

/*------------------------------------------------------------------------------------------------------
����    ����LED_Test
����    �ܡ���תLED
����    ����led   :  LED��
���� �� ֵ����
��ʵ    ����LED_Test(); //����LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_LED(void)
{
    LED_Init();
    while(1)
    {
        LED_ON(0);
        LED_OFF(1);
        LED_OFF(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_ON(1);
        LED_OFF(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_OFF(1);
        LED_ON(2);
        LED_OFF(3);
        delayms(100);
        
        LED_OFF(0);
        LED_OFF(1);
        LED_OFF(2);
        LED_ON(3);
        delayms(100);
        
        LED_Reverse(4);
        LED_Reverse(5);
    }
}