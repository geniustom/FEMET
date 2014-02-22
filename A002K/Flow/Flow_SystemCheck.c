#include "../TaipeiCity_A002_L.h"

unsigned char NowIsSystemCheck=0;

void SystemCheck_Enter(){
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.SpeakState=0;
  DriverFlag.TentelOn=0; //關閉國揚話機以便線路偵測
  Tentel_HangUp();
}

void SystemCheck_Exit(){
  Tentel_HangUp();
  DriverFlag.TentelOn=0; //關閉國揚話機以便線路偵測
}

void CheckRFBTtoLED(){
  //=====================================================壓扣電池
  unsigned RFBTLow=0;
  for(int i=0;i<8;i++){
    RFBTLow+=RF.RFBtIsLow[i];
  }
  if(RFBTLow==0){
    SetLEDState(&LED_RFBT,0,0);     //有電恆滅
  }else{
    SetLEDState(&LED_RFBT,50,0);     //沒電恆亮
  }
}

void SystemCheck_Work(){
  //=====================================================外接電源
  if(DriverFlag.ACState==0){
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayPowerErr,EncodeNowDateTime(),0);
  }else{
  }
  //=====================================================主機電池
  if(DriverFlag.BTState==0){
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayBTLow,EncodeNowDateTime(),0);
  }else{
  }
  //=====================================================線路檢測
  if(CheckLineIsOK()==1){
  }else{
    //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayLineErr,EncodeNowDateTime(),0);
    BuzzerBeep(100);
    Delayms(100);
    BuzzerBeep(100);
  }
  //====================================================若QUEUE已滿直接啟動呼叫
  if(CTIMSGQueue.Length==CTIMessageQueueLength){
    //DriverFlag.KeepAllAlarm=1;   //QUEUE滿不叫
    SetLEDState(&LED_NowIsHelp,500,0);
    DriverFlag.NeedReport=1; //主機需要撥號  (值接跳到STARTLINE有問題..要先回到帶機模式在檢察)
  }
  //====================================================  
  if((QueueNeedSendImportantData()==1)||NeedRemoteSetup==1){  //檢查後，若有重要的事，或是剛剛遠端設定失敗，就啟動傳輸
    DriverFlag.NeedReport=1; //主機需要撥號  (值接跳到STARTLINE有問題..要先回到帶機模式在檢察)
  }
  GoToFlow(State_NormalStandBy);
}