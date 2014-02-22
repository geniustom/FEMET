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
  if(NowIsAlarm==0){  //�x������..�^��ݾ��Ҧ�
    DriverFlag.CancelPress=0;    //�n������s�_��A�_�h�^��STANDBY��|�bĲ�o�@��
    //BuzzerBeep(100);
    GoToFlow(State_NormalStandBy);
  }
}