#include "materialtypethree.h"
#include "gcode.h"
#include "nrf_ctrl.h"
#include "nrfthread.h"

MaterialTypeThree::MaterialTypeThree()
{

}
/********************************************************************************************************************************
*													L6																																																		*
*  			*  *	R1		*****************************************
* 		*          *		*									*																						*			  *				*      *					*
L2* L3 *		    *	L4	*	L5							*		*	 **		    *					*
* 		*		   *	  	*									*																						*			  *				*		   *					*
*	  		*	 *			***************************************	 *	*
*																						L1																																									*
*********************************************************************************************************************************/
MaterialSpecificationTypeThreeParameterInitValue MaterialSpecificationIIIParameterInitValue = //////用于赋值初始值
{
1800  //L1;切割料的长度
,35   //L2;切割料的宽度
,30   //L3;第一个圆孔距离边的距离
,30   //L4;第一个圆孔和第一个矩形之间的距离
,6    //L5;第一个矩形的宽度
,30   //L6;	第一个矩形的长度
,800  //L7 锁孔距离一端的距离
,30		//L8锁孔的宽度
,100  //L9锁孔的长度
,2    //Ridus1;第一个圆的半径
,5    //Ridus2;//侧孔圆的半径，用于YZ平面的Z轴定位运算，Y轴定位运算用Ridus3
,5    //Ridus3;侧孔圆半径，用于XY平面的运算
,5		//ZYRidus3;侧孔圆半径，用于YZ平面的插补运算
,100  //L10 侧孔圆半径到矩形锁孔边的距离
,85		//Wide料高度
,85		//ZYWide料高度
};
MaterialSpecificationTypeThreeParameter MaterialSpecificationIIIParameter;//////用于计算尺寸
//用于赋初值
GCodeStruct Zero =
{
    0
    ,0
    ,0
    ,0
    ,0
    ,0
    ,0
    ,0
    ,0
    ,0
};
//////用于设置初始值
unsigned short x1=369;//X1为料距离Y轴边的距离363
unsigned short y1=45 ;//Y2为料距离X轴边的距离
unsigned short y2=45 ;//Y2为料另一头距离X轴边的距离
unsigned short x2=24; //X2为夹料固定块的宽度
unsigned short x3=573;//主轴横过来后刀尖距离夹料块右表面距离
unsigned short z3=227;//主轴垂直刀距离夹料块上表面的距离，运算是x160
unsigned short z1=203;//主轴横过来后刀距离夹料块上表面的距离，运算是x160
unsigned short z2=203;//主轴横过来后刀距离夹料块上表面的距离，用于YZ轴的插补用x41.89
unsigned char LockHole = 1;//是否打锁孔

//////用于中间运算
unsigned short X1=365;//X1为料距离Y轴边的距离363
unsigned short Y1=45 ;//Y2为料距离X轴边的距离
unsigned short Y2=45 ;//Y2为料另一头距离X轴边的距离
unsigned short X2=24; //X2为夹料固定块的宽度
unsigned short X3=593;//主轴横过来后刀尖距离夹料块右表面距离
unsigned short Z3=227;//Z轴垂直时刀碰到夹料固定块上表面
unsigned short Z1=203;//主轴横过来后刀距离夹料块上表面的距离，运算是x160
unsigned short Z2=203;//主轴横过来后刀距离夹料块上表面的距离，用于YZ轴的插补用x41.89
//////计算料型参数G代码
void CalculateMaterialtypethreeGcode(void)
{
    unsigned char i = 0;

    MaterialSpecificationIIIParameter.L1 = MaterialSpecificationIIIParameterInitValue.L1*41.89;
    MaterialSpecificationIIIParameter.L2 = MaterialSpecificationIIIParameterInitValue.L2*41.89;
    MaterialSpecificationIIIParameter.L3 = MaterialSpecificationIIIParameterInitValue.L3*41.89;
    MaterialSpecificationIIIParameter.L4 = MaterialSpecificationIIIParameterInitValue.L4*41.89;
    MaterialSpecificationIIIParameter.L5 = MaterialSpecificationIIIParameterInitValue.L5*41.89;
    MaterialSpecificationIIIParameter.L6 = MaterialSpecificationIIIParameterInitValue.L6*41.89;
    MaterialSpecificationIIIParameter.L7 = MaterialSpecificationIIIParameterInitValue.L7*41.89;
    MaterialSpecificationIIIParameter.L8 = MaterialSpecificationIIIParameterInitValue.L8*41.89;
    MaterialSpecificationIIIParameter.L9 = MaterialSpecificationIIIParameterInitValue.L9*41.89;
    MaterialSpecificationIIIParameter.L10 = MaterialSpecificationIIIParameterInitValue.L10*41.89;
    MaterialSpecificationIIIParameter.Ridus1 = MaterialSpecificationIIIParameterInitValue.Ridus1*41.89;//用于XY平面的圆孔
    MaterialSpecificationIIIParameter.Ridus2 = MaterialSpecificationIIIParameterInitValue.Ridus2*160;
    MaterialSpecificationIIIParameter.Ridus3 = MaterialSpecificationIIIParameterInitValue.Ridus3*160;
    MaterialSpecificationIIIParameter.ZYRidus3 = MaterialSpecificationIIIParameterInitValue.ZYRidus3*41.89;
    MaterialSpecificationIIIParameter.Wide = MaterialSpecificationIIIParameterInitValue.Wide*160;
    MaterialSpecificationIIIParameter.ZYWide = MaterialSpecificationIIIParameterInitValue.ZYWide*41.89;

    X1 = x1*41.89;
    X2 = x2*41.89;
    X3 = x3*41.89;
    Y2 = y2*41.89;
    Y1 = y1*41.89;
    Z1 = z1*160;//横过来后Z轴刀到夹板上表面的距离
    Z2 = z2*41.89;//横过来后Z轴刀到夹板上表面的距离，用于ZY轴的插补运算
    Z3 = z3*160;
    for(i =0;i<150;i++)//发送料型参数生成的G代码
    {
        GcodeMaterialSpeificationParameter[i] = Zero;
    }
    //////Y轴和UVW转速一样，同时XY轴转速设置为一样，修改他们任何速度，都一起改变

    //////	SetBit(GcodeMaterialSpeificationParameter[0].ValueWords,WORD_GM);//夹料气缸关,测试插补平面的变量
    //////	GcodeMaterialSpeificationParameter[0].Action = GC_ZYInterpolationType;
    //X	轴回零点
    SetBit(GcodeMaterialSpeificationParameter[0].ValueWords,WORD_GM);//GC_M25    X	轴回零点
    GcodeMaterialSpeificationParameter[0].Action = GC_M25;
    //Y	轴回零点
    SetBit(GcodeMaterialSpeificationParameter[1].ValueWords,WORD_GM);////GC_M26  Y	轴回零点
    GcodeMaterialSpeificationParameter[1].Action = GC_M26;
    //Z	轴回零点
    SetBit(GcodeMaterialSpeificationParameter[2].ValueWords,WORD_GM);////GC_M27  Z	轴回零点
    GcodeMaterialSpeificationParameter[2].Action = GC_M27;
    //W	轴回零点
    SetBit(GcodeMaterialSpeificationParameter[3].ValueWords,WORD_GM);////GC_M28  W	轴回零点
    GcodeMaterialSpeificationParameter[3].Action = GC_M28;
    //锯旋转+45
    SetBit(GcodeMaterialSpeificationParameter[4].ValueWords,WORD_GM);//GC_M20锯旋转+45
    GcodeMaterialSpeificationParameter[4].Action = GC_M20;
    //锯固定气缸关
    SetBit(GcodeMaterialSpeificationParameter[5].ValueWords,WORD_GM);//锯固定气缸锁紧
    GcodeMaterialSpeificationParameter[5].Action = GC_M14;

    //夹料块电机前进料长减去30cm
    SetBit(GcodeMaterialSpeificationParameter[6].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -L5/2)Y(y1 + L3 +L4)
    GcodeMaterialSpeificationParameter[6].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[6].ValueWords,WORD_F);
    GcodeMaterialSpeificationParameter[6].Speed = 10;
    GcodeMaterialSpeificationParameter[6].W = MaterialSpecificationIIIParameter.L1 - 300*41.89;
    //夹料气缸关
    SetBit(GcodeMaterialSpeificationParameter[7].ValueWords,WORD_GM);//夹料气缸关，调试屏蔽的
    GcodeMaterialSpeificationParameter[7].Action = GC_M13;
    //右进120cm进行切割
    SetBit(GcodeMaterialSpeificationParameter[8].ValueWords,WORD_GM);//G00  X444
    GcodeMaterialSpeificationParameter[8].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[8].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[8].Speed = 10;
    GcodeMaterialSpeificationParameter[8].X      = 1200*41.89;
    //锯提升气缸下
    SetBit(GcodeMaterialSpeificationParameter[9].ValueWords,WORD_GM);//锯提升气缸下
    GcodeMaterialSpeificationParameter[9].Action = GC_M09;
    //开锯
    SetBit(GcodeMaterialSpeificationParameter[10].ValueWords,WORD_GM);//M06锯开
    GcodeMaterialSpeificationParameter[10].Action = GC_M06;
    //锯下刀
    SetBit(GcodeMaterialSpeificationParameter[11].ValueWords,WORD_GM);//G00 锯Z轴下1cm
    GcodeMaterialSpeificationParameter[11].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[11].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[11].Speed = 10;
    GcodeMaterialSpeificationParameter[11].Z      = 10*160;//Z轴保持在回零点后的位置，未向下
    //左进进行切割
    SetBit(GcodeMaterialSpeificationParameter[12].ValueWords,WORD_GM);//G00  X444
    GcodeMaterialSpeificationParameter[12].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[12].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[12].Speed = 20;
    GcodeMaterialSpeificationParameter[12].X      = 100*41.89;
    //关锯
    SetBit(GcodeMaterialSpeificationParameter[13].ValueWords,WORD_GM);//M06锯关
    GcodeMaterialSpeificationParameter[13].Action = GC_M07;
    //锯提升气缸上
    SetBit(GcodeMaterialSpeificationParameter[14].ValueWords,WORD_GM);//锯提升气缸上
    GcodeMaterialSpeificationParameter[14].Action = GC_M08;

    //	//提刀
    //	SetBit(GcodeMaterialSpeificationParameter[8].ValueWords,WORD_GM);//G00 Z-32 锯Z轴上
    //	GcodeMaterialSpeificationParameter[8].Action = GC_SEEK_G0;
    //	SetBit(GcodeMaterialSpeificationParameter[8].ValueWords,WORD_Z);
    //	GcodeMaterialSpeificationParameter[8].Speed = 1;
    //	GcodeMaterialSpeificationParameter[8].Z      = -30*160;
    //锯回X轴10cm
    //	SetBit(GcodeMaterialSpeificationParameter[9].ValueWords,WORD_GM);//G00 X10
    //	GcodeMaterialSpeificationParameter[9].Action = GC_SEEK_G0;
    //	SetBit(GcodeMaterialSpeificationParameter[9].ValueWords,WORD_X);
    //	GcodeMaterialSpeificationParameter[9].Speed = 1;
    //	GcodeMaterialSpeificationParameter[9].X      = 10*44.4;
    //	SetBit(GcodeMaterialSpeificationParameter[9].ValueWords,WORD_GM);//夹料气缸关
    //	GcodeMaterialSpeificationParameter[9].Action = GC_M13;
    //	GcodeMaterialSpeificationParameter[9] = Zero;//不用的点赋值0
    //锯固定气缸松开
    SetBit(GcodeMaterialSpeificationParameter[15].ValueWords,WORD_GM);//锯固定气缸松开
    GcodeMaterialSpeificationParameter[15].Action = GC_M15;
    //定位至左边料第一个圆的点
    SetBit(GcodeMaterialSpeificationParameter[16].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - R1) Y(y1 + L3)
    GcodeMaterialSpeificationParameter[16].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[16].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[16].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[16].Speed = 10;
    GcodeMaterialSpeificationParameter[16].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[16].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[17].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[17].Action = GC_M03;
    //主轴固定气缸锁紧
    SetBit(GcodeMaterialSpeificationParameter[18].ValueWords,WORD_GM);//主轴固定气缸锁紧
    GcodeMaterialSpeificationParameter[18].Action = GC_M17;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[19].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[19].Action = GC_SEEK_G0;
    GcodeMaterialSpeificationParameter[19].Speed = 30;
    SetBit(GcodeMaterialSpeificationParameter[19].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[19].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割左边料第一个圆
    SetBit(GcodeMaterialSpeificationParameter[20].ValueWords,WORD_GM);//G02 X(x1 + L2/2) Y(y1 + L3 + R1) I R1 J 0
    GcodeMaterialSpeificationParameter[20].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[20].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[20].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[20].Speed = 1;
    GcodeMaterialSpeificationParameter[20].X      = X1 - MaterialSpecificationIIIParameter.L2/2;
    GcodeMaterialSpeificationParameter[20].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[20].I      = MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[20].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[21].ValueWords,WORD_GM);//G02 X(x1 + L2/2 +R1) Y(y1 + L3)	 I 0  J -R1
    GcodeMaterialSpeificationParameter[21].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[21].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[21].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[21].Speed = 1;
    GcodeMaterialSpeificationParameter[21].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[21].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[21].I      = 0;
    GcodeMaterialSpeificationParameter[21].J      = -MaterialSpecificationIIIParameter.Ridus1;

    SetBit(GcodeMaterialSpeificationParameter[22].ValueWords,WORD_GM);//G02 X(x1 + L2/2) Y(y1 + L3 - R1) I -R1J 0
    GcodeMaterialSpeificationParameter[22].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[22].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[22].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[22].Speed = 1;
    GcodeMaterialSpeificationParameter[22].X      = X1 - MaterialSpecificationIIIParameter.L2/2;
    GcodeMaterialSpeificationParameter[22].Y      = Y1 + MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[22].I      = -MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[22].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[23].ValueWords,WORD_GM);//G02 X(x1 + L2/2 - R1) Y(y1 + L3) I 0  JR1
    GcodeMaterialSpeificationParameter[23].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[23].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[23].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[23].Speed = 1;
    GcodeMaterialSpeificationParameter[23].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[23].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[23].I      = 0;
    GcodeMaterialSpeificationParameter[23].J      = MaterialSpecificationIIIParameter.Ridus1;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[24].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[24].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[24].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[24].Speed = 10 ;
    GcodeMaterialSpeificationParameter[24].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //	//主轴关
    //	SetBit(GcodeMaterialSpeificationParameter[22].ValueWords,WORD_GM);//主轴关
    //	GcodeMaterialSpeificationParameter[22].Action = GC_M03;
    //	//切削液关
    //	SetBit(GcodeMaterialSpeificationParameter[23].ValueWords,WORD_GM);//切削液喷关
    //	GcodeMaterialSpeificationParameter[23].Action = GC_M11;
    //定位至左边料第一个矩形的点
    SetBit(GcodeMaterialSpeificationParameter[25].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -L5/2)Y(y1 + L3 +L4)
    GcodeMaterialSpeificationParameter[25].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[25].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[25].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[25].Speed = 10;
    GcodeMaterialSpeificationParameter[25].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2;
    GcodeMaterialSpeificationParameter[25].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4;

    //	//主轴开
    //	SetBit(GcodeMaterialSpeificationParameter[25].ValueWords,WORD_GM);//主轴开
    //	GcodeMaterialSpeificationParameter[25].Action = GC_M18;
    //	//切削液开
    //	SetBit(GcodeMaterialSpeificationParameter[25].ValueWords,WORD_GM);//切削液喷开
    //	GcodeMaterialSpeificationParameter[25].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[26].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[26].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[26].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[26].Speed = 30;
    GcodeMaterialSpeificationParameter[26].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割左边料第一个矩形
    SetBit(GcodeMaterialSpeificationParameter[27].ValueWords,WORD_GM);//G00 Y(y1 + L3 +L4 +L6)
    GcodeMaterialSpeificationParameter[27].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[27].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[27].Speed = 100;
    GcodeMaterialSpeificationParameter[27].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4 + MaterialSpecificationIIIParameter.L6;

    SetBit(GcodeMaterialSpeificationParameter[28].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2)
    GcodeMaterialSpeificationParameter[28].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[28].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[28].Speed = 100;
    GcodeMaterialSpeificationParameter[28].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L5/2;

    SetBit(GcodeMaterialSpeificationParameter[29].ValueWords,WORD_GM);//G00 Y(y1 + L3 +L4)
    GcodeMaterialSpeificationParameter[29].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[29].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[29].Speed = 100;
    GcodeMaterialSpeificationParameter[29].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4;

    SetBit(GcodeMaterialSpeificationParameter[30].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -L5/2)
    GcodeMaterialSpeificationParameter[30].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[30].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[30].Speed = 100;
    GcodeMaterialSpeificationParameter[30].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[31].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[31].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[31].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[31].Speed = 10;
    GcodeMaterialSpeificationParameter[31].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[32].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[32].Action = GC_M03;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[33].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[33].Action = GC_M11;

    //定位至右边料第一个圆的点
    SetBit(GcodeMaterialSpeificationParameter[34].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + Wide - R1) Y(y1 + L3)
    GcodeMaterialSpeificationParameter[34].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[34].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[34].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[34].Speed = 10;
    GcodeMaterialSpeificationParameter[34].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[34].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[35].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[35].Action = GC_M03;
    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[36].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[36].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[37].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[37].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[37].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[37].Speed = 30;
    GcodeMaterialSpeificationParameter[37].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm

    //切割右边料第一个圆
    SetBit(GcodeMaterialSpeificationParameter[38].ValueWords,WORD_GM);//G02 X(x1 + L2/2+ Wide)  Y(y1 + L3 + R1)    I R1 J 0
    GcodeMaterialSpeificationParameter[38].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[38].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[38].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[38].Speed = 1;
    GcodeMaterialSpeificationParameter[38].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[38].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[38].I      = MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[38].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[39].ValueWords,WORD_GM);//G02 X(x1 + L2/2 +R1+ Wide)  Y(y1 + L3)	 I 0  J -R1
    GcodeMaterialSpeificationParameter[39].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[39].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[39].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[39].Speed = 1;
    GcodeMaterialSpeificationParameter[39].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[39].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[39].I      = 0;
    GcodeMaterialSpeificationParameter[39].J      = -MaterialSpecificationIIIParameter.Ridus1;

    SetBit(GcodeMaterialSpeificationParameter[40].ValueWords,WORD_GM);//G02 X(x1 + L2/2+ Wide)      Y(y1 + L3 - R1)    I -R1J 0
    GcodeMaterialSpeificationParameter[40].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[40].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[40].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[40].Speed = 1;
    GcodeMaterialSpeificationParameter[40].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[40].Y      = Y1 + MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[40].I      = -MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[40].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[41].ValueWords,WORD_GM);//G02 X(x1 + L2/2 - R1+ Wide) Y(y1 + L3)         I 0  JR1
    GcodeMaterialSpeificationParameter[41].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[41].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[41].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[41].Speed = 1;
    GcodeMaterialSpeificationParameter[41].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[41].Y      = Y1 + MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[41].I      = 0;
    GcodeMaterialSpeificationParameter[41].J      = MaterialSpecificationIIIParameter.Ridus1;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[42].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[42].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[42].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[42].Speed = 1;
    GcodeMaterialSpeificationParameter[42].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[43].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[43].Action = GC_M05;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[44].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[44].Action = GC_M11;
    //定位至右边料第一个矩形的点
    SetBit(GcodeMaterialSpeificationParameter[45].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -L5/2+ Wide)Y(y1 + L3 +L4)
    GcodeMaterialSpeificationParameter[45].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[45].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[45].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[45].Speed = 10;
    GcodeMaterialSpeificationParameter[45].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[45].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4;

    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[46].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[46].Action = GC_M03;
    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[47].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[47].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[48].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[48].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[48].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[48].Speed = 30;
    GcodeMaterialSpeificationParameter[48].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割右边料第一个矩形
    SetBit(GcodeMaterialSpeificationParameter[49].ValueWords,WORD_GM);//G00 Y(y1 + L3 +L4 +L6)
    GcodeMaterialSpeificationParameter[49].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[49].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[49].Speed = 100;
    GcodeMaterialSpeificationParameter[49].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4 + MaterialSpecificationIIIParameter.L6;

    SetBit(GcodeMaterialSpeificationParameter[50].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2+ Wide)
    GcodeMaterialSpeificationParameter[50].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[50].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[50].Speed = 100;
    GcodeMaterialSpeificationParameter[50].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;

    SetBit(GcodeMaterialSpeificationParameter[51].ValueWords,WORD_GM);//G00  Y(y1 + L3 +L4)
    GcodeMaterialSpeificationParameter[51].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[51].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[51].Speed = 100;
    GcodeMaterialSpeificationParameter[51].Y      = Y1 + MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.L4;

    SetBit(GcodeMaterialSpeificationParameter[52].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -L5/2+ Wide)
    GcodeMaterialSpeificationParameter[52].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[52].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[52].Speed = 100;
    GcodeMaterialSpeificationParameter[52].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;

    //提刀
    SetBit(GcodeMaterialSpeificationParameter[53].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[53].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[53].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[53].Speed = 10;
    GcodeMaterialSpeificationParameter[53].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[54].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[54].Action = GC_M05;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[55].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[55].Action = GC_M11;


    if(LockHole)
    {
        //X轴右移动相当于Z轴
        SetBit(GcodeMaterialSpeificationParameter[56].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
        GcodeMaterialSpeificationParameter[56].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[56].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[56].Speed = 20;
        GcodeMaterialSpeificationParameter[56].X      = X3 + MaterialSpecificationIIIParameter.L2 +100*41.89;//X轴移动X3+料厚+10cm

        //主轴固定气缸开
        SetBit(GcodeMaterialSpeificationParameter[57].ValueWords,WORD_GM);//主轴固定气缸开
        GcodeMaterialSpeificationParameter[57].Action = GC_M16;
        //主轴旋转横向
        SetBit(GcodeMaterialSpeificationParameter[58].ValueWords,WORD_GM);//主轴旋转横向
        GcodeMaterialSpeificationParameter[58].Action = GC_M22;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[59].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[59].Action = GC_M17;

        //定位至右边料锁孔
        SetBit(GcodeMaterialSpeificationParameter[60].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)Y(y1 + L1 -L3 - L4 -L6)
        GcodeMaterialSpeificationParameter[60].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[60].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[60].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[60].Speed = 20;
        GcodeMaterialSpeificationParameter[60].Z      = Z1 - MaterialSpecificationIIIParameter.Wide/2 + MaterialSpecificationIIIParameter.L8/2;
        GcodeMaterialSpeificationParameter[60].Y      = Y1 + MaterialSpecificationIIIParameter.L7 ;


        //主轴提升气缸下
        SetBit(GcodeMaterialSpeificationParameter[61].ValueWords,WORD_GM);//主轴提升气缸下
        GcodeMaterialSpeificationParameter[61].Action = GC_M30;

        //主轴开
        SetBit(GcodeMaterialSpeificationParameter[62].ValueWords,WORD_GM);//主轴开
        GcodeMaterialSpeificationParameter[62].Action = GC_M18;
        //切削液开
        SetBit(GcodeMaterialSpeificationParameter[63].ValueWords,WORD_GM);//切削液喷开
        GcodeMaterialSpeificationParameter[63].Action = GC_M10;
        //X轴相当于Z轴了下刀
        SetBit(GcodeMaterialSpeificationParameter[64].ValueWords,WORD_GM);//G00 X轴下
        GcodeMaterialSpeificationParameter[64].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[64].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[64].Speed = 60;
        GcodeMaterialSpeificationParameter[64].X      = X3 + MaterialSpecificationIIIParameter.L2;
        //切割第一遍锁孔矩形
        SetBit(GcodeMaterialSpeificationParameter[65].ValueWords,WORD_GM);//G00  Y(y1 +L1 -L3 -L4)
        GcodeMaterialSpeificationParameter[65].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[65].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[65].Speed = 100;
        GcodeMaterialSpeificationParameter[65].Y      = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9;


        SetBit(GcodeMaterialSpeificationParameter[66].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2)
        GcodeMaterialSpeificationParameter[66].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[66].ValueWords,WORD_Z);
        GcodeMaterialSpeificationParameter[66].Speed = 100;
        GcodeMaterialSpeificationParameter[66].Z      = Z1 - MaterialSpecificationIIIParameter.Wide/2 - MaterialSpecificationIIIParameter.L8/2;

        SetBit(GcodeMaterialSpeificationParameter[67].ValueWords,WORD_GM);//G00 Y(y1 + L1 -L3 - L4 -L6)
        GcodeMaterialSpeificationParameter[67].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[67].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[67].Speed = 100;
        GcodeMaterialSpeificationParameter[67].Y      = Y1 + MaterialSpecificationIIIParameter.L7;

        SetBit(GcodeMaterialSpeificationParameter[68].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)
        GcodeMaterialSpeificationParameter[68].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[68].ValueWords,WORD_Z);
        GcodeMaterialSpeificationParameter[68].Speed = 100;
        GcodeMaterialSpeificationParameter[68].Z      = Z1 - MaterialSpecificationIIIParameter.Wide/2 + MaterialSpecificationIIIParameter.L8/2;
        //提刀X轴的提刀
        SetBit(GcodeMaterialSpeificationParameter[69].ValueWords,WORD_GM);//G00 Z-32
        GcodeMaterialSpeificationParameter[69].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[69].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[69].Speed = 60;
        GcodeMaterialSpeificationParameter[69].X      = X3 + MaterialSpecificationIIIParameter.L2 - 30*41.89;//X轴移动X3+料厚+10cm
        //第二遍切割锁孔矩形
        SetBit(GcodeMaterialSpeificationParameter[70].ValueWords,WORD_GM);//G00  Y(y1 +L1 -L3 -L4)
        GcodeMaterialSpeificationParameter[70].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[70].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[70].Speed = 100;
        GcodeMaterialSpeificationParameter[70].Y      = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9;

        SetBit(GcodeMaterialSpeificationParameter[71].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2)
        GcodeMaterialSpeificationParameter[71].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[71].ValueWords,WORD_Z);
        GcodeMaterialSpeificationParameter[71].Speed = 100;
        GcodeMaterialSpeificationParameter[71].Z      = Z1 - MaterialSpecificationIIIParameter.Wide/2 - MaterialSpecificationIIIParameter.L8/2;

        SetBit(GcodeMaterialSpeificationParameter[72].ValueWords,WORD_GM);//G00 Y(y1 + L1 -L3 - L4 -L6)
        GcodeMaterialSpeificationParameter[72].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[72].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[72].Speed = 100;
        GcodeMaterialSpeificationParameter[72].Y      = Y1 + MaterialSpecificationIIIParameter.L7;

        SetBit(GcodeMaterialSpeificationParameter[73].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)
        GcodeMaterialSpeificationParameter[73].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[73].ValueWords,WORD_Z);
        GcodeMaterialSpeificationParameter[73].Speed = 100;
        GcodeMaterialSpeificationParameter[73].Z      = Z1 - MaterialSpecificationIIIParameter.Wide/2 + MaterialSpecificationIIIParameter.L8/2;
        //提刀X轴的提刀
        SetBit(GcodeMaterialSpeificationParameter[74].ValueWords,WORD_GM);//G00 Z-32
        GcodeMaterialSpeificationParameter[74].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[74].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[74].Speed = 100;
        GcodeMaterialSpeificationParameter[74].X      = X3 + MaterialSpecificationIIIParameter.L2 +100*41.89;//X轴移动X3+料厚+10cm

        //ZY轴插补运算
        SetBit(GcodeMaterialSpeificationParameter[75].ValueWords,WORD_GM);//ZY轴插补运算
        GcodeMaterialSpeificationParameter[75].Action = GC_ZYInterpolationType;


        //定位至侧孔第一个圆点
        //定位至右边料锁孔
        SetBit(GcodeMaterialSpeificationParameter[76].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)Y(y1 + L1 -L3 - L4 -L6)
        GcodeMaterialSpeificationParameter[76].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[76].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[76].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[76].Speed = 20;
        GcodeMaterialSpeificationParameter[76].Z  = (z2 - MaterialSpecificationIIIParameterInitValue.Wide/2 - MaterialSpecificationIIIParameterInitValue.Ridus3)*160;
        GcodeMaterialSpeificationParameter[76].Y  = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9 + MaterialSpecificationIIIParameter.L10 ;

        //X轴相当于Z轴了下刀
        SetBit(GcodeMaterialSpeificationParameter[77].ValueWords,WORD_GM);//G00 X轴下
        GcodeMaterialSpeificationParameter[77].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[77].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[77].Speed = 30;
        GcodeMaterialSpeificationParameter[77].X      = X3 + MaterialSpecificationIIIParameter.L2;

        //切割锁孔第一个圆
        SetBit(GcodeMaterialSpeificationParameter[78].ValueWords,WORD_GM);//G02 X(x1 + L2/2) Y(y1 + L3 + R1) I R1 J 0
        GcodeMaterialSpeificationParameter[78].Action = GC_CW_ARC;
        SetBit(GcodeMaterialSpeificationParameter[78].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[78].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[78].Speed = 1;
        GcodeMaterialSpeificationParameter[78].Z   = ((z2 - MaterialSpecificationIIIParameterInitValue.Wide/2 - MaterialSpecificationIIIParameterInitValue.Ridus3)*1.091)*41.89 + MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[78].Y   = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9 + MaterialSpecificationIIIParameter.L10 + MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[78].I   = MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[78].J   = 0;

        SetBit(GcodeMaterialSpeificationParameter[79].ValueWords,WORD_GM);//G02 X(x1 + L2/2 +R1) Y(y1 + L3)	 I 0  J -R1
        GcodeMaterialSpeificationParameter[79].Action = GC_CW_ARC;
        SetBit(GcodeMaterialSpeificationParameter[79].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[79].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[79].Speed = 1;
        GcodeMaterialSpeificationParameter[79].Z      = ((z2 - MaterialSpecificationIIIParameterInitValue.Wide/2 - MaterialSpecificationIIIParameterInitValue.Ridus3)*1.091)*41.89 + 2*MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[79].Y      = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9 + MaterialSpecificationIIIParameter.L10;
        GcodeMaterialSpeificationParameter[79].I      = 0;
        GcodeMaterialSpeificationParameter[79].J      = -MaterialSpecificationIIIParameter.ZYRidus3;

        SetBit(GcodeMaterialSpeificationParameter[80].ValueWords,WORD_GM);//G02 X(x1 + L2/2) Y(y1 + L3 - R1) I -R1J 0
        GcodeMaterialSpeificationParameter[80].Action = GC_CW_ARC;
        SetBit(GcodeMaterialSpeificationParameter[80].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[80].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[80].Speed = 1;
        GcodeMaterialSpeificationParameter[80].Z      = ((z2 - MaterialSpecificationIIIParameterInitValue.Wide/2 - MaterialSpecificationIIIParameterInitValue.Ridus3)*1.091)*41.89 + MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[80].Y      = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9 + MaterialSpecificationIIIParameter.L10 - MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[80].I      = -MaterialSpecificationIIIParameter.ZYRidus3;
        GcodeMaterialSpeificationParameter[80].J      = 0;

        SetBit(GcodeMaterialSpeificationParameter[81].ValueWords,WORD_GM);//G02 X(x1 + L2/2 - R1) Y(y1 + L3) I 0  JR1
        GcodeMaterialSpeificationParameter[81].Action = GC_CW_ARC;
        SetBit(GcodeMaterialSpeificationParameter[81].ValueWords,WORD_Z);
        SetBit(GcodeMaterialSpeificationParameter[81].ValueWords,WORD_Y);
        GcodeMaterialSpeificationParameter[81].Speed = 1;
        GcodeMaterialSpeificationParameter[81].Z      = ((z2 - MaterialSpecificationIIIParameterInitValue.Wide/2 - MaterialSpecificationIIIParameterInitValue.Ridus3)*1.091)*41.89;
        GcodeMaterialSpeificationParameter[81].Y      = Y1 + MaterialSpecificationIIIParameter.L7 + MaterialSpecificationIIIParameter.L9 + MaterialSpecificationIIIParameter.L10;
        GcodeMaterialSpeificationParameter[81].I      = 0;
        GcodeMaterialSpeificationParameter[81].J      = MaterialSpecificationIIIParameter.ZYRidus3;


        //XY轴插补运算
        SetBit(GcodeMaterialSpeificationParameter[82].ValueWords,WORD_GM);//ZY轴插补运算
        GcodeMaterialSpeificationParameter[82].Action = GC_XYInterpolationType;

        //提刀X轴的提刀
        SetBit(GcodeMaterialSpeificationParameter[83].ValueWords,WORD_GM);//G00 Z-32
        GcodeMaterialSpeificationParameter[83].Action = GC_SEEK_G0;
        SetBit(GcodeMaterialSpeificationParameter[83].ValueWords,WORD_X);
        GcodeMaterialSpeificationParameter[83].Speed = 20;
        GcodeMaterialSpeificationParameter[83].X      = X3 + MaterialSpecificationIIIParameter.L2 +100*41.89;//X轴移动X3+料厚+10cm
        //主轴固定气缸开
        SetBit(GcodeMaterialSpeificationParameter[84].ValueWords,WORD_GM);//主轴提升气缸下
        GcodeMaterialSpeificationParameter[84].Action = GC_M16;
        //主轴旋转竖向
        SetBit(GcodeMaterialSpeificationParameter[85].ValueWords,WORD_GM);//主轴旋转竖向
        GcodeMaterialSpeificationParameter[85].Action = GC_M23;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[86].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[86].Action = GC_M17;
        //主轴提升气缸上
        SetBit(GcodeMaterialSpeificationParameter[87].ValueWords,WORD_GM);//主轴提升气缸下
        GcodeMaterialSpeificationParameter[87].Action = GC_M29;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[88].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[88].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[89].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[89].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[90].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[90].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[91].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[91].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[92].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[92].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[93].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[93].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[94].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[94].Action = GC_M17;
        //主轴固定气缸关
        SetBit(GcodeMaterialSpeificationParameter[95].ValueWords,WORD_GM);//主轴固定气缸关
        GcodeMaterialSpeificationParameter[95].Action = GC_M17;
    }
    else
    {
        for(i = 0;i <28 ;i ++)
        {
            GcodeMaterialSpeificationParameter[56 + i] = Zero;
        }
    }
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[96].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[96].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[96].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[96].Speed = 10;
    GcodeMaterialSpeificationParameter[96].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //定位至左边料第二个矩形的点
    SetBit(GcodeMaterialSpeificationParameter[97].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)Y(y1 + L1 -L3 - L4 -L6)
    GcodeMaterialSpeificationParameter[97].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[97].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[97].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[97].Speed = 10;
    GcodeMaterialSpeificationParameter[97].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2;
    GcodeMaterialSpeificationParameter[97].Y      = Y1 + MaterialSpecificationIIIParameter.L1 -MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4 - MaterialSpecificationIIIParameter.L6;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[98].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[98].Action = GC_M03;
    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[99].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[99].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[100].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[100].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[100].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[100].Speed = 30;
    GcodeMaterialSpeificationParameter[100].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割左边料第二个矩形
    SetBit(GcodeMaterialSpeificationParameter[101].ValueWords,WORD_GM);//G00 Y(y1 +L1 -L3 -L4)
    GcodeMaterialSpeificationParameter[101].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[101].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[101].Speed = 100;
    GcodeMaterialSpeificationParameter[101].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4;

    SetBit(GcodeMaterialSpeificationParameter[102].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2)
    GcodeMaterialSpeificationParameter[102].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[102].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[102].Speed = 100;
    GcodeMaterialSpeificationParameter[102].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L5/2;

    SetBit(GcodeMaterialSpeificationParameter[103].ValueWords,WORD_GM);//G00  Y(y1 + L1 -L3 - L4 -L6)
    GcodeMaterialSpeificationParameter[103].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[103].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[103].Speed = 100;
    GcodeMaterialSpeificationParameter[103].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4 -MaterialSpecificationIIIParameter.L6;

    SetBit(GcodeMaterialSpeificationParameter[104].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2)
    GcodeMaterialSpeificationParameter[104].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[104].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[104].Speed = 100;
    GcodeMaterialSpeificationParameter[104].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[105].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[105].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[105].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[105].Speed = 1;
    GcodeMaterialSpeificationParameter[105].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm

    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[106].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[106].Action = GC_M05;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[107].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[107].Action = GC_M11;
    //定位至左边第二个圆的点
    SetBit(GcodeMaterialSpeificationParameter[108].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -R1)   Y(y1 + L1 -L3)
    GcodeMaterialSpeificationParameter[108].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[108].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[108].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[108].Speed = 10;
    GcodeMaterialSpeificationParameter[108].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[108].Y      = Y1 + MaterialSpecificationIIIParameter.L1 -MaterialSpecificationIIIParameter.L3;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[109].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[109].Action = GC_M18;
    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[110].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[110].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[111].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[111].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[111].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[111].Speed = 30;
    GcodeMaterialSpeificationParameter[111].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割左边第二个圆
    SetBit(GcodeMaterialSpeificationParameter[112].ValueWords,WORD_GM);//GO2 X(x1 + L2/2) Y(y1 + L1 -L3 +R1)   I R1 J 0
    GcodeMaterialSpeificationParameter[112].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[112].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[112].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[112].Speed = 1;
    GcodeMaterialSpeificationParameter[112].X      = X1 - MaterialSpecificationIIIParameter.L2/2;
    GcodeMaterialSpeificationParameter[112].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[112].I      = MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[112].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[113].ValueWords,WORD_GM);//G02 X(x1 + L2/2 +R1) Y(y1 + L1 -L3)  I 0  J -R1
    GcodeMaterialSpeificationParameter[113].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[113].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[113].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[113].Speed = 1;
    GcodeMaterialSpeificationParameter[113].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[113].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[113].I      = 0;
    GcodeMaterialSpeificationParameter[113].J      = -MaterialSpecificationIIIParameter.Ridus1;

    SetBit(GcodeMaterialSpeificationParameter[114].ValueWords,WORD_GM);//G02 X(x1 + L2/2) Y(y1 + L1 -L3 -R1)   I -R1J 0
    GcodeMaterialSpeificationParameter[114].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[114].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[114].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[114].Speed = 1;
    GcodeMaterialSpeificationParameter[114].X      = X1 - MaterialSpecificationIIIParameter.L2/2;
    GcodeMaterialSpeificationParameter[114].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[114].I      = -MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[114].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[115].ValueWords,WORD_GM);//G02 X(x1 + L2/2 -R1) Y(y1 + L1 -L3)  I 0  JR1
    GcodeMaterialSpeificationParameter[115].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[115].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[115].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[115].Speed = 1;
    GcodeMaterialSpeificationParameter[115].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[115].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[115].I      = 0;
    GcodeMaterialSpeificationParameter[115].J      = MaterialSpecificationIIIParameter.Ridus1;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[116].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[116].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[116].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[116].Speed = 10;
    GcodeMaterialSpeificationParameter[116].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[117].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[117].Action = GC_M19;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[118].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[118].Action = GC_M11;
    //定位至右边料第二个矩形的点
    SetBit(GcodeMaterialSpeificationParameter[119].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2+ Wide)Y(y1 + L1 -L3 - L4 -L6)
    GcodeMaterialSpeificationParameter[119].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[119].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[119].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[119].Speed = 10;
    GcodeMaterialSpeificationParameter[119].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[119].Y      = Y1 + MaterialSpecificationIIIParameter.L1 -MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4 - MaterialSpecificationIIIParameter.L6;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[120].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[120].Action = GC_M18;

    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[121].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[121].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[122].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[122].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[122].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[122].Speed = 30;
    GcodeMaterialSpeificationParameter[122].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割右边料第二个矩形
    SetBit(GcodeMaterialSpeificationParameter[123].ValueWords,WORD_GM);//G00 Y(y1 +L1 -L3 -L4)
    GcodeMaterialSpeificationParameter[123].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[123].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[123].Speed = 100;
    GcodeMaterialSpeificationParameter[123].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4;

    SetBit(GcodeMaterialSpeificationParameter[124].ValueWords,WORD_GM);//G00 X(x1 + L2/2 + L5/2+ Wide)
    GcodeMaterialSpeificationParameter[124].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[124].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[124].Speed = 100;
    GcodeMaterialSpeificationParameter[124].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;

    SetBit(GcodeMaterialSpeificationParameter[125].ValueWords,WORD_GM);//G00 Y(y1 + L1 -L3 - L4 -L6)
    GcodeMaterialSpeificationParameter[125].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[125].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[125].Speed = 100;
    GcodeMaterialSpeificationParameter[125].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.L4 -MaterialSpecificationIIIParameter.L6;

    SetBit(GcodeMaterialSpeificationParameter[126].ValueWords,WORD_GM);//G00 X(x1 + L2/2 - L5/2+ Wide)
    GcodeMaterialSpeificationParameter[126].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[126].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[126].Speed = 100;
    GcodeMaterialSpeificationParameter[126].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.L5/2 + MaterialSpecificationIIIParameter.L2 + X2;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[127].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[127].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[127].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[127].Speed = 10;
    GcodeMaterialSpeificationParameter[127].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[128].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[128].Action = GC_M19;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[129].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[129].Action = GC_M11;
    //定位至右边第二个圆的点
    SetBit(GcodeMaterialSpeificationParameter[130].ValueWords,WORD_GM);//G00 X(x1 + L2/2 -R1+ Wide)   Y(y1 + L1 -L3)
    GcodeMaterialSpeificationParameter[130].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[130].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[130].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[130].Speed = 10;
    GcodeMaterialSpeificationParameter[130].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[130].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3;
    //主轴开
    SetBit(GcodeMaterialSpeificationParameter[131].ValueWords,WORD_GM);//主轴开
    GcodeMaterialSpeificationParameter[131].Action = GC_M18;
    //切削液开
    SetBit(GcodeMaterialSpeificationParameter[132].ValueWords,WORD_GM);//切削液喷开
    GcodeMaterialSpeificationParameter[132].Action = GC_M10;
    //下刀
    SetBit(GcodeMaterialSpeificationParameter[133].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    GcodeMaterialSpeificationParameter[133].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[133].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[133].Speed = 30;
    GcodeMaterialSpeificationParameter[133].Z      = Z3 - MaterialSpecificationIIIParameter.Wide +20*160;//到料厚位置下刀1cm
    //切割右边第二个圆
    SetBit(GcodeMaterialSpeificationParameter[134].ValueWords,WORD_GM);//GO2 X(x1 + L2/2+ Wide)       Y(y1 + L1 -L3 +R1)   I R1 J 0
    GcodeMaterialSpeificationParameter[134].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[134].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[134].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[134].Speed = 1;
    GcodeMaterialSpeificationParameter[134].X      = X1 - MaterialSpecificationIIIParameter.L2/2 +  MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[134].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 + MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[134].I      = MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[134].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[135].ValueWords,WORD_GM);//G02 X(x1 + L2/2 +R1+ Wide)   Y(y1 + L1 -L3)       I 0  J -R1
    GcodeMaterialSpeificationParameter[135].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[135].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[135].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[135].Speed = 1;
    GcodeMaterialSpeificationParameter[135].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[135].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[135].I      = 0;
    GcodeMaterialSpeificationParameter[135].J      = -MaterialSpecificationIIIParameter.Ridus1;

    SetBit(GcodeMaterialSpeificationParameter[136].ValueWords,WORD_GM);//G02 X(x1 + L2/2+ Wide)  Y(y1 + L1 -L3 -R1)   I -R1J 0
    GcodeMaterialSpeificationParameter[136].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[136].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[136].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[136].Speed = 1;
    GcodeMaterialSpeificationParameter[136].X      = X1 - MaterialSpecificationIIIParameter.L2/2 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[136].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3 - MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[136].I      = -MaterialSpecificationIIIParameter.Ridus1;
    GcodeMaterialSpeificationParameter[136].J      = 0;

    SetBit(GcodeMaterialSpeificationParameter[137].ValueWords,WORD_GM);//G02 X(x1 + L2/2 -R1+ Wide)  Y(y1 + L1 -L3)   I 0  JR1
    GcodeMaterialSpeificationParameter[137].Action = GC_CW_ARC;
    SetBit(GcodeMaterialSpeificationParameter[137].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[137].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[137].Speed = 1;
    GcodeMaterialSpeificationParameter[137].X      = X1 - MaterialSpecificationIIIParameter.L2/2 - MaterialSpecificationIIIParameter.Ridus1 + MaterialSpecificationIIIParameter.L2 + X2;
    GcodeMaterialSpeificationParameter[137].Y      = Y1 + MaterialSpecificationIIIParameter.L1 - MaterialSpecificationIIIParameter.L3;
    GcodeMaterialSpeificationParameter[137].I      = 0;
    GcodeMaterialSpeificationParameter[137].J      = MaterialSpecificationIIIParameter.Ridus1;
    //提刀
    SetBit(GcodeMaterialSpeificationParameter[138].ValueWords,WORD_GM);//G00 Z-32
    GcodeMaterialSpeificationParameter[138].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[138].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[138].Speed = 10;
    GcodeMaterialSpeificationParameter[138].Z      = Z3 - MaterialSpecificationIIIParameter.Wide - 20*160;//到料厚位置上刀3cm
    //主轴关
    SetBit(GcodeMaterialSpeificationParameter[139].ValueWords,WORD_GM);//主轴关
    GcodeMaterialSpeificationParameter[139].Action = GC_M19;
    //切削液关
    SetBit(GcodeMaterialSpeificationParameter[140].ValueWords,WORD_GM);//切削液喷关
    GcodeMaterialSpeificationParameter[140].Action = GC_M11;
    //切割第二个45度角,移动到右前方
    SetBit(GcodeMaterialSpeificationParameter[141].ValueWords,WORD_GM);//G00 X444   Y(y1 + L1 -L3 +y2)//////在进行X、Y两轴的G0时，先走X轴等X轴走完后再走Y轴，并不能同时走
    GcodeMaterialSpeificationParameter[141].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[141].ValueWords,WORD_X);
    SetBit(GcodeMaterialSpeificationParameter[141].ValueWords,WORD_Y);
    GcodeMaterialSpeificationParameter[141].Speed = 10;
    GcodeMaterialSpeificationParameter[141].X      = 10*44.4;
    GcodeMaterialSpeificationParameter[141].Y      = Y1 + MaterialSpecificationIIIParameter.L1 -MaterialSpecificationIIIParameter.L3 + Y2;

    //提升气缸下
    SetBit(GcodeMaterialSpeificationParameter[142].ValueWords,WORD_GM);//锯提升气缸下
    GcodeMaterialSpeificationParameter[142].Action = GC_M09;
    //锯固定气缸松开
    SetBit(GcodeMaterialSpeificationParameter[143].ValueWords,WORD_GM);//GC_M15锯固定气缸松开
    GcodeMaterialSpeificationParameter[143].Action = GC_M15;
    //	//下刀
    //	SetBit(GcodeMaterialSpeificationParameter[131].ValueWords,WORD_GM);//G00 Z-32 锯Z轴下
    //	GcodeMaterialSpeificationParameter[131].Action = GC_SEEK_G0;
    //	SetBit(GcodeMaterialSpeificationParameter[131].ValueWords,WORD_Z);
    //	GcodeMaterialSpeificationParameter[131].Speed = 1;
    //	GcodeMaterialSpeificationParameter[131].Z      = -50*160;
    //锯转90度
    SetBit(GcodeMaterialSpeificationParameter[144].ValueWords,WORD_GM);//M20锯正旋转90度
    GcodeMaterialSpeificationParameter[144].Action = GC_M21;
    //	//右进120cm进行切割
    //	SetBit(GcodeMaterialSpeificationParameter[133].ValueWords,WORD_GM);//G00  X444
    //	GcodeMaterialSpeificationParameter[133].Action = GC_SEEK_G0;
    //	SetBit(GcodeMaterialSpeificationParameter[133].ValueWords,WORD_X);
    //	GcodeMaterialSpeificationParameter[133].Speed = 1;
    //	GcodeMaterialSpeificationParameter[133].X      = 120*44.4;
    //锯固定气缸夹紧
    SetBit(GcodeMaterialSpeificationParameter[145].ValueWords,WORD_GM);//锯固定气缸夹紧
    GcodeMaterialSpeificationParameter[145].Action = GC_M14;
    //开锯
    SetBit(GcodeMaterialSpeificationParameter[146].ValueWords,WORD_GM);//M06锯开
    GcodeMaterialSpeificationParameter[146].Action = GC_M06;
    //锯下刀
    SetBit(GcodeMaterialSpeificationParameter[147].ValueWords,WORD_GM);//G00 Z-12 锯Z轴上
    GcodeMaterialSpeificationParameter[147].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[147].ValueWords,WORD_Z);
    GcodeMaterialSpeificationParameter[147].Speed = 30;
    GcodeMaterialSpeificationParameter[147].Z      = 1*160;//////和对面的Z轴下的距离一样，都保持回零点的位置
    //右进12cm进行切割
    SetBit(GcodeMaterialSpeificationParameter[148].ValueWords,WORD_GM);//G00  X444
    GcodeMaterialSpeificationParameter[148].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[148].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[148].Speed = 30;
    GcodeMaterialSpeificationParameter[148].X      = 1200*44.4;
    //锯固定气缸松开
    SetBit(GcodeMaterialSpeificationParameter[149].ValueWords,WORD_GM);//GC_M15锯固定气缸松开
    GcodeMaterialSpeificationParameter[149].Action = GC_M15;
    //关锯
    SetBit(GcodeMaterialSpeificationParameter[150].ValueWords,WORD_GM);//GC_M07锯关
    GcodeMaterialSpeificationParameter[150].Action = GC_M07;
    //左1cm进行切割
    SetBit(GcodeMaterialSpeificationParameter[151].ValueWords,WORD_GM);//G00  X444
    GcodeMaterialSpeificationParameter[151].Action = GC_SEEK_G0;
    SetBit(GcodeMaterialSpeificationParameter[151].ValueWords,WORD_X);
    GcodeMaterialSpeificationParameter[151].Speed = 10;
    GcodeMaterialSpeificationParameter[151].X      = 10*44.4;
    //锯旋转+45
    SetBit(GcodeMaterialSpeificationParameter[152].ValueWords,WORD_GM);//GC_M20锯旋转+45
    GcodeMaterialSpeificationParameter[152].Action = GC_M20;
    //锯提升气缸上
    SetBit(GcodeMaterialSpeificationParameter[153].ValueWords,WORD_GM);//锯提升气缸上
    GcodeMaterialSpeificationParameter[153].Action = GC_M08;
    SetBit(GcodeMaterialSpeificationParameter[153].ValueWords,WORD_GM);//夹料气缸松开
    GcodeMaterialSpeificationParameter[153].Action = GC_M12;
}



