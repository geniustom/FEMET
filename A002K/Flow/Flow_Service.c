#include "../TaipeiCity_A002_L.h"


unsigned char ServiceCallIndex;  //�ثe���ȪA�����էO

unsigned char PhoneIsPickup(){
  if ((P2IN&BIT6)!=0) 
    return  0;  //���_H�A�^��0
  else
    return  1;   //��UL�A�^��1
}

void Service_CallOut(){
  //==============================================�]�w�`���e�m����
  if(SystemConfig_CTINeedPreKey==1){      
    for(int kk=0;kk<8;kk++){
      if(SystemConfig_CTIPreKey[kk]==0xff)break;
      Tentel_SendKey(SystemConfig_CTIPreKey[kk]);
      //Tentel_SendDTMF(SystemConfig_CTIPreKey[kk]); <--�L�k���X
      Delayms(150);
    }
    Delayms(1500);
  }
  //==============================================�]�w�����էO
  unsigned char const *Num;
  switch(ServiceCallIndex){
    case 0: Num=SystemConfig_CTIHelpTel1; break;
    case 1: Num=SystemConfig_CTIHelpTel2; break;
    case 2: Num=SystemConfig_CTIHelpTel3; break;
    case 3: Num=SystemConfig_CTIHelpTel4; break;
  }
  //==============================================���o�����X��
  unsigned char CodeIndex=0;
  for (int i=0;i<16;i++){
    if(Num[i]!=0xff){ CodeIndex++;}
  }
  //==============================================���X���X
  Tentel_SetNumber(Num,CodeIndex);
  Delayms(150);
  Tentel_DialOut();
  //==============================================�֭pServiceCallIndex
  ServiceCallIndex++;
  ServiceCallIndex%=4;
  Delayms(3500);
}


void Service_Enter(){
  SetLEDState(&LED_NowIsHelp,500,0);  //�ǿ��G
  DriverFlag.Phone0Gateway1=0; //���m�q�ܽu(�P�ǿ餣�P)
  DriverFlag.MicState=1;
  DriverFlag.PhoneBusy=0;
  DriverFlag.TentelOn=1;
  DriverFlag.CancelPress=0; //�����������ا�L�_��
  Delayms(2000); //Delay �@��~��N�쥻ALWAYS�_�q����v��������`����CMD
}

void Service_Exit(){
  SetLEDState(&LED_NowIsHelp,0,0);  //�ǿ���
  DriverFlag.Phone0Gateway1=0;
  DriverFlag.MicState=0;
  DriverFlag.PhoneBusy=0;
  DriverFlag.TentelOn=0;
  Tentel_HangUp();
  Delayms(2000);
}

void Beep3TimesAndHangup(){  //�ͤT�n
  Tentel_HangUp();
  DisableSpeaker();
  for (int i=0;i<3;i++){
    BuzzerBeep(50);
    Delayms(50);
  }
}

unsigned char PhoneIsTake(unsigned int Delay){
  unsigned char Result=0;
  for(int i=0;i<Delay;i+=100){
    Delayms(100);
    //==============================================�ˬd�ܵ��O�_���n�A�Y���n�~�༷�X�h�A�S���n�ͤT�n
    if(PhoneIsPickup()!=0){
      Beep3TimesAndHangup();
      Result=1;
      break;
    }
  }
  return Result;
}

void Service_Work(){
  //==============================================�Y���e���b�q�T�A���N�q���_���b�A���ݤ@��A�@���ˬd�ܵ��O�_���_
  Tentel_HangUp();
  if(PhoneIsTake(1000)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================���_�ܵ����ݤ@��A�@���ˬd�ܵ��O�_���_
  GYTentel_State.DetDialTone=0;      //�_��
  Tentel_PickUp();
  if(PhoneIsTake(1000)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================���ݼ������A�Y�������켷�����A�o�X�T�n��
  if ((GYTentel_State.DetDialTone==1 || DriverFlag.NowIsDialTone==1)){
    GYTentel_State.DetDialTone=0;   //�_��
  }else{
    Beep3TimesAndHangup();
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================�}�ҳ�z,����0.5��A0.5���ˬd�ܵ��O�_���_
  EnableSpeaker(SystemConfig_SPK_Dial);
  if(PhoneIsTake(500)==1){
    GoToFlow(State_NormalStandBy);
    return;
  }
  //==============================================�Y����F�~����
  Service_CallOut();
  EnableSpeaker(SystemConfig_SPK_Talk);
  
  unsigned char PhoneAlreadyPickup; //�����b�����e�A�ܱ�O�_�w�g���_
  unsigned char DTMFData;           //�������O�_�e�X*��#
  GYTentel_State.ISBusy=0;          //���������e��v��X��BUSY CMD
  while((DriverFlag.CancelPress==0)||(DriverFlag.PhoneBusy==1)){
    //============================================================================�����O�_���U* (�}�_��z)
    DTMFData=Tentel_GetDTMFDigi();
    if(DTMFData==0xfa){ //*
      AddVoice();
      DriverFlag.MicState=1;
    }
    //============================================================================�����ܵ����U# (������z)
    if(DTMFData==0xf3){ //#
      SubVoice();
      DriverFlag.MicState=1;
    }
    //============================================================================�����ܵ��O�_�b������~���_�A�Y�O�A����MIC�PSPK�A�H�ΰ�v�ܾ�
    if(PhoneIsPickup()==1&&PhoneAlreadyPickup==0){
      Tentel_HangUp();
      DisableSpeaker();
      DriverFlag.MicState=0;    
    }
    //============================================================================�����ܵ��O�_���_
    PhoneAlreadyPickup=PhoneIsPickup(); //�����b�����e�A�ܱ�O�_�w�g���_
    Delayms(50);  //����50ms
    //============================================================================�����ܵ��O�_��U
    if(PhoneAlreadyPickup==1&&PhoneIsPickup()==0){ //�N���_�S��U,�۰ʱ��_�^��N�����A
       break;
    }
    //============================================================================L�O���u����
    if(DriverFlag.PhoneBusy==1){
      DriverFlag.PhoneBusy=0;
      break;
    }
    //============================================================================��v���u����
    if(GYTentel_State.ISBusy==1){
      GYTentel_State.ISBusy=0;
      break;
    }
  }
  
  Tentel_HangUp();
  DisableSpeaker();
  BuzzerBeep(100);
  GoToFlow(State_NormalStandBy);
}