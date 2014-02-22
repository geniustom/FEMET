#include "../TaipeiCity_A002_L.h"


unsigned char ServiceCallIndex;  //目前的客服撥號組別

unsigned char PhoneIsPickup(){
  if ((P2IN&BIT6)!=0) 
    return  0;  //拿起H，回傳0
  else
    return  1;   //放下L，回傳1
}

void Service_CallOut(){
  //==============================================設定總機前置撥號
  if(SystemConfig_CTINeedPreKey==1){      
    for(int kk=0;kk<8;kk++){
      if(SystemConfig_CTIPreKey[kk]==0xff)break;
      Tentel_SendKey(SystemConfig_CTIPreKey[kk]);
      //Tentel_SendDTMF(SystemConfig_CTIPreKey[kk]); <--無法撥碼
      Delayms(150);
    }
    Delayms(1500);
  }
  //==============================================設定撥號組別
  unsigned char const *Num;
  switch(ServiceCallIndex){
    case 0: Num=SystemConfig_CTIHelpTel1; break;
    case 1: Num=SystemConfig_CTIHelpTel2; break;
    case 2: Num=SystemConfig_CTIHelpTel3; break;
    case 3: Num=SystemConfig_CTIHelpTel4; break;
  }
  //==============================================取得撥號碼數
  unsigned char CodeIndex=0;
  for (int i=0;i<16;i++){
    if(Num[i]!=0xff){ CodeIndex++;}
  }
  //==============================================撥出號碼
  Tentel_SetNumber(Num,CodeIndex);
  Delayms(150);
  Tentel_DialOut();
  //==============================================累計ServiceCallIndex
  ServiceCallIndex++;
  ServiceCallIndex%=4;
  Delayms(3500);
}


void Service_Enter(){
  SetLEDState(&LED_NowIsHelp,500,0);  //傳輸恆亮
  DriverFlag.Phone0Gateway1=0; //不搶電話線(與傳輸不同)
  DriverFlag.MicState=1;
  DriverFlag.PhoneBusy=0;
  DriverFlag.TentelOn=1;
  DriverFlag.CancelPress=0; //模擬的取消建把他復位
  Delayms(2000); //Delay 一秒才能將原本ALWAYS斷電的國洋版能夠正常接收CMD
}

void Service_Exit(){
  SetLEDState(&LED_NowIsHelp,0,0);  //傳輸恆滅
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.PhoneBusy=0;
  DriverFlag.TentelOn=0;
  Tentel_HangUp();
  Delayms(2000);
}

void Beep3TimesAndHangup(){  //嗶三聲
  Tentel_HangUp();
  DisableSpeaker();
  for (int i=0;i<3;i++){
    BuzzerBeep(50);
    Delayms(50);
  }
}

unsigned char PhoneIsTake(unsigned int Delay){
  unsigned char Result=0;
  for(int i=0;i<Delay;i+=100){
    Delayms(100);
    //==============================================檢查話筒是否掛好，若掛好才能撥出去，沒掛好嗶三聲
    if(PhoneIsPickup()!=0){
      Beep3TimesAndHangup();
      Result=1;
      break;
    }
  }
  return Result;
}

void Service_Work(){
  //==============================================若先前正在通訊，先將電話斷乾淨，等待一秒，一秒內檢查話筒是否拿起
  Tentel_HangUp();
  if(PhoneIsTake(1000)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================拿起話筒等待一秒，一秒內檢查話筒是否拿起
  GYTentel_State.DetDialTone=0;      //復位
  Tentel_PickUp();
  if(PhoneIsTake(1000)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================等待撥號音，若偵測不到撥號音，發出三聲嗶
  if ((GYTentel_State.DetDialTone==1 || DriverFlag.NowIsDialTone==1)){
    GYTentel_State.DetDialTone=0;   //復位
  }else{
    Beep3TimesAndHangup();
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================開啟喇叭,等待0.5秒，0.5秒內檢查話筒是否拿起
  EnableSpeaker(SystemConfig_SPK_Dial);
  if(PhoneIsTake(500)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================若等到了才撥號
  Service_CallOut();
  EnableSpeaker(SystemConfig_SPK_Talk);
  
  unsigned char PhoneAlreadyPickup; //偵測在撥號前，話桶是否已經拿起
  unsigned char DTMFData;           //偵測對方是否送出*或#
  GYTentel_State.ISBusy=0;          //先關閉先前國洋輸出的BUSY CMD
  while((DriverFlag.CancelPress==0)||(DriverFlag.PhoneBusy==1)){
    //============================================================================偵測是否按下* (開起喇叭)
    DTMFData=Tentel_GetDTMFDigi();
    if(DTMFData==0xfa){ //*
      AddVoice();
      DriverFlag.MicState=1;
    }
    //============================================================================偵測話筒按下# (關閉喇叭)
    if(DTMFData==0xf3){ //#
      SubVoice();
      DriverFlag.MicState=1;
    }
    //============================================================================偵測話筒是否在撥號後才拿起，若是，關閉MIC與SPK，以及國洋話機
    if(PhoneIsPickup()==1&&PhoneAlreadyPickup==0){
      Tentel_HangUp();
      DisableSpeaker();
      DriverFlag.MicState=0;    
    }
    //============================================================================偵測話筒是否拿起
    PhoneAlreadyPickup=PhoneIsPickup(); //偵測在撥號前，話桶是否已經拿起
    Delayms(50);  //等待50ms
    //============================================================================偵測話筒是否放下
    if(PhoneAlreadyPickup==1&&PhoneIsPickup()==0){ //代表拿起又放下,自動掛斷回到代機狀態
       break;
    }
    //============================================================================L板忙線偵測
    if(DriverFlag.PhoneBusy==1){
      DriverFlag.PhoneBusy=0;
      break;
    }
    //============================================================================國洋忙線偵測
    if(GYTentel_State.ISBusy==1){
      GYTentel_State.ISBusy=0;
      break;
    }
  }
  
  Tentel_HangUp();
  DisableSpeaker();
  BuzzerBeep(100);
  GoToFlow(State_NormalStandBy);
}