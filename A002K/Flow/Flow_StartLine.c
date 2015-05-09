#include "../TaipeiCity_A002_L.h"


void TransferErr(){
  for(int i=0;i<10;i++){
    BuzzerBeep(50);
    Delayms(50);
  }
  Tentel_HangUp();
}

void CallSuccess(){
  SetLEDState(&LED_HelpError,0,0);     //成功恆滅
  Tentel_HangUp();
  for(int i=0;i<7;i++){
    BuzzerBeep(100);
    Delayms(100);
  }
}

void CallError(){ 
  SetLEDState(&LED_HelpError,500,0);     //失敗恆亮
  Tentel_HangUp();
  Delayms(100);
  BuzzerBeep(2000);
}

unsigned char Wait15SecToStart(){
  unsigned char BeepCount;  //RD MODE響5聲,非RD MODE響15聲
  if(DriverFlag.RDMode==1){
    BeepCount=5;
  }else{
    BeepCount=15;
  }
    
  for (int i=0;i<BeepCount;i++){
      //-----------------------------每嗶一聲讀取一次國洋設定值--------
      if (i%3==0){
        MEADEV_GetDeviceVER();       
      }
      if (i%3==1){
        Tentel_GetDefault();
      }
      if (i%3==2){
        Tentel_DumpBuf2PC();
        Tentel_HangUp();        
      }
      //-----------------------------------------------------------
    for(int j=0;j<10;j++){//2s秒裡面只要叫0.1秒就好
      if((j==0)&&(i%2==0)){
        BuzzerBeep(100);
      }else{
        Delayms(100);
      }
      //-----------------------------中途按取消鈕----------------------
      if (DriverFlag.CancelPress==1){ //按取消跳出迴圈
        DriverFlag.CancelPress=0;   //按鈕復位
        //DeleteLastMSG(&CTIMSGQueue); //64筆的版本取消時不刪除訊息
        BuzzerBeep(100);
        return 0;
      }
      //------------------------長按時將Queue全部刪除-----------------
      if ((DriverFlag.CancelLongPress==1)&&(DriverFlag.RDMode==0)){
        DriverFlag.CancelLongPress=0;   //按鈕復位
        DeleteAllCTIMSG(&CTIMSGQueue);
        BuzzerBeep(50);
        BuzzerBeep(50);
        BuzzerBeep(50);
        DriverFlag.ResetSystem=1; 
        return 0;
      }
      //--------------------------------------------------------------
    }
    
  }
  return 1;
}


void StartLine_Enter(){
  DriverFlag.Phone0Gateway1=1;
  DriverFlag.MicState=0;
  DriverFlag.PhoneBusy=0;
  DriverFlag.TentelOn=1;
  SetLEDState(&LED_NowIsHelp,500,500);  //傳輸閃爍
}

void StartLine_Exit(){
  DisableSpeaker();
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.PhoneBusy=0;
  SetLEDState(&LED_NowIsHelp,0,0);  //沒傳輸恆滅
}

void StartLine_Work(){
  if(Wait15SecToStart()==0) return; //如果15秒內有取消(回傳0)，則跳離此區
  
  unsigned char FaultCount=0;
  unsigned char Success;
//=================================================撥號流程  
  Tentel_WriteDefault(); //寫入國洋板預設值
  unsigned char DialRetry;
  if(DriverFlag.RDMode==1){
    DialRetry=1;
  }else{
    DialRetry=4;
  }  
  
  for(int i=0;i<DialRetry;i++){
    FaultCount++;
    Success=DataOut(i);
    if(Success==DS)break;
    TransferErr();
    Delayms(7000);    //若失敗，等5秒後再撥
  }
  if((FaultCount==DialRetry)&&(Success!=DS)){  //失敗四次的動作
    DeleteRetryData(&CTIMSGQueue);
    SendTextToUart(COM3,"CTIFAIL",7);  //傳送失敗送出此訊息
    CallError();
  }else{
    SendTextToUart(COM3,"CTISUCC",7);  //傳送成功送出此訊息
    CallSuccess();
  }
//=================================================  
  //-----------------------------中途按取消鈕----------------------
  if (DriverFlag.CancelPress==1){ //按取消跳出迴圈
    DriverFlag.CancelPress=0;   //按鈕復位
    //DeleteLastMSG(&CTIMSGQueue); //64筆的版本取消時不刪除訊息
    BuzzerBeep(100);
  }
  //------------------------長按時將Queue全部刪除-----------------
  if ((DriverFlag.CancelLongPress==1)&&(DriverFlag.RDMode==0)){
    DriverFlag.CancelLongPress=0;   //按鈕復位
    DeleteAllCTIMSG(&CTIMSGQueue);
    BuzzerBeep(50);
    BuzzerBeep(50);
    BuzzerBeep(50);
    DriverFlag.ResetSystem=1; 
  }
  //--------------------------------------------------------------
  Tentel_WriteDefault(); //寫入國洋板預設值
//=================================================       
  if(DriverFlag.RDMode==1){  //每次撥完強制重啟
      DriverFlag.ResetSystem=1;
      Delayms(10);  
  } 
  if(CTIMSGQueue.Length==0&&NeedRemoteSetup==0){  //若訊息都傳完了..就乾脆重開..確保穩定度
    //RDMode時不重開
    //if(DriverFlag.RDMode==0&&DriverFlag.ServicePress==0){
    if(DriverFlag.ServicePress==0){
      DriverFlag.ResetSystem=1;
      Delayms(10);
    }
  }
  
  GoToFlow(State_NormalStandBy);
}