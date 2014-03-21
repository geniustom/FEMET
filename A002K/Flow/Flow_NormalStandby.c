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
  if(DriverFlag.RFBTIsErr==1){
    DriverFlag.RFBTIsErr=0;
    PutCTIMSG(&CTIMSGQueue,ID,CTIMSG_DeviceBTLow,EncodeNowDateTime(),0);
  }
  //========================================================把以下MARK拿掉，壓扣八就具有重啟後並把 Emergency_Flag改為1的功能
  //*
  if((ID==8)&&(A002State.State!=State_Service)){
    //_DINT();
    unsigned char Emergency_BUF[256];
    Emergency_BUF[0]=1;
    Emergency_BUF[1]=DriverFlag.BTState;
    flash_erase_multi_segments(Emergency_Addr,1);
    flash_write_Block(Emergency_Addr,Emergency_BUF,1);
    //_EINT();    
    SendQueueDataToFlash((int *)&CTIMSGQueue);
    DriverFlag.ResetSystem=1; 
    ResetMCUByPMM();
    return;
  }
  //*/
  //=======================================================把以上MARK拿掉，壓扣八就具有重啟後並把 Emergency_Flag改為1的功能
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.RFPress=0;  //因按鈕無效，故取消致能
    return;                     //非待機模式不允許接受訊息
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
//============================================================按下緊急(壓扣八)
  if(Emergency_Flag==1){
    //_DINT();
    DriverFlag.BTState=BTState_Flag;
    unsigned char Emergency_BUF[256];
    Emergency_BUF[0]=0;
    Emergency_BUF[1]=DriverFlag.BTState;
    flash_erase_multi_segments(Emergency_Addr,1);
    flash_write_Block(Emergency_Addr,Emergency_BUF,256);
    //_EINT();
    SendEventToPC(8);
    //####################### 優先權最高的傳送52訊息 ######################
    //DeleteAllCTIMSG(&CTIMSGQueue);
    //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayCall,EncodeNowDateTime(),0); //壓扣8為緊急訊息，其餘為傳輸生理資料
    //GoToFlow(State_StartLine);
    //##################### 將FLASHROM的訊息塞回QUEUE #####################
    GetQueueDataFromFlash((int *)&CTIMSGQueue);
    //####################### 優先權最高的啟動客服 ########################
    DriverFlag.ServicePress=0;
    GoToFlow(State_Service);
    //#####################################################################
    return;
  }   
//============================================================感應到RFID  
  if(DriverFlag.RFIDCardDetect==1){
    SendRFIDToPC(DriverFlag.RFIDCardNumber);
    Delayms(100);
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode1) DriverFlag.RFPress=1;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode2) DriverFlag.RFPress=2;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode3) DriverFlag.RFPress=3;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode4) DriverFlag.RFPress=4;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode5) DriverFlag.RFPress=5;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode6) DriverFlag.RFPress=6;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode7) DriverFlag.RFPress=7;
    if (DriverFlag.RFIDCardNumber==SystemConfig_RfidCode8) DriverFlag.RFPress=8;

    DriverFlag.RFIDCardDetect=0;
    if(DriverFlag.RFPress==0){
      BuzzerBeep(100);
    }else{
      GetRF(DriverFlag.RFPress);
    }
  } 
//============================================================按下壓扣
  if(DriverFlag.RFPress!=0){  
    unsigned char User=DriverFlag.RFPress;
    DriverFlag.RFPress=0;     //復位

    if(SystemConfig_BatchTransfer<50){ //沒資料或單筆傳送只嗶一聲
      BuzzerBeep(100);
    }
    
    if (User==8){       
      //DriverFlag.ServicePress=1;  //壓扣8為客服，其餘為傳輸生理資料
      //DeleteAllCTIMSG(&CTIMSGQueue);
      //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayCall,EncodeNowDateTime(),0); //壓扣8為緊急訊息，其餘為傳輸生理資料
      //GoToFlow(State_StartLine);
    }else{
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