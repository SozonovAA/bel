/* Структуры данных для Modbus */
//#pragma DATA_SECTION (MODBUS_struct,"MODBUS_data_coil");

/*----------------------------------------**
** Адрес зоны регистров флагов - 0xA900   **
** Адрес зоны регистров хранения - 0xA940 **
**----------------------------------------*/
							  
/*--------------------**
** Команды управления **
**--------------------*/


struct control_comm
{
unsigned int frequency:8;
unsigned int reservd1 :8;
//////////////////////////////////////
unsigned int direction:1;
unsigned int action:1;
unsigned int disable_sed:1;
unsigned int disable_ab1:1;
unsigned int disable_ab2:1;
unsigned int sost_vdg1:1;
unsigned int sost_vdg2:1;
unsigned int mode1:1;
unsigned int reservd2 : 8;
/////////////////////////////////////
unsigned int mode2:1;
unsigned int mode3:1;
unsigned int ready_ees:1;
unsigned int disable_LB :1;
unsigned int disable_RB :1;
unsigned int current_control :2;					   // Режим управления (0- от СУТС,1-от "Ручного пульта",2 - от ПИРШ/ОМАП
unsigned int current_CK :1;							   // Главный ЦК в данный момент (0 - ЦК1, 1 - ЦК2)
//unsigned int disable_channel3 :1;
unsigned int reservd3 : 8;
//////////////////////////////////
//unsigned int disable_channel4 :1;
//unsigned int disable_channel5 :1;
//unsigned int disable_channel6 :1;
unsigned int reservd : 8;
/////////////////////////////////////
};

/*---------------------------------**
** Информация о состоянии СУ СЭД-М **
**---------------------------------*/
							   
struct sost__compl
{
unsigned int frequency:8;                        // бит 0 - 7 (от младшего)
unsigned int reservd:4;                          // бит 8 - 12
unsigned int current_control :2;                 // Режим управления (0- от СУТС,1-от "Ручного пульта",2 - от ПИРШ/ОМАП
unsigned int current_CK :1;                      // Главный ЦК в данный момент (0 - ЦК1, 1 - ЦК2)
unsigned int direction:1;                        // бит 15
////////////////////////////////////////////
unsigned int action:1;
unsigned int dpr_general:1;
unsigned int dpr_reserv:1;
unsigned int mode1:1;
unsigned int mode2:1;
unsigned int mode3:1;
unsigned int fault_sed:1;
unsigned int warning_sed :1;
unsigned int ready_channel1 :1;
unsigned int ready_channel2 :1;
unsigned int ready_channel3 :1;
unsigned int ready_channel4 :1;
unsigned int ready_channel5 :1;
unsigned int ready_channel6 :1;
unsigned int reservd2:2;
///////////////////////////////////////////
unsigned int state_channel1 :1;
unsigned int state_channel2 :1;
unsigned int state_channel3 :1;
unsigned int state_channel4 :1;
unsigned int state_channel5 :1;
unsigned int state_channel6 :1;

unsigned int sost_QS1 :1;
unsigned int sost_QS2 :1;
unsigned int sost_QS3 :1;
unsigned int sost_FU1 :1;
unsigned int sost_FU2 :1;
unsigned int sost_FU3 :1;
unsigned int sost_FU4 :1;
unsigned int sost_SVO :1;

unsigned int reservd3:2;
};


/*-----------------------------------**
** АПС и логические сигналы СУ СЭД-М **
**-----------------------------------*/
						   
struct SHIP1
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};

struct SHIP2
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};

struct SHIP3
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};

struct SHIP4
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};

struct SHIP5
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};

struct SHIP6
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1:16;
unsigned int AS2:16;
unsigned int Logic_signal:16;
};


struct AIN1
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};

struct AIN2
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};

struct AIN3
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};

struct AIN4
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};

struct AIN5
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};

struct AIN6
{
unsigned int PS1:16;
unsigned int PS2:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal:16;
};


struct K__PIT
{
unsigned int PS1:16;
unsigned int PS2_1:16;
unsigned int PS2_2:16;
unsigned int PS2_3:16;
unsigned int AS1_1:16;
unsigned int AS1_2:16;
unsigned int AS1_3:16;
unsigned int AS2_1:16;
unsigned int AS2_2:16;
unsigned int Logic_signal_1:16;
unsigned int Logic_signal_2:16;
};


struct K_T_P
{
unsigned int PS1_1:16;
unsigned int PS1_2:16;
unsigned int PS2_1:16;
unsigned int PS2_2:16;
unsigned int AS1:16;
unsigned int Logic_signal:16;
};



struct APS__SED
{
struct SHIP1 SHIP_1;
struct SHIP2 SHIP_2;
struct SHIP1 SHIP_3;
struct SHIP1 SHIP_4;
struct SHIP1 SHIP_5;
struct SHIP1 SHIP_6;
struct AIN1  AIN_1;
struct AIN1  AIN_2;
struct AIN1  AIN_3;
struct AIN1  AIN_4;
struct AIN1  AIN_5;
struct AIN1  AIN_6;
struct K__PIT K_PIT;
struct K_T_P  KTP;
};

struct MODBUS__struct
{
struct control_comm ctrl_comm;
//struct control_comm ctrl_comm_mestn_pult;
//unsigned int current_control;
unsigned int reservd[0x3c];
struct sost__compl sost_compl;
struct APS__SED APS_SED;
};
