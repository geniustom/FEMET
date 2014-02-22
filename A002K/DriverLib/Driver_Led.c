#include "DriverLib.h"

LED LEDList[6];

void InitLEDState(){
  unsigned char LEDType[6]={LED_AC,LED_DC,LED_RFLow,LED_Call,LED_LineErr,LED_CallErr};
  for(int i=0;i<6;i++){
    LEDList[i].LEDType=LEDType[i];
    LEDList[i].Darkms=0;
    LEDList[i].Lightms=0;
  }
}


void SetLEDState(LED *LEDA,unsigned int LightDealyms,unsigned int DarkDealyms){
  LEDA->Lightms=LightDealyms;
  LEDA->Darkms=DarkDealyms;
  LEDA->DelayLms=0;
  LEDA->DelayDms=0;
  LEDA->LEDEnable=0;
}

void ImmediatellySyncLED(){
  LED_Power.LEDEnable=(1-DriverFlag.ACState); //(ACState=0 輸出1,ACState=1 輸出0)
  LED_Power.Lightms=LED_Power.LEDEnable; 
  LED_LineError.LEDEnable=DriverFlag.LineIsErr;
  LED_LineError.Lightms=LED_LineError.LEDEnable; 
  LED_BT.LEDEnable=(1-DriverFlag.BTState);
  LED_BT.Lightms=LED_BT.LEDEnable;
  LED_Power.LEDEnable=DriverFlag.ACState;
  LED_Power.Lightms=LED_Power.LEDEnable;
}

void SyncLED(){
  ImmediatellySyncLED();
  for(int i=0;i<6;i++){
    if(LEDList[i].LEDEnable==1){LEDList[i].DelayLms+=4;}  //若目前LED為亮，則亮計時
    if(LEDList[i].LEDEnable==0){LEDList[i].DelayDms+=4;}  //若目前LED為暗，則暗計時
    if (LEDList[i].Lightms==0){  //亮0秒=LED暗
      LEDList[i].LEDEnable=0;
    }else if (LEDList[i].Darkms==0){ //若亮>0秒且暗=0秒則衡亮 
      LEDList[i].LEDEnable=1;
    }else if (LEDList[i].Lightms!=0&&LEDList[i].Darkms!=0){
      if(LEDList[i].DelayLms>=LEDList[i].Lightms){  //若亮夠了,停止計時與變暗
        LEDList[i].DelayLms=0;
        LEDList[i].LEDEnable=0;
      } 
      if(LEDList[i].DelayDms>=LEDList[i].Darkms){  //若暗夠了,停止計時與變亮
        LEDList[i].DelayDms=0;
        LEDList[i].LEDEnable=1;
      } 
    }
  }  
  
  unsigned char LEDOUT=P6OUT&&0xC0; //11000000
  for(int i=0;i<6;i++){
    LEDOUT|=LEDList[i].LEDEnable*LEDList[i].LEDType;
  }
  P6OUT=LEDOUT;
}