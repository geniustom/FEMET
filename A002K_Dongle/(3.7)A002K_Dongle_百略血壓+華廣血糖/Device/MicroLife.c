#include "../Driver/Driver.h"
#include "MicroLife.h"


/********************************************************************************
1.第一個BYTE收到06
2.第二個BYTE收到筆數
3.從第三個BYTE開始，之後每7個BYTE分成一個PART
4.第一個PART=PART0，取byte0=N，代表還要往後收N個PART
5.PART1 ~ PARTN-1 =第1筆~第N-1筆資料
6.PARTN=前N筆的平均
7.最後一個BYTE=CHECKSUM=除了第一個06之外其他所有BYTE的總合在MOD256
********************************************************************************/


unsigned char MicroLifeBuf[MicroLifeBufLen];
unsigned char MicroLifeCTIData[MicroLifeCTILen];
unsigned int MicroLifeBufIndex=0;
unsigned int MicroLifeDataIndex=0;
unsigned int MicroLifeRecordCount=0;
unsigned int MicroLifeDataLimit=0;
unsigned char MicroLifeCheckSum=0;

const unsigned char MCMD_WakeUP       [5]={0x00,0x00,0x00,0x00,0x00};
const unsigned char MCMD_LinkBP       [4]={0x12,0x16,0x18,0x21};
const unsigned char MCMD_ClearAllData [8]={0x12,0x16,0x18,0x23,0x30,0x30,0x31,0x31};
const unsigned char MCMD_SetTime      [4]={0x12,0x16,0x18,0x27};
const unsigned char MCMD_GetHealthData[4]={0x12,0x16,0x18,0x28};

void ClearMicroLifeBuffer(){
  for(int i=0;i<MicroLifeBufLen;i++){
    MicroLifeBuf[i]=0;
  }
  MicroLifeBufIndex=0;
  MicroLifeDataIndex=0;
  MicroLifeRecordCount=0;
  MicroLifeCheckSum=0;
  MicroLifeDataLimit=0;
}

void SendMicroLifeCMD(unsigned char const *SBUF,unsigned int length){
  ClearMicroLifeBuffer();
  for (long i=0;i<length;i++){
    SentByteToMuxUart(MicroLifeUart,SBUF[i]);
  }
}


void ProcessMicroLifeData(unsigned char UartData){
  MicroLifeDataIndex++;
//===========================================================================檢查第一個BYTE
  if((MicroLifeDataIndex==1)){  //第一個BYTE是0x06才給過
    if(UartData!=0x06){
      ClearMicroLifeBuffer();
    }
    return;
  }
//===========================================================================檢查第二個BYTE(PAGE數)
  if(MicroLifeDataIndex==2){  //第一個BYTE是0x06才給過
    MicroLifeRecordCount=UartData;
    MicroLifeDataLimit=(MicroLifeRecordCount*7)+8;
    MicroLifeCheckSum=UartData;
    return;
  }
//===========================================================================累加CHECKSUM直到最後一個BYTE
  if((MicroLifeDataIndex>=3)&&(MicroLifeDataIndex<=MicroLifeDataLimit)){
    MicroLifeCheckSum+=UartData;
  }
//===========================================================================最後2個PAGE才開始存BUFFER
  if((MicroLifeDataIndex>(MicroLifeDataLimit-14))&&(MicroLifeDataIndex<=MicroLifeDataLimit)){  //CHECK SUM不丟入
    MicroLifeBuf[MicroLifeBufIndex]=UartData;
    MicroLifeBufIndex++;
    MicroLifeBufIndex%=MicroLifeBufLen;
  }
//===========================================================================檢查CHECKSUM
  if(MicroLifeDataIndex==MicroLifeDataLimit+1){   //若不相等..就全部清空
    if(UartData!=MicroLifeCheckSum){
      ClearMicroLifeBuffer();
    }
    //若check sum 檢查ok..則buf的內容中，前7個byte為最後一筆資料..後7個byte為平均值
    return;
  }
}



void ReadMicroLifeData(unsigned long *EnTime,unsigned long *Data){
  ClearMicroLifeBuffer();
  SendMicroLifeCMD(MCMD_WakeUP,5);
  Delayms(100);
  SendMicroLifeCMD(MCMD_LinkBP,4);
  Delayms(100);
//========================取出資料====================
  ClearMicroLifeBuffer(); 
  SendMicroLifeCMD(MCMD_GetHealthData,4);
  Delayms(40);                      //一開始30ms
  Delayms(MicroLifeRecordCount*16);  //依照資料筆數動態調整
  
  unsigned long HealthData=0;
  HealthData=(((unsigned long)MicroLifeBuf[0])*1000000)
                +(((unsigned long)MicroLifeBuf[1])*1000)
                +((unsigned long)MicroLifeBuf[2]);
  
//========================取出時間====================
  unsigned char Y,M,D,H,m;

  Y=(MicroLifeBuf[3]>>4)+(16*(MicroLifeBuf[6]>>7));
  M=MicroLifeBuf[3]%16;
  D=MicroLifeBuf[4]>>3;
  H=((MicroLifeBuf[4]%8)*4)+(MicroLifeBuf[5]>>6);
  m=MicroLifeBuf[5]%64;

//========================輸出========================
  *Data=HealthData;
  *EnTime=EncodeDateTime(Y,M,D,H,m);
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


void ClearMicroLifeFlash(){
  ClearMicroLifeBuffer();
  SendMicroLifeCMD(MCMD_WakeUP,5);
  Delayms(100);
  SendMicroLifeCMD(MCMD_LinkBP,4);
  Delayms(100);
//========================取出資料====================
  ClearMicroLifeBuffer(); 
  SendMicroLifeCMD(MCMD_ClearAllData,8);
}

