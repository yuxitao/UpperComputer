#ifndef SPICOMTHREAD_H
#define SPICOMTHREAD_H

#include<QThread>//�����߳�ʱ��Ҫ������ͷ�ļ�
#include<QString>//�����߳�ʱ��Ҫ������ͷ�ļ�

class SPIComThread :public QThread//�����̵߳�ʱ����Ҫ�̳��߳���
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
