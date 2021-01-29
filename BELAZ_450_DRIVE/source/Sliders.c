/*
 * Sliders.c
 *
 *  Created on: 16.03.2018
 *      Author: smirnov_as
 */

#define SLIDER_RANGE_MEMORY		0x1BFE00
#define NUM_OF_SLIDERS			12

#include "hfa.h"

int *SlidersRangePtr;
int *SlidersStructPtr;

void SlidersMem();

#pragma CODE_SECTION(SlidersMem,"ramfuncs")

Uint16 OldDebug=0;

extern float alpha;

void SlidersMem(){

	int i;

	SlidersStructPtr = &Slider.MAX1;

	//if(Debug > 20) Debug = 20;

	if(Debug - OldDebug)
		{

			if(ANY_IMP)
				Debug = OldDebug;

			UNSET(hb.InitSliderRange);

		}

	OldDebug = Debug;

	if(!hb.InitSliderRange)
	{

		for(i = 0; i < NUM_OF_SLIDERS; i++)
		{

			SlidersRangePtr = (void *)(SLIDER_RANGE_MEMORY + Debug*NUM_OF_SLIDERS + i);

			*SlidersStructPtr++ = *SlidersRangePtr;

			SET(hb.InitSliderRange);

		}
	}

	if(Slider.SaveRange)
	{

		SlidersStructPtr = &Slider.MAX1;

		for(i = 0; i < NUM_OF_SLIDERS; i++)
		{
			SlidersRangePtr = (void *)(SLIDER_RANGE_MEMORY + Debug*NUM_OF_SLIDERS + i);

			*SlidersRangePtr = *SlidersStructPtr++;
		}

		UNSET(Slider.SaveRange);
	}

	switch(Debug)
	{

	case 0:
		Slider.addr1 = 0;
		Slider.addr2 = 0;
		Slider.addr3 = 0;
		Slider.addr4 = 0;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 1:
		Slider.addr1 = 0;
		Slider.addr2 = 0;
		Slider.addr3 = 0;
		Slider.addr4 = 0;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 2:
		Slider.addr1 = (Uint16)&UUAL;
		Slider.addr2 = (Uint16)&UUBL;
		Slider.addr3 = (Uint16)&ChopReg;
		Slider.addr4 = (Uint16)&UUAR;
		Slider.addr5 = (Uint16)&UUBR;
		Slider.addr6 = (Uint16)0;
	break;

	case 3:
		Slider.addr1 = (Uint16)&IdzL;
		Slider.addr2 = (Uint16)0;
		Slider.addr3 = (Uint16)&ChopReg;
		Slider.addr4 = (Uint16)&IdzR;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 4:
		Slider.addr1 = (Uint16)&IqLCurLim;
		Slider.addr2 = (Uint16)&SpeedLz;
		Slider.addr3 = (Uint16)0;
		Slider.addr4 = (Uint16)&IqRCurLim;
		Slider.addr5 = (Uint16)&SpeedRz;
		Slider.addr6 = (Uint16)&ChopReg;
	break;

	case 5:
		Slider.addr1 = (Uint16)&Udz;
		Slider.addr2 = 0;
		Slider.addr3 = (Uint16)&ChopReg;
		Slider.addr4 = 0;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 6:
		Slider.addr1 = (Uint16)&alpha;
		Slider.addr2 = (Uint16)&phi_int;
		Slider.addr3 = (Uint16)&ChopReg;
		Slider.addr4 = 0;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 7:
		Slider.addr1 = 0;
		Slider.addr2 = 0;
		Slider.addr3 = 0;
		Slider.addr4 = 0;
		Slider.addr5 = 0;
		Slider.addr6 = 0;
	break;

	case 9:
		Slider.addr1 = (Uint16)&AmplL;
		Slider.addr2 = (Uint16)&AlphaL;
		Slider.addr3 = 0;
		Slider.addr4 = (Uint16)&AmplR;
		Slider.addr5 = (Uint16)&AlphaR;
		Slider.addr6 = 0;
	break;


	}


}
