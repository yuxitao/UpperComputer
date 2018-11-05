#include "maincontrol.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainControl w;
    w.move(100,100);//初始化显示主界面时的位置
    w.show();

    return a.exec();
    QTextCodec*codec = QTextCodec::codecForName("GBK");  //qt程序设置为GBK编码或UTF-8编码（有无ROM都可），都使用GBK
    //设置和对本地文件系统读写时候的默认编码格式
     QTextCodec::setCodecForLocale(codec);
}
