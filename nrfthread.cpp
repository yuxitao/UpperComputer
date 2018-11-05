#include "nrfthread.h"
#include "nrf_ctrl.h"
#include "nrf24l01.h"
#include "nrftask.h"
#include "dk_conf.h"
#include "ui_maincontrol.h"
#include <QThread>
#include <QApplication>
//#include <pthread.h>






NRFTHREAD::NRFTHREAD()
{
    nrf24l01 = new NRF24L01() ;
    nrftask  = new NRFTask();
}
void NRFTHREAD::run()
{
    //????????????????
    //emit send(QString("thread"));
    NRFtask();
}

void NRFTHREAD::Switch_Buf(void)
{
    if(Rx_Buf.Old == 0)
    {
        Rx_Buf.Old = 1;
        Rx_Buf.New = 0;
    }
    else
    {
        Rx_Buf.Old = 0;
        Rx_Buf.New = 1;
    }
}

/*-------------------------------------???????-----------------------------------------------------*/
void NRFTHREAD::NRF_M_Init(void)								// S ???????
{

        NRF.Ctrl = NRF_M_OK;
        nrf24l01->RX_Mode();
}
//?????buf??????buf[0]??????????G??????????????????????buf[1]???????DK.CTRL
void NRFTHREAD::NRF_M_Send(unsigned char *TX_Buf)
{

    NRF.Time_Out=0;					//?????????
    nrf24l01->TX_Mode();
    //OS.DelayTimeTick(1);
    this->wait(5);
    //????--????????????????????????
//        pthread_mutex_lock(&mutex);

    if(nrf24l01->NRF24L01_TxPacket(TX_Buf)==TX_OK)			 //??????,NRF24L01_TxPacket(TX_Buf)???????
    {
        nrf24l01->RX_Mode();														  //?????????
        while(nrf24l01->NRF24L01_RxPacket(RX_BUF)!=0)		//?????????????NRF24L01_RxPacket(RX_BUF)???????//////???????????0?????????????位??0???????????while???
        {
            //OS.DelayTimeTick(2);
            this->wait(2);
            NRF.Time_Out++;
            if(NRF.Time_Out >=NRF_TIME_OUT)
            {
                NRF.Ctrl = NRF_ERR_TIMEOUT;	//?????????????????????
                NRF.Time_Out++;
                return;
            }
        }
        nrftask->NRFTask_RX(RX_BUF,Tx_Buf);						//???????????
    }
    else			//??????? ?????????
    {
        NRF.Ctrl = NRF_ERR_SEND;
        NRF.ERR_SEND++;
    }
    //????
//       pthread_mutex_unlock(&mutex);

}
//CRC校验程序算法
int NRFTHREAD::CalCrc(int crc, unsigned char *buf, int len)
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
void NRFTHREAD::CRCResult(void)
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
void NRFTHREAD::NRF_M_CRTL(unsigned char *TX_Buf)				 //M 主站控制
{
    NRF.Ctrl = NRF_M_OK;
    while(NRF.Send)		//NRF.Send??????????????????????????????????1?????????????????????????????薪????????????????畏???????????????畏???
    {
        if(NRF.Ctrl != NRF_M_OK)
        {//??????
            DK.ErrN ++;
            Tx_Buf[0] |= NRF_REPEAT; //?????????NRF_REPEAT???????????????
            this->wait(10);
            //OS.DelayTimeTick(10);
        }
        NRF_M_Send(TX_Buf);
    }
}
void NRFTHREAD::NRFtask(void)
{
    unsigned char Success=0,Failure=0;
    unsigned char i=0;

    NRF.Ctrl = NRF_M_OK;
    DK.Ctrl = CTRL_STOP;
    nrftask->Send_DK_Action(NRF_CX_SYS);			//查询DK系统状态
//    NRF_M_CRTL(Tx_Buf);
    while(1)
    {
        //message = (u32)OS.PendMessageQueue(5);
        this->wait(10);
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
                Failure=digitalRead(2);//IRQ 数据传输失败               
            }
            if(Success)
            {
                NRF.Send = 0;
            }
        }
    }
}

