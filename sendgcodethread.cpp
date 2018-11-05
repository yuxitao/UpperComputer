#include "sendgcodethread.h"
#include <QThread>//创建线程时需要包含的头文件
#include <QApplication>//创建线程时需要包含的头文件
#include "materialtypethree.h"
#include "dk_conf.h"
#include "gcode.h"


SendGcodeThread::SendGcodeThread()
{
    nrftaskthree = new NRFTask();
}
void SendGcodeThread::run()
{
    unsigned char i=0;
//		CalculateTestGcode();
    for(i =0;i<155;i++)//发送G代码，总共为155个
    {
        nrftaskthree->Send_GCode(&GcodeMaterialSpeificationParameter[i]);
        this->wait(50);
        while(NRF.Send)
        {
            this->wait(50);
        }
    }
    DK.Ctrl = CTRL_START;						//从机开始执行G代码的标志
    nrftaskthree->Send_DK_Action(NRF_CX);			//发送一次查询从机状态命令
}
