#include "hfa.h"
/*
 0x100000 - ADRESS OF BEGIN FRAM MEMORY

 0x40000 (262144dem) - FULL FRAM
 0x3F7A0 (260000dem) - ARRAYS MEMORY

 0x3F7A0/0x5=0xCB20 (52000dem ___520(lines)x100(vars)___)	- SIZE OF ONE ARRAY

 0x100000 1 array begin
 0x10CB20 2 array begin
 0x119640 3 array begin
 0x126160 4 array begin
 0x132C80 5 array begin
 0x13F7A0 archive

 0x13FB88


*/
/*
#define NUM_OF_VARIABLES 	100
#define LENGHT_ARRAY 	 	520
#define STEPS_AFTER_ALARM  	100  //steps after alarm
*/

#define WORK_ARRAY	1
#define ALARM_ARRAY	2

Uint16 *ptr_array_number = 		(void *)(0x1BD070);
Uint16 *otTimeptr = 		(void *)(0x1BD071);
Uint16 otTime=0;
//Uint16 *ptr_archive	= 			(void *)(0x13FF06);
//Uint16 *ptr_archive_number	= 	(void *)(0x13FF07);

//Uint16 vars[NUM_OF_VARIABLES];
int16 vars[NUM_OF_VARIABLES];

Uint16 array_step=0;
Uint16 array_number=0;

Uint16 archive_number=0;
Uint16 count_after_alarm=0;
Uint16 fault_event=0;
Uint16 test_array_count=0;

int16 empty_var=0;

void osc_var();
void write_array();
void CopyToFram();

#pragma CODE_SECTION(osc_var,"ramfuncs")
#pragma CODE_SECTION(write_array,"ramfuncs")
#pragma CODE_SECTION(CopyToFram,"ramfuncs")

double XX;

Uint16 ArInd=0;

Uint16 MaxAlarmNumber=5;

int ari=0,arj=0;

//int16 CUR_ARRAY[10][10];

struct SCUR_ARRAY{
	Uint16 NumOfVals;
	Uint16 NumOfRaws;
	Uint16 Time1;
	Uint16 Time2;
	Uint16 Time3;
	Uint16 ControllerType;
	Uint16 ArrayType;
	int16 A[LENGHT_ARRAY][NUM_OF_VARIABLES];
};

struct SCUR_ARRAY CUR_ARRAY;

#pragma DATA_SECTION(CUR_ARRAY,"array_sect")

struct sARCHIVE{
	Uint16 Time1;
	Uint16 Time2;
	Uint16 Time3;
	Uint16 ControllerType;
	Uint16 ArrayType;
	Uint16 F1;
	Uint16 F2;
	Uint16 FC;
	Uint16 FDINV;
	Uint16 FDCHP;
};

struct sARCHIVE ARCHIVE;

Uint16 *PtrKoeff;

#define MAX_NUM_OF_ALARM_ARRAYS	19

Uint32 AAMetaData[MAX_NUM_OF_ALARM_ARRAYS+1];
#pragma DATA_SECTION(AAMetaData,"AAMetaData")

Uint32 AlarmArrayNumber=0;
Uint16 MaxNumOfAlarmArrays=0;

Uint16 ArchiveNum=0;
Uint16 *ArchivePtr=0; //0x1bf3e9

void WriteArchive();

#pragma CODE_SECTION(WriteArchive,"ramfuncs")

void write_array()
{

	empty_var++;

	if(!hb.InitArray)
	{// однократно забиваем масив адресами, больше сюда не заходим

		CUR_ARRAY.NumOfVals = NUM_OF_VARIABLES;
		CUR_ARRAY.NumOfRaws = LENGHT_ARRAY;

#ifdef FLASH_RUN
		if(altera_regs.DIN.bit.BitPlace1)
		CUR_ARRAY.ControllerType = PK1;
		if(altera_regs.DIN.bit.BitPlace2)
		CUR_ARRAY.ControllerType = PK2;
		CUR_ARRAY.ArrayType = 1;
#endif

#ifdef TABLE_PK1_RUN
		CUR_ARRAY.ControllerType = PK1;
#endif

#ifdef TABLE_PK2_RUN
		CUR_ARRAY.ControllerType = PK2;
#endif

		InitAddrArray();
		SET(hb.InitArray);

		for(ari=0;ari<NUM_OF_VARIABLES;ari++)
			CUR_ARRAY.A[0][ari] = AddrArray[ari];

		array_step = 1;

		MaxNumOfAlarmArrays = (0x1BF000 - 0x140010)/( 0x7L + NUM_OF_VARIABLES*LENGHT_ARRAY);

	}

		for(ArInd=0;ArInd<NUM_OF_VARIABLES;ArInd++)
		{
			CUR_ARRAY.A[array_step][ArInd] = *(int16 *)AddrArray[ArInd];



			if(array_step < 50 && !ArInd)
				{
					PtrKoeff = &koeff.IFMAX + array_step-1;
					CUR_ARRAY.A[array_step][ArInd] = *PtrKoeff;//забиваем нулевой столбец статичной инфой
				}

		}

		CUR_ARRAY.A[0][0] = array_step;
		/*
		CUR_ARRAY[0][1] = time1;
		CUR_ARRAY[0][1] = time2;
		CUR_ARRAY[0][1] = time3;
		*/

		array_step++;

		if(array_step >= LENGHT_ARRAY)
		{
			array_step = 1;
		}

		//если идет скачивание, обнуляем новый запрос, чтоб не получить второй битый массив
		if(hb.LoadingProcess)
			UNSET(hb.alarm_flag);

		if(hb.alarm_flag)
		{
			count_after_alarm++;

			if(count_after_alarm == STEPS_AFTER_ALARM)
			{

				CUR_ARRAY.Time1 = (data_from_KK->time_and_date.year << 8) + data_from_KK->time_and_date.date;
				CUR_ARRAY.Time2 = (data_from_KK->time_and_date.month << 8) + data_from_KK->time_and_date.hours;
				CUR_ARRAY.Time3 = (data_from_KK->time_and_date.minutes << 8) + data_from_KK->time_and_date.seconds;

				array_step = 1;

				UNSET(hb.alarm_flag);

				CLEAR_COUNTER(count_after_alarm);

				//бит обнуляется, когда массив скачается
				SET(hb.LoadingProcess);

				// на время отладки алгоритма записи и скачивания
				//SET(hb.FaultEvent);

				if(hb.FaultEvent)
				{
					//SET(hb.CopyArrayToFram);
					SET(hb.CopyProcess);

					SET(hb.WriteArchive);
					WriteArchive();

					CUR_ARRAY.ArrayType = ALARM_ARRAY;

				}
				else CUR_ARRAY.ArrayType = WORK_ARRAY;

			}

		}
}

void CopyToFram()
{

	AAMetaData[AAMetaData[0]+1] = 0x140010 + ((0x7L + NUM_OF_VARIABLES*LENGHT_ARRAY)*(AAMetaData[0]));

	memcpy((void *)AAMetaData[AAMetaData[0]+1],&CUR_ARRAY,NUM_OF_VARIABLES*LENGHT_ARRAY+0x7L);

	AAMetaData[0]++;

	if(AAMetaData[0] >= MaxNumOfAlarmArrays)
	{
		AAMetaData[0] = 0;
	}

	UNSET(hb.CopyProcess);

}

void WriteArchive(){

	ArchivePtr = (void *)0x1bf3e9;

	if(*ArchivePtr >= 100) *ArchivePtr = 0;

	ArchiveNum = *ArchivePtr;

	ARCHIVE.Time1 = CUR_ARRAY.Time1;
	ARCHIVE.Time2 = CUR_ARRAY.Time2;
	ARCHIVE.Time3 = CUR_ARRAY.Time3;
	ARCHIVE.ArrayType = CUR_ARRAY.ArrayType;
	ARCHIVE.ControllerType = CUR_ARRAY.ControllerType;
	ARCHIVE.F1 = GS.FAULTS1.all;
	ARCHIVE.F2 = GS.FAULTS2.all;
	ARCHIVE.FC = GS.FAULTSC.all;
	ARCHIVE.FDINV = GS.FAULTSD_INV.all;
	ARCHIVE.FDCHP = GS.FAULTSD_CHOP.all;

	memcpy((void *)(0x1BF000 + ArchiveNum*10),&ARCHIVE,10);

	ArchiveNum++;

	*ArchivePtr = ArchiveNum;

	UNSET(hb.WriteArchive);

}








