
/***************************************************************************//**
 * @file       HAL_Uart.c
 * @addtogroup Uart
 * @{
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "msp430.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_SDCard.h"
#include "HAL_Uart.h"


// Interface            
#define Uart_R0         UCA1BR0
#define Uart_R1         UCA1BR1
#define Uart_MCTL       UCA1MCTL
#define Uart_CTL0       UCA1CTL0
#define Uart_CTL1       UCA1CTL1   
#define Uart_TXBUF      UCA1TXBUF
#define Uart_RXBUF      UCA1RXBUF
   
#define MSP430Clock     25000000
void (*COM1CallBack)(char RX);  //回呼的FUNCTION POINT
void (*COM2CallBack)(char RX);  //回呼的FUNCTION POINT
  


/***************************************************************************//**
 * @brief   Set Baudrate
 * @param   None
 * @return  None
 ******************************************************************************/
void SetBaudrate(unsigned long SYSCLK,unsigned long Baudrate,
                 unsigned char volatile *R0,unsigned char volatile *R1,unsigned char volatile *UMCTL){
  if(SYSCLK==1048576){
    switch (Baudrate){
      case 1200:
        *R0=0x05; *R1=0x0D; *UMCTL=0x52; break;
      case 9600:
        *R0=0xA0; *R1=0x01; *UMCTL=0x5B; break;
      case 19200:
        *R0=0xD0; *R1=0x00; *UMCTL=0x11; break;
      case 57600:
        *R0=0x45; *R1=0x00; *UMCTL=0xAA; break;
      case 115200:
        *R0=0x09; *R1=0x00; *UMCTL=0x10; break;
    }
  }
  if(SYSCLK==4000000){
    switch (Baudrate){
      case 1200:
        *R0=0x05; *R1=0x0D; *UMCTL=0x52; break;
      case 9600:
        *R0=0xA0; *R1=0x01; *UMCTL=0x5B; break;
      case 19200:
        *R0=0xD0; *R1=0x00; *UMCTL=0x11; break;
      case 57600:
        *R0=0x45; *R1=0x00; *UMCTL=0xAA; break;
      case 115200:
        *R0=0x22; *R1=0x00; *UMCTL=0xDD; break;
    }
  }
  if(SYSCLK==8000000){
    switch (Baudrate){
      case 1200:
        *R1=0x1A; *R0=0x0A; *UMCTL=0x00; break;
      case 9600:
        *R1=0x03; *R0=0x41; *UMCTL=0x00; break;
      case 19200:
        *R1=0x01; *R0=0xA0; *UMCTL=0xC0; break;
      case 57600:
        *R1=0x00; *R0=0x8A; *UMCTL=0xDE; break;
      case 115200:
        *R1=0x00; *R0=0x45; *UMCTL=0x4A; break;
    }
  }
  if(SYSCLK==25000000){
    switch (Baudrate){
      case 1200:
        *R0=0x61; *R1=0x51; *UMCTL=0x52; break;
      case 9600: 
        *R0=0x2C; *R1=0x0A; *UMCTL=0x84; break;
      case 19200:
        *R0=0x16; *R1=0x05; *UMCTL=0x20; break;
      case 57600:
        *R0=0xB2; *R1=0x01; *UMCTL=0x00; break;
      case 115200:
        *R0=0xD9; *R1=0x00; *UMCTL=0x00; break;
    }
  }  
} 

void SetControlReg(unsigned char volatile *UCCTL1,unsigned char volatile *UCBR0,
                   unsigned char volatile *UCBR1,unsigned char volatile *UCMCTL,
                   unsigned char volatile *UCIE,unsigned long Baudrate)           {
  *UCCTL1 |= UCSWRST;
  *UCCTL1 |= UCSSEL_2;                     // CLK = ACLK
  SetBaudrate(MSP430Clock,Baudrate,UCBR0,UCBR1,UCMCTL);
  *UCCTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  *UCIE |= UCRXIE;                        // Enable USCI_A1 RX interrupt
}

   
void OpenUart(unsigned char Port,unsigned long Baudrate,void (*CallBackFunction)(char)){
  switch (Port){
    case 1:
      P3SEL |= BIT3 | BIT4;
      SetControlReg(&UCA0CTL1,&UCA0BR0,&UCA0BR1,&UCA0MCTL,&UCA0IE,Baudrate); 
      COM1CallBack=CallBackFunction;
      break;
    case 2:
      P4SEL |= BIT4 | BIT5;
      SetControlReg(&UCA1CTL1,&UCA1BR0,&UCA1BR1,&UCA1MCTL,&UCA1IE,Baudrate);
      COM2CallBack=CallBackFunction;
      break;
  }
}

void SendTextToUart(unsigned char Port,char *SBUF,unsigned int length){
  switch (Port){
    case 1:
      for (int i=0;i<length;i++){
        while (!(UCA0IFG&UCTXIFG));                                 // USART0 TX buffer ready?
        UCA0TXBUF = SBUF[i];
      }
      break;
    case 2:
      for (int i=0;i<length;i++){
        while (!(UCA1IFG&UCTXIFG));                                 // USART0 TX buffer ready?
        UCA1TXBUF = SBUF[i];
      }
      break;
  }
}

void SendByteToUart(unsigned char Port,unsigned char SBUF){
  switch (Port){
    case 1:
      while (!(UCA0IFG&UCTXIFG));                // USCI_A1 TX buffer ready?
      UCA0TXBUF = SBUF;                          // TX -> RXed character
      break;
    case 2:
      while (!(UCA1IFG&UCTXIFG));                // USCI_A1 TX buffer ready?
      UCA1TXBUF = SBUF;                          // TX -> RXed character
      break;
  }
}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI0_ISR(void)
{
  unsigned char RX=UCA0RXBUF;
  if(COM1CallBack!=0)COM1CallBack(RX);
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI1_ISR(void)
{
  unsigned char RX=UCA1RXBUF;
  if(COM2CallBack!=0)COM2CallBack(RX);
}
