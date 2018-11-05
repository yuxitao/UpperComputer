#ifndef GCODE_H
#define GCODE_H

#include "nrf_ctrl.h"

// Define parameter word mapping.
#define WORD_GM  		0
#define WORD_X  		1
#define WORD_Y 		 	2
#define WORD_Z  		3
#define WORD_F  		4
#define WORD_I  		5
#define WORD_J  		6
#define WORD_N  		7
//#define WORD_K  7
//#define WORD_L  8
//#define WORD_P  9
//#define WORD_R  10
//#define WORD_S  11
//#define WORD_T  12

#define GCSTATUS_OK													0
#define GCSTATUS_BAD_NUMBER_FORMAT					1
#define GCSTATUS_EXPECTED_COMMAND_LETTER 		2
#define GCSTATUS_UNSUPPORTED_STATEMENT			3
#define GCSTATUS_FLOATING_POINT_ERROR				4
#define GCSTATUS_UNSUPPORTED_PARAM					5
#define GCSTATUS_UNSOPORTED_FEEDRATE				6
#define GCSTATUS_TABLE_SIZE_OVER_X					7
#define GCSTATUS_TABLE_SIZE_OVER_Y					8
#define GCSTATUS_TABLE_SIZE_OVER_Z					9
#define GCSTATUS_CANCELED										101

#define MM_PER_INCH (25.4)

#define SetBit(data, offset)         (data |= 1U << offset)

#define POSITIVE 	1			//电机正向
#define REVERSE 	0			//电机反向

#define  BeiLv  100		//多少脉冲/MM。实际中100个脉冲对应1mm的移动距离
#define Z_UP_NUM	200		//M05命令上升多少脉冲

//#define GC_DEFAULT 						21
#define GC_DWELL_G4 					5
#define GC_GO_HOME_G28 				28
#define GC_RESET_XYZ_G92 			92
#define GC_STOP 							22
#define GC_SEEK_G0 						1 // G0
#define GC_LINEAR_G1 					2 // G1
//#define GC_EXTRUDER_STOP 			7
//#define GC_EXTRUDER_ON 				8
//#define GC_EXTRUDER_FAST_T 		9
//#define GC_EXTRUDER_WAIT_T 		10
#define GC_CW_ARC 						3
#define GC_CCW_ARC 						4

#define GC_M03 										103	//启动主轴旋转
#define GC_M04 										104
#define GC_M05 										105	//关闭主轴旋转
#define GC_M06 										106 //锯开
#define GC_M07 										107 //锯关
#define GC_M08 										108 //锯提升气缸上
#define GC_M09 										109 //锯提升气缸下
#define GC_M10 										110 //切削液气泵开
#define GC_M11 										111 //切削液气泵关
#define GC_M12 										112 //料松开
#define GC_M13 										113 //料夹紧
#define GC_M14 										114 //锯固定气缸夹紧
#define GC_M15 										115 //锯固定气缸松开
#define GC_M16 						   			116 //主轴固定气缸松开
#define GC_M17 										117 //主轴固定气缸夹紧
#define GC_M18 										118 //主轴开
#define GC_M19 										119 //主轴关
#define GC_M20 										120 //锯正转45度
#define GC_M21 										121 //锯反转45度
#define GC_M22 										122 //主轴旋转横向
#define GC_M23										123 //主轴旋转竖向


#define GC_M25										125 //X轴回零点
#define GC_M26 										126 //Y轴回零点
#define GC_M27										127 //Z轴回零点

#define GC_M28										128 //W轴回零点,夹料电机回零点

#define GC_M29										129 //主轴提升气缸上
#define GC_M30										130 //主轴提升气缸下

#define DK_DELAY									5		//每个G代码间等待的延时时间  *1ms



#define GC_XYInterpolationType    30  //插补的坐标轴，XY轴插补
#define GC_ZYInterpolationType    31	//插补的坐标轴，ZY轴插补

////定义XYZ分别使用哪个出口输出
#define AXIS_X  1
#define AXIS_Y  2
#define AXIS_Z  0


/*  CTRL：0000  0000
                |+++  ++++
                    | |     +- 控制代码 	0000：雕刻停止
                                                            0001：雕刻开始
                                                            0010：单步命令A
                                                            0011：单步命令B
                    | +------- 通讯代码 	000：查询SYS
                    |					 					001：设置SYS，控制代码必须为0
                    |					 					010：发送G代码
                    |					 					011：查询状态
                    |										100：定位控制
                    |					 					101：返回零位，控制代码必须为0
                    |					 					110：关闭主轴，控制代码必须为0
                    +----------是否为重发数据


*/

#define CTRL_STOP					0x00		//雕刻停止命令
#define CTRL_START				0x10		//雕刻开始命令
#define CTRL_PAUSE				0x11		//雕刻暂停命令
#define CTRL_STEP_A				0x12		//雕刻单步命令
#define CTRL_STEP_B				0x13		//雕刻单步完成，等待下次单步命令或运行命令
#define CTRL_SET_DW				0x18		//雕刻定位命令
#define CTRL_GOTOZERO			0x19		//雕刻定位命令

#define DW_NUM_NULL			0

#define DW_NUM_RightBack		0x01	//////右后
#define DW_NUM_Front				0x02  //////前
#define DW_NUM_RightFront		0x03  //////右前
#define DW_NUM_Left				  0x04	//////左
#define DW_NUM_Right				0x05  //////右
#define DW_NUM_LeftBack			0x06	//////左后
#define DW_NUM_Back				  0x07	//////后
#define DW_NUM_LeftFront		0x08  //////左前
#define DW_NUM_XY_0					0x0F


#define DW_NUM_X_ReturnToZero						0x51 //X轴回左零点
#define DW_NUM_Y_ReturnToZero						0x52 //Y轴回后零点
#define DW_NUM_U_ReturnToPositive45			0x53 //U轴回正45度零点
#define DW_NUM_U_ReturnToNegative45			0x54 //U轴回负45度零点
#define DW_NUM_V_ReturnToPositive90			0x55 //U轴回正90度零点
#define DW_NUM_V_ReturnToNegative90 		0x56 //U轴回负90度零点
#define DW_NUM_Z_ReturnToZero						0x57 //Z轴回上零点


#define DW_NUM_Z_UP			0x11
#define DW_NUM_Z_DN			0x12
#define DW_NUM_Z_0			0x1F


#define DW_NUM_U_Positive			0x21
#define DW_NUM_U_Negative			0x22
#define DW_NUM_U_0			      0x2F


#define DW_NUM_V_Positive			0x31
#define DW_NUM_V_Negative			0x32
#define DW_NUM_V_0			      0x3F

#define DW_NUM_W_Forward			0x41
#define DW_NUM_W_Back			    0x42
#define DW_NUM_W_0			      0x4F

#define DW_SAWON			        0x61
#define DW_SAWOFF			        0x62
#define DW_SAWCylinderOneON			        0x63
#define DW_SAWCylinderOneOFF			      0x64
#define DW_SpindleCylinderTwoON			    0x65
#define DW_SpindleCylinderTwoOFF			  0x66

#define DW_CylinderThreeClampON			    0x67
#define DW_CylinderThreeClampOFF			  0x68

#define DW_CylinderFourSpindleFixON			    0x69
#define DW_CylinderFourSpindleFixOFF			  0x70

#define DW_CylinderFiveSawFixON			    0x71
#define DW_CylinderFiveSawFixOFF			  0x72
//typedef struct
//{
//unsigned int End;
//unsigned int NotEnd;
//unsigned int NeedRead;
//unsigned int Open;
//unsigned int ReadStart;
//unsigned int ShowTFT;
//}DK_B_File_Struct;		//报警的位处理



//typedef struct
//{
//unsigned int L[3];
//unsigned int R[3];
//}DK_B_Alarm_Struct;		//报警的位处理

//typedef struct
//{
////	u32 MainMotoRun;
//    unsigned int DK_Step;					//步进操作时的步进状态 与控制命令配合使用
//    unsigned int Inches_Mode;			//英寸模式
//    unsigned int Absolute_Mode;		//绝对坐标模式
//    unsigned int Spindle_On;				//主轴状态
//    unsigned int Axis_EN;					//步进电机使能状态
//}DK_B_StateStruct;  //状态的位处理

///雕刻机的结构体
//typedef struct
//{
//    unsigned char  TFTShowSize;		//TFT显示的倍率
//    unsigned char  	Mode;					//运行模式
//    unsigned short Speed_XY;			//XY轴插补运行时的速度
//    unsigned short Speed_Z;			//Z轴插补运行时的速度
//    unsigned short Speed_Fast;		//快速运行时的速度
////	u16 State;
//}DK_SYS_Struct;


//typedef struct
//{
////	u8 NRF_FC;
//    unsigned char queue;
//    int X;
//    int Y;
//    int Z;
//    unsigned int N;
//    unsigned int NRF_N;
//}DK_NRF_Struct;

//typedef struct
//{
//    unsigned char Ctrl;					//DK控制命令
////	u8 NRF_FC;				//NRF功能码
//    unsigned char File;					//sd卡文件中用
//    unsigned char State;					//状态
//    unsigned char Alarm;					//报警
//    unsigned char GC_Status;  //状态代码 在g_code.c中使用
//    unsigned int N;				//G代码的数量
//    unsigned int ErrN;
//    DK_SYS_Struct SYS;
//    DK_NRF_Struct NRF;

//    DK_B_File_Struct* File_B_P;
//    DK_B_Alarm_Struct* Alarm_B_P;	//报警的位处理结构体
//    DK_B_StateStruct* State_B_P;	//状态的位处理结构体
//}DiaoKe_Struct;

//typedef struct
//{

//    unsigned char Action;
//    unsigned short ValueWords;
//    unsigned short Speed;
//    int X;
//    int Y;
//    short I;
//    short J;
//    int Z;
//    int W;
//    unsigned int N;
////	u16 F;
////	s32 K;
////	float L;
////	float P;
////	float R;
////	float S;
//}GCodeStruct;

extern GCodeStruct GcodeMaterialSpeificationParameter[200];//存放各种料型计算G代码参数的数组
extern GCodeStruct G_Code;

class GCode
{
public:
    GCode();
};

#endif // GCODE_H
