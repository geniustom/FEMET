#include "DriverLib.h"


void InitBuzzer(unsigned char BuzzerOn){
  DriverFlag.BuzzerOn=BuzzerOn;
  DriverFlag.BuzzerState=0;
}

void BuzzerBeep(unsigned long time){
      //----------¥s¤@Án--------
      DriverFlag.BuzzerState=0;
      Delayms(10);
      if(DriverFlag.KeepAllAlarm==0)DriverFlag.BuzzerState=1;
      Delayms(time);
      DriverFlag.BuzzerState=0;
      //------------------------
}

void BuzzerRing(){
      DriverFlag.BuzzerState=0;
      Delayms(10);
      for(int i=0;i<4;i++){
        if(DriverFlag.KeepAllAlarm==0)DriverFlag.BuzzerState=1;
        Delayms(60);
        DriverFlag.BuzzerState=0; 
        Delayms(60);
      } 
      Delayms(520);
}

void TelRing(){
      DriverFlag.BuzzerState=0;
      Delayms(25);
      for(int i=0;i<10;i++){
        if(DriverFlag.KeepAllAlarm==0)DriverFlag.BuzzerState=1;
        Delayms(25);
        DriverFlag.BuzzerState=0; 
        Delayms(25);
      } 
      //Delayms(100);
}