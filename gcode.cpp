#include "gcode.h"




GCodeStruct G_Code;
unsigned char OneLine[64];						//一条Gcode的ASCII码的储存数组



GCodeStruct GcodeMaterialSpeificationParameter[200];//存放各种料型计算G代码参数的数组



GCode::GCode()
{

}
