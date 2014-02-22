#include "../TaipeiCity_A002_L.h"

void ServicePress(){
  if(A002State.State==State_Service){  //客服模式時按客服鈕無效
    DriverFlag.ServicePress=0;  //因按鈕無效，故取消致能
    return;                     //非待機模式不允許接受訊息
  }
  if(DriverFlag.RDMode==1)return; //若是RDMODE，則客服鈕不作動作
  DriverFlag.CancelPress=1;
  SendEventToPC(9);
  CancelPress(); //預先執行按下取消鈕的動作
}

void CancelPress(){
  if(A002State.State==State_SystemCheck)return;  //檢測模式不允許按下Cancel鈕
  DriverFlag.Phone0Gateway1=0;
  A002State.OnExit();
  Tentel_HangUp();
  if(DriverFlag.ServicePress==0)SendEventToPC(0);  //因為新版的客服鈕按下時..會先引動取紐,所以從這裡做檢查
  GoToFlow(State_NormalStandBy);
}

void CancelLongPress(){
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.CancelLongPress=0;  //因按鈕無效，故取消致能
    return;                     //非待機模式不允許接受訊息
  }
  SendEventToPC(10);
}

void GetRF(unsigned char ID){
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.RFPress=0;  //因按鈕無效，故取消致能
    return;                     //非待機模式不允許接受訊息
  }
  
  if(DriverFlag.RFBTIsErr==1){
    DriverFlag.RFBTIsErr=0;
    PutCTIMSG(&CTIMSGQueue,ID,CTIMSG_DeviceBTLow,EncodeNowDateTime(),0);
  }
  
  DriverFlag.RFPress=ID;
  SendEventToPC(ID);
}

void TestQueueSend(){
  //DeleteAllCTIMSG(&CTIMSGQueue);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayPowerErr,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayBTLow,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,1,CTIMSG_DeviceBTLow,EncodeNowDateTime(),0);    //第一組壓扣異常
  for(int i=0;i<CTIMessageQueueLength;i++){
    PutCTIMSG(&CTIMSGQueue,1,CTIMSG_HealthDataUpload,EncodeNowDateTime(),((i+1)*111111111));
  }
}

void NormalStandBy_Enter(){
  DriverFlag.TentelOn=0;
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.SpeakState=0;
  DriverFlag.KeepAllAlarm=0;
  Tentel_HangUp();
}


void NormalStandBy_Exit(){
  DriverFlag.TentelOn=0;
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  Tentel_HangUp();
}


void NormalStandBy_Work(){
//============================================================檢查QUEUE是否已滿，若滿了，不允許做任何事，只能一直播
  if(CTIMSGQueue.Length!=CTIMessageQueueLength){
    SetLEDState(&LED_NowIsHelp,0,0);
  }
//============================================================按下壓扣
  if(DriverFlag.RFPress!=0){  
    unsigned char User=DriverFlag.RFPress;
    DriverFlag.RFPress=0;     //復位

    if(SystemConfig_BatchTransfer<50){ //沒資料或單筆傳送只嗶一聲
      BuzzerBeep(100);
    }
    //unsigned char DataFind=MEADEV_GetDeviceData(User);  //單筆血糖傳輸
    unsigned char DataFind=MEADEV_GetDeviceDataMulti(User);  //多筆血糖傳輸
    MEADEV_SetDeviceTime();
    
    if(DataFind==1){  
      if(SystemConfig_BatchTransfer>=50){ //若為批次傳送就嗶三聲
        for(int i=0;i<3;i++){
          Delayms(50);
          BuzzerBeep(50);
        }
      }

      if(SystemConfig_DataAutoDelete!=0)MEADEV_ClearFlash();
      
      if(QueueNeedSendImportantData()==1){  //有大事才傳送
        GoToFlow(State_StartLine);
      }
    }
    return;
  }
  
//============================================================按下取消鈕
  if(DriverFlag.CancelPress==1){
    DriverFlag.CancelPress=0;
    BuzzerBeep(100);
    return;
  }
//============================================================按下取消鈕
  if(DriverFlag.NeedReport==1){ 
    DriverFlag.NeedReport=0;
    GoToFlow(State_StartLine);
    return;
  }  
//============================================================長按取消鈕
  if(DriverFlag.CancelLongPress==1){
    DriverFlag.CancelLongPress=0;
    BuzzerBeep(100);
    TelRing();    
    if(DriverFlag.RDMode==1){
      TestQueueSend();
      GoToFlow(State_StartLine);
    }else{
      PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
      GoToFlow(State_SystemCheck);    
    }
    return;
  }
//============================================================按下服務鈕 
  if(DriverFlag.ServicePress==1){
    DriverFlag.ServicePress=0;
    GoToFlow(State_Service);
    return;
  } 
//============================================================系統回報
  if(((SystemDateTime.SystemTotalHour-SystemAlarm.SystemReportStartTime)%SystemConfig_SystemReportContinue==0)&&
     (SystemDateTime.Second<5)&&(SystemDateTime.Minute==SystemConfig_FirstReportMinute)) {
    Delayms(1000);
    DriverFlag.KeepAllAlarm=1;   //系統回報不叫
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
    GoToFlow(State_StartLine);
    return;
  }
//===========================================================第一次系統回報
  unsigned long FirstReportTime=EncodeDateTime(SystemConfig_FirstReportYear-2000,SystemConfig_FirstReportMonth,
                                                SystemConfig_FirstReportDate,SystemConfig_FirstReportHour,
                                                SystemConfig_FirstReportMinute);
  if(SystemConfig_FirstReport==1){
    if ((FirstReportTime==SystemDateTime.EncodeTime)&&(SystemDateTime.Second<5)){
      DriverFlag.KeepAllAlarm=1;   //系統回報不叫
      Delayms(1000);
      PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
      NeedSetupTime=1;
      GoToFlow(State_StartLine);
      return;    
    }
  }
//============================================================鬧鈴啟動
  if(NowIsAlarm==1){  //鬧鐘結束..回到待機模式
    //BuzzerBeep(100);
    GoToFlow(State_Alarm);
    return;
  }
//============================================================系統檢查
  if((SystemDateTime.Second==0)&&(SystemDateTime.SystemTotalMinute%SystemConfig_SystemCheckTimeout==0)){
    Delayms(1000);
    MEADEV_SetDeviceTime();
    GoToFlow(State_SystemCheck); 
    return;  
  }

}