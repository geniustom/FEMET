#ifndef DongleLib
#define DongleLib

#include "../../TaipeiCity_A002_L.h"


#define DonglePort  COM1  //°ê¦rª©,¥«©²ª©

extern void ReadDongleData();
extern void ReadDongleVer();
extern void ClearDongleFlash();
extern void ProcessDongleData(unsigned char Rx);


extern unsigned char DongleBuf[64];
extern unsigned char DongleCTIData[14];
extern unsigned char DongleBufIndex;

#endif