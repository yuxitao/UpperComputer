#ifndef SENDGCODETHREAD_H
#define SENDGCODETHREAD_H
#include<QThread>//�����߳�ʱ��Ҫ������ͷ�ļ�
#include<QString>//�����߳�ʱ��Ҫ������ͷ�ļ�
#include "nrftask.h"
class SendGcodeThread:public QThread//�����̵߳�ʱ����Ҫ�̳��߳���
{
public:
    SendGcodeThread();
    void run();
    NRFTask *nrftaskthree;
};

#endif // SENDGCODETHREAD_H
