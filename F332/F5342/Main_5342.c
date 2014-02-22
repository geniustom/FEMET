//#include <stdint.h>

#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "SdCard.h"
#include "Bluetooth.h"
#include "Adc.h"

#define  SampleRate             125
#define  RecordContinue         30
#define  RecordLength           SampleRate*RecordContinue
#define  SDBufSize              512

typedef union{
  struct { 
    unsigned int BufWriteIndex;
    unsigned int BufReadIndex;
    unsigned int BufLength;
    unsigned char NeedWrite;
    unsigned char SDBuf[SDBufSize];
  };
}SDAccess;


uint8_t  StartMarkFlag;
uint8_t  StopMarkFlag;
uint16_t SampleIndex;
uint8_t  TestIndex;
SDAccess SD;
char Buf[SDBufSize];

void System_Init(void){
    // Stop WDT
    WDTCTL = WDTPW + WDTHOLD;
    // Basic GPIO initialization
    Board_init();

    DCOClk_init();
    //REFOClk_Init();
    //XT2Clk_init();
    // Globally enable interrupts
    __enable_interrupt();
}


void SDStruct_Init(){
  SD.BufLength=0;
  SD.BufReadIndex=0;
  SD.BufWriteIndex=0;
  SD.NeedWrite=0;
  for(int i=0;i<SDBufSize;i++){
    SD.SDBuf[i]=0;
  }
}

void SaveToSD(){
  
  unsigned int  BufIndex;
  
  for(int i=0;i<SDBufSize;i++){
    Buf[i]=0;
  }
  BufIndex=0;
  
  _DINT();
  while(SD.BufReadIndex!=SD.BufWriteIndex){    
    Buf[BufIndex]=SD.SDBuf[SD.BufReadIndex];
    SD.BufReadIndex++;
    SD.BufReadIndex%=SDBufSize;
    BufIndex++;
  }  
  _EINT();
  
  WriteFile("DATA.txt", Buf, BufIndex);
  SD.NeedWrite=0;
}

void SaveToBuf(char *d,int len){
  for(int i=0;i<len;i++){
    SD.BufWriteIndex++;
    SD.BufWriteIndex%=SDBufSize;
    SD.SDBuf[SD.BufWriteIndex]=d[i];
  }
  SD.NeedWrite=1;
}


void main(void)
{
    System_Init();
    Bluetooth_Init();
    
    ADS1292R_Init();

    Buttons_Init(BUTTON_ALL);
    Buttons_interruptEnable(BUTTON_ALL);
    SDStruct_Init();
    
    StartMarkFlag=0;
    StopMarkFlag=0;
    SampleIndex=0;
    TestIndex=0;
    buttonsPressed = 0;
    
    P1DIR|=BIT0;
    
    // Main loop
    while (1)
    {
      if ((buttonsPressed & BUTTON_S1) && (StartMarkFlag==0) &&(StopMarkFlag==0)){
        buttonsPressed = 0;
        StartMarkFlag=1;
      }
      if((buttonsPressed & BUTTON_S1) && ((StartMarkFlag!=0) ||(StopMarkFlag!=0))){
        buttonsPressed=0;       //避免未結束前二次按下或按鍵彈跳造成誤動作
      }
      if(SD.NeedWrite!=0){
        SaveToSD();
      }
    }
}


void CheckMarkAndSavetoBuf(char *d){
  
  if((d[0]+d[1]+d[2]+d[3]+d[4]+d[5])==0){               //000000000000改為 000001000001
    d[2]=0x01;
    d[5]=0x01;
  }
  
  if((d[0]+d[1]+d[2]+d[3]+d[4]+d[5])==1530){            //FFFFFFFFFFFF改為 FFFFFEFFFFFE
    d[2]=0xFE;
    d[5]=0xFE;
  }
  
  if (StartMarkFlag==1){                    
    if (SampleIndex==0){                                //標定開始為 FFFFFFFFFFFF
      for(int i=0;i<5;i++) d[i]=0xFF;
      P1OUT^=BIT0;
    }
    
    SampleIndex++;
    if (SampleIndex==RecordLength){                     //判斷為結尾，準備標示結束
      StartMarkFlag=0;
      StopMarkFlag=1;
      P1OUT^=BIT0;
    }
  
    if (StopMarkFlag==1){                              //標定結束為 000000000000
      StopMarkFlag=0;
      SampleIndex=0;
      for(int i=0;i<5;i++) d[i]=0x00;
    }  
    BlueToothWrite(d,6);
  }
  
  SaveToBuf(d,6);
  //WriteFile("DATA.txt", d, 6);
 
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  unsigned char i;
  unsigned char Alldata[9];
  char Rawdata[6];
        
  for (i=0;i<9;i++){
    Send_CMD(0);				// trigger SPI SClk
    __delay_cycles(800);    		// delay
    while (!(UCB0IFG&UCRXIFG));             // USCI_B0 RX buffer ready?
    Alldata[i] = UCB0RXBUF;
    if(i>=3)Rawdata[i-3]=Alldata[i];
  }
        
  /*/====for testing 輸出的文字檔格式從0~9循環並換行====
  for (i=0;i<5;i++){
    Rawdata[i]=0x30+TestIndex;
  }
  Rawdata[4]=0x0d; Rawdata[5]=0x0a;
  TestIndex++;
  TestIndex%=10;
  //P1OUT^=BIT0;
  //===================================================*/
  
  ADCDRDY_clear &= ~ADCDRDY_SEL;
  CheckMarkAndSavetoBuf(Rawdata);      
}


/*
    // Main loop
    while (1)
    {
      _NOP();
      //__delay_cycles(20000000);
      //P2OUT^=BIT7;

      //BlueToothWrite("Hello~~\r\n",9);
      //BlueToothWrite("Hello~~",7);
      if (buttonsPressed & BUTTON_S1){
        buttonsPressed = 0;
        BlueToothWrite("Hello~~\r\n",9);
        //ContinueWriteTest();
      }
*/