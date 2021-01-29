/*---------------------------------------------------------------------------*/
/**
  @file		modbus_utils.h
  @brief	Example modbus utilities header file

  This file contains much modbus utility functions.
  It helps to merge modbus function code and data to a PDU and split PDU
  to modbus function code and data.
  We split one request and response into four functions, for example if modbus
  master sends Read Coils request to slave and gets slave's response, we might
  have to use these four functions.

  Modbus Master					Modbus Slave
  1. MBReadCoils()		---->		2. MBGetReadCoils()
  4. MBGetResponseReadCoils()	<----		3. MBResponseReadCoils


 */
/*---------------------------------------------------------------------------*/

#ifndef MODBUS_UTILS_H
#define MODBUS_UTILS_H

/*---------------------------------------------------------------------------*/
/**
  @brief	get 16 bits data from buf
  @param	var	a 16 bits variable
  @param	buf	a pointer to data buffer
  @return	none
 */
/*---------------------------------------------------------------------------*/
#define GETU16( var, buf) {				\
		(var) = (*(buf) << 8) & 0xFF00;		\
		(var) |= (*((buf)+1) & 0xFF);		\
	}
/*---------------------------------------------------------------------------*/
/**
  @brief	put 16 bits data to buf
  @param	buf	a pointer to data buffer
  @param	var	a 16 bits variable
  @return	none
 */
/*---------------------------------------------------------------------------*/
#define PUTU16( buf, var) {				\
		(*(buf)) = ((var) >> 8);		\
		*((buf)+1) = ((var) & 0xFF);		\
	}
#endif

