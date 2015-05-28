#include "../Driver/Driver.h"


unsigned long long msecCounter;
unsigned long long secCounter;


void InitCLK(){

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  while(CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF){  
    _NOP();
  }   
  BCSCTL1 = CALBC1_16MHZ;//CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_16MHZ;//CALDCO_1MHZ;
  InitWDT();
}

void InitWDT(){
  msecCounter=0;
  //WDTCTL = WDT_MDLY_8;                  //XT2若是8M，則WDT剛好每1ms中斷一次
  WDTCTL = WDT_MDLY_32;
  IE1 |= WDTIE;                         // Enable WDT interrupt
}


void Delayms(unsigned long ms){
  unsigned long NowmSec=msecCounter; 
  while((msecCounter<=(NowmSec+ms))){
    _NOP();
  }
}


// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void){
  msecCounter+=2;
}
