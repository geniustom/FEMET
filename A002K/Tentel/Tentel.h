#ifndef TentelLib
#define TentelLib

#include "RangBuffer.h"

typedef struct{
    unsigned char    RecvMode;
    unsigned char    DetDialTone;                         //DetDialTone=1 偵測到Dialtone時為1 
    unsigned char    ISAlive;                             //ISAlive=0 (送CMD有回應)電話線沒接 ISAlive=1 (送CMD有回應)電話線有接
    unsigned char    DetDTMF;                             //DetDTMF=1 偵測到撥號音為1
    unsigned char    RingCount;                           //電話響鈴聲數
    unsigned char    ISRing;                              //電話正在響
    unsigned char    ISOnline;                            //電話正在線上
    unsigned char    ISBusy;                              //偵測到忙音CMD
    unsigned char    LineIsOK;                            //電話有接線(話機可通訊)
    RANG_BUFFER      DTMFBuffer;                           //存放對方按下的撥號音
    
}Tentel_State;


extern Tentel_State GYTentel_State;

extern unsigned char Init_Tentel();
extern void Tentel_WriteDefault();
extern void Tentel_PickUp();
extern void Tentel_HangUp();
extern void Tentel_CloseSPK();
extern void Tentel_OpenSPK();
extern void Tentel_SendKey(unsigned char Digi);
extern void Tentel_SendDTMF(unsigned char Digi);
extern void Tentel_SetNumber(unsigned char const *NUM,unsigned char Length);
extern void Tentel_SendDTMFList(unsigned char *STR,unsigned long Length);
extern void Tentel_DialOut();
extern void Tentel_ClearDTMFBuf();
extern void Tentel_GetDefault();
extern void Tentel_DumpBuf2PC();

extern unsigned char Tentel_GetDTMFDigi();
//extern unsigned char CheckLineErr();
extern unsigned char CheckLineIsOK();

unsigned char GetDTMFString(unsigned int len);


extern unsigned char DTMFBUF[32];


#endif