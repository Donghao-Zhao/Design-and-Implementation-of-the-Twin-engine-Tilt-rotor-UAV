/*---------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ��жϷ�����
��ע������жϷ�������������startup_MK60D10.s ��
----------------------------------------------------------------*/
#include "include.h"

#define HC_TRIG   PTE9   //���������ź�����
#define HC_ECHO   PTE10  //����ߵ�ƽ����

//------------------------------------------------------------------------------------------------    
//ȫ�ֱ���  ���ڲ��԰����ⲿ�ж�
//------------------------------------------------------------------------------------------------
extern volatile uint8_t key_exti_flag;

extern short steer_left_duty;                   //����
extern short steer_right_duty;                  //�Ҷ��
extern short motor_left_duty;                   //����
extern short motor_right_duty;                  //�ҵ��

extern short aac_x, aac_y, aac_z;               //���ٶ�ԭʼ����
extern short gyro_x, gyro_y, gyro_z;            //������ԭʼ����
extern float pitch,roll,yaw;                    //ŷ����
extern float last_pitch, last_roll, last_yaw;
extern float sum_pitch, sum_roll, sum_yaw;
extern short pitch_fix, roll_fix, yaw_fix;

extern short ang_set_flag;                    //У��ˮƽ��־
extern short ang_i;                           //��������

extern float Ang_sum_x, Ang_sum_y, Ang_sum_z;   //���ٶȼ�ˮƽ����
extern float gyro_sum_x, gyro_sum_y, gyro_sum_z;//�����Ǿ�̬ƫ���
extern float IGyro_x_init, IGyro_y_init, IGyro_z_init;//�����ǻ��ֺ�ĽǶȳ�ֵ

extern float dis;                               //����������

extern short arm_mode;                          //ARMģʽ��־λ
extern short sensor_mode;                       //��ʾ��ģʽ��־λ
extern short remote_mode;
extern short fix_height_mode;                      //����������ģʽ

extern char last[3];                            //�洢���3�����յ�����Ϣ

extern unsigned char tmp[30];                  //�����ַ�ת��

extern uint64_t now_time;
extern uint64_t get_time;
extern uint64_t hc_error_flag;
extern uint64_t hc_time;
extern float dis;
extern float last_dis;
extern float sum_dis;
extern float fix_dis;
float now_dis;
uint64_t break_flag=0;

extern short throttle;

//extern float temp;


//extern char txt[30];
//extern char *a;



/*---------------------------------------------------------------
����    ����PORTB_Interrupt
����    �ܡ�PORTB�˿ڵ��жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/
void PORTB_IRQHandler()
{
  
  /* �ж�ʹ�õ����źţ�����ֻд�˹ܽ�20�͹ܽ�21��22��ʹ�������ܽſ���������� */
  int n;  
  n=20;
  if((PORTB_ISFR & (1<<n)))
  {
    /* �û���������ж��ڳ��� */
    key_exti_flag = 0;
  } 
  n=21;
  if((PORTB_ISFR & (1<<n)))
  {
    /* �û���������ж��ڳ��� */
    key_exti_flag = 1;
  } 
  n=22;
  if((PORTB_ISFR & (1<<n)))
  {
    /* �û���������ж��ڳ��� */
    key_exti_flag = 2;
  }
  //����жϱ�־
  PORTB_ISFR = 0xffffffff;
}


//------------------------------------------------------------------------------------------------    
//ȫ�ֱ���  ���ڲ���PIT��ʱ��
//------------------------------------------------------------------------------------------------ 
extern volatile uint8_t pit0_test_flag;
extern volatile uint8_t pit1_test_flag;
extern volatile uint8_t pit2_test_flag;
extern volatile uint8_t pit3_test_flag;

/*---------------------------------------------------------------
����    ����PIT0_Interrupt
����    �ܡ�PIT0���жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/

void PIT0_IRQHandler()
{  
  /////////////////////////////////////////////////////////////////
  //////////////////�����Ǻͼ��ٶȼƴ�����/////////////////////////
  /////////////////////////////////////////////////////////////////
  
  
  PIT_Flag_Clear(PIT0);                       //���жϱ�־λ
  pit0_test_flag = 1;
  
//  MPU_Get_Accelerometer(&aac_x,&aac_y,&aac_z);//�õ����ٶȴ�����ԭʼ����
//  MPU_Get_Gyroscope(&gyro_x,&gyro_y,&gyro_z); //�õ�������ԭʼ����
  
  last_pitch = pitch;
  last_roll = roll;
  last_yaw = yaw;
  mpu_dmp_get_data(&pitch,&roll,&yaw);
  if(throttle > 0)
  {
    sum_pitch += pitch;
    sum_roll += roll;
    sum_yaw += yaw;
  }
  else
  {
    sum_pitch = 0;
    sum_roll = 0;
    sum_yaw = 0;
  }

  /////////////////////////////////////////////////////////////////
  //////////////////�����Ǻͼ��ٶȼ�У��ˮƽ///////////////////////
  /////////////////////////////////////////////////////////////////

//  if(ang_set_flag==3)
//  {
//    Ang_sum_x += Ang_Acc_x;
//    Ang_sum_y += Ang_Acc_y;
//    Ang_sum_z += Ang_Acc_z;
//    gyro_sum_x += gyro_x;
//    gyro_sum_y += gyro_y;
//    gyro_sum_z += gyro_z;
//    ang_i++;
//    if(ang_i>=100)
//      ang_set_flag = 2;
//  }
//  if(ang_set_flag==1)
//  {
//    if(++ang_i>=100)
//      ang_set_flag = 0;
//  }
  
  /////////////////////////////////////////////////////////////////
  ////////////////////////��ʾ�����///////////////////////////////
  /////////////////////////////////////////////////////////////////
  
  OLED_P8x16Str(0,0,"Listening...");  //״̬��Listening..
  
  /* ��ʾ����ʾARMģʽ */
  if(arm_mode == 0)                     //δ����״̬
  {
    OLED_P6x8Str(0,2,"DISARM");       //��ʾ����ʾDISARM
  }
  if(arm_mode == 1)                     //����״̬
  {
    OLED_P6x8Str(0,2,"ARM   ");          //��ʾ����ʾARM
  }
  
  /* ��ʾ��������ģʽ */
  if(sensor_mode == 0)
  {
    OLED_P6x8Str(0,3,"UART  ");//��ʾ����ʾUART
    /* ��ʾ��������յ���3������ */
    sprintf((char*)tmp,"last[0]:%c",last[0]);
    OLED_P6x8Str(50,2,tmp);
    sprintf((char*)tmp,"last[1]:%c",last[1]);
    OLED_P6x8Str(50,3,tmp);
    sprintf((char*)tmp,"last[2]:%c",last[2]);
    OLED_P6x8Str(50,4,tmp);
  }
  /* ��ʾ����������ģʽ */
  if(sensor_mode == 1)  
  {
    OLED_P6x8Str(0,3,"Sensor");//��ʾ����ʾSensor
    /* ��ʾŷ���� */
    sprintf((char*)tmp,"Pitch:%.3f",pitch);
    OLED_P6x8Str(50,2,tmp);
    sprintf((char*)tmp,"Roll:%.3f",roll);
    OLED_P6x8Str(50,3,tmp);
    sprintf((char*)tmp,"Yaw:%.3f",yaw);
    OLED_P6x8Str(50,4,tmp);   

    /* ��ʾ���������� */
    switch(hc_error_flag){
    case 0:/*�������*/
      sprintf((char*)tmp,"Dis:%.2f   ",dis);
      tmp[11] = '\0';                           //��ֹtmp���ȹ�����Ӱ�����
      OLED_P6x8Str(50,5,tmp);
      break;
    case 1:/*�޶��������Error*/
      sprintf((char*)tmp,"Dis:Error!");
      OLED_P6x8Str(50,5,tmp);
      break;
    case 2:/*���Low*/
      sprintf((char*)tmp,"Dis:Low!  ");
      OLED_P6x8Str(50,5,tmp);
      break;
    case 3:/*���High*/
      sprintf((char*)tmp,"Dis:High! ");
      OLED_P6x8Str(50,5,tmp);
      break;
    }
  }
  
  /* ��ʾң��ģʽ */
  if(remote_mode == 1)
    OLED_P6x8Str(0,4,"remote");
  else if(remote_mode == 0)
    OLED_P6x8Str(0,4,"      ");
  
  /* ��ʾ���ƫת */
  if(steer_left_duty>steer_left_duty_mid){
    sprintf((char*)tmp,"S:L%5.1f ",(float)(steer_left_duty-steer_left_duty_mid)/(steer_left_duty_front-steer_left_duty_mid)*100);
    OLED_P6x8Str(0,6,tmp);
  }
  if(steer_left_duty<=steer_left_duty_mid){
    sprintf((char*)tmp,"S:L%5.1f ",-(float)(steer_left_duty-steer_left_duty_mid)/(steer_left_duty_rear-steer_left_duty_mid)*100);
    OLED_P6x8Str(0,6,tmp);
  }
  if(steer_right_duty<=steer_left_duty_mid){
    sprintf((char*)tmp,"R%5.1f ",(float)(steer_right_duty-steer_right_duty_mid)/(steer_right_duty_front-steer_right_duty_mid)*100);
    OLED_P6x8Str(60,6,tmp);
  }
  if(steer_left_duty>steer_left_duty_mid){
    sprintf((char*)tmp,"R%5.1f ",-(float)(steer_right_duty-steer_right_duty_mid)/(steer_right_duty_rear-steer_right_duty_mid)*100);
    OLED_P6x8Str(60,6,tmp);
  }
  
  /* ��ʾ������� */
  if(motor_left_duty>motor_left_duty_start){
    sprintf((char*)tmp,"M:L%5.1f ",(float)(motor_left_duty-motor_left_duty_start)/(motor_left_duty_full-motor_left_duty_start)*100);
    OLED_P6x8Str(0,7,tmp);
  }
  if(motor_left_duty<=motor_left_duty_start){
    sprintf((char*)tmp,"M:L%5.1f ",0.0);
    OLED_P6x8Str(0,7,tmp);
  }
  if(motor_right_duty>motor_right_duty_start){
    sprintf((char*)tmp,"R%5.1f ",(float)(motor_right_duty-motor_right_duty_start)/(motor_right_duty_full-motor_right_duty_start)*100);
    OLED_P6x8Str(60,7,tmp);
  }
  if(motor_right_duty<=motor_right_duty_start){
    sprintf((char*)tmp,"R%5.1f ",0.0);
    OLED_P6x8Str(60,7,tmp);
  }
  
    LED_Reverse(2);     //LED2��תָʾ��������������
  
  
  //  if(Check_Speed>0)slow();
  //  if(Check_Speed<0)fast();
  
  //  P=Ang*150;//�ٶ�ֵ������Ϊ��������Ϊ��    //�Ƕȣ�ǰ��Ϊ��������Ϊ��////////////////////////////////////////////////////
  //  D=0.1;
  //  P=Ang*250;//�ٶ�ֵ������Ϊ��������Ϊ��    //�Ƕȣ�ǰ��Ϊ��������Ϊ��////////////////////////////////////////////////////
  //  D=gyroy*0.1;
  //  Speed_L = P - D;   //Kp*Ang���ظ���) +  Kd*y������ٶȣ���������
  //  LowerComputer();   //���͵���λ��
  //  UpperMonitor();    //���͵���λ��    
  //  Go(Speed_L); 
  
}

/*---------------------------------------------------------------
����    ����PIT1_Interrupt
����    �ܡ�PIT1���жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/
void PIT1_IRQHandler()
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
  /*�û�����������*/
  pit1_test_flag = 1;  
  /////////////////////////////////////////////////////////////////
  ///////////////////////������������//////////////////////////////
  /////////////////////////////////////////////////////////////////
  
  last_dis = dis;
  if(fix_height_mode == 1)
    sum_dis +=dis - fix_dis; 
  
  /* HC_TRIG ����8-15us�ĸߵ�ƽ������ʹ���ź� */
  GPIO_PinWrite(HC_TRIG, 1);
  systime.delay_us(10);
  GPIO_PinWrite(HC_TRIG, 0);
  
  hc_error_flag = 0;
  
  /* �ȴ�������ģ�鿪ʼ���ͻش��ź� */
  while(!GPIO_PinRead(HC_ECHO))                 //�ȴ��ش��źſ�ʼ
  {
    systime.delay_us(1);
    break_flag++;
    if(break_flag >= 24000)      
    {
      hc_error_flag = 1;
      break;
    }
  }
  break_flag = 0;
  if(hc_error_flag == 0)
  {
    hc_time = systime.get_time_us();             //��¼�ߵ�ƽʱ��
    while(GPIO_PinRead(HC_ECHO))                //�ȴ��ش��źŽ���
    {
      systime.delay_us(1);
      break_flag++;
      if(break_flag>=24000)      
      {
        hc_error_flag = 1;
        break;
      }
    }              
    hc_time = systime.get_time_us() - hc_time;  //��¼�ߵ�ƽʱ��
    now_dis = (float)hc_time * 0.017;          //������� (hc_time*340/2) m/s
    
    /* ���������Զ��ȥ����Чֵ */
    if(now_dis < 2 || now_dis > 200||break_flag>=24000)
    {
      /* ������һ�ζ���ȷ��������Чԭ�� */
      if(dis<20)hc_error_flag = 2;              //���ڿ���
      else if(dis>60)hc_error_flag = 3;        //����Զ��
    }
    else
      dis = now_dis;                            //������Чֵ
  }
  
    LED_Reverse(3);//LED3��תָʾ����������������
}
/*---------------------------------------------------------------
����    ����PIT2_Interrupt
����    �ܡ�PIT2���жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/
void PIT2_IRQHandler()
{
  PIT_Flag_Clear(PIT2);       //���жϱ�־λ
  /*�û�����������*/
  pit2_test_flag = 1;
}
/*---------------------------------------------------------------
����    ����PIT3_Interrupt
����    �ܡ�PIT3���жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/
void PIT3_IRQHandler()
{
  PIT_Flag_Clear(PIT3);       //���жϱ�־λ
  /*�û�����������*/
  LED_Reverse(3);
}


/////////////////////////////////////////////////////////////////
///////////////�����жϷ�����/////////////////////////////////
/////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------
����    ����DMA_CH4_Handler
����    �ܡ�DMAͨ��4���жϷ�����
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/

void UART4_RX_TX_IRQHandler(void)
{
  if(UART4_S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
  {
    //�û���Ҫ�����������
    
    //printf("���յ��ַ��� %c \n", UART_GetChar(UART4));

    ANO_DT_Data_Receive_Prepare(UART_GetChar(UART4));
    
  }
  
}