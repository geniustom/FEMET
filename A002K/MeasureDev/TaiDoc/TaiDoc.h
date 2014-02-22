#ifndef TaiDocLib
#define TaiDocLib

#include "../../TaipeiCity_A002_L.h"

//#define TaiDocPort  COM3  //Lª©
#define TaiDocPort  COM1  //°ê¦rª©,¥«©²ª©

extern void WriteTimeToTaiDoc();
extern void ReadTaiDocData(unsigned long *EnTime,unsigned long *Data);
extern void ClearTaiDocFlash();
extern void ProcessTiDocData(unsigned char Rx);
#endif