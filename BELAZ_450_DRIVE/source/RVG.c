#include "hfa.h"

void RVG();
Uint32 calc_shift_saw(Uint32 count,Uint32 period,Uint16 angle);
interrupt void ecap4_isr(void);

#pragma CODE_SECTION(calc_shift_saw,"ramfuncs")
#pragma CODE_SECTION(RVG,"ramfuncs")
#pragma CODE_SECTION(ecap4_isr,"ramfuncs")


Uint32 rvg_cnt=0;
Uint16 synch_cnt=1000;
int16 freq_3_harm=0;

int16 Udz=0;
int16 UdzByDiz=0;
int16 UdzByDrive=0;

int16  dUd=0;
float  Summ_dUd=0;

Uint16 URvg=0;
Uint32 URvg_=0;

Uint16 phi_int=0;

Uint16 CTR_CAP4=0;
Uint16 CTR_CAP1=0;
Uint16 CTR_CAP2=0;

Uint16 CAP1_REG=0;

float phi=0;
float alpha=0;

Uint16 alpha16=0;

Uint32 PRD=0;
Uint32 HALF_PRD=0;
Uint32 DELTA=5000;

int32 fPRD=0;
int16 fPRD16=0;

int16 PRD16=0;

float fTestUd=0;
int16 TestUd=0;


Uint32 PRD1;
Uint32 PRD2;
Uint32 PRD3;
Uint32 PRD4;

int wtf=0;

int32 DeltaCAP=0;
int32 OldCAP=0;
int16 DeltaCAP16=0;
int16 OldCAP16=0;

Uint16 Cap1Cap1=0;
Uint16 Cap1Cap2=0;
Uint16 Cap1Cap3=0;
Uint16 Cap1Cap4=0;

Uint16 WrongSynchCount=0;

float fUd=0;
float fUgen=0;

int16 KpRVG16=0;
int16 SummRVG16=0;

int16 speedMax=0;

void RVG(void)
{

	PRD	 = ECap4Regs.CAP1;

	speedMax = GetMAX(abs(SpeedL),abs(SpeedR));

	// 150.000.000 / 120 √ц = 1250000
	if(PRD < 1250000)
	{
//TODO должна быть средн€€ скорость
//		if(RPMDiz < (abs(speedMax)*2.235))
//		{
//
//			Udz = F_(RPMDiz)/1.6;
//
//		}
//		else{
//
//			Udz = F_(abs(speedMax))*1.4;
//
//		}

		if(RPMDiz < (abs(speedMax)*1.946))
		{

			Udz = F_(RPMDiz)/1.6;

		}
		else{

			Udz = F_(abs(speedMax))*1.217;

		}

	if(!otf.rsrv1)
	{

		OldCAP = PRD;
		SET(otf.rsrv1);

		ECap1Regs.CAP1 = PRD;
		ECap1Regs.CAP2 = 0;

		ECap2Regs.CAP1 = PRD;
		ECap2Regs.CAP2 = 0;

	}

	DeltaCAP = PRD - OldCAP;

	CAP1_REG = (PRD/100);

	DeltaCAP16 = DeltaCAP/100;

	fPRD += ((int32)PRD - (int32)fPRD)/10;

	fPRD16 = fPRD/100;

	if(abs(DeltaCAP16) > 2000)
	{
			PRD = OldCAP;
			UNSET(otf.rsrv1);
			WrongSynchCount++;

			ECap1Regs.CAP1 = PRD;
			ECap1Regs.CAP2 = URvg_;

			ECap2Regs.CAP1 = PRD;
			ECap2Regs.CAP2 = URvg_;
	}

	OldCAP = PRD;

	//wtf++;
	freq_3_harm = 150000000/fPRD;
	phi_int = 180 -(F_(freq_3_harm)*0.15 + 18);


//DAT5=1;
	HALF_PRD = PRD >> 1;

//REG

	 if(Debug == 5)
	 {
		 	Udz = Slider.s1; /* 0 ... 960*/
		 	//ChopReg = Slider.s3;
	 }

	// dUd = Udz - TestUd;

	// if(Debug == 4)
	//	 Udz =  Slider.s4;

	 if(st.ExImp)
	 {

		 fUd += (Ud - fUd)/koeff.K21;

	 	 fUgen += (Ugen - fUgen)/15.0;

	 	 MinMaxLimitInt(500,940,&Udz);

	 	 if(Ud>(Ugen-koeff.K22))
		 dUd = Udz - Ugen;
	 	 else
		 dUd = Udz - Ud;

	 	 Summ_dUd += F_(dUd*koeff.Ki_Rvg)/10000.0;

	 	 if(Summ_dUd > 170) Summ_dUd = 170;
	 	 if(Summ_dUd < 1) Summ_dUd = 1;

	 	KpRVG16 = F_(dUd*koeff.Kp_Rvg)/100.0;
	 	SummRVG16 = Summ_dUd;

	 	 alpha = F_(dUd*koeff.Kp_Rvg)/100.0 + Summ_dUd;
	 }
	 else
	 {
		 Summ_dUd = 0;
	 }

	 if(Debug == 6)
	 {
		 	alpha = Slider.s1; /* 0 ... 180*/
		 	//phi_int = Slider.s2;
		 	//ChopReg = Slider.s3;
	 }

	 if(alpha < 5) alpha = 5;
	 if(alpha > 180) alpha = 180;

	 alpha16 = alpha;

	 URvg_ = HALF_PRD*((alpha/180.0));

	 PRD16 = HALF_PRD/46;

	}
	else
		{

			UNSET(otf.rsrv1);

			/*ECap1Regs.CAP1 = PRD;
			ECap1Regs.CAP2 = 0;

			ECap1Regs.CAP3 = PRD;
			ECap1Regs.CAP4 = 0;*/
		}
}

int TestC=0;
interrupt void ecap4_isr(void){

		SET(hb.CapIsr);

		ECap1Regs.CAP3 = PRD;
		ECap1Regs.CAP4 = PRD - URvg_;

		ECap2Regs.CAP3 = PRD;
		ECap2Regs.CAP4 = PRD - URvg_;

		ECap1Regs.TSCTR = calc_shift_saw(ECap4Regs.TSCTR,(Uint32)PRD,phi_int);
		ECap2Regs.TSCTR = calc_shift_saw(ECap1Regs.TSCTR,(Uint32)PRD,180);

	   ECap4Regs.ECCLR.bit.CEVT1 = 1;
	   ECap4Regs.ECCLR.bit.INT = 1;
	   ECap4Regs.ECCTL2.bit.REARM = 1;

	   // Acknowledge this interrupt to receive more interrupts from group 4
	   PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

//DAT5=0;
}

Uint32 calc_shift_saw(Uint32 count,Uint32 period,Uint16 angle)
{

        if(count>period*((angle)/360.0))
        return(count - (float)period*((float)angle/(float)360.0));
        else
        return(count + (float)period*(1-((float)angle/(float)360.0)));
}


















