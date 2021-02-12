/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��12��18��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"



/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ȡ����ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 
������ֵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifdef LQ_OLED
void Test_9AX(void)
{ 
    int16_t ACC_X,ACC_Y,ACC_Z,GYRO_X,GYRO_Y,GYRO_Z,MAG_X,MAG_Y,MAG_Z;
    
    char  txt[16]="X:";
    Init_9AX();
    UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
    OLED_P8x16Str(15,0,"LQ 6050 Test"); 
    printf("\r\nLQ 6050 Test");
    while(1)
    {
        //��������ˢ��
        Update9AX(&ACC_X, &ACC_Y, &ACC_Z, &GYRO_X, &GYRO_Y, &GYRO_Z, &MAG_X, &MAG_Y, &MAG_Z);
        sprintf((char*)txt,"ax:%06d",ACC_X);
        OLED_P6x8Str(0,2,txt);
        sprintf((char*)txt,"ay:%06d",ACC_Y);
        OLED_P6x8Str(0,3,txt);
        sprintf((char*)txt,"az:%06d",ACC_Z);
        OLED_P6x8Str(0,4,txt);
        sprintf((char*)txt,"gx:%06d",GYRO_X);
        OLED_P6x8Str(0,5,txt);
        sprintf((char*)txt,"gy:%06d",GYRO_Y);
        OLED_P6x8Str(0,6,txt);
        sprintf((char*)txt,"gz:%06d",GYRO_Z);
        OLED_P6x8Str(0,7,txt);
        sprintf((char*)txt,"MX:%06d",MAG_X);
        OLED_P6x8Str(60,5,txt);
        sprintf((char*)txt,"MY:%06d",MAG_Y);   //
        OLED_P6x8Str(60,6,txt);
        sprintf((char*)txt,"MZ:%06d",MAG_Z);   //
        OLED_P6x8Str(60,7,txt);
        delayms(100);
        printf("\r\nAX: %d  ",ACC_X); 
        printf("\r\nAY: %d  ",ACC_Y);
        printf("\r\nAZ: %d  ",ACC_Z); 
        printf("\r\nGX: %d  ",GYRO_X);
        printf("\r\nGY: %d  ",GYRO_Y); 
        printf("\r\nGZ: %d  ",GYRO_Z);
        printf("\r\nMX: %d  ",MAG_X);
        printf("\r\nMY: %d  ",MAG_Y); 
        printf("\r\nMZ: %d  ",MAG_Z);
    }
}
#else
void Test_9AX(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    UART_Init(UART4, 115200);
    char  txt[30];
	int16_t ACC_X,ACC_Y,ACC_Z,GYRO_X,GYRO_Y,GYRO_Z,MAG_X,MAG_Y,MAG_Z;
    TFTSPI_P8X16Str(2,0,"LQ 9AX Test",u16RED,u16BLUE);
    printf("\r\nLQ 9AX Test");
    
    Init_9AX();
        
    while(1)
    {
        //��������ˢ��
        Update9AX(&ACC_X, &ACC_Y, &ACC_Z, &GYRO_X, &GYRO_Y, &GYRO_Z, &MAG_X, &MAG_Y, &MAG_Z);
        sprintf((char*)txt,"ax:%06d",ACC_X);
        TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"ay:%06d",ACC_Y);
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"az:%06d",ACC_Z);
        TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gx:%06d",GYRO_X);
        TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gy:%06d",GYRO_Y);
        TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gz:%06d",GYRO_Z);
        TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLUE);

        sprintf((char*)txt,"mx:%06d",MAG_X);
        TFTSPI_P8X16Str(0,7,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"my:%06d",MAG_Y);
        TFTSPI_P8X16Str(0,8,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"mz:%06d",MAG_Z);
        TFTSPI_P8X16Str(0,9,txt,u16RED,u16BLUE);
        printf("\r\nAX: %d  ",ACC_X); 
        printf("\r\nAY: %d  ",ACC_Y);
        printf("\r\nAZ: %d  ",ACC_Z); 
        printf("\r\nGX: %d  ",GYRO_X);
        printf("\r\nGY: %d  ",GYRO_Y); 
        printf("\r\nGZ: %d  ",GYRO_Z);
        printf("\r\nMX: %d  ",MAG_X);
        printf("\r\nMY: %d  ",MAG_Y); 
        printf("\r\nMZ: %d  ",MAG_Z);
        delayms(100);
        printf("*********************");
    }
    
}
#endif
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ�� ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 
������ֵ���� �����Ǵ�����,��2000dps   �Ӽ� ����4gģʽ
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Init_9AX(void)
{
  IIC_Init();                         //��ʼ��I2C1 
  
  ///////FXAS21002//////////////////////////////////////////////////////////////////////////////////////////
  // write 0000 0000 = 0x00 to CTRL_REG1 to place FXOS21002 in Standby
  // [7]: ZR_cond=0
  // [6]: RST=0
  // [5]: ST=0 self test disabled
  // [4-2]: DR[2-0]=000 for 800Hz
  // [1-0]: Active=0, Ready=0 for Standby mode
  IIC_WriteByteToSlave( FXAS21002_ADDR, FXAS21002_CTRL_REG1, 0x00); //���ò�����800Hz
  // write 0000 0000 = 0x00 to CTRL_REG0 to configure range and filters
  // [7-6]: BW[1-0]=00, LPF disabled
  // [5]: SPIW=0 4 wire SPI (irrelevant)
  // [4-3]: SEL[1-0]=00 for 10Hz HPF at 200Hz ODR
  // [2]: HPF_EN=0 disable HPF
  // [1-0]: FS[1-0]=00 for 1600dps (TBD CHANGE TO 2000dps when final trimmed parts available)
  IIC_WriteByteToSlave(FXAS21002_ADDR, FXAS21002_CTRL_REG0, 0x00);   //�����Ǵ�����,��2000dps     
  delayms(100);  
  // write 0000 0001 = 0x01 to CTRL_REG1 to configure 800Hz ODR and enter Active mode
  // [7]: ZR_cond=0
  // [6]: RST=0
  // [5]: ST=0 self test disabled
  // [4-2]: DR[2-0]=000 for 800Hz ODR
  // [1-0]: Active=1, Ready=0 for Active mode
  IIC_WriteByteToSlave(FXAS21002_ADDR, FXAS21002_CTRL_REG1, 0x03);   //�����ǹ���
  
  //////FXOS8700///////////////////////////////////////////////////////////////////////////////////////////
  delayms(100);    
  uint8_t val;
  IIC_ReadByteFromSlave(FXOS8700_ADDR, FXOS8700_CTRL_REG1, &val);  //��CTRL1�Ĵ���
  IIC_WriteByteToSlave(FXOS8700_ADDR, FXOS8700_CTRL_REG1, val & (uint8_t)~ACTIVE_MASK);   //ʹ8700���ڴ���ģʽ
  IIC_WriteByteToSlave(FXOS8700_ADDR, F_SETUP_REG,F_MODE_DISABLED);    //��FIFO
  IIC_WriteByteToSlave(FXOS8700_ADDR, FXOS8700_M_CTRL_REG2, MOD_HIGH_RES);   //�߷ֱ���ģʽ
  IIC_WriteByteToSlave( FXOS8700_ADDR, M_CTRL_REG1, (M_RST_MASK | M_OSR_MASK | M_HMS_MASK));   //���ģʽ���Ӽƺ͵شż�ͬʱʹ��
  IIC_WriteByteToSlave(FXOS8700_ADDR, M_CTRL_REG2, M_HYB_AUTOINC_MASK); 
  IIC_WriteByteToSlave(FXOS8700_ADDR, XYZ_DATA_CFG_REG, FULL_SCALE_4G);       //�Ӽ� ����4gģʽ
  IIC_WriteByteToSlave(FXOS8700_ADDR, FXOS8700_CTRL_REG1, (HYB_DATA_RATE_200HZ | ACTIVE_MASK));       //�����������Ƶ�� 200hz ���Ҽ���FX8700
  delayms(10);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ȡ ����  ԭʼ����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ���� 
������ֵ��ָ���ž���ԭʼ���ݵĵ�ַ 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Update9AX(short *ax,short *ay,short *az,short *gx,short *gy,short *gz, short *mx, short *my, short *mz)
{      
  uint8_t acc_buf[6]; 
  uint8_t mag_buf[6]; 
  uint8_t gyr_buf[6];
  IIC_ReadMultByteFromSlave(FXOS8700_ADDR,0x01,6,acc_buf);
  IIC_ReadMultByteFromSlave(FXOS8700_ADDR,0x33,6,mag_buf); 
  IIC_ReadMultByteFromSlave(FXAS21002_ADDR,0x01,6,gyr_buf);
  
  
  *ax = ((int16_t)((uint16_t)acc_buf[0]<<8 | (uint16_t)acc_buf[1]));  //���ٶȼ�14λ�ģ�����λӰ�첻��ֱ�Ӱ�16λ����
  *ay = ((int16_t)((uint16_t)acc_buf[2]<<8 | (uint16_t)acc_buf[3]));
  *az = ((int16_t)((uint16_t)acc_buf[4]<<8 | (uint16_t)acc_buf[5]));

  *mx = (int16_t)((uint16_t)mag_buf[0]<<8 | (uint16_t)mag_buf[1]);
  *my = (int16_t)((uint16_t)mag_buf[2]<<8 | (uint16_t)mag_buf[3]);
  *mz = (int16_t)((uint16_t)mag_buf[4]<<8 | (uint16_t)mag_buf[5]);
  
  *gx = (int16_t)((uint16_t)gyr_buf[0]<<8 | (uint16_t)gyr_buf[1]);
  *gy = (int16_t)((uint16_t)gyr_buf[2]<<8 | (uint16_t)gyr_buf[3]);
  *gz = (int16_t)((uint16_t)gyr_buf[4]<<8 | (uint16_t)gyr_buf[5]);
 
}


