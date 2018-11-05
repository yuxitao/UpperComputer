#ifndef MATERIALTYPETHREE_H
#define MATERIALTYPETHREE_H


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
}MaterialSpecificationTypeThreeParameter;//liaoxingsanjiegouti

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
}MaterialSpecificationTypeThreeParameterInitValue;

void CalculateMaterialtypethreeGcode(void);//根据料参数计算G代码
void CalculateTestGcode(void);//测试尺寸用G代码赋值计算

class MaterialTypeThree
{
public:
    MaterialTypeThree();
};

#endif // MATERIALTYPETHREE_H
