#include "include.h"

extern volatile short aac_x, aac_y, aac_z;               //加速度原始数据
extern volatile short gyro_x, gyro_y, gyro_z;            //陀螺仪原始数据
extern volatile float Ang_Set_x, Ang_Set_y, Ang_Set_z;   //加速度计水平误差
extern volatile short gyro_set_x, gyro_set_y, gyro_set_z;//陀螺仪静态误差
extern volatile float Ang_Acc_x, Ang_Acc_y, Ang_Acc_z;   //加速度计各轴数据
extern volatile float Ang_IGyro_x, Ang_IGyro_y, Ang_IGyro_z;//陀螺仪积分后的角度
extern volatile float IGyro_x_set, IGyro_y_set, IGyro_z_set;//陀螺仪积分后的角度补偿值
extern volatile float skt_x, skt_y, skt_z;               //中间变量，用来看滤波前的值
extern volatile float Ang_Error_x, Ang_Error_y, Ang_Error_z;//互补滤波中间值
extern volatile float Ang_x, Ang_y, Ang_z;               //欧拉角

extern volatile short ang_set_flag;                    //校验水平标志
extern volatile short ang_i;                           //计数变量

extern volatile float Ang_sum_x, Ang_sum_y, Ang_sum_z;   //加速度计水平误差和
extern volatile float gyro_sum_x, gyro_sum_y, gyro_sum_z;//陀螺仪静态偏差和
extern volatile float IGyro_x_init, IGyro_y_init, IGyro_z_init;//陀螺仪积分后的角度初值


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】读取 MPU6050 的原始数据
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无 0：初始化成功   1：失败
【参数值】无 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_TFT1_8
void Test_MPU6050(void)
{
    TFTSPI_Init(1);                //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    UART_Init(UART4, 115200);
    char  txt[30];
    short aacx,aacy,aacz;	        //加速度传感器原始数据
    short gyrox,gyroy,gyroz;        //陀螺仪原始数据 
    TFTSPI_P8X16Str(2,0,"LQ 6050 Test",u16RED,u16BLUE);
    printf("\nLQ MPU6050 Test");
    if(MPU6050_Init())
    {
        TFTSPI_P8X16Str(2,0,"6050 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据  
        sprintf((char*)txt,"ax:%06d",aacx);
        TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"ay:%06d",aacy);
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"az:%06d",aacz);
        TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gx:%06d",gyrox);
        TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gy:%06d",gyroy);
        TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gz:%06d",gyroz);
        TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLUE);

        printf("\r\nAX: %d  ",aacx); 
        printf("\r\nAY: %d  ",aacy);
        printf("\r\nAZ: %d  ",aacz); 
        printf("\r\nGX: %d  ",gyrox);
        printf("\r\nGY: %d  ",gyroy); 
        printf("\r\nGZ: %d  ",gyroz);
        delayms(100);
        printf("*********************");
    }
    
}
#endif
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】读取 MPU6050 的原始数据
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无 0：初始化成功   1：失败
【参数值】无 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_OLED
void Test_MPU6050(void)
{
    unsigned char txt[30];
    short aacx,aacy,aacz;	        //加速度传感器原始数据
    short gyrox,gyroy,gyroz;        //陀螺仪原始数据
    UART_Init(UART4, 115200);
    OLED_Init();                  //LCD初始化
    OLED_CLS();                   //LCD清屏
    OLED_P8x16Str(15,0,"LQ 6050 Test"); 
    printf("\r\nLQ 6050 Test");
    
    if(MPU6050_Init())
    {
        OLED_P8x16Str(15,2,"6050 Init Fail");
        while(1);
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据  
        sprintf((char*)txt,"ax:%06d",aacx);
        OLED_P6x8Str(0,2,txt);
        sprintf((char*)txt,"ay:%06d",aacy);
        OLED_P6x8Str(0,3,txt);
        sprintf((char*)txt,"az:%06d",aacz);
        OLED_P6x8Str(0,4,txt);
        sprintf((char*)txt,"gx:%06d",gyrox);
        OLED_P6x8Str(0,5,txt);
        sprintf((char*)txt,"gy:%06d",gyroy);
        OLED_P6x8Str(0,6,txt);
        sprintf((char*)txt,"gz:%06d",gyroz);
        OLED_P6x8Str(0,7,txt);

        printf("\r\nAX: %d  ",aacx); 
        printf("\r\nAY: %d  ",aacy);
        printf("\r\nAZ: %d  ",aacz); 
        printf("\r\nGX: %d  ",gyrox);
        printf("\r\nGY: %d  ",gyroy); 
        printf("\r\nGZ: %d  ",gyroz);
        delayms(100);
        printf("*********************");
    }
    
}
#endif

//void Set_MPU6050(void)
//{
//  /* 蜂鸣器响2秒 */
//  GPIO_PinInit(PTC17, GPO, 1);
//  delayms(1000);
//  GPIO_PinInit(PTC17, GPO, 0);
//  
//        /* 加速度计和陀螺仪校验水平 */
//        ang_i = 0;                      //各变量初始化
//        Ang_sum_x = 0;
//        Ang_sum_y = 0;
//        Ang_sum_z = 0;
//        gyro_sum_x = 0;
//        gyro_sum_y = 0;
//        gyro_sum_z = 0;
//        ang_set_flag = 3;               //进行收集加速度计和陀螺仪原始数据
//        while(ang_set_flag!=2);         //等待收集结束
//        Ang_Set_x = Ang_Set_x+Ang_sum_x/ang_i;   
//        Ang_Set_y = Ang_Set_y+Ang_sum_y/ang_i;
//        Ang_Set_z = Ang_Set_z+Ang_sum_z/ang_i;
//        gyro_set_x = gyro_set_x+gyro_sum_x/ang_i;
//        gyro_set_y = gyro_set_y+gyro_sum_y/ang_i;
//        gyro_set_z = gyro_set_z+gyro_sum_z/ang_i;
//        
//        IGyro_x_init = Ang_IGyro_x;     //各变量初始化
//        IGyro_y_init = Ang_IGyro_y;
//        IGyro_z_init = Ang_IGyro_z;
//        ang_i = 0;
//        ang_set_flag = 1;               //等待角度积分值
//        while(ang_set_flag!=0);
//        
//        IGyro_x_set = IGyro_x_set+(Ang_IGyro_x-IGyro_x_init)/ang_i;
//        IGyro_y_set = IGyro_y_set+(Ang_IGyro_y-IGyro_y_init)/ang_i;
//        IGyro_z_set = IGyro_z_set+(Ang_IGyro_z-IGyro_z_init)/ang_i;
//        
//        Ang_IGyro_x = 0;
//        Ang_IGyro_y = 0;
//        Ang_IGyro_z = 0;
//        /* 蜂鸣器响2秒 */
//        GPIO_PinInit(PTC17, GPO, 1);
//        delayms(1000);
//        GPIO_PinInit(PTC17, GPO, 0);
//}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】初始化 MPU6050
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无 0：初始化成功   1：失败
【参数值】无 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t MPU6050_Init(void)
{
    uint8_t res;
    IIC_Init();                                         //MPU6050 支持400K I2C
    res=MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);           //读取MPU6050的ID
    if(res!=MPU6050_ID)                                 //器件ID正确
    {
        printf("ID=%#X?",res);
        printf("MPU6050 is fail!?");
    }
    else  printf("MPU6050 is OK!?");

    res = 0;
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU6050
    delayms(100);  //延时100ms
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU6050
    res += MPU_Set_Gyro_Fsr(3);					        	   //陀螺仪传感器,±2000dps   
    res += MPU_Set_Accel_Fsr(1);					       	   //加速度传感器,±4g
    res += MPU_Set_Rate(1000);						       	   //设置采样率1000Hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //设置数字低通滤波器   98hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作
    
    if(res == 0)  //上面寄存器都写入成功
    {
        printf("MPU set is OK!?");
    }
    else return 1;
    
    return 0;
}

//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}

//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature(void)
{
    uint8_t buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU6050_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((uint16_t)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return (short)temp*100;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[6],res; 
	res=MPU_Read_Len(MPU6050_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16_t)buf[0]<<8)|buf[1];  
		*gy=((uint16_t)buf[2]<<8)|buf[3];  
		*gz=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[6],res;  
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];  
		*ay=((uint16_t)buf[2]<<8)|buf[3];  
		*az=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;
}

//得到加计值、温度值、角速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
    uint8_t buf[14],res;  
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];  
		*ay=((uint16_t)buf[2]<<8)|buf[3];  
		*az=((uint16_t)buf[4]<<8)|buf[5];
                *gx=((uint16_t)buf[8]<<8)|buf[9];  
		*gy=((uint16_t)buf[10]<<8)|buf[11];  
		*gz=((uint16_t)buf[12]<<8)|buf[13];
	} 	
    return res;
}


//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
  uint8_t i; 
  IIC_Start(); 
  IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
  if(IIC_WaitAck())	//等待应答
  {
    IIC_Stop();		 
    return 1;		
  }
  IIC_SendByte(reg);	//写寄存器地址
  IIC_WaitAck();		//等待应答
  for(i=0;i<len;i++)
  {
    IIC_SendByte(buf[i]);	//发送数据
    if(IIC_WaitAck())		//等待ACK
    {
      IIC_Stop();	 
      return 1;		 
    }		
  }    
  IIC_Stop();	 
  return 0;
    //return IIC_WriteMultByteToSlave(addr, reg, len, buf);
} 

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
  IIC_Start(); 
  IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
  if(IIC_WaitAck())	//等待应答
  {
    IIC_Stop();		 
    return 1;		
  }
  IIC_SendByte(reg);	//写寄存器地址
  IIC_WaitAck();		//等待应答
  IIC_Start();
  IIC_SendByte((addr<<1)|1);//发送器件地址+读命令	
  IIC_WaitAck();		//等待应答 
  while(len)
  {
    if(len==1)*buf=IIC_ReadByte(0);//读数据,发送nACK 
    else *buf=IIC_ReadByte(1);		//读数据,发送ACK  
    len--;
    buf++; 
  }    
  IIC_Stop();	//产生一个停止条件 
  return 0;	
    //return IIC_ReadMultByteFromSlave(addr, reg, len, buf);     
}


//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t value)
{
    return IIC_WriteByteToSlave(addr, reg, value);
}

//IIC读一个字节 
//reg:寄存器地址 
//返回值:读到的数据
uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t value;
    IIC_ReadByteFromSlave(addr, reg, &value);
    return value;
}






