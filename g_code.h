#ifndef G_CODE_H
#define G_CODE_H


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
typedef struct
{

    unsigned char Action;
    unsigned short int ValueWords;
    unsigned short int Speed;
    signed int X;
    signed int Y;
    signed short int I;
    signed short int J;
    signed int Z;
    signed int W;
    unsigned int N;
//	u16 F;
//	s32 K;
//	float L;
//	float P;
//	float R;
//	float S;
}GCodeStruct;



#endif // G_CODE_H
