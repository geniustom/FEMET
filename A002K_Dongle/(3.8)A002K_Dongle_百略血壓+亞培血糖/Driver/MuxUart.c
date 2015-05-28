#include "../Driver/Driver.h"

Mux_Uart DongleUart;

void ProcessHWUart(unsigned char Rx){
  HW_Uart *NowPort=&(DongleUart.Port[DongleUart.NowUsePort]);
  NowPort->HW_UartBUF[NowPort->BufferIndex]=Rx;
  NowPort->BufferIndex++;
  NowPort->BufferIndex%=HWUartBufLen;
  NowPort->CallBackFunction(Rx);
}


void SetupMuxUart(unsigned char MuxID,unsigned char Init){ //0~3
  _DINT();
  
  P3DIR|=BIT0+BIT1;
  if(Init==1){
    P3OUT=(P3OUT&0xfc)+MuxID;
  }
  DongleUart.NowUsePort=MuxID;
  DongleUart.CurrentPort=&(DongleUart.Port[DongleUart.NowUsePort]);
  ResetHWUartBuf(DongleUart.CurrentPort);

  SetupHwUart(DongleUart.CurrentPort,DongleUart.CurrentPort->Baudrate);

  _EINT();
  
}

void InitMuxUart(unsigned char MuxID,unsigned long BD,void (*CF)(unsigned char),unsigned char Init){

  DongleUart.CurrentPort=&(DongleUart.Port[MuxID]);
  
  DongleUart.CurrentPort->Baudrate=BD;
  DongleUart.CurrentPort->CallBackFunction=CF;
  
  //SetupHwUart(NowPort,NowPort->Baudrate,NowPort->CallBackFunction);
  SetupMuxUart(MuxID,Init);
  
}


void SentByteToMuxUart(unsigned char MuxID,unsigned char Data){
  SetupMuxUart(MuxID,1);
  while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
    UCA0TXBUF =  Data;                    // TX -> RXed character
}

void SentTextToMuxUart(unsigned char MuxID,unsigned char *Data,unsigned int length){
  SetupMuxUart(MuxID,1);
  for(int i=0;i<length;i++){
    while (!(IFG2 & UCA0TXIFG));              // USCI_A0 TX buffer ready?
    UCA0TXBUF =  Data[i];                    // TX -> RXed character
  }
}