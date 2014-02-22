#ifndef TentelLib
#define TentelLib

#include "RangBuffer.h"

typedef struct{
    unsigned char    RecvMode;
    unsigned char    DetDialTone;                         //DetDialTone=1 ������Dialtone�ɬ�1 
    unsigned char    ISAlive;                             //ISAlive=0 (�eCMD���^��)�q�ܽu�S�� ISAlive=1 (�eCMD���^��)�q�ܽu����
    unsigned char    DetDTMF;                             //DetDTMF=1 �����켷������1
    unsigned char    RingCount;                           //�q���T�a�n��
    unsigned char    ISRing;                              //�q�ܥ��b�T
    unsigned char    ISOnline;                            //�q�ܥ��b�u�W
    unsigned char    ISBusy;                              //�����즣��CMD
    unsigned char    LineIsOK;                            //�q�ܦ����u(�ܾ��i�q�T)
    RANG_BUFFER      DTMFBuffer;                           //�s������U��������
    
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