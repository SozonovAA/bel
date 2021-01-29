/***************************************************************************//**

 @file      cprintf.h
 @verbatim
                      ___ \    ___| _)              __ __|
                      |    | \    \  |   _     __ \   |
                      |    |  ---    | (   |  |   |   |
                     _____/_)_____/ _| \__,|  |  _|  _|
                                       |___/
                     Digital Signalprocessing Technology
 @endverbatim
 @brief     Custom Printf: definitions and prototypes

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
#ifndef _CPRINTF_H
#define _CPRINTF_H


/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/
/***************************************************************************//**
  CPrintf buffer size
*******************************************************************************/
#define CPRINTF_BUFFER_SIZE     512

/***************************************************************************//**
  enable available CPrintf Outputs
*******************************************************************************/
#define CPRINTF_CCS_AVAILABLE        1
#define CPRINTF_UART_AVAILABLE       1
//~ #define CPRINTF_USB_AVAILABLE        1
//~ #define CPRINTF_NET_AVAILABLE        1

#define CPRINTF_NO_OUTPUT          0x0

#ifdef CPRINTF_CCS_AVAILABLE
#define CPRINTF_CCS_OUTPUT         0x1
#define CPRINTF_CCS_BIT            0x1
#else
#define CPRINTF_CCS_BIT            0x0
#endif
#ifdef CPRINTF_UART_AVAILABLE
#define CPRINTF_UART_OUTPUT        0x2
#define CPRINTF_UART_BIT           0x2
#else
#define CPRINTF_UART_BIT           0x0
#endif
#ifdef CPRINTF_USB_AVAILABLE
#define CPRINTF_USB_OUTPUT         0x4
#define CPRINTF_USB_BIT            0x4
#else
#define CPRINTF_USB_BIT            0x0
#endif
#ifdef CPRINTF_NET_AVAILABLE
#define CPRINTF_NET_OUTPUT         0x8
#define CPRINTF_NET_BIT            0x8
#else
#define CPRINTF_NET_BIT            0x0
#endif

/*******************************************************************************
  define available output device mask
*******************************************************************************/
#define CPRINTF_OUTPUT_MASK                            \
                                   ( CPRINTF_CCS_BIT   \
                                   | CPRINTF_UART_BIT  \
                                   | CPRINTF_USB_BIT  \
                                   | CPRINTF_NET_BIT  )


/*******************************************************************************
  clear screen macro
*******************************************************************************/
#ifndef CLRSCR
#define CLRSCR "\x1B[2J\x1B[0;0H"
#endif


/*******************************************************************************
  carriage return, line feed
*******************************************************************************/
#ifndef CRLF
#define CRLF "\r\n"
#endif


/*******************************************************************************
*                                                                              *
*    GLOBALS                                                                   *
*                                                                              *
*******************************************************************************/

/* - */

/*******************************************************************************
*                                                                              *
*    PROTOTYPES                                                                *
*                                                                              *
*******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

/***************************************************************************//**

  @brief    Select the CPrintf output device
  @param    device - output device
  @return   nothing
  @see      CPRINTF_NO_OUTPUT, CPRINTF_CCS_OUTPUT, CPRINTF_UART_OUTPUT

*******************************************************************************/
void CPrintf_select_output (int device);

/***************************************************************************//**

    @brief      Custom printf function
    @param      format - format string
    @return     nothing

*******************************************************************************/
void CPrintf(const char *format, ...);


#ifdef __cplusplus
}
#endif

#endif // _CPRINTF_H
