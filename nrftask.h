#ifndef NRFTASK_H
#define NRFTASK_H
#include"g_code.h"
#include "spicomthread.h"



class NRFTask
{
public:
    NRFTask();
    void Send_SZ_StopMainMoto(void);
    void Send_SZ_GotoZero(void);
    //void Send_CX_State(void);
    void Send_GCode(GCodeStruct * GCode);
    void Send_DW(unsigned char Speed,unsigned char XY_Key,unsigned char Z_Key,unsigned char U_Key,unsigned char V_Key,unsigned char W_Key,unsigned char Saw_Key,unsigned char SawCylinder0ne_Key,unsigned char SpindleCylinderTwo_Key,unsigned char CylinderThreeClampKey,unsigned char CylinderFourSpindleFixKey,unsigned char CylinderFiveSawFixKey ,unsigned short int sawPositiveAngle,unsigned short int sawNegativeAngle );///////发送定位数据
    void Send_GotoZero(unsigned char Speed,unsigned char XY_Key,unsigned char Z_Key);
    void Send_SZ_SYS(void);
    void Save_SYS_Buf(unsigned char *RX_Buf);
    void Save_CX_Buf(unsigned char *RX_Buf);
    void Send_DK_Action(unsigned char Action);
    void NRFTask_RX(unsigned char *RX_Buf,unsigned char *TX_Buf);		//控制代码选择
    SPIComThread *spiComThreadOne;//spi
};

#endif // NRFTASK_H
