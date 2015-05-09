#include "DriverLib.h"


unsigned long long msecCounter;
unsigned long long secCounter;

void ResetMCUByPC(){
   asm("MOV 0xFFFE,PC");
}

void ResetMCUByPMM(){
  PMMCTL0 = PMMPW + PMMSWBOR + (PMMCTL0 & 0x0003); 
}

void ResetMCUByWDT(){
  WDTCTL = WDT_MRST_0_064; 
  while(1);
}

void InitWDT(){
  msecCounter=0;
  //WDTCTL = WDT_MDLY_8;                  //XT2若是8M，則WDT剛好每1ms中斷一次
  WDTCTL = WDT_MDLY_32;
  SFRIE1 |= WDTIE;                         // Enable WDT interrupt
}

void Delayms(unsigned long ms){
  unsigned long NowmSec=msecCounter; 
  while((msecCounter<=(NowmSec+ms))){
    _NOP();
    if(DriverFlag.CancelPress==1){
      return;
    }     
    if(DriverFlag.CancelLongPress==1){
      return;
    }
  }
}

void CountTimer(){
  msecCounter+=4;
  if(msecCounter%1000==0){
    secCounter++;
    Sync_Time();
    SyncAlarm();
    CheckAlarm();
  }
}


// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void){
  SyncLED();
  SwitchRFCode();
  CountTimer();
  SetPinSync(&DriverFlag);
  GetPinSync(&DriverFlag);
  
  DriverFlag.NeedRoutin=1;
}
