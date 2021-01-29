/*---------------------------------------------------------------------------*/
/**
  @file		mbtcp.h
  @brief	Example modbus TCP API header file

  This file contains higher level modbus serial utility functions.


 */
/*---------------------------------------------------------------------------*/

#ifndef MBTCP_H
#define MBTCP_H

//#include "socket.h"
#include "modbus_defs.h"
#include "modbus_utils.h"
#include "multidsknet.h"

#define	MAX_SERVER_SIZE			256

typedef struct _MBAP_Struct {
	u16	TransactionIdentifier;		///< copy from server to client
	u16	ProtocolIdentifier;		///< 0 for Modbus protocol
	u16	Length;				///< following bytes number
	u8	UnitIdentifier;			///< copy from server to client, maybe map serial address
} MBAPStruct, *pMBAPStruct;

/// Modbus over TCP/IP API
int	MBTCPServerInit( int port, int *serverfd);
int	MBTCPServerWaitConnection( const int serverfd, int *clientfd, char *client_addr);
int	MBTCPClientInit( int *clientfd);
int	MBTCPClientConnect( const int clientfd, const char *addr, int port);
int	MBTCPBlockRead(int fd, u8 *buf, int len);
int	MBTCPNonBlockRead(int fd, u8 *buf, int len);
int	MBTCPWrite(SOCKET* fd, u8 *pdu, int len, pMBAPStruct mbap);
int	MBTCPServerClose(int fd);
int	MBTCPClientClose(int fd);
int	MBTCPSetTimeout(int fd, u32 timeout);
int	MBTCPGetTimeout(int fd, u32 *timeout);
int	MBTCPGetMBAP(u8 *adu, pMBAPStruct mbap);
int	MBTCPMakeMBAP( pMBAPStruct mbap, u16 tid, u16 len, u8 uid);
int	MBTCPWriteMBAP( char *buf, pMBAPStruct mbap);
int	MBTCPGetPDU(u8 *buf, u8 *adu, int len);
int	MBTCPSendAndWaitResponse(int fd, u8 *buf, u8 *pdu, int len, pMBAPStruct mbap);

/// Modbus over TCP/IP master function
int	MBTCPReadDecreteInputs(int fd, u16 startdec, u16 no, u8 *value, pMBAPStruct mbap);
int	MBTCPReadCoils(int fd, u16 startcoils, u16 no, u8 *value, pMBAPStruct mbap);
int	MBTCPWriteSingleCoil(int fd, u16 coilreg, u16 onoff, pMBAPStruct mbap);
int	MBTCPWriteMultipleCoils(int fd, u16 startcoils, u16 no, u8 *value, pMBAPStruct mbap);

int	MBTCPReadInputRegisters(int fd, u16 startreg, u16 no, u16 *value, pMBAPStruct mbap);
int	MBTCPReadHoldingRegisters(int fd, u16 startreg, u16 no, u16 *value, pMBAPStruct mbap);
int	MBTCPWriteSingleRegister(int fd, u16 devicereg, u16 value, pMBAPStruct mbap);
int	MBTCPWriteMultipleRegisters(int fd, u16 startdevreg, u16 noreg, u8 count, u16 *value, pMBAPStruct mbap);
int     MBTCPReadWriteMultipleRegisters(int fd, u16 rsreg, u16 rno, u16 *rv, u16 wsreg, u16 wno, u8 count, u16 *wv, pMBAPStruct mbap);
int	MBTCPMaskwWriteRegister(int fd, u16 reg, u16 andmask,u16 ormask, pMBAPStruct mbap);
int	MBTCPReadFIFOQueue(int fd, u16 FIFOAddr, u16 *FIFOCount, u16 *FIFOValue, pMBAPStruct mbap);

/// Modbus over TCP/IP slave function
int	MBTCPSendReadDecreteInputs(SOCKET* fd, u16 no, u8 *value, pMBAPStruct mbap);
int	MBTCPSendReadCoils(SOCKET* fd, u16 no, u8 *value, pMBAPStruct mbap);
int	MBTCPSendReadInputRegisters(SOCKET* fd, u16 no, u16 *value, pMBAPStruct mbap);
int	MBTCPSendReadHoldingRegisters(SOCKET* fd, u16 no, u16 *value, pMBAPStruct mbap);
int     MBTCPSendWriteMultipleRegisters(SOCKET* fd, u16 startdevreg, u16 noreg, u8 count, u16 *value, pMBAPStruct mbap);
int	MBTCPSendWriteSingleCoil(SOCKET* fd, u16 coilreg, u16 onoff, pMBAPStruct mbap);
int	MBTCPSendWriteSingleRegister(SOCKET* fd, u16 reg, u16 value, pMBAPStruct mbap);
int     MBTCPSendReadFIFOQueue(SOCKET* fd, u16 no, u16 count, u16 *value, pMBAPStruct mbap);

#endif

