#include "DriverLib.h"

IOFlag DriverFlag;

void InitPortOutput(){

}

void InitPortDirection(){
  P1DIR = 0x00;     //設定為輸入
  P2DIR = 0x00;     //設定為輸入
  P3DIR = CON_ToneDetEn | RTC_SDA | RTC_SCL | CON_Buzzer | CON_SPK | CON_DCDC;
  //P4DIR = RF_C0 | RF_C1 | RF_C2 | RF_C3 | RF_C4 | RF_C5 | RF_C6 | RF_C7;      //設定為輸出
  P5DIR = CON_PorG | CON_MIC;                                                   //設定為輸出
  P6DIR = LED_AC | LED_DC | LED_Call | LED_RFLow | LED_LineErr | LED_CallErr;   //設定為輸出
}


void SetP1InterruptIO(){
  // 將中斷寄存器清零
  P1IE = 0;
  P1IES = 0;
  P1IFG=0;  //清除所有P1中斷期標，避免開機瞬間引發中斷
  //=========打開IO中斷功能 HI:啟用 LO:停用===========
  P1IE =  (unsigned char)(
          (~RF_C8)     |    //I	RF掃描CODE的BIT8
          (~RF_C9)     |    //I	RF掃描CODE的BIT9
          (~RF_C10)    |    //I	RF接收(壓扣)
          (~RF_C11)    |    //I	RF接收(壓扣沒電)
          (KEY_Help)   |    //I	求救按鈕
          (KEY_Cancel) |    //I	取消按鈕
          (DET_Busy)   |    //I	忙音偵測PIN
          (DET_RF));         //I	RF偵測PIN(VT)
  //========設定觸發種類 HI:負緣觸發 LO:正緣觸發======  

  P1IES = (0*RF_C8)     |    //I	RF掃描CODE的BIT8(無)
          (0*RF_C9)     |    //I	RF掃描CODE的BIT9(無)
          (0*RF_C10)    |    //I	RF接收(壓扣)(正緣)
          (0*RF_C11)    |    //I	RF接收(壓扣沒電)(正緣)
          (0*KEY_Help)  |    //I	求救按鈕(負緣)
          (0*KEY_Cancel)|    //I	取消按鈕(負緣)
          (0*DET_Busy)  |    //I	忙音偵測PIN(正緣)  
          (0*DET_RF);        //I	RF偵測PIN(VT)
  //P1IES = 0;
  //==================================================
  P1IFG=0;  //清除所有P1中斷期標，避免開機瞬間引發中斷
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
        ((1-Flag->EnableToneDet) * CON_ToneDetEn); //Tone偵測IC的Enable pin  En:0 Dis:1
        
  if (Flag->BuzzerState==1){
    if (Flag->BuzzerOn==1){P3OUT |= CON_Buzzer;}
  }else{
    P3OUT &=~CON_Buzzer;
  }
//----------------------P4--------------------
  P4OUT=0x00;                 //不管是不是設定為輸出，P4OUT都為0
//----------------------P5--------------------
  P5OUT=
        (Flag->Phone0Gateway1 * CON_PorG) | 
        (Flag->MicState * CON_MIC);  
//----------------------P6--------------------
}

void GetPinSync(IOFlag *Flag){
  if ((P1IN & DET_Busy) ==0x00){  //撥號音或忙音
                                Flag->NowIsDialTone=1;
                             }else{
                                Flag->NowIsDialTone=0;
                             }
  if ((P2IN & DET_Line) ==0x00){ Flag->LineIsErr=1;}else{Flag->LineIsErr=0;}  //正常HI 沒接LO 
  if ((P2IN & DET_MeaDevice) ==0x00){ Flag->MeaDev=1;}else{Flag->MeaDev=0;}   //High：華廣血糖計，Low：百略血壓計
  if ((P6IN & DET_AC) ==0x00){  Flag->ACState=1;}else{Flag->ACState=0;}  //有電LO 沒電HI
  if ((P6IN & DET_DC) ==0x00){  Flag->BTState=0;}else{Flag->BTState=1;}  //有電HI 沒電LO
}


#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
  //=====================================客服鈕===============
  if(P1IFG &KEY_Help){
    ButtonSignal(ServiceButton,(P1IES&KEY_Help));
    P1IES^=KEY_Help;
  }
  //=====================================取消鈕===============
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
        DriverFlag.RFBTIsErr=0;   //有電
    }else{
        DriverFlag.RFBTIsErr=1;   //沒電
    }
    DetRF_VT();
  }
  //====================================忙音檢測==============
  if(P1IFG &DET_Busy){
    if (P1IES&DET_Busy){
      DetBusyHi();
    }else{
      DetBusyLo();
    }
    P1IES^=DET_Busy;   //正負緣觸發互換
  }
  //=============================復位==========================    
  if(P1IFG & BIT0){P1IFG &= ~(BIT0);}// 清除中斷標誌位元
  if(P1IFG & BIT1){P1IFG &= ~(BIT1);}// 清除中斷標誌位元
  if(P1IFG & BIT2){P1IFG &= ~(BIT2);}// 清除中斷標誌位元
  if(P1IFG & BIT3){P1IFG &= ~(BIT3);}// 清除中斷標誌位元
  if(P1IFG & BIT4){P1IFG &= ~(BIT4);}// 清除中斷標誌位元
  if(P1IFG & BIT5){P1IFG &= ~(BIT5);}// 清除中斷標誌位元
  if(P1IFG & BIT6){P1IFG &= ~(BIT6);}// 清除中斷標誌位元
  if(P1IFG & BIT7){P1IFG &= ~(BIT7);}// 清除中斷標誌位元
}