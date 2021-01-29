//Расширенные функции ModBus

#include "DSP2833x_Device.h"
//#include "..\NETlib\multidsknet.h"

extern void Example_Error(Uint16 Status);

#pragma CODE_SECTION(read_words_ext_ECAT,"ramfuncs")
#pragma CODE_SECTION(write_words_ext_ECAT,"ramfuncs")
#pragma CODE_SECTION(write_bit_ext_ECAT,"ramfuncs")

int read_words_ext_ECAT(char *begin_frame );
int write_words_ext_ECAT(char *begin_frame);
int write_bit_ext_ECAT(char *begin_frame);

static inline unsigned short htons (unsigned short val)
{
    return ((unsigned short)((((val) & 0xff) << 8) | ((val) & 0xff00) >> 8));
}

// Чтение нескольких слов
int read_words_ext_ECAT(char *begin_frame)
{
  unsigned long address_mb_ext=0;
  unsigned int len_ADU=0,i=0;
  unsigned int *ADDRESS2=0;
  char *data=0;

  address_mb_ext = htons(*(begin_frame+4));
  address_mb_ext = address_mb_ext<<8;
  address_mb_ext = address_mb_ext | (*(begin_frame+5) & 0xff);
  len_ADU = ((*(begin_frame+5))>>8) & 0xff;

  data = begin_frame+6;

  ADDRESS2 = (unsigned int *)address_mb_ext;

  for(i=len_ADU;i>0;i--)
  {
   *data = htons(*ADDRESS2);
   data++;
   ADDRESS2++;
  }

  // общая длина
  *(begin_frame+2) = htons(len_ADU*2+6);

  return 0;
}

// Запись нескольких слов
int write_words_ext_ECAT(char *begin_frame)
{
  unsigned long address_mb_ext=0;
  unsigned int len_ADU,i=0;
  unsigned int *ADDRESS2;
  char *data=0;

  address_mb_ext = htons(*(begin_frame+4));
  address_mb_ext = address_mb_ext<<8;
  address_mb_ext = address_mb_ext | (*(begin_frame+5) & 0xff);
  len_ADU = ((*(begin_frame+5))>>8) & 0xff;

  ADDRESS2 = (unsigned int *)address_mb_ext;

  data = begin_frame+6;

  for(i=len_ADU;i>0;i--)
  {
		*ADDRESS2=htons(*data);
		data++;
	    ADDRESS2++;
  }
  
  return 0;
}


// Запись бита в слове
int write_bit_ext_ECAT(char *begin_frame)
{
  unsigned long address_mb_ext=0;
  unsigned char bit_position,value_bit=0;
  unsigned int *ADDRESS2,mask=0;

  address_mb_ext = htons(*(begin_frame+4));
  address_mb_ext = address_mb_ext<<8;
  address_mb_ext = address_mb_ext | (*(begin_frame+5) & 0xff);

  ADDRESS2 = (unsigned int *)address_mb_ext;

  bit_position = ((*(begin_frame+5))>>8) & 0xff;
  value_bit = *(begin_frame+6)  & 0xff;

   mask=mask+1;
   mask=mask<<bit_position;

  // Если установить бит в 1
   if (value_bit == 0x1)
   {
    *ADDRESS2=*ADDRESS2|mask;
   }
  // Если установить бит в 0
   else if (value_bit == 0x0)
   {
	*ADDRESS2=*ADDRESS2 & (~mask);	 
   }

  
  return 0;
}
