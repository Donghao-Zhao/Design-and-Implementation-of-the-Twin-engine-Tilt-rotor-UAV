/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
�������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�FTM0���PWM�źſ��Ƶ������
��ע�����
-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_MOTOR.h"


/*------------------------------------------------------------------------------------------------------
����    ����Test_Motor
����    �ܡ�FTM0���PWM�źſ��Ƶ������
����    ����num  :  ������  ��PTC1 �� PTC2���Ƶ��1  ��PTC3 �� PTC4���Ƶ��2
���� �� ֵ��duty �� ռ�ձ�    ��Χ -FTM_PRECISON  �� +FTM_PRECISON
��ʵ    ����Test_Motor(); //���Ե��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void MOTOR_Ctrl(uint8_t num, short duty)
{
    if(abs(duty) > FTM_PRECISON)     //��ֹռ�ձȸ���
    {
        duty = 0;
    }
    switch(num)
    {
      case 1:
        if(duty > 0)
        {
            FTM_PwmDuty(FTM0, FTM_CH0, duty);
            FTM_PwmDuty(FTM0, FTM_CH1, 0);
        }
        else
        {
            FTM_PwmDuty(FTM0, FTM_CH0, 0);
            FTM_PwmDuty(FTM0, FTM_CH1, -duty);
        }
      case 2:
        if(duty > 0)
        {
            FTM_PwmDuty(FTM0, FTM_CH2, duty);
            FTM_PwmDuty(FTM0, FTM_CH3, 0);
        }
        else
        {
            FTM_PwmDuty(FTM0, FTM_CH2, 0);
            FTM_PwmDuty(FTM0, FTM_CH3, -duty);
        }
        
    }

}
/*------------------------------------------------------------------------------------------------------
����    ����Test_Motor
����    �ܡ�FTM0���PWM�źſ��Ƶ������
����    ������
���� �� ֵ����
��ʵ    ����Test_Motor(); //���Ե��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_Motion(void)
{
  /* ��������2�� */
  GPIO_PinInit(PTC17, GPO, 1);
  delayms(1000);
  GPIO_PinInit(PTC17, GPO, 0);
  
  /* Steer Mid   Motor Init */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_init);
  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_init);
  
/////////////////////////////////////////////////////////////////
///////////////////���������//////////////////////////////////
/////////////////////////////////////////////////////////////////
  /* Steer Left */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_front);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_front);
  delayms(1000);
  
  /* Steer Mid */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_mid);
  delayms(1000);
  
  /* Steer Right */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_rear);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_rear);
  delayms(1000);
  
  /* Steer Mid */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_mid);
  delayms(1000);
  
/////////////////////////////////////////////////////////////////
///////////////////���������//////////////////////////////////
/////////////////////////////////////////////////////////////////
  /* Motor Start */
  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_start);
  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_start);
  delayms(1000);
  
  /* Motor 1/3 */
  FTM_PwmDuty(FTM0, FTM_CH2, 6100);
  FTM_PwmDuty(FTM0, FTM_CH3, 6100);
  delayms(1000);
  
  /* Motor 2/3 */
//  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_2);
//  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_2);
//  delayms(1000);
//  
//  /* Motor Full */
//  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_full);
//  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_full);
//  delayms(1000);
//  
//  /* Motor Init */
//  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_init);
//  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_init);
//  delayms(1000);
//  
  /* ��������2�� */
  GPIO_PinInit(PTC17, GPO, 1);
  delayms(1000);
  GPIO_PinInit(PTC17, GPO, 0);
  
  
//    while(1)
//    {
//        switch(KEY_Read(1))     
//        {
//          case 1:
//            LED_Reverse(1); 
//            duty = 10900;
//            MOTOR_Ctrl(1, duty);     //���õ��1��ת��
//            MOTOR_Ctrl(2, duty);     //���õ��2��ת��
//            break;           
//          case 2: 
//            LED_Reverse(2); 
//            duty += 50;
//            if(duty > FTM_PRECISON)  //��ֹduty��
//            {
//                duty = FTM_PRECISON;
//            }
//            MOTOR_Ctrl(1, duty);     //���õ��1��ת��
//            MOTOR_Ctrl(2, duty);     //���õ��2��ת��
//            break;
//          case 3: 
//            LED_Reverse(3); 
//            duty -= 50;
//            if(duty < -FTM_PRECISON)  //��ֹduty��
//            {
//                duty = -FTM_PRECISON;
//            }
//            MOTOR_Ctrl(1, duty);     //���õ��1��ת��
//            MOTOR_Ctrl(2, duty);     //���õ��2��ת��
//            break;
//
//          default:
//            
//            break;
//        }
//        LED_Reverse(0);    
//        delayms(100);
//    }

}

/*------------------------------------------------------------------------------------------------------
����    ����Test_Enc
����    �ܡ������������빦��
����    ������
���� �� ֵ����
��ʵ    ����Test_Enc(); //�����������빦��
��ע�����
--------------------------------------------------------------------------------------------------------*/
#ifdef LQ_OLED
void Test_Enc(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    printf("��������������� \n");

    OLED_Init();
    OLED_CLS();
    
    OLED_P8x16Str(5,0,(uint8_t*)"LQ ENC Test"); 
    
    char txt[16];
    short speed1, speed2;
    while(1)
    {
        speed1 = FTM_ABGet(FTM1);
        speed2 = FTM_ABGet(FTM2);
        
        printf("?/ENC1 %5d ? ",speed1);
        sprintf(txt,"enc1:%5d ",speed1);
        OLED_P8x16Str(20,2,(uint8_t*)txt);
        
        printf("?/ENC2 %5d ? ",speed2);
        sprintf(txt,"enc2:%5d ",speed2);
        OLED_P8x16Str(20,4,(uint8_t*)txt);
        
        delayms(100);
    }

}
#else

void Test_Enc(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    printf("��������������� \n");

    TFTSPI_Init(1);                 //LCD��ʼ��  0:����  1������
    TFTSPI_CLS(u16BLUE);
    
    TFTSPI_P8X16Str(2, 0, "LQ ENC Test", u16RED, u16BLUE);
    
    char txt[16]; 
    short speed1, speed2;
    while(1)
    {
        speed1 = FTM_ABGet(FTM1);
        speed2 = FTM_ABGet(FTM2);
        
        printf("?/ENC1 %5d ? ",speed1);
        sprintf(txt,"enc1:%5d ",speed1);
        TFTSPI_P8X16Str(2, 2, txt, u16RED, u16BLUE);
        
        printf("?/ENC2 %5d ? ",speed2);
        sprintf(txt,"enc2:%5d ",speed2);
        TFTSPI_P8X16Str(2, 4, txt, u16RED, u16BLUE);
        
        delayms(100);
    }

}
#endif