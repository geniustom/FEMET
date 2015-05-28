#include "Wakema.h"
#include "../Driver/Driver.h"

const unsigned char TCMD_GetHealthData[8]={0x51,0x26,0x00,0x00,0x00,0x00,0xA3,0x1A};
const unsigned char TCMD_GetHealthTime[8]={0x51,0x25,0x00,0x00,0x00,0x00,0xA3,0x19};
const unsigned char TCMD_ClearAllData [8]={0x51,0x52,0x00,0x00,0x00,0x00,0xA3,0x46};


unsigned char TiDocBuf[10];
unsigned char TiDocCTIData[14];
unsigned char TiDocBufIndex=0;

void ProcessTiDocData(unsigned char Rx){
  TiDocBuf[TiDocBufIndex]=Rx;
  TiDocBufIndex++;
  TiDocBufIndex%=8;
  //===========================因為此版為共用，所以暫時這樣用
  //ProcessFEMETCMD(Rx);
}


void ClearTaiDocBuffer(){
  for(int i=0;i<10;i++){
    TiDocBuf[i]=0;
  }
  TiDocBufIndex=0;
}

void SendTiDocCMD(unsigned char const *SBUF,unsigned int length){
  ClearTaiDocBuffer();
  for (long i=0;i<length;i++){
    SentByteToMuxUart(WakemaUart,SBUF[i]);
  }
}

void ReadTaiDocData(unsigned long *EnTime,unsigned long *Data){
//========================取出資料====================
  SendTiDocCMD(TCMD_GetHealthData,8);
  Delayms(50);
  
  unsigned char CHKSUM=0;
  unsigned long HealthData=0;
  for(int i=0;i<7;i++){
    CHKSUM+=TiDocBuf[i];
  }
  if((CHKSUM==TiDocBuf[7])&&((TiDocBuf[2]!=0)||(TiDocBuf[3]!=0))){
    HealthData=(((unsigned long)TiDocBuf[3]*256+(unsigned long)TiDocBuf[2])*1000000)
                +((unsigned long)TiDocBuf[4]*1000)
                +((unsigned long)TiDocBuf[5]);
  }else{
    HealthData=0;
    EnTime=0;
    Data=0;
    return;    //若取不到資料，就不要浪費時間了
  }

//========================取出時間====================
  SendTiDocCMD(TCMD_GetHealthTime,8);
  Delayms(50);
  
  CHKSUM=0;
  unsigned long ETime=0;
  unsigned char Y,M,D,H,m;
  for(int i=0;i<7;i++){
    CHKSUM+=TiDocBuf[i];
  }
  if(CHKSUM==TiDocBuf[7]){
    ETime=TiDocBuf[3]*256+TiDocBuf[2];
    Y=(ETime/512)%100;
    M=(ETime/32)%16;
    D=ETime%32;
    m=TiDocBuf[4]%64;
    H=TiDocBuf[5]%32;
  }else{
    ETime=0;
    return;
  }
//========================輸出========================
  *Data=HealthData;
  *EnTime=EncodeDateTime(Y,M,D,H,m);
}


void WriteTimeToTaiDoc(){
  unsigned int EncodeDate=0;
  unsigned char TCMD_SetNowTime[8]={0x51,0x33,0x00,0x00,0x00,0x00,0xA3,0x00};

  EncodeDate=(unsigned int)(SystemDateTime.Day)+
             ((unsigned int)(SystemDateTime.Month)*32)+
             ((unsigned int)(SystemDateTime.Year)*512);
  TCMD_SetNowTime[2]=EncodeDate&0xff;
  TCMD_SetNowTime[3]=EncodeDate>>8;  
  TCMD_SetNowTime[4]=SystemDateTime.Minute;
  TCMD_SetNowTime[5]=SystemDateTime.Hour; 
  unsigned int CheckSum=0;
  for (long i=0;i<7;i++){
    CheckSum+=TCMD_SetNowTime[i];
  }
  TCMD_SetNowTime[7]=(unsigned char)(CheckSum&0xff);
  SendTiDocCMD(TCMD_SetNowTime,8);
}



void ClearTaiDocFlash(){
    SendTiDocCMD(TCMD_ClearAllData,8);
}

