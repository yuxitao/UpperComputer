#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QMainWindow>
#include <QtCore>// 增加定时器才可以��?
#include"location.h"
#include <QButtonGroup>
#include "nrfthread.h"
#include "sendgcodethread.h"//����G�������̶߳���
namespace Ui {
class MainControl;
}

class MainControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainControl(QWidget *parent = 0);
    ~MainControl();
    SendGcodeThread *sendGcodeThread;//����G�������߳�ָ�붨��
private slots:
    void on_pushButton_clicked();
    void reshow();//槽函数在这里定义

    void cornerConnectorButtonsToggled(int, bool);
    void cornerConnectorButtonsClicked(int);

    void keyHoleButtonsToggled(int, bool);
    void keyHoleButtonsClicked(int);
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_graphicsView_5_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

private:
    Ui::MainControl *ui;
    QTimer *switch_timer;//LED切换的定时器
    bool flag1;
private:
    void cornerConnectorDraw1();//定义了图显示函数
    void cornerConnectorDraw2();
    void cornerConnectorDraw3();
    void keyHoleDraw1();
    void keyHoleDraw2();
    void completeMaterialDraw1();
private:
    Location *location;
    NRFTHREAD *nrfthread;//
    int cornerConnectorRadioButtonChooseFlag;
    int keyHoleRadioButtonChooseFlag;
    int mergingData;
    QButtonGroup *cornerConnectorGroup;
    QButtonGroup *keyHoleGroup;

};

#endif // MAINCONTROL_H
