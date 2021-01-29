#include "hfa.h"

extern unsigned char reg_sost;
#pragma DATA_SECTION(state_controller,"STATE_CONTROLLER");

//Указатель на чек сумму рабочей программы + MAP
unsigned int *pCheckMAP = (unsigned int *)0x318000;
extern unsigned int *ver_altera;
//информация о состоянии контроллера для монитора
unsigned int state_controller[6];

void create_state_array(void);
extern unsigned int ControllerID;
int count_i=0;
long address_var[20];
long request_var[20];
void (* Addr_Func)();
unsigned long int execute_func_address=0;

#pragma CODE_SECTION(create_state_array,"secureRamFuncs")
interrupt void cpu_timer0_isr(void);
void create_state_array(void);
void read_request_var(void);

int int_var=0;
unsigned int uint_var=0;
long long_var=0;
unsigned long ulong_var=0;
float float_var=0;


void create_state_array(void)
{
		 state_controller[0]=reg_sost;
		 state_controller[1]=*ver_altera;
		 state_controller[2]= *pCheckMAP;
}

void read_request_var(void)
{
	char type=0,i=0;
	long address=0;

	// Проверяем все заказанные переменные
	for (i=0;i<20;i++)
	{
		//Если адрес не 0
		if (address_var[i]!=0)
		{
			type=(char)((address_var[i]>>24) & 0xff);
			address = address_var[i] & 0xffffff;
//			address=address>>8;

			// Если char
	/*		if (type==1 || )
			{
				request_var[i][1]= (*(unsigned char *)address) & 0xff;
			}*/
			// Если int
			 if (type==0 || type==1)
			{
				request_var[i]= *(unsigned int *)address;
			}
			// Если long
			else if (type==2 || type==3  || type==4)
			{
				request_var[i]= *(unsigned long *)address;
			}

		}
	}

	// Если пришла команда на выполнение функции
	if(execute_func_address!=0)
	{
		Addr_Func =(void (*)) execute_func_address;
		(*Addr_Func)(); //Выполнение Функции
		execute_func_address=0;
	}

}
