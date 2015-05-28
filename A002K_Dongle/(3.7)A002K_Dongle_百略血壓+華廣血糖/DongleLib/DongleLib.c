#include "../Driver/Driver.h"


#define GatewayBufLen   8 

unsigned char GatewayBUF[GatewayBufLen];
unsigned char GatewayBUFIndex;
unsigned int GatewayCHKSUM;
unsigned char NeedTx=0;
DateTime SystemDateTime;




void ClearGatewayBuffer(){
  for(int i=0;i<GatewayBufLen;i++){
    GatewayBUF[i]=0;
  }
  GatewayBUFIndex=0;
  GatewayCHKSUM=0;
  NeedTx=0;
}

void ProcessGateWayData(unsigned char Rx){
  if(NeedTx!=0)return;
  
  GatewayBUFIndex++;
//===========================================================================檢查第一個BYTE
  if((GatewayBUFIndex==1)){  //第一個BYTE是0x06才給過
    if(Rx!=0x55){
      ClearGatewayBuffer();
    }
  }  
//===========================================================================每個BYTE做加總
  if(GatewayBUFIndex<=8){
    GatewayBUF[GatewayBUFIndex-1]=Rx;
  }
//===========================================================================每個BYTE做加總
  if(GatewayBUFIndex==8){
    GatewayCHKSUM=0;
    for(int i=0;i<7;i++){
      GatewayCHKSUM+=GatewayBUF[i];
    }
    if(GatewayCHKSUM!=Rx){
      ClearGatewayBuffer();
    }else{
      SystemDateTime.Year=  GatewayBUF[2];
      SystemDateTime.Month= GatewayBUF[3];
      SystemDateTime.Day=   GatewayBUF[4];
      SystemDateTime.Hour=  GatewayBUF[5];
      SystemDateTime.Minute=GatewayBUF[6];
      NeedTx=GatewayBUF[1];
    }
  }
}


void SendMeasureData(unsigned long M,unsigned long W){
  // M:百略 W:華廣
  unsigned char ReturnBuf[17]={0xaa,0x01,
                               GatewayBUF[2],GatewayBUF[3],GatewayBUF[4],GatewayBUF[5],GatewayBUF[6],0x00,
                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                              };
  unsigned long SP,BP,HR,GL;
  SP=(M/1000000)%1000;
  BP=(M/1000)%1000;
  HR=M%1000;
  GL=(W/1000000)%1000;
  
  ReturnBuf[8]=GL/256;
  ReturnBuf[9]=GL%256;
  ReturnBuf[10]=SP/256;
  ReturnBuf[11]=SP%256;
  ReturnBuf[12]=BP/256;
  ReturnBuf[13]=BP%256;
  ReturnBuf[14]=HR/256;
  ReturnBuf[15]=HR%256;

  for(int i=0;i<16;i++){
    SentByteToMuxUart(GateWayUart,ReturnBuf[i]);
    Delayms(10);
    ReturnBuf[16]+=ReturnBuf[i];
  }
  SentByteToMuxUart(GateWayUart,ReturnBuf[16]);
  Delayms(10);
  ClearGatewayBuffer();
}






void ShowDataToPC(unsigned long Data,unsigned int len){
  if(Data==0)return;
  unsigned long Divide=100000000;
  unsigned char Digi[10]={'0','1','2','3','4','5','6','7','8','9'};
  for(int i=0;i<len;i++){
    SentByteToMuxUart(GateWayUart,Digi[(Data/Divide)%10]);
    Divide/=10;
  }
    SentByteToMuxUart(GateWayUart,13);
  SentByteToMuxUart(GateWayUart,10);
  Delayms(50);
}


unsigned long  EncodeDateTime(unsigned char EYear,unsigned char EMonth,unsigned char EDay,unsigned char EHour,unsigned char EMinute){
  unsigned long EncodeData=0;
  EncodeData=((unsigned long)EYear*13*32*24*60)+
             ((unsigned long)EMonth*32*24*60)+
             ((unsigned long)EDay*24*60)+  
             ((unsigned long)EHour*60)+  
             (unsigned long)EMinute;
  return EncodeData;
}

unsigned long  EncodeNowDateTime(){
  unsigned long EncodeData=0;
  EncodeData=((unsigned long)SystemDateTime.Year*13*32*24*60)+
             ((unsigned long)SystemDateTime.Month*32*24*60)+
             ((unsigned long)SystemDateTime.Day*24*60)+  
             ((unsigned long)SystemDateTime.Hour*60)+  
             (unsigned long)SystemDateTime.Minute;
  return EncodeData;
}