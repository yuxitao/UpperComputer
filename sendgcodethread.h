#ifndef SENDGCODETHREAD_H
#define SENDGCODETHREAD_H
#include<QThread>//创建线程时需要包含的头文件
#include<QString>//创建线程时需要包含的头文件
#include "nrftask.h"
class SendGcodeThread:public QThread//创建线程的时候需要继承线程类
{
public:
    SendGcodeThread();
    void run();
    NRFTask *nrftaskthree;
};

#endif // SENDGCODETHREAD_H
