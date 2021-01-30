/*
 * REGs.h
 *
 *  Created on: 04.10.2018
 *      Author: smirnov_as
 */

#ifndef REGS_H_
#define REGS_H_

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

extern	int 	AmplR;
extern	float 	AlphaR;

extern	long PowerR;
extern	int PowerR16;

extern	void RookerR();
extern	void RegR();


/*******************************************************/
extern	float FourieK[];

extern	int PowerUvtr;
extern	int PowerByGen;
extern	int fPowerByGen;

// структуры
//extern struct ALTERA_REGS altera_regs;
#define NUM_OF_KOEFF 50
struct KOEFF
{

/*00*/	int16 IFMAX;		//аварийная уставка фазного тока
/*01*/	int16 UdMAX;		//аварийная уставка напряжения в звене постоянного тока
/*02*/	int16 IgenMAX;		//аварийная уставка тока генератора
/*03*/	int16 IvMAX;		//аварийная уставка тока возбуждения
/*04*/	int16 IFZero;		//аварийная уставка нуля тока
/*05*/	int16 DeltaUd;		//аварийная уставка производной напряжения для КЗ
/*06*/	int16 UdExMin;		//уставка подачи импульсов на возбудитель
/*07*/	int16 UdInvStart;   //уставка подачи импульсов на инвертора и чоппер
/*08*/	int16 UdInvStop;    //уставка снятия импульсов c инвертора
/*09*/	int16 UdChStop;   	//уставка снятия импульсов с чоппера
/*10*/	int16 K1_Rvg;
/*11*/	int16 K2_Rvg;
/*12*/	int16 Kp_Rvg;
/*13*/	int16 Ki_Rvg;
/*14*/	int16 K_UdzDiz;
/*15*/	int16 B_UdzDiz;
/*16*/	int16 K_UdzDrive;
/*17*/	int16 B_UdzDrive;
/*18*/	int16 Kp;			//пропорциональная часть регулятора тока
/*19*/	int16 Ki;			//интегральная часть регулятора тока
/*20*/	int16 Kd;			//дифференциальная часть регулятора тока
/*21*/	int16 KFiltE;		//аппериодический фильтр ЭДС
/*22*/	int16 KpE;			//пропорциональная часть регулятора ЭДС
/*23*/	int16 KiE;			//интегральная часть регулятора ЭДС
/*24*/	int16 KFiltIq;		//аппериодический фильтр максимального тока
/*25*/	int16 Kf;			//выход на частоту U/f=Const (за сколько милисекунд наберется 1 Герц)
/*26*/	int16 cIf;
/*27*/	int16 cUd;
/*28*/	int16 cIv;
/*29*/	int16 cIgen;
/*30*/	int16 cUgen;
/*31*/	int16 WriteKoeff;
/*32*/	int16 WriteDacs;
/*33*/	int16 K7;
/*34*/	int16 K8;
/*35*/	int16 K9;
/*36*/	int16 K10;
/*37*/	int16 K11;
/*38*/	int16 K12;
/*39*/	int16 K13;
/*40*/	int16 K14;
/*41*/	int16 K15;
/*42*/	int16 K16;
/*43*/	int16 K17;
/*44*/	int16 K18;
/*45*/	int16 K19;
/*46*/	int16 K20;
/*47*/	int16 K21;
/*48*/	int16 K22;
/*49*/	int16 K23;
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

extern struct MashineParam MPL;
extern struct MashineParam MPR;

#define cmd						GS.COMMANDS.bit
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
	Uint16 addr1;
	Uint16 addr2;
	Uint16 addr3;
	Uint16 addr4;
	Uint16 addr5;
	Uint16 addr6;
};

extern struct SSlider Slider;
#endif /* REGS_H_ */
