#include "TaiDoc\TaiDoc.h"
#include "Donglelib\Donglelib.h"
#include "Measuredev.h"


void MEADEV_ProcessData(unsigned char Rx){
  if(DriverFlag.MeaDev==1){   //百略1 華廣0
    ProcessDongleData(Rx);
  }else{
    ProcessTiDocData(Rx);
  }
}

void MEADEV_InitDevice(){
  OpenUart(DonglePort,19200,MEADEV_ProcessData);
  MEADEV_SetDeviceTime();
}

void MEADEV_GetDeviceVER(){
  unsigned char DVer[37]={0x00};
  DVer[0]='V';  DVer[1]='E';  DVer[2]='R';  DVer[3]='D';  DVer[4]='O';
  ReadDongleVer();
  Delayms(500);
  for(int i=0;i<32;i++){
    DVer[5+i]=DongleBuf[2+i];
  }
  SendTextToUart(PCRs232Port,DVer,37);  //DEVICE傳資料給MCU
}

unsigned char MEADEV_GetDeviceData(unsigned char User){
  unsigned long EnTime=0;
  unsigned long Data=0;
  unsigned long CheckSum=0;
  
  
  if(DriverFlag.MeaDev==1){   //百略1 華廣0
    ReadDongleData();
    Delayms(1500);  //DONGLE DELAY秒數
 
    //====================================檢查CHECK SUM==============
    for (long i=0;i<16;i++){
      CheckSum+=DongleBuf[i];
    }
    CheckSum&=0xff;
    if(CheckSum!=DongleBuf[16]){
      return 0;
    }
    //====================================檢查CHECK SUM==============    
    
    SendTextToUart(COM3,"DEV->MCU:",9);  //DEVICE傳資料給MCU
    for (long i=0;i<17;i++){
      SendByteToUart(COM3,DongleBuf[i]);
    }   
    
    unsigned long MData=(((unsigned long)DongleBuf[10]*256+(unsigned long)DongleBuf[11])*1000000)+
                        (((unsigned long)DongleBuf[12]*256+(unsigned long)DongleBuf[13])*1000)+
                        (((unsigned long)DongleBuf[14]*256+(unsigned long)DongleBuf[15]));
    unsigned long WData=((unsigned long)DongleBuf[8]*256+(unsigned long)DongleBuf[9])*1000000;
    if((MData==0)&&(WData==0)){
      return 0;
    }else{
      if(MData!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,EncodeNowDateTime(),MData);   //傳入主機的時間
      if(WData!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,EncodeNowDateTime(),WData);   //傳入主機的時間
      return 1;
    }
  }else{     
    ReadTaiDocData(&EnTime,&Data);
    if(EnTime!=0&&Data!=0){
      //PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,Etime,EData);               //傳入血壓計的時間
      PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,EncodeNowDateTime(),Data);   //傳入主機的時間
      return 1;
    }else{
      return 0;
    }
  }
}


unsigned char MEADEV_GetDeviceDataMulti(unsigned char User){
  unsigned long EnTime=0;
  unsigned long Data=0;
  unsigned long MEADEV_CheckSum=0;
  
  
  if(DriverFlag.MeaDev==1){   //百略1 華廣0
    ReadDongleData();
    Delayms(1500);  //DONGLE DELAY秒數
 
    //====================================檢查CHECK SUM==============
    for (long i=0;i<42;i++){
      MEADEV_CheckSum+=DongleBuf[i];
    }
    MEADEV_CheckSum&=0xff;
    if(MEADEV_CheckSum!=DongleBuf[42]){
      return 0;
    }
    //====================================檢查CHECK SUM==============    
    
    SendTextToUart(COM3,"DEV->MCU:",9);  //DEVICE傳資料給MCU
    for (long i=0;i<43;i++){
      SendByteToUart(COM3,DongleBuf[i]);
    }   
    
    unsigned long MData=(((unsigned long)DongleBuf[36]*256+(unsigned long)DongleBuf[37])*1000000)+
                        (((unsigned long)DongleBuf[38]*256+(unsigned long)DongleBuf[39])*1000)+
                        (((unsigned long)DongleBuf[40]*256+(unsigned long)DongleBuf[41]));
    unsigned long long WData1=((unsigned long)DongleBuf[8]*256+(unsigned long)DongleBuf[9])*1000000;
    unsigned long long WData2=((unsigned long)DongleBuf[15]*256+(unsigned long)DongleBuf[16])*1000000;
    unsigned long long WData3=((unsigned long)DongleBuf[22]*256+(unsigned long)DongleBuf[23])*1000000;
    unsigned long long WData4=((unsigned long)DongleBuf[29]*256+(unsigned long)DongleBuf[30])*1000000;
    
    unsigned long WTime1=EncodeDateTime(DongleBuf[10],DongleBuf[11],DongleBuf[12],DongleBuf[13],DongleBuf[14]);
    unsigned long WTime2=EncodeDateTime(DongleBuf[17],DongleBuf[18],DongleBuf[19],DongleBuf[20],DongleBuf[21]);
    unsigned long WTime3=EncodeDateTime(DongleBuf[24],DongleBuf[25],DongleBuf[26],DongleBuf[27],DongleBuf[28]);
    unsigned long WTime4=EncodeDateTime(DongleBuf[31],DongleBuf[32],DongleBuf[33],DongleBuf[34],DongleBuf[35]);
    
    
    if((MData==0)&&(WData1==0)&&(WData2==0)&&(WData3==0)&&(WData4==0)){
      return 0;
    }else{
      if(MData!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,EncodeNowDateTime(),MData);   //傳入主機的時間
      if(WData1!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,WTime1,WData1);   //傳入量測的時間
       if(WData2!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,WTime2,WData2);   //傳入量測的時間
      if(WData3!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,WTime3,WData3);   //傳入量測的時間
      if(WData4!=0)
        PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,WTime4,WData4);   //傳入量測的時間
      return 1;
    }
  }else{     
    ReadTaiDocData(&EnTime,&Data);
    if(EnTime!=0&&Data!=0){
      //PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,Etime,EData);               //傳入血壓計的時間
      PutCTIMSG(&CTIMSGQueue,User,CTIMSG_HealthDataUpload,EncodeNowDateTime(),Data);   //傳入主機的時間
      return 1;
    }else{
      return 0;
    }
  }
}

void MEADEV_SetDeviceTime(){
  if(DriverFlag.MeaDev==1){   //百略1 華廣0
    _NOP();
  }else{
    WriteTimeToTaiDoc();
  }
}


void MEADEV_ClearFlash(){

  if(DriverFlag.MeaDev==1){   //百略1 華廣0
    ClearDongleFlash();    
  }else{
    ClearTaiDocFlash();
  }

}