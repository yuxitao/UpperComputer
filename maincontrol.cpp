#include "maincontrol.h"
#include "ui_maincontrol.h"
#include"location.h"
#include "nrfthread.h"
#include <QButtonGroup>
#include <QPainter>
#include "wiringPi/wiringPi.h"
#include "wiringPi/wiringPiSPI.h"
#include <QTime>
#include <QApplication>
#include "wiringPi/wiringSerial.h"
#include "materialtypethree.h"//liaoxingsan
#include "materialtypeone.h"
#include "materialtypetwo.h"
#include "materialtypefour.h"
#include "materialtypefive.h"
#include "gcode.h"
MainControl::MainControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainControl)
{
    ui->setupUi(this);

    int l,m,n;
    unsigned char i=0,j=0;
    unsigned char data[38]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    mergingData =0;//鍒濆鍖栦竴涓?
    l = wiringPiSetup();
    m = wiringPiSPISetup(0,5000000);//5Mb/s
    n = wiringPiSPISetup(1,5000000);
    
    pinMode(2,INPUT);//IRQ
    
    pinMode(3,INPUT);//CE

    pinMode(1,OUTPUT);//CSN

    




    //int i=0;
    //wiringPiSetup();
    //for(i=0;i<8;i++)
    //{
    //    pinMode(i,OUTPUT);
    //}

    //   digitalWrite(0,LOW);//宸︽帓6浣庣數骞?
       //digitalWrite(1,HIGH);//鍙虫帓6楂樼數骞?


    /*test  spi*/
//    for(l=0;l<5000;l++)
//    {
//        wiringPiSPIDataRW(0,data,5);//濞村鐦疭PI閼奉亝鏁归懛顏勫絺閻ㄥ嫰妫舵０锟斤拷?
//        for(m=0;m<10;m++)
//        {
//            for(n=0;n<10;n++)
//            {
//                n =n;
//            }
//        }
    int fd;int l2=0,l3=0;

    l2=digitalRead(2);//IRQ 鏁版嵁浼犺緭澶辫触
    l3=digitalRead(3);//CE  鏁版嵁浼犺緭鎴愬姛
    fd = serialOpen("/dev/ttyAMA0",9600);
    for(i=0;i<200;i++)
    {
        serialPuts(fd , "data");
    }
    Clr_NRF24L01_CE;
    for(i=0;i<200;i++)
    {
       for(j=0;j<38;j++)
       {
            data[j] = 100-j;
        }
//         wiringPiSPIDataRW(0,data,34);//濞村鐦疭PI閼奉亝鏁归懛顏勫絺閻ㄥ嫰妫舵０锟斤拷?
    }
//    }
//    while (1) {
//        data1 = 0xcc;
//        for(i=0;i<8;i++)
//        {
//            if( data1&(1<<i))
//                addr |= 1<<(7-i);
//        }
//    }

    cornerConnectorGroup=new QButtonGroup(this);
    cornerConnectorGroup->addButton(ui->radioButton,1);//涓€涓€间负1
    cornerConnectorGroup->addButton(ui->radioButton_2,2);//涓€涓€间负2
    cornerConnectorGroup->addButton(ui->radioButton_3,3);//涓€涓€间负3

    keyHoleGroup=new QButtonGroup(this);
    keyHoleGroup->addButton(ui->radioButton_5,1);//涓€涓€间负1
    keyHoleGroup->addButton(ui->radioButton_6,2);//涓€涓€间负2

    ui->radioButton->setChecked(true);//璁剧疆宸﹁竟缁勪腑radioButton琚€変腑
    ui->radioButton_5->setChecked(true);//璁剧疆鍙宠竟缁剅adioButton_5琚€変腑

    cornerConnectorRadioButtonChooseFlag =1;//瀵硅鐮侀€夋嫨鏍囧織鍒濆鍖?
    keyHoleRadioButtonChooseFlag =1;//瀵归攣瀛旈€夋嫨鏍囧織鍒濆鍖?

    cornerConnectorRadioButtonChooseFlag = cornerConnectorGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    keyHoleRadioButtonChooseFlag = keyHoleGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    mergingData = (cornerConnectorRadioButtonChooseFlag<<3)|keyHoleRadioButtonChooseFlag;//灏嗕袱涓€煎悎骞朵负涓€涓娇鐢?

//    nrfthread = new NRFTHREAD();
//    nrfthread->start();

    sendGcodeThread = new SendGcodeThread();//发送G代码的线程指针

    cornerConnectorDraw1();//瑙掔爜鍥剧墖鏄剧ず
    cornerConnectorDraw2();
    cornerConnectorDraw3();
    keyHoleDraw1();//閿佸瓟鍥剧墖鏄剧ず
    keyHoleDraw2();
    completeMaterialDraw1();




     // 杩炴帴淇″彿
    connect(cornerConnectorGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(cornerConnectorButtonsToggled(int,bool)));
    connect(cornerConnectorGroup, SIGNAL(buttonClicked(int)), this, SLOT(cornerConnectorButtonsClicked(int)));
    connect(keyHoleGroup, SIGNAL(buttonClicked(int)), this, SLOT(keyHoleButtonsClicked(int)));
    connect(keyHoleGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(keyHoleButtonsToggled(int,bool)));


}

MainControl::~MainControl()
{
    delete ui;
}
void MainControl::reshow(){
    QWidget::move(100,100);//绉诲姩绐楀彛鐨勪綅缃?
    this->show();
}
void MainControl::on_pushButton_clicked()//瀹氫綅鐣岄潰鐨勮繑鍥炴寜閿?
{
    this->hide();
    location = new Location();
    connect(location,SIGNAL(sendsignal()),this,SLOT(reshow()));//淇″彿鍜屾Ы寤虹珛杩炴帴
    location->move(100,100);//绉诲姩绐楀彛鐨勪綅缃?
    location->show();
    cornerConnectorDraw1();
    cornerConnectorDraw2();
    cornerConnectorDraw3();
    keyHoleDraw1();
    keyHoleDraw2();
    completeMaterialDraw1();
}

void MainControl::cornerConnectorDraw1()
{
    QGraphicsScene* originalScene1 =new QGraphicsScene(this);
    ui->graphicsView1->setScene(originalScene1);
    QPixmap* pix1=new QPixmap("/home/pi/UpperComputer/resource/方形角码22.bmp");
    originalScene1->addPixmap(*pix1);
    ui->graphicsView1->show();
}
void MainControl::cornerConnectorDraw2()
{
    QGraphicsScene* originalScene2 =new QGraphicsScene(this);
    ui->graphicsView_2->setScene(originalScene2);
    QPixmap* pix2=new QPixmap("/home/pi/UpperComputer/resource/圆方角码11.bmp");
    originalScene2->addPixmap(*pix2);
    ui->graphicsView_2->show();
}
void MainControl::cornerConnectorDraw3()
{
    QGraphicsScene* originalScene3 =new QGraphicsScene(this);
    ui->graphicsView_3->setScene(originalScene3);
    QPixmap* pix3=new QPixmap("/home/pi/UpperComputer/resource/圆角方形角码33.bmp");
    originalScene3->addPixmap(*pix3);
    ui->graphicsView_3->show();
}
void MainControl::keyHoleDraw1()
{
    QGraphicsScene* originalScene4 =new QGraphicsScene(this);
    ui->graphicsView_5->setScene(originalScene4);
    QPixmap* pix4=new QPixmap("/home/pi/UpperComputer/resource/方形锁孔图形.bmp");
    originalScene4->addPixmap(*pix4);
    ui->graphicsView_5->show();
}
void MainControl::keyHoleDraw2()
{
    QGraphicsScene* originalScene5 =new QGraphicsScene(this);
    ui->graphicsView_6->setScene(originalScene5);
    QPixmap* pix5=new QPixmap("/home/pi/UpperComputer/resource/圆形锁孔图形.bmp");
    originalScene5->addPixmap(*pix5);
    ui->graphicsView_6->show();
}
void MainControl::completeMaterialDraw1()
{
    QGraphicsScene* originalScene6 =new QGraphicsScene(this);
    ui->graphicsView->setScene(originalScene6);
    QPixmap* pix6=new QPixmap("/home/pi/UpperComputer/resource/方角码方锁孔1.bmp");
    QPixmap* pix7=new QPixmap("/home/pi/UpperComputer/resource/园方角码方锁孔2.bmp");
    QPixmap* pix8=new QPixmap("/home/pi/UpperComputer/resource/圆方圆角角码方锁孔3.bmp");
    QPixmap* pix9=new QPixmap("/home/pi/UpperComputer/resource/方角码圆锁孔4.bmp");
    QPixmap* pix10=new QPixmap("/home/pi/UpperComputer/resource/园方角码圆锁孔5.bmp");
    switch (mergingData) {
    case 9:
        originalScene6->addPixmap(*pix6);
        break;
    case 17:
         originalScene6->addPixmap(*pix7);
        break;
    case 25:
         originalScene6->addPixmap(*pix8);
        break;
    case 10:
         originalScene6->addPixmap(*pix9);
        break;
    case 18:
         originalScene6->addPixmap(*pix10);
        break;
    default:
        break;
    }
    ui->graphicsView->show();
}
void MainControl::cornerConnectorButtonsToggled(int id, bool status)
{

}

void MainControl::cornerConnectorButtonsClicked(int id)
{
    cornerConnectorRadioButtonChooseFlag = cornerConnectorGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    keyHoleRadioButtonChooseFlag = keyHoleGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    mergingData = (cornerConnectorRadioButtonChooseFlag<<3)|keyHoleRadioButtonChooseFlag;//灏嗕袱涓€煎悎骞朵负涓€涓娇鐢?
    completeMaterialDraw1();
}

void MainControl::keyHoleButtonsToggled(int id, bool state)
{

}

void MainControl::keyHoleButtonsClicked(int id)
{
    cornerConnectorRadioButtonChooseFlag = cornerConnectorGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    keyHoleRadioButtonChooseFlag = keyHoleGroup->checkedId();//鍙栧埌浣犳墍閫夌殑radioButton鐨勫€?
    mergingData = (cornerConnectorRadioButtonChooseFlag<<3)|keyHoleRadioButtonChooseFlag;//灏嗕袱涓€煎悎骞朵负涓€涓娇鐢?
    completeMaterialDraw1();
}




void MainControl::on_pushButton_5_clicked()
{
    unsigned char i=0;
    switch (mergingData)
    {
        case 9://料型一
                CalculateMaterialtypeoneGcode();
                sendGcodeThread->start();

            break;
        case 17://料型二
                CalculateMaterialtypetwoGcode();
                sendGcodeThread->start();
            break;
        case 25://料型三
                CalculateMaterialtypethreeGcode();
                sendGcodeThread->start();
            break;
        case 10://料型四
                CalculateMaterialtypefourGcode();
                sendGcodeThread->start();
            break;
        case 18://料型五
                CalculateMaterialtypefiveGcode();
                sendGcodeThread->start();
            break;
        default:
            break;
    }
}

void MainControl::on_pushButton_3_clicked()
{

}

void MainControl::on_graphicsView_5_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}
