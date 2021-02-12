/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】FTM0输出PWM信号控制电机例子
【注意事项】
-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_MOTOR.h"


/*------------------------------------------------------------------------------------------------------
【函    数】Test_Motor
【功    能】FTM0输出PWM信号控制电机例子
【参    数】num  :  电机标号  用PTC1 和 PTC2控制电机1  用PTC3 和 PTC4控制电机2
【返 回 值】duty ： 占空比    范围 -FTM_PRECISON  到 +FTM_PRECISON
【实    例】Test_Motor(); //测试电机
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void MOTOR_Ctrl(uint8_t num, short duty)
{
    if(abs(duty) > FTM_PRECISON)     //防止占空比给错
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
【函    数】Test_Motor
【功    能】FTM0输出PWM信号控制电机例子
【参    数】无
【返 回 值】无
【实    例】Test_Motor(); //测试电机
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_Motion(void)
{
  /* 蜂鸣器响2秒 */
  GPIO_PinInit(PTC17, GPO, 1);
  delayms(1000);
  GPIO_PinInit(PTC17, GPO, 0);
  
  /* Steer Mid   Motor Init */
  FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty_mid);
  FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty_init);
  FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty_init);
  
/////////////////////////////////////////////////////////////////
///////////////////舵机检测程序//////////////////////////////////
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
///////////////////电机检测程序//////////////////////////////////
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
  /* 蜂鸣器响2秒 */
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
//            MOTOR_Ctrl(1, duty);     //设置电机1的转速
//            MOTOR_Ctrl(2, duty);     //设置电机2的转速
//            break;           
//          case 2: 
//            LED_Reverse(2); 
//            duty += 50;
//            if(duty > FTM_PRECISON)  //防止duty超
//            {
//                duty = FTM_PRECISON;
//            }
//            MOTOR_Ctrl(1, duty);     //设置电机1的转速
//            MOTOR_Ctrl(2, duty);     //设置电机2的转速
//            break;
//          case 3: 
//            LED_Reverse(3); 
//            duty -= 50;
//            if(duty < -FTM_PRECISON)  //防止duty超
//            {
//                duty = -FTM_PRECISON;
//            }
//            MOTOR_Ctrl(1, duty);     //设置电机1的转速
//            MOTOR_Ctrl(2, duty);     //设置电机2的转速
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
【函    数】Test_Enc
【功    能】测试正交解码功能
【参    数】无
【返 回 值】无
【实    例】Test_Enc(); //测试正交解码功能
【注意事项】
--------------------------------------------------------------------------------------------------------*/
#ifdef LQ_OLED
void Test_Enc(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    printf("正交解码测试例程 \n");

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
    printf("正交解码测试例程 \n");

    TFTSPI_Init(1);                 //LCD初始化  0:横屏  1：竖屏
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