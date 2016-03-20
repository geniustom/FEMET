#include "DriverLib.h"
#define ToneBufferLength 12
#define DetCount     6     //抓6聲
unsigned long BusyToneList[ToneBufferLength];
unsigned char BusyToneIndex=0;
unsigned long LastToneTime=0;

/*
原理:
忙音:500ms,掛斷音:250ms,催掛音:125ms
將資料右移5位等同於除32，相當於允許6%的誤差
忙音:15~16 掛斷音: 8 催掛音: 4
*/

unsigned long TempToneList[ToneBufferLength]; //重建一正向續列

/*
unsigned char DetBusy(){ // 2016/03/21 前較嚴謹的偵測
  
  for(int i=0;i<ToneBufferLength;i++)TempToneList[i]=0;
//==================================用一回合將續列由晚到早排列
  for(int i=0;i<ToneBufferLength;i++){
    unsigned char CycleIndex=(BusyToneIndex+ToneBufferLength-i-1)%ToneBufferLength;
    TempToneList[i]=BusyToneList[CycleIndex];
  }
//==================================用一回合比較完所有序列，不相同回0
  for(int i=0;i<DetCount;i++){
    if(TempToneList[i]!=TempToneList[0])
       return 0;
  }
//==================================最後一關，必須>=4且<=16
  if((TempToneList[0]>=4)&&(TempToneList[0]<=16)){  
    return 1;
  }else{
    return 0;
  }
}
*/

double dabs(double data){
  if (data>0){ 
    return data;
  }else{
    return -data;
  }
}

unsigned char DetBusy(){
  for(int i=0;i<ToneBufferLength;i++)TempToneList[i]=0;
//==================================先將續列由晚到早排列6個
  for(int i=0;i<ToneBufferLength;i++){
    unsigned char CycleIndex=(BusyToneIndex+ToneBufferLength-i-1)%ToneBufferLength;
    TempToneList[i]=BusyToneList[CycleIndex];
  }
//==================================第1,3,5 應相等 且第2,4,6應相等
  if ((TempToneList[0]!=TempToneList[2])||(TempToneList[2]!=TempToneList[4])) return 0;
  if ((TempToneList[1]!=TempToneList[3])||(TempToneList[3]!=TempToneList[5])) return 0;
//==================================1~6的平均與 1,3,5 & 2,4,6 不能相差太大  
  double avg=0;
  for(int i=0;i<DetCount;i++){
    avg+=TempToneList[i];
  }
  avg=avg/DetCount;
  for(int i=0;i<DetCount;i++){
    if (dabs(TempToneList[i]-avg)>1) return 0;
  }
//==================================最後一關，必須>=4且<=16
  if((TempToneList[0]>=4)&&(TempToneList[0]<=16)){  
    return 1;
  }else{
    return 0;
  }
}

void DetBusyLo(){
  BusyToneList[BusyToneIndex]=(msecCounter-LastToneTime)>>5;
  BusyToneIndex++;
  BusyToneIndex%=ToneBufferLength;
  LastToneTime=msecCounter;
  
  if(DetBusy()==1){
    DriverFlag.PhoneBusy=1;
  }
}

void DetBusyHi(){
  BusyToneList[BusyToneIndex]=(msecCounter-LastToneTime)>>5;
  BusyToneIndex++;
  BusyToneIndex%=ToneBufferLength;
  LastToneTime=msecCounter;
  
  if(DetBusy()==1){
    DriverFlag.PhoneBusy=1;
  }
}