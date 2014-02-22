#ifndef MicroLifeLib
#define MicroLifeLib

#include "../../TaipeiCity_A002_L.h"

#define MicroLifePort  COM1  //°ê¦rª©,¥«©²ª©

extern void WriteTimeToMicroLife();
extern void ReadMicroLifeData(unsigned long *EnTime,unsigned long *Data);
extern void ClearMicroLifeFlash();
extern void ProcessMicroLifeData(unsigned char Rx);


extern unsigned char MicroLifeBuf[32];
extern unsigned char MicroLifeCTIData[14];
extern unsigned char MicroLifeBufIndex;

#endif