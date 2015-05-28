#ifndef AbbottLib
#define AbbottLib

#define AbbottBufLen  200

extern void ReadAbbottDataMulti(unsigned long long *D1,unsigned long long *D2,unsigned long long *D3,unsigned long long *D4);
extern void ReadAbbottData(unsigned long *EnTime,unsigned long *Data);
extern void ClearAbbottFlash();
extern void WriteTimeToAbbott();
extern void ProcessAbbottData(unsigned char Rx);

#endif
