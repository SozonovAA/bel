#include "hfa.h"

void SpeedAndAngleR();
#pragma CODE_SECTION(SpeedAndAngleR,"ramfuncs")

int16 SpeedRz=0;
int16 SpeedR=0;			// скорость левого колеса в об/мин
float FSpeedR=0;
int16 FinalSpeedR=0;			// скорость левого колеса в об/мин
int16 OldSpeedR=0;

Uint16 ElecAngleR=0;	// электрический угол левого колеса в ое с учетом пар полюсов

Uint32 PRDLAT_R=0;		// период сигнала ДС в ое

Uint16 ThetaR=0;		// Тета электрич угол с учетом скольжения


int PosArrCountR=0;

int SByDelta_R=0;

Uint16 SByPRD_R=0;

Uint16 SByPRD_32R=0;
Uint16 SByPRD_16R=0;

Uint16 PosR;
float PosFR=0;

int CountForDeltaPosR=0;

float fOmegaR=0;
float fOldOmegaR=0;
int OmegaR=0;
int OldThetaR=0;
int DeltaThetaR=0;

Uint16 FirstPosR=0,SecondPosR=0;	// Шаги QEP счетчика
int16 DeltaPosR=0;				// Дельта

void SpeedAndAngleR()
{
//int i=0; long Ls=0;


	//CheckState
	//Где-то косяк в монтаже, сделал крест в разъеме на панели.
	st.DriveDirR = EQep1Regs.QEPSTS.bit.QDF;

		PosR = EQep1Regs.QPOSCNT;

			FirstPosR = PosR;
			DeltaPosR = FirstPosR - SecondPosR;
			SecondPosR = PosR;

			if(st.DriveDirR == FORWARD)
				if(DeltaPosR < 0)
					DeltaPosR +=32400;

			if(st.DriveDirR == BACK)
				if(DeltaPosR > 30000)
					DeltaPosR =32400 - DeltaPosR;

			// 720 импульсов - 1 оборот секунду (60 об/мин)
			// за 1 такт ШИМ придет 720/1500 = 0.48 импульса
			// 60/0.48 = 125(коэффициент перевода количества импульсов за 1 такт в об/мин)
			PosFR += ((float)DeltaPosR - PosFR)/50.0;
			SByDelta_R = (int)(PosFR*125.0);


		// число зубцов * 4 / число пар полюсов
		// (180*4)/3 = 240
		// полученная пила уже с учетом пар полюсов
		// т.е. для ХХ это угол частоты статора
		ElecAngleR = _IQ15div(PosR,240);
		ElecAngleR &= 0x7FFF;

		//if(TestSlip >= 240)
		//	TestSlip -=240;

		//240/(2*M_PI) = 38.198
		ThetaR = _IQ15div(PosR+ThetaSlipR*38.198,240);
		ThetaR &= 0x7FFF;

		PosArrCountR++;


/*********************************************************************************/

		// Производная от Тета по времени, пропущенная через аппериодический фильтр
		// fOmega - чистые радианы (СИ)
		//		      ___________
		//		     |     p     |
		// Theta---->|  -------  |-----> omega
		//		     |  T*p + 1	 |
		//		     |___________|
		//

		DeltaThetaR = ThetaR - OldThetaR;
		OldThetaR = ThetaR;


		DeltaThetaR &= 0x7FFF;

		if(GS.STATE.bit.DriveDirR == BACK)
			DeltaThetaR -= 0x7FFF;

		// 32768/6.283 = 5215.2
		fOmegaR += (DeltaThetaR/(dt*5215.2) - fOmegaR)/25.0;

		OmegaR = fOmegaR;

/*********************************************************************************/

		PRDLAT_R += EQep1Regs.QCPRDLAT;

		if(PosArrCountR == 16)
		{

			SByPRD_R =_IQ4div(390625,PRDLAT_R);

			PRDLAT_R=0;

			PosArrCountR = 0;
		}

		if(GS.STATE.bit.DriveDirR == FORWARD)
		{
			if(SByDelta_R < 10)
				SpeedR = SByDelta_R;
			else
				SpeedR = SByPRD_R;
		}
		if(GS.STATE.bit.DriveDirR == BACK)
		{
			if(SByDelta_R > -10)
				SpeedR = SByDelta_R;
			else
				SpeedR = -SByPRD_R;
		}

		if(abs(SpeedR) > koeff.K14)
		{
			SET_ERROR(f1.nU_R);
			ErrorResponse();
		}

}

void  QEP_InitR(void)
{

    #if (CPU_FRQ_150MHZ)
	  EQep1Regs.QUPRD=1500000;			// Unit Timer for 100Hz at 150 MHz SYSCLKOUT
	#endif
    #if (CPU_FRQ_100MHZ)
	  EQep1Regs.QUPRD=1000000;			// Unit Timer for 100Hz at 100 MHz SYSCLKOUT
	#endif

	EQep1Regs.QDECCTL.bit.QSRC=00;		// QEP quadrature count mode

	EQep1Regs.QEPCTL.bit.FREE_SOFT=0;
	EQep1Regs.QEPCTL.bit.PCRM=01;		// PCRM=00 mode - QPOSCNT reset on index event
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep1Regs.QPOSMAX=32400;
	//EQep2Regs.QPOSMAX=0x7FFF;
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	//EQep2Regs.QCAPCTL.bit.UPPS=5;   	// 1/32 for unit position
	EQep1Regs.QCAPCTL.bit.UPPS=2;   	// 1/1 for unit position
	EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/32 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable

}


