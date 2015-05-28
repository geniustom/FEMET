#include "../Driver/Driver.h"


#define GatewayBufLen       8 
#define GatewayReturnLen    43 

unsigned char GatewayBUF[GatewayBufLen];
unsigned char ReturnBuf[GatewayReturnLen];
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
//===========================================================================�ˬd�Ĥ@��BYTE
  if((GatewayBUFIndex==1)){  //�Ĥ@��BYTE�O0x06�~���L
    if(Rx!=0x55){
      ClearGatewayBuffer();
    }
  }  
//===========================================================================�C��BYTE���[�`
  if(GatewayBUFIndex<=8){
    GatewayBUF[GatewayBUFIndex-1]=Rx;
  }
//===========================================================================�C��BYTE���[�`
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

//========================================================================�h���ǰe�O======================================
void SendMeasureDataMulti(unsigned long M,unsigned long long W1,unsigned long long W2,unsigned long long W3,unsigned long long W4){
  // M:�ʲ� W:�Ȱ�
  //W= GGGYYMMDDHHNN
  unsigned char TempBuf[43]={0xaa,0x01,                                                                     //HEADER  0~1
                               GatewayBUF[2],GatewayBUF[3],GatewayBUF[4],GatewayBUF[5],GatewayBUF[6],0x00,    //�ɶ�    2~7
                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,   //��}�@ : GLU(H),GLU(L),YY,MM,DD,HH,NN            8~14
                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,   //��}�G : GLU(H),GLU(L),YY,MM,DD,HH,NN            15~21
                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,   //��}�T : GLU(H),GLU(L),YY,MM,DD,HH,NN            22~28
                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,   //��}�| : GLU(H),GLU(L),YY,MM,DD,HH,NN            29~35
                               0x00,0x00,0x00,0x00,0x00,0x00,        //���� :   SP(H),SP(L),BP(H),BP(L),HR(H),HR(L)     36~41
                               0x00                                  //CHECKSUM                                         42
                              };
  for (int i=0;i<GatewayReturnLen;i++){
    ReturnBuf[i]=TempBuf[i];
  }
  
  unsigned long SP,BP,HR,CheckSum;
  unsigned long long GL[4],GT[4];
  SP=(M/1000000)%1000;
  BP=(M/1000)%1000;
  HR=M%1000;
  GL[0]=(W1/10000000000)%1000;
  GL[1]=(W2/10000000000)%1000;
  GL[2]=(W3/10000000000)%1000;
  GL[3]=(W4/10000000000)%1000;
  
  GT[0]=(W1%10000000000);
  GT[1]=(W2%10000000000);
  GT[2]=(W3%10000000000);
  GT[3]=(W4%10000000000);
  
  //========================��}========================
  for(int i=0;i<4;i++){
    ReturnBuf[8 +(i*7)]=GL[i]/256;
    ReturnBuf[9 +(i*7)]=GL[i]%256;
    ReturnBuf[10 +(i*7)]=(GT[i]/100000000)%100;   //�~
    ReturnBuf[11+(i*7)]=(GT[i]/1000000)%100;      //��
    ReturnBuf[12+(i*7)]=(GT[i]/10000)%100;        //��
    ReturnBuf[13+(i*7)]=(GT[i]/100)%100;          //��
    ReturnBuf[14+(i*7)]=(GT[i]/1)%100;            //��
  }
  //========================����========================
  ReturnBuf[36]=SP/256;
  ReturnBuf[37]=SP%256;
  ReturnBuf[38]=BP/256;
  ReturnBuf[39]=BP%256;
  ReturnBuf[40]=HR/256;
  ReturnBuf[41]=HR%256;

  CheckSum=0;
  for(int i=0;i<42;i++){
    SentByteToMuxUart(GateWayUart,ReturnBuf[i]);
    Delayms(10);
    CheckSum=CheckSum+ReturnBuf[i];
  }
  ReturnBuf[42]=CheckSum&0xff;
  
  if ((P2IN&BIT0)!=0x00){
    ReturnBuf[42]+=1;
    SentByteToMuxUart(GateWayUart,ReturnBuf[42]);   //HI �e��
  }else{   
    SentByteToMuxUart(GateWayUart,ReturnBuf[42]);   //LO �e��
  }  
  Delayms(10);
  ClearGatewayBuffer();
}
//========================================================================�h���ǰe�O======================================
//========================================================================�浧�ǰe�O======================================
void SendMeasureData(unsigned long M,unsigned long W){
  // M:�ʲ� W:�ؼs
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
//========================================================================�浧�ǰe�O======================================





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