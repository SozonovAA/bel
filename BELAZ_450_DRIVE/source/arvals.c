/*
 * arvals.c
 *
 *  Created on: 29.01.2018
 *      Author: Smirnov_AS
 */

#include "hfa.h"

void InitAddrArray();

#pragma CODE_SECTION(InitAddrArray,"ramfuncs")

Uint16 AddrArray[NUM_OF_VARIABLES];
int TestV=1234;

/*
int16 IaL=0;
int16 IbL=0;
int16 IcL=0;

int16 IAlphaL=0;
int16 IBetaL=0;

int16 IdzL=0;
int16 IdL=0;
int16 SIdL=0;
int16 DeltaIdOldL=0;
int16 DeltaIdL=0;
int16 UUdL=0;

int16 IqzL=0;
int16 IqL=0;
int16 SIqL=0;
int16 DeltaIqOldL=0;
int16 DeltaIqL=0;
int16 UUqL=0;
*/

extern int TestCountArray;

extern int16 UAXL;
extern Uint16 SpeedTestCount;

extern Uint16 QF_STate;
extern Uint16 KM_State;
extern Uint16 KM_ON_Command;

extern Uint16 F1;
extern Uint16 F2;
extern Uint16 FDIL;
extern Uint16 FDI;

extern int LK1;
extern int LK2;
extern int LL1;
extern int LTS;
extern int LTR;
extern int LLM;

extern int RK1;
extern int RK2;
extern int RL1;
extern int RTS;
extern int RTR;
extern int RLM;

extern int M1;

void InitAddrArray()
{

		//____________________________________
	AddrArray[0] = (Uint16)&array_step;
	AddrArray[1] = (Uint16)&RPMDiz;
	AddrArray[2] = (Uint16)&Udz;
	AddrArray[3] = (Uint16)&Ud;
	AddrArray[4] = (Uint16)&Ugen;
	AddrArray[5] = (Uint16)&Iv;
	AddrArray[6] = (Uint16)&Igen;
	AddrArray[7] = (Uint16)&alpha16;
	AddrArray[8] = (Uint16)&TestV;
	AddrArray[9] = (Uint16)&ChopReg;
//____________________________________
	AddrArray[10] = (Uint16)&UUAL;
	AddrArray[11] = (Uint16)&UUBL;
	AddrArray[12] = (Uint16)&UUCL;
	AddrArray[13] = (Uint16)&IaL;
	AddrArray[14] = (Uint16)&IbL;
	AddrArray[15] = (Uint16)&IcL;
	AddrArray[16] = (Uint16)&IdzL;
	AddrArray[17] = (Uint16)&IdL;
	AddrArray[18] = (Uint16)&IqzL;
	AddrArray[19] = (Uint16)&IqL;

//____________________________________
	AddrArray[20] = (Uint16)&E_MaxL;
	AddrArray[21] = (Uint16)&E_LineL;
	AddrArray[22] = (Uint16)&E_ampL;
	AddrArray[23] = (Uint16)&IqLMAX;
	AddrArray[24] = (Uint16)&fUmL;
	AddrArray[25] = (Uint16)&UkdL;
	AddrArray[26] = (Uint16)&UkqL;
	AddrArray[27] = (Uint16)&UUdL;
	AddrArray[28] = (Uint16)&UUqL;
	AddrArray[29] = (Uint16)&ThetaL;
//____________________________________
	AddrArray[30] = (Uint16)&SpeedLz1_16;
	AddrArray[31] = (Uint16)&DeltaSpeedL1;
	AddrArray[32] = (Uint16)&DeltaSpeedL;
	AddrArray[33] = (Uint16)&SpeedL;
	AddrArray[34] = (Uint16)&SpeedLz;
	AddrArray[35] = (Uint16)&Iaz;
	AddrArray[36] = (Uint16)&ImL;
	AddrArray[37] = (Uint16)&UdSIL;
	AddrArray[38] = (Uint16)&UqSIL;
	AddrArray[39] = (Uint16)&UAlphaSIL;
//____________________________________
	AddrArray[40] = (Uint16)&UUAR;
	AddrArray[41] = (Uint16)&UUBR;
	AddrArray[42] = (Uint16)&UUCR;
	AddrArray[43] = (Uint16)&IaR;
	AddrArray[44] = (Uint16)&IbR;
	AddrArray[45] = (Uint16)&IcR;
	AddrArray[46] = (Uint16)&IdzR;
	AddrArray[47] = (Uint16)&IdR;
	AddrArray[48] = (Uint16)&IqzR;
	AddrArray[49] = (Uint16)&IqR;

//____________________________________
	AddrArray[50] = (Uint16)&E_MaxR;
	AddrArray[51] = (Uint16)&E_LineR;
	AddrArray[52] = (Uint16)&E_ampR;
	AddrArray[53] = (Uint16)&IqRMAX;
	AddrArray[54] = (Uint16)&fUmR;
	AddrArray[55] = (Uint16)&UkdR;
	AddrArray[56] = (Uint16)&UkqR;
	AddrArray[57] = (Uint16)&UUdR;
	AddrArray[58] = (Uint16)&UUqR;
	AddrArray[59] = (Uint16)&ThetaR;
//____________________________________
	AddrArray[60] = (Uint16)&SpeedRz1_16;
	AddrArray[61] = (Uint16)&DeltaSpeedR1;
	AddrArray[62] = (Uint16)&DeltaSpeedR;
	AddrArray[63] = (Uint16)&SpeedR;
	AddrArray[64] = (Uint16)&SpeedRz;
	AddrArray[65] = (Uint16)&EAlphaInstL;
	AddrArray[66] = (Uint16)&EBetaInstL;
	AddrArray[67] = (Uint16)&EAlphaInstR;
	AddrArray[68] = (Uint16)&EBetaInstR;
	AddrArray[69] = (Uint16)&AverageCarSpeed;
//____________________________________
	AddrArray[70] = (Uint16)&M1;//phi_int;
	AddrArray[71] = (Uint16)&CTR_CAP4;
	AddrArray[72] = (Uint16)&CTR_CAP1;
	AddrArray[73] = (Uint16)&CTR_CAP2;
	AddrArray[74] = (Uint16)&freq_3_harm;
	AddrArray[75] = (Uint16)&PowerMax16;
	AddrArray[76] = (Uint16)&PowerL16;
	AddrArray[77] = (Uint16)&PowerR16;
	AddrArray[78] = (Uint16)&UAlphaSIR;//LLM;
	AddrArray[79] = (Uint16)&UBetaSIR ;//RLM;
//____________________________________
	AddrArray[80] = (Uint16)&LimitSummSpeedL;//LK1;
	AddrArray[81] = (Uint16)&LimitSummSpeedR;//RK1;
	AddrArray[82] = (Uint16)&SpeedLzCruize;//LK2;
	AddrArray[83] = (Uint16)&SpeedRzCruize;//RK2;
	AddrArray[84] = (Uint16)&UAlphaSIL;//LL1;
	AddrArray[85] = (Uint16)&UBetaSIL ;//RL1;
	AddrArray[86] = (Uint16)&IqzLCruize;//LTS;
	AddrArray[87] = (Uint16)&IqzRCruize;//RTS;
	AddrArray[88] = (Uint16)&SummSpeedLint;//LTR;
	AddrArray[89] = (Uint16)&SummSpeedRint;//RTR;
//____________________________________
	AddrArray[90] = (Uint16)&PowerUvtr;
	AddrArray[91] = (Uint16)&DeltaSpeedLCruize;
	AddrArray[92] = (Uint16)&DeltaSpeedRCruize;
	AddrArray[93] = (Uint16)&IfRMSL;
	AddrArray[94] = (Uint16)&iffL;
	AddrArray[95] = (Uint16)&Faults1;
	AddrArray[96] = (Uint16)&Faults2;
	AddrArray[97] = (Uint16)&FaultsC;
	AddrArray[98] = (Uint16)&FaultsDINV;
	AddrArray[99] = (Uint16)&FaultsDCHOP;
//____________________________________
}

