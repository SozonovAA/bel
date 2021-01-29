void WriteToPhyReg (char RegNo,int Data);
int ReadFromPhyReg (char RegNo);
int ReadMDI();
void delay(unsigned long int k);
void delay_ms(unsigned long int k);

void  WriteOne();
void  WriteZero();

/** ������ � ������� Ethernet ������� ������������������
("0", "1", "Turnaround")
@param code ������ ������� ������������������
@see #CODE_0, #CODE_1, #CODE_TURNAROUND
*/
void WriteCode(int code); 

/** @def CODE_TURNAROUND 
������ ������� ������������������ "Turnaround"
*/
#define CODE_TURNAROUND	0x3330

/** @def CODE_0 
������ ������� ������������������ "0"
*/
#define CODE_0 			0x3338

/** @def CODE_1 
������ ������� ������������������ "1"
*/
#define CODE_1 			0x3339

/** @def WriteZero()
������ � ������� Ethernet ������� ������������������ "0"
@see #WriteCode()
*/
#define WriteZero()	WriteCode(CODE_0)

/** @def WriteOne()
������ � ������� Ethernet ������� ������������������ "1"
@see #WriteCode()
*/
#define WriteOne()	WriteCode(CODE_1)


/**************************************************************************/
/*������ � �������� PHY*/ 
/**************************************************************************/

/** ������ � ������� Ethernet
@param RegNo �����
@param Data ������
*/
void WriteToPhyReg (char RegNo,int Data);

/** ������������� ������ ���� �������� ���� Ethernet
@return ���������� ���: 0 ��� 1
*/
int ReadMDI();

/** ������ �� �������� Ethernet
@param RegNo �����
@return ������
*/
int ReadFromPhyReg (char RegNo);

/** ����������� ��������
@param k ����� ������
*/ 
void delay(unsigned long int k);

/** ������ � ������� Ethernet ������� ������������������
("0", "1", "Turnaround")
@param code ������ ������� ������������������
@see #CODE_0, #CODE_1, #CODE_TURNAROUND
*/
void WriteCode(int code);

