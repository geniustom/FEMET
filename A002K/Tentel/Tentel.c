#include "../TaipeiCity_A002_L.h"

#define TentelPort  COM2
#define DEBUGIO

unsigned char TentelBUF[32];
unsigned char DTMFBUF[32];
unsigned char CMDData[32];
unsigned char AllDataBUF[128];

RANG_BUFFER TentelRangBUF;
RANG_BUFFER TentelAllDataBUF;
Tentel_State GYTentel_State;

//---------------------------------------------------------------------------------------
const unsigned char TCMD_HandFreeOn[4]={0xFA,0x6C,0xC7,0xAB};             //�}�_�K��
const unsigned char TCMD_HandFreeOff[4]={0xFA,0x6C,0xCD,0xA1};            //�����K��
const unsigned char TCMD_DialOut[4]={0xFA,0x65,0xAA,0xCF};                //���X�s�򸹽X
const unsigned char TCMD_SPKOff[4]={0xFA,0x6C,0xC4,0xA8};                 //����SPK
const unsigned char TCMD_SPKOn[4]={0xFA,0x6C,0xC0,0xAC};                  //�}��MIC
const unsigned char TCMD_GetEEPROM[4]={0xFA,0x60,0x64,0x04};              //Ū��EEPROM�X�t�]�w��
const unsigned char TCMD_TestPhone[4]={0xFA,0x60,0x60,0x00};              //���ոܾ��O�_�^��
const unsigned char TCMD_DefaultSetting_1[19]={0xFA,0x51,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x51};
const unsigned char TCMD_DefaultSetting_2[19]={0xFA,0x52,0x10,0x03,0x20,0x03,0x00,0x15,0x12,0x99,0x99,0x06,0x01,0x00,0xAA,0x00,0x99,0x99,0xC8};
//---------------------------------------------------------------------------------------
const unsigned char TRCMD_DialTone[3]={0x89,0x8d,0x04};                   //�����켷����
const unsigned char TRCMD_BusyTone[3]={0x89,0x89,0x33};                   //�����즣��
const unsigned char TRCMD_DTMFTone[1]={0x8A};                             //������DTMF
const unsigned char TRCMD_DialRing[2]={0x80,0x80};                        //�������T�a
const unsigned char TRCMD_TestRequest[1]={0x70};                          //��������ոܾ��^��
//---------------------------------------------------------------------------------------

unsigned char CheckCMDIsSame(unsigned char const *des,unsigned int Length){
  unsigned char Same=1;
  for(int i=0;i<Length;i++){
    if (des[i]!=CMDData[i]){
      Same=0;
    }
  }
  return Same;
}

void DebugIO(){
  P9DIR |= BIT0;
  P9OUT ^= BIT0;
}

void SendPacketCMD(unsigned char *CMD,unsigned int Length){  //�N��ƥ��]��CMD�ðe�X
  unsigned char PCMD[32];
  unsigned char CHKSUM=0x00;
  PCMD[0]=0xFA;
  for(int i=0;i<Length;i++){
    CHKSUM^=CMD[i];
    PCMD[i+1]=CMD[i];
  }
  PCMD[Length+1]=CHKSUM;

  for (long i=0;i<Length+2;i++){
    SendByteToUart(TentelPort,PCMD[i]);
  }  
}

void SyncPhoneStateFromCMD(){
  if (CheckCMDIsSame(TRCMD_DialTone,3)==1){   //�����켷����
    GYTentel_State.DetDialTone=1;
    return;
  }
  if (CheckCMDIsSame(TRCMD_DialTone,3)==1){   //�����켷����
    GYTentel_State.DetDialTone=1;
    return;
  }
  if (CheckCMDIsSame(TRCMD_DTMFTone,1)==1){   //������DTMF
    unsigned char DTMFDigi=CMDData[1]-48;
    if (DTMFDigi==0x0A){DTMFDigi=0;}
    GYTentel_State.DetDTMF=1;
    PutByte(&GYTentel_State.DTMFBuffer,DTMFDigi);
    return;
  }
  
  if (CheckCMDIsSame(TRCMD_DialRing,2)==1){  //�������T�a
    GYTentel_State.ISRing=1;
    GYTentel_State.RingCount++;
    return;
  }                                             
 
  if (CheckCMDIsSame(TRCMD_TestRequest,1)==1){  //��������ոܾ��^��
    GYTentel_State.LineIsOK=1;
    return;
  }   
  if (CheckCMDIsSame(TRCMD_BusyTone,3)==1){     //������ܾ�����
    GYTentel_State.ISBusy=1;
    return;
  }   
}

void ProcessCMD(unsigned char BUF){
  //SendByteToUart(PCRs232Port,BUF);
  PutByte(&TentelAllDataBUF, BUF);
  PutByte(&TentelRangBUF, BUF);
  //�Y�����m�Ҧ��Ĥ@�Ӧ��쪺BYTE������0xfa,
  //�Y�O,�ᱼ0xfa�öi�J�����Ҧ�,
  //�Y���O,�ᱼBYTE�æ^�춢�m�Ҧ�
  if ((GYTentel_State.RecvMode==0)&&(BUF!=0xfa)){
    SkipByte(&TentelRangBUF,1);
    GYTentel_State.RecvMode=0;
    return;
  }
  //���ެ��ƻ�Ҧ�,�u�n����0xfa,�N��e����DATA�����L��,�öi�J�����Ҧ�  
  if(BUF==0xfa){
    SkipALL(&TentelRangBUF);        //���R�����e�������e
    GYTentel_State.RecvMode=1;
    return;
  }
  //�Y�������Ҧ�,���ˬd�O�_BUFFER��,�Y�O,�R���Ҧ���ƨæ^�춢�m�Ҧ�
  if ((GYTentel_State.RecvMode==1)&&(IsFull(&TentelRangBUF)==1)){
    SkipALL(&TentelRangBUF);
    GYTentel_State.RecvMode=0;
    return;
  }  
  //�Y���쪺��ƬO�e���X��byte��XOR�����G,��ܳo�O�@��CMD,�N���X�æ^�춢�m�Ҧ�
  GetAllData(&TentelRangBUF,CMDData);
  unsigned CHKSum=0x00;
  for(int i=0;i<TentelRangBUF.UsedByte-1;i++){
    CHKSum^=CMDData[i];
  }
  if(CHKSum==CMDData[TentelRangBUF.UsedByte-1]){
    SyncPhoneStateFromCMD();
    SkipALL(&TentelRangBUF);
    GYTentel_State.RecvMode=0;
  }
}


void Tentel_WriteDefault(){
  SendTextToUart(TentelPort,TCMD_DefaultSetting_1,19);
  Delayms(300);
  SendTextToUart(TentelPort,TCMD_DefaultSetting_2,19);
  Delayms(300);
}

unsigned char Init_Tentel(){
  OpenUart(TentelPort,1200,ProcessCMD);
  
  CreatRangBuffer(&TentelRangBUF,TentelBUF,32);
  CreatRangBuffer(&TentelAllDataBUF,AllDataBUF,128);
  CreatRangBuffer(&GYTentel_State.DTMFBuffer,DTMFBUF,32);

  Tentel_HangUp();
  return 1;
}


//======================================================================================================
//======================================================================================================
//======================================================================================================
//======================================================================================================
/*
unsigned char CheckLineErr(){   //�Q�ΰeCMD���覡�����q�ܽu���`:0 �q�ܲ{���`:1
  SendTextToUart(TentelPort,TCMD_TestPhone,4);
  Delayms(100);
  if(GYTentel_State.LineIsOK==1){
    GYTentel_State.LineIsOK=0;
    return 0;
  }else{
    return 1;
  }
}
*/
/*
unsigned char CheckLineErr(){   //�Q�ή��_�ܵ����覡�����q�ܽu���`:0 �q�ܲ{���`:1
  Delayms(500); //�����괭�ܾ���A�ݭn����q�ܪ��q����i�괭�ܾ��A�~�i����CMD�A�o������DELAY
  SendTextToUart(TentelPort,TCMD_HandFreeOn,4);
  Delayms(1000);
  SendTextToUart(TentelPort,TCMD_HandFreeOff,4);
  if(GYTentel_State.DetDialTone==1){
    GYTentel_State.DetDialTone=0; //�_��
    return 0;
  }else{
    return 1;
  }
}
*/

unsigned char CheckLineIsOK(){
  if (DriverFlag.LineIsErr==0){
    return 1;
  }else{
    return 0;
  }
} 


void Tentel_PickUp(){
  SendTextToUart(TentelPort,TCMD_HandFreeOn,4);
}

void Tentel_HangUp(){
  SendTextToUart(TentelPort,TCMD_HandFreeOff,4);
}

void Tentel_CloseSPK(){
  SendTextToUart(TentelPort,TCMD_SPKOff,4);
}

void Tentel_OpenSPK(){
  SendTextToUart(TentelPort,TCMD_SPKOn,4);
}

void Tentel_ClearDTMFBuf(){
  SkipALL(&GYTentel_State.DTMFBuffer);
  GYTentel_State.DetDTMF=0;
  GYTentel_State.DTMFBuffer.UsedByte=0;
}

unsigned char GetDTMFString(unsigned int len){
  if (GYTentel_State.DTMFBuffer.UsedByte==len){
    return 1;
  }else{
    return 0;
  }
}

unsigned char Tentel_GetDTMFDigi(){
  unsigned char Result=0xff;
  if(GYTentel_State.DetDTMF==1){ 
#ifdef DEBUGIO
    DebugIO();
#endif
    Result=GetByte(&GYTentel_State.DTMFBuffer);
    if(GYTentel_State.DTMFBuffer.UsedByte==0){  //�YBUFFER�S��ƤF�N��DETDTMF�M�s
       GYTentel_State.DetDTMF=0;   //�_��
    }
  }
  return Result;
}

void Tentel_SendDTMFList(unsigned char *STR,unsigned long Length){ 
  Tentel_SetNumber(STR,Length);
  Delayms(50);
  Tentel_DialOut();
#ifdef DEBUGIO
  DebugIO();
#endif
  Tentel_ClearDTMFBuf();
  Delayms(50);
}


void Tentel_SendKey(unsigned char Digi){ //��CMD���覡�ӥ�
  if(Digi==0){Digi=0x0a;}
  if(Digi=='*'){Digi=0xca;}
  if(Digi=='#'){Digi=0xcb;}
  unsigned char CMD[3]={0x61,0x55,0x00};
  CMD[2]=Digi;
  SendPacketCMD(CMD,3);
#ifdef DEBUGIO
  DebugIO();
#endif
}

void Tentel_SendDTMF(unsigned char Digi){   //�ΰeLIST���覡�ӥ�
  if(Digi==0){Digi=0x0a;}
  if(Digi=='*'){Digi=0xca;}
  if(Digi=='#'){Digi=0xcb;}
  unsigned char *STR=&Digi;
  Tentel_SetNumber(STR,1);
  Delayms(50);
  Tentel_DialOut();
#ifdef DEBUGIO
  DebugIO();
#endif
  Tentel_ClearDTMFBuf();
  Delayms(50);
}

void Tentel_SetNumber(unsigned char const *NUM,unsigned char Length){
  //===============�N�n�������X�s��ܾ����O����
  unsigned char CMD0[32]={
    0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  };
  for(int i=0;i<Length;i++){
    CMD0[i+1]=NUM[i];
    if(NUM[i]==0){CMD0[i+1]=0x0a;}
    if(NUM[i]=='*'){CMD0[i+1]=0xca;}
    if(NUM[i]=='#'){CMD0[i+1]=0xcb;}
  }
  SendPacketCMD(CMD0,Length+1);
}

void Tentel_DialOut(){
  SendTextToUart(TentelPort,TCMD_DialOut,4);
}

void Tentel_GetDefault(){
  SendTextToUart(TentelPort,TCMD_GetEEPROM,4); 
  SkipALL(&TentelAllDataBUF);        //���R�����e�������e 
}


void Tentel_DumpBuf2PC(){
  unsigned char *DataStr=0;
  unsigned char Len=TentelAllDataBUF.UsedByte;
  const unsigned char HEXSTR[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  GetAllData(&TentelAllDataBUF,DataStr);
  SendTextToUart(PCRs232Port,"TENDEF",6);
  SendByteToUart(PCRs232Port,13);
  SendByteToUart(PCRs232Port,10);
  for (int i=1;i<=Len;i++){
    if(i%19==0){
      SendByteToUart(PCRs232Port,13);
      SendByteToUart(PCRs232Port,10);
    }else{
      SendByteToUart(PCRs232Port,HEXSTR[AllDataBUF[i]/16]);
      SendByteToUart(PCRs232Port,HEXSTR[AllDataBUF[i]%16]);
      SendByteToUart(PCRs232Port,0x20);
    }
  }
}