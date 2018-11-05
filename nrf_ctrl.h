#ifndef NRF_CTRL_H
#define NRF_CTRL_H
#include "nrf24l01.h"
#include "nrftask.h"

typedef struct
{
    unsigned char Ctrl;
    unsigned char Send;
    unsigned short int Time_Out;
    unsigned short int ERR_FC;
    unsigned short int ERR_SEND;
    unsigned short int ERR_S;
    unsigned short int ERR_TIMEOUT;
}NRF_Struct;  //CX  ��ѯ
typedef struct
{
    unsigned char Buf[2][32];
    unsigned char New;
    unsigned char Old;
}BUF_Struct;  //CX  ��ѯ
typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK��������
    int X;
    int Y;
    int Z;
    unsigned int N;
    unsigned int State;
    unsigned int NRF_N;
    unsigned char queue;
    unsigned char end;
}NRF_CX_Struct;  //CX  ��ѯ

typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK��������
    unsigned char TFTShowSize;		//TFT��ʾ�ı���
    unsigned char 	Mode;					//����ģʽ
    unsigned short int Speed_XY;			//XY��岹����ʱ���ٶ�
    unsigned short int Speed_Z;			//Z��岹����ʱ���ٶ�
    unsigned short int Speed_Fast;		//��������ʱ���ٶ�
    unsigned char end;
}NRF_SYS_Struct;  //CX  ��ѯ
typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK��������
    unsigned char Year;			//������������
    unsigned char Month;
    unsigned char Date;
    unsigned char Hour;
    unsigned char Min;
    unsigned char Sec;
    unsigned char end;
}NRF_Time_Struct;  //CX  ��ѯ

typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK��������
    unsigned char Action;	//Gcode�Ĺ�����
    unsigned short int ValueWords;
    unsigned short int Speed;
    signed int X;
    signed int Y;
    signed short int I;
    signed short int J;
    signed int Z;
    signed int W;
    unsigned int N;
    unsigned char end;
}NRF_GCode_Struct;


typedef struct //NRF24L01��ͷ�ļ��������ˣ�ÿ�δ���������ֵΪ32�ֽ�
{
    unsigned char FC;
    unsigned char Ctrl;					//DK��������
    unsigned short int DW_XY;
    unsigned short int DW_Z;
    unsigned short int DW_U;
    unsigned short int DW_V;
    unsigned short int DW_W;
    unsigned short int DW_Speed;
    unsigned char Spindle_On;
    unsigned char Saw_On;//�⿪��
    unsigned char CylinderOneSaw;//����������
    unsigned char CylinderTwoSpindle;//������������
    unsigned char CylinderThreeClamp;//�ϼ�������
    unsigned char CylinderFourSpindleFix;//����̶�����
    unsigned char CylinderFiveSawFix;//��̶�����
    unsigned short int SawPositiveAngle;//����ת�����Ƕ�
    unsigned short int SwaNegativeAngle;//�ⷴת�����Ƕȣ����˽ṹ��Ϊ28�ֽ�
    unsigned char end;
}NRF_DW_Struct;
#define	NRF_M_OK					0X00					//NRF��վ����
#define	NRF_ERR_FC                  0x10			//������������
#define	NRF_ERR_SEND                0X11					//���ͳ���
#define	NRF_ERR_S					0X12					//��վ��������У�����
#define	NRF_ERR_TIMEOUT             0X13					//���ճ�ʱ

#define	NRF_TIME_OUT                5				//��ʱ�ȴ�����

#define	NRF_S_START                 0X10				//��վ��ʼ
#define	NRF_S_READY                 0X20				//��վ׼�����

/*****ͨѶ������****/
#define End_D                       0x5A			//������
#define NRF_CX						0x10				//ͨѶЭ�飺��ѯ
#define NRF_CX_STATE				0x11				//ͨѶЭ�飺��ѯ
#define NRF_CX_SYS					0x12


#define NRF_KZ						0x20				//ͨѶЭ�飺����
#define NRF_KZ_GCODE				0x21
#define NRF_KZ_DW					0x22
#define NRF_KZ_RESET				0x23
#define NRF_KZ_MAINMOTO_ON	0x24
#define NRF_KZ_MAINMOTO_OFF	0x25
#define NRF_KZ_MOTO_ON              0x26
#define NRF_KZ_MOTO_OFF             0x27
#define NRF_KZ_GOTOZERO             0x28

#define NRF_SZ						0x30				//ͨѶЭ�飺��ѯ

#define NRF_SZ_SYS                  0x30

#define NRF_REPEAT                  0x80		//�����ط���־



extern NRF_Struct NRF;
extern unsigned char Tx_Buf[34];
extern unsigned char TxBuf[34];//����SPI���ʹ洢�м�����
extern BUF_Struct Rx_Buf;

#define RX_BUF		Rx_Buf.Buf[0]
#define RX_BUF_O	Rx_Buf.Buf[Rx_Buf.Old]
#define RX_BUF_N	Rx_Buf.Buf[Rx_Buf.New]


#endif // NRF_CTRL_H
