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
  //WDTCTL = WDT_MDLY_8;                  //XT2�Y�O8M�A�hWDT��n�C1ms���_�@��
  WDTCTL = WDT_MDLY_32;
  SFRIE1 |= WDTIE;                         // Enable WDT interrupt
}

void Delayms(unsigned long ms){
  unsigned long NowmSec=msecCounter; 
  while((msecCounter<=(NowmSec+ms))){
    ReportWDT();
    _NOP();
    if(DriverFlag.CancelPress==1){
      return;
    }     
    if((DriverFlag.CancelLongPress==1)&&(DriverFlag.RDMode==0)){
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

void ReportWDT(){
  DriverFlag.WDTMonitorCounter=0;
}

void CheckAlive(int sec){
  //5000�O20��A1��O250
  if (DriverFlag.WDTMonitorCounter>=(sec*250)) {
    DriverFlag.WDTMonitorCounter=0;
    //ResetMCUByPMM();
    DriverFlag.BuzzerState=1;  //debug���q��buzzer�@���s�A����n�d���D
  }else{
    DriverFlag.WDTMonitorCounter++;
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
  CheckAlive(10);

  DriverFlag.NeedRoutin=1;
}
