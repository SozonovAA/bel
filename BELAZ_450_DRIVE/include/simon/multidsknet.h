/***************************************************************************//**
 @file multidsknet.h
 @verbatim
                         ___ \    ___| _)              __ __|
                         |    | \    \  |   _     __ \   |
                         |    |  ---    | (   |  |   |   |
                        _____/_)_____/ _| \__,|  |  _|  _|
                                          |___/
                        Digital Signalprocessing Technology
 @endverbatim
 @brief     TCP/IP protocol library

 @author    D.SignT GmbH & Co. KG
 @author    \htmlonly &copy 2001-2012 \endhtmlonly
 @author    Claus Hermbusche
 @version   2.74
 @date      2012-09-06
 @target    dual SMSC91c111 boards
 @compiler  CCS 3.3
 @history  @include history.txt

 @cond Software License Agreement
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
#ifndef _DSKNET_H_
#define _DSKNET_H_
#include <stdlib.h>
#if defined(_TMS320C6X)
#include <stdint.h>
#endif
/*******************************************************************************
*                                                                              *
*    DEFINES                                                                   *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
  basics
*******************************************************************************/

/*******************************************************************************
 type definition for data types
*******************************************************************************/
#if (defined(__TMS320C55X__) || defined(_TMS320C2000) )
#ifndef NULL
#define NULL ((void *) 0L)
#endif

#ifndef null
#define null ((void *) 0L)
#endif

#ifndef TRUE
#define TRUE    1L
#endif

#ifndef FALSE
#define FALSE   0L
#endif

#ifndef true
#define true    1L
#endif

#ifndef false
#define false   0L
#endif

/***************************************************************************//**
 @cond       PRIVATE
  For compatibility reason
*******************************************************************************/
typedef unsigned char       u_int8_t;
typedef unsigned short      u_int16_t;
typedef unsigned long       u_int32_t;

typedef unsigned char       uint8_t;   /* missing in stdint.h */
typedef char                 int8_t;   /* missing in stdint.h */
#ifndef _STDINT_H_
#define _STDINT_H_
typedef          short  int16_t;
typedef unsigned short uint16_t;
typedef          long    int32_t;
typedef unsigned long   uint32_t;
#endif
/***************************************************************************//**
 @endcond
*******************************************************************************/

/*******************************************************************************
 @cond       PRIVATE
  a placeholder
*******************************************************************************/
#define SO_SPARE            50
/***************************************************************************//**
 @endcond
*******************************************************************************/

#else
#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef null
#define null ((void *) 0)
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef true
#define true    1
#endif

#ifndef false
#define false   0
#endif

/*******************************************************************************
 @cond       PRIVATE
  For compatibility reason
*******************************************************************************/
typedef unsigned char       u_int8_t;
typedef unsigned short      u_int16_t;
typedef unsigned int        u_int32_t;
#ifndef _STDINT_H_
#define _STDINT_H_
typedef   signed char   int8_t;
typedef unsigned char  uint8_t;
typedef          short  int16_t;
typedef unsigned short uint16_t;
typedef          int    int32_t;
typedef unsigned int   uint32_t;
#endif
/***************************************************************************//**
 @endcond
*******************************************************************************/

/*******************************************************************************
 @cond       PRIVATE
  a placeholder
*******************************************************************************/
#define SO_SPARE            49
/***************************************************************************//**
 @endcond
*******************************************************************************/
#endif


/***************************************************************************//**
  @addtogroup INIT  Initialization
  @{
*******************************************************************************/

/***************************************************************************//**
  @name    Adapter type
  Adapter type parameter for add_adapter()
*******************************************************************************/
/*@{*/
#define ETH8900       1                       /* CS8900                       */
#define ETH91C111     2                       /* SMSC91C111                   */
#define ETH642        3                       /* DM642                        */
#define ETHAX88783    4                       /* AX88783                      */
#define ETHDM9010B    5                       /* DM9010B                      */
#define ETHKSZ8851    6                       /* KSZ8851                      */
/*@}*/
/***************************************************************************//**
  @name Operation Mode
  Operation mode parameter for dsk_init_dev()
*******************************************************************************/
/*@{*/
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select full duplex
*******************************************************************************/
#undef FULL_DUPLEX
#define FULL_DUPLEX     0x01                              /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select half duplex
*******************************************************************************/
#undef HALF_DUPLEX
#define HALF_DUPLEX     0x00                              /**<  */

/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 10 MBit
*******************************************************************************/
#define SPEED_10        0x00                              /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 100 MBit
*******************************************************************************/
#define SPEED_100       0x04                              /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select Autonegotiation
*******************************************************************************/
#define AUTO_NEG        0x08                              /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 1000 MBit
*******************************************************************************/
#define SPEED_1000      0x20                              /**<  */

/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 100 MBit full duplex
*******************************************************************************/
#define FDX_100       (FULL_DUPLEX | SPEED_100 )        /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 10 MBit full duplex
*******************************************************************************/
#define FDX_10        (FULL_DUPLEX | SPEED_10  )        /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 100 MBit half duplex
*******************************************************************************/
#define HDX_100       (HALF_DUPLEX | SPEED_100 )        /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 10 MBit half duplex
*******************************************************************************/
#define HDX_10        (HALF_DUPLEX | SPEED_10  )        /**<  */
/***************************************************************************//**
  Operation mode parameter for dsk_init_dev() to select 1000 MBit full duplex
*******************************************************************************/
#define FDX_1000      (FULL_DUPLEX | SPEED_1000)        /**<  */

/***************************************************************************//**
   DSK91C111 operation mode, parameter for dsk_init_dev() and Intel PHY with
   fiber optic
*******************************************************************************/
#define FIBER_MODE     0x10                             /**<  */
/*@} */

/***************************************************************************//**
  @name Return Error Code for dsk_init_dev()
*******************************************************************************/
/*@{*/
/*******************************************************************************
 error return codes for dsk_init_dev()
*******************************************************************************/
#define ERR_NO_SMCCHIP     0x8100    /**<  No SMC Chip found                  */
#define ERR_WRONG_VERSION  0x8200    /**<  Wrong SMC Chip version             */
#define ERR_INVALID_EPROM  0x8300    /**<  Invalid EEPROM content found       */
#define ERR_WRONG_MAC      0x8400    /**<  Wrong MAC Address                  */
/*@}*/


/***************************************************************************//**
  @name Service Mode
  Service mode parameter for net_init()
  @{
*******************************************************************************/
/******************************************************************************
 net_init() parameter: enable DHCP
*******************************************************************************/
#define DHCP_ENABLE    dhcp_enable                      /**< @hideinitializer */
/*******************************************************************************
 net_init() parameter: enable DNS
*******************************************************************************/
#define DNS_ENABLE     dns_enable_server                /**< @hideinitializer */
/*@}*/

/*@}*/


/***************************************************************************//**
  @addtogroup SOCKETS  Sockets
  @{
*******************************************************************************/

/***************************************************************************//**
 @brief Incoming protocol information

 in_struct contains user accessable information about incoming messages
 @see use with socket_struct
*******************************************************************************/
struct in_struct
{
    /***********************************************************************//**
     The data_len field holds the valid data length of the last received packet
    ***************************************************************************/
    uint16_t  data_len;
};

/***************************************************************************//**
  @brief Unique description of a bidirectional network communication channel
*******************************************************************************/
struct socket_struct
{
    /***********************************************************************//**
     @ref SOCKET_ERROR_CODE "Socket Error Code"
     @include eclink.inc
     @see net_send(), net_recv()
    ***************************************************************************/
    uint32_t  error_code;             /* Event error code                     */

    /***********************************************************************//**
     socket destination address information @n
     it can be used to determine destinations address after successful net_recv()
    ***************************************************************************/
    uint32_t  dest_addr;              /* Remote address                       */

    /***********************************************************************//**
     socket destination port information @n
     it can be used to determine destinations port after successful net_recv()
    ***************************************************************************/
    uint16_t  dest_port;              /* Remote port                          */

    /***********************************************************************//**
     IP type of service @n
     use immediately before net_send() or after net_recv()
      - bit 15..8 : receive TOS
      - bit  7..0 : send TOS
    ***************************************************************************/
    uint16_t  ip_tos;                 /* IP type of service                   */

    /***************************************************************************
     socket source information
    ***************************************************************************/
    uint32_t  src_addr;               /**< Local address                      */
    uint16_t  src_port;               /**< Local port                         */

    /***********************************************************************//**
     32 bit alignment. Free for custom use as a 16 bit scratch register
    ***************************************************************************/
    uint16_t  res_align2;             /* 32 bit alignment                     */

    /***********************************************************************//**
     Free for custom use as a general purpose pointer
    ***************************************************************************/
    void      *user_pointer;          /* User pointer                         */

    /***********************************************************************//**
     128 bit alignment. Free for custom use as two 32 bit scratch registers
    ***************************************************************************/
    uint32_t  res_align3[2];          /* 128 bit alignment                    */

    struct in_struct   in;            /**< Data length of incoming packets    */

    uint32_t  res[SO_SPARE];          /**< Reserved data space, do not use    */

    /***************************************************************************
     multicast socket information
    ***************************************************************************/
    uint32_t  mc_dest_addr;           /**< Multicast Destination address      */
    uint32_t  mc_group_addr;          /**< Multicast group address            */
    uint16_t  mc_dest_port;           /**< Multicast Destination port         */
    uint16_t  mc_src_port;            /**< Multicast Source port              */
};

/***************************************************************************//**
  @brief socket type definition
  @details Abbreviation for socket_struct
*******************************************************************************/
typedef struct socket_struct SOCKET;


/***************************************************************************//**
  @anchor SOCKET_ERROR_CODE
  @name Socket Error Codes
   Socket Error Codes, read with @ref socket_struct ->@ref socket_struct#error_code "error_code"
  @sa socket_struct
  @{
*******************************************************************************/
#define SO_TRANSMIT_ERROR       0x00000001  /*  Transmit error                */
#define SO_NO_ARP_ADDRESS       0x00000002  /*  Unresolved destination MAC    */
#define SO_TIMED_OUT            0x00000003  /*  transfer function timed out   */
#define SO_IN_USE               0x00000004  /*  TCP only: not ready           */
#define SO_NOT_ESTABLISHED      0x00000005  /*  TCP only: not connected       */
#define SO_CONNECTION_RESET     0x00000006  /*  TCP only: connection reset by remote host */
#define SO_WRONG_CHECKSUM       0x00000007  /*  net_recv():: data checksum failed */
#define SO_BUFFER_TOO_SMALL     0x00000008  /*  net_recv():: data > maxdatalen received */
#define SO_NO_INPUT_BUFFER      0x00000009  /*  net_recv():: NULL pointer given as data buffer */
#define SO_NOT_OPEN             0x0000000a  /*  Socket is not open            */
#define SO_CONNECTION_CLOSED    0x0000000c  /*  TCP only: connection closed   */
#define SO_WINDOW_ERR           0x0000000d  /*  TCP only: window size zero received */
#define SO_CONNECTION_ESTABLISHED 0x0000000e /* TCP only: connected           */
#define SO_MMU_ERROR            0x0000000f  /*  SMCS91c111: MMU error         */
#define SO_SEND_PENDING         0x00000010  /*  Send pending                  */
#define SO_NO_LINK              0x00000011  /*  No valid link                 */
#define SO_DNS_ERR              0x00000012  /*  Name resolution missing or pending */
#define SO_NO_TCP_MEM           0x00000013  /*  TCP out of memory             */

/*@}*/

/***************************************************************************//**
  @name Socket Configuration
  Use with socket_open_dev()
  @{
*******************************************************************************/
#ifndef INVALID_SOCKET
#define INVALID_SOCKET NULL           /**< Invalid Socket                     */
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR    (-1L)         /**< Socket Error, net_recv() and net_send() return value */
#endif

/*******************************************************************************
   Socket data types, use with socket_open_dev()
*******************************************************************************/
#define DATATYPE_CHAR   0x1 /**< socket_open_dev() Parameter: Data type character */
#define DATATYPE_SHORT  0x2 /**< socket_open_dev() Parameter: Data type short     */
#define DATATYPE_INT    0x4 /**< socket_open_dev() Parameter: Data type int       */

/*******************************************************************************
   Socket protocol types, use with socket_open_dev()
*******************************************************************************/
#define IPT_TCP 0x06        /**< socket_open_dev() Parameter: Protocol type TCP @hideinitializer*/
#define IPT_UDP 0x11        /**< socket_open_dev() Parameter: Protocol type UDP @hideinitializer*/

#define TCP_INIT_FUNC tcp_init   /**< socket_open_dev() Parameter: TCP initialization handler @hideinitializer*/
#define UDP_INIT_FUNC udp_init   /**< socket_open_dev() Parameter: UDP initialization handler @hideinitializer*/
#define ICMP_INIT_FUNC icmp_init /**< socket_open_dev() Parameter: ICMP initialization handler @hideinitializer*/

/*******************************************************************************
   socket_open() Parameter: Broadcast and Any IP address
*******************************************************************************/
#define ANY_ADDRESS      "0.0.0.0"          /* Any IP address                 */
#define BROADCAST        "255.255.255.255"  /* Broadcast IP address           */

/***************************************************************************//**
   Macro for testing multicast messages
*******************************************************************************/
#define IS_MULTICAST(a)  ((a & 0x00f00000) == 0x00e00000 )

/*******************************************************************************
 Well known ports and IP adresses
*******************************************************************************/
#define ANY_PORT         0       /**< Used for servers                        */
#define ECHO_PORT        0x07    /**< Echo port                               */
#define TIME_SERVER_PORT 0x0D    /**< Time server port                        */
#define FTP_DATA_PORT    0x14    /**< FTP data port                           */
#define FTP_CONTROL_PORT 0x15    /**< FTP control port                        */
#define TELNET_PORT      0x17    /**< FTP telnet port                         */
#define DNS_SERVER_PORT  0x35    /**< DNS server port                         */
#define DHCP_SERVER_PORT 0x43    /**< DHCP server port                        */
#define DHCP_CLIENT_PORT 0x44    /**< DHCP client port                        */
#define TFTP_SERVER_PORT 0x45    /**< TFTP server port                        */
/*@}*/


/***************************************************************************//**
  @name Socket Option
  Use with set_socket_option()
  @{
*******************************************************************************/

/*******************************************************************************
   Socket options, use with set_socket_option()
*******************************************************************************/
#define SO_UDP_NO_CHECKSUM      0x00000004 /* set_socket_option() Parameter: UDP w/o checksum              */
#define SO_TCP_STATE_CLOSED     0x00000008 /* set_socket_option() Parameter: use TCP state closed          */
#define SO_TCP_NO_RETRANS       0x00000020 /* set_socket_option() Parameter: disable TCP retransmit        */
#define SO_TCP_NO_FAST_RETRANS  0x00000040 /* set_socket_option() Parameter: disable fast TCP retransmit   */
#define SO_USE_PROXY            0x00000200 /* set_socket_option() Parameter: use proxy server              */
/*@}*/

/*@}*/


/***************************************************************************//**
  @addtogroup ARP  ARP Address Resolution Protocol
  @{
*******************************************************************************/
/***************************************************************************//**
 @brief Hardware MAC / IP address pair description
 @details For each device a MAC address is unique, but the IP address may change.
 To resolve the MAC address for a given IP address the address resolution protocol
 (ARP) is used. The resolved address is stored in structure addr_type.
 @see arp_check_ip_address(), check_arp_address(),
*******************************************************************************/
typedef struct
{
    uint16_t  mac[3];                     /**< MAC address                    */
    uint16_t  ip[2];                      /**< IP address (16 bit chunks)     */

    /***********************************************************************//**
     IP address in network byte order.
     Use inet_ntoa() and inet_aton() for conversion
    ***************************************************************************/
    uint32_t  ip_a;    /* IP address                                          */
} addr_type;

/***************************************************************************//**
 @brief Hardware address cache description
 @details Chained list for known IP/MAC addresses. For TCP and UDP this list is
 maintained automatically in background. No user intervention is necessary. For
 RAW-IP sockets the user is responsible for performing the address resolution.
 @see arp_check_ip_address(), check_arp_address(),
*******************************************************************************/
typedef struct arp_list
{
    addr_type  addr;                      /**< MAC / IP pair                  */
    uint16_t   used;                      /**< Used entry                     */
    uint8_t    valid;                     /**< Valid address                  */
    uint32_t   send;                      /**< ARP request sent               */
    uint16_t   resend;                    /**< ARP resend counter             */
    uint32_t   time;                      /**< Invalidate time                */
    struct arp_list * next;               /**< Next entry                     */
} arp_list_type;

/*@}*/


/***************************************************************************//**
  @addtogroup TCP  TCP Transmission Control Protocol
  @{
*******************************************************************************/
/***************************************************************************//**
  @name TCP state
  use with tcp_get_state()
  @{
*******************************************************************************/
#define TCP_CLOSED             0   /**< TCP Socket Closed                     */
#define TCP_LISTEN             1   /**< TCP Socket Listening for connection   */
#define TCP_SYN_SENT           2   /**< TCP Socket Active, have sent SYN      */
#define TCP_SYN_RECEIVED       3   /**< TCP Socket Have sent and received SYN */
#define TCP_ESTABLISHED        4   /**< TCP Socket Established                */
/******************************************************************************/
/*@}*/

/***************************************************************************//**
  @name TCP options
  use with tcp_set_option()
  @{
*******************************************************************************/
/***************************************************************************//**
  TCP unacknowledged segment size
  @code
  // ***************************************************************************
  // set TCP option for unacknowledged packet segment size of 4380 bytes
  // ***************************************************************************
  tcp_set_option (socket, TCP_UNA_SEG, 3*1460);
  @endcode
*******************************************************************************/
#define TCP_UNA_SEG 1  /* TCP unacknowledged segment size                     */

/***************************************************************************//**
  TCP retransmit delay time
  @code
  // ***************************************************************************
  // set shorter TCP retransmit delay
  // ***************************************************************************
  tcp_set_option (socket, TCP_RETRANS_DELAY, 0x40);
  @endcode
*******************************************************************************/
#define TCP_RETRANS_DELAY  2  /* TCP retransmit delay time                    */
/*@}*/

/*@}*/

/**************************************************************************//**

 @addtogroup MISC  Miscellaneous
 @{
*******************************************************************************/
/***************************************************************************//**
   netlib revision string
*******************************************************************************/
extern const char netlib_ver[];
/*@}*/

/***************************************************************************//**
  @addtogroup DHCP  DHCP  Dynamic Host Configuration Protocol
  @{
*******************************************************************************/
/***************************************************************************//**
   Macro for testing link-local addresses
*******************************************************************************/
#define IS_LINKLOCAL(a)  ((a & 0xffff0000) == 0xfea90000 )
/*@}*/

/***************************************************************************//**

 @addtogroup EFS  EFS Embedded File System
 @{
*******************************************************************************/
#ifndef _FSYS_DEF
#define _FSYS_DEF

/*******************************************************************************
  @note don't change these maximum values
*******************************************************************************/
#if defined(_TMS320C2000)
#define MAX_USER                  4    /**< Maximum parallel users            */
#define MAX_DIR                   20   /**< Maximum directories               */
#define MAX_NAME_LEN              30   /**< Maximum name length               */
#define MAX_USERNAME_LEN          30   /**< Maximum username length           */
#define MAX_PASS_LEN              30   /**< Maximum password length           */
#else
#define MAX_USER                  10   /* Maximum parallel users              */
#define MAX_DIR                   200  /* Maximum directories                 */
#define MAX_NAME_LEN              60   /* Maximum name length                 */
#define MAX_USERNAME_LEN          30   /* Maximum username length             */
#define MAX_PASS_LEN              30   /* Maximum password length             */
#endif

/***************************************************************************//**
  @brief Embedded File System directory
*******************************************************************************/
typedef struct
{
    char          dir[MAX_NAME_LEN];  /**< Directory name                     */
    char          name[MAX_NAME_LEN]; /**< File name                          */
    int32_t       size;               /**< File size                          */
    uint32_t      access;             /**< File access                        */
    int8_t        type;               /**< File type 'A'-ASCII, 'B'-bin or 'I'-hex */
    uint32_t      offset;             /**< Location of data in RAM or FLASH   */
    uint32_t      max_offset;         /**< Maximum address offset             */
    uint32_t      pos;                /**< Position of data pointer           */
    uint32_t      rw;                 /**< Read write flag                    */
    uint32_t      timeout;            /**< Timeout counter                    */
    SOCKET       *data_con;           /**< Connected data socket              */
    char         *buffer;             /**< Data buffer for transfer           */
    int32_t       error;              /**< Error_code                         */
    char         *auth_key;           /**< Authentication key                 */
    char         *auth_name;          /**< Authentication name                */
    int32_t       index;              /**< Directory index                    */

    int8_t         (*get_byte) (uint32_t , uint32_t ); /**< File read callback function */
    int32_t        (*put_byte) ( int32_t , int8_t);    /**< File write callback function */
} direntry_type;


/***************************************************************************//**
  @brief User authentication and directory specification
*******************************************************************************/
typedef struct
{
    char           name[MAX_USERNAME_LEN];  /**< User name                    */
    char           pass[MAX_PASS_LEN];      /**< User password                */
    direntry_type *dir[MAX_DIR];            /**< Directories                  */
    uint16_t       max_dir;                 /**< Number of directories        */
} user_type;

/*******************************************************************************
 @cond       PRIVATE
*******************************************************************************/
/*******************************************************************************
 @brief MMC function addresses, assigned at runtime
*******************************************************************************/
typedef struct
{
    int32_t        (*initialize) ();
    int32_t        (*init_card) ();
    uint8_t        (*readblock) ();
    uint16_t       (*writeblock) ();
    int8_t         (*get_byte) ();
    int8_t         (*put_byte) ();
    uint8_t        (*readcsd) ();
    uint8_t        (*readcid) ();
} mmc_function_type;
/*******************************************************************************
 @endcond
*******************************************************************************/

/***************************************************************************//**
  @name Access Permission
  use with direntry_type::access
*******************************************************************************/
/*@{*/
#define FTP_READ    1                 /**< Read files                         */
#define FTP_CREATE  2                 /**< Create new files                   */
#define FTP_WRITE   4                 /**< Overwrite or delete existing files */
#define FTP_RW      (FTP_READ | FTP_WRITE) /**< Read and write permission     */
#define FTP_RAM     8                 /**< File located in RAM                */
/*@}*/

/***************************************************************************//**
  @name Flags
  Use with fsys_send_all()
  @{
*******************************************************************************/
#define FSYS_SEND_ALL          0x00000010 /**< Perform a blocking call        */
#define FSYS_WRITE_BOOT_SECTOR 0x00000020 /**< Allows to write FLASH bootsector */
#define FSYS_ERASE_SECTOR      0x00000040 /**< Pre-Erase FLASH sector         */
/*@}*/

/***************************************************************************//**
  @anchor EFS_ERROR_CODE
  @name Return codes
  Use with fsys_send_all()
  @{
*******************************************************************************/
#define FSYS_BIOS_PROTECT_ERROR    -1 /**< BIOS protection error (D.Module only) */
#define FSYS_CHECKSUM_ERROR        -2 /**< Checksum error                     */
#define FSYS_INTEL_HEX_ERROR       -3 /**< Intel Hex Format error             */
#define FSYS_SECTOR_ERASE_ERROR    -4 /**< FLASH sector erase error           */
#define FSYS_FLASH_PROGRAM_ERROR   -5 /**< FLASH program error                */
#define FSYS_BUFFER_UNDERRUN_ERROR -6 /**< Buffer underrun error              */
#define FSYS_OUT_OF_MEMORY_ERROR   -7 /**< Out of memory error                */
#define FSYS_OUT_OF_RANGE_ERROR    -8 /**< Out of range error                 */
/*@}*/

/*@}*/

/***************************************************************************//**
 Message log function. E.g. printf() or CPrintf()
 Use with net_print_stat()
*******************************************************************************/
typedef void (*tpMessageLogFxn) (const char* format, ...);




/*******************************************************************************

  FUNCTION PROTOTYPES

*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* !__cplusplus */
#include <stdlib.h>



/***************************************************************************//**

 @addtogroup INIT Initialization
 @{
*******************************************************************************/
/***************************************************************************//**
 @cond SMSC91C111
 @addtogroup INITHW  SMSC91c111 Initialization
 @details Initialization functions for SMSC91c111
 @{
*******************************************************************************/


/***************************************************************************//**

 @brief    Add ethernet adapter to active adapterlist
 @param    type      -   adapter type  (ETH8900, ETH91C111, ETH642, ETHAX88783, ETHDM9010B, ETHKSZ8851 )
 @param    addr      -   adapter address
                     -       (BASE_ADDRESS + 0x00000) - 1st adapter
                     -       (BASE_ADDRESS + 0x40000) - 2nd adapter
                     -       (BASE_ADDRESS + 0x80000) - 3rd adapter
                     - (* offset depends on address selection logic)
 @param    bus_speed -   bus speed (obsolete)
 @return
           -  0..2      -   adapter number 1..3
           -  <0        -   error
 @see      ETH8900, ETH91C111, ETH642, ETHAX88783, ETHDM9010B, ETHKSZ8851

*******************************************************************************/
int32_t add_adapter ( uint32_t type, uint32_t addr, uint32_t bus_speed );

/***************************************************************************//**

 @brief   set the DSP clock parameter for internal delay and retransmit loops
 @param   dsp_clock - DSP clock [in Hz]
 @return  always 1

*******************************************************************************/
uint16_t dsk_board_init ( uint32_t dsp_clock);


/***************************************************************************//**

 @brief  LAN chip initialization

 Initializes the ethernet controller. This function resets the
 Ethernet controller, initializes EMIF for the predefined ce-space,
 initializes the receiver and transmitter sections, and configures the
 controller for full, half duplex or fibre mode and 10 or 100 MBit networkspeed.

 @param      dev_nr  - Adapter to initialize
 @param      mode    - AUTO_NEG, HDX_10, HDX_100, FDX_10, FDX_100, FDX_1000
 @param      link_status - callback function for signaling a link status
                          change

 @return     TRUE (1)          - when successfull
 @return     FALSE (0)         - out of memory (heap)
 @return     ERR_NO_SMCCHIP    - no lan chip found
 @return     ERR_WRONG_VERSION - wrong lan chip revision
 @return     ERR_INVALID_EPROM - wrong EEPROM content
 @return     ERR_WRONG_MAC     - wrong MAC-address
 @see      ERR_NO_SMCCHIP, ERR_WRONG_VERSION, ERR_INVALID_EPROM, ERR_WRONG_MAC,
           AUTO_NEG, HDX_10, HDX_100, FDX_10, FDX_100, FDX_1000

*******************************************************************************/
uint16_t dsk_init_dev ( uint16_t dev_nr,
                        uint8_t mode,
                        void (*link_status)(uint8_t));

/* @} */
/***************************************************************************//**
 @endcond
*******************************************************************************/

/**************************************************************************//**

 @addtogroup INITSOFT  Software Initialization
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      Main network initialization function

 @details    Initialize ARP table, sockets, timers and protocol specific handlers
                and assign the unique IP address (static or dynamic)

 @param      ip
                       - fixed IP address or
                       - fully qualified host name if DHCP is used
 @param      dhcp_func
                       - NULL if fixed IP address is used,
                       - DHCP_ENABLE if DHCP is used
 @param      dns
                       - empty string or NULL if DNS not used or
                       - IP address of the DNS server
                       - if DHCP and DNS are used, a NULL will select
                         the DHCP server machine for name resolution
 @param      dns_func
                       - NULL if DNS is not used or
                       - DNS_ENABLE if DNS is used
 @param      dev_nr    - Adapter to initialize

 @return
             - TRUE => success
             - FALSE => out of memory
 @note       This function MUST be called prior to any other net_lib function calls
             (except for the board initialization dsk_init_dev())
 @note       If option DHCP_ENABLE is used, net_init() is a blocking call until the
             IP address is assigned

 @library    net.lib
 @prototype  multidsknet.h
 @see        DNS_ENABLE, DHCP_ENABLE, @ref SWINIT, @ref DHCP, @ref DNS

*******************************************************************************/
int32_t net_init (char     *ip,
                  uint32_t (*dhcp_func)(char *, uint16_t),
                  char     *dns,
                  uint32_t (*dns_func)(void),
                  uint16_t dev_nr);
/*@}*/

/*******************************************************************************
  enable additional protocols in net_init()
*******************************************************************************/
/***************************************************************************//**

 @cond       PRIVATE
 @brief      Initiate DHCP request
 @param      not available for user
 @return     not available for user
 @library    net.lib
 @prototype  multidsknet.h
 @see        net_init(), DHCP_ENABLE
 @note       dhcp_enable() is a netlib internal callback function. It's not
             supposed to be called from user application directly. Use define
             DHCP_ENABLE with net_init() to link additional code to the program,
             if DHCP is required.
 @code
             net_init ("dsp.system.net", DHCP_ENABLE, NULL, DNS_ENABLE);
 @endcode

*******************************************************************************/
uint32_t dhcp_enable (char *, uint16_t);
/***************************************************************************//**
 @endcond
*******************************************************************************/

/***************************************************************************//**

 @cond       PRIVATE
 @brief      Enable DNS
 @param      void
 @return     not available for user
 @library    net.lib
 @prototype  multidsknet.h
 @see        net_init(), DNS_ENABLE
 @note       dns_enable_server() is a netlib internal callback function. It's
             not supposed to be called from user application directly. Use
             define DHCP_ENABLE with net_init() to link additional code to the
             program, if DNS is required.
 @code
             net_init ("192.168.1.100", NULL, "192.168.1.1", DNS_ENABLE);
 @endcode

*******************************************************************************/
uint32_t dns_enable_server (void);
/***************************************************************************//**
 @endcond
*******************************************************************************/

/**************************************************************************//**

 @addtogroup INITLINKSTATUS  Link Status Callback
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      User definable link status change callback function
 @param      mode - HDX_10, HDX_100, FDX_10, FDX_100, FDX_1000
 @return     nothing
 @prototype  multidsknet.h
 @see        HDX_10, HDX_100, FDX_10, FDX_100, FDX_1000,
                dsk_init_dev()
 @note       Add this function to your application, if link status notification is required
 @code
    void link_status (uint8_t mode)
    {
        CPrintf ("\r\n Link status changed: ");

        switch (mode)
        {
            case 0xff:
                CPrintf ("No Link\r\n");
                break;

            default:
                CPrintf ("Linked at %dMbit %s duplex\r\n",
                        (mode & SPEED_100) ? 100:10,
                        (mode & FULL_DUPLEX) ? "full":"half");
                break;
        }
    }
 @endcode

*******************************************************************************/
void link_status1 (uint8_t mode);
void link_status2 (uint8_t mode);
/*@}*/

/*@}*/




/***************************************************************************//**

 @addtogroup SOCKETS  Sockets
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      Create a new socket
 @param      dest_addr
                       -   destination (remote) IP address (e.g. "192.168.1.12")
                       -   or host name if DNS is used (e.g. "host_pc.system.net")
 @param      dest_port
                       -   well known (remote) port (<1025), e.g. 13 for time server
                       -   user-defined ports starting at 1025,
                            use ANY_PORT if a server (e.g. echo server)
                            should run on the DSP
 @param      src_port  @li source (local) port
 @param      data_type @li type of data to be transmitted/received
                           - DATATYPE_CHAR (8 bits)
                           - DATATYPE_SHORT (16 bits) or
                           - DATATYPE_INT (32 bit integers and floats)
 @param      init_func @li   function to initialize socket,
                             use UDP_INIT_FUNC or TCP_INIT_FUNC
 @param      dev_nr    @li   device number specifies the adapter number the
                             socket is bound to

 @return     pointer to socket, NULL if socket cannot be created
 @library    net.lib
 @prototype  multidsknet.h
 @see        UDP_INIT_FUNC, TCP_INIT_FUNC, DATATYPE_CHAR, DATATYPE_SHORT, DATATYPE_INT,
             ANY_PORT, ANY_ADDRESS, @ref SOCKET

*******************************************************************************/
SOCKET *socket_open_dev (char *dest_addr,
                         uint16_t dest_port,
                         uint16_t src_port,
                         uint8_t data_type,
                         int32_t (*init_func)(SOCKET *),
                         uint16_t dev_nr);

/***************************************************************************//**

 @brief      bind socket to adapter
 @param      so     -   the socket to bind
 @param      dev_nr -   device number specifies the adapter number
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void socket_bind_adapter (SOCKET *so, uint16_t dev_nr);

/***************************************************************************//**

 @brief      obtain adapter number the socket is bound to
 @param      so     -   socket
 @return     adapter number
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint16_t socket_get_adapter (void *so);

/*******************************************************************************
  enable protocols in socket_open()
*******************************************************************************/
/***************************************************************************//**
 @cond       PRIVATE
 @brief      Initialize TCP
 @param      not available for user
 @return     always true
 @library    net.lib
 @prototype  multidsknet.h
 @see        TCP_INIT_FUNC, socket_open_dev()
 @note       tcp_init() is a netlib internal callback function. It's not
             supposed to be called from user application directly. Use define
             TCP_INIT_FUNC with socket_open_dev() to link additional code to the
             program, if TCP is required.

*******************************************************************************/
int32_t tcp_init(SOCKET *so);
/***************************************************************************//**
 @endcond
*******************************************************************************/

/***************************************************************************//**

 @cond       PRIVATE
 @brief      Initialize UDP
 @param      not available for user
 @return     always true
 @library    net.lib
 @prototype  multidsknet.h
 @see        UDP_INIT_FUNC, socket_open_dev()
 @note       udp_init() is a netlib internal callback function. It's not
             supposed to be called from user application directly. Use define
             UDP_INIT_FUNC with socket_open_dev() to link additional code to the
             program, if UDP is required.

*******************************************************************************/
int32_t udp_init(SOCKET *so);
/***************************************************************************//**
 @endcond
*******************************************************************************/

/***************************************************************************//**

 @cond       PRIVATE
 @brief      Initialize ICMP
 @param      not available for user
 @return     always true
 @library    net.lib
 @prototype  multidsknet.h
 @see        ICMP_INIT_FUNC, socket_open_dev()
 @note       icmp_init() is a netlib internal callback function. It's not
             supposed to be called from user application directly. Use define
             ICMP_INIT_FUNC with socket_open_dev() to link additional code to the
             program, if ICMP is required.
 @note       If install_icmp_socket() is used no further socket_open_dev() is needed
             for ICMP (ping) support.

*******************************************************************************/
int32_t icmp_init(SOCKET *so);
/***************************************************************************//**
 @endcond
*******************************************************************************/

/***************************************************************************//**

 @brief      Close a socket and free all associated memory
 @param      so -   the socket to close
 @return
             - TRUE if successful
             - FALSE if socket does not exist
 @library    net.lib
 @prototype  multidsknet.h
 @see        shutdown()

*******************************************************************************/
int32_t socket_close (SOCKET *so);

/***************************************************************************//**

 @brief      Install a user callback function for a specific socket
 @details    Define a callback function for event notification of a specific
             socket. Possible events are new received data or socket errors.
             This function calls set_recv_buffer() with parameters so, data and
             maxdata to pre-initialize a receive buffer.
 @param      so                 - Socket for callback
 @param      call_back_function - User defined call back function
 @param      data               - pointer to receive buffer
 @param      maxdata            - receive buffer size
 @return     -
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void socket_define_callback (SOCKET *so,
                             int32_t (*call_back_function)(SOCKET *, void *, uint32_t , uint32_t),
                             void *data,
                             uint16_t maxdata);

/***************************************************************************//**

 @brief      Retrieve a data pointer from socket
 @details    This function returns the current data buffer of socket so.
 @param      so - Socket to get the data pointer from
 @return     current data pointer
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void *socket_get_data_pointer (SOCKET *so);

/***************************************************************************//**

 @brief      Modify socket options
 @param      so     -   the socket to modify
 @param      option -   options, use SO_xxx constants
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t set_socket_option (SOCKET *so,
                            uint32_t option);

/*@}*/


/***************************************************************************//**

 @addtogroup ARP  ARP Address Resolution Protocol
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      Perform MAC address lookup in local ARP cache to find MAC address
             for specified IP address
 @details    Before a message can be sent over ethernet the destination MAC
             address must be known. Use this function to search the local ARP
             cache for a valid MAC address. The returned pointer to the valid
             MAC address (arp->addr) can be used as parameter for send_ip().
             All higher level send functions (net_send(), net_send_ready() and
             net_send_string() ) use this function and arp_check_address() for
             address resolution.

 @param      ip     - IP address ( in network byte order)
 @param      dev_nr - Adapter
 @return
             - pointer to mac address
             - NULL if nothing found
 @library    net.lib
 @prototype  multidsknet.h
 @note       This function does not perform an ARP request if address is not found
 @see        inet_ntoa(), inet_aton() for address conversion

*******************************************************************************/
arp_list_type * arp_check_ip_address (uint32_t ip, uint16_t dev_nr);

/***************************************************************************//**

 @brief      Perform address resolution
 @details    This function performs a ARP cache lookup for the destination IP
             address the socket so is configured to. If the address is not found
             or invalid a new ARP request is started. In case of a new ARP request
             the function configures the stack for the time between two
             consecutive requests and returns after sending the first request.
             Please note that in this case the returned pointer is NULL because
             a wait for the ARP answer could take a indetermined period of time.
 @param      so  - socket with unresolved or resolved IP address
 @param      request_time - time between two requests
 @return
             - pointer to MAC address
             - NULL if request timed out
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
arp_list_type *check_arp_address (SOCKET *so,
                                  uint32_t request_time);

/***************************************************************************//**

 @brief      Invalidate ARP cache
 @details    When the device is plugged from one hub or router to an other it
             may be necessary to clear the ARP cache. Use this function to
             initiate a full ARP cache clear.
 @param      -
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h
 @warning    Consecutice function calls to net_send() may fail due to unresolved
             addresses.

*******************************************************************************/
void arp_clear_cache (void);

/***************************************************************************//**

 @brief      Set timebase for ARP cache.
 @details    Set the aging for ARP addresses.
 @param      val - timeout counter (number of net_isq() loop counts)
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void arp_set_timeout (uint32_t val);

/***************************************************************************//**

 @brief      Invalidates specific IP address
 @details    If a specific IP address is known to be invalid or is going to be
             invalid in the future, use this function to invalidate this address.
 @param      ip - IP address
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void arp_invalid_ip_address (uint32_t ip);
/*@}*/



/***************************************************************************//**

 @addtogroup IP  IP Internet Protocol
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      Low-level send function for sending RAW IP packets
 @param      so - socket to use
 @param      dest   -   destination address information
 @param      len    -   length of data to be transmitted
 @param      id     -   unique packet id
 @return
             - FALSE => success
             - TRUE => error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int16_t send_ip (SOCKET *so,
                 addr_type *dest,
                 uint16_t len,
                 uint16_t id);

/***************************************************************************//**

 @brief      Send a message via the specified socket
 @param      so   -   pointer to socket
 @param      data -   pointer to data, data type as specified in socket_open_dev()
 @param      len -    length of data
 @return
             - >0  message was send immediately
             - <= 0 message could not be delivered immediately,
                  it was passed to protocol stack for delivery,
                          read socket->error_code for details
 @library    net.lib
 @prototype  multidsknet.h
 @warning    A return value true does NOT guarantee successful transmission
 @see        socket_open_dev(), @ref socket_struct ->@ref socket_struct#error_code "error_code",
             SO_TRANSMIT_ERROR, SO_NO_ARP_ADDRESS, SO_IN_USE, SO_NOT_ESTABLISHED,
             SO_NOT_OPEN, SO_CONNECTION_CLOSED, SO_WINDOW_ERR, SO_MMU_ERROR,
             SO_SEND_PENDING, SO_NO_LINK, SO_DNS_ERR

*******************************************************************************/
int32_t net_send (SOCKET *so,
                  void *data,
                  uint16_t len);

/***************************************************************************//**

 @brief      Send a zero terminated string via the specified socket.

 @details    The string can be longer than the maximum packet size. In this case
             it's broken into several packets by net_send_ready(). This is a
             blocking function. a return value true does NOT guarantee
             successful transmission
 @param      so   -   pointer to socket
 @param      data -   pointer to zero terminated data, data type as specified in socket_open()
 @return
             - TRUE if data was successfully sent
             - FALSE if data could not be send, read socket->error_code for details
 @library    net.lib
 @prototype  multidsknet.h
 @see        socket_open_dev(), @ref socket_struct ->@ref socket_struct#error_code "error_code",
             SO_TRANSMIT_ERROR, SO_NO_ARP_ADDRESS, SO_IN_USE, SO_NOT_ESTABLISHED,
             SO_NOT_OPEN, SO_CONNECTION_CLOSED, SO_WINDOW_ERR, SO_MMU_ERROR,
             SO_SEND_PENDING, SO_NO_LINK, SO_DNS_ERR

*******************************************************************************/
int32_t net_send_string (SOCKET *so,
                         char *data);

/***************************************************************************//**

 @brief      Send a message via the specified socket, wait until message is
    successfully transmitted or a timeout occured
 @param      so   -    pointer to socket
 @param      data -    pointer to the data, data type as specified in socket_open_dev()
 @param      len  -    length of data
 @param      timeout - timeout for transmission = number of re-tries
 @return
             - TRUE if data was successfully sent
             - FALSE if data could not be send, read socket->error_code for details
 @library    net.lib
 @prototype  multidsknet.h
 @see        socket_open_dev(), @ref socket_struct ->@ref socket_struct#error_code "error_code",
             SO_TRANSMIT_ERROR, SO_NO_ARP_ADDRESS, SO_IN_USE, SO_NOT_ESTABLISHED,
             SO_NOT_OPEN, SO_CONNECTION_CLOSED, SO_WINDOW_ERR, SO_MMU_ERROR,
             SO_SEND_PENDING, SO_NO_LINK, SO_DNS_ERR

*******************************************************************************/
int32_t net_send_ready (SOCKET *so,
                        void *data ,
                        uint32_t len,
                        uint32_t timeout);


/***************************************************************************//**

 @brief      Receive data via the specified socket
 @param      so   -     pointer to socket
 @param      data -     pointer to receive buffer
 @param      maxdatasize - maximum allowed length
 @return
             - > 0 new data received, return value equal to length of data
             - = 0 nothing received
             - < 0 SOCKET_ERROR, read socket->error_code for details.
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t net_recv (SOCKET *so,
                  void *data,
                  uint16_t maxdatasize);

/***************************************************************************//**

 @brief      Define a socket buffer
 @param      so   -     pointer to socket
 @param      data -     pointer to receive buffer
 @param      maxdatasize - maximum allowed length
 @return
             - (1) - success
             - < 0 socket error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t set_recv_buffer (SOCKET *so,
                         void *data,
                         uint16_t maxdatasize);

/***************************************************************************//**

 @brief      Receive data via the specified socket, wait until message is
    successfully received and connection closed from sender or a
    timeout occured.
 @param      so   -    pointer to socket
 @param      data -    pointer to receive buffer
 @param      len  -    pointer to maximum receive length,
                         returns received data length
 @param      timeout - timeout for receive = number of loop count
 @return
             - > 0 success, maximum data length received
             - = 0 success, data received and connection closed
             - < 0 error, read socket->error_code for details
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t net_recv_ready (SOCKET *so,
                        void *data,
                        int32_t *len,
                        uint32_t timeout);

/*@}*/

/**************************************************************************//**

 @addtogroup NETISQ net_isq()
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      The main polling function for processing sockets,
    must be periodically called in the main application
 @param      -
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h
 @see        @ref INTRO

*******************************************************************************/
void net_isq (void);

/*@}*/

/**************************************************************************//**

 @addtogroup ICMP  ICMP Internet Control Message Protocol
 @{
*******************************************************************************/
/***************************************************************************//**

 @brief      Install an ICMP socket for ping and messages
 @param      size -  maximum size of ICMP message to be processed
 @param      dev_nr - Adapter to use
 @return
             - pointer to socket
             - NULL if socket cannot be created
 @library    net.lib
 @prototype  multidsknet.h
 @note       This function actually calls socket_open_dev with predefined
             parameters for ICMP

*******************************************************************************/
SOCKET *install_icmp_socket_dev (uint16_t size, uint16_t dev_nr);
/*@}*/

/**************************************************************************//**

 @addtogroup TCP  TCP Transmission Control Protocol
 @{
*******************************************************************************/


/**************************************************************************//**

 @brief      Actively establish a connection
 @details    Actively establish a connection. A three-way-hand-shake is performed
             to negotiate transfer parameters. If a timeout of 0 is specified,
             this function returns immediately after a SYN is sent.
             You may identify the error condition by reading
             @ref socket_struct ->@ref socket_struct#error_code "error_code".

 @param      so   -     the socket to use
 @param      data -     pointer to a buffer to hold the data. The data type is
                         defined by the socket.
 @param      send_max - specifies the maximum tries to connect to host
 @param      timeout -  timeout if peer could not be connected measuerd in
                         loop count
 @return     true if connection successfully established, SOCKET_ERROR in case of errors. @n
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t connect (SOCKET *so,
                 void *data,
                 uint32_t send_max,
                 int32_t timeout);

/**************************************************************************//**

 @brief      Active shutdown of a TCP connection.
 @param      so      - the socket to use
 @param      timeout - timeout waiting for acknowledge finish from peer.
                        If timeout is zero, the socket state changes to listening
                        state immediately without waiting for a final ACK FIN
                        from peer ( useful for hanging connection).
 @return
             - >0 if connection successfully terminated
             - <0 in case of errors
 @library    net.lib
 @prototype  multidsknet.h
 @details    Active shutdown of a TCP connection.
 @note       This does not close the socket itself, only the connection is reset
             and must be re-established via connect if it should be used again.

*******************************************************************************/
int32_t shutdown (SOCKET *so, int32_t timeout);

/**************************************************************************//**

 @brief      Check TCP state; if connection established, the socket descriptor is
             returned else NULL.
 @param      so     - listening socket
 @return
             - so if connected
             - NULL if unconnected
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
SOCKET *accept (SOCKET *so);

/**************************************************************************//**

 @brief      Switch socket to listening state
 @param      so -   the socket to use
 @return
             - <0   invalid socket
             - TRUE    success
 @library    net.lib
 @prototype  multidsknet.h
 @note       When socket option @ref SO_TCP_STATE_CLOSED is used, tcp_listen()
             switches the internal socket state from closed to listening
             state. After shutdown or when errors occur the socket falls back
             into closed state.

*******************************************************************************/
int32_t tcp_listen ( SOCKET *so );

/**************************************************************************//**

 @brief      Set a TCP option
 @param      so     - valid socket
 @param      option - option to change
 @param      val    - value
 @return
             - FALSE  success
             - TRUE  error
 @library    net.lib
 @prototype  multidsknet.h
 @see        TCP_UNA_SEG, TCP_RETRANS_DELAY

*******************************************************************************/
uint16_t tcp_set_option (SOCKET *so, uint32_t option, uint32_t val);

/**************************************************************************//**

 @brief      Determine tcp state
 @param      so    -   the socket to use
 @return
             - <0      - invalid socket
             - else tcp state
 @library    net.lib
 @prototype  multidsknet.h
 @see        TCP_CLOSED, TCP_LISTEN, TCP_SYN_SENT, TCP_SYN_RECEIVED, TCP_ESTABLISHED

*******************************************************************************/
int16_t tcp_get_state ( SOCKET *so );

/**************************************************************************//**

 @brief      Test if the last TCP transmission was acknowledged
 @param      so - valid socket
 @return
             - TRUE   transmission complete
             - FALSE   waiting for acknowledge
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint16_t tcp_tx_complete (SOCKET *so);

/***************************************************************************//**

 @brief      returns the number of unacknowledged bytes

 @param      so - valid socket
 @return
             - 0  - transmission complete
             - >0  - transmission pending
             - 0xFFFFFFFF  - Invalid socket or not established
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t tcp_pending_window (SOCKET *so);

/***************************************************************************//**

 @brief      force a retransmit

 @param      so - valid socket
 @return
             - 1  - Socket error
             - 0  - function proceeded
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint16_t tcp_force_retransmit (SOCKET *so);

/**************************************************************************//**

 @brief      Set keep alive time
 @param      so        -   the socket to use
 @param      time      -   keep alive time
 @return     (-1) invalid socket
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int16_t tcp_set_keep_alive_time ( SOCKET *so , uint32_t time);

/**************************************************************************//**

 @brief      send a zero window packet
 @param      so        -   the socket to use
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void tcp_send_zero_window ( void *so );

/**************************************************************************//**

 @brief      update window size
 @param      so        -   the socket to use
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void tcp_send_window_update ( void *so );

/*@}*/


/**************************************************************************//**

 @addtogroup DNS  DNS Domain Name System
 @{
*******************************************************************************/

/**************************************************************************//**

 @brief      Get the ip address of clients specified by name

 @param      hostname - host name string
 @param      timeout - maximum loop count for this blocking function
 @return
             - FALSE - address resolution not possible
             - host address on successful name resolution
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t gethostbyname (char *hostname,
                        int32_t *timeout);
uint32_t gethostbyname_dev (char *hostname,
                            int32_t *timeout,
                            uint16_t dev_nr);
/*@}*/


/**************************************************************************//**

 @addtogroup MISC  Miscellaneous
 @{
*******************************************************************************/

/**************************************************************************//**

 @brief      Configure a gateway
 @param      ip - Gateway IP address
 @param      sub_mask - Subnet Mask
 @param      dev_nr - Adapter to use
 @return     always TRUE (1)
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t net_set_gateway (char *ip,
                          char *sub_mask,
                          uint16_t dev_nr);

/**************************************************************************//**

 @brief      Retrieve netlib revision string
 @param      buffer - buffer to hold string
 @return     pointer to buffer
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
char *get_netlib_ver ( char *buffer );

/**************************************************************************//**

 @brief      Allocate a data buffer, aligned to the processors cache line size
 @note       C6x only
 @param      size to allocate
 @return
             - NULL  out of memory
             - >0 success
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
char *net_allocate_aligned_buffer (int32_t size );

/**************************************************************************//**

 @brief      Get configured IP address
 @param      dev_nr   -  adapter number ( always 0 for DSK)
 @return     assigned IP address
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t get_ip_address (uint16_t dev_nr);

/**************************************************************************//**

 @brief      Set IP address
 @param      dev_nr   -  adapter number ( always 0 for DSK)
 @param      addr_str -  new IP address
 @return     assigned IP address
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t set_ip_address (uint16_t dev_nr, char* addr_str);

/**************************************************************************//**

 @brief      Get MAC address
 @param      dev_nr   -  adapter number ( always 0 for DSK)
 @param      dest     - destination buffer to hold MAC address string
 @return     MAC address
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t get_mac_address (uint16_t dev_nr, uint16_t *dest);

/**************************************************************************//**

 @brief      Print statistic TCP stack information
 @param      dev_nr  - device number
 @param      pLog    - pointer to printf function
 @library    net.lib
 @prototype  multidsknet.h
 @see        tpMessageLogFxn

*******************************************************************************/
void net_print_stat ( uint16_t dev_nr, tpMessageLogFxn pLog );
/*@}*/


/**************************************************************************//**

 @addtogroup CONV  Conversion Support Function
 @{
*******************************************************************************/

/**************************************************************************//**

 @brief      Convert IP-address from 0xbbaaddcc to "aaa.bbb.ccc.ddd"
 @param      i_addr - IP address in network-byte-order
 @param      s      - buffer space for conversion
 @return     pointer to converted buffer
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
char *inet_ntoa (uint32_t i_addr, char *s);

/**************************************************************************//**

 @brief      Converts zero terminated IP-address string from
             "aaa.bbb.ccc.ddd" to integer in network byte order.

 @param      s - ip address string
 @return     ip address in network byte order
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
uint32_t inet_aton (char *s);

/**************************************************************************//**

 @brief      Convert a short int from host to network byte order

 @param      val - short int to convert
 @return     converted short int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint16_t htons (uint16_t val)
{
    return ((uint16_t)((((val) & 0xff) << 8) | ((val) & 0xff00) >> 8));
}


/**************************************************************************//**

 @brief      Convert a short int from network to host byte order

 @param      val - short int to convert
 @return     converted short int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint16_t ntohs (uint16_t val)
{
    return ((uint16_t)((((val) & 0xff) << 8) | ((val) & 0xff00) >> 8));
}

/**************************************************************************//**

 @brief      Convert a long int from host to network byte order

 @param      val - long int to convert
 @return     converted long int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint32_t htonl (uint32_t val)
{
    return ((uint32_t) ((((val) & 0xff)       << 24  ) |
                        (((val) & 0xff00)     << 8   ) |
                        (((val) & 0xff0000)   >> 8   ) |
                         ((val) & 0xff000000) >> 24));
}

/**************************************************************************//**

 @brief      Convert a long int from network to host byte order

 @param      val - long int to convert
 @return     converted long int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint32_t ntohl (uint32_t val)
{
    return ((uint32_t) ((((val) & 0xff)       << 16  ) |
                        (((val) & 0xff00)     << 16  ) |
                        (((val) & 0xff0000)   >> 16  ) |
                         ((val) & 0xff000000) >> 16  ));
}

/**************************************************************************//**

 @brief      Convert two network short int to long host int

 @param      val1 - high word
 @param      val2 - low word
 @return     converted long int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint32_t nstohl (uint16_t val1, uint16_t val2)
{
    return( (uint32_t) ( (((uint32_t)(val1) & 0xff)   << 24 ) |
                         (((uint32_t)(val1) & 0xff00) << 8 )  |
                         (((uint32_t)(val2) & 0xff)   << 8  ) |
                         (((uint32_t)(val2) & 0xff00) >> 8 ) ) );
}

/**************************************************************************//**

 @brief      Convert two network short int to long

 @param      val1 - high word
 @param      val2 - low word
 @return     converted long int
 @prototype  multidsknet.h

*******************************************************************************/
static inline uint32_t nstonl (uint16_t val1, uint16_t val2)
{
    return ((uint32_t)((((uint32_t)(val1) & 0xffff) << 16 ) |
                        ((uint32_t)(val2) & 0xffff) ));
}

/*@}*/


/**************************************************************************//**

 @addtogroup MULTICAST Multicast
 @{
*******************************************************************************/

/**************************************************************************//**

 @brief      Join a multicast group
 @param      so    - socket, wich should join the multicast group
 @param      maddr - multicast address group string (e.g. "224.0.1.1")
 @param      mport - multicast port
 @return
             - > 0   successful
             - = 0   no socket
             - < 0   error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t multicast_join_group ( SOCKET *so, char *maddr, uint16_t mport );

/**************************************************************************//**

 @brief      Leave a multicast group
 @param      so    - socket, wich should leave the multicast group
 @param      maddr - multicast address group string (e.g. "224.0.1.1")
 @param      mport - multicast port
 @return
             - > 0   successful
             - = 0   no socket or address not found
             - < 0   error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t multicast_leave_group ( SOCKET *so, char *maddr, uint16_t mport );
/*@}*/



/***************************************************************************//**

 @addtogroup EFS  EFS Embedded File System
 @{
*******************************************************************************/

/***************************************************************************//**

 @brief      Initialize all directories specified in user_list
 @param      user_list  -  directory list
 @param      mmc_func   -  multi media card support function
 @return
             - TRUE  success
             - FALSE error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t fsys_init_dir ( user_type *user_list, mmc_function_type *mmc_func );

/***************************************************************************//**

 @brief      This function initializes all necessary internal parameters for
             a specific user file.

 @details    When file position or size has been changed, use this function to
             correct internal file parameters. Otherwise for no changes set
             offset or size to zero.
 @param      fp - file pointer
 @param      offset - new offset
 @param      size   - new size
 @return
             - TRUE  success
             - FALSE error
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t fsys_init_file ( direntry_type *fp, uint32_t offset, int32_t size);

/***************************************************************************//**

 @brief      Determine file size of specified file.

 @note       Reading size is only possible for ASCII type; for binary file type
             size the maximum value specified in user_list is taken.
 @param      *fp  - pointer to directory entry
 @return     file size
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
int32_t fsys_get_file_size (direntry_type  *fp);

/***************************************************************************//**

 @brief      File transmission function

 @details    This multi-purpose file transmission function allows to send or
             receive data (ASCII, binary or Intel-Hex) from or to FLASH/RAM
             space via connected TCP socket.
 @param      fp       - file to send
 @param      size     - some bytes left to send from previous packet
 @param      send_all - if TRUE all data will be sent immediately (blocking mode)
 @return
             - pointer to file = sending not finished
             - NULL            = all bytes transmitted
 @library    net.lib
 @prototype  multidsknet.h
 @see        FSYS_SEND_ALL, FSYS_WRITE_BOOT_SECTOR, FSYS_ERASE_SECTOR

*******************************************************************************/
direntry_type *fsys_send_all ( direntry_type *fp, int32_t size, int32_t send_all);

/***************************************************************************//**

 @brief      Initialize FLASH-sectors

 @details    Tag all FLASH-sectors as not empty for correct sector erase.
             Must be called before data is written into FLASH memory via
             fsys_send_all().
 @param      -
 @return     nothing
 @library    net.lib
 @prototype  multidsknet.h

*******************************************************************************/
void fsys_init_flash ( void );

/*@}*/


#endif   // _FSYS_DEF


#ifdef __cplusplus
} // extern "C"
#endif


#endif  // #ifndef _DSKNET_H_

