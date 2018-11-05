#include "location.h"
#include "ui_location.h"
#include "nrfthread.h"
#include "dk_conf.h"
unsigned char DW_Speed;
unsigned char DW_XY_Key;
unsigned char DW_Z_Key;

unsigned char DW_U_Key;//U轴
unsigned char DW_V_Key;//V轴
unsigned char DW_W_Key;//W轴

unsigned char Saw_Key;//锯开关
unsigned char SawCylinderOneKey;
unsigned char SpindleCylinderTwoKey;


unsigned char CylinderThreeClampKey;//料夹具气缸
unsigned char CylinderFourSpindleFixKey;
unsigned char CylinderFiveSawFixKey;

signed int SawPositiveAngleSetParameter =300;//锯正转45补偿角度设置,用于存储edit控件输入的数值
signed int SawNegativeAngleSetParameter =300;//锯反转45补偿角度设置,用于存储edit控件输入的数值

unsigned short int SawPositiveAngleSetParameterNRFSend =0;//锯正转45补偿角度设置，将edit控件输入的32位数值变为16位用于NRF发送，NRF发送16位节约数据带宽
unsigned short int SawNegativeAngleSetParameterNRFSend =0;//锯反转45补偿角度设置，将edit控件输入的32位数值变为16位用于NRF发送，NRF发送16位节约数据带宽



Location::Location(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Location)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1);
    nrftasktwo =new NRFTask();
}

Location::~Location()
{
    delete ui;
}

void Location::on_pushButton_clicked()
{
    emit sendsignal();
    this->close();
}
//发送定位参数
void Location::SendDWParameter(void)
{
    DK.Ctrl = CTRL_SET_DW;
    if(DW_XY_Key || DW_Z_Key) DW_Speed ++;	//当X、Y、Z按下的时候，按下几次速度减小几次，最多减小到10
    if(DW_Speed>=10) DW_Speed = 10;//最大到10，再大了电机就会驱动不起来
    if(DK.Ctrl == CTRL_STOP)		return;		//停止
    if(DK.Alarm)	return;		//有故障退出自动
    if(NRF.Send == 0)	//等待上次发送完成
    {
        nrftasktwo->Send_DW(DW_Speed,DW_XY_Key,DW_Z_Key,DW_U_Key,DW_V_Key,DW_W_Key,Saw_Key,SawCylinderOneKey,SpindleCylinderTwoKey,CylinderThreeClampKey,CylinderFourSpindleFixKey,CylinderFiveSawFixKey,SawPositiveAngleSetParameterNRFSend,SawNegativeAngleSetParameterNRFSend);
    }
}
void Location::DW_Up(void)
{
    DW_Z_Key = 0;
    DW_XY_Key = 0;

    DW_U_Key = 0;//U轴
  DW_V_Key = 0;//V轴
  DW_W_Key = 0;//W轴


    DW_Speed =0;
    DW_Speed = 0;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_Up_XReturnZero(void)//X轴回零点按键弹起
{
    DW_XY_Key = 0;
}

void Location::DW_Up_YReturnZero(void)//Y轴回零点按键弹起
{
    DW_XY_Key = 0;
}
void Location::DW_Up_ZReturnZero(void)//Z轴回零点按键弹起
{
    DW_Z_Key = 0;
}
void Location::DW_Up_USawPositive45Angl(void)//U轴锯旋转电机+45按键弹起
{
    ResetBit(DW_U_Key,7);//将变量8位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数

}
void Location::DW_Up_USawNegative45Angle(void)//U轴锯旋转电机-45按键弹起
{
    ResetBit(DW_U_Key,7);//将变量8位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_Up_VSpindlePositive90Angle(void)//V轴锯旋转电机+90按键弹起
{

}
void Location::DW_Up_VSpindleNegative90Angle(void)//V轴锯旋转电机-90按键弹起
{

}
void Location::DW_LeftFront_Down(void)//左前
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_LeftFront;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}


void Location::DW_Right_Down(void)//X右
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Right;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_RightFront_Down(void)//右前
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_RightFront;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_Back_Down(void)//Y后
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Back;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_Front_Down(void)//Y前
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Front;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_LeftBack_Down(void)//左后
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_LeftBack;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_Left_Down(void)//X左
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Left;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_RightBack_Down(void)//右后
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_RightBack;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_XY_0(void)
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_XY_0;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_Z_Dn_Down(void)//Z轴下
{
    DW_Z_Key = DW_NUM_Z_DN;
    DW_XY_Key = DW_NUM_NULL;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_Z_Up_Down(void)//Z轴上
{
    DW_Z_Key = DW_NUM_Z_UP;
    DW_XY_Key = DW_NUM_NULL;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_MainMotoOn(void)//主轴开
{
    DK.State_B_P->Spindle_On = 1;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_MainMotoOff(void)//主轴关
{
    DK.State_B_P->Spindle_On = 0;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_USawPositiveRotate_Down(void)//锯旋转角度电机正转
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_Positive;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_USawNegativeRotate_Down(void)//锯旋转角度电机反转
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_Negative;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_USawPositive45Angl_Down(void)//锯旋转角度电机正转45
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_ReturnToPositive45;
    SetBit(DW_U_Key,7);//将变量8位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_USawNegative45Angle_Down(void)//锯旋转角度电机反转45
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_ReturnToNegative45;
    SetBit(DW_U_Key,7);//将变量8位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_VSpindlePositiveRotate_Down(void)//主轴旋转角度电机正转
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_Positive;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_VSpindleNegativeRotate_Down(void)//主轴旋转角度电机反转
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_Negative;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_VSpindlePositive90Angle_Down(void)//主轴旋转角度电机正转90
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_ReturnToPositive90;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_VSpindleNegative90Angle_Down(void)//主轴旋转角度电机反转90
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_ReturnToNegative90;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_ClampAdvance_Down(void)//夹具电机前进
{
    DW_Z_Key = 0;
    DW_W_Key = DW_NUM_W_Forward;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_ClampBack_Down(void)//夹具电机后退
{
    DW_Z_Key = 0;
    DW_W_Key = DW_NUM_W_Back;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_SawOn_Down(void)//锯电机旋转开
{
    Saw_Key = DW_SAWON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数

}
void Location::DW_SawOff_Down(void)//锯电机旋转关
{
    Saw_Key = DW_SAWOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数

}

void Location::DW_B_XAixReturnOrignalPoint_Down(void)//X轴回机械原点
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_X_ReturnToZero;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_B_YAixReturnOrignalPoint_Down(void)//Y轴回机械原点
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Y_ReturnToZero;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::DW_B_ZAixReturnOrignalPoint_Down(void)//Z轴回机械原点
{
    DW_XY_Key = DW_NUM_NULL;
    DW_Z_Key = DW_NUM_Z_ReturnToZero;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}



/*****************************************************
***********定位操作页面2的按钮控件********************
**************按下函数设置**********************
*******************************************************/

void Location::DW_CylinderOneON_Down(void)//气缸1开，锯下降气缸
{
    SawCylinderOneKey	 =	DW_SAWCylinderOneON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数

}
void Location::DW_CylinderOneOFF_Down(void)//气缸1关，锯提升气缸
{
    SawCylinderOneKey	 =	DW_SAWCylinderOneOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderTwoON_Down(void)//气缸2开，主轴下降气缸
{
    SpindleCylinderTwoKey = DW_SpindleCylinderTwoON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderTwoOFF_Down(void)//气缸2关，主轴提升气缸
{
    SpindleCylinderTwoKey = DW_SpindleCylinderTwoOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderThreeON_Down(void)//气缸3开，料夹紧气缸
{
    CylinderThreeClampKey	 =	DW_CylinderThreeClampON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderThreeOFF_Down(void)//气缸3关，料松开气缸
{
    CylinderThreeClampKey	 =	DW_CylinderThreeClampOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderFourON_Down(void)//气缸4开，主轴卡紧气缸
{
    CylinderFourSpindleFixKey =	DW_CylinderFourSpindleFixON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderFourOFF_Down(void)//气缸4关，主轴松开气缸
{
    CylinderFourSpindleFixKey =	DW_CylinderFourSpindleFixOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderFiveON_Down(void)//气缸5开，锯固定气缸夹紧
{
    CylinderFiveSawFixKey =	DW_CylinderFiveSawFixON;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::DW_CylinderFiveOFF_Down(void)//气缸5关，锯固定气缸松开
{
    CylinderFiveSawFixKey =	DW_CylinderFiveSawFixOFF;
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}

void Location::SawPositiveAngleSendOne_Down(void)//锯正转45角度补偿值发送按钮1按钮按下函数
{
    SawPositiveAngleSetParameterNRFSend = SawPositiveAngleSetParameter;
    SetBit(SawPositiveAngleSetParameterNRFSend,15);//将变量16位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::SawPositiveAngleSendOne_Up(void)//锯正转45角度补偿值发送按钮1按钮抬起函数
{
    ResetBit(SawPositiveAngleSetParameterNRFSend,15);//将变量16位置为1
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::SawNegativeAngleSendTwo_Down(void)//锯反转45角度补偿值发送按钮2按钮按下函数
{
    SawNegativeAngleSetParameterNRFSend = SawNegativeAngleSetParameter;
    SetBit(SawNegativeAngleSetParameterNRFSend,15);//将变量16位置为1,修改了定位发送参数为按下发送一次后，不需要置位复位了
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}
void Location::SawNegativeAngleSendTwo_Up(void)//锯反转45角度补偿值发送按钮2按钮抬起函数
{
    ResetBit(SawNegativeAngleSetParameterNRFSend,15);//将变量16位置为1,修改了定位发送参数为按下发送一次后，不需要置位复位了
    SendDWParameter();//发送定位参数，包括很多项，速度，几个轴等位置参数
}



void Location::on_pushButton_2_clicked()
{
    DW_LeftFront_Down();//左前
}

void Location::on_pushButton_3_clicked()
{
    DW_Front_Down();//Y轴前
}

void Location::on_pushButton_4_clicked()
{
    DW_RightFront_Down();//右前
}

void Location::on_pushButton_9_clicked()
{
    DW_Right_Down();//X轴右
}

void Location::on_pushButton_7_clicked()
{
    DW_Left_Down();//X轴左
}

void Location::on_pushButton_8_clicked()
{

}

void Location::on_pushButton_5_clicked()
{
     DW_Z_Up_Down();//Z轴上
}

void Location::on_pushButton_15_clicked()
{
    DW_Z_Dn_Down();//Z轴下
}

void Location::on_pushButton_14_clicked()
{
    DW_RightBack_Down();//右后
}

void Location::on_pushButton_13_clicked()
{
    DW_Back_Down();//Y后
}

void Location::on_pushButton_12_clicked()
{
    DW_LeftBack_Down();//左后
}

void Location::on_pushButton_6_clicked()
{
    DW_MainMotoOn();//主轴开
}

void Location::on_pushButton_11_clicked()
{
    DW_MainMotoOff();//主轴关
}

void Location::on_pushButton_17_clicked()
{
    DW_USawPositiveRotate_Down();//锯旋转角度电机正转
}

void Location::on_pushButton_18_clicked()
{
    DW_USawNegativeRotate_Down();//锯旋转角度电机反转
}

void Location::on_pushButton_19_clicked()
{
    DW_USawPositive45Angl_Down();//锯旋转角度电机正转45
}

void Location::on_pushButton_20_clicked()
{
    DW_USawNegative45Angle_Down();//锯旋转角度电机反转45
}

void Location::on_pushButton_22_clicked()
{
    DW_VSpindlePositiveRotate_Down();//主轴旋转角度电机正转
}

void Location::on_pushButton_23_clicked()
{
    DW_VSpindleNegativeRotate_Down();//主轴旋转角度电机反转
}

void Location::on_pushButton_24_clicked()
{
    DW_VSpindlePositive90Angle_Down();//主轴旋转角度电机正转90
}

void Location::on_pushButton_25_clicked()
{
    DW_VSpindleNegative90Angle_Down();//主轴旋转角度电机反转90
}

void Location::on_pushButton_27_clicked()
{
    DW_ClampAdvance_Down();//夹具电机前进
}

void Location::on_pushButton_28_clicked()
{
    DW_ClampBack_Down();//夹具电机后退
}

void Location::on_pushButton_29_clicked()
{
    DW_SawOn_Down();//锯电机旋转开
}

void Location::on_pushButton_30_clicked()
{
    DW_SawOff_Down();//锯电机旋转关
}

void Location::on_pushButton_32_clicked()
{
    DW_CylinderOneON_Down();//气缸1开，锯下降气缸
}

void Location::on_pushButton_37_clicked()
{
    DW_CylinderOneOFF_Down();//气缸1关，锯提升气缸
}

void Location::on_pushButton_33_clicked()
{
    DW_CylinderTwoON_Down();//气缸2开，主轴下降气缸
}

void Location::on_pushButton_38_clicked()
{
    DW_CylinderTwoOFF_Down();//气缸2关，主轴提升气缸
}

void Location::on_pushButton_34_clicked()
{
    DW_CylinderThreeON_Down();//气缸3开，料夹紧气缸
}

void Location::on_pushButton_39_clicked()
{
    DW_CylinderThreeOFF_Down();//气缸3关，料松开气缸
}

void Location::on_pushButton_35_clicked()
{
    DW_CylinderFourON_Down();//气缸4开，主轴卡紧气缸
}

void Location::on_pushButton_40_clicked()
{
    DW_CylinderFourOFF_Down();//气缸4关，主轴松开气缸
}

void Location::on_pushButton_36_clicked()
{
    DW_CylinderFiveON_Down();//气缸5开，锯固定气缸夹紧
}

void Location::on_pushButton_41_clicked()
{
    DW_CylinderFiveOFF_Down();//气缸5关，锯固定气缸松开
}
