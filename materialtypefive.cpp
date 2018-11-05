#include "materialtypefive.h"
#include "gcode.h"//包含G代码的结构体定义
MaterialTypeFive::MaterialTypeFive()
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
MaterialTypeFiveParameterInitValue MaterialSpecificationIVParameterInitValue = //////用于赋值初始值
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
MaterialTypeFiveParameter MaterialSpecificationIVParameter;//////用于计算尺寸
//用于赋初值
GCodeStruct Zerofive =
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
void CalculateMaterialtypefiveGcode(void)//料型一的G代码参数计算
{


}
