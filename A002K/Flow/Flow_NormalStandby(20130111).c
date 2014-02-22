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
  if(A002State.State!=State_NormalStandBy){
    DriverFlag.RFPress=0;  //�]���s�L�ġA�G�����P��
    return;                     //�D�ݾ��Ҧ������\�����T��
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
//============================================================���U����
  if(DriverFlag.RFPress!=0){  
    unsigned char User=DriverFlag.RFPress;
    DriverFlag.RFPress=0;     //�_��

    if(SystemConfig_BatchTransfer<50){ //�S��Ʃγ浧�ǰe�u�ͤ@�n
      BuzzerBeep(100);
    }
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