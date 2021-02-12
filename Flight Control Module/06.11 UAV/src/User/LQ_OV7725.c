/*******************************************************************************
��ƽ    ̨������K66FX���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��4��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4������
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock��100.000MHz
��pllclock��200.000MHz

******************************************************************************/
#include "include.h"


/*------------------------------------------------------------------------------------------------------
����    ����OV7725_Init
����    �ܡ�����ͷ��ʼ��
����    ����fps  ֡��
���� �� ֵ����
��ʵ    �����Ƽ�ʹ��50֡��
��ע�����ע��K60�������ޣ�̫��֡�ʻ������
--------------------------------------------------------------------------------------------------------*/
void OV7725_Init(uint8_t fps)
{     
    uint8_t id[2];    //�������ͷid
    uint8_t ack = 0;  //�������мĴ��������Ƿ����   
    uint16_t width = OV7725_IMAGEW, height = OV7725_IMAGEH;
    uint16_t hstart, vstart, hsize;  
    //����ͷ�Ĵ�������
    SCCB_Init();                     //��ʼ��SCCB�ӿڣ�Ϊ���üĴ�����׼��
    OV7725_SoftwareReset();          //�Ĵ����ָ���ʼֵ
    delayms(50);  
    /*7725���ֱ��� 640 * 480*/
    if ((OV7725_IMAGEW > 640) || (OV7725_IMAGEH > 480))
    {
#ifdef LQ_TFT1_8
        TFTSPI_P8X8Str(0,0,"7725 dpi!!",u16RED,u16BLUE);
#else
        OLED_P6x8Str(2,1,(u8*)"7725 dpi!!");                      //����ͷʶ�ֱ������ù���ֹͣ����
#endif
        while(1);
    }
    ack += SCCB_RegRead(OV7725_SCCB_ADDR,OV7725_PID_REG,&id[0]);  //��ȡ����ͷid�߰�λ
    ack += SCCB_RegRead(OV7725_SCCB_ADDR,OV7725_VER_REG,&id[1]);  //��ȡ����ͷid�Ͱ�λ
    if(OV7725_REVISION != (((uint32_t)id[0] << 8U) | (uint32_t)id[1]))//����ͷ�汾�Ĵ��� 
    {     
#ifdef LQ_TFT1_8
        TFTSPI_P8X8Str(0,0,"7725 NG",u16RED,u16BLUE);
#else
        OLED_P6x8Str(2,1,(u8*)"7725 NG");                      //����ͷʶ��ʧ�ܣ�ֹͣ����
#endif
        
        while(1); 
    } 
    else                                                      //оƬID��ȷ
    {
#ifdef LQ_TFT1_8
        TFTSPI_P8X8Str(0,0,"7725 OK",u16RED,u16BLUE);
#else
        OLED_P6x8Str(2,1,(u8*)"7725 OK");
#endif
        
    }
    ack += OV7725_Init_Regs();     //�Ȱ��ٷ���Ĭ�ϳ�ʼ�� VGA ������Ҫ�ٸ�
    
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM2_REG, 0x03);  //����������� Bit[4]: ˯��ģʽ Bit[1:0]: ��������00: 1x 01: 2x 10: 3x 11: 4x
//    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM7_REG, 0x46);  //  ʹ��QVGA �� RGB565 ��ʽ
//                                                                  /*OV7725_COM7_REG
//                                                                    Bit[7]: ���üĴ���
//                                                                    0: ������
//                                                                    1: �����мĴ�������ΪĬ��ֵ
//                                                                    Bit[6]: �ֱ������ã�7725���֧�����ֱַ��ʣ������������Զ���ֱ����൱�ڽ�ȡ�����ֱַ������е�һ���֣��ᶪʧ��Ұ��
//                                                                    0: VGA
//                                                                    1: QVGA
//                                                                    Bit[5]: BT.656Э�鿪/��ѡ��
//                                                                    Bit[4]: ��������ԭʼֵ
//                                                                    Bit[3:2]: RGB�����ʽ�ؼ�
//                                                                    00: GBR4:2:2
//                                                                    01: RGB565
//                                                                    10: RGB555
//                                                                    11: RGB444
//                                                                    Bit[1:0]: �����ʽ����
//                                                                    00: YUV
//                                                                    01: Processed Bayer RAW
//                                                                    10: RGB
//                                                                    11: Bayer RAW */
//    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM3_REG, 0x00);//Bit[6]: 0ˮƽ����� 1ˮƽ����  ע�⿪��ˮƽ����ʱ��ÿ���0x32�Ĵ�����Bit[7]:����ͼ���Ե����-�ھ���ģʽ��Ӧ������Ϊ1
//                                                                 //Bit[4]: 0 UYVYģʽ  1 YUYVģʽ  
//                                                                 //Bit[3]: 0 С��      1 ��� 
//    hstart = (0x3fU << 2U);   //ͼ��ˮƽ��ʼλ�� ʹ��VGAʱ Ϊ0x23
//    vstart = (0x03U  << 1U) ;   //ͼ��ֱ��ʼλ�� ʹ��VGAʱ Ϊ0x07   
    
    /*OV7725_COM7_REG
    Bit[7]: ���üĴ���
    0: ������
    1: �����мĴ�������ΪĬ��ֵ
    Bit[6]: �ֱ������ã�7725���֧�����ֱַ��ʣ������������Զ���ֱ����൱�ڽ�ȡ�����ֱַ������е�һ���֣��ᶪʧ��Ұ��
    0: VGA
    1: QVGA
    Bit[5]: BT.656Э�鿪/��ѡ��
    Bit[4]: ��������ԭʼֵ
    Bit[3:2]: RGB�����ʽ�ؼ�
    00: GBR4:2:2
    01: RGB565
    10: RGB555
    11: RGB444
    Bit[1:0]: �����ʽ����
    00: YUV
    01: Processed Bayer RAW
    10: RGB
    11: Bayer RAW */
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM7_REG, 0x43);  //  ʹ��QVGA �� Bayer RAW ��ʽ
                                                                  
    
    /*Bit[1:0]: Output selection
      00: YUV or RGB
      01: YUV or RGB
      10: RAW8
      11: RAW10*/
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_DSP_CTRL4_REG, 0x4a);  
    
    //Bit[6]: 0ˮƽ����� 1ˮƽ����  ע�⿪��ˮƽ����ʱ��ÿ���0x32�Ĵ�����Bit[7]:����ͼ���Ե����-�ھ���ģʽ��Ӧ������Ϊ1
    //Bit[4]: 0 UYVYģʽ  1 YUYVģʽ  
    //Bit[3]: ��С��
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM3_REG, 0x00);
    
    /*Bit[7]: ���ÿ���AGC/AEC�㷨
    Bit[6]: AEC -��������
    0: �������ڴ�ֱ�հ�
    1: ���޵Ĳ���
    Bit[5]: �����˿�/��
    Bit[4]: ���õ�������ֵ��AEC
    0: ���ع�ʱ��������1/100��1/120
    ������κι��������µ����ô�ͨ�˲���
    1: �����ع�ʱ��С��1/100��1/120
    �����ǿ�������µ����ô�ͨ�˲���
    Bit[3]: ���õ�AEC��/�ؿ���
    0: ������С�ع�ʱ��Ϊһ��
    1: �����ع�ʱ��С��һ��
    Bit[2]: �Զ��������ʹ
    0: �ֶ�ģʽ
    1: �Զ�ģʽ
    Bit[1]: AWB Enable
    0: �ֶ�ģʽ
    1: �Զ�ģʽ
    Bit[0]: AEC Enable
    0: �ֶ�ģʽ
    1: �Զ�ģʽ*/
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xff);
    
    /*�Աȶ����� ��һ��ֵΪ0x20  ԽС�Աȶ�Խ��*/
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_CNST_REG, 0x20);
//    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BRIGHT_REG, 0x20);/*��������*/
//    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SIGN_REG, 0x20);/*��������*/
    hstart = 0x3fU << 2U;   //ͼ��ˮƽ��ʼλ��
    vstart = 0x03U << 1U;   //ͼ��ֱ��ʼλ��

    
    OV7725_SetFPS(fps);
    
    
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_EXHCL_REG, 0x00); //�������ز���LSB������ˮƽ��������������ص�LSB
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_ADVFL_REG, 0x00); //��ֱͬ������������(1λ����1��)��LSB
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_ADVFH_REG, 0x00); //��ֱͬ�����������е�MSB 
    /* Resolution and timing. */
    hsize = width + 16;

    /* �������ͼƬ��С. */
    
    //ˮƽ��ʼλ�ø�λ  ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����10λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_HREF_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_HSTART_REG, hstart >> 2U); 
    
    //ˮƽ��ȸ�λ      ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����10λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_HREF_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_HSIZE_REG, hsize >> 2U);  
    
    //��ֱ��ʼλ�ø�λ  ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����9λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_HREF_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VSTART_REG, vstart >> 1U); 
    
    //��ֱ�߶ȸ�λ      ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����9λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_HREF_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VSIZE_REG, height >> 1U);   
    
    //ˮƽ�����ȸ�λ  ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����10λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_EXHCH_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_HOUTSIZE_REG, width >> 2U); 
    
    //��ֱ����߶ȸ�λ  ��Ϊ�Ĵ�����8λ�� ���255���������640 * 480 �Ų��£�����9λ���ݣ������Ǹ�8λ��ʣ�µ���λ����OV7725_EXHCH_REG��
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VOUTSIZE_REG, height >> 1U);
    
    //ˮƽ��Ⱥʹ�ֱ�߶ȵĵ�λ
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_HREF_REG,
                    ((vstart & 1U) << 6U) | ((hstart & 3U) << 4U) | ((height & 1U) << 2U) | ((hsize & 3U) << 0U)); 
    
    //ˮƽ����ʹ�ֱ����ĵ�2λ�͵�1λ
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_EXHCH_REG, ((height & 1U) << 2U) | ((width & 3U) << 0U));  
      
}

/*------------------------------------------------------------------------------------------------------
����    ����OV7725_SetFPS
����    �ܡ�����FPS 
����    ����fps
���� �� ֵ����
��ʵ    ����
��ע��������õ�������ͷ��֡�������֡��Խ�ߣ���Ƭ��������Ҫ��Խ��
--------------------------------------------------------------------------------------------------------*/
void OV7725_SetFPS(uint8_t fps)
{
    if(fps > 75)
    {
        /* ���໷8��Ƶ ������
        Bit[7:6]: ���໷��Ƶ������
        00: ���ñ�Ƶ
        01: 4��Ƶ
        10: 6��Ƶ
        11: 8��Ƶ
        Bit[5:4]: �Զ��عⴰ�ڴ�С
        00: Full window
        01: 1/2 window
        10: 1/4 window
        11: Low 2/3 window*/
        SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM4_REG, 0xC1);  //PCLK 48M   
    }
    else
    {
        SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM4_REG, 0x41);  //PCLK 24M   
    }
    uint16_t dm_lnl = 0;                                               //������
    uint8_t  div    = 1;                                               //ʱ�ӷ�Ƶϵ��
    if(fps > 150)
    {
        fps = 150;
        div = 1;
        dm_lnl = 0;     
    }
    else if(fps > 75)
    {
        div = 1;
        dm_lnl = (uint16_t)((150 - fps) / 150.0 * (OV7725_IMAGEH + 36*(div + 1)));
    }
    else if(fps > 50)
    {
        div = 1;
        dm_lnl = (uint16_t)((75 - fps) / 75.0 * (OV7725_IMAGEH + 36*(div + 1)));
    }
    else if(fps > 37)
    {
        div = 2;
        dm_lnl = (uint16_t)((50 - fps) / 50.0 * (OV7725_IMAGEH + 36*(div + 1)));
    }
    else if(fps > 18)
    {
        div = 3;
        dm_lnl = (uint16_t)((37.5 - fps) / 37.5 * (OV7725_IMAGEH + 36*(div + 1)));
    }
    else 
    {
        div = 14;
        dm_lnl = 0;
    }
    /*ʱ������ ʱ�� = PCLK * 4 / ����1+1��*4�� ʱ��Խ�ߣ�֡��Խ�� ����DMA���ܽ��ܲ��˻������ 
    Bit[6]: ֱ��ʹ���ⲿʱ��(û��ʱ��Ԥ�̶ȿ���)
    Bit[5:0]: ʱ�� = PCLK �� ���໷��Ƶ�� /[(CLKRC[5:0] + 1) �� 4]*/
    SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_CLKRC_REG, div);
    
    /*�����еͰ�λ�� ���������п��Խ���֡�ʣ��ʵ���Ӱ�֡�����õ��Լ���Ҫ��֡��*/
    SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_DM_LNL_REG, (uint8_t)dm_lnl);  
    
    /*�����и߰�λ*/
    SCCB_RegWrite(OV7725_SCCB_ADDR, OV7725_DM_LNH_REG, (uint8_t)(dm_lnl>>8)); 
    
}
/*------------------------------------------------------------------------------------------------------
����    ����OV7725_Init_Regs
����    �ܡ��Զ��ع� VGA
����    ������
���� �� ֵ����
��ʵ    ����
��ע�����
--------------------------------------------------------------------------------------------------------*/
uint8_t OV7725_Init_Regs(void)
{
    uint8_t ack = 0;
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x3d, 0x03);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x42, 0x7f);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x4d, 0x09);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x64, 0xff);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x65, 0x20);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x66, 0x00);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x67, 0x48);   
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x0f, 0xc5);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x13, 0xff);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x63, 0xe0);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x14, 0x11);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x22, 0x3f);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x23, 0x07);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x24, 0x40);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x25, 0x30);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x26, 0xa1);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x2b, 0x00);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x6b, 0xaa);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x0d, 0x41);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x90, 0x05);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x91, 0x01);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x92, 0x03);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x93, 0x00);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x94, 0x90);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x95, 0x8a);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x96, 0x06);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x97, 0x0b);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x98, 0x95);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x99, 0xa0);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x9a, 0x1e);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x9b, 0x08);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x9c, 0x20);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x9e, 0x81);

    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0xa6, 0x04);


    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x7e, 0x0c);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x7f, 0x16);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x80, 0x2a);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x81, 0x4e);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x82, 0x61);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x83, 0x6f);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x84, 0x7b);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x85, 0x86);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x86, 0x8e);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x87, 0x97);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x88, 0xa4);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x89, 0xaf);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x8a, 0xc5);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x8b, 0xd7);
    ack += SCCB_RegWrite(OV7725_SCCB_ADDR,0x8c, 0xe8);
    return ack;
}

/*------------------------------------------------------------------------------------------------------
����    ����OV7725_SoftwareReset
����    �ܡ���λ����ͷ �ָ�Ĭ������
����    ������
���� �� ֵ����
��ʵ    ����
��ע�����
--------------------------------------------------------------------------------------------------------*/
void OV7725_SoftwareReset(void)
{
    SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM7_REG, 0x80);
}
/*------------------------------------------------------------------------------------------------------
����    ����OV7725_LightModeConfigs
����    �ܡ��ƹ�����
����    ����0:�Զ�ģʽ1:����2,����3,�칫��4,����5,ҹ��
���� �� ֵ����
��ʵ    ����
��ע�����
--------------------------------------------------------------------------------------------------------*/
void OV7725_LightModeConfigs(uint8_t mode)
{
    switch(mode)
    {
        case 1:  //����
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xfd);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x5a);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x5c);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0x65);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
            break;
        case 2:  //����
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xfd);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x58);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x60);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0x65);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
        
            break;
        case 3:  //�칫��
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xfd);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x84);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x4c);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0x65);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
            break;
        case 4:   //����
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xfd);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x96);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x40);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0x65);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
            break;
        case 5:   //����
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xff);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0xe5);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
            break;
        default:   //�Զ�ģʽ
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM8_REG, 0xff);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_BLUE_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_RED_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_COM5_REG, 0x65);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFL_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_ADVFH_REG, 0x00);
            break;
    }
}
/*------------------------------------------------------------------------------------------------------
����    ����OV7725_SpecialEffectConfigs
����    �ܡ���Ч����
����    ����0:��ͨģʽ 1.�ڰ� 2.����  3,ƫ��4,ƫ��5,ƫ�� 6,��Ƭ
���� �� ֵ����
��ʵ    ����
��ע�����
--------------------------------------------------------------------------------------------------------*/
void OV7725_SpecialEffectConfigs(uint8_t mode)
{

    switch(mode)
    {
        case 1:  //�ڰ�
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x26);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x80);
            break;
        case 2:  //����
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x1e);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x40);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0xa0);
            break;
        case 3:  //ƫ��
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x1e);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0xa0);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x40);
            break;
        case 4:   //ƫ��
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x1e);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x40);
            break;
        case 5:   //ƫ��
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x1e);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x60);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x60);
            break;
        case 6:   //��Ƭ
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x46);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x00);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x00);
            break;
        default:   //��ͨģʽ
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_SDE_REG, 0x06);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_UFIX_REG, 0x80);
            SCCB_RegWrite(OV7725_SCCB_ADDR,OV7725_VFIX_REG, 0x80);
            break;
    }
}



/*********************************************************************
 *����ͷSCCB�ײ�����
 *
 ***********************************************************************/



/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Init(void)
*  ����˵��������SCCB��������ΪGPIO���ܣ���ʱ���������ݷ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Init(void)
{
  GPIO_PinInit(SCCB_SCL_PIN, GPI_UP, 1);//����ΪGPIO����
//   PORTE_BASE_PTR->PCR[4] |= 0x03; //����
  GPIO_PinInit(SCCB_SDA_PIN, GPI_UP, 1);//����ΪGPIO����
// PORTE_BASE_PTR->PCR[5] |= 0x03; //����

}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Wait(void)
*  ����˵����SCCB�ȴ���ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Wait(void)
{
  uint16_t i=0;
  for(i=0;i<100;i++)
  { 
    asm ("nop");
  }  
}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Star(void)
*  ����˵������������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Star(void)
{
  SCL_Out;
  SDA_Out;
  SCCB_Wait();
  SDA_High;
  SCL_High; 
  SCCB_Wait();
  SDA_Low;
  SCCB_Wait();
  SCL_Low; 
  SCCB_Wait();
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Stop(void)
*  ����˵����ֹͣ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Stop(void)
{
  SCL_Out;
  SDA_Out;
  SCCB_Wait();
  SDA_Low;
  SCCB_Wait();
  SCL_High; 
  SCCB_Wait();
  SDA_High;
  SCCB_Wait();  
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�uint8 SCCB_SendByte(uint8 Data)
*  ����˵����SCCB�����ֽں���
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
uint8_t SCCB_SendByte(uint8_t Data)
{
  uint8_t i;
  uint8_t Ack;
  SDA_Out;
  for( i=0; i<8; i++)
  {
    if(Data & 0x80) SDA_High;
    else            SDA_Low;    
    Data <<= 1;
    SCCB_Wait();
    SCL_High;      
    SCCB_Wait();
    SCL_Low;
    SCCB_Wait();
  }
  SDA_In;
  SCCB_Wait();
  
  SCL_High;
  SCCB_Wait();
  Ack = SDA_Data;
  SCL_Low;
  SCCB_Wait();
  SDA_Out;
  return Ack;
}
/*************************************************************** 

* 
* �������ƣ�uint8 SCCB_ReadByte(void) 
* ����˵����SCCB��ȡ�ֽں��� 
* ����˵���� 
* �������أ���ȡ�ֽ� 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8_t SCCB_ReadByte(void) 
{ 
  uint8_t i; 
  uint8_t byte = 0; 
  SCL_Out; 
  SDA_In; //ʹ������
  for( i=0; i<8; i++) 
  { 
    SCCB_Wait(); 
    SCL_High;
    SCCB_Wait();
    byte = byte<<1;
    if(SDA_Data)
        byte++;
    SCCB_Wait();
    SCL_Low;  
  }
  SDA_Out;
  SCCB_Wait(); 
  return byte; 
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_Ack(void) 
* ����˵����IIC�лظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_Ack(void) 
{ 
  SCL_Out; 
  SDA_Out;
  SCL_Low;
  SDA_Low;
  SCCB_Wait();
  SCL_High;
  SCCB_Wait();
  SCL_Low;
  SCCB_Wait();
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_NAck(void) 
* ����˵����IIC�޻ظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_NAck(void) 
{ 
  SCL_Out; 
  SDA_Out;
  SCL_Low;
  SCCB_Wait();
  SDA_High;
  SCCB_Wait();
  SCL_High;
  SCCB_Wait();
  SCL_Low;
  SCCB_Wait();
} 

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data)
*  ����˵�������豸д���� 
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
uint8_t SCCB_RegWrite(uint8 Device,uint8 Address,uint8_t Data)
{
  uint8_t Ack = 0;
  
    SCCB_Star();
    Ack = SCCB_SendByte(Device<<1);
   
    Ack = SCCB_SendByte(Address);
    
    Ack = SCCB_SendByte(Data);
    
    SCCB_Stop();
    return Ack;
}
/*************************************************************** 

* 
* �������ƣ�uint8_t SCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data) 
* ����˵������ȡ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8_t SCCB_RegRead(uint8_t Device,uint8_t Address,uint8_t *Data) 
{   
  uint8 Ack = 0;
  Device = Device<<1;
  SCCB_Star();
  Ack += SCCB_SendByte(Device);
  SCCB_Wait();
  Ack += SCCB_SendByte(Address);
  SCCB_Wait();
  SCCB_Stop();
  SCCB_Wait();
  
  SCCB_Star();
  Ack += SCCB_SendByte(Device | 0x01);
  
  *Data = SCCB_ReadByte();
//  SCCB_Ack();
//  *Data = *Data<<8;
  
//  *Data += SCCB_ReadByte();
  SCCB_NAck();
  
  SCCB_Stop();
  
  return  Ack;
} 
/***************************************************************  
* 
* �������ƣ�int SCCB_Probe(uint8_t chipAddr) 
* ����˵������ѯ�õ�ַ���豸�Ƿ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
int SCCB_Probe(uint8_t chipAddr) 
{ 
  uint8_t err;
  err = 0;
  chipAddr <<= 1;
  
  SCCB_Star();
  err = SCCB_SendByte(chipAddr);
  SCCB_Stop();
  
  return err;
}