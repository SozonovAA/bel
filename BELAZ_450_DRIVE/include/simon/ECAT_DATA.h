//#include "hfa.h"

struct TIME_AND_DATE
{
	unsigned char year,month,date,day_of_week,hours,minutes,seconds,flag;
};

struct KKsDIN{

	unsigned int bBACK :1; 			//SA2 (�����)
	unsigned int bFORWARD :1; 		//SA2 (������)
	unsigned int bSTAB :1; 			//SA3 (���� ����)
	unsigned int bHANDLE_BRAKE :1; 	//���������� ������
	unsigned int bDRIVE :1; 		//Drive (������ ����)
	unsigned int bRSRVD :11; 		//(������)

};

union KKuDIN{

	unsigned int all;
	struct KKsDIN bit;
};



extern struct TIME_AND_DATE time_and_date;
extern struct data_for_transmit *data_transmit;
extern struct data_for_receive *data_receive;
//-----------------------------------------------------------------------------------------------//
// ������ �� �������� �� �� � �������
//-----------------------------------------------------------------------------------------------//



struct data_for_transmit{
	struct TIME_AND_DATE time_and_date;
	union KKuDIN DIN;
	int Drive;
	int Brake;
	int SpeedFL;
	int SpeedFR;
	int SpeedRL;
	int SpeedRR;
};



//-----------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//
// ������ �� ������� � ��

struct _PK12{
	int MessFlag;
	int TxData[10];
};

typedef struct _PK12 sPK12;

struct _PK3{
	int MessFlag;
	int TxData[10];
};

struct _TK{
	int MessFlag;
	int TxData[10];
};

struct data_for_receive{
	long ready_modbus;					// �� �������!!!
	unsigned int data_for_oscil[10];	// �� �������!!!
	struct _PK12 PK_1;
	struct _PK12 PK_2;
	struct _PK3 PK_3;
	struct _TK TK;
};

struct ECAT__memory
{
	struct data_for_transmit* permanent_RX_data;
	struct data_for_receive* permanent_TX_data;
};


