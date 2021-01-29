#ifndef _ALTERA_REGS_H
#define _ALTERA_REGS_H

		struct sRegFltDrv
		{
			unsigned int LAH				: 1;	// 0
			unsigned int LAL				: 1;	// 1
			unsigned int LBH				: 1;	// 2
			unsigned int LBL				: 1;	// 3
			unsigned int LCH				: 1;	// 4
			unsigned int LCL				: 1;	// 5
			unsigned int RAH				: 1;	// 6
			unsigned int RAL				: 1;	// 7
			unsigned int RBH				: 1;	// 8
			unsigned int RBL				: 1;	// 9
			unsigned int RCH				: 1;	// 10
			unsigned int RCL				: 1;	// 11
			unsigned int RSRVD				: 4;	// 12-15
		};

		struct sRegFltChpLatch
		{
			unsigned int CH1				: 1;	// 0
			unsigned int CH2				: 1;	// 1
			unsigned int CH3				: 1;	// 2
			unsigned int CH4				: 1;	// 3
			unsigned int CH5				: 1;	// 4
			unsigned int CH6				: 1;	// 5
			unsigned int RSRVD				: 10;	// 6-15
		} ;

		struct sRegFltChp
		{
			unsigned int CH1				: 1;	// 0
			unsigned int CH2				: 1;	// 1
			unsigned int CH3				: 1;	// 2
			unsigned int CH4				: 1;	// 3
			unsigned int CH5				: 1;	// 4
			unsigned int CH6				: 1;	// 5
			unsigned int RSRVD				: 10;	// 6-15
		} ;

		struct sRegFltCmprLatch
		{
			unsigned int LIA				: 1;	// 0
			unsigned int LIB				: 1;	// 1
			unsigned int LIC				: 1;	// 2
			unsigned int RIA				: 1;	// 3
			unsigned int RIB				: 1;	// 4
			unsigned int RIC				: 1;	// 5
			unsigned int Ud					: 1;	// 6
			unsigned int Ugen				: 1;	// 7
			unsigned int Iv					: 1;	// 8
			unsigned int Igen				: 1;	// 9
			unsigned int RSRVD				: 6;	// 10-15
		} ;

		struct sRegFltCmpr
		{
			unsigned int LIA				: 1;	// 0
			unsigned int LIB				: 1;	// 1
			unsigned int LIC				: 1;	// 2
			unsigned int RIA				: 1;	// 3
			unsigned int RIB				: 1;	// 4
			unsigned int RIC				: 1;	// 5
			unsigned int Ud					: 1;	// 6
			unsigned int Ugen				: 1;	// 7
			unsigned int Iv					: 1;	// 8
			unsigned int Igen				: 1;	// 9
			unsigned int RSRVD				: 6;	// 10-15
		} ;

		struct sDIN
		{
			unsigned int PKI 			: 1;	// 0
			unsigned int Dors 			: 1;	// 1
			unsigned int QF_POWER 		: 1;	// 2
			unsigned int Body			: 1;	// 3
			unsigned int Source			: 1;	// 4
			unsigned int BitPlace1		: 1;	// 5
			unsigned int BitPlace2 		: 1;	// 6
			unsigned int Gercon1		: 1;	// 7
			unsigned int Gercon2		: 1;	// 8
			unsigned int QfPreEx		: 1;	// 9
			unsigned int KM				: 1;	// 10
			unsigned int _42C			: 1;	// 11
			unsigned int PIP			: 1;	// 12
			unsigned int rsrvd1			: 1;	// 13
			unsigned int rsrvd2			: 1;	// 14
			unsigned int rsrvd3			: 1;	// 15
		} ;

		struct sDOUT
		{
			unsigned int KM				: 1;
			unsigned int QF_OFF			: 1;
			unsigned int FAN			: 1;
			unsigned int RSRVD			: 13;
		} ;

//_______________________________________________________________UNIONS

		union	uRegFltDrvLatch								// 	(0x4003)
		{
			unsigned int 			all;
			struct sRegFltDrv  		bit;

		};



//---------------------------------------------------------------------------

		union	uRegFltDrv									// 	(0x4004)
		{
			unsigned int 		all;
			struct sRegFltDrv 	bit;

		} ;


//---------------------------------------------------------------------------


		union	uRegFltChpLatch									// 	(0x4005)
		{
			unsigned int all;
			struct sRegFltDrv bit;

		} ;


//---------------------------------------------------------------------------

		union	uRegFltChp									// 	(0x4006)
		{
			unsigned int all;
			struct sRegFltChp bit;

		} ;


//---------------------------------------------------------------------------

		union	uRegFltCmprLatch									// 	(0x4007)
		{
			unsigned int all;
			struct sRegFltCmprLatch bit;

		} ;


//---------------------------------------------------------------------------

		union	uRegFltCmpr									// 	(0x4008)
		{
			unsigned int all;
			struct sRegFltCmpr bit;

		} ;


//---------------------------------------------------------------------------

		union uDOUT										// 	(0x4009)
		{
			unsigned int all;
			struct sDOUT bit;

		} ;


//----------------------------------------------------------------------------

		union	uDIN									// 	(0x400A)
		{
			unsigned int all;
			struct sDIN bit;

		} ;


struct Altera_Regs
{
	unsigned int RegTypeController;				// Тип конроллера  		(0x4000)
	unsigned int RegVersAltera;					// Версия Altera   		(0x4001)

	union uRegFltDrvLatch RegFltDrvLatch;
	union uRegFltDrv RegFltDrv;
	union uRegFltChpLatch RegFltChpLatch;
	union uRegFltChp RegFltChp;
	union uRegFltCmprLatch RegFltCmprLatch;
	union uRegFltCmpr uRegFltCmpr;
	union uDOUT DOUT;
	union uDIN DIN;

	unsigned int RESET;

};

extern struct Altera_Regs altera_regs;

#endif
