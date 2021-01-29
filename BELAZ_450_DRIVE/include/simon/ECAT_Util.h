/** @file ECAT_Util.h
	@brief Заголовочный файл функций отправки и приёма EtherCAT-фреймов.
	@author Ступаков М.С.
*/ 



/*
typedef struct ECAT_Datagramm
{
	ECAT_Datagramm_header header;
	/// Data BYTE[n] Read/Write Data
	unsigned char *data;

	/// WKC WORD Working Counter (see 2.4)
	/// Read command: Successful read +1, No success = no change
	/// Write command: Successful write +1, No success = no change
	/// ReadWrite command: Successful read +1, Successful write +2, Successful read and write +3
	unsigned char wkc[ECAT_WKC_SIZE];
} ECAT_Datagramm;

typedef struct ECAT_queue_el
{
	ECAT_Datagramm *datagramm;
	struct ECAT_queue_el *next;
} ECAT_queue_el;

typedef struct ECAT_queue
{
	unsigned int count;
	unsigned int length;
	struct ECAT_queue_el *first;
	struct ECAT_queue_el *last;
} ECAT_queue;
*/


/*#define ECAT_TX_SIZE 2
#define ECAT_RX_SIZE 2

#define ETHERNET_MAX_FRAME_SIZE 1514
#define MIN_SHORT_FRAME 60
#define ECAT_MAX_DATA_SIZE 1486
*/


/**
 * @brief 
 * @param srcL
 * @param srcH
 * @return 
 */
inline unsigned int mergeBytes(unsigned int srcL, unsigned int srcH)
{
	return ((srcL & 0xFF) | (srcH << 8));
}

/**
 * @brief 
 * @param src
 * @param dest1
 * @param dest2
 */
inline void splitBytes(unsigned int src, unsigned char *dest1, unsigned char *dest2)
{
	*dest1 = src & 0xFF;
	*dest2 = src >> 8;
}

/**
 * @brief
 *
void handleEthernetInterrupt();

/**
 * @brief 
 * @param header
 *
void get_all_bytes(ECAT_Datagramm_header_bit header);

/**
 * @brief 
 * @param length
 *
void init_frame_header(unsigned int length);

/**
 * @brief 
 * @return 
 *
unsigned int has_tx(void);

/**
 * @brief 
 * @return 
 *
unsigned int has_rx(void);

/**
 * @brief 
 * @param q
 *
void init_queue(ECAT_queue *q);

/**
 * @brief 
 *
void init_ecat_queues();

/**
 * @brief 
 * @param q
 * @param datagramm
 *
void put_Datagramm(ECAT_queue *q, ECAT_Datagramm *datagramm);

/**
 * @brief 
 * @param q
 * @return 
 *
ECAT_Datagramm * get_Datagramm(ECAT_queue *q);

/**
 * @brief 
 * @param datagramm
 *
void destroy_Datagramm(ECAT_Datagramm *datagramm);


/**
 * @brief Инициализация EtherCAT
 *
void eCAT_init(void);

/** Передача фрейма Ethernet
@param buffer Фрейм
@param len Длина фрейма
*
void ethercat_transmit();

/**
 * @brief Передача фрейма Ethernet
 */
/*void ethercat_transmit_datagramm(unsigned char cmd, unsigned char idx, 
unsigned char addr[4], unsigned int len,
unsigned int *data);*

void enqueue_ecat_tx(unsigned int queue, ECAT_Datagramm *datagramm);

void enqueue_ecat_rx(unsigned int queue, ECAT_Datagramm *datagramm);

//void parseDatagrams(unsigned int *i, unsigned int length, unsigned int *word);

//void parseFrameHeader(unsigned int *i, unsigned int n, unsigned int *word);

/**
 * @brief 
 *
void handleEthernetInterrupt();

ECAT_Datagramm * get_RX_Datagramm(void);

*/
