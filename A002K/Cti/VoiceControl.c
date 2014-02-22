#include "../TaipeiCity_A002_L.h"

void SetSpeakLevel(unsigned char Level){
    SetVoice(Level);
}

void AddVoice(){
  unsigned char Level=GetVoice();
  if (Level<7){
    Level+=1;
  }
  SetVoice(Level);
  Delayms(50);
}

void SubVoice(){
  unsigned char Level=GetVoice();
  if (Level>0){
    Level-=1;
  }
  SetVoice(Level);
  Delayms(50);
}

void EnableSpeaker(unsigned char Level){
  if(DriverFlag.KeepAllAlarm==0){
    DriverFlag.SpeakState=1;
    SetSpeakLevel(Level);
  }
  Delayms(50);
}

void DisableSpeaker(){
  DriverFlag.SpeakState=0;
  SetSpeakLevel(0);
  Delayms(50);
}