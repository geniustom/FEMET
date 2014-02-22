#include "../TaipeiCity_A002_L.h"


unsigned char NowIsAlarm=0;

void AlarmStart(unsigned char ID){
  NowIsAlarm=1;
}

void AlarmStop(){
  NowIsAlarm=0;
}

void Alarm_Enter(){
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.SpeakState=0;
  Tentel_HangUp();
}

void Alarm_Exit(){
  Tentel_HangUp();
}

void Alarm_Work(){
  if(NowIsAlarm==0){  //鬧鐘結束..回到待機模式
    DriverFlag.CancelPress=0;    //要把取消鈕復位，否則回到STANDBY後會在觸發一次
    //BuzzerBeep(100);
    GoToFlow(State_NormalStandBy);
  }
}