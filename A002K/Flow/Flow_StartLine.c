#include "../TaipeiCity_A002_L.h"


void TransferErr(){
  for(int i=0;i<10;i++){
    BuzzerBeep(50);
    Delayms(50);
  }
  Tentel_HangUp();
}

void CallSuccess(){
  SetLEDState(&LED_HelpError,0,0);     //���\���
  Tentel_HangUp();
  for(int i=0;i<7;i++){
    BuzzerBeep(100);
    Delayms(100);
  }
}

void CallError(){ 
  SetLEDState(&LED_HelpError,500,0);     //���ѫ�G
  Tentel_HangUp();
  Delayms(100);
  BuzzerBeep(2000);
}

unsigned char Wait15SecToStart(){
  unsigned char BeepCount;  //RD MODE�T5�n,�DRD MODE�T15�n
  if(DriverFlag.RDMode==1){
    BeepCount=5;
  }else{
    BeepCount=15;
  }
    
  for (int i=0;i<BeepCount;i++){
      //-----------------------------�C�ͤ@�nŪ���@����v�]�w��--------
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
    for(int j=0;j<10;j++){//2s��̭��u�n�s0.1��N�n
      if((j==0)&&(i%2==0)){
        BuzzerBeep(100);
      }else{
        Delayms(100);
      }
      //-----------------------------���~�������s----------------------
      if (DriverFlag.CancelPress==1){ //���������X�j��
        DriverFlag.CancelPress=0;   //���s�_��
        //DeleteLastMSG(&CTIMSGQueue); //64�������������ɤ��R���T��
        BuzzerBeep(100);
        return 0;
      }
      //------------------------�����ɱNQueue�����R��-----------------
      if ((DriverFlag.CancelLongPress==1)&&(DriverFlag.RDMode==0)){
        DriverFlag.CancelLongPress=0;   //���s�_��
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
  SetLEDState(&LED_NowIsHelp,500,500);  //�ǿ�{�{
}

void StartLine_Exit(){
  DisableSpeaker();
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.PhoneBusy=0;
  SetLEDState(&LED_NowIsHelp,0,0);  //�S�ǿ���
}

void StartLine_Work(){
  if(Wait15SecToStart()==0) return; //�p�G15��������(�^��0)�A�h��������
  
  unsigned char FaultCount=0;
  unsigned char Success;
//=================================================�����y�{  
  Tentel_WriteDefault(); //�g�J��v�O�w�]��
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
    Delayms(7000);    //�Y���ѡA��5���A��
  }
  if((FaultCount==DialRetry)&&(Success!=DS)){  //���ѥ|�����ʧ@
    DeleteRetryData(&CTIMSGQueue);
    SendTextToUart(COM3,"CTIFAIL",7);  //�ǰe���Ѱe�X���T��
    CallError();
  }else{
    SendTextToUart(COM3,"CTISUCC",7);  //�ǰe���\�e�X���T��
    CallSuccess();
  }
//=================================================  
  //-----------------------------���~�������s----------------------
  if (DriverFlag.CancelPress==1){ //���������X�j��
    DriverFlag.CancelPress=0;   //���s�_��
    //DeleteLastMSG(&CTIMSGQueue); //64�������������ɤ��R���T��
    BuzzerBeep(100);
  }
  //------------------------�����ɱNQueue�����R��-----------------
  if ((DriverFlag.CancelLongPress==1)&&(DriverFlag.RDMode==0)){
    DriverFlag.CancelLongPress=0;   //���s�_��
    DeleteAllCTIMSG(&CTIMSGQueue);
    BuzzerBeep(50);
    BuzzerBeep(50);
    BuzzerBeep(50);
    DriverFlag.ResetSystem=1; 
  }
  //--------------------------------------------------------------
  Tentel_WriteDefault(); //�g�J��v�O�w�]��
//=================================================       
  if(DriverFlag.RDMode==1){  //�C�������j���
      DriverFlag.ResetSystem=1;
      Delayms(10);  
  } 
  if(CTIMSGQueue.Length==0&&NeedRemoteSetup==0){  //�Y�T�����ǧ��F..�N���ܭ��}..�T�Oí�w��
    //RDMode�ɤ����}
    //if(DriverFlag.RDMode==0&&DriverFlag.ServicePress==0){
    if(DriverFlag.ServicePress==0){
      DriverFlag.ResetSystem=1;
      Delayms(10);
    }
  }
  
  GoToFlow(State_NormalStandBy);
}