#include "../TaipeiCity_A002_L.h"

void ServicePress(){
  if(A002State.State==State_Service){  //�ȪA�Ҧ��ɫ��ȪA�s�L��
    DriverFlag.ServicePress=0;  //�]���s�L�ġA�G�����P��
    return;                     //�D�ݾ��Ҧ������\�����T��
  }
  if(DriverFlag.RDMode==1)return; //�Y�ORDMODE�A�h�ȪA�s���@�ʧ@
  DriverFlag.CancelPress=1;
  SendEventToPC(9);
  CancelPress(); //�w��������U�����s���ʧ@
}

void CancelPress(){
  if(A002State.State==State_SystemCheck)return;  //�˴��Ҧ������\���UCancel�s
  DriverFlag.Phone0Gateway1=0;
  A002State.OnExit();
  Tentel_HangUp();
  if(DriverFlag.ServicePress==0)SendEventToPC(0);  //�]���s�����ȪA�s���U��..�|���ްʨ���,�ҥH�q�o�̰��ˬd
  GoToFlow(State_NormalStandBy);
}

void CancelLongPress(){
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.CancelLongPress=0;  //�]���s�L�ġA�G�����P��
    return;                     //�D�ݾ��Ҧ������\�����T��
  }
  SendEventToPC(10);
}

void GetRF(unsigned char ID){
  if(DriverFlag.RFBTIsErr==1){
    DriverFlag.RFBTIsErr=0;
    PutCTIMSG(&CTIMSGQueue,ID,CTIMSG_DeviceBTLow,EncodeNowDateTime(),0);
  }
  //========================================================��H�UMARK�����A�����K�N�㦳���ҫ�ç� Emergency_Flag�אּ1���\��
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
  //=======================================================��H�WMARK�����A�����K�N�㦳���ҫ�ç� Emergency_Flag�אּ1���\��
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.RFPress=0;  //�]���s�L�ġA�G�����P��
    return;                     //�D�ݾ��Ҧ������\�����T��
  }

  DriverFlag.RFPress=ID;
  SendEventToPC(ID);
}

void TestQueueSend(){
  //DeleteAllCTIMSG(&CTIMSGQueue);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayPowerErr,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayBTLow,EncodeNowDateTime(),0);
  //PutCTIMSG(&CTIMSGQueue,1,CTIMSG_DeviceBTLow,EncodeNowDateTime(),0);    //�Ĥ@���������`
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
//============================================================�ˬdQUEUE�O�_�w���A�Y���F�A�����\������ơA�u��@����
  if(CTIMSGQueue.Length!=CTIMessageQueueLength){
    SetLEDState(&LED_NowIsHelp,0,0);
  }
//============================================================���U���(�����K)
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
    //####################### �u���v�̰����ǰe52�T�� ######################
    //DeleteAllCTIMSG(&CTIMSGQueue);
    //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayCall,EncodeNowDateTime(),0); //����8�����T���A��l���ǿ�Ͳz���
    //GoToFlow(State_StartLine);
    //##################### �NFLASHROM���T����^QUEUE #####################
    GetQueueDataFromFlash((int *)&CTIMSGQueue);
    //####################### �u���v�̰����ҰʫȪA ########################
    DriverFlag.ServicePress=0;
    GoToFlow(State_Service);
    //#####################################################################
    return;
  }   
//============================================================�P����RFID  
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
//============================================================���U����
  if(DriverFlag.RFPress!=0){  
    unsigned char User=DriverFlag.RFPress;
    DriverFlag.RFPress=0;     //�_��

    if(SystemConfig_BatchTransfer<50){ //�S��Ʃγ浧�ǰe�u�ͤ@�n
      BuzzerBeep(100);
    }
    
    if (User==8){       
      //DriverFlag.ServicePress=1;  //����8���ȪA�A��l���ǿ�Ͳz���
      //DeleteAllCTIMSG(&CTIMSGQueue);
      //PutCTIMSG(&CTIMSGQueue,0,CTIMSG_GatewayCall,EncodeNowDateTime(),0); //����8�����T���A��l���ǿ�Ͳz���
      //GoToFlow(State_StartLine);
    }else{
      //unsigned char DataFind=MEADEV_GetDeviceData(User);  //�浧��}�ǿ�
      unsigned char DataFind=MEADEV_GetDeviceDataMulti(User);  //�h����}�ǿ�
      MEADEV_SetDeviceTime();
    
      if(DataFind==1){  
        if(SystemConfig_BatchTransfer>=50){ //�Y���妸�ǰe�N�ͤT�n
          for(int i=0;i<3;i++){
            Delayms(50);
            BuzzerBeep(50);
          }
        }

        if(SystemConfig_DataAutoDelete!=0)MEADEV_ClearFlash();
      
        if(QueueNeedSendImportantData()==1){  //���j�Ƥ~�ǰe
          GoToFlow(State_StartLine);
        }
      }
    }
    return;
  }
  
//============================================================���U�����s
  if(DriverFlag.CancelPress==1){
    DriverFlag.CancelPress=0;
    BuzzerBeep(100);
    return;
  }
//============================================================���U�����s
  if(DriverFlag.NeedReport==1){ 
    DriverFlag.NeedReport=0;
    GoToFlow(State_StartLine);
    return;
  }  
//============================================================���������s
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
//============================================================���U�A�ȶs 
  if(DriverFlag.ServicePress==1){
    DriverFlag.ServicePress=0;
    GoToFlow(State_Service);
    return;
  } 
//============================================================�t�Φ^��
  if(((SystemDateTime.SystemTotalHour-SystemAlarm.SystemReportStartTime)%SystemConfig_SystemReportContinue==0)&&
     (SystemDateTime.Second<5)&&(SystemDateTime.Minute==SystemConfig_FirstReportMinute)) {
    Delayms(1000);
    DriverFlag.KeepAllAlarm=1;   //�t�Φ^�����s
    PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
    GoToFlow(State_StartLine);
    return;
  }
//===========================================================�Ĥ@���t�Φ^��
  unsigned long FirstReportTime=EncodeDateTime(SystemConfig_FirstReportYear-2000,SystemConfig_FirstReportMonth,
                                                SystemConfig_FirstReportDate,SystemConfig_FirstReportHour,
                                                SystemConfig_FirstReportMinute);
  if(SystemConfig_FirstReport==1){
    if ((FirstReportTime==SystemDateTime.EncodeTime)&&(SystemDateTime.Second<5)){
      DriverFlag.KeepAllAlarm=1;   //�t�Φ^�����s
      Delayms(1000);
      PutCTIMSG(&CTIMSGQueue,0,CTIMSG_SystemReport,EncodeNowDateTime(),0);
      NeedSetupTime=1;
      GoToFlow(State_StartLine);
      return;    
    }
  }
//============================================================�x�a�Ұ�
  if(NowIsAlarm==1){  //�x������..�^��ݾ��Ҧ�
    //BuzzerBeep(100);
    GoToFlow(State_Alarm);
    return;
  }
//============================================================�t���ˬd
  if((SystemDateTime.Second==0)&&(SystemDateTime.SystemTotalMinute%SystemConfig_SystemCheckTimeout==0)){
    Delayms(1000);
    MEADEV_SetDeviceTime();
    GoToFlow(State_SystemCheck); 
    return;  
  }

}