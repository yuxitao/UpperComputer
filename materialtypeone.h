#ifndef MATERIALTYPEONE_H
#define MATERIALTYPEONE_H

typedef struct
{
    int L1;
    int L2;
    int L3;
    int L4;
    int L5;
    int L6;
    int L7;
    int L8;
    int L9;
    int Ridus1;
    int Ridus2;////Ridus2;//侧孔圆的半径，用于YZ平面的Z轴定位运算，Y轴定位运算用Ridus3
    int Ridus3;//Ridus3;侧孔圆半径，用于YZ平面的插补运算
    int ZYRidus3;//ZYRidus3侧孔圆用于ZY插补的运算
    int L10;
    int Wide;
    int ZYWide;
}MaterialTypeOneParameter;//liaoxingsanjiegouti

typedef struct
{
    int L1;
    int L2;
    int L3;
    int L4;
    int L5;
    int L6;
    int L7;
    int L8;
    int L9;
    int Ridus1;
    int Ridus2;////Ridus2;//侧孔圆的半径，用于YZ平面的Z轴定位运算，Y轴定位运算用Ridus3
    int Ridus3;//Ridus3;侧孔圆半径，用于YZ平面的插补运算
    int ZYRidus3;//ZYRidus3侧孔圆用于ZY插补的运算
    int L10;
    int Wide;
    int ZYWide;
}MaterialTypeOneParameterInitValue;

void CalculateMaterialtypeoneGcode(void);//料型一的G代码参数计算

class MaterialTypeOne
{
public:
    MaterialTypeOne();
};

#endif // MATERIALTYPEONE_H
