
#include "hfa.h"
#include "IQmathLib.h"

void SpeedAndAngleL();
#pragma CODE_SECTION(SpeedAndAngleL,"ramfuncs")

int16 SpeedLz=0;
int16 SpeedL=0;			// скорость левого колеса в об/мин
int16 SpeedLold=0;			// скорость левого колеса в об/мин
float FSpeedL=0;
int16 FinalSpeedL=0;			// скорость левого колеса в об/мин
int16 OldSpeedL=0;

Uint16 ElecAngleL=0;	// электрический угол левого колеса в ое с учетом пар полюсов

Uint32 PRDLAT_L=0;		// период сигнала ДС в ое

Uint16 ThetaL=0;		// Тета электрич угол с учетом скольжения

Uint16 FirstPosL=0,SecondPosL=0;	// Шаги QEP счетчика
int16 DeltaPosL=0;				// Дельта

int PosArrCountL=0;
float PosFL=0;

int KSpeed=50;

int SByDelta_L=0;

Uint16 SByPRD_L=0;

Uint16 SByPRD_32L=0;
Uint16 SByPRD_16L=0;

Uint16 PosL;

int CountForDeltaPosL=0;

extern float fOmegaL;

float fOldOmegaL=0;
int OmegaL=0;
int OldThetaL=0;
int DeltaThetaL=0;

void SpeedAndAngleL()
{
//int i=0; long Ls=0;


	//CheckState
	st.DriveDirL = EQep2Regs.QEPSTS.bit.QDF;

		PosL = EQep2Regs.QPOSCNT;

			FirstPosL = PosL;
			DeltaPosL = FirstPosL - SecondPosL;
			SecondPosL = PosL;

			if(st.DriveDirL == FORWARD)
				if(DeltaPosL < 0)
					DeltaPosL +=32400;

			if(st.DriveDirL == BACK)
				if(DeltaPosL > 30000)
					DeltaPosL =32400 - DeltaPosL;

			// 720 импульсов - 1 оборот секунду (60 об/мин)
			// за 1 такт ШИМ придет 720/1500 = 0.48 импульса
			// 60/0.48 = 125(коэффициент перевода количества импульсов за 1 такт в об/мин)
			PosFL += ((float)DeltaPosL - PosFL)/(float)KSpeed;
			SByDelta_L = (int)(PosFL*125.0);


		// число зубцов * 4 / число пар полюсов
		// (180*4)/3 = 240
		// полученная пила уже с учетом пар полюсов
		// т.е. для ХХ это угол частоты статора
		ElecAngleL = _IQ15div(PosL,240);
		ElecAngleL &= 0x7FFF;

		//if(TestSlip >= 240)
		//	TestSlip -=240;

		//240/(2*M_PI) = 38.198
		ThetaL = _IQ15div(PosL+ThetaSlipL*38.198,240);
		ThetaL &= 0x7FFF;

		PosArrCountL++;


/*********************************************************************************/

		// Производная от Тета по времени, пропущенная через аппериодический фильтр
		// fOmega - чистые радианы (СИ)
		//		      ___________
		//		     |     p     |
		// Theta---->|  -------  |-----> omega
		//		     |  T*p + 1	 |
		//		     |___________|
		//

		DeltaThetaL = ThetaL - OldThetaL;
		OldThetaL = ThetaL;


		DeltaThetaL &= 0x7FFF;

		if(GS.STATE.bit.DriveDirL == BACK)
			DeltaThetaL -= 0x7FFF;

		// 32768/6.283 = 5215.2
		fOmegaL += (DeltaThetaL/(dt*5215.2) - fOmegaL)/25.0;

		OmegaL = fOmegaL;

/*********************************************************************************/

		PRDLAT_L += EQep2Regs.QCPRDLAT;

		if(PosArrCountL == 16)
		{

			SByPRD_L =_IQ4div(390625,PRDLAT_L);

			PRDLAT_L=0;

			PosArrCountL = 0;
		}

		//if(SByDelta_L > 4000)

		if(GS.STATE.bit.DriveDirL == FORWARD)
		{
			if(SByDelta_L < 20)
				SpeedL = SByDelta_L;
			else
				SpeedL = SByPRD_L;
		}
		if(GS.STATE.bit.DriveDirL == BACK)
		{
			if(SByDelta_L > -20)
				SpeedL = SByDelta_L;
			else
				SpeedL = -SByPRD_L;
		}

		if(abs(SpeedL) > 4000)	//явно скачек
			SpeedL = SpeedLold;

		SpeedLold = SpeedL;

		if(abs(SpeedL) > koeff.K14)
		{
			SET_ERROR(f1.nU_L);
			ErrorResponse();
		}
/*
		ASpeed[Ispeed] = SpeedL;
		Ispeed++;

		if(Ispeed == 32) Ispeed=0;
		DAT2=0;
		for(i=0;i<32;i++)
		{
			Ls += ASpeed[i];
		}
		DAT2=1;

		FinalSpeedL = (int)(Ls / 32);
*/

/*
		if(SpeedL - FinalSpeedL > 5)
			FinalSpeedL +=5;
		else
		if(SpeedL - FinalSpeedL < -5)
			FinalSpeedL -=5;
		else
		FinalSpeedL = SpeedL;



		SByPRD_32L += EQep2Regs.QCPRDLAT;

		if(EQep2Regs.QEPSTS.bit.COEF)
		{
			SByPRD_32L += 0xFFFF;
			EQep2Regs.QEPSTS.all=0x8;
		}

		PosArrCountL++;

		if(PosArrCountL == 8)
		{

			if(EQep2Regs.QEPSTS.bit.UPEVNT)
			{

				SByPRD_16L += EQep2Regs.QCPRDLAT;

				if(EQep2Regs.QEPSTS.bit.COEF)
				{
					SByPRD_16L += 0xFFFF;
				}

				if(SpeedL < 20)
					SpeedL =_IQ3div(390625,SByPRD_16L);
				else
					SpeedL =_IQ3div(390625,(SByPRD_32L >> 3));

				SByPRD_16L = 0;

				EQep2Regs.QEPSTS.all=0x88;

			}
			else{
				SpeedL =_IQ3div(390625,SByPRD_16L + EQep2Regs.QCTMR);
			}

			SByPRD_32L = 0;

			PosArrCountL = 0;

		}
*/



}

void  QEP_InitL(void)
{

    #if (CPU_FRQ_150MHZ)
	  EQep2Regs.QUPRD=1500000;			// Unit Timer for 100Hz at 150 MHz SYSCLKOUT
	#endif
    #if (CPU_FRQ_100MHZ)
	  EQep2Regs.QUPRD=1000000;			// Unit Timer for 100Hz at 100 MHz SYSCLKOUT
	#endif

	EQep2Regs.QDECCTL.bit.QSRC=00;		// QEP quadrature count mode

	EQep2Regs.QEPCTL.bit.FREE_SOFT=0;
	EQep2Regs.QEPCTL.bit.PCRM=01;		// PCRM=00 mode - QPOSCNT reset on index event
	EQep2Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep2Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep2Regs.QPOSMAX=32400;
	//EQep2Regs.QPOSMAX=0x7FFF;
	EQep2Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	//EQep2Regs.QCAPCTL.bit.UPPS=5;   	// 1/32 for unit position
	EQep2Regs.QCAPCTL.bit.UPPS=2;   	// 1/1 for unit position
	EQep2Regs.QCAPCTL.bit.CCPS=7;		// 1/32 for CAP clock
	EQep2Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable

}


