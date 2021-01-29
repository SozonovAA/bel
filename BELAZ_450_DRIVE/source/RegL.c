#include "hfa.h"

void LookerL();
void RegL();
void ELCalcL();

#pragma CODE_SECTION(LookerL,"ramfuncs")
#pragma CODE_SECTION(RegL,"ramfuncs")
#pragma CODE_SECTION(ELCalcL,"ramfuncs")

//LEFT MOTOR
int16 IaL=0;
int16 IbL=0;
int16 IcL=0;

int16 IAlphaL=0;
int16 IBetaL=0;

int16 IdzL=0;
float IdzLx=0;
int16 IdL=0;
float SIdL=0;
int16 DeltaIdOldL=0;
int16 DeltaIdL=0;
int16 UUdL=0;

int16 IqzL=0;
int16 IqL=0;
float SIqL=0;
int16 DeltaIqOldL=0;
int16 DeltaIqL=0;
int16 UUqL=0;


int16 UdSIL=0;
int16 UqSIL=0;

float fE_MaxL=0;
int16 E_MaxL=0;
int16 E_LineL=0;
int16 E_ampL=0;    		// ��������� ������� ��� ����� ������� (������)
float fE_ampL=0;    	// ��������� ������� ��� �� ������� (������)
int16 UAlphaSIL=0;		// ���������� �������� ���������� �� ��� ����� (������)
int16 UBetaSIL=0;		// ���������� �������� ���������� �� ��� ���� (������)
int16 DeltaIAlphaL=0;
int16 DeltaIBetaL=0;
int16 OldIAlphaL=0;
int16 OldIBetaL=0;
int16 EAlphaInstL=0;
int16 EBetaInstL=0;

int16 Ez_ampL=0;
int16 SEL=0;

int16 IqLCurLim=0;
int16 IqLMAX=0;
int16 fIqLMAX=0;

int16 UAlphaL=0;
int16 UBetaL=0;

int16 UUAL=0;
int16 UUBL=0;
int16 UUCL=0;

int16 ChopReg=0;

float fIdLf=0;
int iIdLf=0;

int16 iSlipL=0;

float DeltaOmegaSlipL,ThetaSlipL=0;


int16 LTheta;

int TCN=0;

int32 SQRT=0;
int16 SIN16=0;
int16 SIN16Count=0;

float fThetaL=0;

int C=0;

int16 Theta16=0;

void SpeedRegL();

#pragma CODE_SECTION(SpeedRegL,"ramfuncs")

int DeltaSpeedL=0;

int UUqzL=0;
int fUmL=0;
int UmL=0;
int DeltaIdzL=0;
float DeltaIdzLx=0;

int dEL=0;
float sdEL=0;

int UkdL=0;
int UkqL=0;

int32 PowerL=0;
int16 PowerL16=0;

void CalcDeltaIdL();
void RegLToZero();
void CrossComL();

#pragma CODE_SECTION(CalcDeltaIdL,"ramfuncs")
#pragma CODE_SECTION(RegLToZero,"ramfuncs")
#pragma CODE_SECTION(CrossComL,"ramfuncs")

float AFSpeedzL=0;
int   AFSpeedzL16=0;

float SpeedLz1=0;
int SpeedLz1_16=0;
int DeltaSpeedL1=0;

float SummDeltaSpeed=0;

Uint16 SpeedTestCount=0;
float sSpeedLz=0.0;
float fIqurLimL=0;

int Iaz=0;
int Ibz=0;
int Icz=0;

int IAlphaz=0;
int Ibetaz=0;

Uint16 ChopOpen=0;

Uint16 ThetaL6=0;
float  fThetaL6=0;

int SIN6=0;

extern float fOmegaL;

int iffL=0;

int ImL=0;
float XmL=0;

int IfRMSL=0;

int 	AmplL=0;
float 	AlphaL=0;

int16 PowerUvtr=0;
int16 PowerByGen=0;
int16 fPowerByGen=0;

int16 SummChopReg=0;
int16 dUdChop=0;

int16 IqLMAXBrake=0;
int16 ChopRegX=0;

void RegLToZero()
{

	fUmL=0;
	sdEL=0;
	SIdL=0;
	SIqL=0;
	DeltaIdzL=0;
	UUAL=0;
	UUBL=0;
	UUCL=0;
	SummDeltaSpeed=0;
	IdzL=0;
	IqzL=0;

	DeltaSpeedL=0;
	SpeedLz1=0;
	DeltaSpeedL1=0;
	SpeedLz=0;
}

void CalcDeltaIdL()
{

	UmL = GetHypByLegs(UUdL,UUqL);

	if(UmL >= 17500)
	UmL = 17500;

	fUmL += (UmL - fUmL)/25;

	fE_MaxL += ((F_(Udz)*1.15/2.0) - fE_MaxL)/koeff.K17;

	E_MaxL = fE_MaxL;
	E_LineL = F_(abs(SpeedL))*0.0686*koeff.K15;

	if(E_LineL < 50) E_LineL=50;
	if(E_MaxL < 200) E_MaxL=200;

	if(E_LineL<E_MaxL)

		dEL = E_LineL - E_ampL;

	else
		dEL = E_MaxL - E_ampL;

		//MinMaxLimitInt(-540,540,&dEL);

		sdEL += (F_(dEL)/1000.0)*F_(koeff.KiE);

		//if(sdEL > 540) sdEL=540;
		//if(sdEL < -540) sdEL=-540;

		IdzL = L_(dEL)*koeff.KpE/10.0 + sdEL;

	MinMaxLimitInt(0,100,&DeltaIdzL);

}

void CrossComL()
{

	UkdL = fOmegaL*IqzL*(MPL.LS + (MPL.LM*MPL.LR)/(MPL.LM+MPL.LR));

	UkqL = -fOmegaL*IdzL*(MPL.LM + MPL.LS);

	ConvertVParamToRU(UkdL);
	ConvertVParamToRU(UkqL);

}

void SpeedRegL()
{

	DeltaSpeedL = (SpeedLz - IqzL)/5;

	SpeedLz1 += F_(DeltaSpeedL)*(F_(koeff.K7)/2500.0);

	if(koeff.K18 > 2500)
		koeff.K18 = 2500;
	if(koeff.K18 < 100)
		koeff.K18 = 100;

	if(SpeedLz1 > koeff.K18)
		SpeedLz1 = koeff.K18; //SpeedLz;

	if(SpeedLz1 < -500)
		SpeedLz1 = -500; //SpeedRz;

	DeltaSpeedL1 = SpeedLz1 - SpeedL;

	if(Brake < 13) Brake = 13;

	if(cmd.DNR == DRIVE)
	{
		if(Brake > 13 && SpeedL > 40)
		{

			if(PowerL < -1000) IqzL++;
			else
				if(IqzL > -(Brake-13)*20)
			IqzL--;

			SpeedLz1 = SpeedL;
		}
		else
			IqzL = DeltaSpeedL1*koeff.K10;
	}
	if(cmd.DNR == REVERSE)
	{
		if(Brake > 13 && SpeedL < -40)
		{
			IqzL = (Brake-13)*20;
			SpeedLz1 = SpeedL;
		}
		else
			IqzL = DeltaSpeedL1*koeff.K10;
	}

	SpeedLz1_16 = SpeedLz1;

	if(Debug == 4)
	{

		DeltaSpeedL = SpeedLz - SpeedL;

		MinMaxLimitInt(-1500,1500,&DeltaSpeedL);

		SummDeltaSpeed += F_(DeltaSpeedL)/F_(koeff.K2_Rvg);

		MinMaxLimitFloat(-2000,2000,&SummDeltaSpeed);

		IqzL = DeltaSpeedL*koeff.K8 + SummDeltaSpeed;

	}
}

void LookerL(){

	TCN++;
/*
		_____________
		|	LM		|
IdL	--->| ---------	|---------
		|  TR + 1	|	     |
		|___________|		 |
							 |
		________			 |		 _______
        |  LM  |             v       |  1  |
IqL --->| ---- |----------->DIV----->| --- |---------> (ThetaSlipL)
        |  TR  |                     |  p  |
        |______|                     |_____|
*/
	//DAT2=1;
	MagneticSaturation(IdL,&MPL.LM);
	//DAT2=0;

	//	A
	fIdLf += (((MPL.LM*IdL - fIdLf)/MPL.TR)*dt);
	//fIdLf = MPL.LM*IdzL;

	//	1/Sec	equal	rad/sec
	DeltaOmegaSlipL = (MPL.LM*F_(IqL)*(F_(koeff.K9)/10.0))/(fIdLf*MPL.TR + 0.001);

	//  rad
	ThetaSlipL += DeltaOmegaSlipL*dt;

	//ThetaSlipL += (F_(SpeedL*koeff.K9)/1000.0)*dt;

	RadianLimit(&ThetaSlipL);

	// 240/2*M_PI = 38.198
	//ThetaSlipL *= 38.198;

	iIdLf = fIdLf;



	//HeatWinding(&TTheta);

}

void RegL(){

	DizelOutPowerMax();

	LookerL();

	SpeedTestCount++;

	SpeedAndAngleL();

	//32400/2*M_PI = 5156.62
	//32768/2*M_PI = 5215.19
	fThetaL = F_(ThetaL)/5215.19;
	
	ThetaL6 = (long)ThetaL*6L;
	ThetaL6 &= 0x7FFF;
	fThetaL6 = F_(ThetaL)/5215.19;

	CalcDeltaIdL();

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
	//st.LeftImp=1;

	if(GS.STATE.bit.LeftImp)
	{

		if(Debug == 3)
		{
			IdzL = Slider.s1;
			IqzL = 0;
			Udz =  Slider.s2;
		}

		if(Debug == 4)
		{

			IqLCurLim = Slider.s1;

			if(SpeedLz < Slider.s2)
				sSpeedLz += F_(koeff.K16)/100.0;
			else
				sSpeedLz -= F_(koeff.K16)/100.0;

			SpeedLz = sSpeedLz;

			Theta16 = fThetaL*100;

		}

		if(Debug == 0)
		{

			IqLCurLim = abs(fIqLMAX);

			if(Drive < 13) Drive = 13;

			if(cmd.DNR == DRIVE)
					SpeedLz = (Drive-13)*20;
			if(cmd.DNR == REVERSE)
					SpeedLz = -(Drive-13)*20;

		}

		Clark(IaL,IbL,IcL,&IAlphaL,&IBetaL);
		Park(IAlphaL,IBetaL,&IdL,&IqL,fThetaL);

// ##### IdReg bgn

		MinMaxLimitInt(5,900,&IdzL);

		DeltaIdL = IdzL - IdL;
		SIdL += F_(DeltaIdL*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIdL);

		UUdL = F_(DeltaIdL*koeff.Kp)/25.0 + SIdL + (DeltaIdL - DeltaIdOldL)*koeff.Kd;
		DeltaIdOldL = DeltaIdL;

// @@@@@ IdReg end

// ##### ������� ��� ������� bgn


		//�������� ������� �� 0
		if(UqSIL >= 0 && UqSIL < 10)
		UqSIL = 10;

		if(UqSIL < 0 && UqSIL > -10)
		UqSIL = -10;

		//if(PowerMax < 300000) PowerMax = 300000;
		//if(PowerMax > 1600000) PowerMax = 1600000;

		//IqLMAX = ((PowerMax >> 1) - L_(UdSIL)*L_(IdzL))/L_(UqSIL)/1.4142;
		IqLMAX = (PowerMax*0.666 - L_(UdSIL)*L_(IdzL))/L_(UqSIL);

		MinMaxLimitInt(-2000,2000,&IqLMAX);

		fIqLMAX += (IqLMAX - fIqLMAX)/koeff.KFiltIq;

		//IqLMAX = fIqLMAX;



// @@@@@ ������� ��� ������� end

// ##### IqReg bgn

		SpeedRegL();

		MinMaxLimitInt(-1500,abs(IqLCurLim),&IqzL);

		DeltaIqL = IqzL - IqL;
		SIqL += F_(DeltaIqL*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIqL);

		UUqL = F_(DeltaIqL*koeff.Kp)/25.0 + SIqL + (DeltaIqL - DeltaIqOldL)*koeff.Kd;
		DeltaIqOldL = DeltaIqL;

// @@@@@ IqReg end

CrossComL();

		if(koeff.K20)
		{

			if(abs(SpeedL) > 50)
			{
				UUdL += UkdL;
				UUqL += UkqL ;
			}

		}

		iffL = (fUmL - 12500)/63;
		MinMaxLimitInt(0,79,&iffL);

		UdSIL = F_(ConvertVParamToSI(UUdL))/FourieK[iffL];
		UqSIL = F_(ConvertVParamToSI(UUqL))/FourieK[iffL];

		PowerL = (L_(UdSIL)*L_(IdzL) + L_(UqSIL)*L_(IqzL))/666;

		PowerL = F_(PowerL);

		PowerL16 = PowerL;

		//IfRMSL = F_(GetHypByLegs(IdzL,IqzL))/1.4142;


		InvPark(&UAlphaL,&UBetaL,UUdL,UUqL,fThetaL);
		InvClark(&UUAL,&UUBL,&UUCL,UAlphaL,UBetaL);

		InvPark(&IAlphaL,&IBetaL,IdzL,IqzL,fThetaL);
		InvClark(&Iaz,&Ibz,&Icz,IAlphaL,IBetaL);

		ELCalcL();

		if(Debug == 2)
		{
			UUAL = Slider.s1;
			UUBL = Slider.s2;
			UUCL = /*Slider.s3;*/-UUAL - UUBL;

			Udz = Slider.s6;

			//ChopReg = Slider.s3;
		}

		if(Debug == 9)
		{

			AmplL 	= Slider.s1;
			AlphaL	+= F_(Slider.s2)/10000.0; /* -10 10*/

			HandleReg(&UUAL,&UUBL,&UUCL,&AmplL,&AlphaL);

		}

		//SIN6 = ((float)koeff.K_UdzDrive)*sin(fThetaL6);
/*
		UUAL = UUAL*FourieK[iffL];
		UUBL = UUBL*FourieK[iffL];
		UUCL = UUCL*FourieK[iffL];
*/

		UUAL += HALF_PWM_HEIGHT;// - SIN6;
		UUBL += HALF_PWM_HEIGHT;// - SIN6;
		UUCL += HALF_PWM_HEIGHT;// - SIN6;

		/*UZeroL = (GetMAX(UUAL-HALF_PWM_HEIGHT,GetMAX(UUBL-HALF_PWM_HEIGHT,UUCL-HALF_PWM_HEIGHT)) + GetMIN(UUAL-HALF_PWM_HEIGHT,GetMIN(UUBL-HALF_PWM_HEIGHT,UUCL-HALF_PWM_HEIGHT)))/2;

		if(koeff.K20)
		{
			UUAL -= UZeroL;
			UUBL -= UZeroL;
			UUCL -= UZeroL;
		}*/



		if(UUAL <= MIN_PWM) UUAL = 0;
		if(UUAL >= MAX_PWM) UUAL = 25000;
		if(UUBL <= MIN_PWM) UUBL = 0;
		if(UUBL >= MAX_PWM) UUBL = 25000;
		if(UUCL <= MIN_PWM) UUCL = 0;
		if(UUCL >= MAX_PWM) UUCL = 25000;

		EPwm1Regs.CMPA.half.CMPA = UUAL;
		EPwm2Regs.CMPA.half.CMPA = UUBL;
		EPwm3Regs.CMPA.half.CMPA = UUCL;

		/*if(Debug == 0){

			if((Ud - Udz) > 50)
			{
				ChopReg = (Ud - Udz - 50)*500;
			}

		}*/

	}
	else //if(GS.STATE.bit.LeftImp)
		RegLToZero();

//	if(Debug == 4)
//	ChopReg = Slider.s6;

	dUdChop = (Ud - Udz);

	if(dUdChop > 50)
	{
		if(dUdChop > 100) dUdChop = 100;

		ChopRegX = (dUdChop - 50)*500;

	}
	else{
		ChopRegX=0;
	}

	ChopReg += (ChopRegX - ChopReg)/10;

	if(ChopReg < ChopRegX) ChopReg = ChopRegX;

	if(Debug == 2 || Debug == 5)
	ChopReg = Slider.s3;

//	if( Debug == 5)
//	{}
		// �������/�������� ����.xls)
		PowerUvtr = (Ud >> 5)*(Ud >> 5)*2.73;

		// (1024/1000)*(3*Um*Id)/2^0.5
		PowerByGen = (Ugen >> 5)*(Igen >> 5)*2.17;
		fPowerByGen += (PowerByGen - fPowerByGen)/10;


/*
	if(Debug == 6 || Debug == 5 || Debug == 2 || Debug == 3)
	{
			ChopReg = Slider.s3;
	}*/

		if(ChopReg <= 390) ChopReg = 0;
		if(ChopReg >= 24610) ChopReg = 25000;

		if(Debug == 0)
		{
			//����� ���������� ��� ��������� ��������
			if(Ud > koeff.UdChStop && Ud < (koeff.UdInvStop + 10) && !EX_CONTROL_PIN)
			{
				ChopReg = 1000;
			}
		}

		EPwm5Regs.CMPA.half.CMPA = ChopReg;

		ChopOpen = (F_(ChopReg)/F_(25000))*100.0;
/*****************************************************************/
// EOF
/*****************************************************************/
}

void ELCalcL(){


		/*	UAlphaSIL = ConvertVParamToSI(UAlphaL);
			UBetaSIL  = ConvertVParamToSI(UBetaL);

			UAlphaSIL = (int)(F_(UAlphaSIL)/FourieK[iffL]);
			UBetaSIL = (int)(F_(UBetaSIL)/FourieK[iffL]);

			DeltaIAlphaL = IAlphaL - OldIAlphaL;
			DeltaIBetaL = IBetaL - OldIBetaL;

			EAlphaInstL = UAlphaSIL - IAlphaL*MPL.RS - (MPL.LS*DeltaIAlphaL)/dt;
			EBetaInstL = UBetaSIL - IBetaL*MPL.RS - (MPL.LS*DeltaIBetaL)/dt;*/

			OldIAlphaL = IAlphaL;
			OldIBetaL = IBetaL;

			fE_ampL += F_((GetHypByLegs(UdSIL,UqSIL) - fE_ampL))/F_(koeff.KFiltE);

			E_ampL = fE_ampL;

			XmL = fOmegaL*MPL.LM;

			ImL = fE_ampL/XmL;

}































