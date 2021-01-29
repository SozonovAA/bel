
//declare in func.c
/*extern float LM;

#define LS		0.00015
#define LR		0.00014
#define RR		0.00500
#define RS		0.00720
#define K1		LM/(LS+LM)
#define K2		LM/(LR+LM)
#define L1		(LS+LM)*(1-K1*K2)
#define TS		L1/RS
#define TR		(LR+LM)/RR
*/


struct MashineParam{
		float LS;
		float LR;
		float LM;
		float RR;
		float RS;
		float K1;
		float K2;
		float L1;
		float TS;
		float TR;
};

extern struct MashineParam MPL;
extern struct MashineParam MPR;

/*

	LM = 0.0028
	K1 = 0.949
	K2 = 0.952
	L1 = 0.00028
	T1 = 0.039
	T2 = 0.058

K1			K2			L1			T1			T2
0,949152542	0,952380952	0,000283333	0,039351852	0,588

*/


