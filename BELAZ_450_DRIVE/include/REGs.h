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

extern  int32 PowerL;
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

extern	int32 PowerR;
extern	int PowerR16;

extern	void RookerR();
extern	void RegR();


/*******************************************************/
extern	float FourieK[];

extern	int PowerUvtr;
extern	int PowerByGen;
extern	int fPowerByGen;

#endif /* REGS_H_ */
