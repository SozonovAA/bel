/*******************************************************************************
Name:
Developed:
Release Date:
Version: 1.0
*******************************************************************************//*
#include <stdlib.h>
#include <stdio.h>

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "Flash2833x_API_Library.h"
#include "ECAT_Common.h"
#include "ECAT_DATA.h"
#include "altera_regs.h"
*/

/******
add strings to see what changed in git history on CCS5*/

#include "hfa.h"

/* XX - Date XX -Month  X - last number of year */
#define TMS_VERSION 10109

typedef struct {
     Uint16 *StartAddr;
     Uint16 *EndAddr;
} SECTOR;
Uint16 Status;
  Uint16  l;
  Uint16  *Flash_ptr;     // Pointer to a location in flash
  Uint32  Length;         // Number of 16-bit values to be programmed
//  float32 Version;        // Version of the API in floating point
//  Uint16  VersionHex;     // Version of the API in decimal encoded hex
  Uint16  i=0;

  SECTOR Sector[8] = {
           (Uint16 *)0x338000,(Uint16 *)0x33FFFF,
           (Uint16 *)0x330000,(Uint16 *)0x337FFF,
           (Uint16 *)0x328000,(Uint16 *)0x32FFFF,
           (Uint16 *)0x320000,(Uint16 *)0x327FFF,
           (Uint16 *)0x318000,(Uint16 *)0x31FFFF,
           (Uint16 *)0x310000,(Uint16 *)0x317FFF,
           (Uint16 *)0x308000,(Uint16 *)0x30FFFF,
           (Uint16 *)0x300000,(Uint16 *)0x307FFF

  };

  extern Uint16 rts2800_fpu32_LoadStart;
  extern Uint16 rts2800_fpu32_LoadEnd;
  extern Uint16 rts2800_fpu32_RunStart;

  extern Uint16 IQ_secureRamFuncs_loadstart;
  extern Uint16 IQ_secureRamFuncs_loadend;
  extern Uint16 IQ_secureRamFuncs_runstart;

#pragma DATA_SECTION(altera_regs,"altera_regs");
struct Altera_Regs altera_regs;

interrupt void epwm1_isr(void);

// регистр состояния
unsigned char reg_sost;
#pragma DATA_SECTION(reg_sost,"REG_SOST");

#pragma CODE_SECTION(jump_to_bootloader,"secureRamFuncs")
#pragma CODE_SECTION(main_routine,"secureRamFuncs")

unsigned int ControllerID=0;
extern void init_ECAT_data(void * data_transmit,int size_transmit,void * data_receive,int size_receive);

void jump_to_bootloader(void);
extern void tx_mb_monitor(void);
void main_routine(void);

void IniteCAP();
interrupt void adc_isr(void);
void I2CA_Init(void);
extern void InitXintf();
interrupt void ecap4_isr(void);

#pragma CODE_SECTION(I2CA_Init,"ramfuncs")
#pragma CODE_SECTION(IniteCAP,"ramfuncs")
#pragma CODE_SECTION(adc_isr,"ramfuncs")
#pragma CODE_SECTION(InitXintf,"ramfuncs")

#pragma CODE_SECTION(InitFlash,"ramfuncs")
#pragma CODE_SECTION(MemCopy,"ramfuncs")
#pragma CODE_SECTION(memcpy,"ramfuncs")

//struct ALTERA_REGS altera_regs;



void init_koeff();

void  QEP_InitL(void);
void  QEP_InitR(void);

#pragma CODE_SECTION(QEP_InitL,"ramfuncs")
#pragma CODE_SECTION(QEP_InitR,"ramfuncs")
#pragma CODE_SECTION(init_koeff,"ramfuncs")

// #pragma DATA_SECTION(altera_regs,".altera_regs" )

int gg;
int D11=0;


//POSSPEED qep_posspeed=POSSPEED_DEFAULTS;


Uint16 Debug=0;

unsigned int * ver_altera = (unsigned int *)0x4001;
extern void init_ECAT(void);
int pwm_counter1=0;

Uint32 WaitPheripheriaAlive=0;
Uint16 JustCause=0;



/*******************************************************************************

  main program

*******************************************************************************/
void main ( void )
{
	DMAInitialize();
    /***************************************************************************
     Copy time critical code and Flash setup code to RAM
     The  *RamfuncsLoadStart, *RamfuncsLoadEnd, and *RamfuncsRunStart
     symbols are created by the linker. Refer to the ftpclient_flash.cmd file.
    ***************************************************************************/




	MemCopy(&secureRamFuncs_loadstart, &secureRamFuncs_loadend, &secureRamFuncs_runstart);
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	MemCopy(&rts2800_fpu32_LoadStart, &rts2800_fpu32_LoadEnd, &rts2800_fpu32_RunStart);
	memcpy(	&IQ_secureRamFuncs_runstart,
			&IQ_secureRamFuncs_loadstart,
			&IQ_secureRamFuncs_loadend - &IQ_secureRamFuncs_loadstart);

//	 MemCopy(&nettextfast_loadstart, &nettextfast_loadend, &nettextfast_runstart);

    /***************************************************************************
     Call Flash Initialization to setup flash waitstates
     This function must reside in RAM
    ***************************************************************************/
	//InitFlash();

    GS.OTF.all = 0;
    GS.COMMANDS.all = 0;
    GS.HELP_BITS.all = 0;
    GS.MAIN_COMMANDS.all = 0;
    GS.STATE.all = 0;
    GS.BOOL_MACRO.all=0;
    GS.BOOL_MACRO2.all=0;

    Slider.s1 = 0;
    Slider.s2 = 0;
    Slider.s3 = 0;
    Slider.s4 = 0;
    Slider.s5 = 0;
    Slider.s6 = 0;

    Slider.SaveRange = 0;

   /* Slider.MAX1 = 101;
    Slider.MIN1 = 101;
    Slider.MAX2 = 102;
    Slider.MIN2 = 102;
    Slider.MAX3 = 103;
    Slider.MIN3 = 103;
    Slider.MAX4 = 104;
    Slider.MIN4 = 104;
    Slider.MAX5 = 105;
    Slider.MIN5 = 105;
    Slider.MAX6 = 106;
    Slider.MIN6 = 106;*/

	/*unsigned long fWait=0,ggg=9;

	for(WaitPheripheriaAlive=0; WaitPheripheriaAlive < 15000000;WaitPheripheriaAlive++)
		JustCause = WaitPheripheriaAlive*2;*/

	InitSysCtrl();


	   InitEPwm1Gpio(); 	/*GPIO0  (EPWM1A) 1A */ 	/*GPIO1 (EPWM1B) 2A */
	   InitEPwm2Gpio(); 	/*GPIO2  (EPWM2A) 1B */ 	/*GPIO3 (EPWM2B) 2B */
	   InitEPwm3Gpio(); 	/*GPIO4  (EPWM3A) 1C */
	   InitEPwm5Gpio(); 	/*GPIO8  (EPWM5A) CHOPPER */
	   InitEPwm6Gpio(); 	/*GPIO10 (EPWM6A) 2C */

	   /*EALLOW;

	   GpioCtrlRegs.GPADIR.bit.GPIO0=1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;   // Configure GPIO0 as EPWM1A
	   GpioCtrlRegs.GPADIR.bit.GPIO2=1;
	   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO0 as EPWM1A

	   EDIS;*/
	   //InitEPwm4Gpio(); // pin not used, epwm4 is used for adc

	   InitI2CGpio(); 		/*GPIO32 SDAA*/ 			/*GPIO33 SCLA*/

	   InitEQep1Gpio(); 	/*GPIO50 EQEP1A*/ 			/*GPIO51 EQEP1B*/
	   InitEQep2Gpio(); 	/*GPIO24 EQEP2A*/ 			/*GPIO25 EQEP2B*/

	   InitECanGpio();  	/*GPIO18 GPIO19 A*/ 		/*GPIO20 GPIO21 B*/

	   InitECap1Gpio(); 	/*GPIO5 */
	   InitECap2Gpio(); 	/*GPIO7 */
	   InitECap4Gpio(); 	/*GPIO11 */
	   //GpioCtrlRegs.GPAMUX1.bit.GPIO11=0;

	InitPieCtrl();

  //таблица векторов перерывания
	InitPieVectTable();

	 // Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
		DINT;

	// Disable CPU interrupts and clear all CPU interrupt flags:
		IER = 0x0000;
		IFR = 0x0000;


#ifdef FLASH_RUN
		if(altera_regs.DIN.bit.BitPlace1)
			ControllerID = PK1;  // PK1
		if(altera_regs.DIN.bit.BitPlace2)
			ControllerID = PK2;  // PK2
#endif

#ifdef TABLE_PK1_RUN
		ControllerID = PK1;
#endif

#ifdef TABLE_PK2_RUN
		ControllerID = PK2;
#endif
	//**********************************************************************************/
	//
	//**********************************************************************************/

		//for(WaitPheripheriaAlive=0; WaitPheripheriaAlive < 15000000;WaitPheripheriaAlive++)
		//		JustCause = WaitPheripheriaAlive/1000;

		   EALLOW;

		   	   PieVectTable.ADCINT = &adc_isr;
		   	   PieVectTable.ECAP4_INT = &ecap4_isr;

		   EDIS;    // This is needed to disable write to EALLOW protected registers

		   InitCpuTimers();

		   InitXintf();

	//**********************************************************************************/
	// Настройка EtherCAT слэйва
	//**********************************************************************************/
	 init_ECAT();

		   StaticMparams(&MPL);
		   StaticMparams(&MPR);

		   EALLOW;
		   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
		   EDIS;

		   InitEPwm1();
		   InitEPwm2();
		   InitEPwm3();
		   InitEPwm4();
		   InitEPwm5();
		   InitEPwm6();

		   InitAdc();
		   InitADC();

		   I2CA_Init();

		 //  InitECan();

		 //  CANA_vInit ();
		 //  CANB_vInit ();

		   IniteCAP();

		   QEP_InitL();
		   QEP_InitR();

				EALLOW;
				GpioCtrlRegs.GPBMUX2.bit.GPIO55=0;
			    GpioCtrlRegs.GPBDIR.bit.GPIO55=1;

			   // MUX5 = 0;
			   // DIR5 = 1;
				EDIS;


		   EALLOW;
		   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
		   EDIS;

//		   #ifdef MODEL
		   EALLOW;
		//   PieVectTable.TINT0 = &cpu_timer0_isr;
		   EDIS;

		//   ConfigCpuTimer(&CpuTimer0, 150, 66);

		   CpuTimer0Regs.TCR.all = 0x4001;

//		   #endif

		   init_koeff();

		   IER |= M_INT1;
		   IER |= M_INT4;

		   PieCtrlRegs.PIEIER1.bit.INTx6 = 1;			//ADCINT
		   PieCtrlRegs.PIEIER4.bit.INTx4 = 1;			//eCAP4

			EnableInterrupts();


		   EINT;   // Enable Global interrupt INTM
		   ERTM;   // Enable Global realtime interrupt DBGM

		   StateMachine();


		   EALLOW;
		   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;         // GPIO
		   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;         // GPIO
		   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;         // GPIO
		   GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;         // GPIO
		   GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;      	// output INV_R_CONTROL_PIN
		   GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;      	// output CH_CONTROL_PIN
		   GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;          // output EX_CONTROL_PIN
		   GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;          // output INV_L_CONTROL_PIN
		   EDIS;

		    GpioDataRegs.GPADAT.bit.GPIO16 = 1;          // output EX_CONTROL_PIN

		    Reset();

		    SET(hb.WriteDacs);
		    SET(koeff.WriteDacs);

		    ptrPK12->MessFlag=0;

			GS.AlteraVersion = altera_regs.RegVersAltera;
			GS.TmsVersion = TMS_VERSION;

			Reset();

			otf.N = 1;
			cmd.LeftWheel = 1;
			cmd.RightWheel = 1;



			#ifdef MODEL
		    ModelFirstVals();
		    #endif

		   // qep_posspeed.init(&qep_posspeed);

	main_routine();
}

extern void read_packet(long address_eth);

void main_routine(void)
{

	for(i=0;;i++)
	{
		pwm_counter1++;
		slave_background_modbus(0);
		jump_to_bootloader();

		if(hb.CopyProcess)
		{
			CopyToFram();
		}
	}
}


void jump_to_bootloader(void)
{
	//Если перейти в режим работы
	if(reg_sost==0x55)
	{
// Disable CPU interrupts
		DINT;

// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

		asm(" JMP 0x33FFF6");
	}
}


void I2CA_Init(void)
{
   // Initialize I2C
//   I2caRegs.I2CSAR = 0x006f;		// Slave address - EEPROM control code
	I2caRegs.I2CSAR = 0x004f;
   #if (CPU_FRQ_150MHZ)             // Default - For 150MHz SYSCLKOUT
        I2caRegs.I2CPSC.all = 14;   // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
   #endif

   I2caRegs.I2CPSC.all = 14;   // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
   I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
   I2caRegs.I2CIER.all = 0x0;		// Enable SCD & ARDY interrupts

   I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   I2caRegs.I2CMDR.bit.MST=1;		// Stop I2C when suspended

   I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

  // return;
}

void IniteCAP(){


	   ECap4Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
	   ECap4Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
	   ECap4Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	   ECap4Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

	   // Configure peripheral registers
	   ECap4Regs.ECCTL2.bit.CONT_ONESHT = 0;      // continuous mode
	   ECap4Regs.ECCTL2.bit.STOP_WRAP = 1;        // Wrap at 2 events
	   ECap4Regs.ECCTL1.bit.CAP1POL = 0;          // Rising edge
	   ECap4Regs.ECCTL1.bit.CAP2POL = 0;          // Rising edge// Falling edge
	   ECap4Regs.ECCTL1.bit.CAP3POL = 0;          // Rising edge
	   ECap4Regs.ECCTL1.bit.CAP4POL = 0;          // Rising edge// Falling edge
	   ECap4Regs.ECCTL1.bit.CTRRST1 = 1;          // Difference operation
	   ECap4Regs.ECCTL1.bit.CTRRST2 = 1;          // Difference operation
	   ECap4Regs.ECCTL1.bit.CTRRST3 = 1;          // Difference operation
	   ECap4Regs.ECCTL1.bit.CTRRST4 = 1;          // Difference operation
	   ECap4Regs.ECCTL2.bit.SYNCI_EN = 0;         // Enable sync in
	   ECap4Regs.ECCTL2.bit.SYNCO_SEL = 2;        // Disable	//Pass through
	   ECap4Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units
	   ECap4Regs.ECCTL1.bit.PRESCALE = 0;          // Enable capture units
		ECap4Regs.CAP1  = 3600000;
		ECap4Regs.CAP2  = 36000;
		ECap4Regs.CAP3  = 3600000;
		ECap4Regs.CAP4  = 36000;

	   ECap4Regs.ECEINT.bit.CEVT1 = 1;            // 4 events = interrupt
	   ECap4Regs.ECEINT.bit.CTR_EQ_PRD = 1;
	   ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
	   ECap4Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
/*
	   ECap1Regs.ECCTL2.bit.CAP_APWM = 1;	// Enable APWM mode
	   ECap1Regs.ECCTL2.bit.APWMPOL = 1;	// Active low output
	//   ECap1Regs.TSCTR = 49000;
	//   ECap1Regs.CTRPHS = 44;				// Set Phase value
	//   ECap1Regs.CAP1 = 66666;				// Set Period value
	//   ECap1Regs.CAP2 = 33333;//URvg;;				// Set Compare value
	   ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;   // Enable sync in
	   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 2;        // Disable	//Pass through
	   ECap1Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
	   ECap1Regs.CAP1 = 66666;
	   ECap1Regs.CAP3 = 66666;
	   ECap1Regs.CAP2 = 3600000;
	   ECap1Regs.CAP4 = 3600000;

	   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;
*/

	   // Setup APWM mode on CAP3, set period and compare registers
	   ECap1Regs.ECCTL2.bit.CAP_APWM = 1;	// Enable APWM mode
		ECap1Regs.CAP1  = 3600000;
		ECap1Regs.CAP2  = 36000;
		ECap1Regs.CAP3  = 3600000;
		ECap1Regs.CAP4  = 36000;
		ECap1Regs.ECCTL2.bit.APWMPOL = 1;
	   ECap1Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
	   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;
	   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;

	   ECap2Regs.ECCTL2.bit.CAP_APWM = 1;	// Enable APWM mode
		ECap2Regs.CAP1  = 3600000;
		ECap2Regs.CAP2  = 36000;
		ECap2Regs.CAP3  = 3600000;
		ECap2Regs.CAP4  = 36000;
		ECap2Regs.ECCTL2.bit.APWMPOL = 1;
		ECap2Regs.ECCTL1.bit.CAPLDEN = 1;
	   ECap2Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
	   ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;

}
void init_koeff(){

	MemCopy((void *)0x1Bfd00,(void *)0x1Bfd31,&koeff.IFMAX);

}
/*
void  POSSPEED_Init(void)
{

	EQep1Regs.QUPRD=100000;			// 1000000//Unit Timer for 100Hz
	EQep1Regs.QDECCTL.bit.QSRC=00;	// QEP clock Inputs (quadrature count mode)

	EQep1Regs.QEPCTL.bit.FREE_SOFT=0;// (counters/timers stops immediately on emulation suspend)
	EQep1Regs.QEPCTL.bit.PCRM=1;		// PCRM=00 mode (position counter reset on the maximum position)
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep1Regs.QPOSMAX=32640;			//
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	EQep1Regs.QCAPCTL.bit.UPPS=0;//
	EQep1Regs.QCAPCTL.bit.CCPS=5;	//
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable


    EALLOW;                       		// Enable EALLOW
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;   // Configure GPIO50 as EQEP1A
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;   // Configure GPIO51 as EQEP1B
    EDIS;                         		// Disable EALLOW

}*/

