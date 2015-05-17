#include "DriverLib.h"

AlarmSetting SystemAlarm;

#define EncodeMinute(H,M)   (unsigned long)((unsigned long)M + (unsigned long)H *60)%1440

void (*AlarmStartCallBackFP)(unsigned char AlarmID);  //回呼的FUNCTION POINT
void (*AlarmStopCallBackFP)();  //回呼的FUNCTION POINT

void ClearAlarmTable(){
  for(int i=0;i<180;i++){
    SystemAlarm.AlarmTable[i]=0;
  }
}

void SetAlarmTable(int index,unsigned char value){
  unsigned int  part=index >> 3;  //除8
  unsigned char bit;
  unsigned char offset=index%8;

  switch (offset) {
    case 0 : bit=BIT0;break;
    case 1 : bit=BIT1;break;
    case 2 : bit=BIT2;break;
    case 3 : bit=BIT3;break;
    case 4 : bit=BIT4;break;
    case 5 : bit=BIT5;break;
    case 6 : bit=BIT6;break;
    case 7 : bit=BIT7;break;
  }
  
  if (value==0) {
    SystemAlarm.AlarmTable[part]&=~bit;
  }else {
    SystemAlarm.AlarmTable[part]|=bit;
  }
}

unsigned char GetAlarmTable(int index){
  unsigned int  part=index >> 3;  //除8
  unsigned char bit;
  unsigned char offset=index%8;
  
  switch (offset) {
    case 0 : bit=BIT0;break;
    case 1 : bit=BIT1;break;
    case 2 : bit=BIT2;break;
    case 3 : bit=BIT3;break;
    case 4 : bit=BIT4;break;
    case 5 : bit=BIT5;break;
    case 6 : bit=BIT6;break;
    case 7 : bit=BIT7;break;
  }
  
  if ((SystemAlarm.AlarmTable[part]&bit)==0){
    return 0;
  }else{
    return 1;
  }
  
}


void InitAlarmTable(){
  unsigned long EncodeM;
  ClearAlarmTable();
  if(SystemAlarm.NO1_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO1_Hour,SystemAlarm.NO1_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO1_Contiune);i++){
      SetAlarmTable(i%1440,1);
    }
  }
  if(SystemAlarm.NO2_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO2_Hour,SystemAlarm.NO2_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO2_Contiune);i++){
      SetAlarmTable(i%1440,1);
    }
  }
  if(SystemAlarm.NO3_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO3_Hour,SystemAlarm.NO3_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO3_Contiune);i++){
      SetAlarmTable(i%1440,1);
    }
  }
  if(SystemAlarm.NO4_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO4_Hour,SystemAlarm.NO4_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO4_Contiune);i++){
      SetAlarmTable(i%1440,1);
    }
  }  
  
  SystemAlarm.AlarmStart[0]=EncodeMinute(SystemAlarm.NO1_Hour,SystemAlarm.NO1_Minute);
  SystemAlarm.AlarmStart[1]=EncodeMinute(SystemAlarm.NO2_Hour,SystemAlarm.NO2_Minute);
  SystemAlarm.AlarmStart[2]=EncodeMinute(SystemAlarm.NO3_Hour,SystemAlarm.NO3_Minute);
  SystemAlarm.AlarmStart[3]=EncodeMinute(SystemAlarm.NO4_Hour,SystemAlarm.NO4_Minute);
}

void InitAlarm(void (*AlarmStartCallBack)(unsigned char AlarmID),void (*AlarmStopCallBack)()){
  InitAlarmTable();
  AlarmStartCallBackFP=AlarmStartCallBack;
  AlarmStopCallBackFP=AlarmStopCallBack;
}

void StopAlarm(){
  SystemAlarm.RingISStart=0;
  SystemAlarm.CancelRing=0;
  SystemAlarm.AlarmTrigger[0]=0;
  SystemAlarm.AlarmTrigger[1]=0;
  SystemAlarm.AlarmTrigger[2]=0;
  SystemAlarm.AlarmTrigger[3]=0;
  if(AlarmStopCallBackFP!=0)AlarmStopCallBackFP();
}








void SyncAlarm(){   //每秒檢查一次

  if((SystemAlarm.CancelRing==1)&&(SystemAlarm.RingISStart==1)){        //鬧鈴時按了取消鍵
    StopAlarm();  
  }  
  
  if((SystemAlarm.SystemRingBack1==0)&&  //結束了都還沒按取消..呼叫回呼函式
     (SystemAlarm.SystemRingBack2==0)&&
     (SystemAlarm.SystemRingBack3==0)&&
     (SystemAlarm.SystemRingBack4==0)&&
     (SystemAlarm.CancelRing==0)&&
     (SystemAlarm.RingISStart==1)){
     StopAlarm();
  }
  
}

void CheckAlarm(){  //每10秒檢查一次
  unsigned long EncodeNow;
  
  if(SystemDateTime.Second%10!=0){  //每10秒檢查一次
    return;
  }
  
  EncodeNow=EncodeMinute(SystemDateTime.Hour,SystemDateTime.Minute)%1440;  //編碼目前的時間
  for(int i=0;i<4;i++){
    if((EncodeNow==SystemAlarm.AlarmStart[i])&&(SystemDateTime.Second==0)){
      SystemAlarm.AlarmTrigger[i]=1;
      SystemAlarm.RingISStart=1;
      if(AlarmStartCallBackFP!=0)AlarmStartCallBackFP(i);
    }
  }
  
  if((GetAlarmTable(EncodeNow)==1)&&(SystemAlarm.AlarmTrigger[0]==1)){  //第1組
    SystemAlarm.SystemRingBack1=1;
  }else{
    SystemAlarm.SystemRingBack1=0;
  }
  
  if((GetAlarmTable(EncodeNow)==1)&&(SystemAlarm.AlarmTrigger[1]==1)){  //第2組
    SystemAlarm.SystemRingBack2=1;
  }else{
    SystemAlarm.SystemRingBack2=0;
  }

  if((GetAlarmTable(EncodeNow)==1)&&(SystemAlarm.AlarmTrigger[2]==1)){  //第3組
    SystemAlarm.SystemRingBack3=1;
  }else{
    SystemAlarm.SystemRingBack3=0;
  }

  if((GetAlarmTable(EncodeNow)==1)&&(SystemAlarm.AlarmTrigger[3]==1)){  //第3組
    SystemAlarm.SystemRingBack4=1;
  }else{
    SystemAlarm.SystemRingBack4=0;
  }
  
}