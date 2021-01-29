#include "hfa.h"

void InitEPwm1();
void InitEPwm2();
void InitEPwm3();
void InitEPwm4();
void InitEPwm5();
void InitEPwm6();

#pragma CODE_SECTION(InitEPwm1,"ramfuncs")
#pragma CODE_SECTION(InitEPwm2,"ramfuncs")
#pragma CODE_SECTION(InitEPwm3,"ramfuncs")
#pragma CODE_SECTION(InitEPwm4,"ramfuncs")
#pragma CODE_SECTION(InitEPwm5,"ramfuncs")
#pragma CODE_SECTION(InitEPwm6,"ramfuncs")
/*

  25000
    /\
   /  \
  /    \		(0 - 25000 - 50000)*(TB_DIV2) = (0 - 50000 - 100000)
 /      \
/        \								150000000 / 100000 = 1500 Hz
0       50000

*/

void InitEPwm1()
{
   EPwm1Regs.TBPRD = 25000;                        // Set timer period
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0;                      // Clear counter

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV2;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO and PERIOD
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;   

   // Setup compare 
   EPwm1Regs.CMPA.half.CMPA = 12500;
   EPwm1Regs.CMPB = 12500;
   
   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // Set PWM3A on Zero
   EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
   

   EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
   EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;



   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;

   EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
   EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;       // Select SOC from from CPMA on upcount
   EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

   // Interrupt where we will change the Deadband
   //EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   //EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
}

void InitEPwm2()
{
   EPwm2Regs.TBPRD = 25000;                        // Set timer period
   EPwm2Regs.TBPHS.half.TBPHS = 0;           // Phase is 0
   EPwm2Regs.TBCTR = 0;	                      // Clear counter
   
   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV2;          // Slow just to observe on the scope
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;


   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO and PERIOD
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;   

   // Setup compare 
   EPwm2Regs.CMPA.half.CMPA = 12500;
   EPwm2Regs.CMPB = 12500;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // Set PWM3A on Zero
   EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
   

   EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
   EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;
}

void InitEPwm3()
{
   EPwm3Regs.TBPRD = 25000;                   // Set timer period
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;       // Phase is 0
   EPwm3Regs.TBCTR = 0;                       // Clear counter
   
   
   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV2;          // Slow so we can observe on the scope

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO and PERIOD
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;   

   // Setup compare 
   EPwm3Regs.CMPA.half.CMPA = 12500;
   EPwm3Regs.CMPB = 12500;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // Set PWM3A on Zero
   EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
   

   EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
   EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;

}
void InitEPwm4()
{
   EPwm4Regs.TBPRD = 25000;                        // Set timer period
   EPwm4Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm4Regs.TBCTR = 0;                      // Clear counter

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
   EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV2;

   // Setup compare
   EPwm4Regs.CMPB = 12500;
   // Set actions
/*
   EPwm4Regs.ETSEL.bit.SOCAEN = 1;                	// Enable SOCA
   EPwm4Regs.ETSEL.bit.SOCASEL = 6;           		// SOCA on compare CMPB when the timer is incrementing
   EPwm4Regs.ETPS.bit.SOCAPRD = ET_1ST;           	// Generate SOCA on 1st event*/
}
void InitEPwm5()
{
	   EPwm5Regs.TBPRD = 25000;                   // Set timer period
	   EPwm5Regs.TBPHS.half.TBPHS = 0x0000;       // Phase is 0
	   EPwm5Regs.TBCTR = 0;                       // Clear counter


	   // Setup TBCLK
	   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	   EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
	   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV2;          // Slow so we can observe on the scope

	   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO and PERIOD
	 //  EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	//   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

	   // Setup compare
	   EPwm5Regs.CMPA.half.CMPA = 0;
	//   EPwm5Regs.CMPB = 12500;

	   // Set actions
	   EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;              // Set PWM3A on Zero
	   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;


	//   EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
	//   EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;
}

void InitEPwm6()
{
	   EPwm6Regs.TBPRD = 25000;                   // Set timer period
	   EPwm6Regs.TBPHS.half.TBPHS = 0x0000;       // Phase is 0
	   EPwm6Regs.TBCTR = 0;                       // Clear counter


	   // Setup TBCLK
	   EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
	   EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	   EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
	   EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV2;          // Slow so we can observe on the scope

	   EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO and PERIOD
	  // EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	   EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	 //  EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

	   // Setup compare
	   EPwm6Regs.CMPA.half.CMPA = 12500;
	 //  EPwm6Regs.CMPB = 12500;

	   // Set actions
	   EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // Set PWM3A on Zero
	   EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;


	 //  EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
	 //  EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;


	 //  EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;            // Set PWM3A on Zero
	 //  EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;
}

//===========================================================================
// End of file.
//===========================================================================
