/***************************************************************************//**

 @file      common.h
 @verbatim
                      ___ \    ___| _)              __ __|
                      |    | \    \  |   _     __ \   |
                      |    |  ---    | (   |  |   |   |
                     _____/_)_____/ _| \__,|  |  _|  _|
                                       |___/
                     Digital Signalprocessing Technology
 @endverbatim
 @brief     Common modules: definitions and prototypes
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
#ifndef _COMMON_H
#define _COMMON_H
#include <stdlib.h>
#include <stdint.h>
#include "multidsknet.h"               /* network support                */


/******************************************************************************/
/*                                                                            */
/*   DEFINES                                                                  */
/*                                                                            */
/******************************************************************************/
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int             int16;
typedef long            int32;
typedef unsigned int    Uint16;
typedef unsigned long   Uint32;
typedef float           float32;
typedef long double     float64;
#endif
#ifndef TRUE
  #define TRUE   1
#endif
#ifndef FALSE
  #define FALSE  0
#endif


/***************************************************************************//**
 EXIT macro
 @details Use this macro to set the exit code for function PrintExitCode(). The
 parameter is the offset of a specific error message in table @ref exit_tab[]. @n
 EXIT() uses an unsigned int value as offset in @ref exit_tab[] rather than a
 direct message to test for illegal conditions in PrintExitCode() like
 BUFFEROVERFLOW_ERROR.

 Implemented exit codes are:
 @code
#define UNKNOWN_ERROR         0
#define INITUART_ERROR        1
#define MAC_ERROR             2
#define NETINIT_ERROR         3
#define ICMP_ERROR            4
#define SOCKETOPEN_ERROR      5
#define FTPSERVER_ERROR       6
#define HTTPSERVER_ERROR      7
#define BUFFEROVERFLOW_ERROR  8
#define NO_UART_HANDLE_ERROR  9
#define CPRINTF_DEVICE_ERROR  10
#define TIMER_RANGE_ERROR     11
#define ADD_FS_DEVICE_ERROR   12
 @endcode

 Feel free to add own exit codes and messages
 @see exit_code, exit_tab, PrintExitCode()
*******************************************************************************/
#define EXIT(ec)  (exit (exit_code = (ec)))

/*******************************************************************************
  descriptive error codes
   note: must match the error_tab order defined in common.c
*******************************************************************************/
#define UNKNOWN_ERROR         0  /**< unknown error or normal program exit    */
#define INITUART_ERROR        1  /**< InitializeUART() failed                 */
#define MAC_ERROR             2  /**< dsk_init() failed                       */
#define NETINIT_ERROR         3  /**< net_init() failed                       */
#define ICMP_ERROR            4  /**< ICMP socket error                       */
#define SOCKETOPEN_ERROR      5  /**< socket_open() failed                    */
#define FTPSERVER_ERROR       6  /**< ftp_server_init() failed                */
#define HTTPSERVER_ERROR      7  /**< http_server_init() failed               */
#define BUFFEROVERFLOW_ERROR  8  /**< CPrintf() buffer overflow error         */
#define NO_UART_HANDLE_ERROR  9  /**< No UART handle error                    */
#define CPRINTF_DEVICE_ERROR  10 /**< Device not available error              */
#define TIMER_RANGE_ERROR     11 /**< Timer out of range error                */
#define ADD_FS_DEVICE_ERROR   12 /**< Add device error                        */

/*******************************************************************************
 error return codes for dsk_init ( AUTO_NEG );
*******************************************************************************/
#define ERR_NO_SMCCHIP     0x8100
#define ERR_WRONG_VERSION  0x8200
#define ERR_INVALID_EPROM  0x8300
#define ERR_WRONG_MAC      0x8400

/*******************************************************************************
  suppress unused parameter warning
*******************************************************************************/
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)    ((P)=(P))  \
/**< suppresses warnings about params not used */
#endif

#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(P)    ((void)(P)) \
/**< suppresses warnings about params not used */
#endif


/*******************************************************************************
 macros for build date and time
*******************************************************************************/
#define BUILD_YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
                    + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0')) \
/**< build year macro. use to initialize timer variables or for descriptive outputs */


#define BUILD_DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 + (__DATE__ [5] - '0')) \
/**< build day macro. use to initialize timer variables or for descriptive outputs */


#define BUILD_MONTH   (  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6)   \
                       : __DATE__ [2] == 'b' ? 2                               \
                       : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4)   \
                       : __DATE__ [2] == 'y' ? 5                               \
                       : __DATE__ [2] == 'l' ? 7                               \
                       : __DATE__ [2] == 'g' ? 8                               \
                       : __DATE__ [2] == 'p' ? 9                               \
                       : __DATE__ [2] == 't' ? 10                              \
                       : __DATE__ [2] == 'v' ? 11 : 12 )                       \
/**< build month macro. use to initialize timer variables or for descriptive outputs */


#define BUILD_HOUR    ( (__TIME__ [0] - '0')*10 + (__TIME__ [1] - '0') ) /**< build hour macro. use to initialize timer variables or for descriptive outputs */
#define BUILD_MINUTE  ( (__TIME__ [3] - '0')*10 + (__TIME__ [4] - '0') ) /**< build minute macro. use to initialize timer variables or for descriptive outputs */
#define BUILD_SECOND  ( (__TIME__ [6] - '0')*10 + (__TIME__ [7] - '0') ) /**< build second macro. use to initialize timer variables or for descriptive outputs */


/******************************************************************************/
/*                                                                            */
/*   GLOBALS                                                                  */
/*                                                                            */
/******************************************************************************/
/*******************************************************************************
 exit code
*******************************************************************************/
extern int exit_code;

/***************************************************************************//**
 external access to link status
*******************************************************************************/
extern uint16_t _link1;
extern uint16_t _link2;


/*******************************************************************************
  this part exists for the flash run version only
*******************************************************************************/
#ifdef FLASH_RUN

/*******************************************************************************
 These symbols are defined by the linker (refer to xxx_flash.cmd)
*******************************************************************************/
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

//~ extern uint16_t Flash28_API_LoadStart;
//~ extern uint16_t Flash28_API_LoadEnd;
//~ extern uint16_t Flash28_API_RunStart;
extern Uint16 Flash28_API_LoadStart;
extern Uint16 Flash28_API_LoadEnd;
extern Uint16 Flash28_API_RunStart;


extern uint16_t NetTcpRamfuncsLoadStart;
extern uint16_t NetTcpRamfuncsLoadEnd;
extern uint16_t NetTcpRamfuncsRunStart;

extern uint16_t NetSmcRamfuncsLoadStart;
extern uint16_t NetSmcRamfuncsLoadEnd;
extern uint16_t NetSmcRamfuncsRunStart;

extern uint16_t NetSocketRamfuncsLoadStart;
extern uint16_t NetSocketRamfuncsLoadEnd;
extern uint16_t NetSocketRamfuncsRunStart;

extern uint16_t NetIpRamfuncsLoadStart;
extern uint16_t NetIpRamfuncsLoadEnd;
extern uint16_t NetIpRamfuncsRunStart;

extern uint16_t NetMembRamfuncsLoadStart;
extern uint16_t NetMembRamfuncsLoadEnd;
extern uint16_t NetMembRamfuncsRunStart;
#endif


/***************************************************************************//**
*                                                                              *
*    PROTOTYPES                                                                *
*                                                                              *
*******************************************************************************/
#ifdef __cplusplus
  extern "C" {
#endif

/***************************************************************************//**

  @brief  print error message if dsk_init_dev() failed
  @param  error_code - dsk_init_dev() return code
  @return never in case of errors

*******************************************************************************/
void smc_error ( uint16_t error_code );

/***************************************************************************//**

 @brief    Show a descriptive error message on exit
 @param    -
 @return   nothing
 @details  Print descriptive exit message. This function uses string table
           @ref exit_tab[] for printing a certain message. Add your own error
           messages to @ref exit_tab[] and use macro EXIT(x).
 @see exit_code, exit_tab, EXIT()

*******************************************************************************/
void PrintExitCode ( void );

/***************************************************************************//**

 @brief    Initialize application
 @param    dsp_clock [Hz]
 @return   nothing
 @details  Application Initialization Code @n
           Put all your initialization code into this central function. To make
           the CPrintf() function work as well in your initialization code
           called from here CPrintf_select_output() should be moved here too.

*******************************************************************************/
void AppInit (uint32_t dsp_clock);

/***************************************************************************//**

 @brief    Disable interrupts, DMA, timer etc.
 @param    -
 @return   nothing
 @details  Application Cleanup Code at exit @n
           This function is called on exit to cleanup running processes like
           interrupts and DMA, flush opened files, close handles

*******************************************************************************/
void AppCleanup (void);

#if (defined(_DSKNET_H_) || defined(HAVE_LINK_STATUS))
/***************************************************************************//**

  @brief        print error code

  @param        error_code - error code to print
  @param        pLog - printf function
  @return       nothing

*******************************************************************************/
void net_print_error ( int32_t error_code, tpMessageLogFxn pLog );
#endif

/*******************************************************************************

    Function   LED_init

    Turn all LEDs off

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_init();

/*******************************************************************************

    Function  LED_off

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_off(unsigned int ledNum);

/*******************************************************************************

    Function  LED_on

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_on(unsigned int ledNum);

/*******************************************************************************

    Function  LED_toggle

    Parameter
    Returns
    Calls

*******************************************************************************/
void LED_toggle(unsigned int ledNum);

/*******************************************************************************

    Function  LED_state

    Parameter
    Returns
    Calls

*******************************************************************************/
uint16_t LED_state(void);

#ifdef __cplusplus
}
#endif

#endif // _COMMON_H
