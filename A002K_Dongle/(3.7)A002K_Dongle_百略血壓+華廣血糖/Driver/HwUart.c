#include "../Driver/Driver.h"




void SetupHwUart(HW_Uart *HW_UartPort,unsigned long BD){
  unsigned long Modulation=(unsigned long)((unsigned long)16000000/(unsigned long)BD);
  IE2 &= ~UCA0RXIE;                          // Disable USCI_A0 RX interrupt
  P3SEL |= BIT4+BIT5;                             // P3->4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  //1M的時候是104->2,16M的時候是104->2*16=1667=0x0683
  UCA0BR0 = Modulation&0xff;                
  UCA0BR1 = Modulation>>8;                  
  
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

/*
void SentTextToHwUart(unsigned char *Data,unsigned int length){
  for(int i=0;i<length;i++){
    while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
    UCA0TXBUF =  Data[i];                    // TX -> RXed character
  }
}


void SentByteToHwUart(unsigned char Data){
  while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
  UCA0TXBUF =  Data;                    // TX -> RXed character
}
*/

void ResetHWUartBuf(HW_Uart *HW_UartPort){
  for(int i=0;i<HWUartBufLen;i++){
    HW_UartPort->HW_UartBUF[i]=0;
  }
  HW_UartPort->BufferIndex=0;
}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void){
  unsigned char Rx=UCA0RXBUF;
  ProcessHWUart(Rx);
}