#ifndef MATERIALTYPEFOUR_H
#define MATERIALTYPEFOUR_H
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
    int Ridus2;////Ridus2;//���Բ�İ뾶������YZƽ���Z�ᶨλ���㣬Y�ᶨλ������Ridus3
    int Ridus3;//Ridus3;���Բ�뾶������YZƽ��Ĳ岹����
    int ZYRidus3;//ZYRidus3���Բ����ZY�岹������
    int L10;
    int Wide;
    int ZYWide;
}MaterialTypeFourParameter;//liaoxingsanjiegouti

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
    int Ridus2;////Ridus2;//���Բ�İ뾶������YZƽ���Z�ᶨλ���㣬Y�ᶨλ������Ridus3
    int Ridus3;//Ridus3;���Բ�뾶������YZƽ��Ĳ岹����
    int ZYRidus3;//ZYRidus3���Բ����ZY�岹������
    int L10;
    int Wide;
    int ZYWide;
}MaterialTypeFourParameterInitValue;

void CalculateMaterialtypefourGcode(void);//����һ��G�����������

class MaterialTypeFour
{
public:
    MaterialTypeFour();
};

#endif // MATERIALTYPEFOUR_H
