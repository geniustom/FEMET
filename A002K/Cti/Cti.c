#include "../TaipeiCity_A002_L.h"

#define StageTimeout 3000

unsigned char DTMFCMD_List[14];
unsigned char NeedRemoteSetup;
unsigned char NeedSetupTime=1;



void SendStopCode(unsigned char NeedRefreshTime){ //送出14碼9
  unsigned char StopCode1[14]={9,9,9,9,9,9,9,9,9,9,9,9,9,9};
  unsigned char StopCode2[14]={8,8,8,8,8,8,8,8,8,8,8,8,8,8};
  if(NeedRefreshTime==0){
    Tentel_SendDTMFList(StopCode1,14);     //Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET說要拉長
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(StopCode1[i]);
      Delayms(100);  
    }
*/
  }else{
    Tentel_SendDTMFList(StopCode2,14);    //Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET說要拉長
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(StopCode2[i]);
      Delayms(100);  
    }
*/
  }
}

//回傳1:在只定時間內等到了DTMF 回傳0:等不到
unsigned char WaitForDTMF(unsigned long TimeOut,unsigned long DelayAfterGetDTMF,unsigned char DTMF){ 

  unsigned int BreakWaiting=0;
  unsigned long WaitTime=0;
  
  Delayms(300);            //避免其他Tone音還沒結束
  Tentel_ClearDTMFBuf();   //清除BUFFER
  
  while (BreakWaiting==0 && WaitTime<=TimeOut){
    Delayms(100); 
    WaitTime+=100;
    if(Tentel_GetDTMFDigi()==3){
      BreakWaiting=1;
      Delayms(DelayAfterGetDTMF);
      Tentel_ClearDTMFBuf();   //清除BUFFER
      return 1;
    }
  }
  Tentel_ClearDTMFBuf();   //清除BUFFER
  return 0;
}

void SetupDTMFConfig(){
  unsigned char *PTR=(unsigned char *)SystemConfig_Addr;
  unsigned char ConfigSTR[256];
  for(unsigned int i=0;i<256;i++){
    ConfigSTR[i]=*PTR;
    PTR++;
  }
//=========================================================用藥提醒
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
//=========================================================遠端時間更新
  if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x00)){
    unsigned int Y=2000+DTMFCMD_List[2]*10+DTMFCMD_List[3];
    unsigned char DateTimeSource[7];
    DateTimeSource[0]=(unsigned char)(Y%256);                 //年低
    DateTimeSource[1]=(unsigned char)(Y>>8);                  //年高
    DateTimeSource[2]=DTMFCMD_List[4]*10+DTMFCMD_List[5];     //月
    DateTimeSource[3]=DTMFCMD_List[6]*10+DTMFCMD_List[7];     //日
    DateTimeSource[4]=DTMFCMD_List[8]*10+DTMFCMD_List[9];     //時
    DateTimeSource[5]=DTMFCMD_List[10]*10+DTMFCMD_List[11];   //分
    DateTimeSource[6]=DTMFCMD_List[12]*10+DTMFCMD_List[13];   //秒
    unsigned char Addr=0xE0;
    for(int i=0;i<7;i++){
      ConfigSTR[Addr+i]=DateTimeSource[i];
    }
    SetDefaultTime(Y,DateTimeSource[2],DateTimeSource[3],
                   DateTimeSource[4],DateTimeSource[5],DateTimeSource[6]);
    SETRTC_To_S35390();
  }
//=========================================================系統回報
  if((DTMFCMD_List[0]==0xfa)&&(DTMFCMD_List[1]==0x02)){
    unsigned int Y=2000+DTMFCMD_List[2]*10+DTMFCMD_List[3];
    unsigned char ReportSource[7];
    ReportSource[0]=(unsigned char)(Y%256);                                     //年低
    ReportSource[1]=(unsigned char)(Y>>8);                                      //年高
    ReportSource[2]=DTMFCMD_List[4]*10+DTMFCMD_List[5];                         //月
    ReportSource[3]=DTMFCMD_List[6]*10+DTMFCMD_List[7];                         //日
    ReportSource[4]=DTMFCMD_List[8]*10+DTMFCMD_List[9];                         //時 
    ReportSource[5]=DTMFCMD_List[10]*100+DTMFCMD_List[11]*10+DTMFCMD_List[12];  //間隔
    ReportSource[6]=DTMFCMD_List[13];                                           //開關
    unsigned char Addr=0x10;
    for(int i=0;i<6;i++){
      ConfigSTR[Addr+i]=ReportSource[i];
    }
    if(ReportSource[6]==0){ConfigSTR[Addr+5]=0;}   //開關若關掉，則持續時間強制更改為0
  }
//=========================================================傳輸/客服電話設定
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
//=========================================================壓扣開關設定
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
//=========================================================壓扣號碼設定
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
//=========================================================重新載入設定值
  InitAllAlarm();
}


unsigned char SendAllCTIMSG(CTIMessageQueue *CQ){   //執行本FUNCTION之前須確定目前正與CTI主機處於ONLINE狀態
  while(CTIMSGQueue.Length>0){
    Delayms(StageTimeout);  
    CTIMessage CTIM=GetQueueNode(CQ);
    //=========================送QUEUE DATA STAGE1========================
    Tentel_SendDTMFList(CTIM.MessageStage1,14);  //TONNET說要拉長
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(CTIM.MessageStage1[i]);
      Delayms(100);  
    }
*/
    if(WaitForDTMF(10000,StageTimeout,3)==0) return 0;    //10秒內等不到3就離開
    //=========================送QUEUE DATA STAGE2========================
    Tentel_SendDTMFList(CTIM.MessageStage2,14);  //TONNET說要拉長
/*
    for(int i=0;i<14;i++){
      Tentel_SendDTMF(CTIM.MessageStage2[i]);
      Delayms(100);
    }
*/
    //========================送完後從QUEUE刪除===========================      
    if(WaitForDTMF(10000,StageTimeout,3)==0){ //10秒內等不到3就失敗..若等到了就刪QUEUE
      return 0;
    }else{
      DeleteCTIMSG(CQ);      //傳送成功從QUEUE刪除，並進行下一回合傳送      
    }
  }
  return DS;
}


unsigned char GetCTIData(unsigned char *Data,unsigned int Length){
  unsigned int TimeOut=0;
  unsigned char DTMFCount=0;
  for(int k=0;k<Length;k++){  //裡面最少要100ms..做多不能超過900ms
    TimeOut=0;
    Delayms(100);            //粗調 (因為送3之後第一碼馬上就來，所以不需DELAY)
    Tentel_ClearDTMFBuf();   //清除BUFFER 

    while((GYTentel_State.DetDTMF==0)&&(TimeOut<900)){
      Delayms(4);   //微調
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
    Delayms(StageTimeout);  //配合通航拉長時間
    Tentel_SendDTMF(3);
    Delayms(1000);           //因應不同電信機房速度，從0.6秒~3秒皆有可能..未來要改成遠端設定 (原600) 
    if (GetCTIData(DTMFCMD_List,14)==14){
      SetupDTMFConfig();  //寫入設定值到FLASH
      Delayms(1000);
    }else{
      Delayms(1000);
      break;
    }
    //================================先假設此筆為結束碼,在檢查中間是否是14碼9,若不是，再改為0
    SendSuccess=1;
    for(int j=0;j<14;j++){
      if(DTMFCMD_List[j]!=9){SendSuccess=0;break;}
    }    
  }
  if(SendSuccess==1){
//===================================新就板韌體差異處
    EnableSpeaker(SystemConfig_SPK_Voice);
    Delayms(StageTimeout);
    Tentel_SendDTMF(3); //送3告訴IVR可以撥放TTS語音(系統設定完成)
    Delayms(500);       
//===================================
    if(WaitForDTMF(20000,StageTimeout,3)==0) return 0;  //撥放TTS(系統設定完成)並等待3
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    Delayms(100);  //關喇叭DELAY
    Tentel_SendDTMF(3); //送3告訴IVR可以撥放DB的TTS語音
    Delayms(100);  //開喇叭DELAY
    EnableSpeaker(SystemConfig_SPK_Voice);
    long IVRTimeOut=3000; //300秒
    while((Tentel_GetDTMFDigi()!=3)&&(DriverFlag.PhoneBusy==0)&&IVRTimeOut>0){//接收3的訊息,等待播放語音,忙音掛掉
      Tentel_ClearDTMFBuf();   //清除BUFFER
      IVRTimeOut--;
      Delayms(100);
    } 
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    NeedRemoteSetup=0;
    Delayms(500);
    for(int i=0;i<10;i++){
      Tentel_SendDTMF(3);
      Delayms(500);  //ㄧ秒後掛斷
    }
    return 1;
  }else{
    return 0;       //如果沒收到14碼9就跳到這裡..代表傳送失敗
  }
}



unsigned char DataOut(unsigned char TelID){
  //==============================================開啟喇叭
  EnableSpeaker(SystemConfig_SPK_Dial );
  Delayms(10);
  //==============================================等待撥號音
  Tentel_PickUp();
  Delayms(2000);

  if (GYTentel_State.DetDialTone==1 || DriverFlag.NowIsDialTone==1){
    GYTentel_State.DetDialTone=0;           //復位
  }else{
    return 0;
  }

  //==============================================設定總機前置撥號
  if(SystemConfig_CTINeedPreKey==1){      
    for(int kk=0;kk<8;kk++){
      if(SystemConfig_CTIPreKey[kk]==0xff)break;
      Tentel_SendKey(SystemConfig_CTIPreKey[kk]);
      //Tentel_SendDTMF(SystemConfig_CTIPreKey[kk]); <--無法撥碼
      Delayms(150);
    }
    Delayms(1500);
  }
  //==============================================設定撥號組別
  unsigned char const *Num;
  switch(TelID){
    case 0: Num=SystemConfig_CTIDataTel1; break;
    case 1: Num=SystemConfig_CTIDataTel2; break;
    case 2: Num=SystemConfig_CTIDataTel3; break;
    case 3: Num=SystemConfig_CTIDataTel4; break;
  }
  //==============================================取得撥號碼數
  unsigned char CodeIndex=0;
  for (int i=0;i<16;i++){
    if(Num[i]!=0xff){ CodeIndex++;}
  }
  //==============================================撥出號碼
  Tentel_SetNumber(Num,CodeIndex);
  Delayms(150);
  Tentel_DialOut();
  for(int i=0;i<CodeIndex;i++){
    Delayms(300);
  }
  if(WaitForDTMF(1000*SystemConfig_ToneTimeout,StageTimeout,3)==0) return 0;
  if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
  //==============================================送出MSG QUEUE中的資料
  if(SendAllCTIMSG(&CTIMSGQueue)==0)return 0;
  //==============================================送出結束碼
  NeedSetupTime=1;
  SendStopCode(NeedSetupTime);
  if(WaitForDTMF(10000,0,3)==1){
    //==============================================播放"資料傳送完成"語音
    EnableSpeaker(SystemConfig_SPK_Voice);
    if(WaitForDTMF(20000,StageTimeout,3)==0){
      if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
      return 0;
    }
    //==============================================取得待會是否要接受資料
    if(DriverFlag.RDMode==0)EnableSpeaker(SystemConfig_SPK_DTMF);
    NeedRemoteSetup=1;
    return DataIn();
  }else{
    return 0;
  }
}
