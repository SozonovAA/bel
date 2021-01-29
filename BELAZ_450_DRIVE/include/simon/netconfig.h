/*******************************************************************************
*                                                                              *
*  @file      netconfig.c                                                      *
*  @verbatim                                                                   *
*                      ___ \    ___| _)              __ __|                    *
*                      |    | \    \  |   _     __ \   |                       *
*                      |    |  ---    | (   |  |   |   |                       *
*                     _____/_)_____/ _| \__,|  |  _|  _|                       *
*                                       |___/                                  *
*                     Digital Signalprocessing Technology                      *
*  @endverbatim                                                                *
*  @brief     example network configuration                                    *
*                                                                              *
*  @author    D.SignT GmbH & Co. KG, Claus Hermbusche                          *
*  @date      2011-09-23
*                                                                              *
*  Software License Agreement                                                  *
*  Copyright (C) 2011 D.SignT GmbH & Co. KG - http://www.dsignt.de             *
*                                                                              *
*  Redistribution and use in source and binary forms, with or without          *
*  modification, are permitted provided that the following conditions          *
*  are met:                                                                    *
*                                                                              *
*    Redistributions of source code must retain the above copyright            *
*    notice, this list of conditions and the following disclaimer.             *
*                                                                              *
*    Redistributions in binary form must reproduce the above copyright         *
*    notice, this list of conditions and the following disclaimer in the       *
*    documentation and/or other materials provided with the                    *
*    distribution.                                                             *
*                                                                              *
*    Neither the name of D.SignT GmbH & Co. KG nor the names of its            *
*    contributors may be used to endorse or promote products derived           *
*    from this software without specific prior written permission.             *
*                                                                              *
*  Disclaimer                                                                  *
*  THIS SOFTWARE IS PROVIDED BY D.SIGNT GMBH & CO. KG "AS IS" AND ANY          *
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE           *
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR          *
*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL D.SIGNT GMBH & CO. KG BE          *
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT           *
*  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR          *
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,       *
*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE        *
*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,           *
*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          *
*                                                                              *
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
  DSP speed
*******************************************************************************/
unsigned long dsp_clock = 150000000;

/*******************************************************************************
  SMC chip base address
*******************************************************************************/
#define SMC91C111_BASE    0x240180

/*******************************************************************************
 first adapter:
*******************************************************************************/
#define ADAPTER_1         0
static char dsp_ip_addr1[] = "10.121.36.40";
uint32_t SMC91C111_1 = SMC91C111_BASE;

/*******************************************************************************
 network mode: FDX_100, FDX_10, HDX_100, HDX_10, AUTO_NEG
*******************************************************************************/
static uint8_t network_mode1 = AUTO_NEG;

/*******************************************************************************
 second adapter:
*******************************************************************************/
#define ADAPTER_2    1
static char dsp_ip_addr2[] = "10.121.37.41";
uint32_t SMC91C111_2 = (SMC91C111_BASE+0x10000);

/*******************************************************************************
 network mode: FDX_100, FDX_10, HDX_100, HDX_10, AUTO_NEG
*******************************************************************************/
static uint8_t network_mode2 = AUTO_NEG;

/*******************************************************************************
 DNS configuration
*******************************************************************************/
static char dns_server_ip1[] = "192.168.168.1";
static char dns_server_ip2[] = "192.168.168.1";
//~ uint32_t (*dns_setting)(void) = NULL;
uint32_t (*dns_setting)(void) = DNS_ENABLE;

/*******************************************************************************
 DHCP setting
*******************************************************************************/
uint32_t (*dhcp_setting)(char *, uint16_t) = NULL;
//~ uint32_t (*dhcp_setting)(char *, uint16_t) = DHCP_ENABLE;


#ifdef __cplusplus
}
#endif /* extern "C" */

