#include "DriverLib.h"

IOFlag DriverFlag;

void InitPortOutput(){

}

void InitPortDirection(){
  P1DIR = 0x00;     //�]�w����J
  P2DIR = 0x00;     //�]�w����J
  P3DIR = CON_ToneDetEn | RTC_SDA | RTC_SCL | CON_Buzzer | CON_SPK | CON_DCDC;
  //P4DIR = RF_C0 | RF_C1 | RF_C2 | RF_C3 | RF_C4 | RF_C5 | RF_C6 | RF_C7;      //�]�w����X
  P5DIR = CON_PorG | CON_MIC;                                                   //�]�w����X
  P6DIR = LED_AC | LED_DC | LED_Call | LED_RFLow | LED_LineErr | LED_CallErr;   //�]�w����X
}


void SetP1InterruptIO(){
  // �N���_�H�s���M�s
  P1IE = 0;
  P1IES = 0;
  P1IFG=0;  //�M���Ҧ�P1���_���СA�קK�}�������޵o���_
  //=========���}IO���_�\�� HI:�ҥ� LO:����===========
  P1IE =  (unsigned char)(
          (~RF_C8)     |    //I	RF���yCODE��BIT8
          (~RF_C9)     |    //I	RF���yCODE��BIT9
          (~RF_C10)    |    //I	RF����(����)
          (~RF_C11)    |    //I	RF����(�����S�q)
          (KEY_Help)   |    //I	�D�ϫ��s
          (KEY_Cancel) |    //I	�������s
          (DET_Busy)   |    //I	��������PIN
          (DET_RF));         //I	RF����PIN(VT)
  //========�]�wĲ�o���� HI:�t�tĲ�o LO:���tĲ�o======  

  P1IES = (0*RF_C8)     |    //I	RF���yCODE��BIT8(�L)
          (0*RF_C9)     |    //I	RF���yCODE��BIT9(�L)
          (0*RF_C10)    |    //I	RF����(����)(���t)
          (0*RF_C11)    |    //I	RF����(�����S�q)(���t)
          (0*KEY_Help)  |    //I	�D�ϫ��s(�t�t)
          (0*KEY_Cancel)|    //I	�������s(�t�t)
          (0*DET_Busy)  |    //I	��������PIN(���t)  
          (0*DET_RF);        //I	RF����PIN(VT)
  //P1IES = 0;
  //==================================================
  P1IFG=0;  //�M���Ҧ�P1���_���СA�קK�}�������޵o���_
}



void InitInterruptIO(){
  SetP1InterruptIO();
  //SetP2InterruptIO();
}

void InitPort(){
  InitPortDirection();
  InitPortOutput();
  InitInterruptIO();
}


void SetPinSync(IOFlag *Flag){
//----------------------P3--------------------
  P3OUT=
        (Flag->TentelOn * CON_DCDC)|
        (Flag->SpeakState * CON_SPK)|
        ((1-Flag->EnableToneDet) * CON_ToneDetEn); //Tone����IC��Enable pin  En:0 Dis:1
        
  if (Flag->BuzzerState==1){
    if (Flag->BuzzerOn==1){P3OUT |= CON_Buzzer;}
  }else{
    P3OUT &=~CON_Buzzer;
  }
//----------------------P4--------------------
  P4OUT=0x00;                 //���ެO���O�]�w����X�AP4OUT����0
//----------------------P5--------------------
  P5OUT=
        (Flag->Phone0Gateway1 * CON_PorG) | 
        (Flag->MicState * CON_MIC);  
//----------------------P6--------------------
}

void GetPinSync(IOFlag *Flag){
  if ((P1IN & DET_Busy) ==0x00){  //�������Φ���
                                Flag->NowIsDialTone=1;
                             }else{
                                Flag->NowIsDialTone=0;
                             }
  if ((P2IN & DET_Line) ==0x00){ Flag->LineIsErr=1;}else{Flag->LineIsErr=0;}  //���`HI �S��LO 
  if ((P2IN & DET_MeaDevice) ==0x00){ Flag->MeaDev=1;}else{Flag->MeaDev=0;}   //High�G�ؼs��}�p�ALow�G�ʲ������p
  if ((P6IN & DET_AC) ==0x00){  Flag->ACState=1;}else{Flag->ACState=0;}  //���qLO �S�qHI
  if ((P6IN & DET_DC) ==0x00){  Flag->BTState=0;}else{Flag->BTState=1;}  //���qHI �S�qLO
}


#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
  //=====================================�ȪA�s===============
  if(P1IFG &KEY_Help){
    ButtonSignal(ServiceButton,(P1IES&KEY_Help));
    P1IES^=KEY_Help;
  }
  //=====================================�����s===============
  if(P1IFG &KEY_Cancel){
    ButtonSignal(CancelButton,(P1IES&KEY_Cancel));
    P1IES^=KEY_Cancel;
  }
  //=====================================RF===================  
  if(P1IFG &DET_RF){
    RF.LockKey=1;
    unsigned char RFIN_CodeExt=0;
    DriverFlag.RFIN_Code=ByteReverse(P4DIR);
    RFIN_CodeExt=3- (P1IN&(BIT0|BIT1));
    RFIN_CodeExt=((RFIN_CodeExt%2)*2)+(RFIN_CodeExt/2);
    DriverFlag.RFIN_Code=DriverFlag.RFIN_Code*4+RFIN_CodeExt;
    if((P1IN&RF_C10)!=0){
        DriverFlag.RFBTIsErr=0;   //���q
    }else{
        DriverFlag.RFBTIsErr=1;   //�S�q
    }
    DetRF_VT();
  }
  //====================================�����˴�==============
  if(P1IFG &DET_Busy){
    if (P1IES&DET_Busy){
      DetBusyHi();
    }else{
      DetBusyLo();
    }
    P1IES^=DET_Busy;   //���t�tĲ�o����
  }
  //=============================�_��==========================    
  if(P1IFG & BIT0){P1IFG &= ~(BIT0);}// �M�����_�лx�줸
  if(P1IFG & BIT1){P1IFG &= ~(BIT1);}// �M�����_�лx�줸
  if(P1IFG & BIT2){P1IFG &= ~(BIT2);}// �M�����_�лx�줸
  if(P1IFG & BIT3){P1IFG &= ~(BIT3);}// �M�����_�лx�줸
  if(P1IFG & BIT4){P1IFG &= ~(BIT4);}// �M�����_�лx�줸
  if(P1IFG & BIT5){P1IFG &= ~(BIT5);}// �M�����_�лx�줸
  if(P1IFG & BIT6){P1IFG &= ~(BIT6);}// �M�����_�лx�줸
  if(P1IFG & BIT7){P1IFG &= ~(BIT7);}// �M�����_�лx�줸
}