/*---------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】中断服务函数
【注意事项】中断服务函数的名称在startup_MK60D10.s 中
----------------------------------------------------------------*/
#include "include.h"

#define HC_TRIG   PTE9   //驱动发射信号引脚
#define HC_ECHO   PTE10  //输出高电平引脚

//------------------------------------------------------------------------------------------------    
//全局变量  用于测试按键外部中断
//------------------------------------------------------------------------------------------------
extern volatile uint8_t key_exti_flag;

extern short steer_left_duty;                   //左舵机
extern short steer_right_duty;                  //右舵机
extern short motor_left_duty;                   //左电机
extern short motor_right_duty;                  //右电机

extern short aac_x, aac_y, aac_z;               //加速度原始数据
extern short gyro_x, gyro_y, gyro_z;            //陀螺仪原始数据
extern float pitch,roll,yaw;                    //欧拉角
extern float last_pitch, last_roll, last_yaw;
extern float sum_pitch, sum_roll, sum_yaw;
extern short pitch_fix, roll_fix, yaw_fix;

extern short ang_set_flag;                    //校验水平标志
extern short ang_i;                           //计数变量

extern float Ang_sum_x, Ang_sum_y, Ang_sum_z;   //加速度计水平误差和
extern float gyro_sum_x, gyro_sum_y, gyro_sum_z;//陀螺仪静态偏差和
extern float IGyro_x_init, IGyro_y_init, IGyro_z_init;//陀螺仪积分后的角度初值

extern float dis;                               //超声波数据

extern short arm_mode;                          //ARM模式标志位
extern short sensor_mode;                       //显示屏模式标志位
extern short remote_mode;
extern short fix_height_mode;                      //超声波定高模式

extern char last[3];                            //存储最近3条接收到的消息

extern unsigned char tmp[30];                  //用于字符转换

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
【函    数】PORTB_Interrupt
【功    能】PORTB端口的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/
void PORTB_IRQHandler()
{
  
  /* 中断使用的引脚号，这里只写了管脚20和管脚21和22，使用其他管脚可以自行添加 */
  int n;  
  n=20;
  if((PORTB_ISFR & (1<<n)))
  {
    /* 用户自行添加中断内程序 */
    key_exti_flag = 0;
  } 
  n=21;
  if((PORTB_ISFR & (1<<n)))
  {
    /* 用户自行添加中断内程序 */
    key_exti_flag = 1;
  } 
  n=22;
  if((PORTB_ISFR & (1<<n)))
  {
    /* 用户自行添加中断内程序 */
    key_exti_flag = 2;
  }
  //清除中断标志
  PORTB_ISFR = 0xffffffff;
}


//------------------------------------------------------------------------------------------------    
//全局变量  用于测试PIT定时器
//------------------------------------------------------------------------------------------------ 
extern volatile uint8_t pit0_test_flag;
extern volatile uint8_t pit1_test_flag;
extern volatile uint8_t pit2_test_flag;
extern volatile uint8_t pit3_test_flag;

/*---------------------------------------------------------------
【函    数】PIT0_Interrupt
【功    能】PIT0的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/

void PIT0_IRQHandler()
{  
  /////////////////////////////////////////////////////////////////
  //////////////////陀螺仪和加速度计传感器/////////////////////////
  /////////////////////////////////////////////////////////////////
  
  
  PIT_Flag_Clear(PIT0);                       //清中断标志位
  pit0_test_flag = 1;
  
//  MPU_Get_Accelerometer(&aac_x,&aac_y,&aac_z);//得到加速度传感器原始数据
//  MPU_Get_Gyroscope(&gyro_x,&gyro_y,&gyro_z); //得到陀螺仪原始数据
  
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
  //////////////////陀螺仪和加速度计校验水平///////////////////////
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
  ////////////////////////显示屏输出///////////////////////////////
  /////////////////////////////////////////////////////////////////
  
  OLED_P8x16Str(0,0,"Listening...");  //状态栏Listening..
  
  /* 显示屏显示ARM模式 */
  if(arm_mode == 0)                     //未解锁状态
  {
    OLED_P6x8Str(0,2,"DISARM");       //显示屏显示DISARM
  }
  if(arm_mode == 1)                     //解锁状态
  {
    OLED_P6x8Str(0,2,"ARM   ");          //显示屏显示ARM
  }
  
  /* 显示串口数据模式 */
  if(sensor_mode == 0)
  {
    OLED_P6x8Str(0,3,"UART  ");//显示屏显示UART
    /* 显示最近串口收到的3个数据 */
    sprintf((char*)tmp,"last[0]:%c",last[0]);
    OLED_P6x8Str(50,2,tmp);
    sprintf((char*)tmp,"last[1]:%c",last[1]);
    OLED_P6x8Str(50,3,tmp);
    sprintf((char*)tmp,"last[2]:%c",last[2]);
    OLED_P6x8Str(50,4,tmp);
  }
  /* 显示传感器数据模式 */
  if(sensor_mode == 1)  
  {
    OLED_P6x8Str(0,3,"Sensor");//显示屏显示Sensor
    /* 显示欧拉角 */
    sprintf((char*)tmp,"Pitch:%.3f",pitch);
    OLED_P6x8Str(50,2,tmp);
    sprintf((char*)tmp,"Roll:%.3f",roll);
    OLED_P6x8Str(50,3,tmp);
    sprintf((char*)tmp,"Yaw:%.3f",yaw);
    OLED_P6x8Str(50,4,tmp);   

    /* 显示超声波数据 */
    switch(hc_error_flag){
    case 0:/*正常输出*/
      sprintf((char*)tmp,"Dis:%.2f   ",dis);
      tmp[11] = '\0';                           //防止tmp长度过长，影响输出
      OLED_P6x8Str(50,5,tmp);
      break;
    case 1:/*无读数则输出Error*/
      sprintf((char*)tmp,"Dis:Error!");
      OLED_P6x8Str(50,5,tmp);
      break;
    case 2:/*输出Low*/
      sprintf((char*)tmp,"Dis:Low!  ");
      OLED_P6x8Str(50,5,tmp);
      break;
    case 3:/*输出High*/
      sprintf((char*)tmp,"Dis:High! ");
      OLED_P6x8Str(50,5,tmp);
      break;
    }
  }
  
  /* 显示遥控模式 */
  if(remote_mode == 1)
    OLED_P6x8Str(0,4,"remote");
  else if(remote_mode == 0)
    OLED_P6x8Str(0,4,"      ");
  
  /* 显示舵机偏转 */
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
  
  /* 显示电机功率 */
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
  
    LED_Reverse(2);     //LED2反转指示陀螺仪正常运行
  
  
  //  if(Check_Speed>0)slow();
  //  if(Check_Speed<0)fast();
  
  //  P=Ang*150;//速度值：慢了为负，快了为正    //角度：前倾为正，后倾为负////////////////////////////////////////////////////
  //  D=0.1;
  //  P=Ang*250;//速度值：慢了为负，快了为正    //角度：前倾为正，后倾为负////////////////////////////////////////////////////
  //  D=gyroy*0.1;
  //  Speed_L = P - D;   //Kp*Ang（回复力) +  Kd*y方向角速度（阻尼力）
  //  LowerComputer();   //发送到下位机
  //  UpperMonitor();    //发送到上位机    
  //  Go(Speed_L); 
  
}

/*---------------------------------------------------------------
【函    数】PIT1_Interrupt
【功    能】PIT1的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/
void PIT1_IRQHandler()
{
  PIT_Flag_Clear(PIT1);       //清中断标志位
  /*用户添加所需代码*/
  pit1_test_flag = 1;  
  /////////////////////////////////////////////////////////////////
  ///////////////////////超声波传感器//////////////////////////////
  /////////////////////////////////////////////////////////////////
  
  last_dis = dis;
  if(fix_height_mode == 1)
    sum_dis +=dis - fix_dis; 
  
  /* HC_TRIG 保持8-15us的高电平，发出使能信号 */
  GPIO_PinWrite(HC_TRIG, 1);
  systime.delay_us(10);
  GPIO_PinWrite(HC_TRIG, 0);
  
  hc_error_flag = 0;
  
  /* 等待超声波模块开始发送回传信号 */
  while(!GPIO_PinRead(HC_ECHO))                 //等待回传信号开始
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
    hc_time = systime.get_time_us();             //记录高电平时长
    while(GPIO_PinRead(HC_ECHO))                //等待回传信号结束
    {
      systime.delay_us(1);
      break_flag++;
      if(break_flag>=24000)      
      {
        hc_error_flag = 1;
        break;
      }
    }              
    hc_time = systime.get_time_us() - hc_time;  //记录高电平时长
    now_dis = (float)hc_time * 0.017;          //计算距离 (hc_time*340/2) m/s
    
    /* 若过近或过远，去除无效值 */
    if(now_dis < 2 || now_dis > 200||break_flag>=24000)
    {
      /* 根据上一次读数确定读数无效原因 */
      if(dis<20)hc_error_flag = 2;              //过于靠近
      else if(dis>60)hc_error_flag = 3;        //过于远离
    }
    else
      dis = now_dis;                            //保留有效值
  }
  
    LED_Reverse(3);//LED3反转指示超声波的正常运行
}
/*---------------------------------------------------------------
【函    数】PIT2_Interrupt
【功    能】PIT2的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/
void PIT2_IRQHandler()
{
  PIT_Flag_Clear(PIT2);       //清中断标志位
  /*用户添加所需代码*/
  pit2_test_flag = 1;
}
/*---------------------------------------------------------------
【函    数】PIT3_Interrupt
【功    能】PIT3的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/
void PIT3_IRQHandler()
{
  PIT_Flag_Clear(PIT3);       //清中断标志位
  /*用户添加所需代码*/
  LED_Reverse(3);
}


/////////////////////////////////////////////////////////////////
///////////////串口中断服务函数/////////////////////////////////
/////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------
【函    数】DMA_CH4_Handler
【功    能】DMA通道4的中断服务函数
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/

void UART4_RX_TX_IRQHandler(void)
{
  if(UART4_S1 & UART_S1_RDRF_MASK)                                     //接收数据寄存器满
  {
    //用户需要处理接收数据
    
    //printf("接收到字符： %c \n", UART_GetChar(UART4));

    ANO_DT_Data_Receive_Prepare(UART_GetChar(UART4));
    
  }
  
}