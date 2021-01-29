/*******************************************************************************

 @file      uartio.h
 @verbatim
                       ___ \    ___| _)              __ __|
                       |    | \    \  |   _     __ \   |
                       |    |  ---    | (   |  |   |   |
                      _____/_)_____/ _| \__,|  |  _|  _|
                                        |___/
                      Digital Signalprocessing Technology
 @endverbatim
 @brief     thread safe uart access

 @author    D.SignT GmbH & Co. KG, Claus Hermbusche
 @date      2012-08-24

 @cond
  Software License Agreement
  Copyright (C) 2001-2012 D.SignT GmbH & Co. KG - http://www.dsignt.de

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the
    distribution.

    Neither the name of D.SignT GmbH & Co. KG nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

  Disclaimer
  THIS SOFTWARE IS PROVIDED BY D.SIGNT GMBH & CO. KG "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL D.SIGNT GMBH & CO. KG BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  @endcond
*******************************************************************************/
#ifndef _UARTIO_H
#define _UARTIO_H



/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
  UART regs
*******************************************************************************/
typedef struct SCI_REGS* UART_Handle;

/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/
extern UART_Handle h_Uart;
/*******************************************************************************
 Lock handle. used to lock the UART access
*******************************************************************************/
#ifdef USE_DSPBIOS
extern LCK_Handle  h_LckUart;
#endif



/*******************************************************************************

    PROTOTYPES

*******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

/***************************************************************************//**

    @brief      Initialize UART
    @param      baud - baud rate (9600, 19200, 38400, 57600, 115200)
    @return     TRUE  - initialization error
                FALSE - initialization successfull

*******************************************************************************/
int InitializeUART(unsigned long baud);

/***************************************************************************//**

  @brief     open the UART
  @param     device - SCI device (0 == SCIA; 1 == SCIB; 2 == SCIC)
  @param     baud   - baud rate
  @return    UART_Handle or NULL

*******************************************************************************/
UART_Handle DSK_UART_open(unsigned int device, unsigned long baud);

/***************************************************************************//**

  @brief        check line status register and send one char to UART
  @param        hUart  - UART handle
  @param        char   - character to output
  @return       nothing

*******************************************************************************/
void DSK_UART_put_char (UART_Handle hUart, char data);

/***************************************************************************//**

  @brief     Write a zero terminated string over UART

  @param     hUart  - UART handle
  @param     buffer - pointer to string to print
  @return    nothing

*******************************************************************************/
void DSK_UART_WriteStr (UART_Handle hUart, char *buffer);

/***************************************************************************//**

  @brief    Check if receive FIFO is empty
  @param    hUart  - UART handle
  @return    1 - FIFO not empty
             0 - FIFO empty

*******************************************************************************/
int DSK_UART_rcvReady (UART_Handle hUart);

/***************************************************************************//**

  @brief    get one char from UART FIFO
  @param    hUart  - UART handle
  @param    *data  - data buffer
  @return   one char

*******************************************************************************/
int DSK_UART_getChar (UART_Handle hUart, char* data);

/***************************************************************************//**

    @brief      receive and retransmit a string via the UART

    @param      hUart   - Uart handle
    @param      *str    - Pointer to string buffer
    @param      maxsize - buffer size
    @param      timeout - 0:none
    @param      echo    - 0: echo off    1: echo on
    @return     Pointer to string buffer

    @note receive_char maintains a timeout counter and returns NULL if timeout
    expires. Timeout is defined by the number of DSK_UART_get_char() calls
    which return -1 (no char available) and parameter timeout

*******************************************************************************/
char *UARTReadStr (UART_Handle hUart, char *str, unsigned maxsize, unsigned timeout, unsigned echo);


#ifdef __cplusplus
}
#endif

#endif
