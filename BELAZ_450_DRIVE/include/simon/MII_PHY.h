void WriteToPhyReg (char RegNo,int Data);
int ReadFromPhyReg (char RegNo);
int ReadMDI();
void delay(unsigned long int k);
void delay_ms(unsigned long int k);

void  WriteOne();
void  WriteZero();

/** Запись в регистр Ethernet кодовой последовательности
("0", "1", "Turnaround")
@param code Начало кодовой последовательности
@see #CODE_0, #CODE_1, #CODE_TURNAROUND
*/
void WriteCode(int code); 

/** @def CODE_TURNAROUND 
Начало кодовой последовательности "Turnaround"
*/
#define CODE_TURNAROUND	0x3330

/** @def CODE_0 
Начало кодовой последовательности "0"
*/
#define CODE_0 			0x3338

/** @def CODE_1 
Начало кодовой последовательности "1"
*/
#define CODE_1 			0x3339

/** @def WriteZero()
Запись в регистр Ethernet кодовой последовательности "0"
@see #WriteCode()
*/
#define WriteZero()	WriteCode(CODE_0)

/** @def WriteOne()
Запись в регистр Ethernet кодовой последовательности "1"
@see #WriteCode()
*/
#define WriteOne()	WriteCode(CODE_1)


/**************************************************************************/
/*Запись в регистры PHY*/ 
/**************************************************************************/

/** Запись в регистр Ethernet
@param RegNo адрес
@param Data данные
*/
void WriteToPhyReg (char RegNo,int Data);

/** Декодирование одного бита входного кода Ethernet
@return Полученный бит: 0 или 1
*/
int ReadMDI();

/** Чтение из регистра Ethernet
@param RegNo адрес
@return данные
*/
int ReadFromPhyReg (char RegNo);

/** Программная задержка
@param k Число циклов
*/ 
void delay(unsigned long int k);

/** Запись в регистр Ethernet кодовой последовательности
("0", "1", "Turnaround")
@param code Начало кодовой последовательности
@see #CODE_0, #CODE_1, #CODE_TURNAROUND
*/
void WriteCode(int code);

