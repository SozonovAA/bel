#include "hfa.h"

void DizelOutPowerMax();
#pragma CODE_SECTION(DizelOutPowerMax,"ramfuncs")

float KDIS[2]={3.5,0.7};
float BDIS[2]={-3520,300};

Uint16 RPMDiz=0;
int32 PowerMax=0;
Uint16 DisState=0;
Uint16 PowerMax16=0;
int32 fPowerMax=0;

int32 XP=0;

int fPowerMAX=1;

void DizelOutPowerMax(){

	RPMDiz = freq_3_harm*5;

	    if(RPMDiz <= 1200)  PowerMax = 100;
		if(RPMDiz > 1200 && RPMDiz <= 1350) DisState=0;
		if(RPMDiz > 1350) DisState=1;

		if(fPowerMAX == 1)
			PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState] + 50;
		if(fPowerMAX == 2)
			PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState];
		if(fPowerMAX == 0)
			PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState] - 100;


	if(PowerMax < 100) PowerMax = 100;
	if(PowerMax > 1600) PowerMax = 1600;

	fPowerMax += (PowerMax - fPowerMax)/50;

	PowerMax16 = fPowerMax;

	PowerMax = fPowerMax*500;//1000; 1000*(1500(max)/1850) = 813

}




