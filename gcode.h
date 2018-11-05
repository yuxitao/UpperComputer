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

#define POSITIVE 	1			//�������
#define REVERSE 	0			//�������

#define  BeiLv  100		//��������/MM��ʵ����100�������Ӧ1mm���ƶ�����
#define Z_UP_NUM	200		//M05����������������

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

#define GC_M03 										103	//����������ת
#define GC_M04 										104
#define GC_M05 										105	//�ر�������ת
#define GC_M06 										106 //�⿪
#define GC_M07 										107 //���
#define GC_M08 										108 //������������
#define GC_M09 										109 //������������
#define GC_M10 										110 //����Һ���ÿ�
#define GC_M11 										111 //����Һ���ù�
#define GC_M12 										112 //���ɿ�
#define GC_M13 										113 //�ϼн�
#define GC_M14 										114 //��̶����׼н�
#define GC_M15 										115 //��̶������ɿ�
#define GC_M16 						   			116 //����̶������ɿ�
#define GC_M17 										117 //����̶����׼н�
#define GC_M18 										118 //���Ὺ
#define GC_M19 										119 //�����
#define GC_M20 										120 //����ת45��
#define GC_M21 										121 //�ⷴת45��
#define GC_M22 										122 //������ת����
#define GC_M23										123 //������ת����


#define GC_M25										125 //X������
#define GC_M26 										126 //Y������
#define GC_M27										127 //Z������

#define GC_M28										128 //W������,���ϵ�������

#define GC_M29										129 //��������������
#define GC_M30										130 //��������������

#define DK_DELAY									5		//ÿ��G�����ȴ�����ʱʱ��  *1ms



#define GC_XYInterpolationType    30  //�岹�������ᣬXY��岹
#define GC_ZYInterpolationType    31	//�岹�������ᣬZY��岹

////����XYZ�ֱ�ʹ���ĸ��������
#define AXIS_X  1
#define AXIS_Y  2
#define AXIS_Z  0


/*  CTRL��0000  0000
                |+++  ++++
                    | |     +- ���ƴ��� 	0000�����ֹͣ
                                                            0001����̿�ʼ
                                                            0010����������A
                                                            0011����������B
                    | +------- ͨѶ���� 	000����ѯSYS
                    |					 					001������SYS�����ƴ������Ϊ0
                    |					 					010������G����
                    |					 					011����ѯ״̬
                    |										100����λ����
                    |					 					101��������λ�����ƴ������Ϊ0
                    |					 					110���ر����ᣬ���ƴ������Ϊ0
                    +----------�Ƿ�Ϊ�ط�����


*/

#define CTRL_STOP					0x00		//���ֹͣ����
#define CTRL_START				0x10		//��̿�ʼ����
#define CTRL_PAUSE				0x11		//�����ͣ����
#define CTRL_STEP_A				0x12		//��̵�������
#define CTRL_STEP_B				0x13		//��̵�����ɣ��ȴ��´ε����������������
#define CTRL_SET_DW				0x18		//��̶�λ����
#define CTRL_GOTOZERO			0x19		//��̶�λ����

#define DW_NUM_NULL			0

#define DW_NUM_RightBack		0x01	//////�Һ�
#define DW_NUM_Front				0x02  //////ǰ
#define DW_NUM_RightFront		0x03  //////��ǰ
#define DW_NUM_Left				  0x04	//////��
#define DW_NUM_Right				0x05  //////��
#define DW_NUM_LeftBack			0x06	//////���
#define DW_NUM_Back				  0x07	//////��
#define DW_NUM_LeftFront		0x08  //////��ǰ
#define DW_NUM_XY_0					0x0F


#define DW_NUM_X_ReturnToZero						0x51 //X��������
#define DW_NUM_Y_ReturnToZero						0x52 //Y��غ����
#define DW_NUM_U_ReturnToPositive45			0x53 //U�����45�����
#define DW_NUM_U_ReturnToNegative45			0x54 //U��ظ�45�����
#define DW_NUM_V_ReturnToPositive90			0x55 //U�����90�����
#define DW_NUM_V_ReturnToNegative90 		0x56 //U��ظ�90�����
#define DW_NUM_Z_ReturnToZero						0x57 //Z��������


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
//}DK_B_File_Struct;		//������λ����



//typedef struct
//{
//unsigned int L[3];
//unsigned int R[3];
//}DK_B_Alarm_Struct;		//������λ����

//typedef struct
//{
////	u32 MainMotoRun;
//    unsigned int DK_Step;					//��������ʱ�Ĳ���״̬ ������������ʹ��
//    unsigned int Inches_Mode;			//Ӣ��ģʽ
//    unsigned int Absolute_Mode;		//��������ģʽ
//    unsigned int Spindle_On;				//����״̬
//    unsigned int Axis_EN;					//�������ʹ��״̬
//}DK_B_StateStruct;  //״̬��λ����

///��̻��Ľṹ��
//typedef struct
//{
//    unsigned char  TFTShowSize;		//TFT��ʾ�ı���
//    unsigned char  	Mode;					//����ģʽ
//    unsigned short Speed_XY;			//XY��岹����ʱ���ٶ�
//    unsigned short Speed_Z;			//Z��岹����ʱ���ٶ�
//    unsigned short Speed_Fast;		//��������ʱ���ٶ�
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
//    unsigned char Ctrl;					//DK��������
////	u8 NRF_FC;				//NRF������
//    unsigned char File;					//sd���ļ�����
//    unsigned char State;					//״̬
//    unsigned char Alarm;					//����
//    unsigned char GC_Status;  //״̬���� ��g_code.c��ʹ��
//    unsigned int N;				//G���������
//    unsigned int ErrN;
//    DK_SYS_Struct SYS;
//    DK_NRF_Struct NRF;

//    DK_B_File_Struct* File_B_P;
//    DK_B_Alarm_Struct* Alarm_B_P;	//������λ����ṹ��
//    DK_B_StateStruct* State_B_P;	//״̬��λ����ṹ��
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

extern GCodeStruct GcodeMaterialSpeificationParameter[200];//��Ÿ������ͼ���G�������������
extern GCodeStruct G_Code;

class GCode
{
public:
    GCode();
};

#endif // GCODE_H
