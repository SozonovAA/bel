
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



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include "driver.h"
#include "math_convert.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void drive_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Custom Start code goes here.
 */
pwm_a=0;
pwm_b=0;
pwm_c=0;
flag_start=0;
flag_start_o=0;
flag_start_v=0;
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void drive_Outputs_wrapper(const real_T *speed_z,
			const real_T *feedbacks,
			real_T *U_to_pwm,
			real_T *test_data)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
 */
//скалярное управление

//generat_sine();

//векторное управление
//vect_drive(double Ia, double Ib, double Ic, double speed, double angle_r, double speeed_z)
vect_drive(feedbacks[0], feedbacks[1], feedbacks[2], feedbacks[3], feedbacks[4], speed_z, feedbacks[5]);

U_to_pwm[0]=pwm_a;
U_to_pwm[1]=pwm_b;
U_to_pwm[2]=pwm_c;


test_data[0]=diagn_data.Id_test;
test_data[1]=diagn_data.Iq_test;
test_data[2]=diagn_data.theta_test;
test_data[3]=diagn_data.alpha_test;
test_data[4]=diagn_data.Id_z_test;
test_data[5]=diagn_data.Iq_z_test;
test_data[6]=diagn_data.Uud_sqr_test;
test_data[7]=diagn_data.Uud_test;
test_data[8]=diagn_data.Uuq_test;
test_data[9]=diagn_data.Uu_ampl_test;
test_data[10]=diagn_data.Uuq_pred_test;
test_data[11]=diagn_data.test_signal;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


