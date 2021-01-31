
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
			BusObject *Out)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
IaL = Lpars[0];
IbL = Lpars[1];
IcL = Lpars[2];
ElectricAngleL = Lpars[3];
Ud = Lpars[4];
SpeedL = Lpars[5];

Out[0].IaL=IaL;
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


