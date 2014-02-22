#include "F332_Lib.h"


#define UartBufLen      64

unsigned char DTMF_Buf[32];
unsigned int  DTMF_BufIndex;
unsigned char UART_Buf[UartBufLen];
unsigned int  UART_BufIndex;



//---------------------------------------------------------------------------------------
const unsigned char TCMD_HandFreeOn[4]={0xFA,0x6C,0xC7,0xAB};             //�}�_�K��
const unsigned char TCMD_HandFreeOff[4]={0xFA,0x6C,0xCD,0xA1};            //�����K��
const unsigned char TCMD_DialOut[4]={0xFA,0x65,0xAA,0xCF};                //���X�s�򸹽X
const unsigned char TCMD_SPKOff[4]={0xFA,0x6C,0xC4,0xA8};                 //����SPK
const unsigned char TCMD_SPKOn[4]={0xFA,0x6C,0xC0,0xAC};                  //�}��SPK
const unsigned char TCMD_GetEEPROM[4]={0xFA,0x60,0x64,0x04};              //Ū��EEPROM�X�t�]�w��
const unsigned char TCMD_TestPhone[4]={0xFA,0x60,0x60,0x00};              //���ոܾ��O�_�^��
const unsigned char TCMD_DefaultSetting_1[19]={0xFA,0x51,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x51};
const unsigned char TCMD_DefaultSetting_2[19]={0xFA,0x52,0x10,0x03,0x20,0x03,0x00,0x15,0x12,0x99,0x99,0x06,0x01,0x00,0xAA,0x00,0x99,0x99,0xC8};
//---------------------------------------------------------------------------------------
const unsigned char TRCMD_DialTone[3]={0x89,0x8d,0x04};                   //�����켷����
const unsigned char TRCMD_BusyTone[3]={0x89,0x89,0x33};                   //�����즣��
const unsigned char TRCMD_DTMFTone[1]={0x8A};                             //������DTMF
const unsigned char TRCMD_DialRing[2]={0x80,0x80};                        //�������T�a
const unsigned char TRCMD_TestRequest[1]={0x70};                          //��������ոܾ��^��
//---------------------------------------------------------------------------------------



void DTMFGen_init(){
  P4DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT6 + BIT7;
  P4OUT |= BIT6;        //HT9200B Serial or Parallel Mode Select	High�GParallel Mode�ALow�GSerial Mode
  P4OUT |= BIT7;        //HT9200B Chip Enable Pin	Low�GHT9200B Chip Enable
}

void DTMFRecv_init(){
  // CS Enable
  P2DIR |= BIT0;
  P2OUT &= ~BIT0;
  // DTMF-STD
  P1DIR &= ~BIT7; 
  P1REN |= BIT7;                            // Enable P1.7 internal resistance
  P1OUT |= BIT7;                            // Set P1.7 as pull-Up resistance
  P1IES |= BIT7;                            // P1.7 Hi/Lo edge
  P1IFG &= ~BIT7;                           // P1.7 IFG cleared
  P1IE |= BIT7;                             // P1.7 interrupt enabled
}


void Delayms(unsigned int t){
  for(int i=0;i<t;i++){
    __delay_cycles(25000);
  }
}

void F332_RX(char RX){
  if(RX==0xFA){
    for(int i=0;i<UartBufLen;i++){
      UART_Buf[i]=0;
    }
    UART_BufIndex=0;
  }
  UART_Buf[UART_BufIndex]=RX;
  UART_BufIndex++;
}


void F332_init(){
    DTMFGen_init();
    DTMFRecv_init();  
    OpenUart(2,1200,F332_RX); 

}



void F332_PickUp(){          //�����B��������	High�G�����ALow�G����
  P1DIR |= BIT0;
  P1OUT |= BIT0;
}

void F332_HangUp(){          //�����B��������	High�G�����ALow�G����
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
}

void F332_SetMute(int m){    //Speech or Dialing Mode����	High�G�y��IC�R���A�i�@�����ALow�G�y���q��
  P1DIR |= BIT1;
  if(m==0){
    P1OUT &= ~BIT1;
  }else{
    P1OUT |= BIT1;
  }
}


void F332_DTMF_Comein(unsigned char Digi){
  unsigned char DTMF[16]={'D','1','2','3','4','5','6','7','8','9','0','*','#','A','B','C'};
  DTMF_Buf[DTMF_BufIndex]=DTMF[Digi];
  DTMF_BufIndex++;
  DTMF_BufIndex %=32;
}

void F332_DTMF_Out(unsigned char Digi){
  unsigned char DTMF[10]={0x0a,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
  unsigned char D;
  //=======================�T�O��������=======================
  F332_SetMute(1);
  //==========================================================
  
  switch(Digi){
    case 0x2A: 
      D=0x0b;    break;        //*
    case 0x23: 
      D=0x0c;    break;        //#
    case 0x41: 
      D=0x0d;    break;        //A
    case 0x42: 
      D=0x0e;    break;        //B
    case 0x43: 
      D=0x0f;    break;        //C
    case 0x44: 
      D=0x00;    break;        //D 
    default: 
      D=DTMF[Digi-0x30];
  }
  
  //HT9200B Chip Enable Pin	Low�GHT9200B Chip Enable
  P4OUT = (P4OUT & 0xf0) + (D & 0x0f);
  P4OUT &= ~BIT7;              //�o�X�n��  
  Delayms(100);
  P4OUT |= BIT7;               //�����n��   
  Delayms(100);                 
}

void F332_DTMF_OutList(unsigned char *Digi,unsigned int Len){
  for(int i=0;i<Len;i++){
    F332_DTMF_Out(Digi[i]);
  }
}


/***************************************************************************//**
 * @brief  Handles Port 1 interrupts - performs button debouncing and registers
 *         button presses.
 * @param  none
 * @return none
 ******************************************************************************/

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  if((P1IFG & BIT7) == BIT7){                //������ DTMF
    unsigned char Digi= (P1IN & (BIT2+BIT3+BIT4+BIT5)) >>2 ;
    F332_DTMF_Comein(Digi);
    P1IFG &= ~BIT7;                          // P1.7 IFG cleared
  }  
}
