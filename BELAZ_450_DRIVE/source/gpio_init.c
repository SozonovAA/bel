/*
 * gpio_init.c
 *
 */

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_GlobalPrototypes.h"

void gpio_init(void)
{
	EALLOW;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТЕСТОВЫЕ НОГИ
	//GPIO0 на выход ШИМ 1
			GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;

	//GPIO1
			GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;

	//GPIO3
			GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;

	//GPIO5
			GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;

	//GPIO8
			GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//GPIO4   													// выход оптики
			GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
			GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;


	EDIS;
}







