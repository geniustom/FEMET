#include "../Driver/Driver.h"
#include "Abbott.h"

//const unsigned char TCMD_GetHealthData[17]={0x02,0x31,0x47,0x45,0x54,0x5F,0x45,0x56,0x45,0x4E,0x54,0x53,0x03,0x34,0x38,0x0D,0x0A};
const unsigned char TCMD_GetHealthData[9]={'$','x','l','o','g',',','1',0x0D ,0x0A};
const unsigned char TCMD_ClearAllData1[9]={'$','c','o','l','z',',','1',0x0D ,0x0A};
const unsigned char TCMD_ClearAllData2[9]={'$','c','o','l','z',',','2',0x0D ,0x0A};
//const unsigned char TCMD_ENQ[1] = {0x05};
//const unsigned char TCMD_EOT[1] = {0x04};
//const unsigned char TCMD_ACK[1] = {0x06};


unsigned char AbbottBuf[AbbottBufLen];
unsigned char AbbottCTIData[14];
unsigned char AbbottBufIndex=0;

void ProcessAbbottData(unsigned char Rx){
  AbbottBuf[AbbottBufIndex]=Rx;
  //if(AbbottBufIndex<AbbottBufLen-1){
  //  AbbottBufIndex++;
  //}
  AbbottBufIndex++;
  AbbottBufIndex%=AbbottBufLen;  //避免BUFFER被塞滿..蓋掉原本的資料..所以不能這樣用
  
  //===========================因為此版為共用，所以暫時這樣用
  //ProcessFEMETCMD(Rx);
}

// $tim,02,07,12,14,24  //月,日,年,時,分
void WriteTimeToAbbott(){
  const unsigned char Digi[10]={'0','1','2','3','4','5','6','7','8','9'};
  unsigned char SteTimeCMD[21]={'$','t','i','m',',','0','0',',','0','0',',','0','0',',','0','0',',','0','0',0x0d,0x0a};
  SteTimeCMD[5]=Digi[(SystemDateTime.Month)/10];
  SteTimeCMD[6]=Digi[(SystemDateTime.Month)%10];
  
  SteTimeCMD[8]=Digi[(SystemDateTime.Day)/10];
  SteTimeCMD[9]=Digi[(SystemDateTime.Day)%10];
  
  SteTimeCMD[11]=Digi[(SystemDateTime.Year)/10];
  SteTimeCMD[12]=Digi[(SystemDateTime.Year)%10];
  
  SteTimeCMD[14]=Digi[(SystemDateTime.Hour)/10];
  SteTimeCMD[15]=Digi[(SystemDateTime.Hour)%10];
  
  SteTimeCMD[17]=Digi[(SystemDateTime.Minute)/10];
  SteTimeCMD[18]=Digi[(SystemDateTime.Minute)%10];
  
   for (long i=0;i<21;i++){
    SentByteToMuxUart(WakemaUart,SteTimeCMD[i]);
  }
}

void ClearAbbottBuffer(){
  for(int i=0;i<AbbottBufLen;i++){
    AbbottBuf[i]=0;
  }
  AbbottBufIndex=0;
}

void SendAbbottCMD(unsigned char const *SBUF,unsigned int length){
  ClearAbbottBuffer();
  for (long i=0;i<length;i++){
    SentByteToMuxUart(WakemaUart,SBUF[i]);
  }
}

void ReadAbbottData(unsigned long *EnTime,unsigned long *Data){
//========================取出資料====================
  Delayms(20);
  SendAbbottCMD(TCMD_GetHealthData,9);
  Delayms(200);

 
  unsigned long HealthData=0;

  if((AbbottBuf[44]==0x0d)&&(AbbottBuf[45]==0x0a)&&(AbbottBuf[21]==0x0d)&&(AbbottBuf[22]==0x0a)&&(AbbottBuf[76]==0x0d)&&(AbbottBuf[77]==0x0a)){
    HealthData=(AbbottBuf[46]-0x30)*100+(AbbottBuf[47]-0x30)*10+(AbbottBuf[48]-0x30);
    HealthData=HealthData*1000000;
  }else{
    HealthData=0;
    EnTime=0;
    Data=0;
    return;    //若取不到資料，就不要浪費時間了
  }

//========================輸出========================
  *Data=HealthData;
  *EnTime=EncodeNowDateTime();
}


unsigned long long GetAbbottDataDateTime(){
  unsigned long long YY,MM,DD,HH,NN,EnDateTime;
  unsigned char *MONTHData[13]={"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}; 
  unsigned char *StrM;
    
  for (int i=1;i<13;i++){
    StrM=MONTHData[i];
    if ((AbbottBuf[51]==StrM[0])&&(AbbottBuf[52]==StrM[1])&&(AbbottBuf[53]==StrM[2])){
      MM=i;
    }
  }
  
  YY=(AbbottBuf[61]-0x30)*10+(AbbottBuf[62]-0x30);
  DD=(AbbottBuf[56]-0x30)*10+(AbbottBuf[57]-0x30);
  HH=(AbbottBuf[64]-0x30)*10+(AbbottBuf[65]-0x30);
  NN=(AbbottBuf[67]-0x30)*10+(AbbottBuf[68]-0x30);
  
  EnDateTime=YY*100000000+
             MM*1000000+
             DD*10000+
             HH*100+
             NN*1;
  return EnDateTime;
}

void ReadAbbottDataMulti(unsigned long long *D1,unsigned long long *D2,unsigned long long *D3,unsigned long long *D4){
  unsigned char CMD_GetHealthData[9]={'$','x','l','o','g',',',0x30,0x0D ,0x0A};
  unsigned long long GL[4],GT[4];
//========================取出資料====================
  //Delayms(20);
  for (int i=0;i<4;i++){
    CMD_GetHealthData[6]=0x31+i;
    GL[i]=0;
    ClearAbbottBuffer();
    
    SendAbbottCMD(CMD_GetHealthData,9);
    Delayms(75);
    
    if((AbbottBuf[44]==0x0d)&&(AbbottBuf[45]==0x0a)&&
       (AbbottBuf[21]==0x0d)&&(AbbottBuf[22]==0x0a)&&
       (AbbottBuf[76]==0x0d)&&(AbbottBuf[77]==0x0a)&&
       (AbbottBuf[46]!='L')&&(AbbottBuf[47]!='o')&&
       (AbbottBuf[46]!='H')&&(AbbottBuf[47]!='i')){
      GL[i]=(AbbottBuf[46]-0x30)*100+(AbbottBuf[47]-0x30)*10+(AbbottBuf[48]-0x30);
      GT[i]=GetAbbottDataDateTime();
    }else{
      GL[i]=0;
      GT[i]=0;
    }
  }
  
  *D1=GL[0]*10000000000+GT[0];
  *D2=GL[1]*10000000000+GT[1];
  *D3=GL[2]*10000000000+GT[2];
  *D4=GL[3]*10000000000+GT[3];
}

void ClearAbbottFlash(){
  SendAbbottCMD(TCMD_ClearAllData1,9);
  Delayms(80);
  SendAbbottCMD(TCMD_ClearAllData2,9);
}

