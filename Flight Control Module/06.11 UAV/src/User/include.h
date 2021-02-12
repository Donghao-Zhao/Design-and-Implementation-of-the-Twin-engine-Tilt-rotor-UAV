#ifndef INCLUDE_H_
#define INCLUDE_H_

/*
 * ����Cortex-M�ں˵�ͨ��ͷ�ļ�
 */
#include    <stdio.h>                       //printf
#include    <string.h>                      //memcpy
#include    <stdlib.h>                      //malloc
#include "math.h"
#include "common.h" 
#include "MK66F18.h"   /* �Ĵ���ӳ��ͷ�ļ� */
#include "core_cm4.h"         /* �ں��ļ����������ж����ȼ� */

/*----------------------------------------------------------------
                   �ײ������ļ�
------------------------------------------------------------------*/
#include "MK60_ADC.h"              /* ����ADCģ�� */
#include "MK60_GPIO.h"             /* ����GPIOģ�� */
#include "MK60_GPIO_Cfg.h"         /* ����GPIOģ�� ��51��IO���� */
#include "MK60_PLL.h"              /* ����ʱ��Ƶ������ */
#include "MK60_UART.h"             /* ���ڴ���ģ�� */
#include "MK60_PIT.h"              /* ����PIT��ʱ��ģ�� */
#include "MK60_FTM.h"              /* ����FTM��ʱ��ģ�� */
#include "MK60_CMT.h"              /* ����CMT��ʱ��ĳ�� */
#include "MK60_IIC.h"              /* ����IICģ�� */
#include "MK60_DMA.h"              /* ����DMAģ�� */
#include "MK60_LPTMR.h"            /* ����LPTMR��ʱ��ģ�� */
#include "MK60_WDOG.h"             /* ���ڿ��Ź� */
#include "MK60_SYSTICK.h"          /* systick �ں˶�ʱ�� */
#include "MK60_FLASH.h"            /* Flash ��д */
/*----------------------------------------------------------------
                    ����ģ������
------------------------------------------------------------------*/
#include "LQ_LED.h"                /* LED         ���� */
#include "LQ_KEY.h"                /* KEY         ���� */
#include "LQ_PIT.h"                /* PIT         ���� */
#include "LQ_UART.h"               /* UART        ���� */
#include "LQ_LPTMR.h"              /* LPTMR       ���� */
#include "LQ_SYSTICK.h"            /* SYSTICK     ���� */
#include "LQ_12864.h"              /* OLED        ���� */
#include "LQ_SGP18T.h"             /* TFT1.8      ���� */
#include "LQ_ADC.h"                /* ADC         ���� */
#include "LQ_WDOG.h"               /* WDOG        ���� */
#include "LQ_SD5.h"                /* ���        ���� */
#include "LQ_MOTOR.h"              /* ���        ���� */
#include "LQ_MPU6050.h"            /* 6050        ���� */
#include "LQ_9AX.h"                /* ����        ���� */
#include "LQ_MT9V034.h"            /* ����        ���� */
#include "LQ_CAMERA.h"             /* ����ͷ      ���� */
#include "LQ_FLASH.h"              /* FLASH       ���� */
#include "LQ_CCD.h"                /* CCD         ���� */
#include "LQ_Ultrasonic.h"         /* ���������  ���� */
#include "ANO_DT.h"


#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


/////////////////////////////////////////////////////////////////
///////////////////////����ֵ����////////////////////////////////
/////////////////////////////////////////////////////////////////
#define steer_left_duty_front   8550    //������ǰֵ
#define steer_left_duty_mid     7550    //�����м�ֵ
#define steer_left_duty_rear    6550    //�������ֵ
#define steer_right_duty_front  6150    //�Ҷ����ǰֵ
#define steer_right_duty_mid    7150    //�Ҷ���м�ֵ
#define steer_right_duty_rear   8150    //�Ҷ�����ֵ
#define motor_left_duty_zero    0       //������ֵ
#define motor_left_duty_init    3500    //������ʼ��ֵ
#define motor_left_duty_start   5700    //��������ֵ
#define motor_left_duty_1       7200    //����1/3��
#define motor_left_duty_2       8400    //����2/3��
#define motor_left_duty_full    9600    //����ȫ���ֵ
#define motor_right_duty_zero   0       //�ҵ����ֵ
#define motor_right_duty_init   3500    //�ҵ����ʼ��ֵ
#define motor_right_duty_start  5700    //�ҵ������ֵ
#define motor_right_duty_1      7200    //�ҵ��1/3��
#define motor_right_duty_2      8400    //�ҵ��2/3��
#define motor_right_duty_full   9600    //�ҵ��ȫ���ֵ
#define hc_valid_min            2       //�����������Чֵ
#define hc_valid_max            300     //�����������Чֵ


  
/* ��OLED ����ʾ������TFT1.8��ʾ */
#define LQ_OLED     
//#define LQ_TFT1_8       
   

#endif

