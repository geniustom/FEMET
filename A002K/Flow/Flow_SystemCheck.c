#include "../TaipeiCity_A002_L.h"

unsigned char NowIsSystemCheck=0;

void SystemCheck_Enter(){
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.SpeakState=0;
  DriverFlag.TentelOn=0; //�����괭�ܾ��H�K�u������
  Tentel_HangUp();
}

void SystemCheck_Exit(){
  Tentel_HangUp();
  DriverFlag.TentelOn=0; //�����괭�ܾ��H�K�u������
}

void CheckRFBTtoLED(){
  //=====================================================�����q��
  unsigned RFBTLow=0;
  for(int i=0;i<8;i++){
    RFBTLow+=RF.RFBtIsLow[i];
  }
  if(RFBTLow==0){
    SetLEDState(&LED_RFBT,0,0);     //���q���
  }else{
    SetLEDState(&LED_RFBT,50,0);     //�S�q��G
  }
}

void SystemCheck_Work(){
  //=====================================================�~���q��
  if(DriverFlag.ACState==0){
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayPowerErr,EncodeNowDateTime(),0);
  }else{
  }
  //=====================================================�D���q��
  if(DriverFlag.BTState==0){
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayBTLow,EncodeNowDateTime(),0);
  }else{
  }
  //=====================================================�u���˴�
  if(CheckLineIsOK()==1){
  }else{
    //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayLineErr,EncodeNowDateTime(),0);
    BuzzerBeep(100);
    Delayms(100);
    BuzzerBeep(100);
  }
  //====================================================�YQUEUE�w�������ҰʩI�s
  if(CTIMSGQueue.Length==CTIMessageQueueLength){
    //DriverFlag.KeepAllAlarm=1;   //QUEUE�����s
    SetLEDState(&LED_NowIsHelp,500,0);
    DriverFlag.NeedReport=1; //�D���ݭn����  (�ȱ�����STARTLINE�����D..�n���^��a���Ҧ��b�˹�)
  }
  //====================================================  
  if((QueueNeedSendImportantData()==1)||NeedRemoteSetup==1){  //�ˬd��A�Y�����n���ơA�άO��軷�ݳ]�w���ѡA�N�Ұʶǿ�
    DriverFlag.NeedReport=1; //�D���ݭn����  (�ȱ�����STARTLINE�����D..�n���^��a���Ҧ��b�˹�)
  }
  GoToFlow(State_NormalStandBy);
}