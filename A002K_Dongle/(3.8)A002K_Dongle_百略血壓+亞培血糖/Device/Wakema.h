#ifndef WakemaLib
#define WakemaLib

extern void WriteTimeToTaiDoc();
extern void ReadTaiDocData(unsigned long *EnTime,unsigned long *Data);
extern void ClearTaiDocFlash();
extern void ProcessTiDocData(unsigned char Rx);
#endif