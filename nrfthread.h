#ifndef NRFTHREAD_H
#define NRFTHREAD_H
#include<QThread>
#include<QString>
#include "nrf24l01.h"
#include "nrftask.h"
#include "dk_conf.h"

extern unsigned char RunFlag;//
extern DiaoKe_Struct DK;  //雕刻机的数据结构体

class NRFTHREAD :public QThread
{
    Q_OBJECT
public:
    NRFTHREAD();
    virtual void run();
    void stop();
public:
    void NRF_M_CRTL(unsigned char *txbuf);
    void NRF_M_Init(void);
    void Switch_Buf(void);
    void NRF_M_Send(unsigned char *TX_Buf);
    void NRFtask(void);
    int  CalCrc(int crc, unsigned char *buf, int len);
    void  CRCResult(void);
    NRF24L01  *nrf24l01;
    NRFTask   *nrftask;
signals:
    void send(QString msg);
private:



};

#endif // NRFTHREAD_H
