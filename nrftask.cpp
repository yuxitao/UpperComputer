#include "nrftask.h"
#include "nrf_ctrl.h"
#include "dk_conf.h"
#include "nrfthread.h"
NRFTask::NRFTask()
{
    spiComThreadOne = new SPIComThread();
}
void NRFTask::Send_DK_Action(unsigned char Action)
{
    NRF.Send = 1;
    Tx_Buf[0] = Action;						//�ӻ����պ��һ���ַ��Ǳ�ʾִ�еĲ���
    Tx_Buf[1] = DK.Ctrl;
    Tx_Buf[2] = End_D;
    //OS.PostMessageQueue(NRFTaskPriority, (void *)((u32)UseMessage_NRF <<24));
    RunFlag =1;//����������б�־λ
    spiComThreadOne->start();
}

void NRFTask::Send_GCode(GCodeStruct * GCode)//����G����
{
    NRF_GCode_Struct *NRF_GCode_P;
    NRF.Send = 1;													//�����κβ���ʱ����Ҫ�Ƚ�NRF.Send��1
    NRF_GCode_P = (NRF_GCode_Struct *)Tx_Buf;	//��24L01�ķ�������ָ�븳ֵ���ṹ��ָ�����
    NRF_GCode_P->FC = NRF_KZ_GCODE;						//�ӻ����պ��һ���ַ��Ǳ�ʾִ�еĲ���
    NRF_GCode_P->Action = GCode->Action;
    NRF_GCode_P->Speed  = GCode->Speed;
    NRF_GCode_P->ValueWords = GCode->ValueWords;
    NRF_GCode_P->X = GCode->X;
    NRF_GCode_P->Y = GCode->Y;
    NRF_GCode_P->Z = GCode->Z;
    NRF_GCode_P->I = GCode->I;
    NRF_GCode_P->J = GCode->J;
    NRF_GCode_P->W = GCode->W;
    NRF_GCode_P->N = DK.N;
    NRF_GCode_P->end = End_D;
    //OS.PostMessageQueue(NRFTaskPriority, (void *)((u32)UseMessage_NRF <<24));
    RunFlag =1;//����������б�־λ
    spiComThreadOne->start();
}
void NRFTask::Send_DW(unsigned char Speed,unsigned char XY_Key,unsigned char Z_Key,unsigned char U_Key,unsigned char V_Key,unsigned char W_Key,unsigned char Saw_Key,unsigned char SawCylinder0ne_Key,unsigned char SpindleCylinderTwo_Key,unsigned char CylinderThreeClampKey,unsigned char CylinderFourSpindleFixKey,unsigned char CylinderFiveSawFixKey ,unsigned short int sawPositiveAngle,unsigned short int sawNegativeAngle )///////���Ͷ�λ����
{
    NRF_DW_Struct *NRF_GCode_P;
    NRF.Send = 1;													//�����κβ���ʱ����Ҫ�Ƚ�NRF.Send��1
    NRF_GCode_P = (NRF_DW_Struct *)Tx_Buf;
    NRF_GCode_P->FC 											= NRF_KZ_DW;
    NRF_GCode_P->Ctrl 										= CTRL_SET_DW;
    NRF_GCode_P->DW_XY 										= XY_Key;
    NRF_GCode_P->DW_Z 										= Z_Key;
    NRF_GCode_P->DW_U 										= U_Key;
    NRF_GCode_P->DW_V 										= V_Key;
    NRF_GCode_P->DW_W 										= W_Key;
    NRF_GCode_P->DW_Speed 								= Speed;
//    NRF_GCode_P->Spindle_On 							= DK.State_B_P->Spindle_On;//zheyigeyoucuowu
    NRF_GCode_P->Saw_On   								= Saw_Key;//�⿪��
    NRF_GCode_P->CylinderOneSaw           = SawCylinder0ne_Key;//���������׿���
    NRF_GCode_P->CylinderTwoSpindle       = SpindleCylinderTwo_Key;//�����������׿���
    NRF_GCode_P->CylinderThreeClamp       = CylinderThreeClampKey;//�ϼ�������
    NRF_GCode_P->CylinderFourSpindleFix   = CylinderFourSpindleFixKey;//����̶����׿���
    NRF_GCode_P->CylinderFiveSawFix       = CylinderFiveSawFixKey;//��̶����׿���
    NRF_GCode_P->SawPositiveAngle         = sawPositiveAngle;//����ת45�����Ƕ�
    NRF_GCode_P->SwaNegativeAngle         = sawNegativeAngle;//�ⷴת45�����Ƕ�
    NRF_GCode_P->end 			= End_D;
    //OS.PostMessageQueue(NRFTaskPriority, (void *)((u32)UseMessage_NRF <<24));
    RunFlag =1;//����������б�־λ
    spiComThreadOne->start();
}
//�����ࣺ0x30  �����ࣺ0x20  ��ѯ�ࣺ0x10

void NRFTask::Send_SZ_SYS(void)//�������ò���
{
    NRF_SYS_Struct *Set_SYS_P;
    NRF.Send = 1;											//�����κβ���ʱ����Ҫ�Ƚ�NRF.Send��1
    Set_SYS_P = (NRF_SYS_Struct *)Tx_Buf;
    Set_SYS_P->FC = NRF_SZ_SYS;
    Set_SYS_P->Ctrl = DK.Ctrl;
    Set_SYS_P->Speed_XY = DK.SYS.Speed_XY;
    Set_SYS_P->Speed_Z = DK.SYS.Speed_Z;
    Set_SYS_P->Speed_Fast = DK.SYS.Speed_Fast;
    Set_SYS_P->TFTShowSize = DK.SYS.TFTShowSize;
    Set_SYS_P->end = End_D;
    //OS.PostMessageQueue(NRFTaskPriority, (void *)((u32)UseMessage_NRF <<24));
    RunFlag =1;//����������б�־λ
    spiComThreadOne->start();
}


void NRFTask::Save_SYS_Buf(unsigned char *RX_Buf)//��ȡ�ӻ����ػ�����ϵͳ����
{
    NRF_SYS_Struct *Set_SYS_P;
    Set_SYS_P = (NRF_SYS_Struct *)RX_Buf;//��24L01���յ��Ĳ���λ��ֵ��DK.SYS�ṹ��
    DK.SYS.Speed_Fast = 		Set_SYS_P->Speed_Fast;
    DK.SYS.Speed_XY = 			Set_SYS_P->Speed_XY;
    DK.SYS.Speed_Z = 				Set_SYS_P->Speed_Z;
    DK.SYS.TFTShowSize = 		Set_SYS_P->TFTShowSize;
    DK.Ctrl = CTRL_STOP;
    //LED2 = !LED2;
    NRF.Send = 0;
}


void NRFTask::Save_CX_Buf(unsigned char *RX_Buf)//��ȡ�ӻ����ػ�����λ�ò���
{
    NRF_CX_Struct * DK_State_P;
    DK_State_P = (NRF_CX_Struct *)RX_Buf;//��24L01���յ��Ĳ���λ��ֵ��DK.NRF�ṹ��
    DK.NRF.X = DK_State_P->X >>6;
    DK.NRF.Y = DK_State_P->Y >>6;
    DK.NRF.Z = DK_State_P->Z >>6;

    DK.NRF.NRF_N = DK_State_P->NRF_N;
    DK.NRF.N = DK_State_P->N;
    DK.Alarm = DK_State_P->State;
    DK.NRF.queue = DK_State_P->queue;
    //LED2 = !LED2;
    //GPIO_SetBits(GPIOF , GPIO_Pin_9);///////������
    NRF.Send = 0;

}

void NRFTask::NRFTask_RX(unsigned char *RX_Buf,unsigned char *TX_Buf)		//���ƴ���ѡ��
{
      switch (RX_Buf[0])
      {
        case NRF_CX_STATE:
        case NRF_KZ_GCODE:
        case NRF_KZ_DW:
        case NRF_KZ_RESET:
        case NRF_KZ_MAINMOTO_ON:
        case NRF_KZ_MOTO_ON:
        case NRF_KZ_MOTO_OFF:
        case NRF_KZ_MAINMOTO_OFF:
        case NRF_KZ_GOTOZERO:
                    Save_CX_Buf(RX_Buf);
                    NRF.Ctrl=NRF_M_OK;
                    NRF.Send = 0;
            break;
        case NRF_SZ_SYS:
                    Save_CX_Buf(RX_Buf);
                    NRF.Ctrl=NRF_M_OK;
                    NRF.Send = 0;
            break;
        case NRF_CX_SYS:
                    Save_SYS_Buf(RX_Buf);
                    NRF.Ctrl=NRF_M_OK;
                    NRF.Send = 0;
                    break;
        case 0xFF:
                    NRF.Ctrl = NRF_ERR_S;
                        NRF.ERR_S++;
                    break;
        default:
                        NRF.Ctrl = NRF_ERR_FC;
                        NRF.ERR_FC++;
//NRF.Send = 0;//////�����ã�����ģ��24L01�������������ݣ����ط���־λNRF.Send = 0��
            break;
      }
}
