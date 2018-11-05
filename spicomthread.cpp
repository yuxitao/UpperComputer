#include "spicomthread.h"
#include "nrf_ctrl.h"
#include "dk_conf.h"
#include <QThread>//创建线程时需要包含的头文件
#include <QApplication>//创建线程时需要包含的头文件


unsigned char RunFlag;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



DiaoKe_Struct DK;  //??????????????



BUF_Struct Rx_Buf;
NRF_Struct NRF;



unsigned char Tx_Buf[34];
unsigned char TxBuf[34];//用于SPI发送存储中间数据

SPIComThread::SPIComThread()
{

}
void SPIComThread::run()
{
    //????????????????
    //emit send(QString("thread"));
//    NRFtask();
    SPICom();
}
//CRC校验程序算法
int SPIComThread::CalCrc(int crc, unsigned char *buf, int len)
{
    unsigned int byte;
    unsigned char k;
    unsigned short ACC,TOPBIT;
//    unsigned short remainder = 0x0000;
    unsigned short remainder = crc;
    TOPBIT = 0x8000;
    for (byte = 0; byte < len; ++byte)
    {
        ACC = buf[byte];
        remainder ^= (ACC <<8);
        for (k = 8; k > 0; --k)
        {
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^0x8005;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    remainder=remainder^0x0000;
    return remainder;
}
void SPIComThread::CRCResult(void)
{
    int i;
    int crcresault;
    //char buffer[22] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x01, 0x02, 0x03, 0x04};
    unsigned char buffer[34];
    for(i=0;i<32;i++)
    {
        buffer[i] = Tx_Buf[i];
    }
    crcresault = CalCrc(0, buffer, 32);//计算得到的16位CRC校验码
    buffer[32] = (char)crcresault;//取校验码的低八位
    buffer[33] = (char)(crcresault >> 8);//取校验码的高八位
    Tx_Buf[32] = buffer[32];
    Tx_Buf[33] = buffer[33];
}
void SPIComThread::SPICom(void)
{
    unsigned char Success=0,Failure=0;
    unsigned char i=0;

    NRF.Ctrl = NRF_M_OK;
    DK.Ctrl = CTRL_STOP;
    //    nrftask->Send_DK_Action(NRF_CX_SYS);			//查询DK系统状态
    //    NRF_M_CRTL(Tx_Buf);
    if(RunFlag)
    {
        RunFlag = 0;
        CRCResult();
        for(i=0;i<34;i++)
        {
            TxBuf[i]=Tx_Buf[i];
        }
        wiringPiSPIDataRW(0,TxBuf,34);//通过SPI接口发送指令参数
        //            wiringPiSPIDataRW(0,Tx_Buf,35);//通过SPI接口发送指令参数
        this->wait(2);
        Failure=digitalRead(2);//IRQ 数据传输失败
        Success=digitalRead(3);//CE  数据传输成功
        while((Success|Failure)==0)
        {
            Success=digitalRead(2);//IRQ 数据传输失败
            Failure=digitalRead(3);//CE  数据传输成功
        }
        while(Failure)//
        {
            for(i=0;i<34;i++)
            {
                TxBuf[i]=Tx_Buf[i];
            }
            wiringPiSPIDataRW(0,TxBuf,34);//通过SPI接口发送指令参数
            this->wait(5);
            Success=digitalRead(2);//IRQ 数据传输失败
            Failure=digitalRead(3);//IRQ 数据传输失败
        }
        while (NRF.Send)
        {
            if(Success)
            {
                NRF.Send = 0;
            }
            Success=digitalRead(2);//IRQ 数据传输失败
            Failure=digitalRead(3);//IRQ 数据传输失败
        }
    }
}
