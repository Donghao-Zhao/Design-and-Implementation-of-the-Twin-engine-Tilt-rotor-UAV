/****************************************************************************************************
��ƽ    ̨������K66FX���ܳ�VCĸ��
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2019��04��12��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.2
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock�� 40.000MHz
��pllclock��200.000MHz
-------------------------------------------------------------
��LED
LED1--PTA17
LED2--PTC0
LED3--PTD15
LED4--PTE26
-------------------------------------------------------------
������
PTC17
-------------------------------------------------------------
����KEY
key0��PTB20
key1��PTB21
key2��PTB22
-------------------------------------------------------------
HC-SR04������������
HC_TRIG��PTE9
HC_ECHO��PTE10
-------------------------------------------------------------
MPU6050������(IIC)
SCL��PTD8
SDA��PTD9
-------------------------------------------------------------
���PWM
left��PTC01
right��PTC02
���PWM
left��PTC03
right��PTC04
-------------------------------------------------------------
����UART4
RXD��PTE25
TXD��PTE24
-------------------------------------------------------------
=============================================================
******************************************************************************************************/

#include "include.h"



/////////////////////////////////////////////////////////////////
////////////////////////��������/////////////////////////////////
/////////////////////////////////////////////////////////////////

/* ���ٶȡ�������ԭʼ���� */
short aac_x = 0;
short aac_y = 0;
short aac_z = 0;
short gyro_x = 0;
short gyro_y = 0;
short gyro_z = 0;

/* ŷ���� */
float pitch = 0;
float roll = 0;
float yaw = 0;
/* ŷ���� D */
float last_pitch = 0;
float last_roll = 0;
float last_yaw = 0;
/* ŷ���� I*/
float sum_pitch = 0;
float sum_roll = 0;
float sum_yaw = 0;
/* ŷ����У���� */
float set_pitch = 0;
float set_roll = 0;
float set_yaw = 0;

/* ����͵������ */
short steer_left_duty = steer_left_duty_mid;            //��������ֵ������������ǰ
short steer_right_duty = steer_right_duty_mid;          //�Ҷ������ֵ����С������ǰ
short motor_left_duty = motor_left_duty_zero;           //������ʼ��ֵ
short motor_right_duty = motor_right_duty_zero;         //�ҵ����ʼ��ֵ

/* ��̬���Ʊ��� */
short throttle = 0;
short duty_up = 100;                      //���ŵ���ϵ��

short steer_left_P_pitch = 25;            //���� ������ P
short steer_left_P_roll = 10;             //���� ����� P
short steer_left_P_yaw = 5;              //���� ����� P
short steer_right_P_pitch = 25;           //�Ҷ�� ������ P
short steer_right_P_roll = 10;            //�Ҷ�� ����� P
short steer_right_P_yaw = 5;             //���� ����� P
short motor_left_P_pitch = 0;            //���� ������ P
short motor_left_P_roll = 30;             //���� ����� P
short motor_left_P_yaw = 0;              //���� ����� P
short motor_right_P_pitch = 0;           //�ҵ�� ������ P
short motor_right_P_roll = 30;            //�ҵ�� ����� P
short motor_right_P_yaw = 0;             //�ҵ�� ����� P
//
//short steer_left_P_pitch = 20;            //���� ������ P
//short steer_left_P_roll = 10;             //���� ����� P
//short steer_left_P_yaw = 5;              //���� ����� P
//short steer_right_P_pitch = 20;           //�Ҷ�� ������ P
//short steer_right_P_roll = 10;            //�Ҷ�� ����� P
//short steer_right_P_yaw = 5;             //���� ����� P
//short motor_left_P_pitch = 15;            //���� ������ P
//short motor_left_P_roll = 15;             //���� ����� P
//short motor_left_P_yaw = 10;              //���� ����� P
//short motor_right_P_pitch = 15;           //�ҵ�� ������ P
//short motor_right_P_roll = 15;            //�ҵ�� ����� P
//short motor_right_P_yaw = 10;             //�ҵ�� ����� P

float steer_left_I_pitch = 0.0001;            //���� ������ I
float steer_left_I_roll = 0.0001;             //���� ����� I
float steer_left_I_yaw = 0.0001;              //���� ����� I
float steer_right_I_pitch = 0.0001;           //�Ҷ�� ������ I
float steer_right_I_roll = 0.0001;            //�Ҷ�� ����� I
float steer_right_I_yaw = 0.0001;             //���� ����� I
float motor_left_I_pitch = 0.0001;            //���� ������ I
float motor_left_I_roll = 0.0001;             //���� ����� I
float motor_left_I_yaw = 0.0001;              //���� ����� I
float motor_right_I_pitch = 0.0001;           //�ҵ�� ������ I
float motor_right_I_roll = 0.0001;            //�ҵ�� ����� I
float motor_right_I_yaw = 0.0001;             //�ҵ�� ����� I

short steer_left_D_pitch = 80;            //���� ������ D
short steer_left_D_roll = 5;             //���� ����� D
short steer_left_D_yaw = 60;              //���� ����� D
short steer_right_D_pitch = 80;           //�Ҷ�� ������ D
short steer_right_D_roll = 5;            //�Ҷ�� ����� D
short steer_right_D_yaw = 60;             //���� ����� D
short motor_left_D_pitch = 0;            //���� ������ D
short motor_left_D_roll = 50;             //���� ����� D
short motor_left_D_yaw = 5;              //���� ����� D
short motor_right_D_pitch = 0;           //�ҵ�� ������ D
short motor_right_D_roll = 50;            //�ҵ�� ����� D
short motor_right_D_yaw = 5;             //�ҵ�� ����� D

short motor_left_P_high = 10;              //���� �߶� P
short motor_right_P_high = 10;             //�ҵ�� �߶� P
short motor_left_I_high = 0;               //���� �߶� I
short motor_right_I_high = 0;              //�ҵ�� �߶� I
short motor_left_D_high = 0;             //���� �߶� D
short motor_right_D_high = 0;            //�ҵ�� �߶� D

/* ΢��ֵ */
short pitch_fix = 8;
short roll_fix = 25;
short yaw_fix = 0;

/* ��־λ���� */
short arm_mode = 0;             //ARMģʽ��־λ
short sensor_mode = 0;          //��ʾ��ģʽ��־λ
short remote_mode = 0;          //ң��ģʽ��־λ
short fix_height_mode = 0;      //����������ģʽ
short pid_flag = 0;             //0:P 1:I 2:D
short pid_set_flag = 0;         //0:pitch 1:roll 2:yaw 3:height
short pid_cmd_flag = 0;         //0:steer 1:motor

/* ���ڹ��ܶ��� */
char recv = '0';                //���ڽ��ջ����ַ�
char last[3];                   //�洢���3�����յ�����Ϣ
char uart_flag = 0;             //���ڿɽ��ձ�־��0���ɽ���

unsigned char tmp[30];          //������ʾ������ַ�ת��

/* ������ģ��������� */
uint64_t hc_error_flag = 0;     //���ճ�ʱ��־λ
uint64_t now_time;              //��ǰϵͳʱ��ֵ
uint64_t get_time;              //�յ����������ϵͳʱ��ֵ
uint64_t hc_time;               //���������͵����յ�ʱ��

/* ���������뷵��ֵ */
float dis = 0;
float last_dis = 0;
float sum_dis = 0;
/* ���������߼�¼ֵ */
float fix_dis = 0;
//float temp = -0.000185;


void main(void)
{
  
  
/////////////////////////////////////////////////////////////////
///////////////////////�ܳ�ʼ��//////////////////////////////////
/////////////////////////////////////////////////////////////////
  
  PLL_Init(PLL230);                     //��ʼ��PLL���໷Ϊ230M
  
  /* �����ж����ȼ���  0: 0����ռ���ȼ�16λ�������ȼ�
  * 1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ�
  * 3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ�*/
  
  NVIC_SetPriorityGrouping(2);
  
  /* OLED��ʼ�� */
  OLED_Init();
  
  /* UART��ʼ�� */
  OLED_P8x16Str(0,0,"UART_Init_Start");
  while(UART_Init(UART4, 115200))
    OLED_P8x16Str(0,0,"UART_Init_Fial");
  OLED_P8x16Str(0,0,"UART_Init_Done");
  
  /* LED��ʼ�� */
  OLED_P8x16Str(0,0,"LED_Init_Start");
  while(LED_Init())
    OLED_P8x16Str(0,0,"LED_Init_Fial");
  OLED_P8x16Str(0,0,"LED_Init_Done");
  
  /* KEY��ʼ�� */
  OLED_P8x16Str(0,0,"KEY_Init_Start");
  while(KEY_Init())
    OLED_P8x16Str(0,0,"KEY_Init_Fial");
  OLED_P8x16Str(0,0,"KEY_Init_Done");
  
  /* HC-SR04��ʼ�� */
  OLED_P8x16Str(0,0,"HC_Init_Start");
  while(HCSR04_Init())
    OLED_P8x16Str(0,0,"HC_Init_Fial");
  OLED_P8x16Str(0,0,"HC_Init_Done");
  
  /* MPU��ʼ�� */
  OLED_P8x16Str(0,0,"MPU_Init_Start");
  while(MPU6050_Init())
    OLED_P8x16Str(0,0,"MPU_Init_Fial");
  OLED_P8x16Str(0,0,"MPU_Init_Done");
  
  /* DMP��ʼ�� */
  OLED_P8x16Str(0,0,"DMP_Init_Start");
  while(mpu_dmp_init())
    OLED_P8x16Str(0,0,"DMP_Init_Fial");
  OLED_P8x16Str(0,0,"DMP_Init_Done");
  
  /* �����ʼ�� */
  OLED_P8x16Str(0,0,"Motor_Init_Start");
  FTM_PwmInit(FTM0, FTM_CH0, 50, steer_left_duty_mid); //��������
  FTM_PwmInit(FTM0, FTM_CH1, 50, steer_right_duty_mid); //�Ҷ������
  FTM_PwmInit(FTM0, FTM_CH2, 50, motor_left_duty_zero);    //����
  FTM_PwmInit(FTM0, FTM_CH3, 50, motor_right_duty_zero);    //�ҵ��
  OLED_P8x16Str(0,0,"Motor_Init_Done");
  
  PIT_Init(PIT0, 5);                  //��ʱ���жϻ�ȡ��������ֵ��ÿ20ms����һ��
  PIT_Init(PIT1, 100);
  /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
  NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)); 
  /* ���ȼ����� ��ռ���ȼ�0  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
  NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)); 
  NVIC_EnableIRQ(PIT0_IRQn);            //ʹ��PIT0_IRQn���ж�
  NVIC_EnableIRQ(PIT1_IRQn);		//ʹ��PIT1_IRQn���ж�
  
  OLED_CLS();                           //LCD������ȥ����Ӱ
  printf("Listening...?");
  
  /* ��������һ�±�����ʼ�����ɹ� */
  GPIO_PinInit(PTC17, GPO, 1);
  delayms(500);
  GPIO_PinInit(PTC17, GPO, 0);
  
  //  PIT_Init(PIT1, 100);
  //  PIT_Init(PIT2, 200);
  //  PIT_Init(PIT3, 300);
  
  /* ���ȼ����� ��ռ���ȼ�0  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
  //NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
  
  /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
  //NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
  
  /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
  //NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
  
  //NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1))
  
  
  //NVIC_EnableIRQ(PIT1_IRQn);			          //ʹ��PIT1_IRQn���ж�
  //NVIC_EnableIRQ(PIT2_IRQn);			          //ʹ��PIT2_IRQn���ж�
  //NVIC_EnableIRQ(PIT3_IRQn);			          //ʹ��PIT3_IRQn���ж�
  //NVIC_EnableIRQ(UART4_RX_TX_IRQn);			  //ʹ��UART4_RX_TX_IRQn���ж�
  
  /* ��ѭ�� */
  while(1)
  {
    
    
    //Test_ANO();//������λ��ͨѶ������Ҫ�õ���ȡ��ע��
    
    recv = '\0';                        //���ڽ��ջ����ַ���ʼ������
    
    /////////////////////////////////////////////////////////////////
    ///////////////////����������//////////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    if(GPIO_PinRead(PTB20) == 0)        //�м䰴������
    {
      delayms(3000);
      if(GPIO_PinRead(PTB20) == 0)      //�м䰴��3�����Ȼ����(Key0)
      {
        
        /* LEDȫ�� */
        GPIO_PinInit(PTA17, GPO, 0);
        GPIO_PinInit(PTC0 , GPO, 0);
        GPIO_PinInit(PTD15, GPO, 0);
        GPIO_PinInit(PTE26, GPO, 0);
        
        /* �������� */
        GPIO_PinInit(PTC17, GPO, 1);
        
        /* �л�ģʽ */
        if(arm_mode == 0)arm_mode = 1;
        else if(arm_mode == 1)
        {
          arm_mode = 0;
          remote_mode = 0;                      //ͬʱ�ر�ң��ģʽ
          fix_height_mode = 0;                     //ͬʱ�رճ���������ģʽ
        }
        delayms(2000);
        
        /* LEDȫ�� */
        GPIO_PinInit(PTA17, GPO, 1);
        GPIO_PinInit(PTC0 , GPO, 1);
        GPIO_PinInit(PTD15, GPO, 1);
        GPIO_PinInit(PTE26, GPO, 1);
        
        /* �������� */
        GPIO_PinInit(PTC17, GPO, 0);
      }
    }
    
    /* �󰴼����� */
    if(GPIO_PinRead(PTB21) == 0)
    {
      delayms(500);
      if(GPIO_PinRead(PTB21)==0)                //�󰴼�0.5�����Ȼ����(Key1)
      {
        
        /* ARMģʽ�л� */
        if(sensor_mode == 0)sensor_mode = 1;    
        else if(sensor_mode == 1)sensor_mode = 0;
      }
    }
    
    /* �Ұ������� */
    if(GPIO_PinRead(PTB22) == 0)
    {
      delayms(500);
      if(GPIO_PinRead(PTB22)==0)                //�󰴼�0.5�����Ȼ����(Key1)
      {
        
        /* ң��ģʽ�л� */
        if(remote_mode == 0 && arm_mode == 1)
        {
          remote_mode = 1;
          steer_left_duty = steer_left_duty_mid;            //��������ֵ
          steer_right_duty = steer_right_duty_mid;          //�Ҷ������ֵ
          motor_left_duty = motor_left_duty_start;          //��������
          motor_right_duty = motor_left_duty_start;         //�ҵ������
          
          /* ���ŷ���ǻ���ֵ */
          sum_pitch = 0;
          sum_roll = 0;
          sum_yaw = 0;
        }
        else if(remote_mode == 1){
          remote_mode = 0;
          fix_height_mode = 0;                     //ͬʱ�رճ���������ģʽ
        }
      }
    }
    
    
    /////////////////////////////////////////////////////////////////
    ///////////////�������ݴ�����//////////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    /* �������ݼĴ����� */
    if(UART4_S1 & UART_S1_RDRF_MASK)    
    {
      if(uart_flag == 0)
      {
      
      /* ���������ʾ���յ����ݣ�ʵ�ʲ��Ե�ʱ��Ҫȥ����Ϊռ��ʱ�� */
      GPIO_PinInit(PTC17, GPO, 1);
      delayms(100);
      GPIO_PinInit(PTC17, GPO, 0);
      
      /* FIFO����������յ����������� */
      last[2] = last[1];
      last[1] = last[0];
      recv = UART_GetChar(UART4);
      last[0] = recv;                   //�µ����ַ���Զ���ڵ�һ��������
      printf("last:%s?", last);        //���ڴ�ӡ������ܵ�3���ַ�
      }
      else if(uart_flag != 0)
      {
        UART_GetChar(UART4);
        uart_flag = 0;
      }
    }
    
    /* ������յ����ַ��ǡ�5�������ڴ�ӡbingo���� */
    if(recv == '5')                     
    {
      printf("bingo?");
      printf("Listening...?");
    }
    
    /* ������յ����ַ��ǡ�6�����˶����� */
    if(recv == '6')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //���ڷ���DISARM
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        printf("remote?");                     //���ڷ���remote
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        
        printf("Test_Motion...?");
        uart_flag = 1;
        Test_Motion();                          //����������
        printf("Test_Motion Success?");
        printf("Listening...?");
      }
    }
    
    /* ������յ����ַ��ǡ�7��У��ˮƽ */
    if(recv == '7')                     
    {
      
      /* ���ɿش���ARMģʽ */
      if(arm_mode == 1)                 
      {
        printf("ARM?");                        //���ڷ���ARM
        printf("Listening...?");
      }
      
      /* ���ɿش���DISARMģʽ */
      else if(arm_mode == 0)            
      {
        GPIO_PinInit(PTC17, GPO, 1);
        delayms(500);
        GPIO_PinInit(PTC17, GPO, 0);
        
        printf("Set_Ang...?");
        
        /* �ر�PIT��ʱ���ж� */     
        NVIC_DisableIRQ(PIT0_IRQn);
        NVIC_DisableIRQ(PIT0_IRQn);

        /* MPU��ʼ�� */  
        printf("MPU_Init_Start?");
        while(MPU6050_Init());
        
        /* DMP��ʼ�� */
        printf("DMP_Init_Start?");
        while(mpu_dmp_init());
        
        /* ʹ��PIT��ʱ���ж� */
        NVIC_EnableIRQ(PIT0_IRQn);
        NVIC_EnableIRQ(PIT1_IRQn);
        
        printf("Set_Ang Success?");
        
        GPIO_PinInit(PTC17, GPO, 1);
        delayms(500);
        GPIO_PinInit(PTC17, GPO, 0);
        
        printf("Listening...?");
      }
    } 
    
    /* ������յ����ַ��ǡ�r��������ң�� */
    if(recv == 'r')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        printf("remote_on_already?");                     //���ڷ���remote
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        remote_mode = 1;
        printf("remote_on?");
        printf("Listening...?");
      }
    }
    
    /* ������յ����ַ��ǡ�f�����ر�ң�� */
    if(recv == 'f')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");                     //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
      else if(arm_mode == 1 && remote_mode == 1)               
      {
        remote_mode = 0;
        printf("remote_off?");                     //���ڷ���remote
        printf("Listening...?");
      }
      else if(arm_mode == 1 && remote_mode == 0)            
      {
        printf("remote_off_already?");
        printf("Listening...?");
      }
    }
    
    /////////////////////////////////////////////////////////////////
    ////////////////////////΢�����ܺ���/////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    if(recv == 'i')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      { 
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
      else if(arm_mode == 1)            
      {
        if(--roll_fix < -30)
          roll_fix = -30;
        printf("roll_fix:%d?",roll_fix);
        printf("Listening...?");
      }
    } 
       
/////////////////////////////////////////////////////////////////
///////////////////////PID��������///////////////////////////////
/////////////////////////////////////////////////////////////////
    
    if(recv == 'g')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
      
      /* ���ɿش���DISARMģʽ */
      if(arm_mode == 0)                 
      {
        printf("DISARM?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
///////////////////��̬��״̬��������////////////////////////////
/////////////////////////////////////////////////////////////////
    
    
    /* ������յ����ַ��ǡ�0������������ */
    if(recv == '0')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(remote_mode == 0)                 
      {
        printf("DISremote?");               //���ڷ��ط�ң��
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
    
    /* ������յ����ַ��ǡ�1������С���� */
    if(recv == '1')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(remote_mode == 0)                 
      {
        printf("DISremote?");               //���ڷ��ط�ң��
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
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
    
    /* ������յ����ַ��ǡ�x�������ŵ��� */
    if(recv == 'x')                     
    {
      
      /* ���ɿش���DISARMģʽ */
      if(remote_mode == 0)                 
      { 
        printf("DISremote?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      
      /* ���ɿش���ARMģʽ */
      else if(remote_mode == 1)            
      {
        printf("duty_break...?");
        fix_height_mode = 0;                       //�رն���ģʽ
        printf("fix_high_mode_off?");
        remote_mode = 0;
        printf("remote_mode_off?");
        throttle = 0;
        printf("duty:%d?", throttle);
        printf("Listening...?");
      }
    }
    
    /* ������յ����ַ��ǡ�8������������������ģʽ*/
    if(recv == '8')                     
    {
      /* ���ɿش��ڷ�ң��ģʽ */
      if(remote_mode == 0)                 
      {
        
        printf("DISremote?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      /* ���ɿش���ң��ģʽ */
      else if(remote_mode == 1)            
      {
        /* ���ɿ�δ���ڶ���ģʽ */
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
    
    /* ������յ����ַ��ǡ�9�����رճ���������ģʽ*/
    if(recv == '9')                     
    {
      /* ���ɿش��ڷ�ң��ģʽ */
      if(remote_mode == 0)                 
      {
        
        printf("DISremote?");               //���ڷ���DISARM
        printf("Listening...?");
      }
      /* ���ɿش���ң��ģʽ */
      else if(remote_mode == 1)            
      {
        /* ���ɿ�δ���ڶ���ģʽ */
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
    
    
    /* ������δ����״̬��������������ռ�ձ�Ϊ�� */
    if(arm_mode == 0)
    {
      remote_mode = 0;                                  //�ر�ARM��ģʽ
      fix_height_mode = 0;
      GPIO_PinInit(PTC0 , GPO, 1);
      steer_left_duty = steer_left_duty_mid;            //��������
      steer_right_duty = steer_right_duty_mid;          //�Ҷ������
      motor_left_duty = motor_left_duty_zero;           //������0
      motor_right_duty = motor_right_duty_zero;         //�ҵ����0
    }
    /* �������ѽ���״̬����������������ʼ�� */
    if(arm_mode == 1 && remote_mode == 0)
    {
      LED_Reverse(1);
      if(remote_mode == 0)
      {
        steer_left_duty = steer_left_duty_mid;            //��������ֵ
        steer_right_duty = steer_right_duty_mid;          //�Ҷ������ֵ
        motor_left_duty = motor_left_duty_init;           //������ʼ��
        motor_right_duty = motor_left_duty_init;          //�ҵ����ʼ��
      }
    }
    
    
    //////////////////////���Ʒ�������//////////////////
    
    /* ���ɿش���ң��ģʽ */
    if(arm_mode == 1 && remote_mode == 1)            
    {
      
      // �������
      steer_left_duty  = (short) (steer_left_duty_mid                  //����ֵ
                                  +  steer_left_P_pitch * (pitch+pitch_fix)       //������P
                                  -  steer_left_P_roll *  (roll+roll_fix)          //�����P
                                  +  steer_left_P_yaw * (yaw+yaw_fix)         //�����P
                                      
                                  +  steer_left_I_pitch * sum_pitch        //������I
                                  -  steer_left_I_roll * sum_roll         //�����I
                                  +  steer_left_I_yaw * sum_yaw          //�����I
                                    
                                  +  steer_left_D_pitch * (pitch-last_pitch)       //������D
                                  -  steer_left_D_roll *  (roll-last_roll)          //�����D
                                  +  steer_left_D_yaw * (yaw-last_yaw)         //�����D
      );
      // �Ҷ�����                                                                     
      steer_right_duty = (short) (steer_right_duty_mid                 //����ֵ
                                  -  steer_right_P_pitch * (pitch+pitch_fix)        //������P
                                  -  steer_left_P_roll *  (roll+roll_fix)          //�����P
                                  +  steer_right_P_yaw * (yaw+yaw_fix)          //�����P  
                                    
                                  -  steer_right_I_pitch * sum_pitch        //������I
                                  -  steer_left_I_roll * sum_roll         //�����I
                                  +  steer_right_I_yaw * sum_yaw          //�����I
                                    
                                  -  steer_right_D_pitch * (pitch-last_pitch)       //������D
                                  -  steer_left_D_roll *  (roll-last_roll)          //�����D
                                  +  steer_right_D_yaw * (yaw-last_yaw)         //�����D
      );
      // �������
      motor_left_duty  = (short) (motor_left_duty_start                //ͣתת��
                                  +  throttle                            //���ſ���
                                  +  motor_left_P_pitch *  fabs(pitch+pitch_fix)  //������P
                                  -  motor_left_P_roll *  (roll+roll_fix)          //�����P
                                  +  motor_left_P_yaw * fabs(yaw+yaw_fix)       //�����P
                                    
                                  +  motor_left_I_pitch * fabs(sum_pitch) //������I
                                  -  motor_left_I_roll * sum_roll         //�����I
                                  +  motor_left_I_yaw * fabs(sum_roll)      //�����I
                                  
                                  +  motor_left_D_pitch *  fabs(pitch-last_pitch)  //������D
                                  -  motor_left_D_roll *  (roll-last_roll)          //�����D
                                  +  motor_left_D_yaw * fabs(yaw-last_yaw)       //�����D
                                    
                                  +  fix_height_mode * (motor_left_P_high * (fix_dis - dis)
                                  -  motor_left_I_high * (sum_dis + motor_left_D_high * (dis-last_dis)))
      );
      
      // �ҵ�����                                                                                                     
      motor_right_duty = (short) (motor_right_duty_start               //ͣתת��
                                  +  throttle                            //���ſ���
                                  +  motor_right_P_pitch * fabs(pitch+pitch_fix) //������P
                                  +  motor_right_P_roll * (roll+roll_fix)         //�����P
                                  +  motor_right_P_yaw * fabs(yaw+yaw_fix)      //�����P
                                    
                                  +  motor_right_I_pitch * fabs(sum_pitch) //������I
                                  +  motor_right_I_roll * sum_roll         //�����I
                                  +  motor_right_I_yaw * fabs(sum_roll)      //�����I
                                    
                                  +  motor_right_D_pitch * fabs(pitch-last_pitch)  //������D
                                  +  motor_right_D_roll * (roll-last_roll)          //�����D
                                  +  motor_right_D_yaw * fabs(yaw-last_yaw)       //�����D
                                    
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
    
    /* ��������� */
    FTM_PwmDuty(FTM0, FTM_CH0, steer_left_duty);
    FTM_PwmDuty(FTM0, FTM_CH1, steer_right_duty);
    FTM_PwmDuty(FTM0, FTM_CH2, motor_left_duty);
    FTM_PwmDuty(FTM0, FTM_CH3, motor_right_duty);
    
    LED_Reverse(0);//LED0��תָʾ���������������
    delayms(5);
  }
  
}
