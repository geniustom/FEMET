#include "DriverLib/DriverLib.h"
#include "TENTEL/Tentel.h"
#include "TaipeiCity_A002_L.h"


unsigned char P1IESetting,P2IESetting;
 
void DisableP1P2Int(){
  P1IESetting=P1IE;
  P2IESetting=P2IE;
  P1IE=0;
  P2IE=0;
}

void EnableP1P2Int(){
  P1IE=P1IESetting;
  P2IE=P2IESetting;
}



void InitAllDriver(){
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    StartXT1();
    SetSystemClock(SYSCLK_8MHZ);  
    
    InitWDT();
    
    InitPort();
    DisableP1P2Int();
    
    RF.Code[0]=SystemConfig_MachineID1;
    RF.Code[1]=SystemConfig_MachineID2;
    RF.Code[2]=SystemConfig_MachineID3;
    RF.Code[3]=SystemConfig_MachineID4;
    RF.Code[4]=SystemConfig_MachineID5;
    RF.Code[5]=SystemConfig_MachineID6;
    RF.Code[6]=SystemConfig_MachineID7;
    RF.Code[7]=SystemConfig_MachineID8;
    InitRF(GetRF);
    InitRFID();
    
    InitBuzzer(SystemConfig_BuzzerMode);
    InitLEDState();
    InitButton(2000,ServicePress,CancelPress,ServicePress,CancelLongPress);
    //客服鈕長按功能相同，但取消鈕長按為手動系統回報
 
    Init_RTC();

    SetDefaultTime(SystemConfig_NowYear,SystemConfig_NowMonth,SystemConfig_NowDay,
                   SystemConfig_NowHour,SystemConfig_NowMinute,SystemConfig_NowSecond);    
    
    _EINT();
    
}

void InitAllAlarm(){
  SystemAlarm.NO1_Hour=SystemConfig_AlarmHour1;
  SystemAlarm.NO1_Minute=SystemConfig_AlarmMinute1;
  SystemAlarm.NO1_Contiune=SystemConfig_AlarmContinue1;
  SystemAlarm.NO2_Hour=SystemConfig_AlarmHour2;
  SystemAlarm.NO2_Minute=SystemConfig_AlarmMinute2;
  SystemAlarm.NO2_Contiune=SystemConfig_AlarmContinue2;
  SystemAlarm.NO3_Hour=SystemConfig_AlarmHour3;
  SystemAlarm.NO3_Minute=SystemConfig_AlarmMinute3;
  SystemAlarm.NO3_Contiune=SystemConfig_AlarmContinue3;
  SystemAlarm.NO4_Hour=SystemConfig_AlarmHour4;
  SystemAlarm.NO4_Minute=SystemConfig_AlarmMinute4;
  SystemAlarm.NO4_Contiune=SystemConfig_AlarmContinue4;  
  InitAlarm(AlarmStart,AlarmStop);
}

void InitAllProgram(){
  Init_Tentel();
  MEADEV_InitDevice();
  Init_PCRS232();
  InitAllAlarm();
 
  SystemAlarm.SystemReportStartTime=((unsigned long)SystemConfig_SystemReportHour)+
                                    ((unsigned long)SystemConfig_SystemReportDate*24)+
                                    ((unsigned long)SystemConfig_SystemReportMonth*720)+
                                    ((unsigned long)(SystemConfig_SystemReportYear-2000)*8640); 
}



void Routin(){
    if(A002State.Step==0){
      A002State.OnEnter();
      A002State.Step=1;
      Delayms(10);
    }
    
    if(A002State.Step==1){A002State.OnWork();}
    if(A002State.Step==2){A002State.OnDTMF();}
    if(A002State.Step==3){
      A002State.PreExit();
      A002State.Step=0;
      Delayms(10);
    }
    CheckRFBTtoLED();
    Delayms(10);
}

/*
void RunSystem(){
  InitAllDriver();
  InitAllProgram();
  Delayms(100); 
  BuzzerBeep(100); 

  InitFlow();  
  while(1){
    DriverRoutin();
    Routin();
  }
}
*/


int main( void )
{
  InitAllDriver();
  CreateCTIMSGQueue(&CTIMSGQueue);
  InitAllProgram();
  SendTextToUart(COM3,"GWON",4);
  SendTextToUart(COM3,VER,4);
  
  //Delayms(100); 
  BuzzerBeep(100); 
  CheckSOPMode(); //===========檢查是否要進入SOP MODE
  
  InitFlow();  
  EnableP1P2Int();

  SendQueueSizeToPC(&CTIMSGQueue);
  while(1){
    ReportWDT();
    if(DriverFlag.RDMode==1){
      //TestQueueSend();   //一次塞32筆data到QUEUE
      DriverFlag.CancelLongPress=1;       //瘋狂燒機測試時使用
    }
    if(DriverFlag.RDModeStateChange==1){  //回復狀態時Reset
      if(DriverFlag.RDMode==1){           //進入
        GoToFlow(State_NormalStandBy);            
        DriverFlag.RDModeStateChange=0;
      }else{                              //回復
        DriverFlag.ResetSystem=1;   
      }
    }
    DriverRoutin();
    Routin();
  }
}



/*
    for(int i=0;i<6;i++){
      SetLEDState(&LEDList[i],50,50);
    }

    SetLEDState(&LED_Power,50,50);
    SetLEDState(&LED_BT,100,100);
    SetLEDState(&LED_NowIsHelp,100,300);
      Delayms(1000);
      BuzzerBeep(100);
      Delayms(1000);
      BuzzerRing();
      Delayms(1000);
      TelRing();
*/