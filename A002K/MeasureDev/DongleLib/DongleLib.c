#include "DongleLib.h"

unsigned char DongleBuf[64];
unsigned char DongleCTIData[14];
unsigned char DongleBufIndex;


void ClearDongleBuffer(){
  for(int i=0;i<64;i++){
    DongleBuf[i]=0;
  }
  DongleBufIndex=0;
}


void SendDongleCMD(unsigned char const *SBUF,unsigned int length){
  ClearDongleBuffer();
  for (long i=0;i<length;i++){
    SendByteToUart(DonglePort,SBUF[i]);
  }
  
  SendTextToUart(COM3,"MCU->DEV:",9);  //MCU傳資料給DEVICE
  for (long i=0;i<length;i++){
    SendByteToUart(COM3,SBUF[i]);
  }
}

void ReadDongleData(){
                               //  封包頭,年,月,日,時,分,CHK 
  unsigned char DCMD_GetData[8]={0x55,0x01,0x00,0x00,0x00,0x00,0x00,0x00};
  DCMD_GetData[2]=SystemDateTime.Year;
  DCMD_GetData[3]=SystemDateTime.Month;
  DCMD_GetData[4]=SystemDateTime.Day;
  DCMD_GetData[5]=SystemDateTime.Hour;
  DCMD_GetData[6]=SystemDateTime.Minute;
  
  for(int i=0;i<7;i++){
    DCMD_GetData[7]+=DCMD_GetData[i];
  }
  SendDongleCMD(DCMD_GetData,8);
}

void ReadDongleVer(){
                               //  封包頭,年,月,日,時,分,CHK 
  unsigned char DCMD_GetData[8]={0x55,0x03,0x00,0x00,0x00,0x00,0x00,0x00};
  DCMD_GetData[2]=SystemDateTime.Year;
  DCMD_GetData[3]=SystemDateTime.Month;
  DCMD_GetData[4]=SystemDateTime.Day;
  DCMD_GetData[5]=SystemDateTime.Hour;
  DCMD_GetData[6]=SystemDateTime.Minute;
  
  for(int i=0;i<7;i++){
    DCMD_GetData[7]+=DCMD_GetData[i];
  }
  SendDongleCMD(DCMD_GetData,8);  
}


void ClearDongleFlash(){
                               //  封包頭,年,月,日,時,分,CHK 
  unsigned char DCMD_EraseData[8]={0x55,0x02,0x00,0x00,0x00,0x00,0x00,0x00};
  DCMD_EraseData[2]=SystemDateTime.Year;
  DCMD_EraseData[3]=SystemDateTime.Month;
  DCMD_EraseData[4]=SystemDateTime.Day;
  DCMD_EraseData[5]=SystemDateTime.Hour;
  DCMD_EraseData[6]=SystemDateTime.Minute;
  
  for(int i=0;i<7;i++){
    DCMD_EraseData[7]+=DCMD_EraseData[i];
  }
  SendDongleCMD(DCMD_EraseData,8);
}


void ProcessDongleData(unsigned char Rx){
  DongleBuf[DongleBufIndex]=Rx;
  DongleBufIndex++;
  DongleBufIndex%=64;
}


