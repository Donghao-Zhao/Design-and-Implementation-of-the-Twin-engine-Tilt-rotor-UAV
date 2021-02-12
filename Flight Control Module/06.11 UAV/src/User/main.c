/****************************************************************************************************
【平    台】龙邱K66FX智能车VC母板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2019年04月12日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR8.2
【Target  】K66FX1M0VLQ18
【Crystal 】 50.000Mhz
【busclock】 40.000MHz
【pllclock】200.000MHz
-------------------------------------------------------------
灯LED
LED1--PTA17
LED2--PTC0
LED3--PTD15
LED4--PTE26
-------------------------------------------------------------
蜂鸣器
PTC17
-------------------------------------------------------------
按键KEY
key0—PTB20
key1—PTB21
key2—PTB22
-------------------------------------------------------------
HC-SR04超声波传感器
HC_TRIG—PTE9
HC_ECHO—PTE10
-------------------------------------------------------------
MPU6050陀螺仪(IIC)
SCL—PTD8
SDA—PTD9
-------------------------------------------------------------
舵机PWM
left—PTC01
right—PTC02
电机PWM
left—PTC03
right—PTC04
-------------------------------------------------------------
串口UART4
RXD—PTE25
TXD—PTE24
-------------------------------------------------------------
=============================================================
******************************************************************************************************/

#include "include.h"



/////////////////////////////////////////////////////////////////
////////////////////////变量定义/////////////////////////////////
/////////////////////////////////////////////////////////////////

/* 加速度、陀螺仪原始数据 */
short aac_x = 0;
short aac_y = 0;
short aac_z = 0;
short gyro_x = 0;
short gyro_y = 0;
short gyro_z = 0;

/* 欧拉角 */
float pitch = 0;
float roll = 0;
float yaw = 0;
/* 欧拉角 D */
float last_pitch = 0;
float last_roll = 0;
float last_yaw = 0;
/* 欧拉角 I*/
float sum_pitch = 0;
float sum_roll = 0;
float sum_yaw = 0;
/* 欧拉角校正角 */
float set_pitch = 0;
float set_roll = 0;
float set_yaw = 0;

/* 舵机和电机功率 */
short steer_left_duty = steer_left_duty_mid;            //左舵机中立值，增大则舵机向前
short steer_right_duty = steer_right_duty_mid;          //右舵机中立值，减小则舵机向前
short motor_left_duty = motor_left_duty_zero;           //左电机初始化值
short motor_right_duty = motor_right_duty_zero;         //右电机初始化值

/* 姿态控制变量 */
short throttle = 0;
short duty_up = 100;                      //油门调控系数

short steer_left_P_pitch = 25;            //左舵机 俯仰角 P
short steer_left_P_roll = 10;             //左舵机 横滚角 P
short steer_left_P_yaw = 5;              //左舵机 航向角 P
short steer_right_P_pitch = 25;           //右舵机 俯仰角 P
short steer_right_P_roll = 10;            //右舵机 横滚角 P
short steer_right_P_yaw = 5;             //左舵机 航向角 P
short motor_left_P_pitch = 0;            //左电机 俯仰角 P
short motor_left_P_roll = 30;             //左电机 横滚角 P
short motor_left_P_yaw = 0;              //左电机 航向角 P
short motor_right_P_pitch = 0;           //右电机 俯仰角 P
short motor_right_P_roll = 30;            //右电机 横滚角 P
short motor_right_P_yaw = 0;             //右电机 航向角 P
//
//short steer_left_P_pitch = 20;            //左舵机 俯仰角 P
//short steer_left_P_roll = 10;             //左舵机 横滚角 P
//short steer_left_P_yaw = 5;              //左舵机 航向角 P
//short steer_right_P_pitch = 20;           //右舵机 俯仰角 P
//short steer_right_P_roll = 10;            //右舵机 横滚角 P
//short steer_right_P_yaw = 5;             //左舵机 航向角 P
//short motor_left_P_pitch = 15;            //左电机 俯仰角 P
//short motor_left_P_roll = 15;             //左电机 横滚角 P
//short motor_left_P_yaw = 10;              //左电机 航向角 P
//short motor_right_P_pitch = 15;           //右电机 俯仰角 P
//short motor_right_P_roll = 15;            //右电机 横滚角 P
//short motor_right_P_yaw = 10;             //右电机 航向角 P

float steer_left_I_pitch = 0.0001;            //左舵机 俯仰角 I
float steer_left_I_roll = 0.0001;             //左舵机 横滚角 I
float steer_left_I_yaw = 0.0001;              //左舵机 航向角 I
float steer_right_I_pitch = 0.0001;           //右舵机 俯仰角 I
float steer_right_I_roll = 0.0001;            //右舵机 横滚角 I
float steer_right_I_yaw = 0.0001;             //左舵机 航向角 I
float motor_left_I_pitch = 0.0001;            //左电机 俯仰角 I
float motor_left_I_roll = 0.0001;             //左电机 横滚角 I
float motor_left_I_yaw = 0.0001;              //左电机 航向角 I
float motor_right_I_pitch = 0.0001;           //右电机 俯仰角 I
float motor_right_I_roll = 0.0001;            //右电机 横滚角 I
float motor_right_I_yaw = 0.0001;             //右电机 航向角 I

short steer_left_D_pitch = 80;            //左舵机 俯仰角 D
short steer_left_D_roll = 5;             //左舵机 横滚角 D
short steer_left_D_yaw = 60;              //左舵机 航向角 D
short steer_right_D_pitch = 80;           //右舵机 俯仰角 D
short steer_right_D_roll = 5;            //右舵机 横滚角 D
short steer_right_D_yaw = 60;             //左舵机 航向角 D
short motor_left_D_pitch = 0;            //左电机 俯仰角 D
short motor_left_D_roll = 50;             //左电机 横滚角 D
short motor_left_D_yaw = 5;              //左电机 航向角 D
short motor_right_D_pitch = 0;           //右电机 俯仰角 D
short motor_right_D_roll = 50;            //右电机 横滚角 D
short motor_right_D_yaw = 5;             //右电机 航向角 D

short motor_left_P_high = 10;              //左电机 高度 P
short motor_right_P_high = 10;             //右电机 高度 P
short motor_left_I_high = 0;               //左电机 高度 I
short motor_right_I_high = 0;              //右电机 高度 I
short motor_left_D_high = 0;             //左电机 高度 D
short motor_right_D_high = 0;            //右电机 高度 D

/* 微调值 */
short pitch_fix = 8;
short roll_fix = 25;
short yaw_fix = 0;

/* 标志位定义 */
short arm_mode = 0;             //ARM模式标志位
short sensor_mode = 0;          //显示屏模式标志位
short remote_mode = 0;          //遥控模式标志位
short fix_height_mode = 0;      //超声波定高模式
short pid_flag = 0;             //0:P 1:I 2:D
short pid_set_flag = 0;         //0:pitch 1:roll 2:yaw 3:height
short pid_cmd_flag = 0;         //0:steer 1:motor

/* 串口功能定义 */
char recv = '0';                //串口接收缓冲字符
char last[3];                   //存储最近3条接收到的消息
char uart_flag = 0;             //串口可接收标志，0：可接收

unsigned char tmp[30];          //用于显示屏输出字符转换

/* 超声波模块变量定义 */
uint64_t hc_error_flag = 0;     //接收超时标志位
uint64_t now_time;              //当前系统时钟值
uint64_t get_time;              //收到超声波后的系统时钟值
uint64_t hc_time;               //超声波发送到接收的时间

/* 超声波距离返回值 */
float dis = 0;
float last_dis = 0;
float sum_dis = 0;
/* 超声波定高记录值 */
float fix_dis = 0;
//float temp = -0.000185;


void main(void)
{
  
  
/////////////////////////////////////////////////////////////////
///////////////////////总初始化//////////////////////////////////
/////////////////////////////////////////////////////////////////
  
  PLL_Init(PLL230);                     //初始化PLL锁相环为230M
  
  /* 设置中断优先级组  0: 0个抢占优先级16位个子优先级
  * 1: 2个抢占优先级 8个子优先级 2: 4个抢占优先级 4个子优先级
  * 3: 8个抢占优先级 2个子优先级 4: 16个抢占优先级 0个子优先级*/
  
  NVIC_SetPriorityGrouping(2);
  
  /* OLED初始化 */
  OLED_Init();
  
  /* UART初始化 */
  OLED_P8x16Str(0,0,"UART_Init_Start");
  while(UART_Init(UART4, 115200))
    OLED_P8x16Str(0,0,"UART_Init_Fial");
  OLED_P8x16Str(0,0,"UART_Init_Done");
  
  /* LED初始化 */
  OLED_P8x16Str(0,0,"LED_Init_Start");
  while(LED_Init())
    OLED_P8x16Str(0,0,"LED_Init_Fial");
  OLED_P8x16Str(0,0,"LED_Init_Done");
  
  /* KEY初始化 */
  OLED_P8x16Str(0,0,"KEY_Init_Start");
  while(KEY_Init())
    OLED_P8x16Str(0,0,"KEY_Init_Fial");
  OLED_P8x16Str(0,0,"KEY_Init_Done");
  
  /* HC-SR04初始化 */
  OLED_P8x16Str(0,0,"HC_Init_Start");
  while(HCSR04_Init())
    OLED_P8x16Str(0,0,"HC_Init_Fial");
  OLED_P8x16Str(0,0,"HC_Init_Done");
  
  /* MPU初始化 */
  OLED_P8x16Str(0,0,"MPU_Init_Start");
  while(MPU6050_Init())
    OLED_P8x16Str(0,0,"MPU_Init_Fial");
  OLED_P8x16Str(0,0,"MPU_Init_Done");
  
  /* DMP初始化 */
  OLED_P8x16Str(0,0,"DMP_Init_Start");
  while(mpu_dmp_init())
    OLED_P8x16Str(0,0,"DMP_Init_Fial");
  OLED_P8x16Str(0,0,"DMP_Init_Done");
  
  /* 电机初始化 */
  OLED_P8x16Str(0,0,"Motor_Init_Start");
  FTM_PwmInit(FTM0, FTM_CH0, 50, steer_left_duty_mid); //左舵机中立
  FTM_PwmInit(FTM0, FTM_CH1, 50, steer_right_duty_mid); //右舵机中立
  FTM_PwmInit(FTM0, FTM_CH2, 50, motor_left_duty_zero);    //左电机
  FTM_PwmInit(FTM0, FTM_CH3, 50, motor_right_duty_zero);    //右电机
  OLED_P8x16Str(0,0,"Motor_Init_Done");
  
  PIT_Init(PIT0, 5);                  //定时器中断获取传感器数值，每20ms进行一次
  PIT_Init(PIT1, 100);
  /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
  NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)); 
  /* 优先级配置 抢占优先级0  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
  NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)); 
  NVIC_EnableIRQ(PIT0_IRQn);            //使能PIT0_IRQn的中断
  NVIC_EnableIRQ(PIT1_IRQn);		//使能PIT1_IRQn的中断
  
  OLED_CLS();                           //LCD清屏，去除残影
  printf("Listening...?");
  
  /* 蜂鸣器响一下表明初始化都成功 */
  GPIO_PinInit(PTC17, GPO, 1);
  delayms(500);
  GPIO_PinInit(PTC17, GPO, 0);
  
  //  PIT_Init(PIT1, 100);
  //  PIT_Init(PIT2, 200);
  //  PIT_Init(PIT3, 300);
  
  /* 优先级配置 抢占优先级0  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
  //NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
  
  /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
  //NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
  
  /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
  //NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
  
  //NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1))
  
  
  //NVIC_EnableIRQ(PIT1_IRQn);			          //使能PIT1_IRQn的中断
  //NVIC_EnableIRQ(PIT2_IRQn);			          //使能PIT2_IRQn的中断
  //NVIC_EnableIRQ(PIT3_IRQn);			          //使能PIT3_IRQn的中断
  //NVIC_EnableIRQ(UART4_RX_TX_IRQn);			  //使能UART4_RX_TX_IRQn的中断
  
  /* 主循环 */
  while(1)
  {
    
    
    //Test_ANO();//匿名上位机通讯程序，需要用到则取消注释
    
    recv = '\0';                        //串口接收缓冲字符初始化清零
    
    /////////////////////////////////////////////////////////////////
    ///////////////////按键处理函数//////////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    if(GPIO_PinRead(PTB20) == 0)        //中间按键按下
    {
      delayms(3000);
      if(GPIO_PinRead(PTB20) == 0)      //中间按键3秒后依然按下(Key0)
      {
        
        /* LED全亮 */
        GPIO_PinInit(PTA17, GPO, 0);
        GPIO_PinInit(PTC0 , GPO, 0);
        GPIO_PinInit(PTD15, GPO, 0);
        GPIO_PinInit(PTE26, GPO, 0);
        
        /* 蜂鸣器开 */
        GPIO_PinInit(PTC17, GPO, 1);
        
        /* 切换模式 */
        if(arm_mode == 0)arm_mode = 1;
        else if(arm_mode == 1)
        {
          arm_mode = 0;
          remote_mode = 0;                      //同时关闭遥控模式
          fix_height_mode = 0;                     //同时关闭超声波定高模式
        }
        delayms(2000);
        
        /* LED全灭 */
        GPIO_PinInit(PTA17, GPO, 1);
        GPIO_PinInit(PTC0 , GPO, 1);
        GPIO_PinInit(PTD15, GPO, 1);
        GPIO_PinInit(PTE26, GPO, 1);
        
        /* 蜂鸣器关 */
        GPIO_PinInit(PTC17, GPO, 0);
      }
    }
    
    /* 左按键按下 */
    if(GPIO_PinRead(PTB21) == 0)
    {
      delayms(500);
      if(GPIO_PinRead(PTB21)==0)                //左按键0.5秒后依然按下(Key1)
      {
        
        /* ARM模式切换 */
        if(sensor_mode == 0)sensor_mode = 1;    
        else if(sensor_mode == 1)sensor_mode = 0;
      }
    }
    
    /* 右按键按下 */
    if(GPIO_PinRead(PTB22) == 0)
    {
      delayms(500);
      if(GPIO_PinRead(PTB22)==0)                //左按键0.5秒后依然按下(Key1)
      {
        
        /* 遥控模式切换 */
        if(remote_mode == 0 && arm_mode == 1)
        {
          remote_mode = 1;
          steer_left_duty = steer_left_duty_mid;            //左舵机中立值
          steer_right_duty = steer_right_duty_mid;          //右舵机中立值
          motor_left_duty = motor_left_duty_start;          //左电机启动
          motor_right_duty = motor_left_duty_start;         //右电机启动
          
          /* 清空欧拉角积分值 */
          sum_pitch = 0;
          sum_roll = 0;
          sum_yaw = 0;
        }
        else if(remote_mode == 1){
          remote_mode = 0;
          fix_height_mode = 0;                     //同时关闭超声波定高模式
        }
      }
    }
    
    
    /////////////////////////////////////////////////////////////////
    ///////////////串口数据处理函数//////////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    /* 接收数据寄存器满 */
    if(UART4_S1 & UART_S1_RDRF_MASK)    
    {
      if(uart_flag == 0)
      {
      
      /* 蜂鸣器响表示接收到数据，实际测试的时候要去掉因为占用时间 */
      GPIO_PinInit(PTC17, GPO, 1);
      delayms(100);
      GPIO_PinInit(PTC17, GPO, 0);
      
      /* FIFO，保留最近收到的三个数据 */
      last[2] = last[1];
      last[1] = last[0];
      recv = UART_GetChar(UART4);
      last[0] = recv;                   //新到的字符永远放在第一个数组中
      printf("last:%s?", last);        //串口打印最近接受的3个字符
      }
      else if(uart_flag != 0)
      {
        UART_GetChar(UART4);
        uart_flag = 0;
      }
    }
    
    /* 如果接收到的字符是‘5’，串口打印bingo测试 */
    if(recv == '5')                     
    {
      printf("bingo?");
      printf("Listening...?");
    }
    
    /* 如果接收到的字符是‘6’，运动测试 */
    if(recv == '6')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //串口返回DISARM
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        printf("remote?");                     //串口返回remote
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        
        printf("Test_Motion...?");
        uart_flag = 1;
        Test_Motion();                          //电机舵机测试
        printf("Test_Motion Success?");
        printf("Listening...?");
      }
    }
    
    /* 如果接收到的字符是‘7’校验水平 */
    if(recv == '7')                     
    {
      
      /* 若飞控处于ARM模式 */
      if(arm_mode == 1)                 
      {
        printf("ARM?");                        //串口返回ARM
        printf("Listening...?");
      }
      
      /* 若飞控处于DISARM模式 */
      else if(arm_mode == 0)            
      {
        GPIO_PinInit(PTC17, GPO, 1);
        delayms(500);
        GPIO_PinInit(PTC17, GPO, 0);
        
        printf("Set_Ang...?");
        
        /* 关闭PIT定时器中断 */     
        NVIC_DisableIRQ(PIT0_IRQn);
        NVIC_DisableIRQ(PIT0_IRQn);

        /* MPU初始化 */  
        printf("MPU_Init_Start?");
        while(MPU6050_Init());
        
        /* DMP初始化 */
        printf("DMP_Init_Start?");
        while(mpu_dmp_init());
        
        /* 使能PIT定时器中断 */
        NVIC_EnableIRQ(PIT0_IRQn);
        NVIC_EnableIRQ(PIT1_IRQn);
        
        printf("Set_Ang Success?");
        
        GPIO_PinInit(PTC17, GPO, 1);
        delayms(500);
        GPIO_PinInit(PTC17, GPO, 0);
        
        printf("Listening...?");
      }
    } 
    
    /* 如果接收到的字符是‘r’，开启遥控 */
    if(recv == 'r')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        printf("remote_on_already?");                     //串口返回remote
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        remote_mode = 1;
        printf("remote_on?");
        printf("Listening...?");
      }
    }
    
    /* 如果接收到的字符是‘f’，关闭遥控 */
    if(recv == 'f')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        remote_mode = 0;
        printf("remote_off?");                     //串口返回remote
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        printf("remote_off_already?");
        printf("Listening...?");
      }
    }
    
    /////////////////////////////////////////////////////////////////
    ////////////////////////微调功能函数/////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    if(recv == 'i')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      { 
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++pitch_fix > 30)
          pitch_fix = 30;
        printf("pitch_fix:%d?",pitch_fix);
        printf("Listening...?");
      }
    }
    
    if(recv == 'k')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(--pitch_fix < -30)
          pitch_fix = -30;
        printf("pitch_fix:%d?",pitch_fix);
        printf("Listening...?");
      }
    }
    
    if(recv == 'j')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(--yaw_fix < -30)
          yaw_fix = -30;
        printf("yaw_fix:%d?",yaw_fix);
        printf("Listening...?");
      }
    } 
    
    if(recv == 'l')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++yaw_fix > 30)
          yaw_fix = 30;
        printf("yaw_fix:%d?",yaw_fix);
        printf("Listening...?");
      }
    }
    
    if(recv == 'u')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++roll_fix > 30)
          roll_fix = 30;
        printf("roll_fix:%d?",roll_fix);
        printf("Listening...?");
      }
    }
    
    if(recv == 'o')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(--roll_fix < -30)
          roll_fix = -30;
        printf("roll_fix:%d?",roll_fix);
        printf("Listening...?");
      }
    } 
       
/////////////////////////////////////////////////////////////////
///////////////////////PID调整函数///////////////////////////////
/////////////////////////////////////////////////////////////////
    
    if(recv == 'g')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++pid_flag >= 3)
          pid_flag = 0;
        switch(pid_flag){
        case 0:
          printf("pid_mode:P?");break;
        case 1:
          printf("pid_mode:I?");break;
        case 2:
          printf("pid_mode:D?");break;
        }
        switch(pid_set_flag){
        case 0:
          printf("set_mode:pitch?");break;
        case 1:
          printf("set_mode:roll?");break;
        case 2:
          printf("set_mode:yaw?");break;
        case 3:
          printf("set_mode:height?");break;
        }
        if(pid_cmd_flag == 0){
          printf("cmd_mode:steer?");
        }else{
          printf("cmd_mode:motor?");
        }
        printf("Listening...?");
      }
    }
    
    if(recv == 'b')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++pid_set_flag >= 4)
          pid_set_flag = 0;
        switch(pid_flag){
        case 0:
          printf("pid_mode:P?");break;
        case 1:
          printf("pid_mode:I?");break;
        case 2:
          printf("pid_mode:D?");break;
        }
        switch(pid_set_flag){
        case 0:
          printf("set_mode:pitch?");break;
        case 1:
          printf("set_mode:roll?");break;
        case 2:
          printf("set_mode:yaw?");break;
        case 3:
          printf("set_mode:height?");break;
        }
        if(pid_cmd_flag == 0){
          printf("cmd_mode:steer?");
        }else{
          printf("cmd_mode:motor?");
        }
        printf("Listening...?");
      }
    }
    
    if(recv == 'v')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(++pid_cmd_flag >= 2)
          pid_cmd_flag = 0;
        switch(pid_flag){
        case 0:
          printf("pid_mode:P?");break;
        case 1:
          printf("pid_mode:I?");break;
        case 2:
          printf("pid_mode:D?");break;
        }
        switch(pid_set_flag){
        case 0:
          printf("set_mode:pitch?");break;
        case 1:
          printf("set_mode:roll?");break;
        case 2:
          printf("set_mode:yaw?");break;
        case 3:
          printf("set_mode:height?");break;
        }
        if(pid_cmd_flag == 0){
          printf("cmd_mode:steer?");
        }else{
          printf("cmd_mode:motor?");
        }
        printf("Listening...?");
      }
    }
    
    if(recv == 'h')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(pid_flag == 0){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
              steer_left_P_pitch++;
              steer_right_P_pitch++;
              printf("steer_P_pitch:%d?",steer_left_P_pitch);
            }else{
              motor_left_P_pitch++;
              motor_right_P_pitch++;
              printf("motor_P_pitch:%d?",motor_left_P_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
              steer_left_P_roll++;
              steer_right_P_roll++;
              printf("steer_P_roll:%d?",steer_left_P_roll);
            }else{
              motor_left_P_roll++;
              motor_right_P_roll++;
              printf("motor_P_roll:%d?",motor_left_P_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
              steer_left_P_yaw++;
              steer_right_P_yaw++;
              printf("steer_P_yaw:%d?",steer_left_P_yaw);
            }else{
              motor_left_P_yaw++;
              motor_right_P_yaw++;
              printf("motor_P_yaw:%d?",motor_left_P_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
              motor_left_P_high++;
              motor_right_P_high++;
              printf("motor_P_height:%d?",motor_left_P_high);
            }break;
          }
        }
        if(pid_flag == 1){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
              steer_left_I_pitch=1/(1/steer_left_I_pitch-1);
              steer_right_I_pitch=1/(1/steer_right_I_pitch-1);
              printf("steer_I_pitch:%f?",steer_left_I_pitch);
            }else{
              motor_left_I_pitch=1/(1/motor_left_I_pitch-1);
              motor_right_I_pitch=1/(1/motor_right_I_pitch-1);
              printf("motor_I_pitch:%f?",motor_left_I_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
              steer_left_I_roll=1/(1/steer_left_I_roll-1);
              steer_right_I_roll=1/(1/steer_right_I_roll-1);
              printf("steer_I_roll:%f?",steer_left_I_roll);
            }else{
              motor_left_I_roll=1/(1/motor_left_I_roll-1);
              motor_right_I_roll=1/(1/motor_right_I_roll-1);
              printf("motor_I_roll:%f?",motor_left_I_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
              steer_left_I_yaw=1/(1/steer_left_I_yaw-1);
              steer_right_I_yaw=1/(1/steer_right_I_yaw-1);
              printf("steer_I_yaw:%f?",steer_left_I_yaw);
            }else{
              motor_left_I_yaw=1/(1/motor_left_I_yaw-1);
              motor_right_I_yaw=1/(1/motor_right_I_yaw-1);
              printf("motor_I_yaw:%f?",motor_left_I_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
              motor_left_I_high++;
              motor_right_I_high++;
              printf("motor_left_I_height:%d?",motor_left_I_high);
            }break;
          }
        }
        if(pid_flag == 2){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
              steer_left_D_pitch++;
              steer_right_D_pitch++;
              printf("steer_D_pitch:%d?",steer_left_D_pitch);
            }else{
              motor_left_D_pitch++;
              motor_right_D_pitch++;
              printf("motor_D_pitch:%d?",motor_left_D_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
              steer_left_D_roll++;
              steer_right_D_roll++;
              printf("steer_D_roll:%d?",steer_left_D_roll);
            }else{
              motor_left_D_roll++;
              motor_right_D_roll++;
              printf("motor_D_roll:%d?",motor_left_D_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
              steer_left_D_yaw++;
              steer_right_D_yaw++;
              printf("steer_D_yaw:%d?",steer_left_D_yaw);
            }else{
              motor_left_D_yaw++;
              motor_right_D_yaw++;
              printf("motor_D_yaw:%d?",motor_left_D_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
              motor_left_D_high++;
              motor_right_D_high++;
              printf("motor_D_height:%d?",motor_left_D_high);
            }break;
          }
        }
        printf("Listening...?");
      }
    }
    
    if(recv == 'n')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(arm_mode == 1)            
      {
        if(pid_flag == 0){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
              steer_left_P_pitch--;
              steer_right_P_pitch--;
              printf("steer_P_pitch:%d?",steer_left_P_pitch);
            }else{
              motor_left_P_pitch--;
              motor_right_P_pitch--;
              printf("motor_P_pitch:%d?",motor_left_P_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
              steer_left_P_roll--;
              steer_right_P_roll--;
              printf("steer_P_roll:%d?",steer_left_P_roll);
            }else{
              motor_left_P_roll--;
              motor_right_P_roll--;
              printf("motor_P_roll:%d?",motor_left_P_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
              steer_left_P_yaw--;
              steer_right_P_yaw--;
              printf("steer_P_yaw:%d?",steer_left_P_yaw);
            }else{
              motor_left_P_yaw--;
              motor_right_P_yaw--;
              printf("motor_P_yaw:%d?",motor_left_P_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
              motor_left_P_high--;
              motor_right_P_high--;
              printf("motor_P_height:%d?",motor_left_P_high);
            }break;
          }
        }
        if(pid_flag == 1){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
              steer_left_I_pitch=1/(1/steer_left_I_pitch+1);
              steer_right_I_pitch=1/(1/steer_right_I_pitch+1);
              printf("steer_I_pitch:%f?",steer_left_I_pitch);
            }else{
              motor_left_I_pitch=1/(1/motor_left_I_pitch+1);
              motor_right_I_pitch=1/(1/motor_right_I_pitch+1);
              printf("motor_I_pitch:%f?",motor_left_I_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
              steer_left_I_roll=1/(1/steer_left_I_roll+1);
              steer_right_I_roll=1/(1/steer_right_I_roll+1);
              printf("steer_I_roll:%f?",steer_left_I_roll);
            }else{
              motor_left_I_roll=1/(1/motor_left_I_roll+1);
              motor_right_I_roll=1/(1/motor_right_I_roll+1);
              printf("motor_I_roll:%f?",motor_left_I_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
              steer_left_I_yaw=1/(1/steer_left_I_yaw+1);
              steer_right_I_yaw=1/(1/steer_right_I_yaw+1);
              printf("steer_I_yaw:%f?",steer_left_I_yaw);
            }else{
              motor_left_I_yaw=1/(1/motor_left_I_yaw+1);
              motor_right_I_yaw=1/(1/motor_right_I_yaw+1);
              printf("motor_I_yaw:%f?",motor_left_I_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
              motor_left_I_high--;
              motor_right_I_high--;
              printf("motor_I_height:%d?",motor_left_I_high);break;
            }
          }
        }
        if(pid_flag == 2){
          switch(pid_set_flag){
          case 0:
            if(pid_cmd_flag == 0){
            steer_left_D_pitch--;
            steer_right_D_pitch--;
            printf("steer_D_pitch:%d?",steer_left_D_pitch);
            }else{
            motor_left_D_pitch--;
            motor_right_D_pitch--;
            printf("motor_D_pitch:%d?",motor_left_D_pitch);
            }break;
          case 1:
            if(pid_cmd_flag == 0){
            steer_left_D_roll--;
            steer_right_D_roll--;
            printf("steer_D_roll:%d?",steer_left_D_roll);
            }else{
            motor_left_D_roll--;
            motor_right_D_roll--;
            printf("motor_D_roll:%d?",motor_left_D_roll);
            }break;
          case 2:
            if(pid_cmd_flag == 0){
            steer_left_D_yaw--;
            steer_right_D_yaw--;
            printf("steer_D_yaw:%d?",steer_left_D_yaw);
            }else{
            motor_left_D_yaw--;
            motor_right_D_yaw--;
            printf("motor_D_yaw:%d?",motor_left_D_yaw);
            }break;
          case 3:
            if(pid_cmd_flag == 0){
            }else{
            motor_left_D_high--;
            motor_right_D_high--;
            printf("motor_D_height:%d?",motor_left_D_high);
            }break;
          }
        }
        printf("Listening...?");
      }
    }
/////////////////////////////////////////////////////////////////
///////////////////姿态和状态调整函数////////////////////////////
/////////////////////////////////////////////////////////////////
    
    
    /* 如果接收到的字符是‘0’，增加油门 */
    if(recv == '0')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(remote_mode == 0)                 
      {
        printf("DISremote?");               //串口返回非遥控
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(remote_mode == 1)            
      {
        printf("duty_up...?");
        
        throttle += duty_up;
        if(throttle > 3700)
          throttle = 3700;
        printf("duty:%d?", throttle);
        printf("Listening...?");
      }
    } 
    
    /* 如果接收到的字符是‘1’，减小油门 */
    if(recv == '1')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(remote_mode == 0)                 
      {
        printf("DISremote?");               //串口返回非遥控
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(remote_mode == 1)            
      {
        printf("duty_down...?");
        throttle -= duty_up;
        if(throttle < 0)
          throttle = 0;
        printf("duty:%d?", throttle);
        printf("Listening...?");
      }
    }
    
    /* 如果接收到的字符是‘x’，油门调空 */
    if(recv == 'x')                     
    {
      
      /* 若飞控处于DISARM模式 */
      if(remote_mode == 0)                 
      { 
        printf("DISremote?");               //串口返回DISARM
        printf("Listening...?");
      }
      
      /* 若飞控处于ARM模式 */
      else if(remote_mode == 1)            
      {
        printf("duty_break...?");
        fix_height_mode = 0;                       //关闭定高模式
        printf("fix_high_mode_off?");
        remote_mode = 0;
        printf("remote_mode_off?");
        throttle = 0;
        printf("duty:%d?", throttle);
        printf("Listening...?");
      }
    }
    
    /* 如果接收到的字符是‘8’，开启超声波定高模式*/
    if(recv == '8')                     
    {
      /* 若飞控处于非遥控模式 */
      if(remote_mode == 0)                 
      {
        
        printf("DISremote?");               //串口返回DISARM
        printf("Listening...?");
      }
      /* 若飞控处于遥控模式 */
      else if(remote_mode == 1)            
      {
        /* 若飞控未处于定高模式 */
        if(fix_height_mode == 0)
        {
          if(hc_error_flag == 0)
          {
            fix_dis = dis;
            sum_dis = 0;
            fix_height_mode = 1;
            printf("fix_high_mode_on?");
          }
          else if(hc_error_flag != 0)
          {
            printf("fix_high_mode_fail?");
          }
        }
        else if(fix_height_mode == 1)
        {
          printf("on_already?");
        }
        printf("Listening...?");
      }
    }
    
    /* 如果接收到的字符是‘9’，关闭超声波定高模式*/
    if(recv == '9')                     
    {
      /* 若飞控处于非遥控模式 */
      if(remote_mode == 0)                 
      {
        
        printf("DISremote?");               //串口返回DISARM
        printf("Listening...?");
      }
      /* 若飞控处于遥控模式 */
      else if(remote_mode == 1)            
      {
        /* 若飞控未处于定高模式 */
        if(fix_height_mode == 0)
        {
            printf("off_already?");
        }
        else if(fix_height_mode == 1)
        {
          fix_height_mode = 0;
          printf("fix_high_mode_off?");
        }
        printf("Listening...?");
      }
    }
    
    
    /* 舵机电机未解锁状态，舵机中立，电机占空比为零 */
    if(arm_mode == 0)
    {
      remote_mode = 0;                                  //关闭ARM子模式
      fix_height_mode = 0;
      GPIO_PinInit(PTC0 , GPO, 1);
      steer_left_duty = steer_left_duty_mid;            //左舵机中立
      steer_right_duty = steer_right_duty_mid;          //右舵机中立
      motor_left_duty = motor_left_duty_zero;           //左电机置0
      motor_right_duty = motor_right_duty_zero;         //右电机置0
    }
    /* 舵机电机已解锁状态，舵机中立，电机初始化 */
    if(arm_mode == 1 && remote_mode == 0)
    {
      LED_Reverse(1);
      if(remote_mode == 0)
      {
        steer_left_duty = steer_left_duty_mid;            //左舵机中立值
        steer_right_duty = steer_right_duty_mid;          //右舵机中立值
        motor_left_duty = motor_left_duty_init;           //左电机初始化
        motor_right_duty = motor_left_duty_init;          //右电机初始化
      }
    }
    
    
    //////////////////////控制反馈函数//////////////////
    
    /* 若飞控处于遥控模式 */
    if(arm_mode == 1 && remote_mode == 1)            
    {
      
      // 左舵机输出
      steer_left_duty  = (short) (steer_left_duty_mid                  //中立值
                                  +  steer_left_P_pitch * (pitch+pitch_fix)       //俯仰角P
                                  -  steer_left_P_roll *  (roll+roll_fix)          //横滚角P
                                  +  steer_left_P_yaw * (yaw+yaw_fix)         //航向角P
                                      
                                  +  steer_left_I_pitch * sum_pitch        //俯仰角I
                                  -  steer_left_I_roll * sum_roll         //横滚角I
                                  +  steer_left_I_yaw * sum_yaw          //航向角I
                                    
                                  +  steer_left_D_pitch * (pitch-last_pitch)       //俯仰角D
                                  -  steer_left_D_roll *  (roll-last_roll)          //横滚角D
                                  +  steer_left_D_yaw * (yaw-last_yaw)         //航向角D
      );
      // 右舵机输出                                                                     
      steer_right_duty = (short) (steer_right_duty_mid                 //中立值
                                  -  steer_right_P_pitch * (pitch+pitch_fix)        //俯仰角P
                                  -  steer_left_P_roll *  (roll+roll_fix)          //横滚角P
                                  +  steer_right_P_yaw * (yaw+yaw_fix)          //航向角P  
                                    
                                  -  steer_right_I_pitch * sum_pitch        //俯仰角I
                                  -  steer_left_I_roll * sum_roll         //横滚角I
                                  +  steer_right_I_yaw * sum_yaw          //航向角I
                                    
                                  -  steer_right_D_pitch * (pitch-last_pitch)       //俯仰角D
                                  -  steer_left_D_roll *  (roll-last_roll)          //横滚角D
                                  +  steer_right_D_yaw * (yaw-last_yaw)         //航向角D
      );
      // 左电机输出
      motor_left_duty  = (short) (motor_left_duty_start                //停转转速
                                  +  throttle                            //油门控制
                                  +  motor_left_P_pitch *  fabs(pitch+pitch_fix)  //俯仰角P
                                  -  motor_left_P_roll *  (roll+roll_fix)          //横滚角P
                                  +  motor_left_P_yaw * fabs(yaw+yaw_fix)       //航向角P
                                    
                                  +  motor_left_I_pitch * fabs(sum_pitch) //俯仰角I
                                  -  motor_left_I_roll * sum_roll         //横滚角I
                                  +  motor_left_I_yaw * fabs(sum_roll)      //航向角I
                                  
                                  +  motor_left_D_pitch *  fabs(pitch-last_pitch)  //俯仰角D
                                  -  motor_left_D_roll *  (roll-last_roll)          //横滚角D
                                  +  motor_left_D_yaw * fabs(yaw-last_yaw)       //航向角D
                                    
                                  +  fix_height_mode * (motor_left_P_high * (fix_dis - dis)
                                  -  motor_left_I_high * (sum_dis + motor_left_D_high * (dis-last_dis)))
      );
      
      // 右电机输出                                                                                                     
      motor_right_duty = (short) (motor_right_duty_start               //停转转速
                                  +  throttle                            //油门控制
                                  +  motor_right_P_pitch * fabs(pitch+pitch_fix) //俯仰角P
                                  +  motor_right_P_roll * (roll+roll_fix)         //横滚角P
                                  +  motor_right_P_yaw * fabs(yaw+yaw_fix)      //航向角P
                                    
                                  +  motor_right_I_pitch * fabs(sum_pitch) //俯仰角I
                                  +  motor_right_I_roll * sum_roll         //横滚角I
                                  +  motor_right_I_yaw * fabs(sum_roll)      //航向角I
                                    
                                  +  motor_right_D_pitch * fabs(pitch-last_pitch)  //俯仰角D
                                  +  motor_right_D_roll * (roll-last_roll)          //横滚角D
                                  +  motor_right_D_yaw * fabs(yaw-last_yaw)       //航向角D
                                    
                                  +  fix_height_mode * (motor_right_P_high * (fix_dis - dis)
                                  -  motor_right_I_high * (sum_dis + motor_right_D_high * (dis-last_dis)))
      );
      
      if(steer_left_duty > steer_left_duty_front)   steer_left_duty = steer_left_duty_front;
      if(steer_left_duty < steer_left_duty_rear)    steer_left_duty = steer_left_duty_rear;
      
      if(steer_right_duty < steer_right_duty_front) steer_right_duty = steer_right_duty_front;
      if(steer_right_duty > steer_right_duty_rear)  steer_right_duty = steer_right_duty_rear;
      
      if(motor_left_duty < motor_left_duty_start)   motor_left_duty = motor_left_duty_start;
      if(motor_left_duty > motor_left_duty_full)    motor_left_duty = motor_left_duty_full;
      
      if(motor_right_duty < motor_right_duty_start) motor_right_duty = motor_right_duty_start;
      if(motor_right_duty > motor_right_duty_full)  motor_right_duty = motor_right_duty_full;
    }
    
    /* 舵机电机输出 */
    FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty);
    FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty);
    FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty);
    FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty);
    
    LED_Reverse(0);//LED0反转指示主程序的正常运行
    delayms(5);
  }
  
}
