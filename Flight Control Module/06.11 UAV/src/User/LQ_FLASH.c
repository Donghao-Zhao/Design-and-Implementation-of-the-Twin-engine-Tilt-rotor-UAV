/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�FLASH ��д����
��ע�������Ҫд��ǰ������  �Ḳ�ǳ���
-------------------------------------------------------------------------------------------------------*/
#include "include.h"


//------------------------------------------------------------------------------------------------    
//����һ��PID�����ṹ��  ���ڲ���FLASH��д
//------------------------------------------------------------------------------------------------ 
typedef struct
{
    float                _kp;         //P
    float                _ki;         //I
    float                _kd;         //D
    float                _imax;       //�����޷�
    
    float                _pid_out_p;  //KP���
    float                _pid_out_i;  //KI���
    float                _pid_out_d;  //KD���
    float                _pid_out;    //pid���
    
    float                _integrator; ///< integrator value
    float                _last_error; ///< last error for derivative
    float                _last_derivative;///< last derivative for low-pass filter
    uint32_t             _last_t;    ///< last time  
    float                scaler;      //����
}_pid_param_t;

_pid_param_t pid_param_write = 
{
	._kp             =  1.0 ,
	._ki             =  0.5 ,
	._kd             =  0.1 ,
	._imax           =   50 , 
	
	._pid_out_p      =   0,  
	._pid_out_i      =   0,  
	._pid_out_d      =   0,  
	._pid_out        =   0,
	
	._integrator     =   0, 
	._last_error     =   0, 
	._last_derivative=   0,
	._last_t         =   0,  
	.scaler          =   7,
};

/*------------------------------------------------------------------------------------------------------
����    ����Test_Flash
����    �ܡ�����flash ��д
����    ������
���� �� ֵ����
��ʵ    ����Test_Flash(); 
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_Flash(void)
{
	UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
	KEY_Init();
	FLASH_Init();
    OLED_P8x16Str(15,0,"LQ FLASH Test"); 
    printf("\r\nLQ FLASH Test");
	printf("\r\n��Ҫд��ǰ������  �Ḳ�ǳ���");
	printf("\r\n����K1����Ӧ��ֵ��1");
	printf("\r\n����K2����Ӧ��ֵ��1");
	printf("\r\n����K0�����浱ǰ����");
	
	char txt[16];
	
	_pid_param_t pid_param_read;
	
	/* �ӵ�����һ������ 0ƫ��λ�ÿ�ʼ �����ṹ������ */
	pid_param_read = FLASH_Read(3, 0, _pid_param_t);
	
	if(pid_param_read._kp != 1)    //��һ��д
	{
		FLASH_WriteBuf(3,(const uint8 *)&pid_param_write, sizeof(pid_param_write), 0);//д������
	}

	while(1)
	{
		switch(KEY_Read(0))  
        {
            case 1:
				FLASH_EraseSector(3);                                                          //��������
				FLASH_WriteBuf(3,(const uint8 *)&pid_param_read, sizeof(pid_param_read), 0);//д������
                LED_Reverse(0);
                break;           
            case 2:   
				pid_param_read._ki++;
                LED_Reverse(1);
                break;
            case 3:  
				pid_param_read._ki--;
                LED_Reverse(2);
                break;
            default:
                LED_Reverse(3);
                break;
        }
		printf("Ki is : %f \n", pid_param_read._ki);
		sprintf(txt,"Ki :%5f",pid_param_read._ki);
        OLED_P8x16Str(20,6,(uint8_t*)txt);
		delayms(100);
	}

}
