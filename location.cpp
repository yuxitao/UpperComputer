#include "location.h"
#include "ui_location.h"
#include "nrfthread.h"
#include "dk_conf.h"
unsigned char DW_Speed;
unsigned char DW_XY_Key;
unsigned char DW_Z_Key;

unsigned char DW_U_Key;//U��
unsigned char DW_V_Key;//V��
unsigned char DW_W_Key;//W��

unsigned char Saw_Key;//�⿪��
unsigned char SawCylinderOneKey;
unsigned char SpindleCylinderTwoKey;


unsigned char CylinderThreeClampKey;//�ϼо�����
unsigned char CylinderFourSpindleFixKey;
unsigned char CylinderFiveSawFixKey;

signed int SawPositiveAngleSetParameter =300;//����ת45�����Ƕ�����,���ڴ洢edit�ؼ��������ֵ
signed int SawNegativeAngleSetParameter =300;//�ⷴת45�����Ƕ�����,���ڴ洢edit�ؼ��������ֵ

unsigned short int SawPositiveAngleSetParameterNRFSend =0;//����ת45�����Ƕ����ã���edit�ؼ������32λ��ֵ��Ϊ16λ����NRF���ͣ�NRF����16λ��Լ���ݴ���
unsigned short int SawNegativeAngleSetParameterNRFSend =0;//�ⷴת45�����Ƕ����ã���edit�ؼ������32λ��ֵ��Ϊ16λ����NRF���ͣ�NRF����16λ��Լ���ݴ���



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
//���Ͷ�λ����
void Location::SendDWParameter(void)
{
    DK.Ctrl = CTRL_SET_DW;
    if(DW_XY_Key || DW_Z_Key) DW_Speed ++;	//��X��Y��Z���µ�ʱ�򣬰��¼����ٶȼ�С���Σ�����С��10
    if(DW_Speed>=10) DW_Speed = 10;//���10���ٴ��˵���ͻ�����������
    if(DK.Ctrl == CTRL_STOP)		return;		//ֹͣ
    if(DK.Alarm)	return;		//�й����˳��Զ�
    if(NRF.Send == 0)	//�ȴ��ϴη������
    {
        nrftasktwo->Send_DW(DW_Speed,DW_XY_Key,DW_Z_Key,DW_U_Key,DW_V_Key,DW_W_Key,Saw_Key,SawCylinderOneKey,SpindleCylinderTwoKey,CylinderThreeClampKey,CylinderFourSpindleFixKey,CylinderFiveSawFixKey,SawPositiveAngleSetParameterNRFSend,SawNegativeAngleSetParameterNRFSend);
    }
}
void Location::DW_Up(void)
{
    DW_Z_Key = 0;
    DW_XY_Key = 0;

    DW_U_Key = 0;//U��
  DW_V_Key = 0;//V��
  DW_W_Key = 0;//W��


    DW_Speed =0;
    DW_Speed = 0;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_Up_XReturnZero(void)//X�����㰴������
{
    DW_XY_Key = 0;
}

void Location::DW_Up_YReturnZero(void)//Y�����㰴������
{
    DW_XY_Key = 0;
}
void Location::DW_Up_ZReturnZero(void)//Z�����㰴������
{
    DW_Z_Key = 0;
}
void Location::DW_Up_USawPositive45Angl(void)//U�����ת���+45��������
{
    ResetBit(DW_U_Key,7);//������8λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���

}
void Location::DW_Up_USawNegative45Angle(void)//U�����ת���-45��������
{
    ResetBit(DW_U_Key,7);//������8λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_Up_VSpindlePositive90Angle(void)//V�����ת���+90��������
{

}
void Location::DW_Up_VSpindleNegative90Angle(void)//V�����ת���-90��������
{

}
void Location::DW_LeftFront_Down(void)//��ǰ
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_LeftFront;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}


void Location::DW_Right_Down(void)//X��
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Right;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_RightFront_Down(void)//��ǰ
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_RightFront;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_Back_Down(void)//Y��
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Back;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_Front_Down(void)//Yǰ
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Front;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_LeftBack_Down(void)//���
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_LeftBack;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_Left_Down(void)//X��
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Left;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_RightBack_Down(void)//�Һ�
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_RightBack;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_XY_0(void)
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_XY_0;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_Z_Dn_Down(void)//Z����
{
    DW_Z_Key = DW_NUM_Z_DN;
    DW_XY_Key = DW_NUM_NULL;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_Z_Up_Down(void)//Z����
{
    DW_Z_Key = DW_NUM_Z_UP;
    DW_XY_Key = DW_NUM_NULL;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_MainMotoOn(void)//���Ὺ
{
    DK.State_B_P->Spindle_On = 1;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_MainMotoOff(void)//�����
{
    DK.State_B_P->Spindle_On = 0;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_USawPositiveRotate_Down(void)//����ת�Ƕȵ����ת
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_Positive;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_USawNegativeRotate_Down(void)//����ת�Ƕȵ����ת
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_Negative;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_USawPositive45Angl_Down(void)//����ת�Ƕȵ����ת45
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_ReturnToPositive45;
    SetBit(DW_U_Key,7);//������8λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_USawNegative45Angle_Down(void)//����ת�Ƕȵ����ת45
{
    DW_Z_Key = 0;
    DW_U_Key = DW_NUM_U_ReturnToNegative45;
    SetBit(DW_U_Key,7);//������8λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_VSpindlePositiveRotate_Down(void)//������ת�Ƕȵ����ת
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_Positive;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_VSpindleNegativeRotate_Down(void)//������ת�Ƕȵ����ת
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_Negative;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_VSpindlePositive90Angle_Down(void)//������ת�Ƕȵ����ת90
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_ReturnToPositive90;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_VSpindleNegative90Angle_Down(void)//������ת�Ƕȵ����ת90
{
    DW_Z_Key = 0;
    DW_V_Key = DW_NUM_V_ReturnToNegative90;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_ClampAdvance_Down(void)//�оߵ��ǰ��
{
    DW_Z_Key = 0;
    DW_W_Key = DW_NUM_W_Forward;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_ClampBack_Down(void)//�оߵ������
{
    DW_Z_Key = 0;
    DW_W_Key = DW_NUM_W_Back;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_SawOn_Down(void)//������ת��
{
    Saw_Key = DW_SAWON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���

}
void Location::DW_SawOff_Down(void)//������ת��
{
    Saw_Key = DW_SAWOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���

}

void Location::DW_B_XAixReturnOrignalPoint_Down(void)//X��ػ�еԭ��
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_X_ReturnToZero;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_B_YAixReturnOrignalPoint_Down(void)//Y��ػ�еԭ��
{
    DW_Z_Key = 0;
    DW_XY_Key = DW_NUM_Y_ReturnToZero;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::DW_B_ZAixReturnOrignalPoint_Down(void)//Z��ػ�еԭ��
{
    DW_XY_Key = DW_NUM_NULL;
    DW_Z_Key = DW_NUM_Z_ReturnToZero;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}



/*****************************************************
***********��λ����ҳ��2�İ�ť�ؼ�********************
**************���º�������**********************
*******************************************************/

void Location::DW_CylinderOneON_Down(void)//����1�������½�����
{
    SawCylinderOneKey	 =	DW_SAWCylinderOneON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���

}
void Location::DW_CylinderOneOFF_Down(void)//����1�أ�����������
{
    SawCylinderOneKey	 =	DW_SAWCylinderOneOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderTwoON_Down(void)//����2���������½�����
{
    SpindleCylinderTwoKey = DW_SpindleCylinderTwoON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderTwoOFF_Down(void)//����2�أ�������������
{
    SpindleCylinderTwoKey = DW_SpindleCylinderTwoOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderThreeON_Down(void)//����3�����ϼн�����
{
    CylinderThreeClampKey	 =	DW_CylinderThreeClampON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderThreeOFF_Down(void)//����3�أ����ɿ�����
{
    CylinderThreeClampKey	 =	DW_CylinderThreeClampOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderFourON_Down(void)//����4�������Ῠ������
{
    CylinderFourSpindleFixKey =	DW_CylinderFourSpindleFixON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderFourOFF_Down(void)//����4�أ������ɿ�����
{
    CylinderFourSpindleFixKey =	DW_CylinderFourSpindleFixOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderFiveON_Down(void)//����5������̶����׼н�
{
    CylinderFiveSawFixKey =	DW_CylinderFiveSawFixON;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::DW_CylinderFiveOFF_Down(void)//����5�أ���̶������ɿ�
{
    CylinderFiveSawFixKey =	DW_CylinderFiveSawFixOFF;
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}

void Location::SawPositiveAngleSendOne_Down(void)//����ת45�ǶȲ���ֵ���Ͱ�ť1��ť���º���
{
    SawPositiveAngleSetParameterNRFSend = SawPositiveAngleSetParameter;
    SetBit(SawPositiveAngleSetParameterNRFSend,15);//������16λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::SawPositiveAngleSendOne_Up(void)//����ת45�ǶȲ���ֵ���Ͱ�ť1��ţ̌����
{
    ResetBit(SawPositiveAngleSetParameterNRFSend,15);//������16λ��Ϊ1
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::SawNegativeAngleSendTwo_Down(void)//�ⷴת45�ǶȲ���ֵ���Ͱ�ť2��ť���º���
{
    SawNegativeAngleSetParameterNRFSend = SawNegativeAngleSetParameter;
    SetBit(SawNegativeAngleSetParameterNRFSend,15);//������16λ��Ϊ1,�޸��˶�λ���Ͳ���Ϊ���·���һ�κ󣬲���Ҫ��λ��λ��
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}
void Location::SawNegativeAngleSendTwo_Up(void)//�ⷴת45�ǶȲ���ֵ���Ͱ�ť2��ţ̌����
{
    ResetBit(SawNegativeAngleSetParameterNRFSend,15);//������16λ��Ϊ1,�޸��˶�λ���Ͳ���Ϊ���·���һ�κ󣬲���Ҫ��λ��λ��
    SendDWParameter();//���Ͷ�λ�����������ܶ���ٶȣ��������λ�ò���
}



void Location::on_pushButton_2_clicked()
{
    DW_LeftFront_Down();//��ǰ
}

void Location::on_pushButton_3_clicked()
{
    DW_Front_Down();//Y��ǰ
}

void Location::on_pushButton_4_clicked()
{
    DW_RightFront_Down();//��ǰ
}

void Location::on_pushButton_9_clicked()
{
    DW_Right_Down();//X����
}

void Location::on_pushButton_7_clicked()
{
    DW_Left_Down();//X����
}

void Location::on_pushButton_8_clicked()
{

}

void Location::on_pushButton_5_clicked()
{
     DW_Z_Up_Down();//Z����
}

void Location::on_pushButton_15_clicked()
{
    DW_Z_Dn_Down();//Z����
}

void Location::on_pushButton_14_clicked()
{
    DW_RightBack_Down();//�Һ�
}

void Location::on_pushButton_13_clicked()
{
    DW_Back_Down();//Y��
}

void Location::on_pushButton_12_clicked()
{
    DW_LeftBack_Down();//���
}

void Location::on_pushButton_6_clicked()
{
    DW_MainMotoOn();//���Ὺ
}

void Location::on_pushButton_11_clicked()
{
    DW_MainMotoOff();//�����
}

void Location::on_pushButton_17_clicked()
{
    DW_USawPositiveRotate_Down();//����ת�Ƕȵ����ת
}

void Location::on_pushButton_18_clicked()
{
    DW_USawNegativeRotate_Down();//����ת�Ƕȵ����ת
}

void Location::on_pushButton_19_clicked()
{
    DW_USawPositive45Angl_Down();//����ת�Ƕȵ����ת45
}

void Location::on_pushButton_20_clicked()
{
    DW_USawNegative45Angle_Down();//����ת�Ƕȵ����ת45
}

void Location::on_pushButton_22_clicked()
{
    DW_VSpindlePositiveRotate_Down();//������ת�Ƕȵ����ת
}

void Location::on_pushButton_23_clicked()
{
    DW_VSpindleNegativeRotate_Down();//������ת�Ƕȵ����ת
}

void Location::on_pushButton_24_clicked()
{
    DW_VSpindlePositive90Angle_Down();//������ת�Ƕȵ����ת90
}

void Location::on_pushButton_25_clicked()
{
    DW_VSpindleNegative90Angle_Down();//������ת�Ƕȵ����ת90
}

void Location::on_pushButton_27_clicked()
{
    DW_ClampAdvance_Down();//�оߵ��ǰ��
}

void Location::on_pushButton_28_clicked()
{
    DW_ClampBack_Down();//�оߵ������
}

void Location::on_pushButton_29_clicked()
{
    DW_SawOn_Down();//������ת��
}

void Location::on_pushButton_30_clicked()
{
    DW_SawOff_Down();//������ת��
}

void Location::on_pushButton_32_clicked()
{
    DW_CylinderOneON_Down();//����1�������½�����
}

void Location::on_pushButton_37_clicked()
{
    DW_CylinderOneOFF_Down();//����1�أ�����������
}

void Location::on_pushButton_33_clicked()
{
    DW_CylinderTwoON_Down();//����2���������½�����
}

void Location::on_pushButton_38_clicked()
{
    DW_CylinderTwoOFF_Down();//����2�أ�������������
}

void Location::on_pushButton_34_clicked()
{
    DW_CylinderThreeON_Down();//����3�����ϼн�����
}

void Location::on_pushButton_39_clicked()
{
    DW_CylinderThreeOFF_Down();//����3�أ����ɿ�����
}

void Location::on_pushButton_35_clicked()
{
    DW_CylinderFourON_Down();//����4�������Ῠ������
}

void Location::on_pushButton_40_clicked()
{
    DW_CylinderFourOFF_Down();//����4�أ������ɿ�����
}

void Location::on_pushButton_36_clicked()
{
    DW_CylinderFiveON_Down();//����5������̶����׼н�
}

void Location::on_pushButton_41_clicked()
{
    DW_CylinderFiveOFF_Down();//����5�أ���̶������ɿ�
}
