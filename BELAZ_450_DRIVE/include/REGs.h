/*
 * REGs.h
 *
 *  Created on: 04.10.2018
 *      Author: smirnov_as
 */
#ifndef FLASH_RUN
#define MATLAB
#endif

#ifdef MATLAB
//#include "math.h"
#define HALF_PWM_HEIGHT			12500

#define DRIVE					1
#define REVERSE					2
#define NEUTRAL					0

#define dt						0.000666

#define MIN_PWM					1000
#define MAX_PWM					(25000-MIN_PWM)

//PINS
#define RIGHT_INV_CONTROL_PIN	//DAT59
#define LEFT_INV_CONTROL_PIN	//DAT14
#define EX_CONTROL_PIN			16//DAT16
#define CHOP_CONTROL_PIN		//DAT15

// MATH CONSTANT
#define M_PI        			3.14159
#define _3SQRT2 				1.73205
#define _2SQRT2 				1.41421
#define _1DIV3SQRT2				0.57735


#define _2PIdiv3				2.09439
#define _4PIdiv3				4.18878
#define CONST					28		//U/f=CONST

#endif
#ifndef REGS_H_
#define REGS_H_
extern float SummDeltaSpeed;

//LEFT MOTOR
extern	int IaL;
extern	int IbL;
extern	int IcL;

extern	int IAlphaL;
extern	int IBetaL;

extern	int IdzL;
extern	int IdL;
extern	float SIdL;
extern	int DeltaIdOldL;
extern	int DeltaIdL;
extern	int UUdL;

extern	int IqzL;
extern	int IqL;
extern	float SIqL;
extern	int DeltaIqOldL;
extern	int DeltaIqL;
extern	int UUqL;


extern	int UdSIL;
extern	int UqSIL;

extern	int E_ampL;    	// Амплитуда фазного ЭДС после фильтра (Вольты)
extern	float fE_ampL;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
extern	int UAlphaSIL;	// Мгновенное значение напряжения по оси альфа (Вольты)
extern	int UBetaSIL;		// Мгновенное значение напряжения по оси бета (Вольты)
extern	int DeltaIAlphaL;
extern	int DeltaIBetaL;
extern	int OldIAlphaL;
extern	int OldIBetaL;
extern	int EAlphaInstL;
extern	int EBetaInstL;
extern  int E_MaxL;
extern  int E_LineL;



extern	int Ez_ampL;
extern	int SEL;

extern	int IqLCurLim;
extern	int IqLMAX;
extern	int fIqLMAX;

extern	int UAlphaL;
extern	int UBetaL;

extern	int UUAL;
extern	int UUBL;
extern	int UUCL;

extern	int ChopReg;

extern int UUqzL;
extern int fUmL;
extern int UmL;
extern int DeltaIdzL;

extern int dEL;
extern float sdEL;

extern int UkdL;
extern int UkqL;

extern 	float ThetaSlipL;
extern 	float fThetaL;

extern 	int EbyFreqL;

extern  int LmL16;
extern  int FreqL16;

extern  int   AFSpeedzL16;

extern  int DeltaSpeedL;

extern  int SpeedLz1_16;
extern  int DeltaSpeedL1;

extern  long PowerL;
extern  int PowerL16;

extern  int Iaz;
extern  int Ibz;
extern  int Icz;

extern  int IAlphaz;
extern  int Ibetaz;

extern  int ImL;
extern  int iffL;

extern  int IfRMSL;

extern	int 	AmplL;
extern	float 	AlphaL;

extern		void LookerL();
extern		void RegL();

extern		int IdzLbyE;

//RIGHT MOTOR

extern	int IaR;
extern	int IbR;
extern	int IcR;

extern	int IAlphaR;
extern	int IBetaR;

extern	int IdzR;
extern	int IdR;
extern	float SIdR;
extern	int DeltaIdOldR;
extern	int DeltaIdR;
extern	int UUdR;

extern	int IqzR;
extern	int IqR;
extern	float SIqR;
extern	int DeltaIqOldR;
extern	int DeltaIqR;
extern	int UUqR;


extern	int UdSIR;
extern	int UqSIR;

extern	int E_ampR;    	// Амплитуда фазного ЭДС после фильтра (Вольты)
extern	float fE_ampR;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
extern	int UAlphaSIR;	// Мгновенное значение напряжения по оси альфа (Вольты)
extern	int UBetaSIR;		// Мгновенное значение напряжения по оси бета (Вольты)
extern	int DeltaIAlphaR;
extern	int DeltaIBetaR;
extern	int OldIAlphaR;
extern	int OldIBetaR;
extern	int EAlphaInstR;
extern	int EBetaInstR;
extern  int E_MaxR;
extern  int E_LineR;

extern  int URsAlpha_R;
extern  int URsBeta_R;
extern  int ULsAlpha_R;
extern  int ULsBeta_R;

extern  int URsAlpha_L;
extern  int URsBeta_L;
extern  int ULsAlpha_L;
extern  int ULsBeta_L;

extern	int Ez_ampR;
extern	int SER;

extern	int IqRCurLim;
extern	int IqRMAX;
extern	int fIqRMAX;

extern	int UAlphaR;
extern	int UBetaR;

extern	int UUAR;
extern	int UUBR;
extern	int UUCR;

extern	int ChopReg;

extern int UUqzR;
extern int fUmR;
extern int UmR;
extern int DeltaIdzR;

extern int dUUqR;
extern float sdUUqR;

extern int UkdR;
extern int UkqR;

extern 	float ThetaSlipR;
extern 	float fThetaR;

extern 	int EbyFreqR;

extern  int RmR16;
extern  int FreqR16;

extern  int   AFSpeedzR16;

extern  int DeltaSpeedR;

extern  int SpeedRz1_16;
extern  int DeltaSpeedR1;
extern  float SpeedRz1;
extern  float SpeedLz1;

extern	int 	AmplR;
extern	float 	AlphaR;

extern	long PowerR;
extern	int PowerR16;

extern	void RookerR();
extern	void RegR();

extern	int PowerBrakeMax;

/*******************************************************/
extern	float FourieK[];

extern	int PowerUvtr;
extern	int PowerByGen;
extern	int fPowerByGen;

//-------------------------func.c------------------------
#ifdef MATLAB
#ifndef null
#define null ((void *) 0)
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef true
#define true    1
#endif

#ifndef false
#define false   0
#endif
extern		void _PAUSE(unsigned long step);
extern		int GetMIN(int A,int B);
extern		int GetMAX(int A,int B);
extern		int CountUP(int *C,int V);
extern		void Clark(int A,int B,int C,int *Alpha,int *Beta);
extern		void InvClark(int *A,int *B,int *C,int Alpha,int Beta);
extern		void Park(int Alpha,int Beta,int *D,int *Q,float Theta);
extern		void InvPark(int *Alpha,int *Beta,int D,int Q,float Theta);
extern		void MagneticSaturation(int Id,float *Lm);
extern		void HeatWinding(float *Rs);
extern		void RadianLimit(float *Var);
extern		void MinMaxLimitInt(int MIN,int MAX,int *Var);
extern		void MinMaxLimitFloat(int MIN,int MAX,float *Var);
extern		int ConvertVParamToSI(int Param);
extern		int GetHypByLegs(int Leg1,int Leg2);
extern		int GetCatByHypNLeg(int Leg1,int Hyp);
extern		int ConvertVParamToRU(int Param);



extern		int  SpeedLz ;
extern		int  SpeedL ;			// скорость левого колеса в об/мин
extern		int  SpeedRz ;
extern		int  SpeedR ;			// скорость левого колеса в об/мин
extern		int Udz ;
extern		int Drive ;
extern		int Brake ;
extern		unsigned int Debug ;
extern		unsigned int ThetaL ;		// Тета электрич угол с учетом скольжения
extern		long PowerMax ;
extern		int Ugen ;
extern		int Igen ;
extern		int Ud ;

struct cmd_
{
	int DNR;
};
extern struct cmd_ cmd;

extern float ElectricAngleL;
extern float ElectricAngleR;
#endif

extern int UUqRMAX;
extern float kIqR;
extern int UUqLMAX;
extern float kIqL;

//Диференциал
extern int  DeltaAxleSpeedL; 		// Разность скорости левого колеса и средней скорости по оси
extern int  DeltaAxleSpeedR; 		// Разность скорости правого колеса и средней скорости по оси
extern int  AverageAxleSpeed;		// Средняя скорость оси

extern float deltaAxleProcent; 		// Текущий процент разности скоростей
extern float deltaAxleProcentMAX;	// Текущий допустимый процент разности скоростей

extern float SummSpeedL;				// Интегратор РС
extern int   LimitSummSpeedL;		// Ограничение интегратора РС

extern float SummSpeedR;				// Интегратор РС
extern int   LimitSummSpeedR;		// Ограничение интегратора РС

extern int SummSpeedRint;
extern int SummSpeedLint;

extern int fCalcEByZ;
extern int fUseDeltaTheta;
extern int fTryBrakeDiff;

extern float kEamp;
extern float kpz;
extern float kiz;

extern int limitZeroSpeed;
extern int fHoldZero;

//ABS
extern int DeltaSpeedLABS;
extern int DeltaSpeedRABS;

extern int SpeedLOther;
extern int SpeedROther;

extern int AverageThisAxleSpeed;
extern int AverageOtherAxleSpeed;
extern int AverageCarSpeed;
extern int ABS;
extern int fABS;

extern float kDiff;

extern int SpeedHolding;
extern int zRPMDiz;
extern int SumPower;
//Круизконтроль
extern int otfCruize;
extern int kphold;
extern float CruizeDriveL;
extern 	int DeltaSpeedLCruize;
extern 	int SpeedLzCruize;
extern 	int DeltaSpeedRCruize;
extern 	int SpeedRzCruize;
extern 	int IqzLCruize;
extern 	int IqzRCruize;

extern int sdEXMAX;
extern int sdELint;
extern int sdERint;

extern int KSI;

extern float SummSpeedBackL;
extern float SummSpeedBackR;
extern float kB;

// структуры
//extern struct ALTERA_REGS altera_regs;
#define NUM_OF_KOEFF 50
struct KOEFF
{

/*00*/	int IFMAX;		//аварийная уставка фазного тока
/*01*/	int UdMAX;		//аварийная уставка напряжения в звене постоянного тока
/*02*/	int IgenMAX;		//аварийная уставка тока генератора
/*03*/	int IvMAX;		//аварийная уставка тока возбуждения
/*04*/	int IFZero;		//аварийная уставка нуля тока
/*05*/	int DeltaUd;		//аварийная уставка производной напряжения для КЗ
/*06*/	int UdExMin;		//уставка подачи импульсов на возбудитель
/*07*/	int UdInvStart;   //уставка подачи импульсов на инвертора и чоппер
/*08*/	int UdInvStop;    //уставка снятия импульсов c инвертора
/*09*/	int UdChStop;   	//уставка снятия импульсов с чоппера
/*10*/	int K1_Rvg;
/*11*/	int K2_Rvg;
/*12*/	int Kp_Rvg;
/*13*/	int Ki_Rvg;
/*14*/	int K_UdzDiz;
/*15*/	int B_UdzDiz;
/*16*/	int K_UdzDrive;
/*17*/	int B_UdzDrive;
/*18*/	int Kp;			//пропорциональная часть регулятора тока
/*19*/	int Ki;			//интегральная часть регулятора тока
/*20*/	int Kd;			//дифференциальная часть регулятора тока
/*21*/	int KFiltE;		//аппериодический фильтр ЭДС
/*22*/	int KpE;			//пропорциональная часть регулятора ЭДС
/*23*/	int KiE;			//интегральная часть регулятора ЭДС
/*24*/	int KFiltIq;		//аппериодический фильтр максимального тока
/*25*/	int Kf;			//выход на частоту U/f=Const (за сколько милисекунд наберется 1 Герц)
/*26*/	int cIf;
/*27*/	int cUd;
/*28*/	int cIv;
/*29*/	int cIgen;
/*30*/	int cUgen;
/*31*/	int WriteKoeff;
/*32*/	int WriteDacs;
/*33*/	int K7;
/*34*/	int K8;
/*35*/	int K9;
/*36*/	int K10;
/*37*/	int K11;
/*38*/	int K12;
/*39*/	int K13;
/*40*/	int K14;
/*41*/	int K15;
/*42*/	int K16;
/*43*/	int K17;
/*44*/	int K18;
/*45*/	int K19;
/*46*/	int K20;
/*47*/	int K21;
/*48*/	int K22;
/*49*/	int K23;
};

extern struct KOEFF koeff;


struct MashineParam{
		float LS;
		float LR;
		float LM;
		float RR;
		float RS;
		float K1;
		float K2;
		float L1;
		float TS;
		float TR;
};

void ELCalc(int *, int , int *, int , int , int *, int *,  int , int ,int *, int *,
			int *, int *, struct MashineParam , int *, int *, int *, int *,	float *, int *);

void Looker(int , struct MashineParam , float *, float *, int , float *, int *);

void CrossCom(int *, int *, float *, struct MashineParam, int, int);

void SpeedReg(int *, int , int *, float *, struct KOEFF , int *,const int , int *,
				int , int *, unsigned int , float *);

void CalcDeltaId(int *, int , int , int *, int , float *,int *, int *, const int , int *, const int, float *, int *, int *);


extern struct MashineParam MPL;
extern struct MashineParam MPR;
#ifndef MATLAB
#define cmd						GS.COMMANDS.bit
#endif
//________________________COMMANDS
struct Commands
{
	unsigned Gen:1;				//0
	unsigned LeftWheel:1;		//1
	unsigned RightWheel:1;		//2
	unsigned ManualControl:1;	//3

	unsigned ArrayLabel:1;		//4
	unsigned LoadArray:1;		//5
	unsigned Start:1;			//6
	unsigned DNR:2;				//7,8
	unsigned Reset:1;			//9
	unsigned ApplyDebug:1;		//10

	unsigned rsrv:5;
};




struct SSlider{

	int s1;
	int s2;
	int s3;
	int s4;
	int s5;
	int s6;
	int SaveRange;
	int MAX1;
	int MIN1;
	int MAX2;
	int MIN2;
	int MAX3;
	int MIN3;
	int MAX4;
	int MIN4;
	int MAX5;
	int MIN5;
	int MAX6;
	int MIN6;
	unsigned int addr1;
	unsigned int addr2;
	unsigned int addr3;
	unsigned int addr4;
	unsigned int addr5;
	unsigned int addr6;
};

extern struct SSlider Slider;
#endif /* REGS_H_ */
