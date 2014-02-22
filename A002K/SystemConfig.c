#include "DriverLib/DriverLib.h"
#include "TENTEL/Tentel.h"
#include "TaipeiCity_A002_L.h"
#include "MeasureDev/MeasureDev.h"


RANG_BUFFER PC_RS232BUF;
unsigned char PC_DATAMode=0;
unsigned char RS232BUF[RS232BUFLength];
unsigned long SetupStartTime;

unsigned char Init_PCRS232(){
  OpenUart(PCRs232Port,19200,ProcessFEMETCMD);  //�X�f���~���
  CreatRangBuffer(&PC_RS232BUF,RS232BUF,RS232BUFLength);
  return 1;
}


void ProcessFEMETCMD(unsigned char BUF){
  PutByte(&PC_RS232BUF,BUF);
  //========================================�Y8���٨S�����ǿ�A�N���誺CMD�i�঳���D
  if((SystemDateTime.secCounter-SetupStartTime>8)&&(PC_DATAMode==1)){
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    PC_DATAMode=0;
    return;    
  }
  //========================================�Y���O�X�k��CMD
  if((PC_RS232BUF.UsedByte>6)&&(PC_DATAMode==0)) {
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    PC_DATAMode=0;
    return;
  }
  //========================================�P�_�Ĥ@�X��@
  if((PC_DATAMode==0)&&(RS232BUF[0]!='@')){
    PC_DATAMode=0;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    return;
  }  
  //========================================�P�_�᤭�X��FEMET
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='F')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='M')&&(RS232BUF[4]=='E')&&(RS232BUF[5]=='T')){
    SetupStartTime=SystemDateTime.secCounter; //�}�l�p��
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendTextToUart(PCRs232Port,"WRITEREADY",10);
    return;
  }
  //========================================�P�_�᤭�X��READ! ���o�Ҧ����+CHECK SUM
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='R')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='A')&&(RS232BUF[4]=='D')&&(RS232BUF[5]=='!')){
    PC_DATAMode=0;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendTextToUart(PCRs232Port,"READREADY",9);
    //=============================
    unsigned char *PTR=(unsigned char *)SystemConfig_Addr;
    unsigned char ConfigSTR[256];
    for(unsigned int i=0;i<256;i++){
      ConfigSTR[i]=*PTR;
      PTR++;
    }
    //=============================�N�ثe�t�ήɶ��g�^�}�C
    ConfigSTR[0xE0]= SystemDateTime.Year % 256;
    ConfigSTR[0xE1]= SystemDateTime.Year / 256;
    ConfigSTR[0xE2]= SystemDateTime.Month;
    ConfigSTR[0xE3]= SystemDateTime.Day;
    ConfigSTR[0xE4]= SystemDateTime.Hour;
    ConfigSTR[0xE5]= SystemDateTime.Minute;
    ConfigSTR[0xE6]= SystemDateTime.Second;
    //=============================
    unsigned char RDCHKSUM=0;
    for(int i=0;i<256;i++){
      SendByteToUart(PCRs232Port,ConfigSTR[i]);
      RDCHKSUM^=ConfigSTR[i];
    }
    SendByteToUart(PCRs232Port,RDCHKSUM);
    return;
  }  
  //========================================�P�_�᤭�X��TEST! �����Ҧ��I�ϤΨD�ϥ\��
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='T')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='S')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendTextToUart(PCRs232Port,"TESTREADY",9);
    return;
  }
  //========================================�P�_�᤭�X��STOP! �����Ҧ��I�ϤΨD�ϥ\��
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='T')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='S')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendTextToUart(PCRs232Port,"STOPREADY",9);
    return;
  }
  //========================================����CHKSUM�T�{�L�~��CMD����A�}�l�g��FLASH
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='W')&&(RS232BUF[2]=='R')&&(RS232BUF[3]=='I')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='E')){
    _DINT();
    flash_erase_multi_segments(SystemConfig_Addr,1);
    flash_write_Block(SystemConfig_Addr,SystemConfig_BackData,256);
    _EINT();
    SetDefaultTime(SystemConfig_NowYear,SystemConfig_NowMonth,SystemConfig_NowDay,
                   SystemConfig_NowHour,SystemConfig_NowMinute,SystemConfig_NowSecond);
    SETRTC_To_S35390();
    SkipALL(&PC_RS232BUF);        //���R�����e�������e    
    SendTextToUart(PCRs232Port,"FINISH",6);
    Delayms(500);
    DriverFlag.ResetSystem=1;
    return;
  }
  //========================================�P�_�᤭�X��CALL! �Ұʱj��t�Φ^��
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='C')&&(RS232BUF[2]=='A')&&(RS232BUF[3]=='L')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendTextToUart(PCRs232Port,"CALLREADY",9);
    DriverFlag.CancelLongPress=1;
    return;
  }
  //========================================�P�_�᤭�X��QUEUE �NQUEUE�뺡
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='Q')&&(RS232BUF[2]=='U')&&(RS232BUF[3]=='E')&&(RS232BUF[4]=='U')&&(RS232BUF[5]=='E')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    TestQueueSend();
    return;   
  }
  //========================================�P�_�᤭�X��CLEAR �NQUEUE�M��
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='C')&&(RS232BUF[2]=='L')&&(RS232BUF[3]=='E')&&(RS232BUF[4]=='A')&&(RS232BUF[5]=='R')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    DeleteAllCTIMSG(&CTIMSGQueue);
    return;   
  }
  //========================================�P�_�᤭�X��GETQU �NQUEUE�Ҧ����X�Ǧ^
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='G')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='T')&&(RS232BUF[4]=='Q')&&(RS232BUF[5]=='U')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendQueueDataToPc(&CTIMSGQueue);
    return;   
  }
  //========================================�P�_�᤭�X��QSIZE �N�^��QUEUE SIZE
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='Q')&&(RS232BUF[2]=='S')&&(RS232BUF[3]=='I')&&(RS232BUF[4]=='Z')&&(RS232BUF[5]=='E')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //���R�����e�������e
    SendQueueSizeToPC(&CTIMSGQueue);
    return;
  }
  //========================================�P�_�᤭�X��ICALL �B�ثe���ݾ����A �N�Ұʱj��^��
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='I')&&(RS232BUF[2]=='C')&&(RS232BUF[3]=='A')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='L')&&(A002State.State==State_NormalStandBy)){
    DriverFlag.CancelLongPress=1;
    return;
  }
  //========================================�P�_�᤭�X��KILLD �B�ثe���ݾ����A �N�R��DONGLE���
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='K')&&(RS232BUF[2]=='I')&&(RS232BUF[3]=='L')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='D')&&(A002State.State==State_NormalStandBy)){
    MEADEV_ClearFlash();
    return;
  }
  //========================================�P�_��ƶǿ駹��

  if((PC_RS232BUF.UsedByte==256)&&(PC_DATAMode==1)){
    //======================================�g�JFLASH=========
    _DINT();
    flash_erase_multi_segments(SystemConfig_BackAddr,1);
    flash_write_Block(SystemConfig_BackAddr,RS232BUF,256);
    _EINT();
    //========================================================
    unsigned char CHKSUM=0;
    for(int i=0;i<256;i++){
      CHKSUM^=RS232BUF[i];
    }
    
    SkipALL(&PC_RS232BUF);
    SendTextToUart(PCRs232Port,"WRITEOK",7);
    SendByteToUart(PCRs232Port,CHKSUM);
    PC_DATAMode=0;
    _NOP();
  }
}


void SendEventToPC(unsigned char EventNum){
/*
  9:�ȪA
  1~8:����
  0:����
  10:�S��s
*/  
  SendTextToUart(PCRs232Port,"RFPRESS",7);
  SendByteToUart(PCRs232Port,EventNum);
}