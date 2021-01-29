#include "hfa.h"

//ADDRESS OF DACS

#define D42					0x13
#define D43					0x20
#define D44					0x21
#define D48					0x22
#define D49					0x23
#define D50					0x30
#define D54					0x31
#define D55					0x32
#define D56					0x33
#define D60					0x40
#define D61					0x41
#define D62					0x42

/*
#define D42					0x10
#define D43					0x10
#define D44					0x10
#define D48					0x10
#define D49					0x10
#define D50					0x10
#define D54					0x10
#define D55					0x10
#define D56					0x10
#define D60					0x10
#define D61					0x10
#define D62					0x10
*/

//COMMANDS
#define WTIR				0x0 // Write to Input Register
#define UDR					0x1 // Update DAC Register
#define WTAU				0x3 // Write to and Update
#define PD					0x4 // Power Down
#define NO					0xF // No Operation

//INTERNAL ADDRESS
#define DAC_A				0x0 
#define DAC_B				0x1 
#define ALL_DAC				0xF 

#define NUM_OF_DACS			24

#define INPUT_WORD(A,B) 	((A) << 4) + B

Uint16 DAC_ADDR[NUM_OF_DACS] = {\
D42	,\
D42	,\
D43	,\
D43	,\
D44	,\
D44	,\
D48	,\
D48	,\
D49	,\
D49	,\
D50	,\
D50	,\
D54	,\
D54	,\
D55	,\
D55	,\
D56	,\
D56	,\
D60	,\
D60	,\
D61	,\
D61	,\
D62	,\
D62	};

Uint16 DAC_VALS[NUM_OF_DACS];// = {341,682,1024,1364,1705,2048,2387,2728,3069,3410,3752,4092};

void i2cDacs();

Uint16 dac_step=0;
Uint16 dac_addr =0;
int count_i2c = 0;

//extern int f_load_koeff = 0;
int dac_write;

#pragma CODE_SECTION(i2cDacs,"ramfuncs");

int TestAddr=0;
int TestVal=0;

int fDACsWRT=0;

void i2cDacs()
{

if(hb.WriteDacs)
{
/*
	koeff.cIf = 1000;
	if(koeff.cIf > 2000) koeff.cIf = 2000;
*/

	DAC_VALS[0] = koeff.cIf + 2048;
	DAC_VALS[1] = 2048 - koeff.cIf;

	DAC_VALS[2] = koeff.cIf + 2048;
	DAC_VALS[3] = 2048 - koeff.cIf;

	DAC_VALS[4] = koeff.cIf + 2048;
	DAC_VALS[5] = 2048 - koeff.cIf;

	DAC_VALS[6] = koeff.cIv;
	DAC_VALS[7] = 0;

	DAC_VALS[8] = koeff.cUd;
	DAC_VALS[9] = 0;

	DAC_VALS[10] = koeff.cIgen;
	DAC_VALS[11] = 0;

	DAC_VALS[12] = koeff.cIf + 2048;
	DAC_VALS[13] = 2048 - koeff.cIf;

	DAC_VALS[14] = koeff.cIf + 2048;
	DAC_VALS[15] = 2048 - koeff.cIf;

	DAC_VALS[16] = koeff.cIf + 2048;
	DAC_VALS[17] = 2048 - koeff.cIf;

	DAC_VALS[18] = 4000;
	DAC_VALS[19] = 100;

	DAC_VALS[20] = 4000;
	DAC_VALS[21] = 100;

	DAC_VALS[22] = 4000;
	DAC_VALS[23] = 100;

/*
	//D42
	DAC_VALS[0] = 22 << 4;
	DAC_VALS[1] = 22 << 4;
	//D43
	DAC_VALS[2] = 44 << 4;
	DAC_VALS[3] = 44 << 4;
	//D44
	DAC_VALS[4] = 66 << 4;
	DAC_VALS[5] = 66 << 4;
	//D48
	DAC_VALS[6] = 88 << 4;
	DAC_VALS[7] = 88 << 4;
	//D49
	DAC_VALS[8] = 110<< 4;
	DAC_VALS[9] = 110 << 4;
	//D50
	DAC_VALS[10] = 132 << 4;
	DAC_VALS[11] = 132 << 4;
	//D54
	DAC_VALS[12] = 154 << 4;
	DAC_VALS[13] = 154 << 4;
	//D55
	DAC_VALS[14] = 176 << 4;
	DAC_VALS[15] = 176 << 4;
	//D56
	DAC_VALS[16] = 198 << 4;
	DAC_VALS[17] = 198 << 4;
	//D60
	DAC_VALS[18] = 220 << 4;
	DAC_VALS[19] = 220 << 4;
	//D61
	DAC_VALS[20] = 242 << 4;
	DAC_VALS[21] = 242 << 4;
	//D62
	DAC_VALS[22] = 255 << 4;
	DAC_VALS[23] = 255 << 4;
*/

		dac_step++;
			
			if(dac_step == 3)
			{

				I2caRegs.I2CSAR 	= DAC_ADDR[dac_addr];	//setup slave address
				I2caRegs.I2CCNT 	= 0x3;								// how many data bytes to transmit 
				I2caRegs.I2CDXR 	= INPUT_WORD(WTAU,DAC_A);				
				I2caRegs.I2CDXR		= (DAC_VALS[dac_addr] >> 4) & 0xFF;	
				I2caRegs.I2CDXR		= (DAC_VALS[dac_addr] << 4) & 0xFF;
				I2caRegs.I2CMDR.all = 0x6620;

			   dac_addr++;

			}

				if(dac_step == 6)
				{

					I2caRegs.I2CSAR 	= DAC_ADDR[dac_addr];	//setup slave address
					I2caRegs.I2CCNT 	= 0x3;	// how many data bytes to transmit
					I2caRegs.I2CDXR 	= INPUT_WORD(WTAU,DAC_B);	
					I2caRegs.I2CDXR		= (DAC_VALS[dac_addr] >> 4) & 0xFF;	
					I2caRegs.I2CDXR		= (DAC_VALS[dac_addr] << 4) & 0xFF;
					I2caRegs.I2CMDR.all = 0x6620;

					dac_addr++;

					dac_step = 0;

					if(dac_addr == NUM_OF_DACS)
					{
						UNSET(hb.WriteDacs);
						dac_addr=0;

						koeff.WriteDacs = 0;

						fDACsWRT = 100;
					}

				} 

}// end of if (write_i2c)
}//end of test_i2c()
