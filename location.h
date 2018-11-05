#ifndef LOCATION_H
#define LOCATION_H
#include "nrftask.h"
#include <QDialog>
#include "nrf_ctrl.h"

namespace Ui {
class Location;
}
#define SetBit(data, offset)         (data |= 1U << offset)
#define ResetBit(data, offset)       (data &= ~(1U << offset))
#define GetBit(data, offset)         ((data >> offset) &0x01)

#define UintToByte3(data)               ((unsigned char *)(&(data)))[3]
#define UintToByte2(data)               ((unsigned char *)(&(data)))[2]
#define UintToByte1(data)               ((unsigned char *)(&(data)))[1]
#define UintToByte0(data)               ((unsigned char *)(&(data)))[0]

#define UintToUshort1(data)             ((unsigned short int *)(&(data)))[1]
#define UintToUshort0(data)             ((unsigned short *)(&(data)))[0]

class Location : public QDialog
{
    Q_OBJECT

public:
    explicit Location(QWidget *parent = 0);
    ~Location();
    void SendDWParameter(void);
    void DW_Up(void);
    void DW_Up_XReturnZero(void);//X轴回零点按键弹起
    void DW_Up_YReturnZero(void);//Y轴回零点按键弹起
    void DW_Up_ZReturnZero(void);//Z轴回零点按键弹起
    void DW_Up_USawPositive45Angl(void);//U轴锯旋转电机+45按键弹起
    void DW_Up_USawNegative45Angle(void);//U轴锯旋转电机-45按键弹起
    void DW_Up_VSpindlePositive90Angle(void);//V轴锯旋转电机+90按键弹起
    void DW_Up_VSpindleNegative90Angle(void);//V轴锯旋转电机-90按键弹起
    void DW_LeftFront_Down(void);//左前
    void DW_Right_Down(void);//X右
    void DW_RightFront_Down(void);//右前
    void DW_Back_Down(void);//Y后
    void DW_Front_Down(void);//Y前
    void DW_LeftBack_Down(void);//左后
    void DW_Left_Down(void);//X左
    void DW_RightBack_Down(void);//右后
    void DW_XY_0(void);
    void DW_Z_Dn_Down(void);//Z轴下
    void DW_Z_Up_Down(void);//Z轴上
    void DW_NextPage(void);//定位界面下一页
    void DW_MainMotoOn(void);//主轴开
    void DW_MainMotoOff(void);//主轴关
    void DW_USawPositiveRotate_Down(void);//锯旋转角度电机正转
    void DW_USawNegativeRotate_Down(void);//锯旋转角度电机反转
    void DW_USawPositive45Angl_Down(void);//锯旋转角度电机正转45
    void DW_USawNegative45Angle_Down(void);//锯旋转角度电机反转45
    void DW_VSpindlePositiveRotate_Down(void);//主轴旋转角度电机正转
    void DW_VSpindleNegativeRotate_Down(void);//主轴旋转角度电机反转
    void DW_VSpindlePositive90Angle_Down(void);//主轴旋转角度电机正转90
    void DW_VSpindleNegative90Angle_Down(void);//主轴旋转角度电机反转90
    void DW_ClampAdvance_Down(void);//夹具电机前进
    void DW_ClampBack_Down(void);//夹具电机后退
    void DW_SawOn_Down(void);//锯电机旋转开
    void DW_SawOff_Down(void);//锯电机旋转关
    void DW_B_XAixReturnOrignalPoint_Down(void);//X轴回机械原点
    void DW_B_YAixReturnOrignalPoint_Down(void);//Y轴回机械原点
    void DW_B_ZAixReturnOrignalPoint_Down(void);//Z轴回机械原点
    void DW_CylinderOneON_Down(void);//气缸1开，锯下降气缸
    void DW_CylinderOneOFF_Down(void);//气缸1关，锯提升气缸
    void DW_CylinderTwoON_Down(void);//气缸2开，主轴下降气缸
    void DW_CylinderTwoOFF_Down(void);//气缸2关，主轴提升气缸
    void DW_CylinderThreeON_Down(void);//气缸3开，料夹紧气缸
    void DW_CylinderThreeOFF_Down(void);//气缸3关，料松开气缸
    void DW_CylinderFourON_Down(void);//气缸4开，主轴卡紧气缸
    void DW_CylinderFourOFF_Down(void);//气缸4关，主轴松开气缸
    void DW_CylinderFiveON_Down(void);//气缸5开，锯固定气缸夹紧
    void DW_CylinderFiveOFF_Down(void);//气缸5关，锯固定气缸松开
    void SawPositiveAngleSendOne_Down(void);//锯正转45角度补偿值发送按钮1按钮按下函数
    void SawPositiveAngleSendOne_Up(void);//锯正转45角度补偿值发送按钮1按钮抬起函数
    void SawNegativeAngleSendTwo_Down(void);//锯反转45角度补偿值发送按钮2按钮按下函数
    void SawNegativeAngleSendTwo_Up(void);//锯反转45角度补偿值发送按钮2按钮抬起函数
    NRFTask *nrftasktwo;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_41_clicked();

signals:
    /*
    * 信号必须要signals关键字来声明
    * 信号没有返回值, 但可以有参数
    * 信号就是函数的声明, 无需定义
    * 使用: emit mySignal();
    * 信号可以被重载
    */
    void sendsignal();
private:
    Ui::Location *ui;
};

#endif // LOCATION_H
