
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

#include "TMS320F28335_bus.h"

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include "BELAZ_450_DRIVE\include\REGs.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 7
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void TMS320F28335_Outputs_wrapper(const real_T *Lpars,
			const real_T *Rpars,
			const real_T *FromKabine,
			real_T *PWM,
			DebugInfL *Out_L,
			DebugInfR *Out_R)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
IaL = Lpars[0];
IbL = Lpars[1];
IcL = Lpars[2];
ElectricAngleL = Lpars[3];
Ud = Lpars[4];
SpeedL = Lpars[6];

IaR = Rpars[0];
IbR = Rpars[1];
IcR = Rpars[2];
ElectricAngleR = Rpars[3];
Ud = Rpars[4];
SpeedR = Rpars[6];

Out_L[0].IaL=IaL;
Out_L[0].IbL = IbL;
Out_L[0].IcL = IcL;
Out_L[0].IAlphaL = IAlphaL;
Out_L[0].IBetaL = IBetaL;
Out_L[0].IdzL = IdzL;
Out_L[0].IdL = IdL;
Out_L[0].SIdL = SIdL;
Out_L[0].DeltaIdOldL = DeltaIdOldL;
Out_L[0].DeltaIdL = DeltaIdL;
Out_L[0].UUdL = UUdL;
Out_L[0].IqzL = IqzL;
Out_L[0].IqL = IqL;
Out_L[0].SIqL = SIqL;
Out_L[0].DeltaIqOldL = DeltaIqOldL;
Out_L[0].DeltaIqL = DeltaIqL;
Out_L[0].UUqL = UUqL;
Out_L[0].UdSIL = UdSIL;
Out_L[0].UqSIL = UqSIL;
Out_L[0].E_ampL = E_ampL;
Out_L[0].fE_ampL = fE_ampL;
Out_L[0].UAlphaSIL = UAlphaSIL;
Out_L[0].UBetaSIL = UBetaSIL;
Out_L[0].DeltaIAlphaL = DeltaIAlphaL;
Out_L[0].DeltaIBetaL = DeltaIBetaL;
Out_L[0].OldIAlphaL = OldIAlphaL;
Out_L[0].OldIBetaL = OldIBetaL;
Out_L[0].EAlphaInstL = EAlphaInstL;
Out_L[0].EBetaInstL = EBetaInstL;
Out_L[0].E_MaxL = E_MaxL;
Out_L[0].E_LineL = E_LineL;
Out_L[0].Ez_ampL = Ez_ampL;
Out_L[0].SEL = SEL;
Out_L[0].IqLCurLim = IqLCurLim;
Out_L[0].IqLMAX = IqLMAX;
Out_L[0].fIqLMAX = fIqLMAX;
Out_L[0].UAlphaL = UAlphaL;
Out_L[0].UBetaL = UBetaL;
Out_L[0].UUAL = UUAL;
Out_L[0].UUBL = UUBL;
Out_L[0].UUCL = UUCL;
Out_L[0].ChopReg = ChopReg;
Out_L[0].UUqzL = UUqzL;
Out_L[0].fUmL = fUmL;
Out_L[0].UmL = UmL;
Out_L[0].DeltaIdzL = DeltaIdzL;
Out_L[0].dEL = dEL;
Out_L[0].sdEL = sdEL;
Out_L[0].UkdL = UkdL;
Out_L[0].UkqL = UkqL;
Out_L[0].ThetaSlipL = ThetaSlipL;
Out_L[0].fThetaL = fThetaL;
Out_L[0].EbyFreqL = 0;//EbyFreqL;
Out_L[0].LmL16 = 0;//LmL16;
Out_L[0].FreqL16 = 0;//FreqL16;
Out_L[0].AFSpeedzL16 = AFSpeedzL16;
Out_L[0].DeltaSpeedL = DeltaSpeedL;
Out_L[0].SpeedLz1_16 = SpeedLz1_16;
Out_L[0].DeltaSpeedL1 = DeltaSpeedL1;
Out_L[0].PowerL = PowerL;
Out_L[0].PowerL16 = PowerL16;
Out_L[0].Iaz = Iaz;
Out_L[0].Ibz = Ibz;
Out_L[0].Icz = Icz;
Out_L[0].IAlphaz = IAlphaz;
Out_L[0].Ibetaz = Ibetaz;
Out_L[0].ImL = ImL;
Out_L[0].iffL = iffL;
Out_L[0].IfRMSL = IfRMSL;
Out_L[0].AmplL = AmplL;
Out_L[0].AlphaL = AlphaL;

Out_R[0].IaR = IaR;
Out_R[0].IbR = IbR;
Out_R[0].IcR = IcR;
Out_R[0].IAlphaR = IAlphaR;
Out_R[0].IBetaR = IBetaR;
Out_R[0].IdzR = IdzR;
Out_R[0].IdR = IdR;
Out_R[0].SIdR = SIdR;
Out_R[0].DeltaIdOldR = DeltaIdOldR;
Out_R[0].DeltaIdR = DeltaIdR;
Out_R[0].UUdR = UUdR;
Out_R[0].IqzR = IqzR;
Out_R[0].IqR = IqR;
Out_R[0].SIqR = SIqR;
Out_R[0].DeltaIqOldR = DeltaIqOldR;
Out_R[0].DeltaIqR = DeltaIqR;
Out_R[0].UUqR = UUqR;
Out_R[0].UdSIR = UdSIR;
Out_R[0].UqSIR = UqSIR;
Out_R[0].E_ampR = E_ampR;
Out_R[0].fE_ampR = fE_ampR;
Out_R[0].UAlphaSIR = UAlphaSIR;
Out_R[0].UBetaSIR = UBetaSIR;
Out_R[0].DeltaIAlphaR = DeltaIAlphaR;
Out_R[0].DeltaIBetaR = DeltaIBetaR;
Out_R[0].OldIAlphaR = OldIAlphaR;
Out_R[0].OldIBetaR = OldIBetaR;
Out_R[0].EAlphaInstR = EAlphaInstR;
Out_R[0].EBetaInstR = EBetaInstR;
Out_R[0].E_MaxR = E_MaxR;
Out_R[0].E_LineR = E_LineR;
Out_R[0].Ez_ampR = Ez_ampR;
Out_R[0].SER = SER;
Out_R[0].IqRCurLim = IqRCurLim;
Out_R[0].IqRMAX = IqRMAX;
Out_R[0].fIqRMAX = fIqRMAX;
Out_R[0].UAlphaR = UAlphaR;
Out_R[0].UBetaR = UBetaR;
Out_R[0].UUAR = UUAR;
Out_R[0].UUBR = UUBR;
Out_R[0].UUCR = UUCR;
Out_R[0].ChopReg = ChopReg;
Out_R[0].UUqzR = UUqzR;
Out_R[0].fUmR = fUmR;
Out_R[0].UmR = UmR;
Out_R[0].DeltaIdzR = DeltaIdzR;
Out_R[0].dUUqR = dUUqR;
Out_R[0].sdUUqR = sdUUqR;
Out_R[0].UkdR = UkdR;
Out_R[0].UkqR = UkqR;
Out_R[0].ThetaSlipR = ThetaSlipR;
Out_R[0].fThetaR = fThetaR;
Out_R[0].EbyFreqR = 0;//EbyFreqR;
Out_R[0].RmR16 = 0;//RmR16;
Out_R[0].FreqR16 = 0;//FreqR16;
Out_R[0].AFSpeedzR16 = AFSpeedzR16;
Out_R[0].DeltaSpeedR = DeltaSpeedR;
Out_R[0].SpeedRz1_16 = SpeedRz1_16;
Out_R[0].DeltaSpeedR1 = DeltaSpeedR1;
Out_R[0].AmplR = AmplR;
Out_R[0].AlphaR = AlphaR;
Out_R[0].PowerR = PowerR;
Out_R[0].PowerR16 = PowerR16;

SpeedLz = FromKabine[0]*20;
SpeedRz = FromKabine[0]*20;

RegL();
RegR();

PWM[0] = UUAL;
PWM[1] = UUBL;
PWM[2] = UUCL;
PWM[3] = UUAR;
PWM[4] = UUBR;
PWM[5] = UUCR;
PWM[6] = ChopReg;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


