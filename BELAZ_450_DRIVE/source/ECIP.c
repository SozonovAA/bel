/*
 *
 * 		ECIP.c
 * 		EtherCat Internal Protocol
 *
 */

#include "hfa.h"

#define RSRVD		0x0

#define MESS_1		0x0
#define MESS_2		0x1
#define MESS_3		0x2
#define MESS_4		0x3

#define LAST_MESS	0x3

sPK12 *ptrPK12;

void AssemblyECIPMess();

#pragma CODE_SECTION(AssemblyECIPMess,"ramfuncs")

int CountPK2=0;

int SendMessToKK=0;

Uint16 DFKK=0;//drive from KK

extern unsigned int ControllerID;

int Drive=0;
int Brake=0;

extern Uint16 ChopOpen;

void AssemblyECIPMess()
{

	DFKK = data_from_KK->DIN.all & 0x003F;

	Drive = data_from_KK->Drive;
	Brake = data_from_KK->Brake;


#ifdef MacroProj_PK12
/*
IdL[0]			IqL[0]			IdR[0]			IqR[0]
Ud[0]			Ugen[0]			Igen[0]			Iv[0]
RPM_GEN[0]		Alpha[0]		RPM_L[0]		RPM_R[0]
Rsrv			Rsrv			Faults1[0]		Faults2[0]
FaultsC[0]		FaultsD_INV[0]	FaultsD_CHOP[0]	DIN[0]
*/
	CountPK2++;

	if (ControllerID == PK1)
	ptrPK12 = &data_for_KK->PK_1;

	if (ControllerID == PK2)
	ptrPK12 = &data_for_KK->PK_2;

	if(ptrPK12->MessFlag == LAST_MESS)
	UNSET(ptrPK12->MessFlag);

	switch(ptrPK12->MessFlag)
	{

		case	MESS_1:

			ptrPK12->TxData[0] = /*CountPK2;*/IdL;
			ptrPK12->TxData[1] = IqL;
			ptrPK12->TxData[2] = IdR;
			ptrPK12->TxData[3] = IqR;
			ptrPK12->TxData[4] = Ud;
			ptrPK12->TxData[5] = Ugen;
			ptrPK12->TxData[6] = Igen;
			ptrPK12->TxData[7] = Iv;
			ptrPK12->TxData[8] = RPMDiz;
			ptrPK12->TxData[9] = alpha16;

			ptrPK12->MessFlag++;

			SendMessToKK++;

		break;

		case	MESS_2:

			ptrPK12->TxData[0] = /*CountPK2;*/SpeedL;
			ptrPK12->TxData[1] = SpeedR;
			ptrPK12->TxData[2] = st.LeftImp;;
			ptrPK12->TxData[3] = st.RightImp;
			ptrPK12->TxData[4] = GS.FAULTS1.all;
			ptrPK12->TxData[5] = GS.FAULTS2.all;
			ptrPK12->TxData[6] = GS.FAULTSC.all;
			ptrPK12->TxData[7] = GS.FAULTSD_INV.all;
			ptrPK12->TxData[8] = GS.FAULTSD_CHOP.all;
			ptrPK12->TxData[9] = altera_regs.DIN.all;//DIN

			ptrPK12->MessFlag++;

			SendMessToKK++;

		break;

		case	MESS_3:

			ptrPK12->TxData[0] = ChopOpen;
			ptrPK12->TxData[1] = Udz;
			ptrPK12->MessFlag++;

			SendMessToKK++;

		break;

	}

#endif

#ifdef MacroProj_PK3

	switch(data_for_KK->PK_3.MessFlag)
	{

		case	MESS_1:

				data_for_KK->PK_3.TxData[0] = Ifam;
				data_for_KK->PK_3.TxData[1] = RPM_COOLER;
				data_for_KK->PK_3.TxData[2] = cFaults;
				data_for_KK->PK_3.TxData[3] = cFaultsC;
				data_for_KK->PK_3.TxData[4] = cFaultsD_INV;
				data_for_KK->PK_3.TxData[5] = 0;
				data_for_KK->PK_3.TxData[6] = 0;
				data_for_KK->PK_3.TxData[7] = 0;
				data_for_KK->PK_3.TxData[8] = 0;
				data_for_KK->PK_3.TxData[9] = 0;

				UNSET(data_for_KK->PK_3.MessFlag);

		break;

	}
#endif

#ifdef MacroProj_PKT

	switch(data_for_KK->PK_3.MessFlag)
	{

		case	MESS_1:

				data_for_KK->PK_3.TxData[0] = Ifam;
				data_for_KK->PK_3.TxData[1] = RPM_COOLER;
				data_for_KK->PK_3.TxData[2] = cFaults;
				data_for_KK->PK_3.TxData[3] = cFaultsC;
				data_for_KK->PK_3.TxData[4] = cFaultsD_INV;
				data_for_KK->PK_3.TxData[5] = 0;
				data_for_KK->PK_3.TxData[6] = 0;
				data_for_KK->PK_3.TxData[7] = 0;
				data_for_KK->PK_3.TxData[8] = 0;
				data_for_KK->PK_3.TxData[9] = 0;

				UNSET(data_for_KK->PK_3.MessFlag);

		break;

	}
#endif
}
