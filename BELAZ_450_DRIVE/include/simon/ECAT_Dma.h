void init_ethernet(void);
unsigned int getEthData(unsigned int offset);
void ecat_transmitSmallFrame(unsigned int cmd[6]);
void allocFramePWM(void);
void allocFrameBG(void);

void transmitFrameByType(unsigned int);
void receiveFrameByType(unsigned int);

void transmitMBFrameBody();
void transmitBGFrameBody();
void receive_MB_Frame();
void receive_BG_Frame();
void onCompleteDMA();

Uint16 getEthFreeMem(void);
unsigned int isECATFrame(void);
void saveEthRegs(void);
unsigned int getFrameType(void);
void receiveSmallData();
void loadRxPNR();
void receiveModbusRequest();
void receiveModbusResult();
void receiveSmallData();
void saveRxPNR(void);
void loadEthRegs();
void ethReceive(void);
void configRxDma(volatile unsigned int *buffer, Uint16 transfer_size);
void startDMA(void);
void releaseReceivedFrame();
void removeFrameFromFIFO();
void incRxWd(void);

#define ETHERNET_MAX_FRAME_SIZE 1514
#define MIN_SHORT_FRAME 60
#define ECAT_MAX_DATA_SIZE 1486


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




#define FRAME_PWM 0
#define FRAME_BG 1
#define FRAME_UNKNOWN 2
#define FRAME_VOID 3

typedef struct EthRegs {
	Uint16 pnr;
	Uint16 ptr;
	Uint16 sel;
} EthRegs;

typedef struct EcatProcess
{
	Uint16 txPnr;
	Uint16 rxPnr;
	Uint16 state;
	Uint16 rxWd;
} EcatProcess;

typedef struct EcatDMA
{
	Uint16 isWorking;
	Uint16 type;

	Uint16 mb_tx_wkc;
	Uint16 modbus_tx_wkc;
	Uint16 small_data_wkc;
	Uint16 mb_rx_wkc;
	Uint16 modbus_rx_wkc;

} EcatDMA;

#define MODBUS_BUFFER_SIZE 128
