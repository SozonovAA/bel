#include "hfa.h"

void _PAUSE(Uint32 step);
int GetMIN(int A,int B);
int GetMAX(int A,int B);
int CountUP(int *C,int V);
void Clark(int16 A,int16 B,int16 C,int16 *Alpha,int16 *Beta);
void InvClark(int16 *A,int16 *B,int16 *C,int16 Alpha,int16 Beta);
void Park(int16 Alpha,int16 Beta,int16 *D,int16 *Q,float Theta);
void InvPark(int16 *Alpha,int16 *Beta,int16 D,int16 Q,float Theta);
void MagneticSaturation(int Id,float *Lm);
void HeatWinding(float *Rs);
void RadianLimit(float *Var);
void MinMaxLimitInt(int16 MIN,int16 MAX,int16 *Var);
void MinMaxLimitFloat(int16 MIN,int16 MAX,float *Var);
int16 ConvertVParamToSI(int16 Param);
int16 GetHypByLegs(int16 Leg1,int16 Leg2);
int16 GetCatByHypNLeg(int16 Leg1,int16 Hyp);
int16 ConvertVParamToRU(int16 Param);

#pragma CODE_SECTION(_PAUSE,"ramfuncs")
#pragma CODE_SECTION(GetMIN,"ramfuncs")
#pragma CODE_SECTION(GetMAX,"ramfuncs")
#pragma CODE_SECTION(CountUP,"ramfuncs")
#pragma CODE_SECTION(Clark,"ramfuncs")
#pragma CODE_SECTION(InvClark,"ramfuncs")
#pragma CODE_SECTION(Park,"ramfuncs")
#pragma CODE_SECTION(InvPark,"ramfuncs")
#pragma CODE_SECTION(MagneticSaturation,"ramfuncs")
#pragma CODE_SECTION(HeatWinding,"ramfuncs")
#pragma CODE_SECTION(RadianLimit,"ramfuncs")
#pragma CODE_SECTION(MinMaxLimitInt,"ramfuncs")
#pragma CODE_SECTION(MinMaxLimitFloat,"ramfuncs")
#pragma CODE_SECTION(ConvertVParamToSI,"ramfuncs")
#pragma CODE_SECTION(GetHypByLegs,"ramfuncs")
#pragma CODE_SECTION(GetCatByHypNLeg,"ramfuncs")
#pragma CODE_SECTION(ConvertVParamToRU,"ramfuncs")


/*****************************************************************/

void _PAUSE(Uint32 step)
{
	Uint32 i;
	for(i=0;i<=step;i++)
	{
		asm("NOP");
	}
}

/*****************************************************************/

int GetMIN(int A,int B){

	if(A < B) return(A);
	else return(B);
}

/*****************************************************************/

int GetMAX(int A,int B){

	if(A > B) return(A);
	else return(B);
}

/*****************************************************************/

int CountUP(int *C,int V){

	*C++;

	if(*C > V) *C=0;

	if(*C == V)
	return(true);
	else
	return(0);

}
/***************************************************************/
/* ABC ----> Alpha/Beta ---> DQ ------> Alpha/Beta -------> ABC*/
/* ____Clark____________Park____InvPark ___________InvClark____*/
/***************************************************************/

void Clark(int16 A,int16 B,int16 C,int16 *Alpha,int16 *Beta)
{
	//ABC ----> Alpha/Beta

	*Alpha = A;
	*Beta  = I_((F_(B) - F_(C))/_3SQRT2);

}

void InvClark(int16 *A,int16 *B,int16 *C,int16 Alpha,int16 Beta)
{
	//Alpha/Beta -------> ABC

	*A = Alpha;
	*B = (_3SQRT2*Beta - Alpha)/2;
	*C = -(_3SQRT2*Beta + Alpha)/2;

}

void Park(int16 Alpha,int16 Beta,int16 *D,int16 *Q,float Theta)
{
	//Alpha/Beta ---> DQ

	*D = F_(Beta)*sin(Theta) + F_(Alpha)*cos(Theta);
	*Q = F_(Beta)*cos(Theta) - F_(Alpha)*sin(Theta);

}

void InvPark(int16 *Alpha,int16 *Beta,int16 D,int16 Q,float Theta)
{
	//DQ ------> Alpha/Beta

	*Alpha = F_(D)*cos(Theta) - F_(Q)*sin(Theta);
	*Beta  = F_(D)*sin(Theta) + F_(Q)*cos(Theta);

}

/*****************************************************************/

void RadianLimit(float *Var)
{

	if(*Var > 2*M_PI) *Var -= 2*M_PI;
	if(*Var < 0) *Var += 2*M_PI;

}

/*****************************************************************/

void MinMaxLimitInt(int16 MIN,int16 MAX,int16 *Var)
{

	if(*Var >= MAX) *Var = MAX;
	if(*Var <= MIN) *Var = MIN;

}

/*****************************************************************/

void MinMaxLimitFloat(int16 MIN,int16 MAX,float *Var)
{

	if(*Var >= MAX) *Var = MAX;
	if(*Var <= MIN) *Var = MIN;

}

/*****************************************************************/

void MagneticSaturation(int Id,float *Lm)
{

	/*if(Id < 200 || *Lm < 0.0067) *Lm = 0.0067;
	if(Id < 700 && Id > 200) *Lm = (2.68 - 0.002262*Id)/335;
	if(Id > 700) *Lm = (1.345 - 0.00065*Id)/287;
	if(*Lm < 0.0022) *Lm = 0.0022;*/

	Id = abs(Id);

	if(*Lm < 0.0067) *Lm = 0.0067;
	if(Id < 495 && Id >= 145) *Lm = -0.00001*Id+0.008;
	if(Id < 1000 && Id >= 495) *Lm = -0.0000032*Id+0.0046;
	if(*Lm < 0.0022) *Lm = 0.0022;

}

/*****************************************************************/

void HeatWinding(float *Rs)
{
	int TempStator=0;//must be global

	*Rs = (50 + TempStator/5)/10000;

}

/*****************************************************************/

int16 ConvertVParamToSI(int16 Param)
{

	Param = (Param / F_(HALF_PWM_HEIGHT))*(Udz/2.0);

	return(Param);
}

/*****************************************************************/

int16 GetHypByLegs(int16 Leg1,int16 Leg2){

	int Hyp=0;

	Hyp = _IQ1sqrt((L_(Leg1)*L_(Leg1) + L_(Leg2)*L_(Leg2)) >> 1);

	return(Hyp);

}

/*****************************************************************/

int16 GetCatByHypNLeg(int16 Leg1,int16 Hyp){

	int Leg2=0;

	int32 H=0;
	int32 leg=0;

	H = (int32)(Hyp)*(int32)(Hyp);
	leg = (int32)(Leg1)*(int32)(Leg1);

	Leg2 = sqrt(H - leg);

	return(Leg2);

}

/*****************************************************************/

int16 ConvertVParamToRU(int16 Param)
{

	Param = (Param / F_((Ud >> 1)))*HALF_PWM_HEIGHT;

	return(Param);

}

/*****************************************************************/

float FourieK[80]={
0.999721447,\
0.999444048,\
0.999167795,\
0.998892681,\
0.9986187  ,\
0.999335344,\
1.000049054,\
1.000759848,\
1.001467742,\
1.002172756,\
1.00305264 ,\
1.003929267,\
1.004802657,\
1.005672825,\
1.006539791,\
1.00770098 ,\
1.008857705,\
1.01000999 ,\
1.011157862,\
1.012301346,\
1.013763329,\
1.01521957 ,\
1.016670102,\
1.018114959,\
1.019554173,\
1.021123501,\
1.022687139,\
1.024245118,\
1.02579747 ,\
1.027344224,\
1.029441787,\
1.031531015,\
1.033611958,\
1.035684666,\
1.037749187,\
1.039998286,\
1.042239365,\
1.044472467,\
1.046697635,\
1.048914911,\
1.051610329,\
1.054295872,\
1.056971594,\
1.059637548,\
1.062293788,\
1.065296401,\
1.068288054,\
1.07126881 ,\
1.074238726,\
1.077197862,\
1.080801626,\
1.084391889,\
1.087968726,\
1.091532212,\
1.095082423,\
1.09909042 ,\
1.103084349,\
1.107064284,\
1.111030298,\
1.114982464,\
1.119618515,\
1.124238309,\
1.128841931,\
1.133429467,\
1.138001001,\
1.143383307,\
1.148746373,\
1.154090301,\
1.159415194,\
1.164721154,\
1.170764914,\
1.176787839,\
1.182790035,\
1.18877161 ,\
1.194732669,\
1.201866624,\
1.208975936,\
1.216060732,\
1.223121138,\
1.230157281,\
};

//EOF


















