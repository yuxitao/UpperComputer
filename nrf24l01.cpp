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

//    Set_NRF24L01_CE;                                 	//初始化时先拉高
//    Clr_NRF24L01_CE; 	                               	//使能24L01
//    Set_NRF24L01_CSN;                                	//SPI片选取消
}
//上电检测NRF24L01是否在位
//写5个数据然后再读回来进行比较，相同时返回值:0，表示在位;否则返回1，表示不在位
unsigned char NRF24L01::NRF24L01_Check(void)
{
    unsigned char  buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
    unsigned char  buf1[5];
    unsigned char  i;
    NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.
    NRF24L01_Read_Buf(TX_ADDR,buf1,5);              //读出写入的地址
    for(i=0;i<5;i++)if(buf1[i]!=0XA5)break;
    if(i!=5)return 1;                               //NRF24L01不在位
    return 0;		                                //NRF24L01在位
}
//通过SPI写寄存器
unsigned char NRF24L01::NRF24L01_Write_Reg(unsigned char regaddr,unsigned char data)
{
    unsigned char status;
    Clr_NRF24L01_CSN;                    //使能SPI传输
    status =NRF_SPI_ReadWriteByte(regaddr); //发送寄存器号
    NRF_SPI_ReadWriteByte(data);            //写入寄存器的值
    Set_NRF24L01_CSN;                    //禁止SPI传输
    return(status);       		         //返回状态值
}
//读取SPI寄存器值 ，regaddr:要读的寄存器
unsigned char NRF24L01::NRF24L01_Read_Reg(unsigned char regaddr)
{
    unsigned char reg_val;
    adressnumber = 0XFF;
    Clr_NRF24L01_CSN;                //使能SPI传输
    NRF_SPI_ReadWriteByte(regaddr);     //发送寄存器号
    reg_val=NRF_SPI_ReadWriteByte(adressnumber);//读取寄存器内容//将常数赋值给变量
    Set_NRF24L01_CSN;                //禁止SPI传输
    return(reg_val);                 //返回状态值
}
//在指定位置读出指定长度的数据
//*pBuf:数据指针
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01::NRF24L01_Read_Buf(unsigned char regaddr,unsigned char *pBuf,unsigned char datalen)
{
    unsigned char status,u8_ctr;
    adressnumber = 0XFF;
    Clr_NRF24L01_CSN;                     //使能SPI传输
    status=NRF_SPI_ReadWriteByte(regaddr);   //发送寄存器值(位置),并读取状态值
    for(u8_ctr=0;u8_ctr<datalen;u8_ctr++)pBuf[u8_ctr]=NRF_SPI_ReadWriteByte(adressnumber);//读出数据//将常数赋值给变量
    Set_NRF24L01_CSN;                     //关闭SPI传输
    return status;                        //返回读到的状态值
}
//在指定位置写指定长度的数据
//*pBuf:数据指针
//返回值,此次读到的状态寄存器值
unsigned char NRF24L01::NRF24L01_Write_Buf(unsigned char regaddr, unsigned char *pBuf, unsigned char datalen)
{
    unsigned char status,u8_ctr;
    Clr_NRF24L01_CSN;                                    //使能SPI传输
    status = NRF_SPI_ReadWriteByte(regaddr);                //发送寄存器值(位置),并读取状态值
    for(u8_ctr=0; u8_ctr<datalen; u8_ctr++)NRF_SPI_ReadWriteByte(*pBuf++); //写入数据
    Set_NRF24L01_CSN;                                    //关闭SPI传输
    return status;                                       //返回读到的状态值
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
unsigned char NRF24L01::NRF24L01_TxPacket(unsigned char *txbuf)
{
    unsigned char state,i;
    int irqstate;
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
    Set_NRF24L01_CE;                                     //启动发送
//    while(i<200)
//    {i++;}
    irqstate = digitalRead(2);
    while(irqstate!=0);                                  //等待发送完成
    state=NRF24L01_Read_Reg(STATUS);                     //读取状态寄存器的值
    NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state);      //清除TX_DS或MAX_RT中断标志
    if(state&MAX_TX)                                     //达到最大重发次数
    {
        NRF24L01_Write_Reg(FLUSH_TX,0xff);               //清除TX FIFO寄存器
        return MAX_TX;
    }
    if(state&TX_OK)                                      //发送完成
    {
        return TX_OK;
    }
    return 0xff;                                         //其他原因发送失败
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
unsigned char NRF24L01::NRF24L01_RxPacket(unsigned char *rxbuf)
{
    unsigned char state;
    state=NRF24L01_Read_Reg(STATUS);                //读取状态寄存器的值
    NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
    if(state&RX_OK)                                 //接收到数据
    {
        NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
        NRF24L01_Write_Reg(FLUSH_RX,0xff);          //清除RX FIFO寄存器
        return 0;
    }
    return 1;                                      //没收到任何数据
}

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了
void NRF24L01::RX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char *)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址

    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答
    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,10);	     //设置RF通信频率
    NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f); //设置TX发射参数,0db增益,2Mbps,低噪声增益开启  0X07 1M 0X0F 2M
    NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f);  //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
    Set_NRF24L01_CE;                                //CE为高,进入接收模式
}
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了
//CE为高大于10us,则启动发送.
void NRF24L01::TX_Mode(void)
{
    Clr_NRF24L01_CE;
    NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,(unsigned char *)TX_ADDRESS,TX_ADR_WIDTH);    //写TX节点地址
    NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(unsigned char *)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK

    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答
    NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址
    NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x7A);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次 0x1a
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,10);       //设置RF通道为40
    NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启     0X07 1M 0X0F 2M
    NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
    Set_NRF24L01_CE;                                  //CE为高,10us后启动发送
}
