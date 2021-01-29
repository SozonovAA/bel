;// TI File $Revision: /main/1 $
;// Checkin $Date: August 18, 2006   13:45:55 $
;//###########################################################################
;//
;// FILE:  eZDSP2833x_CodeStartBranch.asm 
;//
;// TITLE: Branch for redirecting code execution after boot for eZdsp F28335. 
;// derived from DSP2833x_CodeStartBranch.asm
;//
;// For these examples, code_start is the first code that is executed after
;// exiting the boot ROM code. 
;//
;// The codestart section in the linker cmd file is used to physically place
;// this code at the correct memory location.  This section should be placed 
;// at the location the BOOT ROM will re-direct the code to.  For example, 
;// for boot to FLASH this code will be located at 0x3f7ff6. 
;//
;// In addition, the example DSP2833x projects are setup such that the codegen
;// entry point is also set to the code_start label.  This is done by linker 
;// option -e in the project build options.  When the debugger loads the code,
;// it will automatically set the PC to the "entry point" address indicated by
;// the -e linker option.  In this case the debugger is simply assigning the PC, 
;// it is not the same as a full reset of the device. 
;// 
;// The compiler may warn that the entry point for the project is other then
;//  _c_init00.  _c_init00 is the C environment setup and is run before 
;// main() is entered. The code_start code will re-direct the execution 
;// to _c_init00 and thus there is no worry and this warning can be ignored. 
;// 
;//###########################################################################
;// $TI Release: DSP2833x Header Files V1.02 $
;// $Release Date: October 5, 2007 $
;//###########################################################################


***********************************************************************

WD_DISABLE     .set    1  ;set to 1 to disable WD, else set to 0
INIT_XINTF16   .set    1  ;set to 1 to initialize XINTF to 16 bit, else set to 0
INIT_XINTF32   .set    0  ;set to 1 to initialize XINTF,to 32 bit, else set to 0

    .ref _c_int00
    .ref _InitSysCtrl
    .ref _InitXintf
    .ref _InitXintf16Gpio
    .ref _InitXintf32Gpio
    .global code_start
;    .def vers_prog

;	.sect "ver_prog"
;vers_prog:
;		.word 0ABCDh
***********************************************************************
* Function: codestart section
*
* Description: Branch to code starting point
***********************************************************************

    .sect "codestart"

code_start:
        LB pre_init       ;Branch to pre-initialization code

;end codestart section



***********************************************************************
* Function: wd_disable
*
* Description: Disables the watchdog timer
***********************************************************************
 .if WD_DISABLE == 1

    .text
wd_disable:
    EALLOW                ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6    ;Set data page for WDCR register
    MOV @7029h, #0068h    ;Set WDDIS bit in WDCR to disable WD
    EDIS                  ;Disable EALLOW protected register access
    LRETR
 .endif

;end wd_disable



***********************************************************************
* Function: pre_init
*
* Description: pre-initialization of the external interface
***********************************************************************

pre_init:
    SETC OBJMODE          ;Set OBJMODE for 28x object code
 .if WD_DISABLE == 1
        LCR wd_disable    ;Branch to watchdog disable code
 .endif
        
;    LCR _InitSysCtrl      ;PLL, WatchDog, enable Peripheral Clocks
;    LCR _InitXintf        ;Initialize XINTF
 .if INIT_XINTF16 == 1
;    LCR _InitXintf16Gpio  ;Configure the GPIO for XINTF with a 16-bit data bus
 .endif
 .if INIT_XINTF32 == 1
;    LCR _InitXintf32Gpio  ;Configure the GPIO for XINTF with a 32-bit data bus
 .endif
    
;    EALLOW                ;Enable EALLOW protected register access
;    MOVZ DP, #0b2eh>>6  
;    MOV @0b2eh, #9429h    ;set SRAM timing
;    RPT #7 || NOP
;    MOV @0b2fh, #03h      ;set SRAM timing
;    RPT #7 || NOP
;    EDIS                  ;Disable EALLOW protected register access
;    MOV   AL,#0000h
;    MOV   AH,#001h
;_DSP28x_CodeStartDelay:
;        SUB    ACC,#1
;        NOP
;        NOP
;        BF     _DSP28x_CodeStartDelay,GEQ    ;; Loop if ACC >= 0
    LB _c_int00           ;Branch to start of boot.asm in RTS library

;end pre_init



    .end
    
;//===========================================================================
;// End of file.
;//===========================================================================
