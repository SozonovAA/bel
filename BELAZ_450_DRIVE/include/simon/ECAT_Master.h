/** @file ECAT_Master.h
	@brief Заголовочный файл кода EtherCAT Master.
	@author Ступаков М.С.
*/ 
//#include "Ethernet_Util.h"

/** @def RECEIVE_DELAY 
Задержка между отправкой и приёмом фрейма EtherCAT
*/
#define RECEIVE_DELAY 10000

/**
	Идентификаторы фреймов EtherCAT, соответствующих командам инициализации
*/
enum commands_idx 
{
	/**	Получение состояния Slave широковещательным методом,
	подходит для состояния INIT.
	@see #state
	*/
	cmd_get_all_status =		1,

	/**	Установка состояния Slave методом автоинкрементной адресации,
	подходит для состояния INIT.
	@see #state
	*/
	cmd_get_slave_status =		2,

	/**	Установка адреса Slave методом автоинкрементной адресации.
	@see #NODEADDR
	*/
	cmd_set_state =	3,


	/**
	Очищаем почтовый ящик всех slave, устанавливаем данные Master
	*/
	cmd_tx_mailbox =	0x4,

	/**
	Считываем почтовый ящик всех slave
	*/
	cmd_rx_mailbox =	0x4,

	/**	Получение состояния Slave обращением по настроенному адресу узла
	@see #NODEADDR
	*/
	cmd_get_NODE_ADDR =	5,

		/**	Получение состояния Slave обращением по настроенному адресу узла
	@see #NODEADDR
	*/
	cmd_set_NODE_ADDR =	6,


	/**
	Modbus
	*/
	cmd_modbusRequest=0xa,
    cmd_modbusResult=0xb
};


/**
 * @brief 
 * @param slave
 * @param addr
 */
void setSlaveNodeAddr(unsigned int slave, unsigned int addr);

/**
 * @brief 
 */
void transmit_broadcast_init(unsigned int);

/**
 * @brief 
 */
void ecat_react_mailbox_tx();

/**
 * @brief
 */
void ecat_react_mailbox_rx();
void ecat_react_modbusRequest(unsigned int request_id, unsigned int wkc); 
void ecat_react_modbusResult(); 
void ecat_react_small(unsigned int wkc);


void ecat_modbusRequest();
void ecat_modbusResult();
void ecat_modbusSuccess();
void ecat_modbusFailure(unsigned int err);
void modbusBgReplyParse(void);

unsigned int ecat_from_modbus(unsigned int controller_id);

//#define SMALL_CONTENT_OFFSET ECAT_DATAGRAMM_HEADER_SIZE+(SMALL_OFFSET-MB_TX_OFFSET)>>1

void ecat_background_routine(void);


typedef struct ECAT_Slave_flags_bit
{
	unsigned int	askNodeAddr:1;
	unsigned int	hasNodeAddr:1;
	unsigned int	hasClearFMMU:1;
	unsigned int	hasClearSM:1;
	unsigned int	step4:1;
	unsigned int	step5:1;
	unsigned int	step6:1;
	unsigned int	step7:1;
	unsigned int	step8:1;
	unsigned int	step9:1;
	unsigned int	stepA:1;
	unsigned int	stepB:1;
	unsigned int	stepC:1;
	unsigned int	stepD:1;
	unsigned int	stepE:1;
	unsigned int	stepF:1;
} ECAT_Slave_flags_bit;

typedef union ECAT_Slave_flags
{
	struct ECAT_Slave_flags_bit fields;
	unsigned int all;
} ECAT_Slave_flags;

//enum varWrModes {varWrMode_nop, varWrMode_setRequest, varWrMode_getResult, varWrMode_waitRequest, varWrMode_waitResult, varWrMode_success, varWrMode_failure};
//enum varRdModes {varRdMode_nop, varRdMode_setRequest, varRdMode_getResult, varRdMode_waitRequest, varRdMode_waitResult, varRdMode_success, varRdMode_failure};


enum slaveModbusFrameModes {
	mf_nop,
	mf_Request,
	mf_Result,
	mf_ClearFMMU,
	mf_ClearSM
};

enum masterModbusCmdModes {
	mCmd_nop,
	mCmd_tx,
	mCmd_wait,
	mCmd_copyDma,
	mCmd_waitParse,
	mCmd_parse
};

enum ethModes {
	eth_nop,
	eth_tx,
	eth_waitRx,
	eth_DMAwork,
	eth_waitParse,
	eth_Parse,
	eth_release
};


#define DIR_TO_SLAVE 0
#define DIR_TO_MONITOR 1

//#define MODE_REQUEST 1
//#define MODE_RESULT	 2
//#define MODE_RESULT	 2
//#define MODE_RESULT	 2
//#define MODE_RESULT	 2


typedef struct ECAT_Slave
{
	unsigned char 	modbus_mode;
	unsigned int 	modbus_watchdog;
	unsigned int 	modbus_cmd_id;

	unsigned int 	number_modbus;

	unsigned char	state;
	unsigned int	nodeAddress;

	ECAT_Slave_flags flags;
} ECAT_Slave;



typedef struct ECAT_Datagramm_header_bit
{
	/// Cmd [BYTE] EtherCAT Command Type (see 2.6)
	unsigned char cmd:8;

	/// Idx [BYTE] The index is a numeric identifier used by the master for
	/// identification of duplicates/lost datagrams, that shall not be
	/// changed by EtherCAT slaves
	unsigned char idx:8;

	/// Address BYTE[4] Address (Auto Increment, Configured Station Address, or Logical
	/// Address, see 2.3)
	unsigned char addr[4];

	/// Len [11 bit] Length of the following data within this datagram
	unsigned int len:11;

	/// Reserved, 0
	unsigned char reserved:3;

	/// Circulating frame:
	/// 0: Frame is not circulating
	/// 1: Frame has circulated once
	unsigned char circulating:1;

	/// More [1 bit] More EtherCAT datagrams
	/// 0: Last EtherCAT datagram
	/// 1: More EtherCAT datagrams will follow
	unsigned char more:1;

	/// IRQ [WORD] EtherCAT Interrupt Request registers of all slaves combined with
	/// a logical OR
	unsigned int IRQ:16;
} ECAT_Datagramm_header_bit;

/*#define ECAT_DATAGRAMM_HEADER_SIZE 5
#define ECAT_FRAME_HEADER_SIZE 8
#define ECAT_DATA_INDEX 13
#define ECAT_WKC_SIZE 1
*/

typedef union ECAT_Datagramm_header
{
	ECAT_Datagramm_header_bit fields;
	unsigned char all[10];
} ECAT_Datagramm_header;

typedef struct ModbusProcess
{
	Uint16 state;
	Uint16 frameMode;
	Uint16 target;
	Uint16 rxWd;
} ModbusProcess;


void transmit_BG_Frame(void);

#define MODBUS_FLAG_WD 0x1FFF

#define ECAT_MASTER_MB_OFFSET 12

