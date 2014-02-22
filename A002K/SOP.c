#include "DriverLib/DriverLib.h"
#include "TENTEL/Tentel.h"
#include "TaipeiCity_A002_L.h"

void SOPMode1(){
    DriverFlag.Phone0Gateway1=0; //���m�q�ܽu(�P�ǿ餣�P)
    DriverFlag.MicState=0;
    DriverFlag.PhoneBusy=0;
    DriverFlag.RDMode=1;
    DriverFlag.TentelOn=1;      //����vALWAYS�����ɡA�n�N�����}
    //==============================================�}�ҳ�z
    DriverFlag.SpeakState=1;
    EnableSpeaker(SystemConfig_SPK_Talk);
    Delayms(10);
    //==============================================���ݼ�����
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
      //============================================================================�����O�_���U* (�}�_��z)
      unsigned char DTMFData=Tentel_GetDTMFDigi();
      if(DTMFData==0xfa){ //*
        AddVoice();
        DriverFlag.MicState=1;
      }
      //============================================================================�����ܵ����U# (������z)
      if(DTMFData==0xf3){ //#
        SubVoice();
        DriverFlag.MicState=1;
      }
      //============================================================================��������
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
  if ((P1IN&CheckButton)==CheckButton){  //�}���ɭY���U�����s�A�Ұ�SOP�Ҧ�
    SetLEDState(&LED_NowIsHelp,1000,0); //�ǿ�LED��G
    BuzzerBeep(3000);
    //================================����3���A�˹���䱡�p
    switch (P1IN&CheckButton){
      case (KEY_Help | KEY_Cancel):     //�Y���������s�ARESET�b���A�դ@��
        DriverFlag.ResetSystem=1; break;
      case KEY_Help:                    //��H�i�JSOP�Ҧ�
        SOPMode1();               break;
      case KEY_Cancel:                  //��C�i�JDEBUG�Ҧ�
        SOPMode2();               break;  
    }
    //�ƻ򳣨S���A�p�������}���y�{
  }
}