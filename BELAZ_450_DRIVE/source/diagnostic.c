#include "hfa.h"

void ErrorResponse();
void StateMachine();
void Reset();
void FirstStateOfSystem();
void StateOfControlPins();
void CheckN();

#pragma CODE_SECTION(ErrorResponse,"ramfuncs")
#pragma CODE_SECTION(StateMachine,"ramfuncs")
#pragma CODE_SECTION(Reset,"ramfuncs")
#pragma CODE_SECTION(FirstStateOfSystem,"ramfuncs")
#pragma CODE_SECTION(StateOfControlPins,"ramfuncs")
#pragma CODE_SECTION(CheckN,"ramfuncs")

/*
 * Debug
 * 0	Штатный режим
 * 1
 * 2	проверка импульсов
 * 3	регулятор тока
 * 4	L экскаваторная характеристика, R - белазовская
 * 5
 * 6	управление углом коммутации тиристоров.
 * 7
 * 8
 * 9
 */



#define AND *
#define NOT !
#define OR  ||

Uint16 CountFEX=0; //First excitation

/*

#define F1					0x1
#define F2					0x2
#define FC					0x3
#define FDL					0x4
#define FDR					0x5

#define LEFT_INV_CONTROL_PIN
#define RIGHT_INV_CONTROL_PIN
#define EX_CONTROL_PIN
#define CHOP_CONTROL_PIN
#define POWER_QF

*/

/*
#define INV_L_MASK_F1		0x0000
#define INV_R_MASK_F1		0x0000

#define INV_L_MASK_F2		0x0000
#define INV_R_MASK_F2		0x0000
#define EX_MASK_F2			0x0000
#define QF_MASK_F2			0x0000

#define INV_L_MASK_C		0x0000
#define INV_R_MASK_C		0x0000
#define EX_MASK_C			0x0000
#define QF_MASK_C			0x0000

#define INV_L_MASK_DL		0x0000
#define CHOP_MASK_DL		0x0000

#define INV_R_MASK_DR		0x0000
#define CHOP_MASK_DR		0x0000

#define EX_MASK_D			0x0000
#define QF_MASK_D			0x0000
*/

Uint16 Faults1;
Uint16 Faults2;
Uint16 FaultsC;
Uint16 FaultsDINV;
Uint16 FaultsDCHOP;

#ifdef NotIfDef_JustForLook
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
#endif

Uint16 FaultEvent=0;
Uint16 AlarmFlag=0;

#define ALTERA_CHECK

Uint16 F1=0;
Uint16 F2=0;
Uint16 FDIL=0;
Uint16 FDI=0;

Uint16 NCount=0;

extern Uint16 ChopOpen;

struct ValsToWindow{
	int16	RPMDiz;  //- скорость генератора
	int16	Iv;	//- ток возбуждения
	int16	Ud;	//- Напряжение в ЗПТ
	int16	Udz;	//- Напряжение задания
	int16	Ugen;	//- Напряжение генератора
	int16	Igen;	//- ток генератора
	int16	alpha16;	//- угол коммутации
	int16	ChopOpen;//- Открытие чоппера
	int16	SpeedL;	//- скорость
	int16	IdzL;	//- ток намагничивания
	int16	IqzL;	//- ток моментообразующий
	int16	SpeedR;	//
	int16	IdzR;	//
	int16	IqzR;	//
};

struct ValsToWindow sVTW;

Uint16 FAN=0;
Uint16 catchHB=0;
void ErrorResponse()
{
/**********************************************************************************************/

	GS.FAULTSD_INV.all = altera_regs.RegFltDrvLatch.all;
	GS.FAULTSD_CHOP.all = altera_regs.RegFltChpLatch.all;
	GS.FAULTSC.all = altera_regs.RegFltCmprLatch.all;

	FDIL = altera_regs.RegFltDrvLatch.all;
	FDI = altera_regs.RegFltDrv.all;

	if(!altera_regs.DIN.bit.PIP)
	SET_ERROR(f2.PIP);

	if(!altera_regs.DIN.bit.QF_POWER)
	SET_ERROR(f2.QF_EX);

	if(!altera_regs.DIN.bit.QfPreEx)
	SET_ERROR(f2.QF_pre_EX);

	if(ANY_FAULT && ANY_IMP && !hb.FaultEvent)
	{
			SET(hb.FaultEvent);
			SET(hb.alarm_flag);
	}

	if( (GS.FAULTS1.all & M_L_IMP_F1) || \
		(GS.FAULTS2.all & M_L_IMP_F2) || \
		(GS.FAULTSC.all & M_L_IMP_FC) || \
		(GS.FAULTSD_INV.all & M_L_IMP_FDI) ||\
		(GS.FAULTSD_CHOP.all & M_L_IMP_FDCH))
		{
			POFF(LEFT_INV_CONTROL_PIN);
			SET(bm.MskIL);
			UNSET(cmd.LeftWheel);
		}
		else
			UNSET(bm.MskIL);

	if( (GS.FAULTS1.all & M_R_IMP_F1) || \
		(GS.FAULTS2.all & M_R_IMP_F2) || \
		(GS.FAULTSC.all & M_R_IMP_FC) || \
		(GS.FAULTSD_INV.all & M_R_IMP_FDI) ||\
		(GS.FAULTSD_CHOP.all & M_R_IMP_FDCH))
		{
			POFF(RIGHT_INV_CONTROL_PIN);
			SET(bm.MskIR);
			UNSET(cmd.RightWheel);
		}
		else
			UNSET(bm.MskIR);

	if( (GS.FAULTS1.all & M_EX_IMP_F1) || \
		(GS.FAULTS2.all & M_EX_IMP_F2) || \
		(GS.FAULTSC.all & M_EX_IMP_FC) || \
		(GS.FAULTSD_INV.all & M_EX_IMP_FDI) ||\
		(GS.FAULTSD_CHOP.all &M_EX_IMP_FDCH))
		{
			POFF(EX_CONTROL_PIN);
			SET(bm.MskAEx);
			CLEAR_COMMAND(cmd.Gen);
			cmd.DNR = NEUTRAL;
		}
		else
			UNSET(bm.MskAEx);

	if( (GS.FAULTS1.all & M_CH_IMP_F1) || \
		(GS.FAULTS2.all & M_CH_IMP_F2) || \
		(GS.FAULTSC.all & M_CH_IMP_FC) || \
		(GS.FAULTSD_INV.all & M_CH_IMP_FDI) ||\
		(GS.FAULTSD_CHOP.all & M_CH_IMP_FDCH))
		{
			POFF(CHOP_CONTROL_PIN);
			SET(bm.MskICH);
		}
		else
			UNSET(bm.MskICH);

	if( (GS.FAULTS1.all & M_QF_OFF_F1) || \
		(GS.FAULTS2.all & M_QF_OFF_F2) || \
		(GS.FAULTSC.all & M_QF_OFF_FC) || \
		(GS.FAULTSD_INV.all & M_QF_OFF_FDI) ||\
		(GS.FAULTSD_CHOP.all & M_QF_OFF_FDCH))
		{
			PON(altera_regs.DOUT.bit.QF_OFF);
			CLEAR_COMMAND(cmd.Gen);
			cmd.DNR = NEUTRAL;

		}
		else
			{
				UNSET(altera_regs.DOUT.bit.QF_OFF);
			}

	FaultEvent = hb.FaultEvent;
	AlarmFlag = hb.alarm_flag;

	//TODO	отказ от ПИП

	StateOfControlPins();

	Faults1 = GS.FAULTS1.all;
	Faults2 = GS.FAULTS2.all;
	FaultsC = GS.FAULTSC.all;
	FaultsDINV = GS.FAULTSD_INV.all;
	FaultsDCHOP = GS.FAULTSD_CHOP.all;

}

void StateMachine(){

	if(altera_regs.DIN.bit.BitPlace1)
	altera_regs.DOUT.bit.FAN = FAN;

	GS.DIN.all = altera_regs.DIN.all;
	GS.DOUT.all = altera_regs.DOUT.all;
	GS.FAULTSD_INV.all = altera_regs.RegFltDrvLatch.all;
	GS.FAULTSD_CHOP.all = altera_regs.RegFltChpLatch.all;
	GS.FAULTSC.all = altera_regs.RegFltCmprLatch.all;


	if(cmd.ManualControl == DISABLE)
		{

			if(data_from_KK->DIN.bit.bBACK)
			{
				cmd.DNR = REVERSE;
				//GS.COMMANDS.bit.Gen = 1;
			}
			else
			if(data_from_KK->DIN.bit.bFORWARD)
			{
				cmd.DNR = DRIVE;
				//GS.COMMANDS.bit.Gen = 1;
			}
			else
				{
					cmd.DNR = NEUTRAL;
					//GS.COMMANDS.bit.Gen = 0;
				}

			if(data_from_KK->DIN.bit.bHANDLE_BRAKE)
			{
			/*	UNSET(cmd.Gen);
				UNSET(cmd.LeftWheel);
				UNSET(cmd.RightWheel);
				UNSET(cmd.Start);*/

				catchHB = 1;
			}
			/*else
			{
				SET(cmd.Gen);
				SET(cmd.LeftWheel);
				SET(cmd.RightWheel);
			}*/

			// GS.COMMANDS.all &= MASK_COMMANDS;
			// если не ручное управление - маскируем некоторые команды монитора

			//cmd.DNR
		}

	// отображаем структуру принятых с любого уровня команд
	// на структуру основных комманд
	GS.MAIN_COMMANDS.all = GS.COMMANDS.all;

	bm.EnEx 		= mcmd.Gen;
	bm.EnIL 		= mcmd.LeftWheel;
	bm.EnIR 		= mcmd.RightWheel;
	bm.ManContr 	= mcmd.ManualControl;
	bm.Start 		= mcmd.Start;
/*
	  Ud ^
		 |      **********
		 |     *          *
		 |    *UdInvStart  *
		 |   *              *
		 |  *                *UdInvStop
		 | *UdExMin           *1
		 |*                    *UdChopStop
		 |______________________*_____________>

*/
	if(Ud > koeff.UdInvStart)
	{
		SET(bm.UdInvStart);
		UNSET(bm.UdInvStop);
		UNSET(bm.UdChStop);
	}

	if(Ud < koeff.UdInvStop && bm.UdInvStart)
	{
		SET(bm.UdInvStop);
		UNSET(bm.UdInvStart);
	}

	if(Ud < koeff.UdChStop)
	{
		SET(bm.UdChStop);
		UNSET(bm.UdInvStart);
	}

	if(GS.MAIN_COMMANDS.bit.DNR == NEUTRAL)
	{
		SET(bm.N);
		UNSET(bm.ExTimeOver);
		UNSET(otf.KM1);
		UNSET(hb.SCFEX);
		CLEAR_COUNTER(CountFEX);
	}
	else
	{
		UNSET(bm.N);

		if(!otf.KM1)
		{
			SET(hb.SCFEX);
			SET(otf.KM1);
		}
	}

	if(cmd.Reset||COMEPP.bit.reset)
	Reset();

	if(koeff.WriteKoeff)
	{

		MemCopy(&koeff.IFMAX,&koeff.IFMAX+NUM_OF_KOEFF-1,(void *)0x1Bfd00);

		UNSET(koeff.WriteKoeff);
	}

	sVTW.RPMDiz = RPMDiz;  //- скорость генератора
	sVTW.Iv=Iv;	//- ток возбуждения
	sVTW.Ud=Ud;	//- Напряжение в ЗПТ
	sVTW.Udz=Udz;	//- Напряжение задания
	sVTW.Ugen=Ugen;	//- Напряжение генератора
	sVTW.Igen=Igen;	//- ток генератора
	sVTW.alpha16=alpha16;	//- угол коммутации
	sVTW.ChopOpen=ChopOpen;//- Открытие чоппера
	sVTW.SpeedL=SpeedL;	//- скорость
	sVTW.IdzL=IdzL;	//- ток намагничивания
	sVTW.IqzL=IqzL;	//- ток моментообразующий
	sVTW.SpeedR=SpeedR;	//
	sVTW.IdzR=IdzR;	//
	sVTW.IqzR=IqzR;	//


}

void FirstStateOfSystem(){

		ALLOW(GS.OTF.bit.KM1);
		CLEAR_COUNTER(CountFEX);

}

void Reset()
{
int i=0;
//обнуляем только флаги аварий

			CLEAR_ERRORS(GS.FAULTS1.all);
			CLEAR_ERRORS(GS.FAULTS2.all);

			CLEAR_COMMAND(cmd.Reset);

			UNSET(altera_regs.RESET);

			SET(cmd.RightWheel);
			SET(cmd.LeftWheel);
			SET(cmd.Gen);

}

Uint16 QF_STate=0;
Uint16 KM_State=0;
Uint16 KM_ON_Command=0;

void StateOfControlPins()
{

/*
  Ud ^
	 |      **********
	 |     *          *
	 |    *UdInvStart  *
	 |   *              *
	 |  *                *UdInvStop
	 | *UdExMin           *1
	 |*                    *UdChopStop
	 |______________________*_____________>

		X1	Авария по маске импульсов возбуждения
		X2	Авария по маске импульсов левого инвертора
		X3	Авария по маске импульсов правого инвертора
		X4	Авария по маске импульсов чопперов
		X5	Разрешение подачи импульсов возбуждения
		X6	Разрешение подачи импульсов левого инвертора
		X7	Разрешение подачи импульсов правого инвертора
		X8	Успешная отработка предварительного возбуждения
		X9	Ud > UdExMin
		X10	Ud > UdInvStart
		X11	Ud < UdInvStop
		X12	Ud < UdChopStop. Разряд ЗПТ
		X13	Ручное управление
		X14	Start
		X15	Нейтраль
		X16	Отработал таймер предварительного возбуждения
		X17	Ручник
*/

	EX_CONTROL_PIN 			= !X15&&!X1&&X5&&(!X13&&X8||X13);
	_PAUSE(2);
	LEFT_INV_CONTROL_PIN 	= !X2&&X6&&(!X13&&!X11&&X10&&!X17||X13&&X14);
	_PAUSE(2);
	RIGHT_INV_CONTROL_PIN 	= !X3&&X7&&(!X13&&!X11&&X10&&!X17||X13&&X14);
	_PAUSE(2);
	CHOP_CONTROL_PIN		= !X4&&(!X13&&!X12||X13&&X14);
	_PAUSE(2);
	KM_Switch				= !X15&&!X8&&!X16;

	QF_STate=altera_regs.DIN.bit.QF_POWER;
	KM_State=altera_regs.DIN.bit.KM;
	KM_ON_Command=KM_Switch;

/*
 * для отладки
	LEFT_INV_CONTROL_PIN = X6;
	WAIT_FEW_STEPS;
	RIGHT_INV_CONTROL_PIN = X7;
	WAIT_FEW_STEPS;
	CHOP_CONTROL_PIN = X5;
*/
	st.LeftImp = LEFT_INV_CONTROL_PIN;
	WAIT_FEW_STEPS;
	st.RightImp = RIGHT_INV_CONTROL_PIN;
	WAIT_FEW_STEPS;
	st.ChopImp = CHOP_CONTROL_PIN;
	WAIT_FEW_STEPS;
	st.ExImp = EX_CONTROL_PIN;
	WAIT_FEW_STEPS;

	st.HandleBrake = data_from_KK->DIN.bit.bHANDLE_BRAKE;
	st.Drive = data_from_KK->DIN.bit.bDRIVE;
	st.Pedal = data_from_KK->DIN.bit.bDRIVE;
	st.Stab = data_from_KK->DIN.bit.bSTAB;

	//CheckState  st.ExImp = EX_CONTROL_PIN;
	//CheckState  st.LeftImp = LEFT_INV_CONTROL_PIN;
	//CheckState  st.RightImp = RIGHT_INV_CONTROL_PIN;
	//CheckState  st.ChopImp = CHOP_CONTROL_PIN;

	//altera_regs.Reg_Altera_RD1.bit.rsvd

}

Uint16 MonN=0;



void CheckN()
{


	if(mcmd.DNR == NEUTRAL)
	{
		if(NCount < 4500)
		NCount++;
		else
		{
			SET(otf.N);
			CLEAR_COUNTER(NCount);
			//UNSET(GS.COMMANDS.bit.Gen);
			UNSET(bm.FExDone);
		}
	}
	else
		{
			CLEAR_COUNTER(NCount);
			UNSET(otf.N);
			SET(GS.COMMANDS.bit.Gen);
		}

	MonN = otf.N;


}








