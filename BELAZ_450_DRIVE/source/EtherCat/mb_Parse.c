#include "ECAT_Common.h"  
#include "DSP2833x_Device.h"

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

extern char tx_data_mb[];

#pragma CODE_SECTION(bPutToSlave,"ramfuncs")
#pragma CODE_SECTION(doMBFunction,"ramfuncs")
/*---------------------------------------------------------------------------*/

unsigned int bPutToSlave(char *rx_data_mb,int num_slave);

extern int error_code;
extern unsigned int ControllerID;

extern int read_words_ext_ECAT(char *begin_frame);
extern int write_words_ext_ECAT(char *begin_frame);
extern int write_bit_ext_ECAT(char *begin_frame);

void doMBFunction(char* MBframe)
{
	unsigned int code_func=0;

	    code_func = MBframe[3]>>8;

		switch (code_func)
		{
				// чтение несколько регистров (User function)
			   case 0x41:
					read_words_ext_ECAT(MBframe);
			   break;

				 // запись несколько регистров (User function)
				case 0x42:
					 write_words_ext_ECAT(MBframe);
				break;

				 // запись бита в слове  (User function)
				case 0x43:
					write_bit_ext_ECAT(MBframe);
				break;

		}
}



