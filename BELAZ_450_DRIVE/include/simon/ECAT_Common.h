/** @file ECAT_Common.h
	@brief Заголовочный файл кода, общего для Slave и Master EtherCAT.
	@author
*/ 


#include "multidsknet.h"

extern int transmit_buffer[50];
extern  int ecat_regul_data[250];
extern int data_transmit_size,data_receive_size;

extern long SMC91C111_FIRST;
extern long SMC91C111_SECOND;
extern void init_ethernet(long num_eth);
extern void slave_background_modbus(int num_ecat);
extern long SMC91C111_FIRST;
extern long SMC91C111_SECOND;
extern int slave_init(int num_ecat,long address_eth,int ID);
extern void TX_ECAT_Frame(void);
extern int detect_main_CK(void);

struct ECAT__RX{
	int regul_rx_1;
	int modbus_rx_1;
	int regul_rx_2;
	int modbus_rx_2;
	int ID_ECAT;
	long num_ethetnet_modbus_rx;
	int PTR;
};


#define CK_altera 0xf201			// 0xFC03
#define AIN_altera 0xFE03			//0xFE01
#define SHIP_altera 0xFD02
#define KTP_altera 0xFA05
#define KPIT_altera 0xF906

enum NET_addr
{
	BROAD=0,
	KK1=1,
	KK2=2,
	KK3=3,
	KK4=4,
	KK5=5,
	KK6=6,
	KK7=7,
	KK8=8,
	KK9=9,
	KK10=10,
	KTP1=11,
	KTP2=12,
	KPS1=13,
	KPS2=14,
	res1=15,
	res2=16,
	CK1=17,
	CK2=18,
};

/**
Адреса контроллеров
*/
#define	 KABINNIY_KONTR 1

#define	 PK1	2
#define	 PK2	3
#define  PK3	4
#define	 TEMP_CONTR	5
#define	 last_frame	1
#define	 not_last_frame	0
#define slave_number 18


struct number_slave_in__chain{
	int ethernet_1;
	int tx_frame_ethernet_1;
	int ethernet_2;
	int tx_frame_ethernet_2;
};


/*
enum NET_addr
{
//	BROAD=0,
	KABIN=1,
	PK1=2,
	PK2=3,
	PK3=4,
	TEMP_CONTR=5,
};
*/
enum slaveModbusModes {
	mm_nop,
	mm_getFromMonitor,
	mm_sendRequest,
	res_ready,
	mm_waitRequest,
	mm_sendResult,
	mm_waitResult,
	mm_DMA_working,
	mm_wait_sendToMonitor,
	mm_sendToMonitor
};


struct MB_frame_sost{
	SOCKET *fd;
	int controller_in_net;
	int slaveModbusModes;		// NOP; Frame для передачи в ECAT; Frame wait_answer; ready_answer_mb; answer_monitor;
	int array_MB[130];
//	int permanent_data_rx[20];
};


/**
Константы состояний EtherCAT
*/
enum state
{
	/// Инициализация
	INIT = 0x01,
	/// Подготовительный режим	
	PREOP = 0x02,
	/// Безопасный режим
	SAFEOP = 0x04,
	/// Рабочий режим
	OP = 0x08
};

/**
Команды EtherCAT
*/
enum ECAT_command
{
	/// No Operation
	/// Slave ignores command
	NOP  =	 0,

	/// Auto Increment Read
	/// Slave increments address. Slave puts read data
	/// into the EtherCAT datagram if received address is
	/// zero.
	APRD =	 1,

	/// Auto Increment Write
	/// Slave increments address. Slave writes data into
	/// memory location if received address is zero.
	APWR =	 2,

	/// Auto Increment Read Write
	/// Slave increments address. Slave puts read data
	/// into the EtherCAT datagram and writes the data
	/// into the same memory location if received address
	/// is zero.
	APRW =	 3,

	/// Configured Address Read Slave puts read data into the EtherCAT datagram
	/// if address matches with one of its configured
	/// addresses
	FPRD =	 4,

	/// Configured Address Write
	/// Slave writes data into memory location if address
	/// matches with one of its configured addresses
	FPWR =	 5,

	/// Configured Address Read Write
	/// Slave puts read data into the EtherCAT datagram
	/// and writes data into the same memory location if
	/// address matches with one of its configured
	/// addresses
	FPRW =	 6,

	/// Broadcast Read
	/// All slaves put logical OR of data of the memory
	/// area and data of the EtherCAT datagram into the
	/// EtherCAT datagram
	BRD  =	 7,

	/// Broadcast Write
	/// All slaves write data into memory location
	BWR  =	 8,

	/// Broadcast Read Write
	/// All slaves put logical OR of data of the memory
	/// area and data of the EtherCAT datagram into the
	/// EtherCAT datagram, and write data into memory
	/// location. BRW is typically not used.
	BRW  =	 9,

	/// Logical Memory Read 
	/// Slave puts read data into the EtherCAT datagram
	/// if received address matches with one of the
	/// configured FMMU areas for reading.
	LRD  =	10,

	/// Logical Memory Write
	/// Slaves writes data to into memory location if
	/// received address matches with one of the
	/// configured FMMU areas for writing.
	LWR  =	11,

	/// Logical Memory Read Write
	/// Slave puts read data into the EtherCAT datagram
	/// if received address matches with one of the
	/// configured FMMU areas for reading. Slaves writes
	/// data to into memory location if received address
	/// matches with one of the configured FMMU areas
	/// for writing.
	LRW  =	12,

	/// Auto Increment Read Multiple Write
	/// Slave increments address. Slave puts read data
	/// into the EtherCAT datagram if received address is
	/// zero, otherwise slave writes the data into memory
	/// location.
	ARMW =	13,

	/// Configured Read Multiple Write
	/// Slave puts read data into the EtherCAT datagram
	/// if address matches with one of its configured
	/// addresses, otherwise slave writes the data into
	/// memory location.
	FRMW =	14
};

//--------------------------------------------------
#define TX_SIZE	24
#define RX_SIZE	368

#define MODBUS_DATA_SIZE	260
#define MODBUS_FLAG_OFFSET	256
#define SLAVE_MODBUS_RX_OFFSET	1024

//--------------------------------------------------

#define SLAVE_MODBUS_TX_OFFSET	1284

#define MAILBOX_SIZE	392
#define ECAT_DATAGRAMM_HEADER_SIZE	10

#define TX_FRAME_SIZE	34
#define RX_FRAME_SIZE	378


#define ECAT_FRAME_HEADER_SIZE	16
/*#define ECAT_DATA_INDEX 26*/
#define ECAT_WKC_SIZE	2

//header_size
#define MB_TX_OFFSET	16
//	=16+12+	24		tx_size
#define MODBUS_TX_OFFSET	52
//	=52+12+	260		modbus_data_size
#define SMALL_OFFSET	324
//	=324+12+	2
#define MB_RX_OFFSET	338
//	=338+12+	368		rx_size
#define MODBUS_RX_OFFSET	718
//	=718+12+	260		modbus_data_size
#define BIG_FRAME_ETH_SIZE	990

//13 + (RX_SIZE >> 1)
#define ECAT_MODBUS_CMD_OFFSET 197

//5 + ECAT_MODBUS_CMD_OFFSET
#define ECAT_MODBUS_DATA_OFFSET 202

//982 + 8




/*#define OFFSET_MB_TX ECAT_FRAME_HEADER_SIZE
#define OFFSET_MB_RX OFFSET_MB_TX + ECAT_DATAGRAMM_HEADER_SIZE + TX_SIZE + ECAT_WKC_SIZE
//#define ECAT_MB_FRAME_SIZE MB_RX_OFFSET + (ECAT_DATAGRAMM_HEADER_SIZE + RX_SIZE + ECAT_WKC_SIZE)
#define ECAT_MB_FRAME_SIZE 424
*/

//#define MB_RX_OFFSET ECAT_DATA_INDEX+(TX_SIZE>>1)+ECAT_WKC_SIZE+ECAT_DATAGRAMM_HEADER_SIZE;

//#define MODBUS_QUEUE_LEN 512


enum arrayStates {
	arr_resetTx=0,
	arr_waitResetRx=0x1,
	arr_resetRx=0x2,
	arr_reset=0x4,
	arr_run=0x8,
	arr_stopTx=0x10,
	arr_waitStopRx=0x20,
	arr_stopRx=0x40,
	arr_stop=0x80,
};

#define SLAVE_MAX_COUNT 4


/*
	CK1,// = 	0,		0
	AIN1,// =	15,		1
	AIN2,// =	4,		2
	AIN3,// =	6,		3
	AIN4,// =	9,		4
	AIN5,// =	11,		5
	AIN6,// =	13,		6
	SHIP1,// =	14,		7
	SHIP2,// =	16,		8
	SHIP3,// =	5,		9
	SHIP4,// =	8,		10
	SHIP5,// =	10,		11
	SHIP6,// =	12,		12
	KS1,// = 	1,		13
	KS2,// = 	2,		14
	KTP,// = 	3,		15
	KSHP,// =	7,		16
	CK1,// = 	0,		17
	CK2// =		17		18
*/

/*#pragma DATA_SECTION(modbus_from_ecat,"secureRamVars")
static unsigned int modbus_from_ecat[SLAVE_MAX_COUNT]=
{//#modbus_id  #name	#ecat_position
	17,//	CK1 = 	0,
	13,//	KS1 = 	1,
	14,//	KS2 = 	2,
	15,//	KTP = 	3,
	2,//	AIN2 =	4,
	9,//	SHIP3 =	5,
	3,//	AIN3 =	6,
	16,//	KSHP =	7,
	10,//	SHIP4 =	8,
	4,//	AIN4 =	9,
	11,//	SHIP5 =	10,
	5,//	AIN5 =	11,
	12,//	SHIP6 =	12,
	6,//	AIN6 =	13,
	7,//	SHIP1 =	14,
	1,//	AIN1 =	15,
	8,//	SHIP2 =	16,
	18//	CK2 =	17
};

/*#pragma DATA_SECTION(ecat_from_modbus,"secureRamVars")
static unsigned int ecat_from_modbus[SLAVE_MAX_COUNT+1]=
{		//  #name	#ecat	#modbus_id
	CK1,// = 	0,		0
	AIN1,// =	15,		1
	AIN2,// =	4,		2
	AIN3,// =	6,		3
	AIN4,// =	9,		4
	AIN5,// =	11,		5
	AIN6,// =	13,		6
	SHIP1,// =	14,		7
	SHIP2,// =	16,		8
	SHIP3,// =	5,		9
	SHIP4,// =	8,		10
	SHIP5,// =	10,		11
	SHIP6,// =	12,		12
	KS1,// = 	1,		13
	KS2,// = 	2,		14
	KTP,// = 	3,		15
	KSHP,// =	7,		16
	CK1,// = 	0,		17
	CK2// =		17		18
};*/

#define RX_ADDR 0x170

#define LOGICSTATE_OFFSET 0
#define KS1_OFFSET 4
#define KS2_OFFSET 10
#define KK_OFFSET 16


#ifndef CHAIN_C_FILE

extern unsigned char used_nodes[20];

#endif

#define ECAT_USED_SLAVE_COUNT 6

#define ECAT_NUM_OF_VARS 27
#define ECAT_NUM_OF_SAMPLES 2400

/*#define ECAT_VAR_RD_OFFSET 0x1400
#define ECAT_VAR_WR_OFFSET 0x1300
*/

//#define ECAT_SLAVE_RD_OFFSET 0x400
//#define ECAT_SLAVE_WR_OFFSET 0x300


//enum types {type_NOP=0, type_char=1, type_int=2, type_long=3, type_byte=4, type_massive=5};


/*
#define OFFSET_SMALL ECAT_FRAME_HEADER_SIZE
#define OFFSET_MODBUS_RX OFFSET_SMALL + (ECAT_DATAGRAMM_HEADER_SIZE + 2 + ECAT_WKC_SIZE)
#define OFFSET_MODBUS_TX OFFSET_MODBUS_RX +(ECAT_DATAGRAMM_HEADER_SIZE + MODBUS_DATA_SIZE + ECAT_WKC_SIZE)
#define ECAT_BG_FRAME_SIZE OFFSET_MODBUS_TX + (ECAT_DATAGRAMM_HEADER_SIZE + MODBUS_DATA_SIZE + ECAT_WKC_SIZE)
//ECAT_BG_FRAME_SIZE 574
*/

//#define BIG_FRAME_ETH_SIZE 574

/*
#define MODBUS_TX_OFFSET 424
#define MODBUS_RX_OFFSET 696
#define SMALL_OFFSET 968
#define CLEAR_OFFSET 982

#define SLAVE_ARRAY_FLAGS_OFFSET 0x450
*/


 struct ECAT_controller
{
	unsigned int *ecat_reg;
	unsigned int *ecat_WRITE_permanent_data;
	unsigned int *ecat_READ_permanent_data;
	unsigned int *ecat_WRITE_MB_data;
	unsigned int *ecat_READ_MB_data;

	unsigned int slave_state;
	unsigned int requested_state;
	unsigned int slave_counter;
	unsigned int modbus_counter;
};

/**
@def Slave_ALStatus
адрес регистра ALStatus
*/
#define Slave_ALStatus	0x0130

/**
@def Slave_ALControl
адрес регистра ALControl
*/
#define Slave_ALControl	0x0120

/**
@def ECAT_ARRAY_CONTROL
адрес флагов управления массивом
*/
#define ECAT_ARRAY_CONTROL 0x100


/**
@def Slave_DLStatus
адрес регистра DLStatus
*/
#define Slave_DLStatus	0x0110

/**
@def Slave_Address
адрес регистра сконфигурированного адреса Slave (ECAT)
*/
#define Slave_Address	0x010


/**
@def Slave_Address_Alias
адрес регистра сконфигурированного адреса Slave (контроллером)
*/
#define Slave_Address_Alias	0x012

/**
Установка состояния
@param state Состояние из набора state
@see #state
*/
void setState(int num_ecat,int state);

/**
Получение запроса состояния от Master
@return Запрашиваемое состояние
@see #state
*/
int getRequestedState(void);



/**
Текущее состояние Slave
@return Текущее состояние
@see #state
*/
int getState(int num_ecat);

/**
Запрос состояния связи
@return Содержимое регистра Slave Data Link Status
*/
int getDLStatus(void);

/**
Основной цикл работы Slave
@return Состояние Slave
@see #state
*/
int slave_main_routine(void);

#define ECAT_DATARAM_SIZE 0x800

#define ECAT_CONTROLLER_COUNT 1







//---------------------------------------------- DEBUG

//#define ECAT_DEBUG_SIGNALS
//#define ECAT_MODBUS_DEBUG
