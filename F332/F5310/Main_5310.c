#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Uart.h"
#include "F332_Lib.h"



void System_Init(void){
    // Stop WDT
    WDTCTL = WDTPW + WDTHOLD;
    // Basic GPIO initialization
    Board_init();
    DCOClk_init();
    
    F332_init();
    // Globally enable interrupts
    __enable_interrupt();
}





void main( void )
{
  System_Init();
  F332_PickUp();
  Delayms(2000);
  /*
    DTMF_Out('0');
    DTMF_Out('9');
    DTMF_Out('1');
    DTMF_Out('7');
    DTMF_Out('7');
    DTMF_Out('6');
    DTMF_Out('8');
    DTMF_Out('9');
    DTMF_Out('7');
    DTMF_Out('5');
  */
    //DTMF_OutList("0917768975",10);
  
  while(1){
    _NOP();
  }
}





