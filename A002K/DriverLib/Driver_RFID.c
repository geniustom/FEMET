#include "DriverLib.h"

#define RFIDBUFLength   32


unsigned char RFIDBUF[RFIDBUFLength];
unsigned int RFIDBUFIndex;
unsigned char CMDState;
unsigned long StartTime;

const unsigned char CMD1[1]={0x55};
const unsigned char CMD2[5]={0x05,0x09,0x00,0x0E,0x00};
const unsigned char CMD3[1]={0x5A};


unsigned long GetRFIDNumber(){
  unsigned long Num;
  //RFID位置從RFIDBUF[14~18]
  Num=(unsigned long)RFIDBUF[15] * 256 * 256 * 256
     +(unsigned long)RFIDBUF[16] * 256 * 256
     +(unsigned long)RFIDBUF[17] * 256 
     +(unsigned long)RFIDBUF[18];
  
  return Num;
}

void ClearRFIDBUF(){
  for(int i=0;i<RFIDBUFLength;i++){
    RFIDBUF[i]=0x00;
  }
  RFIDBUFIndex=0;
  CMDState=0;
}

void ProcessRFIDCMD(unsigned char BUF){
  RFIDBUF[RFIDBUFIndex]=BUF;
  RFIDBUFIndex++;  
}


void InitRFID(){
  OpenUart(COM0,9600,ProcessRFIDCMD);  //出貨版才能用
  RFIDBUFIndex=0;
  DriverFlag.RFIDCardDetect=0;
}

void ReadRFID(){

  if(CMDState==0){
    SendTextToUart(COM0,CMD1,1);
    Delayms(40);
    SendTextToUart(COM0,CMD2,5);
    Delayms(80);
    SendTextToUart(COM0,CMD3,1);
    CMDState=2;
    StartTime=msecCounter;
  }

  //=====判定為有讀到卡號=====
  if ((CMDState==2)&&(RFIDBUFIndex==26)&&((RFIDBUF[2]==0x18)||(RFIDBUF[3]==0x09))){
    DriverFlag.RFIDCardNumber=GetRFIDNumber();
    DriverFlag.RFIDCardDetect=1;
    ClearRFIDBUF();
  }

  //=====判定為沒讀到卡號=====
  if ((CMDState==2)&&(RFIDBUFIndex>3)&&(RFIDBUF[2]==0x06)){
    DriverFlag.RFIDCardNumber=0;
    DriverFlag.RFIDCardDetect=0; 
    ClearRFIDBUF();  
  }    
  
  //=====判定為Timeout=====
  if (msecCounter-StartTime>500){ 
    ClearRFIDBUF();
  }

}
                           
                           
                           