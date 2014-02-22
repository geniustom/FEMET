#include "MicroLife.h"


unsigned char MicroLifeBuf[32];
unsigned char MicroLifeCTIData[14];
unsigned char MicroLifeBufIndex=0;

const unsigned char MCMD_ClearAllData [4]={0x12,0x16,0x18,0x23};
const unsigned char MCMD_SetTime      [4]={0x12,0x16,0x18,0x27};
const unsigned char MCMD_GetHealthData[4]={0x12,0x16,0x18,0x28};


void ClearMicroLifeBuffer(){
  for(int i=0;i<32;i++){
    MicroLifeBuf[i]=0;
  }
  MicroLifeBufIndex=0;
}

void SendMicroLifeCMD(unsigned char const *SBUF,unsigned int length){
  ClearMicroLifeBuffer();
  for (long i=0;i<length;i++){
    Delayms(10);
    SendByteToUart(MicroLifePort,SBUF[i]);
  }
  
  SendTextToUart(COM3,"MCU->DEV:",9);  //MCU傳資料給DEVICE
  for (long i=0;i<length;i++){
    SendByteToUart(COM3,SBUF[i]);
  }
}


void ClearMicroLifeFlash(){
  for(int i=0;i<3;i++){
    Delayms(50);
    SendMicroLifeCMD(MCMD_ClearAllData,4);
  }
}


void WriteTimeToMicroLife(){
  unsigned long MEncodeDate=0;
  unsigned long MEncodeTime=0;
  unsigned int CheckSum=0;
  unsigned char MCMD_SetNowTime[16];

  MEncodeDate=(unsigned long)(SystemDateTime.Year)+
             ((unsigned long)(SystemDateTime.Day)*100)+
             ((unsigned long)(SystemDateTime.Month)*10000);
  MEncodeTime=(unsigned long)(SystemDateTime.Second)+
             ((unsigned long)(SystemDateTime.Minute)*100)+
             ((unsigned long)(SystemDateTime.Hour)*10000);
  
  
  for(int i=0;i<6;i++){
    MCMD_SetNowTime[6-i-1]=(unsigned char)((MEncodeDate % 10)+0x30);
    MEncodeDate=MEncodeDate/10;
  }
  
  MCMD_SetNowTime[6]=0x32;
  MCMD_SetNowTime[7]=0x30; 
  
  for (int i=13;i>7;i--){
    MCMD_SetNowTime[i]=(unsigned char)((MEncodeTime % 10)+0x30);
    MEncodeTime=MEncodeTime/10;
  }
  
  for(int i=0;i<14;i++){
    CheckSum+=MCMD_SetNowTime[i];
  }
  CheckSum=CheckSum%256;
  
  unsigned char HexWord[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  MCMD_SetNowTime[14]=HexWord[(CheckSum%16)];
  MCMD_SetNowTime[15]=HexWord[(CheckSum>>4)];
  
  SendMicroLifeCMD(MCMD_SetTime,4);
  SendMicroLifeCMD(MCMD_SetNowTime,16);
}

void ProcessMicroLifeData(unsigned char Rx){
  MicroLifeBuf[MicroLifeBufIndex]=Rx;
  MicroLifeBufIndex++;
  MicroLifeBufIndex%=32;
  //===========================因為此版為共用，所以暫時這樣用
  //ProcessFEMETCMD(Rx);
}



void ReadMicroLifeData(unsigned long *EnTime,unsigned long *Data){
  MicroLifeBufIndex=0;  //先清空BUFFER
  ClearMicroLifeBuffer();
//========================取出資料====================
 
  SendMicroLifeCMD(MCMD_GetHealthData,4);
  Delayms(100);
  
  unsigned long HealthData=0;
  HealthData=(((unsigned long)MicroLifeBuf[8])*1000000)
                +(((unsigned long)MicroLifeBuf[9])*1000)
                +((unsigned long)MicroLifeBuf[10]);
  
  SendTextToUart(COM3,"DEV->MCU:",9);  //DEVICE傳資料給MCU
  for (long i=0;i<22;i++){
    SendByteToUart(COM3,MicroLifeBuf[i]);
  }
//========================取出時間====================
  unsigned char Y,M,D,H,m;

  Y=(MicroLifeBuf[11]>>4)+(16*(MicroLifeBuf[14]>>7));
  M=MicroLifeBuf[11]%16;
  D=MicroLifeBuf[12]>>3;
  H=((MicroLifeBuf[12]%8)*4)+(MicroLifeBuf[13]>>6);
  m=MicroLifeBuf[13]%64;

//========================輸出========================
  *Data=HealthData;
  *EnTime=EncodeDateTime(Y,M,D,H,m);
}

