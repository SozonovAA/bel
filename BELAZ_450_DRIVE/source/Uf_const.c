#include "hfa.h"

void Uf_Const();
void HandleReg(int16 *A,int16 *B,int16 *C,int *Ampl, float *Alpha);

#pragma CODE_SECTION(Uf_Const,"ramfuncs")
#pragma CODE_SECTION(HandleReg,"ramfuncs")

int UDSI=0;

float Uam=0;
float UamPWM=0;
float OmegaT=0;
float dOmega=0;
float Freq=0;
float Freqz=0;
float LimFreq=0;

int iOmegaT=0;

int16 UZeroL=0;
int16 UAXL=0;

void Uf_Const()
{

		if(Slider.s1 > 25) Slider.s1 = 25;
		if(Slider.s1 < 0)  Slider.s1 = 0;

		OmegaT += dOmega;			// Угол синуса

		RadianLimit(&OmegaT);		// Ограничение диапазона

		UUAL = UamPWM*sin(OmegaT);
		UUBL = UamPWM*sin(OmegaT - _2PIdiv3);
		UUCL = UamPWM*sin(OmegaT - _4PIdiv3);

}

int16 AlphaInt=0;

void HandleReg(int16 *A,int16 *B,int16 *C,int *Ampl, float *Alpha){

	RadianLimit(Alpha);

	AlphaInt = *Alpha*1000;

	*A = (*Ampl)*sin(*Alpha );
	*B = (*Ampl)*sin(*Alpha - _2PIdiv3);
	*C = (*Ampl)*sin(*Alpha - _4PIdiv3);

}






























