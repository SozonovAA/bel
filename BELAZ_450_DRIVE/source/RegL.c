#ifndef FLASH_RUN
#define MATLAB
#endif

#ifndef MATLAB
#include "hfa.h"
#else
#include "BELAZ_450_DRIVE\include\REGs.h"
#endif
#ifndef MATLAB
struct MashineParam MPL;
struct MashineParam MPR;
struct GS_ GS;
struct KOEFF koeff;
#endif
struct SSlider Slider;



#ifdef MATLAB
int  SpeedLz=0;
int  SpeedL=0;			// скорость левого колеса в об/мин
int Udz=0;
int Drive=0;
int Brake=0;
unsigned int Debug=0;
unsigned int ThetaL=0;		// Тета электрич угол с учетом скольжения
long PowerMax=0;
int Ugen=0;
int Igen=0;
int Ud=0;
struct cmd_ cmd;

struct KOEFF koeff={ 2500, ///*00*/	int IFMAX;		//аварийная уставка фазного тока
		1070, ///*01*/	int UdMAX;		//аварийная уставка напряжения в звене постоянного тока
		2000, ///*02*/	int IgenMAX;		//аварийная уставка тока генератора
		350, ///*03*/	int IvMAX;		//аварийная уставка тока возбуждения
		444, ///*04*/	int IFZero;		//аварийная уставка нуля тока
		400, ///*05*/	int DeltaUd;		//аварийная уставка производной напряжения для КЗ
		80, ///*06*/	int UdExMin;		//уставка подачи импульсов на возбудитель
		350, ///*07*/	int UdInvStart;   //уставка подачи импульсов на инвертора и чоппер
		250, ///*08*/	int UdInvStop;    //уставка снятия импульсов c инвертора
		40, ///*09*/	int UdChStop;   	//уставка снятия импульсов с чоппера
		182, ///*10*/	int K1_Rvg;
		300, ///*11*/	int K2_Rvg;
		75, ///*12*/	int Kp_Rvg;
		25, ///*13*/	int Ki_Rvg;
		12345, ///*14*/	int K_UdzDiz;
		12345, ///*15*/	int B_UdzDiz;
		0, ///*16*/	int K_UdzDrive;
		12345, ///*17*/	int B_UdzDrive;
		75, ///*18*/	int Kp;			//пропорциональная часть регулятора тока
		25, ///*19*/	int Ki;			//интегральная часть регулятора тока
		0, ///*20*/	int Kd;			//дифференциальная часть регулятора тока
		2, ///*21*/	int KFiltE;		//аппериодический фильтр ЭДС
		50, ///*22*/	int KpE;			//пропорциональная часть регулятора ЭДС
		10, ///*23*/	int KiE;			//интегральная часть регулятора ЭДС
		10, ///*24*/	int KFiltIq;		//аппериодический фильтр максимального тока
		2, ///*25*/	int Kf;			//выход на частоту U/f=Const (за сколько милисекунд наберется 1 Герц)
		670, ///*26*/	int cIf;
		1000, ///*27*/	int cUd;
		1300, ///*28*/	int cIv;
		2000, ///*29*/	int cIgen;
		0, ///*30*/	int cUgen;
		0, ///*31*/	int WriteKoeff;
		0, ///*32*/	int WriteDacs;
		2, ///*33*/	int K7;
		10, ///*34*/	int K8;
		10, ///*35*/	int K9;
		6, ///*36*/	int K10;
		50, ///*37*/	int K11;
		10, ///*38*/	int K12;
		0, ///*39*/	int K13;
		2500, ///*40*/	int K14;
		10, ///*41*/	int K15;
		30, ///*42*/	int K16;
		4, ///*43*/	int K17;
		3000, ///*44*/	int K18;
		50, ///*45*/	int K19;
		0, ///*46*/	int K20;
		1, ///*47*/	int K21;
		0, ///*48*/	int K22;
		50 };///*49*/	int K23;

struct MashineParam MPL={0.00015, //LS
		0.00014, //LR
		0.0067,  //LM
		0.00483, //RR
		0.0072,  //RS
		0.9781,  //K1
		0.9795,  //K2
		0.00028736, //L1
		0.03991, //L1
		1.4161 };//TR
struct MashineParam MPR={0.00015, //LS
		0.00014, //LR
		0.0067,  //LM
		0.00483, //RR
		0.0072,  //RS
		0.9781,  //K1
		0.9795,  //K2
		0.00028736, //L1
		0.03991, //L1
		1.4161}; //TR
float ElectricAngleL=0;
#endif



void LookerL();
void RegL();
void ELCalcL();

#ifndef MATLAB
#pragma CODE_SECTION(LookerL,"ramfuncs")
#pragma CODE_SECTION(RegL,"ramfuncs")
#pragma CODE_SECTION(ELCalcL,"ramfuncs")
#endif

int URsAlpha_L=0;
int URsBeta_L=0;
int ULsAlpha_L=0;
int ULsBeta_L=0;

//LEFT MOTOR
int IaL=0;
int IbL=0;
int IcL=0;

int IAlphaL=0;
int IBetaL=0;

int IdzL=0;
float IdzLx=0;
int IdL=0;
float SIdL=0;
int DeltaIdOldL=0;
int DeltaIdL=0;
int UUdL=0;

float IqzLnf=0;
int IqzL=0;
int IqL=0;
float SIqL=0;
int DeltaIqOldL=0;
int DeltaIqL=0;
int UUqL=0;


int UdSIL=0;
int UqSIL=0;

float fE_MaxL=0;
int E_MaxL=0;
int E_LineL=0;
int E_ampL=0;    		// Амплитуда фазного ЭДС после фильтра (Вольты)
float fE_ampL=0;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
int UAlphaSIL=0;		// Мгновенное значение напряжения по оси альфа (Вольты)
int UBetaSIL=0;		// Мгновенное значение напряжения по оси бета (Вольты)
int DeltaIAlphaL=0;
int DeltaIBetaL=0;
int OldIAlphaL=0;
int OldIBetaL=0;
int EAlphaInstL=0;
int EBetaInstL=0;

int Ez_ampL=0;
int SEL=0;

int IqLCurLim=0;
int IqLMAX=0;
int fIqLMAX=0;

int UAlphaL=0;
int UBetaL=0;

int UUAL=0;
int UUBL=0;
int UUCL=0;

int ChopReg=0;

float fIdLf=0;
int iIdLf=0;

int iSlipL=0;

float DeltaOmegaSlipL,ThetaSlipL=0;


int LTheta;

int TCN=0;

long SQRT=0;
int SIN16=0;
int SIN16Count=0;

float fThetaL=0;

int C=0;

int Theta16=0;

void SpeedRegL();

#ifndef MATLAB
#pragma CODE_SECTION(SpeedRegL,"ramfuncs")
#endif

int DeltaSpeedL=0;

int UUqzL=0;
int fUmL=0;
int UmL=0;
int DeltaIdzL=0;
float DeltaIdzLx=0;

int dEL=0;
float sdEL=0;
int sdEXMAX=1100;

int sdELint;
int sdERint;

int UkdL=0;
int UkqL=0;

long PowerL=0;
int PowerL16=0;

void CalcDeltaIdL();
void RegLToZero();
void CrossComL();

#ifndef MATLAB
#pragma CODE_SECTION(CalcDeltaIdL,"ramfuncs")
#pragma CODE_SECTION(RegLToZero,"ramfuncs")
#pragma CODE_SECTION(CrossComL,"ramfuncs")
#endif

float AFSpeedzL=0;
int   AFSpeedzL16=0;

float SpeedLz1=0;
int SpeedLz1_16=0;
int DeltaSpeedL1=0;

float SummDeltaSpeed=0;

unsigned int SpeedTestCount=0;
float sSpeedLz=0.0;
float fIqurLimL=0;

int Iaz=0;
int Ibz=0;
int Icz=0;

int IAlphaz=0;
int Ibetaz=0;

unsigned int ChopOpen=0;

unsigned int ThetaL6=0;
float  fThetaL6=0;

int SIN6=0;

float fOmegaL=0;
int iffL=0;

int ImL=0;
float XmL=0;

int IfRMSL=0;

int 	AmplL=0;
float 	AlphaL=0;

int PowerUvtr=0;
int PowerByGen=0;
int fPowerByGen=0;

int SummChopReg=0;
int dUdChop=0;

int IqLMAXBrake=0;
int ChopRegX=0;

float IqSummInBrakeL=0;
extern float kBrake;

int UUqLMAX;
float kIqL=1.0;
float fkIqL=1.0;
//Дифференциал
int  DeltaAxleSpeedL=0; 		// Разность скорости левого колеса и средней скорости по оси
int  DeltaAxleSpeedR=0; 		// Разность скорости правого колеса и средней скорости по оси
int  AverageAxleSpeed=0;		// Средняя скорость оси

float deltaAxleProcent=0; 		// Текущий процент разности скоростей
float deltaAxleProcentMAX=0.3;	// Текущий допустимый процент разности скоростей

float SummSpeedL=0;				// Интегратор РС
int   LimitSummSpeedL=0;		// Ограничение интегратора РС

int TaskUDZYVTR=400;

int SummSpeedLint=0;

float oldThetaL=0;
float deltaThetaL=0;

int fCalcEByZ=1;
int fUseDeltaTheta=1;
int fTryBrakeDiff=1;

float kEamp=1.1;

float kpz=5;
float kiz=150;

int limitZeroSpeed=10;

int fHoldZero=0;

float kDiff=10.0;

int kChop = 10;

int drivePedalON=0;
//учет скольжения в зависимости от скорости
int fUseDeltaThetaSlip=0; //флаг о том что учитываем скольжение в угле
float koefThetaSlip=0.000322; //коэфициент скольжения (по коду понятно за что отвечает)

float deltaThetaSlipL=0; //изменение угла от скольжения

int YVTRREZ=0;

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

	if(UUdL>17400) UUdL=17400;

	UUqLMAX = GetCatByHypNLeg(UUdL,17500);

	if(UmL >= 17500)
		UmL = 17500;

	fUmL += (UmL - fUmL)/25;

#ifdef MATLAB
	Udz = 940;
#endif

	fE_MaxL += (((float)(Udz)*kEamp/2.0) - fE_MaxL)/koeff.K17;

	E_MaxL = fE_MaxL*fkIqL;
	E_LineL = (float)(abs(SpeedL))*0.0686*koeff.K15;

	if(E_LineL < 100) E_LineL = 100;
	if(E_MaxL < 200) E_MaxL = 200;

	if(E_LineL<E_MaxL)
		dEL = E_LineL - E_ampL;

	else
		dEL = E_MaxL - E_ampL;

	//MinMaxLimitInt(-540,540,&dEL);

	sdEL += ((float)(dEL)/1000.0)*(float)(koeff.KiE);

	if(sdEL > sdEXMAX) sdEL=sdEXMAX;
	if(sdEL < -sdEXMAX) sdEL=-sdEXMAX;

	IdzL = (long)(dEL)*koeff.KpE/10.0 + sdEL;

	MinMaxLimitInt(0,100,&DeltaIdzL);

	sdELint = sdEL;

}

void CrossComL()
{

	UkdL = fOmegaL*IqzL*(MPL.LS + (MPL.LM*MPL.LR)/(MPL.LM+MPL.LR));

	UkqL = -fOmegaL*IdzL*(MPL.LM + MPL.LS);

	ConvertVParamToRU(UkdL);
	ConvertVParamToRU(UkqL);

}

extern unsigned int ControllerID;

//ABS
int DeltaSpeedLABS=0;
int DeltaSpeedRABS=0;

int SpeedLOther=0;
int SpeedROther=0;

int AverageThisAxleSpeed=0;
int AverageOtherAxleSpeed=0;
int AverageCarSpeed=0;
int ABS=75;
int fABS=1;

int SpeedHolding=0;
int zRPMDiz=0;
int SumPower=0;

//Круизконтроль
int otfCruize=0;
int kphold=20;
int IqzLCruize=0;
float CruizeDriveL=0;
int DeltaSpeedLCruize=0;
int SpeedLzCruize =0;
//ограничение скорости движения
int SpeedMAXFront=2000; //максимальная допустимая скорость вперед
int SpeedMAXRevers=400;//максимальная допустимая скорость назад
float kpSpeedMAX=1; //пропорциональный коэфициент на который домножаем разность скоростей
int BrakeSpeedMAX=0; //тормозное усилие от ограничения скорости
int deltaSpeedMAX=0;//разница между текущей и максимальной скоростью
int fUseSpeedMAX=0; //флаг на использование ограничения скорости
int fToKKSpeedMAX=0;//флаг который отправяем в КК о том что работает ограничение скорости

int KSI=5;

float SummSpeedBackL=0;
float SummSpeedBackR=0;
float kB=2500.0;
int fBackTest=1;

void SpeedRegL()
{

#ifdef MATLAB
	cmd.DNR = 1;
	AverageCarSpeed = (SpeedR + SpeedL)/2;

	if(drivePedalON > 13) drivePedalON = 1;
	else
		drivePedalON = 0;
#else
	drivePedalON = data_from_KK->DIN.bit.bDRIVE;

	if(Brake > 13)
		drivePedalON = 0;
#endif
//ограничение скорости
	if(cmd.DNR == DRIVE)
	{
		//ограничение скорости движения
		//Созонов 22.03
		deltaSpeedMAX=AverageCarSpeed-SpeedMAXFront;
		MinMaxLimitInt(0,100,&deltaSpeedMAX);


		BrakeSpeedMAX=deltaSpeedMAX*kpSpeedMAX;
		if(BrakeSpeedMAX>13) {
			fToKKSpeedMAX=1;
			fABS=0;
		}
		else{
			fToKKSpeedMAX=0;
			fABS=1;
		}
		Brake+=BrakeSpeedMAX*fUseSpeedMAX;
	}
	if(cmd.DNR == REVERSE)
	{
		//ограничение скорости движения
		//Созонов 22.03
		deltaSpeedMAX=abs(AverageCarSpeed)-SpeedMAXRevers;
		MinMaxLimitInt(0,100,&deltaSpeedMAX);


		BrakeSpeedMAX=deltaSpeedMAX*kpSpeedMAX;
		if(BrakeSpeedMAX>13) {
			fToKKSpeedMAX=1;
		}
		else{
			fToKKSpeedMAX=0;
		}
		Brake+=BrakeSpeedMAX*fUseSpeedMAX;
	}

		//------------------------ DIFF ----------------------------

	AverageAxleSpeed = (SpeedL + SpeedR) >> 1;
	DeltaAxleSpeedL = AverageAxleSpeed - SpeedL;

	if(DeltaAxleSpeedL > -10 && DeltaAxleSpeedL < 10)
		DeltaAxleSpeedL = 0;

	if (0<AverageAxleSpeed && AverageAxleSpeed<1) AverageAxleSpeed=1;
	if (0>AverageAxleSpeed && AverageAxleSpeed>-1) AverageAxleSpeed=-1;
	deltaAxleProcent = ((float)DeltaAxleSpeedL / ((float)AverageAxleSpeed));

	if(deltaAxleProcent > deltaAxleProcentMAX)
	{
		LimitSummSpeedL = DeltaAxleSpeedL*10;
	}
	else
		if(deltaAxleProcent < -deltaAxleProcentMAX)
		{
			LimitSummSpeedL = DeltaAxleSpeedL*10;
		}
		else
		{
			LimitSummSpeedL-=10;
			if(LimitSummSpeedL<30) LimitSummSpeedL=30;
		}

	if(LimitSummSpeedL > 700) LimitSummSpeedL = 700;
	if(LimitSummSpeedL < -700) LimitSummSpeedL = -700;

	if(Brake < 13){
		SummSpeedL += ((float)DeltaAxleSpeedL)/kDiff;
	}

	if(fHoldZero) SummSpeedL += (float)(0 - SpeedL)/kiz;

	SummSpeedLint = SummSpeedL;

	if(Brake < 13)
		MinMaxLimitFloat(-abs(LimitSummSpeedL),abs(LimitSummSpeedL),&SummSpeedL);
	else
		MinMaxLimitFloat(-1500,1500,&SummSpeedL);

	//////////////////////////

	DeltaSpeedL = (SpeedLz - IqzL)/5;

	if(!SpeedHolding){
		SpeedLz1 += (float)(DeltaSpeedL)*((float)(koeff.K7)/2500.0);
		otfCruize=0;
	}
	else if(!otfCruize){
		otfCruize=1;
		SpeedLzCruize = AverageCarSpeed;
		SpeedRzCruize = AverageCarSpeed;
	}


	if(koeff.K18 > 3000)
		koeff.K18 = 3000;
	if(koeff.K18 < 100)
		koeff.K18 = 100;

	if(SpeedLz1 > koeff.K18)
		SpeedLz1 = koeff.K18; //SpeedLz;

	if(SpeedLz1 < -500)
		SpeedLz1 = -500; //SpeedRz;

	if(Brake > 13 )
	{

		SpeedLz1 = SpeedL;
		SpeedLz = SpeedL;
	}

	DeltaSpeedL1 = SpeedLz1 - SpeedL;

	DeltaSpeedLCruize = SpeedLzCruize - AverageCarSpeed;

	//if(Brake < 13) Brake = 13;



	if(cmd.DNR == DRIVE)
	{
//		//ограничение скорости движения
//		//Созонов 22.03
//		deltaSpeedMAX=AverageCarSpeed-SpeedMAXFront;
//		MinMaxLimitInt(0,100,&deltaSpeedMAX);
//
//
//		BrakeSpeedMAX=deltaSpeedMAX*kpSpeedMAX;
//		if(BrakeSpeedMAX>13) {
//			fToKKSpeedMAX=1;
//			fABS=0;
//		}
//		else{
//			fToKKSpeedMAX=0;
//			fABS=1;
//		}
//		Brake+=BrakeSpeedMAX*fUseSpeedMAX;


		if(Brake > 13 )
		{

			//левая ось
			DeltaSpeedLABS=AverageCarSpeed -SpeedL;
#ifdef MATLAB
			DeltaSpeedLABS=SpeedR - SpeedL;
#endif
			if(DeltaSpeedLABS>ABS && IqzL<=0 && ! fHoldZero && fABS)
			{
				IqSummInBrakeL+=1;
				//IqzL=1000;
				//else IqzL-=3;
				IqzLnf = IqSummInBrakeL ;
			}
			else
				if(SpeedL > limitZeroSpeed && ! fHoldZero)
				{
					if(PowerL < PowerBrakeMax) IqSummInBrakeL += 0.1*kBrake;
					else
					{
						if(IqSummInBrakeL > -(Brake-13)*20)
							IqSummInBrakeL -= 0.1*kBrake;
						if(IqSummInBrakeL < -(Brake-13)*20)
							IqSummInBrakeL += 0.1*kBrake;
					}

					IqzLnf = IqSummInBrakeL + fTryBrakeDiff*SummSpeedL;
				}
				else
					fHoldZero = 1;//IqzL = (0-SpeedL)*kpz + fTryBrakeDiff*SummSpeedL;

			if(fHoldZero)
			{
				IqzLnf = (0-SpeedL)*kpz + fTryBrakeDiff*SummSpeedL;
			}

			//IqzL += (IqzLnf - IqzL)/25.0;

			if(IqzL < IqzLnf) IqzL++;
			else IqzL--;

			SpeedLz1 = SpeedL;
			SpeedLzCruize = AverageCarSpeed;

			//else SpeedLz1 = AverageCarSpeed;

		}
		else
		{
			fHoldZero = 0;
			if(!SpeedHolding || drivePedalON)
				IqzL = (float)(DeltaSpeedL1*koeff.K10)/4.0 + SummSpeedL;
			else{
				//CruizeDriveL += (float)(DeltaSpeedL)*((float)(koeff.K7)/2500.0);
				//MinMaxLimitInt(0,1500,&CruizeDriveL);
				IqzLCruize = DeltaSpeedLCruize*kphold ;//+ SummSpeedL;
				if (IqzL<IqzLCruize) IqzL+=20;
				else IqzL-=20;
			}

			IqSummInBrakeL = 0;
		}

		SummSpeedBackL=0;
	}
	if(cmd.DNR == REVERSE)
	{
//		//ограничение скорости движения
//		//Созонов 22.03
//		deltaSpeedMAX=abs(AverageCarSpeed)-SpeedMAXRevers;
//		MinMaxLimitInt(0,100,&deltaSpeedMAX);
//
//
//		BrakeSpeedMAX=deltaSpeedMAX*kpSpeedMAX;
//		if(BrakeSpeedMAX>13) {
//			fToKKSpeedMAX=1;
//		}
//		else{
//			fToKKSpeedMAX=0;
//		}
//		Brake+=BrakeSpeedMAX*fUseSpeedMAX;

		SummSpeedBackL += fBackTest*((float)DeltaSpeedL1/kB);

		MinMaxLimitFloat(-abs(DeltaSpeedL1*4),abs(DeltaSpeedL1*4),&SummSpeedBackL);

		if(Brake > 13)
		{
			if(SpeedL < -limitZeroSpeed && !fHoldZero)
			{
				if(IqzL < ((Brake-13)*20))
					IqzL++;
				else
					IqzL--;

				SpeedLz1 = SpeedL;

			}
			else
				fHoldZero = 1;

			if(fHoldZero)
			{
				IqzLnf = (0-SpeedL)*kpz + fTryBrakeDiff*SummSpeedL;
				//IqzL += (IqzLnf - IqzL)/25.0;

				if(IqzL < IqzLnf) IqzL++;
				else IqzL--;
			}
		}
		else
		{
			fHoldZero = 0;
			if(drivePedalON)
				IqzL = (float)(DeltaSpeedL1*koeff.K10)/4.0 + SummSpeedBackL;
		}
	}

	if(drivePedalON == 0 && Brake < 13)
	{
		IqzLnf = 0;

		//IqzL += (IqzLnf - IqzL)/25.0;

		if(IqzL < IqzLnf) IqzL++;
		else IqzL--;

		SpeedLz1 = SpeedL;
		SpeedLz = SpeedL;
	}

	SpeedLz1_16 = SpeedLz1;

	if(Debug == 4)
	{

		DeltaSpeedL = SpeedLz - SpeedL;

		MinMaxLimitInt(-1500,1500,&DeltaSpeedL);

		SummDeltaSpeed += (float)(DeltaSpeedL)/(float)(koeff.K2_Rvg);

		MinMaxLimitFloat(-2000,2000,&SummDeltaSpeed);

		IqzL = DeltaSpeedL*koeff.K8 + SummDeltaSpeed;

	}
}
float klt=1.0;
int MAXUYVTR=500;
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
	MagneticSaturation(IdzL,&MPL.LM);
	//DAT2=0;
#ifdef MATLAB
	fIdLf += (((0.003*IdzL - fIdLf)/0.5)*dt);
#else
	//	A
	fIdLf += (((MPL.LM*IdzL - fIdLf)/(MPL.TR*klt))*dt);
	//fIdLf = MPL.LM*IdzL;
#endif

#ifdef MATLAB
	//	1/Sec	equal	rad/sec
	DeltaOmegaSlipL = (0.003*(float)(IqzL)*((float)(koeff.K9)/10.0))/(fIdLf*0.5 + 0.001);
#else
	DeltaOmegaSlipL = (MPL.LM*(float)(IqzL)*((float)(koeff.K9)/10.0))/(fIdLf*(MPL.TR*klt) + 0.001);
#endif
	//  rad
	ThetaSlipL += DeltaOmegaSlipL*dt;

	//ThetaSlipL += ((float)(SpeedL*koeff.K9)/1000.0)*dt;

	RadianLimit(&ThetaSlipL);

	// 240/2*M_PI = 38.198
	//ThetaSlipL *= 38.198;

	iIdLf = fIdLf;



	//HeatWinding(&TTheta);

}

void RegL(){

#ifdef MATLAB
	PowerMax=700000;
#endif

#ifndef MATLAB
	DizelOutPowerMax();
#endif
	LookerL();

	SpeedTestCount++;
#ifndef MATLAB

	if (ControllerID == PK1)
	{
		SpeedLOther = data_from_KK->SpeedRL;
		SpeedROther = data_from_KK->SpeedRR;
	}
	if (ControllerID == PK2)
	{
		SpeedLOther = data_from_KK->SpeedFL;
		SpeedROther = data_from_KK->SpeedFR;
	}

	//------------------------ ABS ----------------------------

	AverageThisAxleSpeed = (SpeedL+SpeedR)/2;
	AverageOtherAxleSpeed = (SpeedLOther+SpeedROther)/2;
	AverageCarSpeed = (AverageThisAxleSpeed + AverageOtherAxleSpeed)/2;

	SpeedAndAngleL();

	//32400/2*M_PI = 5156.62
	//32768/2*M_PI = 5215.19
	fThetaL = (float)(ThetaL)/5215.19;

	ThetaL6 = (long)ThetaL*6L;
	ThetaL6 &= 0x7FFF;
	fThetaL6 = (float)(ThetaL)/5215.19;
#else
	fThetaL = ThetaSlipL + ElectricAngleL;
	RadianLimit(&fThetaL);
#endif

	if(((fThetaL - oldThetaL)<4) && ((fThetaL - oldThetaL)>-4)) // исключаем перегиб диапазона на 2 ПИ
		deltaThetaL = (fThetaL - oldThetaL);

	oldThetaL = fThetaL;

	CalcDeltaIdL();

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
	//st.LeftImp=1;
#ifndef MATLAB
	if(GS.STATE.bit.LeftImp)
#endif
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
				sSpeedLz += (float)(koeff.K16)/100.0;
			else
				sSpeedLz -= (float)(koeff.K16)/100.0;

			SpeedLz = sSpeedLz;

			Theta16 = fThetaL*100;

		}

		if(Debug == 0)
		{

			if(Drive < 13) Drive = 13;
#ifndef MATLAB
			if(cmd.DNR == DRIVE)
				SpeedLz = (Drive-13)*30;
			if(cmd.DNR == REVERSE)
				SpeedLz = -(Drive-13)*30;
#endif
		}

		Clark(IaL,IbL,IcL,&IAlphaL,&IBetaL);
		Park(IAlphaL,IBetaL,&IdL,&IqL,fThetaL);

		// ##### IdReg bgn

		MinMaxLimitInt(5,1100,&IdzL);

		//IdzL *=fkIqL;

		DeltaIdL = IdzL - IdL;
		SIdL += (float)(DeltaIdL*koeff.Ki)/25.0;

		MinMaxLimitFloat(-18000,18000,&SIdL);

		UUdL = (float)(DeltaIdL*koeff.Kp)/25.0 + SIdL + (DeltaIdL - DeltaIdOldL)*koeff.Kd;
		DeltaIdOldL = DeltaIdL;

		// @@@@@ IdReg end

		// ##### Считаем ток отсечки bgn


		//избегаем деление на 0
		if(UqSIL >= 0 && UqSIL < 10)
			UqSIL = 10;

		if(UqSIL < 0 && UqSIL > -10)
			UqSIL = -10;

		if(Brake < 13)
			IqLMAX = (PowerMax*0.666 - (long)(UdSIL)*(long)(IdzL))/(long)(UqSIL);
		else
			IqLMAX = ((1000000)*0.666 - (long)(UdSIL)*(long)(IdzL))/(long)(UqSIL);

		MinMaxLimitInt(-2000,2500,&IqLMAX);

		fIqLMAX += (IqLMAX - fIqLMAX)/koeff.KFiltIq;

		IqLCurLim = abs(fIqLMAX);

		// @@@@@ Считаем ток отсечки end

		// ##### IqReg bgn

		SpeedRegL();

		if(abs(SpeedL) > 150/*  && Brake < 13*/)
			MinMaxLimitInt(-abs(IqLCurLim),abs(IqLCurLim),&IqzL);

		if(UUqL > UUqLMAX) kIqL = (float)15500/(float)UUqL;
		else kIqL = 1;

		fkIqL += (kIqL - fkIqL)/75.0;

		//IqzL*=fkIqL;

		DeltaIqL = IqzL - IqL;
		SIqL += (float)(DeltaIqL*koeff.Ki)/25.0;

		MinMaxLimitFloat(-17500,17500,&SIqL);

		UUqL = (float)(DeltaIqL*koeff.Kp)/25.0 + SIqL + (DeltaIqL - DeltaIqOldL)*koeff.Kd;
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

		UdSIL = (float)(ConvertVParamToSI(UUdL))/FourieK[iffL];
		UqSIL = (float)(ConvertVParamToSI(UUqL))/FourieK[iffL];

		PowerL = ((long)(UdSIL)*(long)(IdzL) + (long)(UqSIL)*(long)(IqzL))/666;

		PowerL = (float)(PowerL);

		PowerL16 = PowerL;

		//IfRMSL = (float)(GetHypByLegs(IdzL,IqzL))/1.4142;

		if(fUseDeltaTheta)
			fThetaL += deltaThetaL*0.8;
		//учет сокльжения в зависимости от скорости (для больших скоростей)
		//Созонов 22.03
		deltaThetaSlipL=koefThetaSlip*((float)SpeedL/1050);
		if(fUseDeltaThetaSlip) fThetaL-=deltaThetaSlipL;

		InvPark(&UAlphaL,&UBetaL,UUdL,UUqL,fThetaL);
		InvClark(&UUAL,&UUBL,&UUCL,UAlphaL,UBetaL);

		if(fUseDeltaTheta)
			fThetaL -= deltaThetaL*0.8;
		//учет сокльжения в зависимости от скорости (для больших скоростей)
		if(fUseDeltaThetaSlip) fThetaL+=deltaThetaSlipL;

		if(fCalcEByZ)
		{
			InvPark(&IAlphaL,&IBetaL,IdzL,IqzL,fThetaL);
			InvClark(&Iaz,&Ibz,&Icz,IAlphaL,IBetaL);
		}

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
			AlphaL	+= (float)(Slider.s2)/10000.0; /* -10 10*/
#ifndef MATLAB
			HandleReg(&UUAL,&UUBL,&UUCL,&AmplL,&AlphaL);
#endif
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

		/*UZeroL = (GetMAX(UUAL-HALF_PWM_HEIGHT,GetMAX(UUBL-HALF_PWM_HEIGHT,UUCL-HALF_PWM_HEIGHT)) + 
GetMIN(UUAL-HALF_PWM_HEIGHT,GetMIN(UUBL-HALF_PWM_HEIGHT,UUCL-HALF_PWM_HEIGHT)))/2;

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

#ifndef MATLAB
		EPwm1Regs.CMPA.half.CMPA = UUAL;
		EPwm2Regs.CMPA.half.CMPA = UUBL;
		EPwm3Regs.CMPA.half.CMPA = UUCL;
#endif
		/*if(Debug == 0){

			if((Ud - Udz) > 50)
			{
				ChopReg = (Ud - Udz - 50)*500;
			}

		}*/

	}
#ifndef MATLAB
	else //if(GS.STATE.bit.LeftImp)

		RegLToZero();
#endif
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

	ChopReg += (ChopRegX - ChopReg)/kChop;

	if(ChopReg < ChopRegX) ChopReg = ChopRegX;

	if(Debug == 2 || Debug == 5)
		ChopReg = Slider.s3;
	////////Режим УВТР с ЭПП/////////
	//	if(COMEPP.bit.ONYVTR)YVTRREZ=1;
	//
	//	if(YVTRREZ)
	//	{
	//
	//		if((ControllerID==2 && COMEPP.bit.OnOffDiezlF) || (ControllerID==3 && COMEPP.bit.OnOffDiezlR) )
	//		{
	//			if(COMEPP.bit.OnOffChop)
	//			{
	//				ChopReg=25000;
	//				PowerUvtr = (Ud >> 5)*(Ud >> 5)*2.73;
	//			}
	//			else {ChopReg=0; PowerUvtr=0;}
	//			if(UDZ_YVTR>=400) TaskUDZYVTR=UDZ_YVTR;
	//MinMaxLimitInt(400,MAXUYVTR,&TaskUDZYVTR);
	//		}
	//
	//	}
	//	else TaskUDZYVTR=400;
	//	if(YVTRREZ==1 && COMEPP.bit.ONYVTR=0)
	//	{
	//
	//		ChopReg=0;
	//		YVTRREZ=1;
	//		PowerUvtr=0;
	//
	//	}


	//	if( Debug == 5)
	//	{}
	// Расчеты/Мощность УВТР.xls)
	//PowerUvtr = (Ud >> 5)*(Ud >> 5)*2.73;

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
		//сброс напряжения при установке нейтрали
		if(Ud > koeff.UdChStop && Ud < (koeff.UdInvStop + 10) && !EX_CONTROL_PIN)
		{
			ChopReg = 1000;
		}
	}

#ifndef MATLAB
	EPwm5Regs.CMPA.half.CMPA = ChopReg;
#endif

	ChopOpen = ((float)(ChopReg)/(float)(25000))*100.0;
	/*****************************************************************/
	// EOF
	/*****************************************************************/
}

int M1=0;

void ELCalcL(){


	UAlphaSIL = ConvertVParamToSI(UAlphaL);
	UBetaSIL  = ConvertVParamToSI(UBetaL);

	UAlphaSIL = (int)((float)(UAlphaSIL)/FourieK[iffL]);
	UBetaSIL = (int)((float)(UBetaSIL)/FourieK[iffL]);

	DeltaIAlphaL = IAlphaL - OldIAlphaL;
	DeltaIBetaL = IBetaL - OldIBetaL;

	URsAlpha_L = IAlphaL*MPL.RS;
	URsBeta_L = IBetaL*MPL.RS;

	ULsAlpha_L = (MPL.LS*DeltaIAlphaL)*1500;//dt;
	ULsBeta_L = (MPL.LS*DeltaIBetaL)*1500;//dt;

	EAlphaInstL = UAlphaSIL - URsAlpha_L - ULsAlpha_L;
	EBetaInstL = UBetaSIL - URsBeta_L - ULsBeta_L;

	//			EAlphaInstL = UAlphaSIL - IAlphaL*MPL.RS - (MPL.LS*DeltaIAlphaL)/dt;
	//			EBetaInstL = UBetaSIL - IBetaL*MPL.RS - (MPL.LS*DeltaIBetaL)/dt;

	OldIAlphaL = IAlphaL;
	OldIBetaL = IBetaL;

	fE_ampL += (float)((GetHypByLegs(EAlphaInstL,EBetaInstL) - fE_ampL))/(float)(koeff.KFiltE);


	//fE_ampL += (float)((GetHypByLegs(UdSIL,UqSIL) - fE_ampL))/(float)(koeff.KFiltE);

	E_ampL = fE_ampL;

	XmL = fOmegaL*MPL.LM;

	ImL = fE_ampL/XmL;

	M1 = 4.5*((float)IqL*(float)IdL)*MPL.LM;

}

/*Функция для расчёта амплитудного значения ЭДС.
 *
 * Во входных параметрах заменять _Х_ на R/L.
 		ELCalc (&UAlphaSIR, UAlphaR, &UBetaSIR, UBetaR, iffR, &DeltaIAlphaR, &DeltaIBetaR, IAlphaR, 
IBetaR,
				   &OldIAlphaR, &OldIBetaR, &URsAlpha_R, &URsBeta_R, MPR, &ULsAlpha_R, &ULsBeta_R, 
&EAlphaInstR, &EBetaInstR,
				   &fE_ampR, &E_ampR);

		ELCalc (&UAlphaSIL, UAlphaL, &UBetaSIL, UBetaL, iffL, &DeltaIAlphaL, &DeltaIBetaL, IAlphaL, 
IBetaL,
				   &OldIAlphaL, &OldIBetaL, &URsAlpha_L, &URsBeta_L, MPL, &ULsAlpha_L, &ULsBeta_L, 
&EAlphaInstL, &EBetaInstL,
				   &fE_ampL, &E_ampL);

 */
void ELCalc(int *UAlphaSI_X, int UAlpha_X, int *UBetaSI_X, int UBeta_X,
		int iff_X, int *DeltaIAlpha_X, int *DeltaIBeta_X,  int IAlpha_X, int IBeta_X,
		int *OldIAlpha_X, int *OldIBeta_X, int *URsAlpha_X, int *URsBeta_X, struct MashineParam MP_X,
		int *ULsAlpha_X, int *ULsBeta_X, int *EAlphaInst_X, int *EBetaInst_X,
		float *fE_amp_X, int *E_amp_X){

	//приводим входные параметры к СИ
	*UAlphaSI_X = ConvertVParamToSI(UAlpha_X);
	*UBetaSI_X  = ConvertVParamToSI(UBeta_X);
	//
	*UAlphaSI_X = (int)((float)(*UAlphaSI_X)/FourieK[iff_X]);
	*UBetaSI_X = (int)((float)(*UBetaSI_X)/FourieK[iff_X]);
	//расчёт изменения тока, за время с прошлого вызова функции
	*DeltaIAlpha_X = IAlpha_X - *OldIAlpha_X;
	*DeltaIBeta_X = IBeta_X - *OldIBeta_X;
	//
	*URsAlpha_X = IAlpha_X*MP_X.RS;
	*URsBeta_X = IBeta_X*MP_X.RS;
	//
	*ULsAlpha_X = (MP_X.LS*(*DeltaIAlpha_X))*1500;//dt;
	*ULsBeta_X = (MP_X.LS*(*DeltaIBeta_X))*1500;//dt;
	//
	*EAlphaInst_X = (*UAlphaSI_X) - (*URsAlpha_X) - (*ULsAlpha_X);
	*EBetaInst_X = (*UBetaSI_X) - (*URsBeta_X) - (*ULsBeta_X);
	// значение тока, для последующего расчёта изменения за шаг
	*OldIAlpha_X = IAlpha_X;
	*OldIBeta_X = IBeta_X;
	// Амплитуда фазного ЭДС после фильтра (Вольты)(float)
	*fE_amp_X += (float)((GetHypByLegs(*EAlphaInst_X,*EBetaInst_X) - *fE_amp_X))/(float)(koeff.KFiltE);
	// Амплитуда фазного ЭДС после фильтра (Вольты)(int)
	*E_amp_X = *fE_amp_X;
}

/* Функция расчёта перекрестных связей
 * Во входных параметрах заменять _Х_ на R/L.
 * CrossCom(&UkdL, &UkqL, &fOmegaL, MPL, IqzL, IdzL);
 * CrossCom(&UkdR, &UkqR, &fOmegaR, MPR, IqzR, IdzR);
 */
void CrossCom(int *Ukd_X, int *Ukq_X, float *fOmega_X, struct MashineParam MP_X,
		int Iqz_X, int Idz_X)
{

	*Ukd_X = (*fOmega_X)*Iqz_X*(MP_X.LS + (MP_X.LM*MP_X.LR)/(MP_X.LM+MP_X.LR));

	*Ukq_X = -(*fOmega_X)*Idz_X*(MP_X.LM + MP_X.LS);

	ConvertVParamToRU(*Ukd_X);
	ConvertVParamToRU(*Ukq_X);

}

/*
 * Функция реализации следящего устройства, для расчёта Тетты с учётом скольжения
 * Во входных параметрах заменять _Х_ на R/L.
 * Looker(IdL, MPL, &fIdLf, &DeltaOmegaSlipL, IqL, &ThetaSlipL, &iIdLf);
 * Looker(IdR, MPR, &fIdRf, &DeltaOmegaSlipR, IqR, &ThetaSlipR, &iIdRf);
 */
void Looker(int Id_X, struct MashineParam MP_X, float *fId_X_f, float *DeltaOmegaSlip_X,
		int Iq_X, float *ThetaSlip_X, int *iId_X_f){
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
	MagneticSaturation(Id_X,&MP_X.LM);
	//	A
	*fId_X_f += (((MP_X.LM*Id_X - (*fId_X_f))/MP_X.TR)*dt);
	//	1/Sec	equal	rad/sec
	*DeltaOmegaSlip_X = (MP_X.LM*(float)(Iq_X)*((float)(koeff.K9)/10.0))/((*fId_X_f)*MP_X.TR + 0.001);

	*ThetaSlip_X += (*DeltaOmegaSlip_X)*dt;

	RadianLimit(ThetaSlip_X);

	*iId_X_f=*fId_X_f;
}
/*
 * Функция реализует регулятор скорости
 * Во входных параметрах заменять _Х_ на R/L.
 * SpeedReg(&DeltaSpeedR,  SpeedRz, &IqzR, &SpeedRz1, koeff, &DeltaSpeedR1,SpeedR, &Brake,
		PowerR, &SpeedRz1_16, Debug, &SummDeltaSpeed);
 * SpeedReg(&DeltaSpeedL,  SpeedLz, &IqzL, &SpeedLz1, koeff, &DeltaSpeedL1,SpeedR, &Brake,
		PowerL, &SpeedLz1_16, Debug, &SummDeltaSpeed);
 */
void SpeedReg(int *DeltaSpeed_X, int Speed_X_z, int *Iqz_X, float *Speed_X_z1,
		struct KOEFF koeff, int *DeltaSpeed_X_1,const int Speed_X, int *Brake,
		int Power_X, int *Speed_X_z1_16, unsigned int Debug, float *SummDeltaSpeed)
{

#ifdef MATLAB
	cmd.DNR = 1;
#endif

	*DeltaSpeed_X = (Speed_X_z - (*Iqz_X))/5;

	*Speed_X_z1 += (float)(*DeltaSpeed_X)*((float)(koeff.K7)/2500.0);

	if(koeff.K18 > 2500)
		koeff.K18 = 2500;
	if(koeff.K18 < 100)
		koeff.K18 = 100;

	if(*Speed_X_z1 > koeff.K18)
		*Speed_X_z1 = koeff.K18; //SpeedLz;

	if(*Speed_X_z1 < -500)
		*Speed_X_z1 = -500; //SpeedRz;


	*DeltaSpeed_X_1 = *Speed_X_z1 - Speed_X;

	if(*Brake < 13) *Brake = 13;

	if(cmd.DNR == DRIVE)
	{
		if(*Brake > 13 && Speed_X > 40)
		{

			if(Power_X < -1000) (*Iqz_X)++;
			else
				if((*Iqz_X) > -(*Brake-13)*20)
					(*Iqz_X)--;

			*Speed_X_z1 = Speed_X;
		}
		else
			(*Iqz_X) = (*DeltaSpeed_X_1)*koeff.K10;
	}
	if(cmd.DNR == REVERSE)
	{
		if(*Brake > 13 && Speed_X < -40)
		{
			(*Iqz_X) = (*Brake-13)*20;
			*Speed_X_z1 = Speed_X;
		}
		else
			(*Iqz_X) = (*DeltaSpeed_X_1)*koeff.K10;
	}

	*Speed_X_z1_16 = *Speed_X_z1;

	if(Debug == 4)
	{

		*DeltaSpeed_X  = Speed_X_z - Speed_X ;

		MinMaxLimitInt(-1500,1500, DeltaSpeed_X );

		*SummDeltaSpeed += (float)(*DeltaSpeed_X )/(float)(koeff.K2_Rvg);

		MinMaxLimitFloat(-2000,2000,SummDeltaSpeed);

		(*Iqz_X) = *DeltaSpeed_X*koeff.K8 + *SummDeltaSpeed;
	}
}
/*
 * Функция реализует расчёт Id с учётом значения ЭДС.
 * Во входных параметрах заменять _Х_ на R/L.
 * CalcDeltaId(&UmL, UUdL, UUqL, &fUmL, Udz, &fE_MaxL,&E_MaxL, &E_LineL, SpeedL, &dEL, E_ampL, &sdEL, 
&IdzL, 
&DeltaIdzL);
 * CalcDeltaId(&UmR, UUdR, UUqR, &fUmR, Udz, &fE_MaxR,&E_MaxR, &E_LineR, SpeedR, &dER, E_ampR, &sdER, 
&IdzR, 
&DeltaIdzR);
 */
void CalcDeltaId(int *Um_X, int UUd_X, int UUq_X, int *fUm_X, int Udz, float *fE_Max_X,
		int *E_Max_X, int *E_Line_X, const int Speed_X, int *dE_X, const int E_amp_X,
		float *sdE_X, int *Idz_X, int *DeltaIdz_X)
{

	*Um_X = GetHypByLegs(UUd_X,UUq_X);

	if(*Um_X >= 17500)
		*Um_X = 17500;

	*fUm_X += (*Um_X - *fUm_X)/25;

#ifdef MATLAB
	Udz = 940;
#endif

	*fE_Max_X += (((float)(Udz)*1.15/2.0) - *fE_Max_X)/koeff.K17;

	*E_Max_X = *fE_Max_X;
	*E_Line_X = (float)(abs(Speed_X))*0.0686*koeff.K15;

	if(*E_Line_X < 50) *E_Line_X=50;
	if(*E_Max_X < 200) *E_Max_X=200;

	if(*E_Line_X<*E_Max_X)

		*dE_X = *E_Line_X - E_amp_X;

	else
		*dE_X = *E_Max_X - E_amp_X;

	//MinMaxLimitInt(-540,540,&dEL);

	*sdE_X += ((float)(*dE_X)/1000.0)*(float)(koeff.KiE);

	if(*sdE_X > 540) *sdE_X=540;
	if(*sdE_X < -540) *sdE_X=-540;

	*Idz_X = (long)(*dE_X)*koeff.KpE/10.0 + *sdE_X;

	MinMaxLimitInt(0,100,DeltaIdz_X);
}






























