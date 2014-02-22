#include "../TaipeiCity_A002_L.h"

#define StageTimeout 3000

unsigned char DTMFCMD_List[14];
unsigned char NeedRemoteSetup;
unsigned char NeedSetupTime=1;



void SendStopCode(unsigned char NeedRefreshTime){ //�e�X14�X9
  unsigned char StopCode1[14]={9,9,9,9,9,9,9,9,9,9,9,9,9,9};
  unsigned char StopCode2[14]={8,8,8,8,8,8,8,8,8,8,8,8,8,8};
  if(NeedRefreshTime==0){
    Tentel_SendDTMFList(StopCode1,14);     //Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET���n�Ԫ�
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(StopCode1[i]);
      Delayms(100);  
    }
*/
  }else{
    Tentel_SendDTMFList(StopCode2,14);    //Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET���n�Ԫ�
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(StopCode2[i]);
      Delayms(100);  
    }
*/
  }
}

//�^��1:�b�u�w�ɶ�������FDTMF �^��0:������
unsigned char WaitForDTMF(unsigned long TimeOut,unsigned long DelayAfterGetDTMF,unsigned char DTMF){ 

  unsigned int BreakWaiting=0;
  unsigned long WaitTime=0;
  
  Delayms(300);            //�קK��LTone���٨S����
  Tentel_ClearDTMFBuf();   //�M��BUFFER
  
  while (BreakWaiting==0 && WaitTime<=TimeOut){
    Delayms(100); 
    WaitTime+=100;
    if(Tentel_GetDTMFDigi()==3){
      BreakWaiting=1;
      Delayms(DelayAfterGetDTMF);
      Tentel_ClearDTMFBuf();   //�M��BUFFER
      return 1;
    }
  }
  Tentel_ClearDTMFBuf();   //�M��BUFFER
  return 0;
}

void SetupDTMFConfig(){
  unsigned char *PTR=(unsigned char *)SystemConfig_Addr;
  unsigned char ConfigSTR[256];
  for(unsigned int i=0;i<256;i++){
    ConfigSTR[i]=*PTR;
    PTR++;
  }
//=========================================================���Ĵ���
  if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x01)){   
    unsigned char Grouop=DTMFCMD_List[3];
    unsigned char Addr=0x30+(Grouop-1)*3;  //0x30~0x32,0x33~0x35,0x36~0x38,0x39~0x3A
    
    unsigned char Hour=DTMFCMD_List[4]*10+DTMFCMD_List[5];
    unsigned char Minute=DTMFCMD_List[6]*10+DTMFCMD_List[7];
    unsigned char Continue=DTMFCMD_List[8]*10+DTMFCMD_List[9];
    
    ConfigSTR[Addr]=Hour;
    ConfigSTR[Addr+1]=Minute;
    ConfigSTR[Addr+2]=Continue;
  }
//=========================================================���ݮɶ���s
  if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x00)){
    unsigned int Y=2000+DTMFCMD_List[2]*10+DTMFCMD_List[3];
    unsigned char DateTimeSource[7];
    DateTimeSource[0]=(unsigned char)(Y%256);                 //�~�C
    DateTimeSource[1]=(unsigned char)(Y>>8);                  //�~��
    DateTimeSource[2]=DTMFCMD_List[4]*10+DTMFCMD_List[5];     //��
    DateTimeSource[3]=DTMFCMD_List[6]*10+DTMFCMD_List[7];     //��
    DateTimeSource[4]=DTMFCMD_List[8]*10+DTMFCMD_List[9];     //��
    DateTimeSource[5]=DTMFCMD_List[10]*10+DTMFCMD_List[11];   //��
    DateTimeSource[6]=DTMFCMD_List[12]*10+DTMFCMD_List[13];   //��
    unsigned char Addr=0xE0;
    for(int i=0;i<7;i++){
      ConfigSTR[Addr+i]=DateTimeSource[i];
    }
    SetDefaultTime(Y,DateTimeSource[2],DateTimeSource[3],
                   DateTimeSource[4],DateTimeSource[5],DateTimeSource[6]);
    SETRTC_To_S35390();
  }
//=========================================================�t�Φ^��
  if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x02)){
    unsigned int Y=2000+DTMFCMD_List[2]*10+DTMFCMD_List[3];
    unsigned char ReportSource[7];
    ReportSource[0]=(unsigned char)(Y%256);                                     //�~�C
    ReportSource[1]=(unsigned char)(Y>>8);                                      //�~��
    ReportSource[2]=DTMFCMD_List[4]*10+DTMFCMD_List[5];                         //��
    ReportSource[3]=DTMFCMD_List[6]*10+DTMFCMD_List[7];                         //��
    ReportSource[4]=DTMFCMD_List[8]*10+DTMFCMD_List[9];                         //�� 
    ReportSource[5]=DTMFCMD_List[10]*100+DTMFCMD_List[11]*10+DTMFCMD_List[12];  //���j
    ReportSource[6]=DTMFCMD_List[13];                                           //�}��
    unsigned char Addr=0x10;
    for(int i=0;i<6;i++){
      ConfigSTR[Addr+i]=ReportSource[i];
    }
    if(ReportSource[6]==0){ConfigSTR[Addr+5]=0;}   //�}���Y�����A�h����ɶ��j���אּ0
  }
//=========================================================�ǿ�/�ȪA�q�ܳ]�w
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x03||DTMFCMD_List[1]==0x04)){
      unsigned char TelClass=DTMFCMD_List[1]*10+DTMFCMD_List[2];
      unsigned char Addr=0;
      switch(TelClass){
        case 31:  Addr=0x60;  break;
        case 32:  Addr=0x70;  break;
        case 33:  Addr=0x80;  break;
        case 34:  Addr=0x90;  break;
        case 41:  Addr=0xA0;  break;
        case 42:  Addr=0xB0;  break;
        case 43:  Addr=0xC0;  break;
        case 44:  Addr=0xD0;  break;  
      }
      for(int i=0;i<16;i++){  ConfigSTR[Addr+i]=0xff; }
      for(int i=0;i<11;i++){
        ConfigSTR[Addr+i]=DTMFCMD_List[3+i];
        if(ConfigSTR[Addr+i]>9){ConfigSTR[Addr+i]=0xff;}
      }
    }
//=========================================================�����}���]�w
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x05)){
      if(DTMFCMD_List[2]==0x00){      ConfigSTR[0x41]|=0x80;      }else{        ConfigSTR[0x41]&=~(0x80);      }
      if(DTMFCMD_List[3]==0x00){      ConfigSTR[0x43]|=0x80;      }else{        ConfigSTR[0x43]&=~(0x80);      }
      if(DTMFCMD_List[4]==0x00){      ConfigSTR[0x45]|=0x80;      }else{        ConfigSTR[0x45]&=~(0x80);      }
      if(DTMFCMD_List[5]==0x00){      ConfigSTR[0x47]|=0x80;      }else{        ConfigSTR[0x47]&=~(0x80);      }
      if(DTMFCMD_List[6]==0x00){      ConfigSTR[0x49]|=0x80;      }else{        ConfigSTR[0x49]&=~(0x80);      }
      if(DTMFCMD_List[7]==0x00){      ConfigSTR[0x4B]|=0x80;      }else{        ConfigSTR[0x4B]&=~(0x80);      }
      if(DTMFCMD_List[8]==0x00){      ConfigSTR[0x4D]|=0x80;      }else{        ConfigSTR[0x4D]&=~(0x80);      }
      if(DTMFCMD_List[9]==0x00){      ConfigSTR[0x4F]|=0x80;      }else{        ConfigSTR[0x4F]&=~(0x80);      }
    }
//=========================================================�������X�]�w
    unsigned int RFBCode1,RFBCode2;
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x06)&&(DTMFCMD_List[2]==0x01)&&(DTMFCMD_List[7]==0x02)){
      RFBCode1=((ConfigSTR[0x41]*256+ConfigSTR[0x40])&0x8000)+(DTMFCMD_List[3]*1000)+(DTMFCMD_List[4]*100)+(DTMFCMD_List[5]*10)+(DTMFCMD_List[6]);
      RFBCode2=((ConfigSTR[0x43]*256+ConfigSTR[0x42])&0x8000)+(DTMFCMD_List[8]*1000)+(DTMFCMD_List[9]*100)+(DTMFCMD_List[10]*10)+(DTMFCMD_List[11]);
      ConfigSTR[0x40]=RFBCode1 % 256;
      ConfigSTR[0x41]=RFBCode1 / 256;
      ConfigSTR[0x42]=RFBCode2 % 256;
      ConfigSTR[0x43]=RFBCode2 / 256;
    }
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x06)&&(DTMFCMD_List[2]==0x03)&&(DTMFCMD_List[7]==0x04)){
      RFBCode1=((ConfigSTR[0x45]*256+ConfigSTR[0x44])&0x8000)+(DTMFCMD_List[3]*1000)+(DTMFCMD_List[4]*100)+(DTMFCMD_List[5]*10)+(DTMFCMD_List[6]);
      RFBCode2=((ConfigSTR[0x47]*256+ConfigSTR[0x46])&0x8000)+(DTMFCMD_List[8]*1000)+(DTMFCMD_List[9]*100)+(DTMFCMD_List[10]*10)+(DTMFCMD_List[11]);
      ConfigSTR[0x44]=RFBCode1 % 256;
      ConfigSTR[0x45]=RFBCode1 / 256;
      ConfigSTR[0x46]=RFBCode2 % 256;
      ConfigSTR[0x47]=RFBCode2 / 256;
    }
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x06)&&(DTMFCMD_List[2]==0x05)&&(DTMFCMD_List[7]==0x06)){
      RFBCode1=((ConfigSTR[0x49]*256+ConfigSTR[0x48])&0x8000)+(DTMFCMD_List[3]*1000)+(DTMFCMD_List[4]*100)+(DTMFCMD_List[5]*10)+(DTMFCMD_List[6]);
      RFBCode2=((ConfigSTR[0x4B]*256+ConfigSTR[0x4A])&0x8000)+(DTMFCMD_List[8]*1000)+(DTMFCMD_List[9]*100)+(DTMFCMD_List[10]*10)+(DTMFCMD_List[11]);
      ConfigSTR[0x48]=RFBCode1 % 256;
      ConfigSTR[0x49]=RFBCode1 / 256;
      ConfigSTR[0x4A]=RFBCode2 % 256;
      ConfigSTR[0x4B]=RFBCode2 / 256;
    }
    if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x06)&&(DTMFCMD_List[2]==0x07)&&(DTMFCMD_List[7]==0x08)){
      RFBCode1=((ConfigSTR[0x4D]*256+ConfigSTR[0x4C])&0x8000)+(DTMFCMD_List[3]*1000)+(DTMFCMD_List[4]*100)+(DTMFCMD_List[5]*10)+(DTMFCMD_List[6]);
      RFBCode2=((ConfigSTR[0x4F]*256+ConfigSTR[0x4E])&0x8000)+(DTMFCMD_List[8]*1000)+(DTMFCMD_List[9]*100)+(DTMFCMD_List[10]*10)+(DTMFCMD_List[11]);
      ConfigSTR[0x4C]=RFBCode1 % 256;
      ConfigSTR[0x4D]=RFBCode1 / 256;
      ConfigSTR[0x4E]=RFBCode2 % 256;
      ConfigSTR[0x4F]=RFBCode2 / 256;
    }
//========================================================= 
  _DINT();
  flash_erase_multi_segments(SystemConfig_Addr,1);
  flash_write_Block(SystemConfig_Addr,ConfigSTR,256);
  _EINT();
//=========================================================���s���J�]�w��
  InitAllAlarm();
}


unsigned char SendAllCTIMSG(CTIMessageQueue *CQ){   //���楻FUNCTION���e���T�w�ثe���PCTI�D���B��ONLINE���A
  while(CTIMSGQueue.Length>0){
    Delayms(StageTimeout);  
    CTIMessage CTIM=GetQueueNode(CQ);
    //=========================�eQUEUE DATA STAGE1========================
    Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET���n�Ԫ�
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(CTIM.MessageStage1[i]);
      Delayms(100);  
    }
*/
    if(WaitForDTMF(10000,StageTimeout,3)==0) return 0;    //10��������3�N���}
    //=========================�eQUEUE DATA STAGE2========================
    Tentel_SendDTMFList(CTIM.MessageStage2,14);  //TONNET���n�Ԫ�
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(CTIM.MessageStage2[i]);
      Delayms(100);
    }
*/
    //========================�e����qQUEUE�R��===========================      
    if(WaitForDTMF(10000,StageTimeout,3)==0){ //10��������3�N����..�Y����F�N�RQUEUE
      return 0;
    }else{
      DeleteCTIMSG(CQ);      //�ǰe���\�qQUEUE�R���A�öi��U�@�^�X�ǰe      
    }
  }
  return DS;
}


unsigned char GetCTIData(unsigned char *Data,unsigned int Length){
  unsigned int TimeOut=0;
  unsigned char DTMFCount=0;
  for(int k=0;k<Length;k++){  //�̭��̤֭n100ms..���h����W�L900ms
    TimeOut=0;
    Delayms(100);            //�ʽ� (�]���e3����Ĥ@�X���W�N�ӡA�ҥH����DELAY)
    Tentel_ClearDTMFBuf();   //�M��BUFFER 

    while((GYTentel_State.DetDTMF==0)&&(TimeOut<900)){
      Delayms(4);   //�L��
      TimeOut+=4;
      if(TimeOut>=900){
        return 0;
      }
    }
    if(GYTentel_State.DetDTMF==1){ 
      Data[DTMFCount]=Tentel_GetDTMFDigi();
      DTMFCount++;
    }
  }  
  return DTMFCount;
}

unsigned char DataIn(){
  unsigned char SendSuccess=0;
  while(SendSuccess==0){
    Delayms(StageTimeout);  //�t�X�q��Ԫ��ɶ�
    Tentel_SendDTMF(3);
    Delayms(1000);           //�]�����P�q�H���гt�סA�q0.6��~3��Ҧ��i��..���ӭn�令���ݳ]�w (��600) 
    if (GetCTIData(DTMFCMD_List,14)==14){
      SetupDTMFConfig();  //�g�J�]�w�Ȩ�FLASH
      Delayms(1000);
    }else{
      Delayms(1000);
      break;
    }
    //================================�����]�����������X,�b�ˬd�����O�_�O14�X9,�Y���O�A�A�אּ0
    SendSuccess=1;
    for(int j=0;j<14;j++){
      if(DTMFCMD_List[j]!=9){SendSuccess=0;break;}
    }    
  }
  if(SendSuccess==1){
//===================================�s�N�O����t���B
    EnableSpeaker(SystemConfig_SPK_Voice);
    Delayms(StageTimeout);
    Tentel_SendDTMF(3); //�e3�i�DIVR�i�H����TTS�y��(�t�γ]�w����)
    Delayms(500);       
//===================================
    if(WaitForDTMF(20000,StageTimeout,3)==0) return 0;  //����TTS(�t�γ]�w����)�õ���3
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    Delayms(100);  //����zDELAY
    Tentel_SendDTMF(3); //�e3�i�DIVR�i�H����DB��TTS�y��
    Delayms(100);  //�}��zDELAY
    EnableSpeaker(SystemConfig_SPK_Voice);
    long IVRTimeOut=3000; //300��
    while((Tentel_GetDTMFDigi()!=3)&&(DriverFlag.PhoneBusy==0)&&IVRTimeOut>0){//����3���T��,���ݼ���y��,��������
      Tentel_ClearDTMFBuf();   //�M��BUFFER
      IVRTimeOut--;
      Delayms(100);
    } 
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    NeedRemoteSetup=0;
    Delayms(500);
    for(int i=0;i<10;i++){
      Tentel_SendDTMF(3);
      Delayms(500);  //����᱾�_
    }
    return 1;
  }else{
    return 0;       //�p�G�S����14�X9�N����o��..�N��ǰe����
  }
}



unsigned char DataOut(unsigned char TelID){
  //==============================================�}�ҳ�z
  EnableSpeaker(SystemConfig_SPK_Dial );
  Delayms(10);
  //==============================================���ݼ�����
  Tentel_PickUp();
  Delayms(2000);

  if (GYTentel_State.DetDialTone==1 || DriverFlag.NowIsDialTone==1){
    GYTentel_State.DetDialTone=0;           //�_��
  }else{
    return 0;
  }

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
  switch(TelID){
    case 0: Num=SystemConfig_CTIDataTel1; break;
    case 1: Num=SystemConfig_CTIDataTel2; break;
    case 2: Num=SystemConfig_CTIDataTel3; break;
    case 3: Num=SystemConfig_CTIDataTel4; break;
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
  for(int i=0;i<CodeIndex;i++){
    Delayms(300);
  }
  if(WaitForDTMF(1000*SystemConfig_ToneTimeout,StageTimeout,3)==0) return 0;
  if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
  //==============================================�e�XMSG QUEUE�������
  if(SendAllCTIMSG(&CTIMSGQueue)==0)return 0;
  //==============================================�e�X�����X
  NeedSetupTime=1;
  SendStopCode(NeedSetupTime);
  if(WaitForDTMF(10000,0,3)==1){
    //==============================================����"��ƶǰe����"�y��
    EnableSpeaker(SystemConfig_SPK_Voice);
    if(WaitForDTMF(20000,StageTimeout,3)==0){
      if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
      return 0;
    }
    //==============================================���o�ݷ|�O�_�n�������
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    NeedRemoteSetup=1;
    return DataIn();
  }else{
    return 0;
  }
}
