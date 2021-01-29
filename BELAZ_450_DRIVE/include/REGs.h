/*
 * REGs.h
 *
 *  Created on: 04.10.2018
 *      Author: smirnov_as
 */

#ifndef REGS_H_
#define REGS_H_

//LEFT MOTOR
extern	int16 IaL;
extern	int16 IbL;
extern	int16 IcL;

extern	int16 IAlphaL;
extern	int16 IBetaL;

extern	int16 IdzL;
extern	int16 IdL;
extern	float SIdL;
extern	int16 DeltaIdOldL;
extern	int16 DeltaIdL;
extern	int16 UUdL;

extern	int16 IqzL;
extern	int16 IqL;
extern	float SIqL;
extern	int16 DeltaIqOldL;
extern	int16 DeltaIqL;
extern	int16 UUqL;


extern	int16 UdSIL;
extern	int16 UqSIL;

extern	int16 E_ampL;    	// Амплитуда фазного ЭДС после фильтра (Вольты)
extern	float fE_ampL;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
extern	int16 UAlphaSIL;	// Мгновенное значение напряжения по оси альфа (Вольты)
extern	int16 UBetaSIL;		// Мгновенное значение напряжения по оси бета (Вольты)
extern	int16 DeltaIAlphaL;
extern	int16 DeltaIBetaL;
extern	int16 OldIAlphaL;
extern	int16 OldIBetaL;
extern	int16 EAlphaInstL;
extern	int16 EBetaInstL;
extern  int16 E_MaxL;
extern  int16 E_LineL;

extern	int16 Ez_ampL;
extern	int16 SEL;

extern	int16 IqLCurLim;
extern	int16 IqLMAX;
extern	int16 fIqLMAX;

extern	int16 UAlphaL;
extern	int16 UBetaL;

extern	int16 UUAL;
extern	int16 UUBL;
extern	int16 UUCL;

extern	int16 ChopReg;

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

extern 	int16 EbyFreqL;

extern  int16 LmL16;
extern  int16 FreqL16;

extern  int   AFSpeedzL16;

extern  int DeltaSpeedL;

extern  int SpeedLz1_16;
extern  int DeltaSpeedL1;

extern  int32 PowerL;
extern  int16 PowerL16;

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

extern		int16 IdzLbyE;

//RIGHT MOTOR

extern	int16 IaR;
extern	int16 IbR;
extern	int16 IcR;

extern	int16 IAlphaR;
extern	int16 IBetaR;

extern	int16 IdzR;
extern	int16 IdR;
extern	float SIdR;
extern	int16 DeltaIdOldR;
extern	int16 DeltaIdR;
extern	int16 UUdR;

extern	int16 IqzR;
extern	int16 IqR;
extern	float SIqR;
extern	int16 DeltaIqOldR;
extern	int16 DeltaIqR;
extern	int16 UUqR;


extern	int16 UdSIR;
extern	int16 UqSIR;

extern	int16 E_ampR;    	// Амплитуда фазного ЭДС после фильтра (Вольты)
extern	float fE_ampR;    	// Амплитуда фазного ЭДС до фильтра (Вольты)
extern	int16 UAlphaSIR;	// Мгновенное значение напряжения по оси альфа (Вольты)
extern	int16 UBetaSIR;		// Мгновенное значение напряжения по оси бета (Вольты)
extern	int16 DeltaIAlphaR;
extern	int16 DeltaIBetaR;
extern	int16 OldIAlphaR;
extern	int16 OldIBetaR;
extern	int16 EAlphaInstR;
extern	int16 EBetaInstR;
extern  int16 E_MaxR;
extern  int16 E_LineR;

extern	int16 Ez_ampR;
extern	int16 SER;

extern	int16 IqRCurLim;
extern	int16 IqRMAX;
extern	int16 fIqRMAX;

extern	int16 UAlphaR;
extern	int16 UBetaR;

extern	int16 UUAR;
extern	int16 UUBR;
extern	int16 UUCR;

extern	int16 ChopReg;

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

extern 	int16 EbyFreqR;

extern  int16 RmR16;
extern  int16 FreqR16;

extern  int   AFSpeedzR16;

extern  int DeltaSpeedR;

extern  int SpeedRz1_16;
extern  int DeltaSpeedR1;

extern	int 	AmplR;
extern	float 	AlphaR;

extern	int32 PowerR;
extern	int16 PowerR16;

extern	void RookerR();
extern	void RegR();


/*******************************************************/
extern	float FourieK[];

extern	int16 PowerUvtr;
extern	int16 PowerByGen;
extern	int16 fPowerByGen;

#endif /* REGS_H_ */
