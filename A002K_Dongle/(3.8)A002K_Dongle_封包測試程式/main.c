#include "Driver/Driver.h"
#include "Device/MicroLife.h"
#include "Device/Abbott.h"

unsigned long EnTime;
unsigned long EData;
unsigned long long WD1,WD2,WD3,WD4;
unsigned char P2PRE;

void DetectDevice(){
  if(P2PRE!=(P2IN&(BIT0+BIT1))){
    asm("MOV 0xFFFE,PC");         //RESET
  }
  
  if((P2IN&BIT0)!=0){
    P3OUT&=~BIT6;
  }else{
    P3OUT|=BIT6;    
  }
  
  if((P2IN&BIT1)!=0){
    P3OUT&=~BIT7;
  }else{
    P3OUT|=BIT7;
  }  
}


void main( void ){
  InitCLK();
  InitMuxUart(MicroLifeUart,9600,&ProcessMicroLifeData,0);
  InitMuxUart(WakemaUart,19200,&ProcessAbbottData,0);
  InitMuxUart(GateWayUart,19200,&ProcessGateWayData,0);
  P3DIR=BIT0+BIT1+BIT6+BIT7;
  P3OUT&=~(BIT0+BIT1);
  P2DIR=0x00;
  P2PRE=P2IN&(BIT0+BIT1);
  while(1){
    DetectDevice();
    if(NeedTx==1){
      //unsigned long MData=0;
      //unsigned long WData=0;                //單筆時才用
      
      
      //ReadMicroLifeData(&EnTime,&MData);

      //WData=0;                              //單筆時才用
      //ReadAbbottData(&EnTime,&WData);       //單筆時才用
      //WD1=0;  WD2=0;  WD3=0;  WD4=0;
      //ReadAbbottDataMulti(&WD1,&WD2,&WD3,&WD4);
      
      
      //Delayms(50);
      //WriteTimeToMicroLife();
      //Delayms(50);
      //WriteTimeToAbbott();
      
      //Delayms(50);
      //SendMeasureData(MData,WData);         //單筆時才用
      SendMeasureDataMulti(120090060,111201102171200,222201102171200,333201102171200,444201102171200);
      NeedTx=0;
      asm("MOV 0xFFFE,PC");         //RESET
    }    
    if(NeedTx==2){
      Delayms(50);
      ClearMicroLifeFlash();
      Delayms(50);
      ClearAbbottFlash();
      Delayms(50);
      SentByteToMuxUart(GateWayUart,'O');
      Delayms(10);
      SentByteToMuxUart(GateWayUart,'K');
      ClearGatewayBuffer();
      NeedTx=0;
      asm("MOV 0xFFFE,PC");         //RESET
    }
    if(NeedTx==3){
      Delayms(50);
      unsigned char VerData[32]={0x00};
      VerData[0]=0xAA;
      VerData[1]=0x03;
      for(int i=0;i<30;i++){
        VerData[2+i]=DongleVER[i];
      }
      unsigned int CHKSUM=0;
      for(int i=0;i<31;i++){
        CHKSUM+=VerData[i];
      }
      VerData[31]=(unsigned char)(CHKSUM&0xff);
      for(int i=0;i<32;i++){
        Delayms(10);
        SentByteToMuxUart(GateWayUart,VerData[i]);
      }
      NeedTx=0;
      asm("MOV 0xFFFE,PC");         //RESET
    }
  }
}




/*
      //ShowDataToPC(MData,9);
      //ShowDataToPC(WData,3);

void ShowData(unsigned long Data,unsigned int len){
  P2DIR=0x0f;
  P2OUT=0x0A;
  if(Data==0)return;
  Delayms(1000);
  unsigned long Divide=100000000;
  for(int i=0;i<len;i++){
    P2OUT=0x0F;
    Delayms(250);
    P2OUT=(Data/Divide)%10;
    Divide/=10;
    Delayms(750);
  }
  Delayms(1000);
}
*/