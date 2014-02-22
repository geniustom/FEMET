#include "DriverLib/DriverLib.h"
#include "TENTEL/Tentel.h"
#include "TaipeiCity_A002_L.h"
#include "MeasureDev/MeasureDev.h"


RANG_BUFFER PC_RS232BUF;
unsigned char PC_DATAMode=0;
unsigned char RS232BUF[RS232BUFLength];
unsigned long SetupStartTime;

unsigned char Init_PCRS232(){
  OpenUart(PCRs232Port,19200,ProcessFEMETCMD);  //出貨版才能用
  CreatRangBuffer(&PC_RS232BUF,RS232BUF,RS232BUFLength);
  return 1;
}


void ProcessFEMETCMD(unsigned char BUF){
  PutByte(&PC_RS232BUF,BUF);
  //========================================若8秒內還沒完成傳輸，代表剛剛的CMD可能有問題
  if((SystemDateTime.secCounter-SetupStartTime>8)&&(PC_DATAMode==1)){
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    PC_DATAMode=0;
    return;    
  }
  //========================================若不是合法的CMD
  if((PC_RS232BUF.UsedByte>6)&&(PC_DATAMode==0)) {
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    PC_DATAMode=0;
    return;
  }
  //========================================判斷第一碼為@
  if((PC_DATAMode==0)&&(RS232BUF[0]!='@')){
    PC_DATAMode=0;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    return;
  }  
  //========================================判斷後五碼為FEMET
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='F')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='M')&&(RS232BUF[4]=='E')&&(RS232BUF[5]=='T')){
    SetupStartTime=SystemDateTime.secCounter; //開始計時
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendTextToUart(PCRs232Port,"WRITEREADY",10);
    return;
  }
  //========================================判斷後五碼為READ! 取得所有資料+CHECK SUM
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='R')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='A')&&(RS232BUF[4]=='D')&&(RS232BUF[5]=='!')){
    PC_DATAMode=0;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendTextToUart(PCRs232Port,"READREADY",9);
    //=============================
    unsigned char *PTR=(unsigned char *)SystemConfig_Addr;
    unsigned char ConfigSTR[256];
    for(unsigned int i=0;i<256;i++){
      ConfigSTR[i]=*PTR;
      PTR++;
    }
    //=============================將目前系統時間寫回陣列
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
  //========================================判斷後五碼為TEST! 關閉所有呼救及求救功能
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='T')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='S')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendTextToUart(PCRs232Port,"TESTREADY",9);
    return;
  }
  //========================================判斷後五碼為STOP! 關閉所有呼救及求救功能
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='T')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='S')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendTextToUart(PCRs232Port,"STOPREADY",9);
    return;
  }
  //========================================收到CHKSUM確認無誤的CMD之後，開始寫到FLASH
  if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='W')&&(RS232BUF[2]=='R')&&(RS232BUF[3]=='I')&&(RS232BUF[4]=='T')&&(RS232BUF[5]=='E')){
    _DINT();
    flash_erase_multi_segments(SystemConfig_Addr,1);
    flash_write_Block(SystemConfig_Addr,SystemConfig_BackData,256);
    _EINT();
    SetDefaultTime(SystemConfig_NowYear,SystemConfig_NowMonth,SystemConfig_NowDay,
                   SystemConfig_NowHour,SystemConfig_NowMinute,SystemConfig_NowSecond);
    SETRTC_To_S35390();
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容    
    SendTextToUart(PCRs232Port,"FINISH",6);
    Delayms(500);
    DriverFlag.ResetSystem=1;
    return;
  }
  //========================================判斷後五碼為CALL! 啟動強制系統回報
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='C')&&(RS232BUF[2]=='A')&&(RS232BUF[3]=='L')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='!')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendTextToUart(PCRs232Port,"CALLREADY",9);
    DriverFlag.CancelLongPress=1;
    return;
  }
  //========================================判斷後五碼為QUEUE 將QUEUE塞滿
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='Q')&&(RS232BUF[2]=='U')&&(RS232BUF[3]=='E')&&(RS232BUF[4]=='U')&&(RS232BUF[5]=='E')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    TestQueueSend();
    return;   
  }
  //========================================判斷後五碼為CLEAR 將QUEUE清空
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='C')&&(RS232BUF[2]=='L')&&(RS232BUF[3]=='E')&&(RS232BUF[4]=='A')&&(RS232BUF[5]=='R')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    DeleteAllCTIMSG(&CTIMSGQueue);
    return;   
  }
  //========================================判斷後五碼為GETQU 將QUEUE所有的碼傳回
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='G')&&(RS232BUF[2]=='E')&&(RS232BUF[3]=='T')&&(RS232BUF[4]=='Q')&&(RS232BUF[5]=='U')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendQueueDataToPc(&CTIMSGQueue);
    return;   
  }
  //========================================判斷後五碼為QSIZE 將回傳QUEUE SIZE
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='Q')&&(RS232BUF[2]=='S')&&(RS232BUF[3]=='I')&&(RS232BUF[4]=='Z')&&(RS232BUF[5]=='E')){
    PC_DATAMode=1;
    SkipALL(&PC_RS232BUF);        //先刪掉之前全部內容
    SendQueueSizeToPC(&CTIMSGQueue);
    return;
  }
  //========================================判斷後五碼為ICALL 且目前為待機狀態 將啟動強制回報
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='I')&&(RS232BUF[2]=='C')&&(RS232BUF[3]=='A')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='L')&&(A002State.State==State_NormalStandBy)){
    DriverFlag.CancelLongPress=1;
    return;
  }
  //========================================判斷後五碼為KILLD 且目前為待機狀態 將刪除DONGLE資料
   if((PC_DATAMode==0)&&(PC_RS232BUF.UsedByte==6)&&(RS232BUF[0]=='@')&&(RS232BUF[1]=='K')&&(RS232BUF[2]=='I')&&(RS232BUF[3]=='L')&&(RS232BUF[4]=='L')&&(RS232BUF[5]=='D')&&(A002State.State==State_NormalStandBy)){
    MEADEV_ClearFlash();
    return;
  }
  //========================================判斷資料傳輸完畢

  if((PC_RS232BUF.UsedByte==256)&&(PC_DATAMode==1)){
    //======================================寫入FLASH=========
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
  9:客服
  1~8:壓扣
  0:取消
  10:特殊鈕
*/  
  SendTextToUart(PCRs232Port,"RFPRESS",7);
  SendByteToUart(PCRs232Port,EventNum);
}