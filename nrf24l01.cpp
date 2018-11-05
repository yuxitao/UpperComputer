#include "nrf24l01.h"
#include "location.h"
#include "wiringPi/wiringPi.h"
NRF24L01::NRF24L01()
{



}
//#define SetBit(data, offset)         (data |= 1U << offset)
//#define ResetBit(data, offset)       (data &= ~(1U << offset))
//#define GetBit(data, offset)         ((data >> offset) &0x01)
//unsigned char readandwrite(unsigned char Adrr)
//{

//    wiringPiSPIDataRW(0,&Adrr,1)

//}
unsigned char NRF_SPI_ReadWriteByte    (unsigned char data)
{
    int i;unsigned char dat =0;
//    unsigned char addr = 0;
//    for(i=0;i<8;i++)
//    {
//        if( data&(1<<i))
//            addr |= 1<<(7-i);
//    }
    dat = wiringPiSPIDataRW(0,&data,1);
//    data = 0;
//    for(i=0;i<8;i++)
//    {
//        if( addr&(1<<i))
//            data |= 1<<(7-i);
//    }
    return data;
}

void NRF24L01::NRF24L01_Init(void)
{

    //pinMode(0,OUTPUT);
    //digitalWrite(0,HIGH);
    //pinMode(1,OUTPUT);
    //digitalWrite(1,LOW);
    //pinMode(2,INPUT);
    //digitalRead(2);
    //bcm2835_spi_begin();
    int m =0,n = 0,l =0;
//    unsigned char data1 =0,i;unsigned char addr=0;
//    unsigned char data[5]={0x11,0x22,0x44,0x88,0x99};

    unsigned char a =0xf0;
    //bcm2835_spi_begin();
//    l = wiringPiSetup();
//    m = wiringPiSPISetup(0,3000000);//3Mb/s
//    n = wiringPiSPISetup(1,3000000);

//    pinMode(3,OUTPUT);

//    pinMode(1,OUTPUT);

//    pinMode(2,INPUT);

//    Set_NRF24L01_CE;                                 	//��ʼ��ʱ������
//    Clr_NRF24L01_CE; 	                               	//ʹ��24L01
//    Set_NRF24L01_CSN;                                	//SPIƬѡȡ��
}
//�ϵ���NRF24L01�Ƿ���λ
//д5������Ȼ���ٶ��������бȽϣ���ͬʱ����ֵ:0����ʾ��λ;���򷵻�1����ʾ����λ
unsigned char NRF24L01::NRF24L01_Check(void)
{
    unsigned char  buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
    unsigned char  buf1[5];
    unsigned char  i;
    NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.
    NRF24L01_Read_Buf(TX_ADDR,buf1,5);              //����д��ĵ�ַ
    for(i=0;i<5;i++)if(buf1[i]!=0XA5)break;
    if(i!=5)return 1;                               //NRF24L01����λ
    return 0;		                                //NRF24L01��λ
}
//ͨ��SPIд�Ĵ���
unsigned char NRF24L01::NRF24L01_Write_Reg(unsigned char regaddr,unsigned char data)
{
    unsigned char status;
    Clr_NRF24L01_CSN;                    //ʹ��SPI����
    status =NRF_SPI_ReadWriteByte(regaddr); //���ͼĴ�����
    NRF_SPI_ReadWriteByte(data);            //д��Ĵ�����ֵ
    Set_NRF24L01_CSN;                    //��ֹSPI����
    return(status);       		         //����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ ��regaddr:Ҫ���ļĴ���
unsigned char NRF24L01::NRF24L01_Read_Reg(unsigned char regaddr)
{
    unsigned char reg_val;
    adressnumber = 0XFF;
    Clr_NRF24L01_CSN;                //ʹ��SPI����
    NRF_SPI_ReadWriteByte(regaddr);     //���ͼĴ�����
    reg_val=NRF_SPI_ReadWriteByte(adressnumber);//��ȡ�Ĵ�������//��������ֵ������
    Set_NRF24L01_CSN;                //��ֹSPI����
    return(reg_val);                 //����״ֵ̬
}
//��ָ��λ�ö���ָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
unsigned char NRF24L01::NRF24L01_Read_Buf(unsigned char regaddr,unsigned char *pBuf,unsigned char datalen)
{
    unsigned char status,u8_ctr;
    adressnumber = 0XFF;
    Clr_NRF24L01_CSN;                     //ʹ��SPI����
    status=NRF_SPI_ReadWriteByte(regaddr);   //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for(u8_ctr=0;u8_ctr<datalen;u8_ctr++)pBuf[u8_ctr]=NRF_SPI_ReadWriteByte(adressnumber);//��������//��������ֵ������
    Set_NRF24L01_CSN;                     //�ر�SPI����
    return status;                        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
unsigned char NRF24L01::NRF24L01_Write_Buf(unsigned char regaddr, unsigned char *pBuf, unsigned char datalen)
{
    unsigned char status,u8_ctr;
    Clr_NRF24L01_CSN;                                    //ʹ��SPI����
    status = NRF_SPI_ReadWriteByte(regaddr);                //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for(u8_ctr=0; u8_ctr<datalen; u8_ctr++)NRF_SPI_ReadWriteByte(*pBuf++); //д������
    Set_NRF24L01_CSN;                                    //�ر�SPI����
    return status;                                       //���ض�����״ֵ̬
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
unsigned char NRF24L01::NRF24L01_TxPacket(unsigned char *txbuf)
{
    unsigned char state,i;
    int irqstate;
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
    Set_NRF24L01_CE;                                     //��������
//    while(i<200)
//    {i++;}
    irqstate = digitalRead(2);
    while(irqstate!=0);                                  //�ȴ��������
    state=NRF24L01_Read_Reg(STATUS);                     //��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state);      //���TX_DS��MAX_RT�жϱ�־
    if(state&MAX_TX)                                     //�ﵽ����ط�����
    {
        NRF24L01_Write_Reg(FLUSH_TX,0xff);               //���TX FIFO�Ĵ���
        return MAX_TX;
    }
    if(state&TX_OK)                                      //�������
    {
        return TX_OK;
    }
    return 0xff;                                         //����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
unsigned char NRF24L01::NRF24L01_RxPacket(unsigned char *rxbuf)
{
    unsigned char state;
    state=NRF24L01_Read_Reg(STATUS);                //��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); //���TX_DS��MAX_RT�жϱ�־
    if(state&RX_OK)                                 //���յ�����
    {
        NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
        NRF24L01_Write_Reg(FLUSH_RX,0xff);          //���RX FIFO�Ĵ���
        return 0;
    }
    return 1;                                      //û�յ��κ�����
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������
void NRF24L01::RX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char *)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ

    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,10);	     //����RFͨ��Ƶ��
    NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��  0X07 1M 0X0F 2M
    NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    Set_NRF24L01_CE;                                //CEΪ��,�������ģʽ
}
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������
//CEΪ�ߴ���10us,����������.
void NRF24L01::TX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,(unsigned char *)TX_ADDRESS,TX_ADR_WIDTH);    //дTX�ڵ��ַ
    NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char *)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK

    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x7A);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10�� 0x1a
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,10);       //����RFͨ��Ϊ40
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��     0X07 1M 0X0F 2M
    NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
    Set_NRF24L01_CE;                                  //CEΪ��,10us����������
}
