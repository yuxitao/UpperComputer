#ifndef MATERIALTYPEFIVE_H
#define MATERIALTYPEFIVE_H
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
}MaterialTypeFiveParameter;//liaoxingsanjiegouti

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
}MaterialTypeFiveParameterInitValue;

void CalculateMaterialtypefiveGcode(void);//����һ��G�����������

class MaterialTypeFive
{
public:
    MaterialTypeFive();
};

#endif // MATERIALTYPEFIVE_H
