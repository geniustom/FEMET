#include "DriverLib.h"

/*
void main(){
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    StartXT1();
    SetSystemClock(SYSCLK_8MHZ);
    InitWDT();
    InitPort();
    InitLEDState();
    _EINT();
    
    SetLEDState(&LED_Power,50,50);
    SetLEDState(&LED_BT,100,100);
    SetLEDState(&LED_NowIsHelp,100,300);
    while(1){
      _NOP();
      Delayms(1000);
      BuzzerBeep(100);
      Delayms(1000);
      BuzzerRing();
      Delayms(1000);
      TelRing();
    }

}
*/