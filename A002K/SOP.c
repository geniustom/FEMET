#include "DriverLib/DriverLib.h"
#include "TENTEL/Tentel.h"
#include "TaipeiCity_A002_L.h"

void SOPMode1(){
    DriverFlag.Phone0Gateway1=0; //不搶電話線(與傳輸不同)
    DriverFlag.MicState=0;
    DriverFlag.PhoneBusy=0;
    DriverFlag.RDMode=1;
    DriverFlag.TentelOn=1;      //讓國洋ALWAYS掛機時，要將此打開
    //==============================================開啟喇叭
    DriverFlag.SpeakState=1;
    EnableSpeaker(SystemConfig_SPK_Talk);
    Delayms(10);
    //==============================================等待撥號音
    Delayms(2000);
    Tentel_PickUp();
    Delayms(2000);
    
    unsigned char SOPDTMF[12]={1,2,3,4,5,6,7,8,9,'*',0,'#'};
    Tentel_SendDTMFList(SOPDTMF,12);   
/*  
    Tentel_SendKey(1);   Delayms(500);
    Tentel_SendKey(2);   Delayms(500);
    Tentel_SendKey(3);   Delayms(500);
    Tentel_SendKey(4);   Delayms(500);
    Tentel_SendKey(5);   Delayms(500);
    Tentel_SendKey(6);   Delayms(500);
    Tentel_SendKey(7);   Delayms(500);
    Tentel_SendKey(8);   Delayms(500);
    Tentel_SendKey(9);   Delayms(500);
    Tentel_SendKey('*'); Delayms(500);
    Tentel_SendKey(0);   Delayms(500);
    Tentel_SendKey('#'); Delayms(500);
*/    
    DriverFlag.MicState=1;
    
    Delayms(3000);
    EnableP1P2Int();
    
    while(1){
      //============================================================================偵測是否按下* (開起喇叭)
      unsigned char DTMFData=Tentel_GetDTMFDigi();
      if(DTMFData==0xfa){ //*
        AddVoice();
        DriverFlag.MicState=1;
      }
      //============================================================================偵測話筒按下# (關閉喇叭)
      if(DTMFData==0xf3){ //#
        SubVoice();
        DriverFlag.MicState=1;
      }
      //============================================================================偵測忙音
      if(DriverFlag.PhoneBusy==1){
        DriverFlag.PhoneBusy=0;
        DriverFlag.ResetSystem=1;
        return;
      }
    }
}

void SOPMode2(){
    DriverFlag.RDMode=1;
}


void CheckSOPMode(){
  if(SystemConfig_DebugModeEnable==1){
    for(int i=0;i<200;i++){
      Delayms(10);
    }
    SOPMode2();
    return;
  }
  
  unsigned CheckButton= KEY_Help | KEY_Cancel;
  if ((P1IN&CheckButton)==CheckButton){  //開機時若按下兩顆鈕，啟動SOP模式
    SetLEDState(&LED_NowIsHelp,1000,0); //傳輸LED恆亮
    BuzzerBeep(3000);
    //================================等待3秒後，檢察按鍵情況
    switch (P1IN&CheckButton){
      case (KEY_Help | KEY_Cancel):     //若仍按兩顆鈕，RESET在讓你試一次
        DriverFlag.ResetSystem=1; break;
      case KEY_Help:                    //按H進入SOP模式
        SOPMode1();               break;
      case KEY_Cancel:                  //按C進入DEBUG模式
        SOPMode2();               break;  
    }
    //甚麼都沒按，計續原先的開機流程
  }
}