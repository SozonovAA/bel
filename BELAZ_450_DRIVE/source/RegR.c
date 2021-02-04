#ifndef FLASH_RUN
#define MATLAB
#endif

#ifndef MATLAB
#include "hfa.h"
#else
#include "BELAZ_450_DRIVE\include\REGs.h"
#endif

#ifdef MATLAB
int SpeedRz=0;
int SpeedR=0;			// скорость левого колеса в об/мин
unsigned int ThetaR=0;		// Тета электрич угол с учетом скольжения
float ElectricAngleR=0;
#endif

void LookerR();
void RegR();
void ELCalcR();
void ELRegR();

#ifndef MATLAB
#pragma CODE_SECTION(LookerR,"ramfuncs")
#pragma CODE_SECTION(RegR,"ramfuncs")
#pragma CODE_SECTION(ELCalcR,"ramfuncs")
#pragma CODE_SECTION(ELRegR,"ramfuncs")
#endif

int URsAlpha_R=0;
int URsBeta_R=0;
int ULsAlpha_R=0;
int ULsBeta_R=0;


//REFT MOTOR
int IaR=0;
int IbR=0;
int IcR=0;

int IAlphaR=0;
int IBetaR=0;

int IdzR=0;
float IdzRx=0;
int IdR=0;
float SIdR=0;
int DeltaIdOldR=0;
int DeltaIdR=0;
int UUdR=0;

int IqzR=0;
int IqR=0;
float SIqR=0;
int DeltaIqOldR=0;
int DeltaIqR=0;
int UUqR=0;


int UdSIR=0;
int UqSIR=0;

float fE_MaxR=0;
int E_MaxR=0;
int E_LineR=0;
int E_ampR=0;    		// Амплитуда фазного ЭДС после фильтра (Вольты)
float fE_ampR=0;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
int UAlphaSIR=0;		// Мгновенное значение напряжения по оси альфа (Вольты)
int UBetaSIR=0;		// Мгновенное значение напряжения по оси бета (Вольты)
int DeltaIAlphaR=0;
int DeltaIBetaR=0;
int OldIAlphaR=0;
int OldIBetaR=0;
int EAlphaInstR=0;
int EBetaInstR=0;

int Ez_ampR=0;
int SER=0;

int IqRCurLim=0;
int IqRMAX=0;
int fIqRMAX=0;

int UAlphaR=0;
int UBetaR=0;

int UUAR=0;
int UUBR=0;
int UUCR=0;

//int ChopReg=0;

float fIdRf=0;
int iIdRf=0;

int iSlipR=0;

float DeltaOmegaSlipR,ThetaSlipR=0;


int RTheta;

float fThetaR=0;

void SpeedRegR();

#ifndef MATLAB
#pragma CODE_SECTION(SpeedRegR,"ramfuncs")
#endif

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

long PowerR=0;
int PowerR16=0;

int PowerBrakeMax=-1000;

int iffR=0;

float IqSummInBrakeR=0;
float kBrake=5;

void CalcDeltaIdR();

#ifndef MATLAB
#pragma CODE_SECTION(CalcDeltaIdR,"ramfuncs")
#endif

void RegRToZero();

#ifndef MATLAB
#pragma CODE_SECTION(RegRToZero,"ramfuncs")
#endif

int UUqRMAX;
float kIqR=1.0;

void RegRToZero()
{
	sdER=0;
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
#ifdef MATLAB
	Udz = 940;
#endif

	UmR = GetHypByLegs(UUdR,UUqR);

	if(UUqR>17400) UUqR=17400;

	UUqRMAX = GetCatByHypNLeg(UUqR,17500);

	if(UmR >= 17500)
	UmR = 17500;

	fUmR += (UmR - fUmR)/25;

	fE_MaxR += (((float)(Udz)*1.10/2.0) - fE_MaxR)/koeff.K17;

	E_MaxR = fE_MaxR;
	E_LineR = (float)(abs(SpeedR))*0.0686*koeff.K15;

	if(E_LineR < 50) E_LineR=50;
	if(E_MaxR < 200) E_MaxR=200;

	if(E_LineR<E_MaxR)

		dER = E_LineR - E_ampR;

	else
		dER = E_MaxR - E_ampR;

		//MinMaxLimitInt(-540,540,&dER);

		sdER += ((float)(dER)/1000.0)*(float)(koeff.KiE);

		if(sdER > 540) sdER=540;
		if(sdER < -540) sdER=-540;

		IdzR = (long)(dER)*koeff.KpE/10.0 + sdER;

	MinMaxLimitInt(0,100,&DeltaIdzR);

}

float fOmegaR=0;


void CrossComR();
#ifndef MATLAB
#pragma CODE_SECTION(CrossComR,"ramfuncs")
#endif

void CrossComR()
{

	UkdR = fOmegaR*IqzR*(MPR.RS + (MPR.LM*MPR.RR)/(MPR.LM+MPR.RR));

	UkqR = -fOmegaR*IdzR*(MPR.LM + MPR.RS);

	ConvertVParamToRU(UkdR);
	ConvertVParamToRU(UkdR);

}


void SpeedRegR()
{
#ifdef MATLAB
	cmd.DNR = 1;
#endif
	DeltaSpeedR = (SpeedRz - IqzR)/5;

	SpeedRz1 += (float)(DeltaSpeedR)*((float)(koeff.K7)/2500.0);

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

			if(PowerR < PowerBrakeMax) IqSummInBrakeR += 0.1*kBrake;
			else
				if(IqSummInBrakeR > -(Brake-13)*20)
					IqSummInBrakeR -= 0.1*kBrake;

			IqzR = IqSummInBrakeR;

			SpeedRz1 = SpeedR;
		}
		else
			{
				IqzR = (float)(DeltaSpeedR1*koeff.K10)/4.0;
				IqSummInBrakeR = IqzR;
			}
	}
	if(cmd.DNR == REVERSE)
	{
		if(Brake > 13 && SpeedR < -40)
		{
			IqzR = (Brake-13)*20;
			SpeedRz1 = SpeedR;
		}
		else
			IqzR = (float)(DeltaSpeedR1*koeff.K10)/4.0;
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
	DeltaOmegaSlipR = (MPR.LM*(float)(IqR)*((float)(koeff.K9)/10.0))/(fIdRf*MPR.TR + 0.001);

	//  rad
	ThetaSlipR += DeltaOmegaSlipR*dt;

	//ThetaSlipR += ((float)(SpeedR*koeff.K9)/1000.0)*dt;

	RadianLimit(&ThetaSlipR);

	// 240/2*M_PI = 38.198
	//ThetaSlipR *= 38.198;

	iIdRf = fIdRf;

	//HeatWinding(&TTheta);

}

float sSpeedRz=0.0;
float fIqurRimR=0;
void RegR(){

#ifdef MATLAB
	PowerMax=800000;
#endif

#ifndef MATLAB
	DizelOutPowerMax();
		#endif

	LookerR();
#ifndef MATLAB
	SpeedAndAngleR();

	//32400/2*M_PI = 5156.62
	fThetaR = (float)(ThetaR)/5215.19;

#else
	fThetaR = ThetaSlipR + ElectricAngleR;
	RadianLimit(&fThetaR);
#endif

	CalcDeltaIdR();

	/*
	 * Debug
	 * 0	Штатный режим
	 * 1
	 * 2	проверка импульсов
	 * 3	регулятор тока
	 * 4	L экскаваторная характеристика, R - белазовская
	 * 5
	 * 6	управление углом коммутации тиристоров.
	 * 7
	 * 8
	 * 9
	 */



	//Разрешение импульсов только для настольной отладки
	//st.ReftImp=1;
#ifndef MATLAB
	if(GS.STATE.bit.RightImp)
#endif
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
				sSpeedRz += (float)(koeff.K16)/100.0;
			else
				sSpeedRz -= (float)(koeff.K16)/100.0;

			SpeedRz = sSpeedRz;

			//ChopReg = Slider.s6;

		}

		if(Debug == 0)
		{

			IqRCurLim = abs(fIqRMAX);

			if(Drive < 13) Drive = 13;

#ifndef MATLAB
			if(cmd.DNR == DRIVE)
					SpeedRz = (Drive-13)*20;
			if(cmd.DNR == REVERSE)
					SpeedRz = -(Drive-13)*20;
#endif
		}

		Clark(IaR,IbR,IcR,&IAlphaR,&IBetaR);
		Park(IAlphaR,IBetaR,&IdR,&IqR,fThetaR);

// ##### IdReg bgn

		MinMaxLimitInt(5,900,&IdzR);

		DeltaIdR = IdzR - IdR;
		SIdR += (float)(DeltaIdR*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIdR);

		UUdR = (float)(DeltaIdR*koeff.Kp)/25.0 + SIdR + (DeltaIdR - DeltaIdOldR)*koeff.Kd;
		DeltaIdOldR = DeltaIdR;

// @@@@@ IdReg end

// ##### Считаем ток отсечки bgn

		//избегаем деление на 0
		if(UqSIR >= 0 && UqSIR < 10)
		UqSIR = 10;

		if(UqSIR < 0 && UqSIR > -10)
		UqSIR = -10;

		//if(PowerMax < 300000) PowerMax = 300000;
		//if(PowerMax > 1600000) PowerMax = 1600000;

		//IqRMAX = ((PowerMax >> 1) - (long)(UdSIR)*(long)(IdzR))/(long)(UqSIR)/1.4142; XZ!!!
		IqRMAX = (PowerMax*0.666 - (long)(UdSIR)*(long)(IdzR))/(long)(UqSIR);

		MinMaxLimitInt(-2000,2000,&IqRMAX);

		fIqRMAX += (IqRMAX - fIqRMAX)/koeff.KFiltIq;

		iffR = (fUmR - 12500)/63;
		MinMaxLimitInt(0,79,&iffR);

		UdSIR = (float)(ConvertVParamToSI(UUdR))/FourieK[iffR];
		UqSIR = (float)(ConvertVParamToSI(UUqR))/FourieK[iffR];

		PowerR = ((long)(UdSIR)*(long)(IdzR) + (long)(UqSIR)*(long)(IqzR))/666;

		PowerR = (float)(PowerR);

		PowerR16 = PowerR;

// @@@@@ Считаем ток отсечки end

// ##### IqReg bgn

		SpeedRegR();

		MinMaxLimitInt(-2000,abs(IqRCurLim),&IqzR);

		if(UUqR > UUqRMAX) kIqR = (float)UUqR/(float)17500;
		else kIqR = 1;

		IqzR*=kIqR;

		DeltaIqR = IqzR - IqR;
		SIqR += (float)(DeltaIqR*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIqR);

		UUqR = (float)(DeltaIqR*koeff.Kp)/25.0 + SIqR + (DeltaIqR - DeltaIqOldR)*koeff.Kd;
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

		InvPark(&IAlphaR,&IBetaR,IdzR,IqzR,fThetaR);
		InvClark(&Iaz,&Ibz,&Icz,IAlphaR,IBetaR);

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
			AlphaR	+= (float)(Slider.s5)/10000.0; /* -10 10*/
#ifndef MATLAB
			HandleReg(&UUAR,&UUBR,&UUCR,&AmplR,&AlphaR);
		#endif

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
#ifndef MATLAB
		EPwm1Regs.CMPB = UUAR;
		EPwm2Regs.CMPB = UUBR;
		EPwm6Regs.CMPA.half.CMPA = UUCR;
		#endif

	}
#ifndef MATLAB
	else
		RegRToZero();
		#endif


}


void ELCalcR(){

			UAlphaSIR = ConvertVParamToSI(UAlphaR);
			UBetaSIR  = ConvertVParamToSI(UBetaR);

			UAlphaSIR = (int)((float)(UAlphaSIR)/FourieK[iffR]);
			UBetaSIR = (int)((float)(UBetaSIR)/FourieK[iffR]);

			DeltaIAlphaR = IAlphaR - OldIAlphaR;
			DeltaIBetaR = IBetaR - OldIBetaR;

			URsAlpha_R = IAlphaR*MPR.RS;
			URsBeta_R = IBetaR*MPR.RS;

			ULsAlpha_R = (MPR.LS*DeltaIAlphaR)*1500;//dt;
			ULsBeta_R = (MPR.LS*DeltaIBetaR)*1500;//dt;

			EAlphaInstR = UAlphaSIR - URsAlpha_R - ULsAlpha_R;
			EBetaInstR = UBetaSIR - URsBeta_R - ULsBeta_R;

			//EAlphaInstR = UAlphaSIR - IAlphaR*MPR.RS - (MPR.LS*DeltaIAlphaR)/dt;
			//EBetaInstR = UBetaSIR - IBetaR*MPR.RS - (MPR.LS*DeltaIBetaR)/dt;

			OldIAlphaR = IAlphaR;
			OldIBetaR = IBetaR;

			fE_ampR += (float)((GetHypByLegs(EAlphaInstR,EBetaInstR) - fE_ampR))/(float)(koeff.KFiltE);

			//fE_ampR += (float)((GetHypByLegs(UdSIR,UqSIR) - fE_ampR))/(float)(koeff.KFiltE);

			E_ampR = fE_ampR;

}



















