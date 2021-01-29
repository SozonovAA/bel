/****************************************************************************/
/*   ftpclient_flash.cmd - Sample linker command file for eZDSKF28335 and eZDSK-91c111     */
/*                                                                          */
/*   Description: This file is a sample F28335 linker command file that can */
/*                be used for linking programs built with the TMS320C2000   */
/*                C Compiler. Use it as a guideline; you may want to change */
/*                the allocation scheme according to the size of your       */
/*                program and the memory layout of your target system.      */
/****************************************************************************/
-l rts2800_fpu32.lib
/*-m BELAZ_450.map*/

MEMORY
{
PAGE 0 :    /* page 0 - program memory */
/* RAM */
    RAML_PROGRAM      : origin = 0x008000, length = 0x04000


/* FLASH */
    FLASHH     : origin = 0x300000, length = 0x008000     /* reserv */
    FLASHG     : origin = 0x308000, length = 0x008000     /* reserv */
    FLASHF     : origin = 0x310000, length = 0x008000     /* reserv */
    FLASHE     : origin = 0x318000, length = 0x008000     /* MAP file */

/* run self */
   BEGIN      : origin = 0x320000, length = 0x000002

/* run by loader */
  /*  BEGIN      : origin = 0x320000, length = 0x000002*/

	FLASHCD    : origin = 0x320002, length = 0x00fffe


    FLASHB     : origin = 0x330000, length = 0x008000     /* reserv */
    FLASHA     : origin = 0x338000, length = 0x007F00     /* BootLoader */

/* SYSTEM */
    CSM_RSVD   : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
    PASSWORDS  : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
    OTP        : origin = 0x380400, length = 0x000400     /* on-chip OTP */
    ADC_CAL    : origin = 0x380080, length = 0x000009     /* ADC_cal function in Reserved memory */
   
    IQTABLES   : origin = 0x3FE000, length = 0x000b50     /* IQ Math Tables in Boot ROM */
    IQTABLES2  : origin = 0x3FEB50, length = 0x00008c     /* IQ Math Tables in Boot ROM */  
    FPUTABLES  : origin = 0x3FEBDC, length = 0x0006A0     /* FPU Tables in Boot ROM */
    ROM        : origin = 0x3FF27C, length = 0x000D44     /* Boot ROM */        
    RESET      : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
    VECTORS    : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */


PAGE 1 :   /* page 1 - data memory */
/* RAM */
    BOOT_RSVD  : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
    RAMM0      : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
    RAMM1      : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
    RAML_DATA  : origin = 0x00C000, length = 0x004000



/* XINTF ZONE 0 */
    ALTERA		: origin = 0x4000, length = 0xff
	    
/* XINTF ZONE 6 */
  CURRENT_ARRAY				: origin = 0x100000, length = 0x00C807/*0x008000*/

  ALARM_ARRAYS_META_DATA	: origin = 0x1bfC00, length = 0x000028/*40-dec*/
  KOEFF_MEMORY				: origin = 0x1BFD00, length = 0x000032/*50-dec*/
  SLIDERS					: origin = 0x1bfE00, length = 0x000100
  SOST       				: origin = 0x140000, length = 0x000001
  STATE           			: origin = 0x140002, length = 0x000006


/* XINTF ZONE 7 */
  ECAT       : origin = 0x200000, length = 0x01000


}
 
SECTIONS
{
   /* 22-bit program sections */
   /* Allocate program areas: */

   array_sect		   : > CURRENT_ARRAY,       PAGE = 1

   altera_regs         : > ALTERA,       PAGE = 1
   REG_SOST            : > SOST,       PAGE = 1
   STATE_CONTROLLER    : > STATE,      PAGE = 1
   sliders    		   : > SLIDERS,      PAGE = 1
   AAMetaData  		   : > ALARM_ARRAYS_META_DATA,      PAGE = 1

/*
    xintf16			   : LOAD = FLASHCD,
						 RUN = RAML_PROGRAM,
						 LOAD_START(_XINTF16_loadstart),
						 RUN_START(_XINTF16_runstart),
						 SIZE(_XINTF16_size),
						 PAGE = 0*/

	secureRamVars    : > RAML_DATA,				PAGE = 1
   /* Section secureRamFuncs used by file SysCtrl.c. */

   secureRamFuncs    :   LOAD = FLASHCD,		PAGE = 0                /* Should be Flash */
                         RUN = RAML_PROGRAM,      PAGE = 0                /* Must be CSM secured RAM */
                         LOAD_START(_secureRamFuncs_loadstart),
                         LOAD_END(_secureRamFuncs_loadend),
                         RUN_START(_secureRamFuncs_runstart),
						 SIZE(_secureRamFuncs_size)



   ramfuncs            : LOAD = FLASHCD, PAGE = 0
                         RUN = RAML_PROGRAM,  PAGE = 0
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
					     SIZE(_RamfuncsSize)

rts_fpu32		/* :>L012SARAM,		PAGE = 0*/
      {
		-l rts2800_fpu32.lib<l_div.obj>(.text)
		-l rts2800_fpu32.lib<i_div.obj>(.text)
		-l rts2800_fpu32.lib<i_mod.obj>(.text)
		-l rts2800_fpu32.lib<L_div.obj>(.text)
		-l rts2800_fpu32.lib<ll_div.obj>(.text)
		-l rts2800_fpu32.lib<UL_div.obj>(.text)
		-l rts2800_fpu32.lib<ULL_div.obj>(.text)
		-l rts2800_fpu32.lib<fs_div.obj>(.text)
		-l rts2800_fpu32.lib<fs_mod.obj>(.text)
		-l rts2800_fpu32.lib<fd_div.obj>(.text)
		-l rts2800_fpu32.lib<sin.obj>(.text)
		-l rts2800_fpu32.lib<cos.obj>(.text)
		/*-l rts2800_fpu32.lib<sqrt.obj>(.text)*/
		/*-l rts2800_fpu32.lib(.econst)*/
	/*	-l rts2800_fpu32.lib(.cinit)*/
		/*-l rts2800_fpu32.lib(.ebss)*/
	} 			   	LOAD = FLASHCD,
					RUN	= RAML_PROGRAM,
					LOAD_START(_rts2800_fpu32_LoadStart),
					LOAD_END(_rts2800_fpu32_LoadEnd),
					RUN_START(_rts2800_fpu32_RunStart),
					PAGE = 0

IQmath : LOAD = FLASHCD, PAGE = 0
		 RUN = RAML_PROGRAM,      PAGE = 0
		 LOAD_START(_IQ_secureRamFuncs_loadstart),
		 LOAD_END(_IQ_secureRamFuncs_loadend),
		 RUN_START(_IQ_secureRamFuncs_runstart)

   csmpasswds          : > PASSWORDS   PAGE = 0
   csm_rsvd            : > CSM_RSVD    PAGE = 0
   
   /* run all other netlib code from FLASH */
  /* .nettextfast : > FLASHCD, PAGE = 0
   .nettextslow : > FLASHCD, PAGE = 0
   .switch      : > FLASHCD, PAGE = 0

   .uartsect      : > FLASHCD, PAGE = 0
   .commonsect    : > FLASHCD, PAGE = 0
   .cprintfsect   : > FLASHCD, PAGE = 0
   */

   .koeff_memory	   : > KOEFF_MEMORY			PAGE = 1
   
   .cinit              : > FLASHCD      		PAGE = 0			/* значения для инициализации глобальных и статических переменных */
   .text               : > FLASHCD      		PAGE = 0			/* исполняемый код */
   .econst     		   : > FLASHCD,  			PAGE = 0			/* Константы */
   codestart           : > BEGIN       			PAGE = 0			/* точка входа программы*/
   .stack      		   : > RAMM1,    			PAGE = 1			/* Стек */
   .ebss       		   : > RAML_DATA,  			PAGE = 1			/* Глобальные и статические переменные */
   .esysmem   		   : > RAML_DATA,  			PAGE = 1			/* Динамическая память (heap) */
   .sysmem   		   : > RAML_DATA,  			PAGE = 1

   
   /* Allocate IQ math areas: */
   IQmath           : > RAML_PROGRAM,     PAGE = 0
   IQmathTables     : > IQTABLES,    PAGE = 0, TYPE = NOLOAD
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD 
   
   /* .reset is a standard section used by the compiler.  It contains the */ 
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */ 
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS     PAGE = 0, TYPE = DSECT
  
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD

}
