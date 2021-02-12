#include "include.h"

extern volatile short aac_x, aac_y, aac_z;               //���ٶ�ԭʼ����
extern volatile short gyro_x, gyro_y, gyro_z;            //������ԭʼ����
extern volatile float Ang_Set_x, Ang_Set_y, Ang_Set_z;   //���ٶȼ�ˮƽ���
extern volatile short gyro_set_x, gyro_set_y, gyro_set_z;//�����Ǿ�̬���
extern volatile float Ang_Acc_x, Ang_Acc_y, Ang_Acc_z;   //���ٶȼƸ�������
extern volatile float Ang_IGyro_x, Ang_IGyro_y, Ang_IGyro_z;//�����ǻ��ֺ�ĽǶ�
extern volatile float IGyro_x_set, IGyro_y_set, IGyro_z_set;//�����ǻ��ֺ�ĽǶȲ���ֵ
extern volatile float skt_x, skt_y, skt_z;               //�м�������������˲�ǰ��ֵ
extern volatile float Ang_Error_x, Ang_Error_y, Ang_Error_z;//�����˲��м�ֵ
extern volatile float Ang_x, Ang_y, Ang_z;               //ŷ����

extern volatile short ang_set_flag;                    //У��ˮƽ��־
extern volatile short ang_i;                           //��������

extern volatile float Ang_sum_x, Ang_sum_y, Ang_sum_z;   //���ٶȼ�ˮƽ����
extern volatile float gyro_sum_x, gyro_sum_y, gyro_sum_z;//�����Ǿ�̬ƫ���
extern volatile float IGyro_x_init, IGyro_y_init, IGyro_z_init;//�����ǻ��ֺ�ĽǶȳ�ֵ


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ȡ MPU6050 ��ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_TFT1_8
void Test_MPU6050(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    UART_Init(UART4, 115200);
    char  txt[30];
    short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
    short gyrox,gyroy,gyroz;        //������ԭʼ���� 
    TFTSPI_P8X16Str(2,0,"LQ 6050 Test",u16RED,u16BLUE);
    printf("\nLQ MPU6050 Test");
    if(MPU6050_Init())
    {
        TFTSPI_P8X16Str(2,0,"6050 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
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
����  �ߡ�LQ-005
������˵������ȡ MPU6050 ��ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_OLED
void Test_MPU6050(void)
{
    unsigned char txt[30];
    short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
    short gyrox,gyroy,gyroz;        //������ԭʼ����
    UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
    OLED_P8x16Str(15,0,"LQ 6050 Test"); 
    printf("\r\nLQ 6050 Test");
    
    if(MPU6050_Init())
    {
        OLED_P8x16Str(15,2,"6050 Init Fail");
        while(1);
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
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
//  /* ��������2�� */
//  GPIO_PinInit(PTC17, GPO, 1);
//  delayms(1000);
//  GPIO_PinInit(PTC17, GPO, 0);
//  
//        /* ���ٶȼƺ�������У��ˮƽ */
//        ang_i = 0;                      //��������ʼ��
//        Ang_sum_x = 0;
//        Ang_sum_y = 0;
//        Ang_sum_z = 0;
//        gyro_sum_x = 0;
//        gyro_sum_y = 0;
//        gyro_sum_z = 0;
//        ang_set_flag = 3;               //�����ռ����ٶȼƺ�������ԭʼ����
//        while(ang_set_flag!=2);         //�ȴ��ռ�����
//        Ang_Set_x = Ang_Set_x+Ang_sum_x/ang_i;   
//        Ang_Set_y = Ang_Set_y+Ang_sum_y/ang_i;
//        Ang_Set_z = Ang_Set_z+Ang_sum_z/ang_i;
//        gyro_set_x = gyro_set_x+gyro_sum_x/ang_i;
//        gyro_set_y = gyro_set_y+gyro_sum_y/ang_i;
//        gyro_set_z = gyro_set_z+gyro_sum_z/ang_i;
//        
//        IGyro_x_init = Ang_IGyro_x;     //��������ʼ��
//        IGyro_y_init = Ang_IGyro_y;
//        IGyro_z_init = Ang_IGyro_z;
//        ang_i = 0;
//        ang_set_flag = 1;               //�ȴ��ǶȻ���ֵ
//        while(ang_set_flag!=0);
//        
//        IGyro_x_set = IGyro_x_set+(Ang_IGyro_x-IGyro_x_init)/ang_i;
//        IGyro_y_set = IGyro_y_set+(Ang_IGyro_y-IGyro_y_init)/ang_i;
//        IGyro_z_set = IGyro_z_set+(Ang_IGyro_z-IGyro_z_init)/ang_i;
//        
//        Ang_IGyro_x = 0;
//        Ang_IGyro_y = 0;
//        Ang_IGyro_z = 0;
//        /* ��������2�� */
//        GPIO_PinInit(PTC17, GPO, 1);
//        delayms(1000);
//        GPIO_PinInit(PTC17, GPO, 0);
//}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ�� MPU6050
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 0����ʼ���ɹ�   1��ʧ��
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t MPU6050_Init(void)
{
    uint8_t res;
    IIC_Init();                                         //MPU6050 ֧��400K I2C
    res=MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);           //��ȡMPU6050��ID
    if(res!=MPU6050_ID)                                 //����ID��ȷ
    {
        printf("ID=%#X?",res);
        printf("MPU6050 is fail!?");
    }
    else  printf("MPU6050 is OK!?");

    res = 0;
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU6050
    delayms(100);  //��ʱ100ms
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU6050
    res += MPU_Set_Gyro_Fsr(3);					        	   //�����Ǵ�����,��2000dps   
    res += MPU_Set_Accel_Fsr(1);					       	   //���ٶȴ�����,��4g
    res += MPU_Set_Rate(1000);						       	   //���ò�����1000Hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����
    
    if(res == 0)  //����Ĵ�����д��ɹ�
    {
        printf("MPU set is OK!?");
    }
    else return 1;
    
    return 0;
}

//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}

//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}

//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
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
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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

//�õ��Ӽ�ֵ���¶�ֵ�����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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


//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
  uint8_t i; 
  IIC_Start(); 
  IIC_SendByte((addr<<1)|0);//����������ַ+д����	
  if(IIC_WaitAck())	//�ȴ�Ӧ��
  {
    IIC_Stop();		 
    return 1;		
  }
  IIC_SendByte(reg);	//д�Ĵ�����ַ
  IIC_WaitAck();		//�ȴ�Ӧ��
  for(i=0;i<len;i++)
  {
    IIC_SendByte(buf[i]);	//��������
    if(IIC_WaitAck())		//�ȴ�ACK
    {
      IIC_Stop();	 
      return 1;		 
    }		
  }    
  IIC_Stop();	 
  return 0;
    //return IIC_WriteMultByteToSlave(addr, reg, len, buf);
} 

//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
  IIC_Start(); 
  IIC_SendByte((addr<<1)|0);//����������ַ+д����	
  if(IIC_WaitAck())	//�ȴ�Ӧ��
  {
    IIC_Stop();		 
    return 1;		
  }
  IIC_SendByte(reg);	//д�Ĵ�����ַ
  IIC_WaitAck();		//�ȴ�Ӧ��
  IIC_Start();
  IIC_SendByte((addr<<1)|1);//����������ַ+������	
  IIC_WaitAck();		//�ȴ�Ӧ�� 
  while(len)
  {
    if(len==1)*buf=IIC_ReadByte(0);//������,����nACK 
    else *buf=IIC_ReadByte(1);		//������,����ACK  
    len--;
    buf++; 
  }    
  IIC_Stop();	//����һ��ֹͣ���� 
  return 0;	
    //return IIC_ReadMultByteFromSlave(addr, reg, len, buf);     
}


//IICдһ���ֽ� 
//devaddr:����IIC��ַ
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t value)
{
    return IIC_WriteByteToSlave(addr, reg, value);
}

//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t value;
    IIC_ReadByteFromSlave(addr, reg, &value);
    return value;
}






