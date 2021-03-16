
#include <stdlib.h>
#include <stdio.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "math.h"
#include "gpio_def.h"
#include "IQmathLib.h"
#include "REGs.h"

#include "Flash2833x_API_Library.h"
#include "ECAT_Common.h"
#include "ECAT_DATA.h"
#include "altera_regs.h"

//#include "eCAP_defines.h"
#include "posspeed.h"
#include "MashineParams.h"
#include "eCAP_defines.h"

//**************************************************************************//
//***************                                        *******************//
//***************              HEADERS FOR ALL           *******************//
//***************                                        *******************//
//**************************************************************************//

typedef char BYTE;

//**************************************************************************//
//***************                                        *******************//
//***************              DEFINES           		 *******************//
//***************                                        *******************//
//**************************************************************************//

#define X1		GS.BOOL_MACRO.bit.MskAEx		//+
#define X2		GS.BOOL_MACRO.bit.MskIL			//+
#define X3		GS.BOOL_MACRO.bit.MskIR			//+
#define X4		GS.BOOL_MACRO.bit.MskICH		//+

#define X5		GS.BOOL_MACRO.bit.EnEx			//+
#define X6		GS.BOOL_MACRO.bit.EnIL			//+
#define X7		GS.BOOL_MACRO.bit.EnIR			//+
#define X8		GS.BOOL_MACRO.bit.FExDone		//+

#define X9		GS.BOOL_MACRO.bit.UdExMin		//-
#define X10		GS.BOOL_MACRO.bit.UdInvStart	//+
#define X11		GS.BOOL_MACRO.bit.UdInvStop		//+
#define X12		GS.BOOL_MACRO.bit.UdChStop		//+

#define X13		GS.BOOL_MACRO.bit.ManContr		//+
#define X14		GS.BOOL_MACRO.bit.Start			//+
#define X15		otf.N							//+
#define X16		GS.BOOL_MACRO.bit.ExTimeOver	//+

#define X17		data_from_KK->DIN.bit.bHANDLE_BRAKE

/*
 * 	union _UC		COMMANDS;
	union _UC		MAIN_COMMANDS;
	union _UFLT1 	FAULTS1;
	union _UFLT2 	FAULTS2;
	union _UFLTC 	FAULTSC;
	union _UFLTD 	FAULTSDL;
	union _UFLTD 	FAULTSDR;
	union _UHB1 	HELP_BITS;
	union _US  		STATE;
	union _UOTF  	OTF;
	union _UBM  	BOOL_MACRO;
 */

#define ARCHIVE_SIZE					10
#define MAX_ARCHIVE_NUMBER				LENGHT_ARCHIVE_MEMORY/ARCHIVE_SIZE

#define NUM_OF_VARIABLES 				100L
#define LENGHT_ARRAY 	 				512L
#define STEPS_AFTER_ALARM  				100L

#define MAX_ALARM_NUMBER				FULL_ARRAY_MEMORY/(NUM_OF_VARIABLES*LENGHT_ARRAY)

//----------------------------------------------------------------


#define MIN_PWM					1000
#define MAX_PWM					(25000-MIN_PWM)


#define mcmd					GS.MAIN_COMMANDS.bit

#define f1						GS.FAULTS1.bit
#define f2						GS.FAULTS2.bit
#define fc						GS.FAULTSC.bit
#define fdl						GS.FAULTSDL.bit
#define fdr						GS.FAULTSDR.bit

#define hb						GS.HELP_BITS.bit
#define st						GS.STATE.bit

#define otf						GS.OTF.bit
#define bm						GS.BOOL_MACRO.bit

#define ANY_FAULT 				(GS.FAULTSD_INV.all || GS.FAULTSD_CHOP.all || GS.FAULTSC.all || GS.FAULTS1.all ||GS.FAULTS2.all)
#define ANY_IMP					(RIGHT_INV_CONTROL_PIN || LEFT_INV_CONTROL_PIN || EX_CONTROL_PIN || CHOP_CONTROL_PIN)

//VALUES
#define FREQ_CPU				150000000
#define HALF_FREQ_CPU			75000000

#define HALF_PWM_HEIGHT			12500

#define SECOND					1500

#define SOME_VALUE				1

#define START					1
#define STOP					0

#define ENABLE					1
#define DISABLE					0

#define SWITCH_ON				1
#define SWITCH_OFF				0

#define FORWARD					1
#define BACK					0

#define DRIVE					1
#define REVERSE					2
#define NEUTRAL					0

#ifndef true
	#define true					1
#endif

#ifndef false
	#define false					1
#endif

//PINS
#define RIGHT_INV_CONTROL_PIN	DAT59
#define LEFT_INV_CONTROL_PIN	DAT14
#define EX_CONTROL_PIN			DAT16
#define CHOP_CONTROL_PIN		DAT15

//DIN`S
#define KM_Switch_ON 			altera_regs.DOUT.bit.KM=1
#define KM_Switch_OFF 			altera_regs.DOUT.bit.KM=0
#define KM_Switch 				altera_regs.DOUT.bit.KM
#define QF_Switch_OFF 			altera_regs.DOUT.bit.QF_OFF=1
#define QF_Switch 				altera_regs.DOUT.bit.QF_OFF

#define dt						0.000666

// MATH CONSTANT
#define M_PI        			3.14159
#define _3SQRT2 				1.73205
#define _2SQRT2 				1.41421
#define _1DIV3SQRT2				0.57735


#define _2PIdiv3				2.09439
#define _4PIdiv3				4.18878
#define CONST					28		//U/f=CONST

// MACRO FUNCS
#define F_(A) 					(float)A
#define L_(A) 					(long)A
#define UI_(A) 					(Uint16)A
#define I_(A) 					(int16)A

#define SET(A)   				A=1
#define UNSET(A)  				A=0

#define PON(A)   				SET(A)
#define POFF(A)  				UNSET(A)

#define ALLOW(A) 				SET(A)
#define BAN(A) 					UNSET(A)

#define SET_ERROR(A)   			SET(A)

#define CLEAR_COUNTER(A)  		UNSET(A)
#define CLEAR_ERRORS(A)  		UNSET(A)
#define CLEAR_COMMAND(A)  		UNSET(A)

#define GetRMS(AMP)				(AMP)/=_2SQRT2
#define GetAMP(RMS)				(RMS)*=_2SQRT2

#define AF(A,B,C) 				*A+=(B-(*A))/C

#define WAIT_FEW_STEPS			asm(" NOP");asm(" NOP");asm(" NOP");asm(" NOP");asm(" NOP");asm(" NOP")
#define WAIT(A,B)					for(A=0;A<B;A++) {A=A;}
//**************************************************************************//
//***************                                        *******************//
//***************              		VFP           		 *******************//
//***************                                        *******************//
//**************************************************************************//

//--------------------main.c-------------------------------
extern	Uint16 bit_place;
extern	char dsp_ip_addr[];
extern 	Uint16 state;
extern 	Uint16 fault_event;

extern 	int IZ;
extern 	int I;
extern 	int KP;
extern 	int KI;
extern 	int Summ;

extern 	Uint16 Period2;

extern 	Uint16 Debug;

extern	Uint16 *state_work_prg;

extern	void  QEP_InitL(void);
extern	void  QEP_InitR(void);

//--------------------adc_interrupt.c---------------------
extern 	int16 Ki;
extern 	int16 Kp;

extern 	int16 Ugen;
extern 	int16 Igen;
extern 	int16 Ud;
extern 	int16 Iv;

extern 	Uint16 PosL;
extern 	int16 dPosL;
extern 	int16 OldPosL;
extern 	Uint16 LookAtSpeed;
extern 	int16 RPM;
extern 	Uint16 ElecAngleL;

extern 	Uint32 PRDLAT_L;
extern 	Uint16 QTMR;
extern 	Uint16 CNTR;
extern 	Uint32 OF;

extern 	int16 Hz;
extern 	int16 fHz;

extern		void InitADC();

//--------------------Sliders.c----------------------------

extern		void SlidersMem();

//--------------------array.c----------------------------

extern		Uint16 array_step;

extern 		Uint32 AAMetaData[];

extern 		struct SCUR_ARRAY CUR_ARRAY;

extern		void write_array();
extern		void CopyToFram();
//---------------------vals.c----------------------------

extern		Uint16 AddrArray[NUM_OF_VARIABLES];

extern		void InitAddrArray();

//---------------------RVG.c-----------------------------

extern 	Uint32 rvg_cnt;
extern 	Uint16 synch_cnt;
extern 	int16 freq_3_harm;
extern 	Uint16 phi_int;
extern 	Uint16 CTR_CAP4;
extern 	Uint16 CTR_CAP1;
extern 	Uint16 CTR_CAP2;
extern 	Uint32 PRD;
extern 	Uint32 DELTA;
extern	Uint16 alpha16;
extern	Uint16 CAP1_REG;
extern	int16 DeltaCAP16;
extern	int16 OldCAP16;

extern	Uint16 Cap1Cap1;
extern	Uint16 Cap1Cap2;
extern	Uint16 Cap1Cap3;
extern	Uint16 Cap1Cap4;

extern	Uint16 WrongSynchCount;
extern	int16 fPRD16;

extern	int16 Udz;
extern	int16 dUd;

extern	float fUd;

extern	int16 KpRVG16;
extern	int16 SummRVG16;

extern		void RVG();

//---------------------I2C_DACS.c------------------------

extern 		void i2cDacs();

//-------------------------SpeedL.c-----------------------

extern	Uint16 ThetaL;
extern	float fOmegaL;
extern	int16 SpeedL;
extern	int16 SpeedLz;

//-------------------------SpeedR.c-----------------------

extern	Uint16 ThetaR;
extern	float fOmegaR;
extern	int16 SpeedR;
extern	int16 SpeedRz;

extern		void SpeedAndAngleL();

//-------------------------RegL.c------------------------

extern		void SpeedAndAngleR();

//-------------------------RegR.c------------------------

extern 	int16 IaR;
extern 	int16 IbR;
extern 	int16 IcR;

extern 	int16 IdzR;
extern 	int16 IdR;
extern 	int16 IqzR;
extern 	int16 IqR;

extern 	int16 UUAR;
extern 	int16 UUBR;
extern 	int16 UUCR;


extern		void RegR();

//-------------------------Dizel.c-----------------------

extern 	Uint16 RPMDiz;
extern 	int32 PowerMax;
extern 	Uint16 PowerMax16;

extern		void DizelOutPowerMax();

//-------------------------func.c------------------------

extern		void _PAUSE(Uint32 step);
extern		int GetMIN(int A,int B);
extern		int GetMAX(int A,int B);
extern		int CountUP(int *C,int V);
extern		void Clark(int16 A,int16 B,int16 C,int16 *Alpha,int16 *Beta);
extern		void InvClark(int16 *A,int16 *B,int16 *C,int16 Alpha,int16 Beta);
extern		void Park(int16 Alpha,int16 Beta,int16 *D,int16 *Q,float Theta);
extern		void InvPark(int16 *Alpha,int16 *Beta,int16 D,int16 Q,float Theta);
extern		void MagneticSaturation(int Id,float *Lm);
extern		void HeatWinding(float *Rs);
extern		void RadianLimit(float *Var);
extern		void MinMaxLimitInt(int16 MIN,int16 MAX,int16 *Var);
extern		void MinMaxLimitFloat(int16 MIN,int16 MAX,float *Var);
extern		int16 ConvertVParamToSI(int16 Param);
extern		int16 GetHypByLegs(int16 Leg1,int16 Leg2);
extern		int16 GetCatByHypNLeg(int16 Leg1,int16 Hyp);
extern		int16 ConvertVParamToRU(int16 Param);

//--------------------diagnostic.c---------------

extern 	Uint16 CountFEX;

extern 	Uint16 Faults1;
extern 	Uint16 Faults2;
extern 	Uint16 FaultsC;
extern 	Uint16 FaultsDINV;
extern 	Uint16 FaultsDCHOP;

extern		void ErrorResponse();
extern		void StateMachine();
extern		void Reset();
extern		void FirstStateOfSystem();
extern		void StateOfControlPins();
extern		void CheckN();

//--------------------ethernet.c-----------------

extern	Uint16 *MAC;

extern		void ethernet();
extern		void net();
extern		void WriteEEPROM(unsigned int last_word_ip );



//--------------------DSP2833x_Pwm_init.c

extern		void InitEPwm1();
extern		void InitEPwm2();
extern		void InitEPwm3();
extern		void InitEPwm4();
extern		void InitEPwm5();
extern		void InitEPwm6();

//--------------------AsynchMashine.c

extern		void CalcCurMParms(struct MashineParam *M);
extern		void StaticMparams(struct MashineParam *M);

//--------------------Uf_const.c

extern 		int UDSI;

extern		int iOmegaT;
extern		float Freqz;

extern		int16 UZeroL;

extern		void Uf_Const();
extern		void HandleReg(int16 *A,int16 *B,int16 *C,int *Ampl, float *Alpha);

//--------------------timer0_interrupt.c

extern		void create_state_array(void);
extern		void read_request_var(void);

//---------------EPIC.c
extern void AssemblyECIPMess();
extern sPK12 *ptrPK12;
extern int Drive;
extern int Brake;

//---------------EtherCat
extern struct data_for_transmit *data_from_KK;
extern struct data_for_receive *data_for_KK;



//**************************************************************************//
//***************                                        *******************//
//***************              STRUCTURES          		 *******************//
//***************                                        *******************//
//**************************************************************************//

#define	M_L_IMP_F1		0x007F	/*0000 0000 0111 1111*/
#define	M_R_IMP_F1		0x7F00	/*0111 1111 0000 0000*/
#define	M_EX_IMP_F1		0x0000	/*0000 0000 0000 0000*/
#define	M_CH_IMP_F1		0x0000	/*0000 0000 0000 0000*/
#define	M_QF_OFF_F1		0x0000	/*0000 0000 0000 0000*/

#define	M_L_IMP_F2		0x4011	/*0100 0000 0001 0001*/
#define	M_R_IMP_F2		0x4011	/*0100 0000 0001 0001*/
#define	M_EX_IMP_F2		0x409D	/*0100 0000 1001 1101*/
#define	M_CH_IMP_F2		0x4060	/*0100 0000 0110 0000*/
#define	M_QF_OFF_F2		0x401D	/*0100 0000 0001 1101*/

#define	M_L_IMP_FC		0x0047	/*0000 0000 0100 0111*/
#define	M_R_IMP_FC		0x0078	/*0000 0000 0111 1000*/
#define	M_EX_IMP_FC		0x0340	/*0000 0011 0100 0000*/
#define	M_CH_IMP_FC		0x0000	/*0000 0000 0000 0000*/
#define	M_QF_OFF_FC		0x0340	/*0000 0011 0100 0000*/

#define	M_L_IMP_FDI		0x0FFF	/*0000 1111 1111 1111*/
#define	M_R_IMP_FDI		0x0FFF	/*0000 1111 1111 1111*/
#define	M_EX_IMP_FDI	0x0FFF	/*0000 1111 1111 1111*/
#define	M_CH_IMP_FDI	0x0000	/*0000 0000 0000 0000*/
#define	M_QF_OFF_FDI	0x0FFF	/*0000 1111 1111 1111*/

#define	M_L_IMP_FDCH	0x003F	/*0000 0000 0011 1111*/
#define	M_R_IMP_FDCH	0x003F	/*0000 0000 0011 1111*/
#define	M_EX_IMP_FDCH	0x003F	/*0000 0000 0011 1111*/
#define	M_CH_IMP_FDCH	0x003F	/*0000 0000 0011 1111*/
#define	M_QF_OFF_FDCH	0x003F	/*0000 0000 0011 1111*/


//______________________FAULTS1

struct Faults1{
unsigned IAL_ZERO:1;	//0		Нет нуля тока фазы А левого двигателя
unsigned IBL_ZERO:1;	//1		Нет нуля тока фазы В левого двигателя
unsigned ICL_ZERO:1;	//2		Нет нуля тока фазы С левого двигателя
unsigned IAL:1;			//3 	Превышение тока фазы А левого двигателя

unsigned IBL:1;			//4 	Превышение тока фазы В левого двигателя
unsigned ICL:1;			//5 	Превышение тока фазы С левого двигателя
unsigned nU_L:1;		//6 	Превышение скорости левый двигатель
unsigned rsrv7:1;		//7

unsigned IAR_ZERO:1;	//8		Нет нуля тока фазы А правого двигателя
unsigned IBR_ZERO:1;	//9		Нет нуля тока фазы В правого двигателя
unsigned ICR_ZERO:1;	//10	Нет нуля тока фазы С правого двигателя
unsigned IAR:1;			//11	Превышение тока фазы А правого двигателя

unsigned IBR:1;			//12	Превышение тока фазы В правого двигателя
unsigned ICR:1;			//13	Превышение тока фазы С правого двигателя
unsigned nU_R:1;		//14	Превышение скорости правый двигатель
unsigned rsrv15:1;		//15
};

union _UFLT1
{
   Uint16      		all;
   struct Faults1  	bit;
};

//______________________FAULTS2

struct Faults2{
unsigned Ud:1;			//0		Превышение напряжения в звене пост. тока
unsigned Ugen:1;		//1		Превышение напряжения генератора
unsigned Iv:1;			//2		Превышение тока возбуждения генератора
unsigned Igen:1;		//3		Превышение тока генератора

unsigned SHORT:1;		//4		КЗ в звене пост. тока
unsigned Gercon1:1;		//5		Геркон1
unsigned Gercon2:1;		//6		Геркон2
unsigned EX:1;			//7		Нет возбуждения

unsigned QF_EX:1;		//8		Отключен силовой автомат
unsigned QF_pre_EX:1;	//9		Отключен автомат предв. возб.
unsigned DRIVER:1;		//10	Обобщенная ошибка по драйверам
unsigned COMP:1;		//11	Обобщенная ошибка по компараторам

unsigned VENT_D:1;		//12	Драйвер вентиляторов
unsigned VENT_ERR:1;	//13	Ошибка по вентиляторам
unsigned PIP:1;			//14	Исправность ПИПа
unsigned rsrv15:1;		//14	Резерв
};

union _UFLT2
{
   Uint16      		all;
   struct Faults2  	bit;
};

//______________________FAULTSC

struct FaultsC{
unsigned IAL:1;			//0	Компаратор фазы А левый инвертор
unsigned IBL:1;			//1 Компаратор фазы B левый инвертор
unsigned ICL:1;			//2 Компаратор фазы С левый инвертор
unsigned IAR:1;			//3 Компаратор фазы А правый инвертор

unsigned IBR:1;			//4 Компаратор фазы B правый инвертор
unsigned ICR:1;			//5 Компаратор фазы С правый инвертор
unsigned Ud:1;			//6 Компаратор напряжения в ЗПТ
unsigned Ugen:1;		//7 Компаратор напряжения генератора

unsigned Iv:1;			//8 Компаратор тока возбуждения
unsigned Igen:1;		//9 Компаратор тока генератора
unsigned rsrv10:1;		//10
unsigned rsrv11:1;		//11

unsigned rsrv12:1;		//12
unsigned rsrv13:1;		//13
unsigned rsrv14:1;		//14
unsigned rsrv15:1;		//15
};

union _UFLTC
{
   Uint16      		all;
   struct FaultsC  	bit;
};

//______________________FAULTSD_INV

struct FaultsD_INV{
unsigned LAH:1;			//0 Драйвер левого инвертора фазы А верхний
unsigned LAL:1;			//1 Драйвер левого инвертора фазы А верхний
unsigned LBH:1;			//2
unsigned LBL:1;			//3

unsigned LCH:1;			//4
unsigned LCL:1;			//5
unsigned RAH:1;			//6
unsigned RAL:1;			//7

unsigned RBH:1;			//8
unsigned RBL:1;			//9
unsigned RCH:1;			//10
unsigned RCL:1;			//11

unsigned rsrv12:1;		//12
unsigned rsrv13:1;		//13
unsigned rsrv14:1;		//14
unsigned rsrv15:1;		//15
};

union _UFLTD_INV
{
   Uint16      		all;
   struct FaultsD_INV 	bit;
};

//______________________FAULTSD_CHOP

struct FaultsD_CHOP{
unsigned CH1:1;			//0
unsigned CH2:1;			//1
unsigned CH3:1;			//2
unsigned CH4:1;			//3

unsigned CH5:1;			//4
unsigned CH6:1;			//5
unsigned rsrv6:1;		//6
unsigned rsrv7:1;		//7

unsigned rsrv8:1;		//8
unsigned rsrv9:1;		//9

unsigned rsrv10:1;		//10
unsigned rsrv11:1;		//11

unsigned rsrv12:1;		//12
unsigned rsrv13:1;		//13
unsigned rsrv14:1;		//14
unsigned rsrv15:1;		//15
};

union _UFLTD_CHOP
{
   Uint16      			all;
   struct FaultsD_CHOP 	bit;
};

//________________________FLAGS1
struct STATE
{

	unsigned ExImp:1;		//0		Импульсы возбуждения
	unsigned LeftImp:1;		//1 	Импульсы левого инвертора
	unsigned RightImp:1;	//2 	Импульсы правого инвертора
	unsigned ChopImp:1;		//3 	Импульсы на чоппер

	unsigned HandleBrake:1;	//4 	Ручник
	unsigned Stab:1;		//5 	Стабилизация скорости
	unsigned FreeRun:1;		//6 	Выбег
	unsigned Drive:1;		//7		Тяга

	unsigned Break:1;		//8		Торможение
	unsigned Pedal:1;		//9		На
	unsigned DriveDirL:1;	//10	Напр. движения левого колеса (1 - вперед, 0 - назад)
	unsigned DriveDirR:1;	//11	Напр. движения правого колеса (1 - вперед, 0 - назад)

	unsigned Synch:1;		//12	Синхронизация возбудителя
	unsigned rsrvd13:1;		//13
	unsigned rsrvd14:1;		//14
	unsigned rsrvd15:1;		//15

};

union _US
{
   Uint16      		all;
   struct STATE  	bit;
};

// MASK_COMMANDS 0000 0010 0011 1000	0x0238
#define MASK_COMMANDS 0x238


union _UC
{
   Uint16      		all;
   struct Commands  bit;
};


struct SHB1 //struct help bits
{
	unsigned InitArray:1;		// 0 инициализация массива адресов
	unsigned alarm_flag:1;		// 1 Флаг по которому массив отсчитает STEPS_AFTER_ALARM точек после его установки, и установит флаг LoadingProcess
	unsigned CopyArrayToFram:1;	// 2 Флаг вызова функции записи инфы из SRAM во FRAM при аварии
	unsigned FaultEvent:1;		// 3 Флаг аварии

	unsigned LoadingProcess:1;	// 4 Флаг передачи массива на ноут
	unsigned CopyProcess:1;		// 5 Флаг процесса копирования из SRAM во FRAM
	unsigned WriteArchive:1;	// 6 Флаг записи архива
	unsigned SCFEX:1; 			// 7 start count first excitation

	unsigned SynchReSynch:1; 	// 8
	unsigned CapIsr:1; 			// 9
	unsigned WriteKoeff:1; 		// 10 Флаг записи коэф во FRAM
	unsigned WriteDacs:1; 		// 11 Флаг записи ЦАПов

	unsigned InitSliderRange:1; // 12 Флаг инициализации диапазона слайдеров
	unsigned CalcShiftCurrent:1;// 13 Флаг замера смещения токовых каналов

};

union _UHB1
{
   Uint16       all;
   struct SHB1  bit;
};

struct BM //struct MACRO bit`s
{
	unsigned MskAEx:1; 		//
	unsigned MskIL:1; 		//
	unsigned MskIR:1; 		//
	unsigned MskICH:1; 		//

	unsigned EnEx:1; 		//
	unsigned EnIL:1; 		//
	unsigned EnIR:1; 		//
	unsigned FExDone:1;		//

	unsigned UdExMin:1; 	//
	unsigned UdInvStart:1; 	//
	unsigned UdInvStop:1; 	//
	unsigned UdChStop:1; 	//

	unsigned ManContr:1; 	//
	unsigned Start:1; 		//
	unsigned N:1; 			//
	unsigned ExTimeOver:1;
};

union _UBM
{
   Uint16       all;
   struct BM  	bit;
};

struct OneTimeFlags
{
	unsigned KM1:1;//accept
	unsigned rsrv1:1;//accept
	unsigned N:1;//accept
	unsigned rsrv3:1;//accept

	unsigned rsrv4:1;
	unsigned rsrv5:1;
	unsigned rsrv6:1;
	unsigned rsrv7:1;

	unsigned rsrv8:1;
	unsigned rsrv9:1;
	unsigned rsrv10:1;
	unsigned rsrv11:1;

	unsigned rsrv12:1;
	unsigned rsrv13:1;
	unsigned rsrv14:1;
	unsigned rsrv15:1;
};

union _UOTF
{
   Uint16      			all;
   struct OneTimeFlags  bit;
};

struct GS_ //GLOBAL_STRUCT
{
	union _UHB1 		HELP_BITS;
	union _UC			COMMANDS;
	union _UC			MAIN_COMMANDS;
	union _UFLT1 		FAULTS1;
	union _UFLT2 		FAULTS2;
	union _UFLTC 		FAULTSC;
	union _UFLTD_INV 	FAULTSD_INV;
	union _UFLTD_CHOP 	FAULTSD_CHOP;
	union _US  			STATE;
	union _UOTF  		OTF;
	union _UBM  		BOOL_MACRO;
	union _UBM  		BOOL_MACRO2; //для синхр данных вент
	/*union _UDIN1 		DIN1;
	union _UDIN2 		DIN2;*/
	union uDIN 			DIN;
	union uDOUT 		DOUT;
	Uint16 				TmsVersion;
	Uint16 				AlteraVersion;

};

extern struct GS_ GS;

//-----------------------------------------------------------------------------------------------//
// Данные команды от ЭПП
//-----------------------------------------------------------------------------------------------//


struct comand{
unsigned reset:1;			//0 Сбросить Ошибки
unsigned ONYVTR:1;			//1 Войти в режим нагрузки дизеля на УВТР
unsigned OnOffChop:1;		//2 Включить/Выключить чоперы
unsigned OnOffDiezlF:1;		//3 Дизель передней оси
unsigned OnOffDiezlR:1;		//4 Дизель Задней оси
unsigned rsrv:3;		//6-15

};

union _COM
{
   int     		all;
   struct comand 	bit;
};

extern union _COM COMEPP; //
extern int UDZ_YVTR;// НАпряжение задания в Режиме УВТР

extern int PowerHudrF,PowerHudrR;
/*
struct ALTERA_REGS
{

	unsigned int ADR_Type_Controller;
	unsigned int ADR_Version_Altera;
	unsigned int Driver_Errors_L;
	unsigned int Driver_Errors_R;
	unsigned int Compare_Errors1;
	unsigned int Compare_Errors2;
	unsigned int bit_place;
	union _UDIN1 DIN1;
	union _UDIN2 DIN2;
	union _UDOUT DOUT;
	
};*/




//**************************************************************************//
//***************              END OF FILE           	 *******************//
//**************************************************************************//


