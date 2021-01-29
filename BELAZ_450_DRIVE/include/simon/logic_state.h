struct LOGIC_STATE_BIT							//структура данных для управления включением/выключением комплекса
{
	unsigned int D_Cntrl_Inv_1_Ready:1;		//готовность контроллера АИН1
	unsigned int D_Cntrl_Inv_2_Ready:1;		//готовность контроллера АИН2
	unsigned int D_Cntrl_Inv_3_Ready:1;		//готовность контроллера АИН3
	unsigned int D_Cntrl_Inv_4_Ready:1;		//готовность контроллера АИН4
	unsigned int D_Cntrl_Inv_5_Ready:1;		//готовность контроллера АИН5
	unsigned int D_Cntrl_Inv_6_Ready:1;		//готовность контроллера АИН6
	unsigned int D_Cntrl_Pwm_1_Ready:1;		//готовность контроллера ШИП1
	unsigned int D_Cntrl_Pwm_2_Ready:1;		//готовность контроллера ШИП2
	unsigned int D_Cntrl_Pwm_3_Ready:1;		//готовность контроллера ШИП3
	unsigned int D_Cntrl_Pwm_4_Ready:1;		//готовность контроллера ШИП4
	unsigned int D_Cntrl_Pwm_5_Ready:1;		//готовность контроллера ШИП5
	unsigned int D_Cntrl_Pwm_6_Ready:1;		//готовность контроллера ШИП6
	unsigned int D_Cntrl_Inv_1_Start:1;		//разрешение работы контроллера АИН1
	unsigned int D_Cntrl_Inv_2_Start:1;		//разрешение работы контроллера АИН2
	unsigned int D_Cntrl_Inv_3_Start:1;		//разрешение работы контроллера АИН3
	unsigned int D_Cntrl_Inv_4_Start:1;		//разрешение работы контроллера АИН4
	unsigned int D_Cntrl_Inv_5_Start:1;		//разрешение работы контроллера АИН5
	unsigned int D_Cntrl_Inv_6_Start:1;		//разрешение работы контроллера АИН6
	unsigned int D_Cntrl_Pwm_1_Start:1;		//разрешение работы контроллера ШИП1
	unsigned int D_Cntrl_Pwm_2_Start:1;		//разрешение работы контроллера ШИП2
	unsigned int D_Cntrl_Pwm_3_Start:1;		//разрешение работы контроллера ШИП3
	unsigned int D_Cntrl_Pwm_4_Start:1;		//разрешение работы контроллера ШИП4
	unsigned int D_Cntrl_Pwm_5_Start:1;		//разрешение работы контроллера ШИП5
	unsigned int D_Cntrl_Pwm_6_Start:1;		//разрешение работы контроллера ШИП6
	unsigned int fstart:1;
	unsigned int fstop:1;
	unsigned int fpow_sup_parallel:1;
	unsigned int fpow_sup_serial:1;
	unsigned int fpow_sup_ready:1;
	unsigned int fdpr:1;
	unsigned int fno_dpr:1;
	unsigned int rsvd:1;
};

union LOGIC_STATE							//структура данных для управления включением/выключением комплекса
{
	struct LOGIC_STATE_BIT bit;
	unsigned long int all;
};

struct ENABLE_CONTROLLERS					//структура данных для выбора работающих контроллеров при управлении от монитора
{
	unsigned int enable_Pwm_6:1;
	unsigned int enable_Inv_6:1;
	unsigned int enable_Pwm_5:1;
	unsigned int enable_Inv_5:1;
	unsigned int enable_Pwm_4:1;
	unsigned int enable_Inv_4:1;
	unsigned int enable_Pwm_3:1;
	unsigned int enable_Inv_3:1;
	unsigned int enable_Pwm_2:1;
	unsigned int enable_Inv_2:1;
	unsigned int enable_Pwm_1:1;
	unsigned int enable_Inv_1:1;
	unsigned int rsvd:4;

};




extern union LOGIC_STATE logic_state;
extern struct ENABLE_CONTROLLERS enable_controllers;
