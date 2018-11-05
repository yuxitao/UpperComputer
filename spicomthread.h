#ifndef SPICOMTHREAD_H
#define SPICOMTHREAD_H

#include<QThread>//创建线程时需要包含的头文件
#include<QString>//创建线程时需要包含的头文件

class SPIComThread :public QThread//创建线程的时候需要继承线程类
{
    Q_OBJECT
public:
    SPIComThread();
    void run();
    int CalCrc(int crc, unsigned char *buf, int len);
    void CRCResult(void);
    void SPICom(void);
};

#endif // SPICOMTHREAD_H
