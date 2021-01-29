/********************************************************************************************/
/********************************************************************************************/
/*PHY REGISTERS*/
/********************************************************************************************/
/********************************************************************************************/
#define PHY_CONTROL 									0
#define PHY_STATUS  									1
#define PHY_IDENTIFIER1 								2
#define PHY_IDENTIFIER2 								3
#define PHY_AUTO-NEGOTIATION_ADVERTISEMENT 				4
#define PHY_AUTO-NEGOTIATION_REMOTE_END_CAPABILITY 		5
#define PHY_CONFIGURATION1 								16
#define PHY_CONFIGURATION2 								17
#define PHY_STATUS_OUTPUT  								18
#define PHY_MASK 										19
#define PHY_RESERVED									20




/********************************************************************************************/
/********************************************************************************************/
/*BANK0*/
/********************************************************************************************/
/********************************************************************************************/
struct TCRREG
{
volatile unsigned int TXENA:1;
volatile unsigned int LOOP:1;
volatile unsigned int FORCOL:1;
volatile unsigned int RESERVED1:4;
volatile unsigned int PAD_EN:1;
volatile unsigned int NOCRC:1;
volatile unsigned int RESERVED2:1;
volatile unsigned int MON_CSN:1;
volatile unsigned int FDUPLX:1;
volatile unsigned int STP_SQET:1;
volatile unsigned int EPH_LOOP:1;
volatile unsigned int RESERVED3:1;
volatile unsigned int SWDUP :1;
};

union TCR_REG1
{
volatile unsigned int  all;
volatile struct TCRREG bit;
};

/********************************************************************************************/

struct EPHSRREG
{
volatile unsigned int TX_SUC:1;
volatile unsigned int SNGL_COL:1;
volatile unsigned int MUL_COL:1;
volatile unsigned int LTX_MULT:1;
volatile unsigned int _16COL:1;
volatile unsigned int SQET:1;
volatile unsigned int LTX_BRD:1;
volatile unsigned int TX_DEFR:1;
volatile unsigned int RESERVED:1;
volatile unsigned int LATCOL:1;
volatile unsigned int LOST_CARR:1;
volatile unsigned int EXC_DEF:1;
volatile unsigned int CTR_ROL :1;
volatile unsigned int RESERVED2:1;
volatile unsigned int LINK_OK:1;
volatile unsigned int RESERVED3 :1;
};

union EPHSR_REG
{
volatile unsigned int  all;
volatile struct EPHSRREG bit;
};


/********************************************************************************************/
struct RCRREG
{
volatile unsigned int RX_ABORT:1;
volatile unsigned int PRMS:1;
volatile unsigned int ALMUL:1;
volatile unsigned int RESERVED:5;
volatile unsigned int RXEN:1;
volatile unsigned int STRIP_CRC:1;
volatile unsigned int RESERVED2:3;
volatile unsigned int ABORT_ENB:1;
volatile unsigned int FILT_CAR:1;
volatile unsigned int SOFT_RST:1;
};

union RCR_REG
{
volatile unsigned int  all;
volatile struct RCRREG bit;
};

/********************************************************************************************/
struct ECRREG
{
volatile unsigned int SINGLE_COL_COUNT:4;
volatile unsigned int MULTIPLE_COL_COUNT:4;
volatile unsigned int NUMBER_OF_DEF_TX:4;
volatile unsigned int NUMBER_OF_EXTDEF_TX:4;
};

union ECR_REG
{
volatile unsigned int  all;
volatile struct ECRREG bit;
};

/********************************************************************************************/
struct MIRREG
{
volatile unsigned int MEMORY_SIZE:8;
volatile unsigned int FREE_MEMORY_AVAILABLE:8;
};

union MIR_REG
{
volatile unsigned int  all;
volatile struct MIRREG bit;
};

/********************************************************************************************/
struct RPCRREG
{
volatile unsigned int RESERVED:2;
volatile unsigned int LS0B:1;
volatile unsigned int LS1B:1;
volatile unsigned int LS2B:1;
volatile unsigned int LS0A:1;
volatile unsigned int LS1A:1;
volatile unsigned int LS2A:1;
volatile unsigned int RESERVED2:3;
volatile unsigned int ANEG:1;
volatile unsigned int DPLX:1;
volatile unsigned int SPEED:1;
volatile unsigned int RESERVED3:2;
};

union RPCR_REG
{
volatile unsigned int  all;
volatile struct RPCRREG bit;
};

/********************************************************************************************/
struct RESREG
{
volatile unsigned int RESERVED:16;
};

union RES_REG
{
volatile unsigned int  all;
volatile struct RESREG bit;
};

/********************************************************************************************/

struct BANKSELECT
{
volatile unsigned int BS0:1;
volatile unsigned int BS1:1;
volatile unsigned int BS2:1;
volatile unsigned int RESERVED:13;
};

union BANK_SELECT_REG
{
volatile unsigned int  all;
volatile struct BANKSELECT bit;
};


/********************************************************************************************/

struct BANK_0
{
volatile union TCR_REG1                           TCR;
volatile union EPHSR_REG                       EPHSR;
volatile union RCR_REG                           RCR;
volatile union ECR_REG                           ECR;
volatile union MIR_REG                            MIR;
volatile union RPCR_REG                         RPCR;
volatile union RES_REG                             RES;
volatile union BANK_SELECT_REG          BANK_SELECT;
};

/********************************************************************************************/
/********************************************************************************************/
/*BANK1*/
/********************************************************************************************/
/********************************************************************************************/

struct CRREG
{
volatile unsigned int RESERVED:9;
volatile unsigned int EXT_PHY:1;
volatile unsigned int GPCNTRL:1;
volatile unsigned int RESERVED2:1;
volatile unsigned int NO_WAIT:1;
volatile unsigned int RESERVED3:2;
volatile unsigned int EPH_POWER_EN:1;
};

union CR_REG
{
volatile unsigned int all;
volatile struct CRREG bit;
};

/********************************************************************************************/


struct BARREG
{
volatile unsigned int RESERVED:8;
volatile unsigned int A5:1;
volatile unsigned int A6:1;
volatile unsigned int A7:1;
volatile unsigned int A8:1;
volatile unsigned int A9:1;
volatile unsigned int A13:1;
volatile unsigned int A14:1;
volatile unsigned int A15:1;
};

union BAR_REG
{
volatile unsigned int all;
volatile struct BARREG bit;
};

/********************************************************************************************/


struct IAR0REG
{
volatile unsigned int ADDRESS0:8;
volatile unsigned int ADDRESS1:8;
};

union IAR0_REG
{
volatile unsigned int all;
volatile struct IAR0REG bit;
};

/********************************************************************************************/


struct IAR1REG
{
volatile unsigned int ADDRESS2:8;
volatile unsigned int ADDRESS3:8;
};

union IAR1_REG
{
volatile unsigned int all;
volatile struct IAR1REG bit;
};

/********************************************************************************************/


struct IAR2REG
{
volatile unsigned int ADDRESS4:8;
volatile unsigned int ADDRESS5:8;
};

union IAR2_REG
{
volatile unsigned int all;
volatile struct IAR2REG bit;
};

/********************************************************************************************/


struct GPRREG
{
volatile unsigned int LOW_DATA_BYTE:8;
volatile unsigned int HIGH_DATA_BYTE:8;
};

union GPR_REG
{
volatile unsigned int all;
volatile struct GPRREG bit;
};

/********************************************************************************************/


struct CTRREG
{
volatile unsigned int STORE:1;
volatile unsigned int RELOAD:1;
volatile unsigned int EEPROM_SELECT:1;
volatile unsigned int RESERVED:2;
volatile unsigned int TE_ENABLE:1;
volatile unsigned int CR_ENABLE:1;
volatile unsigned int LE_ENABLE:1;
volatile unsigned int RESERVED2:3;
volatile unsigned int AUTO_RELEASE:1;
volatile unsigned int RESERVED3:2;
volatile unsigned int RCV_BAD:1;
volatile unsigned int RESERVED4:1;
};

union CTR_REG
{
volatile unsigned int all;
volatile struct CTRREG bit;
};



/********************************************************************************************/

struct BANK_1
{
volatile union CR_REG                               CR;                
volatile union BAR_REG                             BAR;
volatile union IAR0_REG                            IAR0;
volatile union IAR1_REG                            IAR1;
volatile union IAR2_REG                            IAR2;
volatile union GPR_REG                             GPR;
volatile union CTR_REG                             CTR;
volatile union BANK_SELECT_REG            BANK_SELECT;
};


/********************************************************************************************/
/********************************************************************************************/
/*BANK2*/
/********************************************************************************************/
/********************************************************************************************/

struct MMUCRREG
{
volatile unsigned int BUSY:1;
volatile unsigned int RESERVED:4;
volatile unsigned int COMMAND:3;
volatile unsigned int RESERVED2:8;
};

union MMUCR_REG
{
volatile unsigned int  all;
volatile struct MMUCRREG bit;
};

/********************************************************************************************/

struct PNRREG
{
volatile unsigned int PACKET_NUMBER_TX:6;
volatile unsigned int RESERVED:2;
volatile unsigned int ALLOCATED_PAC_NUMBER:6;
volatile unsigned int RESERVED2:1;
volatile unsigned int FAILED:1;
};

union PNR_REG
{
volatile unsigned int  all;
volatile struct PNRREG bit;
};


/********************************************************************************************/

struct FIFOREG
{
volatile unsigned int TX_FIFO_PACKET_NUMBER:6;
volatile unsigned int RESERVED:1;
volatile unsigned int TEMPTY:1;
volatile unsigned int RX_FIFO_PACKET_NUMBER:6;
volatile unsigned int RESERVED2:1;
volatile unsigned int REMPTY:1;
};

union FIFO_REG
{
volatile unsigned int  all;
volatile struct FIFOREG bit;
};

/********************************************************************************************/

struct PTRREG
{
volatile unsigned int POINTER:11;
volatile unsigned int NOT_EMPTY:1;
volatile unsigned int RESERVED:1;
volatile unsigned int READ:1;
volatile unsigned int AUTO_INCR:1;
volatile unsigned int RCV:1;
};

union PTR_REG
{
volatile unsigned int  all;
volatile struct PTRREG bit;
};

/********************************************************************************************/

struct DATA1REG
{
volatile unsigned int DATA:16;
};

union DATA1_REG
{
volatile unsigned int  all;
volatile struct DATA1REG bit;
};

/********************************************************************************************/

struct DATA2REG
{
volatile unsigned int DATA:16;
};

union DATA2_REG
{
volatile unsigned int  all;
volatile struct DATA2REG bit;
};

/********************************************************************************************/

struct ISTREG
{
volatile unsigned int RCV_INT:1;
volatile unsigned int TX_INT:1;
volatile unsigned int TX_EMPTY_INT:1;
volatile unsigned int ALLOC_INT:1;
volatile unsigned int RX_OVRN_INT:1;
volatile unsigned int EPH_INT:1;
volatile unsigned int RESERVED:1;
volatile unsigned int MD_INT:1;
volatile unsigned int RCV_INT_MASK:1;
volatile unsigned int TX_INT_MASK:1;
volatile unsigned int TX_EMPTY_INT_MASK:1;
volatile unsigned int ALLOC_INT_MASK:1;
volatile unsigned int RX_OVRN_INT_MASK:1;
volatile unsigned int EPH_INT_MASK:1;
volatile unsigned int RESERVED2:1;
volatile unsigned int MD_INT_MASK:1;
};

union IST_REG
{
volatile unsigned int  all;
volatile struct ISTREG bit;
};

/********************************************************************************************/

struct BANK_2
{
volatile union MMUCR_REG                           MMUCR;
volatile union PNR_REG                                PNR;
volatile union FIFO_REG                               FIFO;
volatile union PTR_REG                                PTR;
volatile union DATA1_REG                            DATA1;
volatile union DATA2_REG                            DATA2;
volatile union  IST_REG                                IST;
volatile union BANK_SELECT_REG               BANK_SELECT;
};

/********************************************************************************************/
/********************************************************************************************/
/*BANK3*/
/********************************************************************************************/
/********************************************************************************************/

struct MT01REG
{
volatile unsigned int MT0:8;
volatile unsigned int MT1:8;
};

union MT01_REG
{
volatile unsigned int  all;
volatile struct MT01REG bit;
};

/********************************************************************************************/

struct MT23REG
{
volatile unsigned int MT2:8;
volatile unsigned int MT3:8;
};

union MT23_REG
{
volatile unsigned int  all;
volatile struct MT23REG bit;
};

/********************************************************************************************/

struct MT45REG
{
volatile unsigned int MT4:8;
volatile unsigned int MT5:8;
};

union MT45_REG
{
volatile unsigned int  all;
volatile struct MT45REG bit;
};

/********************************************************************************************/

struct MT67REG
{
volatile unsigned int MT6:8;
volatile unsigned int MT7:8;
};

union MT67_REG
{
volatile unsigned int  all;
volatile struct MT67REG bit;
};


/********************************************************************************************/


struct MGMTREG
{
volatile unsigned int MDO:1;
volatile unsigned int MDI:1;
volatile unsigned int MCLK:1;
volatile unsigned int MDOE:1;
volatile unsigned int RESERVED1:10;
volatile unsigned int MSK_CRS100:1;
volatile unsigned int RESERVED2:1;
};

union MGMT_REG
{
volatile unsigned int  all;
volatile struct MGMTREG bit;
};


/********************************************************************************************/


struct REVREG
{
volatile unsigned int REV1:4;
volatile unsigned int CHIP1:4;
volatile unsigned int REV2:4;
volatile unsigned int CHIP2:4;

};

union REV_REG
{
volatile unsigned int  all;
volatile struct REVREG bit;
};


/********************************************************************************************/


struct RCVREG
{
volatile unsigned int MBO1:1;
volatile unsigned int MBO2:1;
volatile unsigned int MBO3:1;
volatile unsigned int MBO4:1;
volatile unsigned int MBO5:1;
volatile unsigned int RESERVED1:2;
volatile unsigned int RCV_DISCRD:1;
volatile unsigned int RESERVED2:8;

};

union RCV_REG
{
volatile unsigned int  all;
volatile struct RCVREG bit;
};

/********************************************************************************************/


struct BANK_3
{
volatile union MT01_REG                           MT01;
volatile union MT23_REG                           MT23;
volatile union MT45_REG                           MT45;
volatile union MT67_REG                           MT67;
volatile union MGMT_REG                           MGMT;
volatile union REV_REG                             REV;
volatile union RCV_REG                             RCV;
volatile union BANK_SELECT_REG            BANK_SELECT;
};





typedef union 
{
volatile struct BANK_0 BANK0;
volatile struct BANK_1 BANK1;
volatile struct BANK_2 BANK2;
volatile struct BANK_3 BANK3;

}BANK_all;








