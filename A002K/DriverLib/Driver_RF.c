#include "DriverLib.h"

RFStruct RF;

void InitRF(void(*RFCallBack)(unsigned char ID)){
  P4OUT=0;
  RF.SwitchInterval=80;
  RF.RFCallBack=RFCallBack;
  for(int i=0;i<=7;i++){
    RF.RFBtIsLow[i]=0;
    if(RF.Code[i]>1023){ //>1023 壓扣不啟用
      RF.ISEnable[i]=0;  
    }else{
      RF.ISEnable[i]=1;
    }
  }
}

unsigned char ByteReverse(unsigned char Input){
  unsigned char Output=0;
  if((Input&BIT0)!=0) Output |=BIT7;
  if((Input&BIT1)!=0) Output |=BIT6;
  if((Input&BIT2)!=0) Output |=BIT5;
  if((Input&BIT3)!=0) Output |=BIT4;
  if((Input&BIT4)!=0) Output |=BIT3;
  if((Input&BIT5)!=0) Output |=BIT2;
  if((Input&BIT6)!=0) Output |=BIT1;
  if((Input&BIT7)!=0) Output |=BIT0;
  
  return Output;
}

void SwitchRFCode(){
  _DINT();  //不關中斷可能會跳號
  if((P1IN&DET_RF)==0){
    RF.LockKey=0;
  }
  if(RF.SwitchInterval==0) return;
  if(msecCounter%RF.SwitchInterval!=0) return;
  if(RF.LockKey==1)return;
  //===========================================RF有設定且時間到才做切換
  P4DIR=ByteReverse(RF.Code[RF.ScanIndex]>>2);
  RF.ScanIndex++;
  RF.ScanIndex%=8;
  _EINT();
}



void DetRF_VT(){
  DriverFlag.RFPress=0;
  for(int i=0;i<8;i++){
    if((RF.Code[i]==DriverFlag.RFIN_Code)&&(RF.ISEnable[i]==1)){
      DriverFlag.RFPress=i+1;
      RF.RFBtIsLow[i]=DriverFlag.RFBTIsErr;
    }
  }
  
  if(DriverFlag.RFPress!=0)RF.RFCallBack(DriverFlag.RFPress);
}