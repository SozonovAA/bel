/***********************************************************************************/
// Распределение адресного пространства EtherCAT
/*
 * 	0x200800   (0x1000)     BWR запись постоянных данных
 * 	0x200880   (0x1100)     BRD чтение постоянных данных
 * 	0x200A00   (0x1400)     MB WR запись ModBus посылки
 * 	0x200B00   (0x1600)     MB RD чтение ModBus посылки
 */


#include "ECAT_Common.h"
#include "multidsknet.h"
#include "ECAT_DATA.h"

struct ECAT_controller ecat[2];
unsigned int *modbus_buffer = (unsigned int *)0x200B00;
extern unsigned int ControllerID;
extern void doMBFunction(char* MBframe);

void fill_data_for_oscil(void);
#pragma CODE_SECTION(fill_data_for_oscil,"secureRamFuncs")

#pragma CODE_SECTION(slave_background_modbus,"secureRamFuncs")
#pragma CODE_SECTION(getState,"secureRamFuncs")

struct data_for_transmit *data_WR_in_ECAT_1;
struct data_for_transmit *data_WR_in_ECAT_2;

struct data_for_transmit *data_from_KK;
struct data_for_receive *data_for_KK;

long address_for_oscil[20];
unsigned int counter_oscil;
unsigned int data_for_oscil[20];

/**
Установка состояния
@param state Состояние из набора state
@see #state
*/
void setState(int num_ecat,int state)
{
	ecat[num_ecat].ecat_reg[Slave_ALStatus >>1] = state;
}

/**
Текущее состояние Slave
@return Текущее состояние
@see #state
*/
int getState(int num_ecat)
{
	return(ecat[num_ecat].ecat_reg[Slave_ALStatus >>1]);
}

/**
Адрес Slave полученный от мастера
@return Текущее состояние
@see #state
*/
int getAddress(int num_ecat)
{
	return(ecat[num_ecat].ecat_reg[Slave_Address >>1]);
}

/**
Установка адреса
@param state Состояние из набора state
@see #state
*/
void setAddressAlias(int address)
{
	ecat[0].ecat_reg[Slave_Address_Alias >>1] = address;
	ecat[1].ecat_reg[Slave_Address_Alias >>1] = address;
}


int slave_init(int num_ecat,long address_ECAT,int ID)
{
	int i=0;
		ecat[num_ecat].ecat_reg = (unsigned int *)( address_ECAT);
		ecat[num_ecat].ecat_WRITE_permanent_data = ecat[num_ecat].ecat_reg + 0x800;
		ecat[num_ecat].ecat_READ_permanent_data = ecat[num_ecat].ecat_reg + 0x880;
		ecat[num_ecat].ecat_WRITE_MB_data = ecat[num_ecat].ecat_reg + 0xA00;
		ecat[num_ecat].ecat_READ_MB_data = ecat[num_ecat].ecat_reg + 0xB00;
		ecat[num_ecat].slave_state = 0;
		ecat[num_ecat].requested_state = 0;
		ecat[num_ecat].slave_counter = 0;
		ecat[num_ecat].modbus_counter = 0;

		setAddressAlias(ID);

		setState(num_ecat,INIT);
		setState(num_ecat,PREOP);
		setState(num_ecat,SAFEOP);
		setState(num_ecat,OP);

		*ecat[num_ecat].ecat_READ_MB_data = 0;
		*(ecat[num_ecat].ecat_READ_MB_data+1) = 0;

		for(i=0;i<500;i++)
		{
			while(*(ecat[num_ecat].ecat_WRITE_permanent_data+i)!=0)
			*(ecat[num_ecat].ecat_WRITE_permanent_data+i)=0;
		}


		if(getState(num_ecat) == OP)
			return 1;
		else
			return 0;

}

int detect_ECAT_chip(long address)
{

	if(*((int *)address) !=0x0011 || *((int *)(address+2)) !=0x0808)
	{
		return 0;
	}
	return 1;
}


void init_ECAT(void)
{

	while(detect_ECAT_chip(0x200000)==0)
	{}

	// Ожидаем пока ECAT контроллер инициализируется
	while(slave_init(0,0x200000,ControllerID)==0)
	{}

	data_from_KK = (struct data_for_transmit *)(ecat[0].ecat_WRITE_permanent_data);
	data_for_KK =  (struct data_for_receive *)(ecat[0].ecat_READ_permanent_data);

	memset(address_for_oscil, 0, sizeof(address_for_oscil));
	memset(data_for_oscil, 0, sizeof(data_for_oscil));

}

void slave_background_modbus(int num_ecat)
{
	unsigned int i=0,k=0,len,ID;

//	if(*((int *)0x200008) !=0/* && ControllerID==0*/  && detect_ECAT_chip(0x200000)==1)
//		ControllerID =  *((int *)0x200008);

	if(getState(0)!=8)
		slave_init(0,0x200000,ControllerID);

	if( *ecat[num_ecat].ecat_WRITE_MB_data==1)
	{
		len = htons(ecat[num_ecat].ecat_WRITE_MB_data[2/*3*/]);
		ID = ecat[num_ecat].ecat_WRITE_MB_data[3/*4*/] & 0xff;


		if (ControllerID == ID)
		{
			for(i=0; i < (len/2 + 4); i++)
			{
				modbus_buffer[k]= ecat[num_ecat].ecat_WRITE_MB_data[i];
				k++;
			}


			doMBFunction((char *)modbus_buffer);

			 *ecat[num_ecat].ecat_READ_MB_data= 1;
		}

		// Сбрасываем флаг о том что пришло Modbus сообщение
		*(ecat[num_ecat].ecat_WRITE_MB_data)=0;
	}

	// Переносим состояние о том готово ли Modbus сообщение для ЦК для чтения  (первые 2 слова в постоянных данных номер бита соответствует Modbus ID и ID ECAT контроллера)
	if(ControllerID<16)
	{
		*ecat[num_ecat].ecat_READ_permanent_data =(*ecat[num_ecat].ecat_READ_MB_data)<<ControllerID;
		*(ecat[num_ecat].ecat_READ_permanent_data+1)=0;
	}
	else
	{
		*ecat[num_ecat].ecat_READ_permanent_data=0;
		*(ecat[num_ecat].ecat_READ_permanent_data+1) =(*ecat[num_ecat].ecat_READ_MB_data)<<(ControllerID-16);
	}


}

void fill_data_for_oscil(void)
{
	int ID=0,i=0;
	long address=0;

	  for(i=0;i<10;i++)
	  {
		  ID = address_for_oscil[i]>>24;
		  address = address_for_oscil[i] & 0xffffff;

		  if(ControllerID == ID && address !=0)
		  {
			  data_for_KK->data_for_oscil[i]=  *((int *)address);
		  }
		  else
		  {
			  data_for_KK->data_for_oscil[i] = 0;
		  }
	  }
}






