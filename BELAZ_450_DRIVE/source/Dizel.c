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

int fTestStabSpeed=0;

void DizelOutPowerMax(){

	RPMDiz = freq_3_harm*5;

	    if(RPMDiz <= 1200)  PowerMax = 100;
		if(RPMDiz > 1200 && RPMDiz <= 1350) DisState=0;
		if(RPMDiz > 1350) DisState=1;

		if(fPowerMAX == 1)
		{
			if(RPMDiz < 1600)
				PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState];
			else
				PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState]+100;
		}
		if(fPowerMAX == 2)
			PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState];
		if(fPowerMAX == 0)
			PowerMax = RPMDiz*KDIS[DisState] + BDIS[DisState] - 100;

		if(!fTestStabSpeed)
		SumPower = PowerL16 + PowerR16;

		if(SumPower < 1280) DisState = 0;
		else DisState = 1;

		zRPMDiz = ((float)(SumPower - BDIS[DisState]))/KDIS[DisState];

		if(zRPMDiz < 1250 ) zRPMDiz = 1250;
		if(zRPMDiz > 1900 ) zRPMDiz = 1900;



	if(PowerMax < 100) PowerMax = 100;
	if(PowerMax > 1700) PowerMax = 1700;

	fPowerMax += (PowerMax - fPowerMax)/50;

	PowerMax16 = fPowerMax;

	PowerMax = fPowerMax*500;//1000; 1000*(1500(max)/1850) = 813

}




