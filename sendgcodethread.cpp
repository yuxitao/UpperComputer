#include "sendgcodethread.h"
#include <QThread>//�����߳�ʱ��Ҫ������ͷ�ļ�
#include <QApplication>//�����߳�ʱ��Ҫ������ͷ�ļ�
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
    for(i =0;i<155;i++)//����G���룬�ܹ�Ϊ155��
    {
        nrftaskthree->Send_GCode(&GcodeMaterialSpeificationParameter[i]);
        this->wait(50);
        while(NRF.Send)
        {
            this->wait(50);
        }
    }
    DK.Ctrl = CTRL_START;						//�ӻ���ʼִ��G����ı�־
    nrftaskthree->Send_DK_Action(NRF_CX);			//����һ�β�ѯ�ӻ�״̬����
}
