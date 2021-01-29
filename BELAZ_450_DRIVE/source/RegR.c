#include "hfa.h"

void LookerR();
void RegR();
void ELCalcR();
void ELRegR();

#pragma CODE_SECTION(LookerR,"ramfuncs")
#pragma CODE_SECTION(RegR,"ramfuncs")
#pragma CODE_SECTION(ELCalcR,"ramfuncs")
#pragma CODE_SECTION(ELRegR,"ramfuncs")

//REFT MOTOR
int16 IaR=0;
int16 IbR=0;
int16 IcR=0;

int16 IAlphaR=0;
int16 IBetaR=0;

int16 IdzR=0;
float IdzRx=0;
int16 IdR=0;
float SIdR=0;
int16 DeltaIdOldR=0;
int16 DeltaIdR=0;
int16 UUdR=0;

int16 IqzR=0;
int16 IqR=0;
float SIqR=0;
int16 DeltaIqOldR=0;
int16 DeltaIqR=0;
int16 UUqR=0;


int16 UdSIR=0;
int16 UqSIR=0;

float fE_MaxR=0;
int16 E_MaxR=0;
int16 E_LineR=0;
int16 E_ampR=0;    		// ��������� ������� ��� ����� ������� (������)
float fE_ampR=0;    	// ��������� ������� ��� �� ������� (������)
int16 UAlphaSIR=0;		// ���������� �������� ���������� �� ��� ����� (������)
int16 UBetaSIR=0;		// ���������� �������� ���������� �� ��� ���� (������)
int16 DeltaIAlphaR=0;
int16 DeltaIBetaR=0;
int16 OldIAlphaR=0;
int16 OldIBetaR=0;
int16 EAlphaInstR=0;
int16 EBetaInstR=0;

int16 Ez_ampR=0;
int16 SER=0;

int16 IqRCurLim=0;
int16 IqRMAX=0;
int16 fIqRMAX=0;

int16 UAlphaR=0;
int16 UBetaR=0;

int16 UUAR=0;
int16 UUBR=0;
int16 UUCR=0;

//int16 ChopReg=0;

float fIdRf=0;
int iIdRf=0;

int16 iSlipR=0;

float DeltaOmegaSlipR,ThetaSlipR=0;


int16 RTheta;

float fThetaR=0;

void SpeedRegR();

#pragma CODE_SECTION(SpeedRegR,"ramfuncs")

int DeltaSpeedR=0;

int UUqzR=0;
int fUmR=0;
int UmR=0;
int DeltaIdzR=0;
float DeltaIdzRx=0;

int dUUqR=0;
float sdUUqR=0;

int UkdR=0;
int UkqR=0;

int 	AmplR=0;
float 	AlphaR=0;

float AFSpeedzR=0;
int   AFSpeedzR16=0;

float SpeedRz1=0;
int SpeedRz1_16=0;
int DeltaSpeedR1=0;

int dER=0;
float sdER=0;

int32 PowerR=0;
int16 PowerR16=0;

int iffR=0;

void CalcDeltaIdR();

#pragma CODE_SECTION(CalcDeltaIdR,"ramfuncs")

void RegRToZero();

#pragma CODE_SECTION(RegRToZero,"ramfuncs")

void RegRToZero()
{

	fUmR=0;
	sdUUqR=0;
	SIdR=0;
	SIqR=0;
	DeltaIdzR=0;
	UUAR=0;
	UUBR=0;
	UUCR=0;

	IdzR=0;
	IqzR=0;

	DeltaSpeedR=0;
	SpeedRz1=0;
	DeltaSpeedR1=0;
	SpeedRz=0;
}

void CalcDeltaIdR()
{


	UmR = GetHypByLegs(UUdR,UUqR);

	if(UmR >= 17500)
	UmR = 17500;

	fUmR += (UmR - fUmR)/25;

	fE_MaxR += ((F_(Udz)*1.15/2.0) - fE_MaxR)/koeff.K17;

	E_MaxR = fE_MaxR;
	E_LineR = F_(abs(SpeedR))*0.0686*koeff.K15;

	if(E_LineR < 50) E_LineR=50;
	if(E_MaxR < 200) E_MaxR=200;

	if(E_LineR<E_MaxR)

		dER = E_LineR - E_ampR;

	else
		dER = E_MaxR - E_ampR;

		//MinMaxLimitInt(-540,540,&dER);

		sdER += (F_(dER)/1000.0)*F_(koeff.KiE);

		//if(sdER > 540) sdER=540;
		//if(sdER < -540) sdER=-540;

		IdzR = L_(dER)*koeff.KpE/10.0 + sdER;

	MinMaxLimitInt(0,100,&DeltaIdzR);

}

extern float fOmegaR;



void CrossComR();

#pragma CODE_SECTION(CrossComR,"ramfuncs")

void CrossComR()
{

	UkdR = fOmegaR*IqzR*(MPR.RS + (MPR.LM*MPR.RR)/(MPR.LM+MPR.RR));

	UkqR = -fOmegaR*IdzR*(MPR.LM + MPR.RS);

	ConvertVParamToRU(UkdR);
	ConvertVParamToRU(UkdR);

}


void SpeedRegR()
{

	DeltaSpeedR = (SpeedRz - IqzR)/5;

	SpeedRz1 += F_(DeltaSpeedR)*(F_(koeff.K7)/2500.0);

	if(koeff.K18 > 2500)
		koeff.K18 = 2500;
	if(koeff.K18 < 100)
		koeff.K18 = 100;

	if(SpeedRz1 > koeff.K18)
		SpeedRz1 = koeff.K18; //SpeedLz;

	if(SpeedRz1 < -500)
		SpeedRz1 = -500; //SpeedRz;

	DeltaSpeedR1 = SpeedRz1 - SpeedR;

	if(Brake < 13) Brake = 13;

	if(cmd.DNR == DRIVE)
	{
		if(Brake > 13 && SpeedR > 40)
		{

			if(PowerR < -1000) IqzR++;
			else
				if(IqzR > -(Brake-13)*20)
			IqzR--;

			SpeedRz1 = SpeedR;
		}
		else
			IqzR = DeltaSpeedR1*koeff.K10;
	}
	if(cmd.DNR == REVERSE)
	{
		if(Brake > 13 && SpeedR < -40)
		{
			IqzR = (Brake-13)*20;
			SpeedRz1 = SpeedR;
		}
		else
			IqzR = DeltaSpeedR1*koeff.K10;
	}

	SpeedRz1_16 = SpeedRz1;

}

void LookerR(){

/*
		_____________
		|	RM		|
IdR	--->| ---------	|---------
		|  TR + 1	|	     |
		|___________|		 |
							 |
		________			 |		 _______
        |  RM  |             v       |  1  |
IqR --->| ---- |----------->DIV----->| --- |---------> (ThetaSlipR)
        |  TR  |                     |  p  |
        |______|                     |_____|
*/
	//DAT2=1;
	MagneticSaturation(IdR,&MPR.LM);
	//DAT2=0;

	//	A
	fIdRf += (((MPR.LM*IdR - fIdRf)/MPR.TR)*dt);
	//fIdRf = MPR.RM*IdzR;

	//	1/Sec	equal	rad/sec
	DeltaOmegaSlipR = (MPR.LM*F_(IqR)*(F_(koeff.K9)/10.0))/(fIdRf*MPR.TR + 0.001);

	//  rad
	ThetaSlipR += DeltaOmegaSlipR*dt;

	//ThetaSlipR += (F_(SpeedR*koeff.K9)/1000.0)*dt;

	RadianLimit(&ThetaSlipR);

	// 240/2*M_PI = 38.198
	//ThetaSlipR *= 38.198;

	iIdRf = fIdRf;

	//HeatWinding(&TTheta);

}

float sSpeedRz=0.0;
float fIqurRimR=0;
void RegR(){

	DizelOutPowerMax();

	LookerR();

	SpeedAndAngleR();

	//32400/2*M_PI = 5156.62
	fThetaR = F_(ThetaR)/5215.19;

	//fThetaR += F_(koeff.k10)/100000.0;

	CalcDeltaIdR();

	/*
	 * Debug
	 * 0	������� �����
	 * 1
	 * 2	�������� ���������
	 * 3	��������� ����
	 * 4	L ������������� ��������������, R - �����������
	 * 5
	 * 6	���������� ����� ���������� ����������.
	 * 7
	 * 8
	 * 9
	 */



	//���������� ��������� ������ ��� ���������� �������
	//st.ReftImp=1;

	if(GS.STATE.bit.RightImp)
	{

		if(Debug == 3)
		{
			IdzR = Slider.s4;
			IqzR = 0;
		}

		if(Debug == 4)
		{
			//IdzR = Slider.s1 + DeltaIdzR;

			IqRCurLim = Slider.s4;

			if(SpeedRz < Slider.s5)
				sSpeedRz += F_(koeff.K16)/100.0;
			else
				sSpeedRz -= F_(koeff.K16)/100.0;

			SpeedRz = sSpeedRz;

			//ChopReg = Slider.s6;

		}

		if(Debug == 0)
		{

			IqRCurLim = abs(fIqRMAX);

			if(Drive < 13) Drive = 13;

			if(cmd.DNR == DRIVE)
					SpeedRz = (Drive-13)*20;
			if(cmd.DNR == REVERSE)
					SpeedRz = -(Drive-13)*20;

		}

		Clark(IaR,IbR,IcR,&IAlphaR,&IBetaR);
		Park(IAlphaR,IBetaR,&IdR,&IqR,fThetaR);

// ##### IdReg bgn

		MinMaxLimitInt(5,900,&IdzR);

		DeltaIdR = IdzR - IdR;
		SIdR += F_(DeltaIdR*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIdR);

		UUdR = F_(DeltaIdR*koeff.Kp)/25.0 + SIdR + (DeltaIdR - DeltaIdOldR)*koeff.Kd;
		DeltaIdOldR = DeltaIdR;

// @@@@@ IdReg end

// ##### ������� ��� ������� bgn

		//�������� ������� �� 0
		if(UqSIR >= 0 && UqSIR < 10)
		UqSIR = 10;

		if(UqSIR < 0 && UqSIR > -10)
		UqSIR = -10;

		//if(PowerMax < 300000) PowerMax = 300000;
		//if(PowerMax > 1600000) PowerMax = 1600000;

		//IqRMAX = ((PowerMax >> 1) - L_(UdSIR)*L_(IdzR))/L_(UqSIR)/1.4142; XZ!!!
		IqRMAX = (PowerMax*0.666 - L_(UdSIR)*L_(IdzR))/L_(UqSIR);

		MinMaxLimitInt(-2000,2000,&IqRMAX);

		fIqRMAX += (IqRMAX - fIqRMAX)/koeff.KFiltIq;

		iffR = (fUmR - 12500)/63;
		MinMaxLimitInt(0,79,&iffR);

		UdSIR = F_(ConvertVParamToSI(UUdR))/FourieK[iffR];
		UqSIR = F_(ConvertVParamToSI(UUqR))/FourieK[iffR];

		PowerR = (L_(UdSIR)*L_(IdzR) + L_(UqSIR)*L_(IqzR))/666;

		PowerR = F_(PowerR);

		PowerR16 = PowerR;

// @@@@@ ������� ��� ������� end

// ##### IqReg bgn

		SpeedRegR();

		MinMaxLimitInt(-2000,abs(IqRCurLim),&IqzR);

		DeltaIqR = IqzR - IqR;
		SIqR += F_(DeltaIqR*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIqR);

		UUqR = F_(DeltaIqR*koeff.Kp)/25.0 + SIqR + (DeltaIqR - DeltaIqOldR)*koeff.Kd;
		DeltaIqOldR = DeltaIqR;

// @@@@@ IqReg end

	/*	if(koeff.K18)
		{

			CrossComR();

			UUdR += UkdR;
			UUqR += UkqR ;

		}*/


		UdSIR = ConvertVParamToSI(UUdR);
		UqSIR = ConvertVParamToSI(UUqR);

		InvPark(&UAlphaR,&UBetaR,UUdR,UUqR,fThetaR);
		InvClark(&UUAR,&UUBR,&UUCR,UAlphaR,UBetaR);

		ELCalcR();

		if(Debug == 2)
		{
			UUAR = Slider.s4;
			UUBR = Slider.s5;
			UUCR = /*Slider.s3;*/-UUAR - UUBR;

			//Udz = Slider.s6;

			//ChopReg = Slider.s3;
		}
/*
		UUAR=C;
		UUBR=C;
		UUCR=C;
*/
		if(Debug == 9)
		{

			AmplR 	= Slider.s4;
			AlphaR	+= F_(Slider.s5)/10000.0; /* -10 10*/

			HandleReg(&UUAR,&UUBR,&UUCR,&AmplR,&AlphaR);

		}

		UUAR += HALF_PWM_HEIGHT;
		UUBR += HALF_PWM_HEIGHT;
		UUCR += HALF_PWM_HEIGHT;

		if(UUAR <= MIN_PWM) UUAR = 0;
		if(UUAR >= MAX_PWM) UUAR = 25000;
		if(UUBR <= MIN_PWM) UUBR = 0;
		if(UUBR >= MAX_PWM) UUBR = 25000;
		if(UUCR <= MIN_PWM) UUCR = 0;
		if(UUCR >= MAX_PWM) UUCR = 25000;

		EPwm1Regs.CMPB = UUAR;
		EPwm2Regs.CMPB = UUBR;
		EPwm6Regs.CMPA.half.CMPA = UUCR;

	}
	else
		RegRToZero();


}

void ELCalcR(){
/*
			UAlphaSIR = ConvertVParamToSI(UAlphaR);
			UBetaSIR  = ConvertVParamToSI(UBetaR);

			UAlphaSIR = (int)(F_(UAlphaSIR)/FourieK[iffR]);
			UBetaSIR = (int)(F_(UBetaSIR)/FourieK[iffR]);

			DeltaIAlphaR = IAlphaR - OldIAlphaR;
			DeltaIBetaR = IBetaR - OldIBetaR;

			EAlphaInstR = UAlphaSIR - IAlphaR*MPR.RS - (MPR.LS*DeltaIAlphaR)/dt;
			EBetaInstR = UBetaSIR - IBetaR*MPR.RS - (MPR.LS*DeltaIBetaR)/dt;

			OldIAlphaR = IAlphaR;
			OldIBetaR = IBetaR;
*/
			fE_ampR += F_((GetHypByLegs(UdSIR,UqSIR) - fE_ampR))/F_(koeff.KFiltE);

			E_ampR = fE_ampR;

}


















