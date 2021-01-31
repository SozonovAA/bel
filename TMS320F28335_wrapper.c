
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
			DebugInfL *Out)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
IaL = Lpars[0];
IbL = Lpars[1];
IcL = Lpars[2];
ElectricAngleL = Lpars[3];
Ud = Lpars[4];
SpeedL = Lpars[5];

Out[0].IaL=IaL;
Out[0].IbL = IbL;
Out[0].IcL = IcL;
Out[0].IAlphaL = IAlphaL;
Out[0].IBetaL = IBetaL;
Out[0].IdzL = IdzL;
Out[0].IdL = IdL;
Out[0].SIdL = SIdL;
Out[0].DeltaIdOldL = DeltaIdOldL;
Out[0].DeltaIdL = DeltaIdL;
Out[0].UUdL = UUdL;
Out[0].IqzL = IqzL;
Out[0].IqL = IqL;
Out[0].SIqL = SIqL;
Out[0].DeltaIqOldL = DeltaIqOldL;
Out[0].DeltaIqL = DeltaIqL;
Out[0].UUqL = UUqL;
Out[0].UdSIL = UdSIL;
Out[0].UqSIL = UqSIL;
Out[0].E_ampL = E_ampL;
Out[0].fE_ampL = fE_ampL;
Out[0].UAlphaSIL = UAlphaSIL;
Out[0].UBetaSIL = UBetaSIL;
Out[0].DeltaIAlphaL = DeltaIAlphaL;
Out[0].DeltaIBetaL = DeltaIBetaL;
Out[0].OldIAlphaL = OldIAlphaL;
Out[0].OldIBetaL = OldIBetaL;
Out[0].EAlphaInstL = EAlphaInstL;
Out[0].EBetaInstL = EBetaInstL;
Out[0].E_MaxL = E_MaxL;
Out[0].E_LineL = E_LineL;
Out[0].Ez_ampL = Ez_ampL;
Out[0].SEL = SEL;
Out[0].IqLCurLim = IqLCurLim;
Out[0].IqLMAX = IqLMAX;
Out[0].fIqLMAX = fIqLMAX;
Out[0].UAlphaL = UAlphaL;
Out[0].UBetaL = UBetaL;
Out[0].UUAL = UUAL;
Out[0].UUBL = UUBL;
Out[0].UUCL = UUCL;
Out[0].ChopReg = ChopReg;
Out[0].UUqzL = UUqzL;
Out[0].fUmL = fUmL;
Out[0].UmL = UmL;
Out[0].DeltaIdzL = DeltaIdzL;
Out[0].dEL = dEL;
Out[0].sdEL = sdEL;
Out[0].UkdL = UkdL;
Out[0].UkqL = UkqL;
Out[0].ThetaSlipL = ThetaSlipL;
Out[0].fThetaL = fThetaL;
Out[0].EbyFreqL = 0;//EbyFreqL;
Out[0].LmL16 = 0;//LmL16;
Out[0].FreqL16 = 0;//FreqL16;
Out[0].AFSpeedzL16 = AFSpeedzL16;
Out[0].DeltaSpeedL = DeltaSpeedL;
Out[0].SpeedLz1_16 = SpeedLz1_16;
Out[0].DeltaSpeedL1 = DeltaSpeedL1;
Out[0].PowerL = PowerL;
Out[0].PowerL16 = PowerL16;
Out[0].Iaz = Iaz;
Out[0].Ibz = Ibz;
Out[0].Icz = Icz;
Out[0].IAlphaz = IAlphaz;
Out[0].Ibetaz = Ibetaz;
Out[0].ImL = ImL;
Out[0].iffL = iffL;
Out[0].IfRMSL = IfRMSL;
Out[0].AmplL = AmplL;
Out[0].AlphaL = AlphaL;


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


