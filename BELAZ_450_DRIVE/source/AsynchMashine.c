#include "hfa.h"

struct MashineParam MPL;
struct MashineParam MPR;

void CalcCurMParms(struct MashineParam *M);
void StaticMparams(struct MashineParam *M);

#pragma CODE_SECTION(CalcCurMParms,"ramfuncs")
#pragma CODE_SECTION(StaticMparams,"ramfuncs")

/*
#define LS		0.00015
#define LR		0.00014
#define RR		0.00500
#define RS		0.00720
#define K1		LM/(LS+LM)
#define K2		LM/(LR+LM)
#define L1		(LS+LM)*(1-K1*K2)
#define TS		L1/RS
#define TR		(LR+LM)/RR
#define dt		0.000666
*/

int LK1=0;
int LK2=0;
int LL1=0;
int LTS=0;
int LTR=0;
int LLM=0;

int RK1=0;
int RK2=0;
int RL1=0;
int RTS=0;
int RTR=0;
int RLM=0;

void StaticMparams(struct MashineParam *M)
{
	M->LS = 0.00015;
	M->LR = 0.00014;
	M->LM = 0.0067;
	M->RS = /*0.005*/0.0072;
	M->RR = 0.00483;
}

void CalcCurMParms(struct MashineParam *M)
{

	M->K1 = M->LM/(M->LS+M->LM);
	M->K2 = M->LM/(M->LR+M->LM);
	M->L1 = (M->LS+M->LM)*(1-M->K1*M->K2);
	M->TS = M->L1/M->RS;
	M->TR = (M->LR+M->LM)/M->RR;

	LK1=MPL.K1*10000;
	LK2=MPL.K2*10000;
	LL1=MPL.L1*10000;
	LTS=MPL.TS*10000;
	LTR=MPL.TR*10000;
	LLM=MPL.LM*10000;

	RK1=MPR.K1*10000;
	RK2=MPR.K2*10000;
	RL1=MPR.L1*10000;
	RTS=MPR.TS*10000;
	RTR=MPR.TR*10000;
	RLM=MPR.LM*10000;

}





