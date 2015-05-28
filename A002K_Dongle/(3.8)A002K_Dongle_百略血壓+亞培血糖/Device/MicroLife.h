#ifndef MicroLifeLib
#define MicroLifeLib

#define MicroLifeBufLen     14
#define MicroLifeCTILen     14

extern void WriteTimeToMicroLife();
extern void ReadMicroLifeData(unsigned long *EnTime,unsigned long *Data);
extern void ClearMicroLifeFlash();
extern void ProcessMicroLifeData(unsigned char Rx);


extern unsigned char MicroLifeBuf[MicroLifeBufLen];
extern unsigned char MicroLifeCTIData[MicroLifeCTILen];
extern unsigned int MicroLifeBufIndex;
extern unsigned int MicroLifeDataIndex;
extern unsigned int MicroLifeRecordCount;

#endif