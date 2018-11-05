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
}NRF_Struct;  //CX  查询
typedef struct
{
    unsigned char Buf[2][32];
    unsigned char New;
    unsigned char Old;
}BUF_Struct;  //CX  查询
typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK控制命令
    int X;
    int Y;
    int Z;
    unsigned int N;
    unsigned int State;
    unsigned int NRF_N;
    unsigned char queue;
    unsigned char end;
}NRF_CX_Struct;  //CX  查询

typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK控制命令
    unsigned char TFTShowSize;		//TFT显示的倍率
    unsigned char 	Mode;					//运行模式
    unsigned short int Speed_XY;			//XY轴插补运行时的速度
    unsigned short int Speed_Z;			//Z轴插补运行时的速度
    unsigned short int Speed_Fast;		//快速运行时的速度
    unsigned char end;
}NRF_SYS_Struct;  //CX  查询
typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK控制命令
    unsigned char Year;			//公历日月年周
    unsigned char Month;
    unsigned char Date;
    unsigned char Hour;
    unsigned char Min;
    unsigned char Sec;
    unsigned char end;
}NRF_Time_Struct;  //CX  查询

typedef struct
{
    unsigned char FC;
    unsigned char Ctrl;					//DK控制命令
    unsigned char Action;	//Gcode的功能码
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


typedef struct //NRF24L01在头文件中设置了，每次传输的最大数值为32字节
{
    unsigned char FC;
    unsigned char Ctrl;					//DK控制命令
    unsigned short int DW_XY;
    unsigned short int DW_Z;
    unsigned short int DW_U;
    unsigned short int DW_V;
    unsigned short int DW_W;
    unsigned short int DW_Speed;
    unsigned char Spindle_On;
    unsigned char Saw_On;//锯开关
    unsigned char CylinderOneSaw;//锯提升气缸
    unsigned char CylinderTwoSpindle;//主轴提升气缸
    unsigned char CylinderThreeClamp;//料夹子气缸
    unsigned char CylinderFourSpindleFix;//主轴固定气缸
    unsigned char CylinderFiveSawFix;//锯固定气缸
    unsigned short int SawPositiveAngle;//锯正转补偿角度
    unsigned short int SwaNegativeAngle;//锯反转补偿角度，至此结构体为28字节
    unsigned char end;
}NRF_DW_Struct;
#define	NRF_M_OK					0X00					//NRF主站就绪
#define	NRF_ERR_FC                  0x10			//功能码错误错误
#define	NRF_ERR_SEND                0X11					//发送出错
#define	NRF_ERR_S					0X12					//从站接收数据校验错误
#define	NRF_ERR_TIMEOUT             0X13					//接收超时

#define	NRF_TIME_OUT                5				//超时等待次数

#define	NRF_S_START                 0X10				//从站开始
#define	NRF_S_READY                 0X20				//从站准备完毕

/*****通讯控制码****/
#define End_D                       0x5A			//结束码
#define NRF_CX						0x10				//通讯协议：查询
#define NRF_CX_STATE				0x11				//通讯协议：查询
#define NRF_CX_SYS					0x12


#define NRF_KZ						0x20				//通讯协议：控制
#define NRF_KZ_GCODE				0x21
#define NRF_KZ_DW					0x22
#define NRF_KZ_RESET				0x23
#define NRF_KZ_MAINMOTO_ON	0x24
#define NRF_KZ_MAINMOTO_OFF	0x25
#define NRF_KZ_MOTO_ON              0x26
#define NRF_KZ_MOTO_OFF             0x27
#define NRF_KZ_GOTOZERO             0x28

#define NRF_SZ						0x30				//通讯协议：查询

#define NRF_SZ_SYS                  0x30

#define NRF_REPEAT                  0x80		//数据重发标志



extern NRF_Struct NRF;
extern unsigned char Tx_Buf[34];
extern unsigned char TxBuf[34];//用于SPI发送存储中间数据
extern BUF_Struct Rx_Buf;

#define RX_BUF		Rx_Buf.Buf[0]
#define RX_BUF_O	Rx_Buf.Buf[Rx_Buf.Old]
#define RX_BUF_N	Rx_Buf.Buf[Rx_Buf.New]


#endif // NRF_CTRL_H
