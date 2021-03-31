#include "hfa.h"

/*

 - Замер токов 5 раз
 - Замер параметров без смещения 4 раза

	Iх = Iх/1.3;

	Ugen = (F_(Ugen)*100.0)/F_(koeff.K1_Rvg);
	Igen = F_(Igen)/1.92;
	Iv   = F_(Iv)/3.5;
	Ud   = Ud;

*/

#define ADC_usDELAY  5000L

//#define LinkPin

void InitADC();
void SetLeftDriveParams();
void SetRightDriveParams();
void SetGenParams();

#pragma CODE_SECTION(InitADC,"ramfuncs")
#pragma CODE_SECTION(SetLeftDriveParams,"ramfuncs")
#pragma CODE_SECTION(SetRightDriveParams,"ramfuncs")
#pragma CODE_SECTION(SetGenParams,"ramfuncs")

#define LEFT_MOTOR		0x1
#define RIGHT_MOTOR		0x2
#define GENERATOR		0x3
#define REGS			0x4

#define NUM_OF_SEQ_PHASE_CUR	5
#define NUM_OF_SEQ				4
#define NUM_OF_SEQ_SHIFT		64

Uint16 CalcShiftCount=0;

int32  CurrentsShift[6]={0,0,0,0,0,0};

#define ADC_HALF		2048*NUM_OF_SEQ_PHASE_CUR

// 4000А - мгновенная защита по току

int16 Ki=0;
int16 Kp=0;

int16 Ugen=0;
int16 Igen=0;
int16 Ud=0;
int16 Iv=0;

int16 OldUd=0;
int16 DeltaUd=0;

double Omega_L;
double Omega_R;

volatile Uint16 *adc_ptr;

extern POSSPEED qep_posspeed;
extern void fill_data_for_oscil(void);

Uint16 WaitFewSeconds=10000;

void InitADC(){

	   // Configure ADC
	   AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
	   AdcRegs.ADCTRL1.bit.CPS = 1;

	   AdcRegs.ADCMAXCONV.all = 0x000E;       	// Setup 16 conv's on SEQ1

	   SetLeftDriveParams();

	   AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	   AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;	// Enable SOCA from ePWM to start SEQ1
	   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  	// Enable SEQ1 interrupt (every EOS)
	   AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit

	   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

}


int seq_step=0;
int swa=0;
int WriteArrayStep=0;
int qep_count=0;
int latch_qep;

int TestCountArray=0;

int eCatExchCount=0;

#define SHIFT_TEST
#ifdef SHIFT_TEST
	int16 CS1=0;
	int16 CS2=0;
	int16 CS3=0;
	int16 CS4=0;
	int16 CS5=0;
	int16 CS0=0;
#endif

//переменные для массива
int DIN=0;
int DOUT=0;

interrupt void adc_isr(void)
{
	int i;

	if(koeff.WriteDacs)
	{
		hb.WriteDacs=1;
		i2cDacs();
	}

	//переменные для массива
	DIN  = altera_regs.DIN.all;
	DOUT = altera_regs.DOUT.all;
//*********************************************************
//TODO
//	calculate zero_shift for currents
//*********************************************************

	//if(!hb.WriteDacs)
	seq_step++;
	//seq_step=1;

//*********************************************************
//*********************************************************
//*********************************************************


	StateOfControlPins();

	if(seq_step == LEFT_MOTOR)
	{
		if(WaitFewSeconds)
			WaitFewSeconds--;

		if(CalcShiftCount < NUM_OF_SEQ_SHIFT &&!WaitFewSeconds)
		{
			CalcShiftCount++;
			SET(hb.CalcShiftCurrent);
		}
		else
			{
				if(hb.CalcShiftCurrent)
				for(i=0;i<6;i++)
				{
					CurrentsShift[i] >>= 6;
				}

				UNSET(hb.CalcShiftCurrent);

				if(abs(CurrentsShift[0]) > koeff.IFZero)
				SET_ERROR(f1.IAL_ZERO);
				if(abs(CurrentsShift[1]) > koeff.IFZero)
				SET_ERROR(f1.IBL_ZERO);
				if(abs(CurrentsShift[2]) > koeff.IFZero)
				SET_ERROR(f1.ICL_ZERO);
				if(abs(CurrentsShift[3]) > koeff.IFZero)
				SET_ERROR(f1.IAR_ZERO);
				if(abs(CurrentsShift[4]) > koeff.IFZero)
				SET_ERROR(f1.IBR_ZERO);
				if(abs(CurrentsShift[5]) > koeff.IFZero)
				SET_ERROR(f1.ICR_ZERO);

				ErrorResponse();
			}

		//---------------------------------------------------------
		#ifdef LinkPin
		DAT2=1;
		#endif
		//---------------------------------------------------------
		adc_ptr = &AdcRegs.ADCRESULT0;
		IaL=0;IbL=0;IcL=0;

		if(hb.CalcShiftCurrent&&!WaitFewSeconds)
		{

			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[0] += (*adc_ptr) >> 4;
				adc_ptr++;
			}
			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[1] += (*adc_ptr) >> 4;
				adc_ptr++;
			}
			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[2] += (*adc_ptr) >> 4;
				adc_ptr++;
			}

			CurrentsShift[0] -= ADC_HALF;
			CurrentsShift[1] -= ADC_HALF;
			CurrentsShift[2] -= ADC_HALF;

		}
		else
			{

				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IaL += (*adc_ptr) >> 4;
					adc_ptr++;
				}
				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IbL += (*adc_ptr) >> 4;
					adc_ptr++;
				}
				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IcL += (*adc_ptr) >> 4;
					adc_ptr++;
				}

				IaL = IaL - ADC_HALF - CurrentsShift[0];
				IbL = IbL - ADC_HALF - CurrentsShift[1];
				IcL = IcL - ADC_HALF - CurrentsShift[2];

				IaL = F_(IaL)/1.3;
				IbL = F_(IbL)/1.3;
				IcL = F_(IcL)/1.3;

			}

		// Currents to koef 5
		// ...

		if(abs(IaL) > koeff.IFMAX)
		{
			SET_ERROR(f1.IAL);
			ErrorResponse();
		}
		if(abs(IbL) > koeff.IFMAX)
		{
			SET_ERROR(f1.IBL);
			ErrorResponse();
		}
		if(abs(IcL) > koeff.IFMAX)
		{
			SET_ERROR(f1.ICL);
			ErrorResponse();
		}

			//ErrorResponse();
			SetRightDriveParams();

			//CalcCurMParms(&MPL);
			//RegL();


		  	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
		  	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
		  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

		  	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
		  	//---------------------------------------------------------
			#ifdef LinkPin
		  	DAT2=0;
			#endif
		  	//---------------------------------------------------------
	}


//*********************************************************
//*********************************************************
//*********************************************************

	if(seq_step == RIGHT_MOTOR)
	{
		//---------------------------------------------------------
		#ifdef LinkPin
			DAT2=1;
		#endif
		//---------------------------------------------------------
		adc_ptr = &AdcRegs.ADCRESULT0;
		IaR=0;IbR=0;IcR=0;

		if(hb.CalcShiftCurrent&&!WaitFewSeconds)
		{

			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[3] += (*adc_ptr) >> 4;
				adc_ptr++;
			}
			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[4] += (*adc_ptr) >> 4;
				adc_ptr++;
			}
			for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
			{
				CurrentsShift[5] += (*adc_ptr) >> 4;
				adc_ptr++;
			}

			CurrentsShift[3] -= ADC_HALF;
			CurrentsShift[4] -= ADC_HALF;
			CurrentsShift[5] -= ADC_HALF;

		}
		else
				{

				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IaR += (*adc_ptr) >> 4;
					adc_ptr++;
				}
				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IbR += (*adc_ptr) >> 4;
					adc_ptr++;
				}
				for(i=0;i<NUM_OF_SEQ_PHASE_CUR;i++)
				{
					IcR += (*adc_ptr) >> 4;
					adc_ptr++;
				}

				IaR = IaR - ADC_HALF - CurrentsShift[3];
				IbR = IbR - ADC_HALF - CurrentsShift[4];
				IcR = IcR - ADC_HALF - CurrentsShift[5];

				IaR = F_(IaR)/1.3;
				IbR = F_(IbR)/1.3;
				IcR = F_(IcR)/1.3;

			}

		// Currents to koef 5
		// ...

		if(abs(IaR) > koeff.IFMAX)
		{
			SET_ERROR(f1.IAR);
			ErrorResponse();
		}
		if(abs(IbR) > koeff.IFMAX)
		{
			SET_ERROR(f1.IBR);
			ErrorResponse();
		}
		if(abs(IcR) > koeff.IFMAX)
		{
			SET_ERROR(f1.ICR);
			ErrorResponse();
		}

			//ErrorResponse();
			SetGenParams();

			//CalcCurMParms(&MPR);

			//RegR();


		  	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
		  	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
		  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

		  	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;


		  	//---------------------------------------------------------
			#ifdef LinkPin
		  		DAT2=0;
			#endif
		  	//---------------------------------------------------------
	}

//*********************************************************
//*********************************************************
//*********************************************************

	if(seq_step == GENERATOR)
	{
	//---------------------------------------------------------
	#ifdef LinkPin
		DAT2=1;
	#endif
	//---------------------------------------------------------

		adc_ptr = &AdcRegs.ADCRESULT0;

			Iv=0;
			Ud=0;
			Ugen=0;
			Igen=0;


		for(i=0;i<NUM_OF_SEQ;i++)
			{Iv +=(*adc_ptr) >> 4;adc_ptr++;}

		for(i=0;i<NUM_OF_SEQ;i++)
			{Ud +=(*adc_ptr) >> 4;adc_ptr++;}

		for(i=0;i<NUM_OF_SEQ;i++)
			{Igen +=(*adc_ptr) >> 4;adc_ptr++;}

		for(i=0;i<NUM_OF_SEQ;i++)
			{Ugen +=(*adc_ptr) >> 4;adc_ptr++;}

		Ugen = Ugen >> 2;
		Igen = Igen >> 2;
		Ud = Ud >> 2;
		Iv = Iv >> 2;

		//Ugen = F_(Ugen)/1.9;
		Ugen = (F_(Ugen)*100.0)/F_(koeff.K1_Rvg);
		Igen = F_(Igen)/1.92;
		Iv   = F_(Iv)/3.5;

		DeltaUd = OldUd - Ud;
		OldUd = Ud;

		MinMaxLimitInt(0,1070,&koeff.UdMAX);

		if( DeltaUd > koeff.DeltaUd )
		{
			SET_ERROR(f2.SHORT);
		}
		if( Iv > koeff.IvMAX )
		{
			SET_ERROR(f2.Iv);
		}
		if( Ud > koeff.UdMAX )
		{
			SET_ERROR(f2.Ud);
		}
		if( Igen > koeff.IgenMAX )
		{
			SET_ERROR(f2.Igen);
		}


		ErrorResponse();
		SetLeftDriveParams();


				//SpeedAndAngleL();


				CalcCurMParms(&MPL);
				CalcCurMParms(&MPR);

				RegL();
				RegR();

/*
				DAT2=1;
				TableMagnetSaturation(IdL);
				DAT2=0;
*/

				CTR_CAP1 = (Uint16)(ECap1Regs.TSCTR/45L);
				CTR_CAP2 = (Uint16)(ECap2Regs.TSCTR/45L);
				CTR_CAP4 = (Uint16)(ECap4Regs.TSCTR/45L);

				Cap1Cap1 = ECap1Regs.CAP1/100;
				Cap1Cap2 = ECap1Regs.CAP2/100;
				Cap1Cap3 = ECap1Regs.CAP3/100;
				Cap1Cap4 = ECap1Regs.CAP4/100;

				if(ECap1Regs.TSCTR > ECap1Regs.CAP1)
					ECap1Regs.TSCTR = 0;

				if(ECap2Regs.TSCTR > ECap2Regs.CAP1)
					ECap2Regs.TSCTR = 0;

				//PRD += (ECap4Regs.CAP1 - PRD) >> 7;

			seq_step=0;

			WriteArrayStep++;

			TestCountArray++;

			if(WriteArrayStep >= koeff.K13)
			{
					if(!hb.CopyProcess && !hb.LoadingProcess)
					write_array();
					WriteArrayStep=0;
			}

			//sensor();

			fill_data_for_oscil();

			AssemblyECIPMess();

			eCatExchCount++;

			if(eCatExchCount >= 100)
			{
			  create_state_array();
			  read_request_var();

			  SlidersMem();

			  eCatExchCount=0;

				if(!ANY_FAULT)
				UNSET(hb.FaultEvent);

			}


		  	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
		  	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
		  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE



		  	//AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

		  	//LKR(IaL,IbL,IcL,Omega_L,LEFT);
		  	//LKR(IaR,IbR,IcR,Omega_R,RIGHT);

		  	//---------------------------------------------------------
			#ifdef LinkPin
		  		DAT2=0;
			#endif
		  	//---------------------------------------------------------

// COUNTERS AND OTHERS
// seq_step GENERATOR
/**********************************************************************/

	if(hb.SCFEX)
	{
		CountFEX++;

		altera_regs.DOUT.bit.KM = 1;

		if(Ud < koeff.UdExMin-5)
		{

			if(CountFEX >= 10*SECOND)
			{
				SET_ERROR(f2.EX);
				bm.ExTimeOver = 1;
				hb.SCFEX = 0;
				CLEAR_COUNTER(CountFEX);
				altera_regs.DOUT.bit.KM = 0;
			}
		}
		if(Ud >= koeff.UdExMin+20)
		{

			hb.SCFEX = 0;
			CLEAR_COUNTER(CountFEX);
			bm.FExDone = 1;
			//altera_regs.DOUT.bit.KM = 0;

		}
	}

	if(!COMEPP.bit.ONYVTR)CheckN();

/**********************************************************************/

	}//end seq_step GENERATOR

	if(hb.CapIsr)
	{
		RVG();
		UNSET(hb.CapIsr);
	}

	StateMachine();

#ifdef SHIFT_TEST
	CS0 = CurrentsShift[0];
	CS1 = CurrentsShift[1];
	CS2 = CurrentsShift[2];
	CS3 = CurrentsShift[3];
	CS4 = CurrentsShift[4];
	CS5 = CurrentsShift[5];
#endif

}

void SetLeftDriveParams(){

	   AdcRegs.ADCMAXCONV.all = 0x000E;       	// Setup 15 conv's on SEQ1
	   AdcRegs.ADCCHSELSEQ1.all = 0x0000; 		// IaL,IaL,IaL,IaL.
	   AdcRegs.ADCCHSELSEQ2.all = 0x1110; 		// IbL,IbL,IbL,IaL.
	   AdcRegs.ADCCHSELSEQ3.all = 0x2211; 		// IcL,IcL,IbL,IbL.
	   AdcRegs.ADCCHSELSEQ4.all = 0x0222; 		//  X ,IcL,IcL,IcL.

}
void SetRightDriveParams(){

	   AdcRegs.ADCMAXCONV.all = 0x000E;       	// Setup 15 conv's on SEQ1
	   AdcRegs.ADCCHSELSEQ1.all = 0x8888; 		// IaR,IaR,IaR,IaR.
	   AdcRegs.ADCCHSELSEQ2.all = 0x9998; 		// IbR,IbR,IbR,IaR.
	   AdcRegs.ADCCHSELSEQ3.all = 0xAA99; 		// IcR,IcR,IbR,IbR.
	   AdcRegs.ADCCHSELSEQ4.all = 0x0AAA; 		//  X ,IcR,IcR,IcR.

}
void SetGenParams(){

	   AdcRegs.ADCMAXCONV.all = 0x000F;       	// Setup 16 conv's on SEQ1
	   AdcRegs.ADCCHSELSEQ1.all = 0x3333; 		// Iv,Iv,Iv,Iv.
	   AdcRegs.ADCCHSELSEQ2.all = 0x4444; 		// Ud,Ud,Ud,Ud.
	   AdcRegs.ADCCHSELSEQ3.all = 0x5555; 		// Ugen,Ugen,Ugen,Ugen.
	   AdcRegs.ADCCHSELSEQ4.all = 0x6666; 		// Igen,Igen,Igen,Igen.

}







