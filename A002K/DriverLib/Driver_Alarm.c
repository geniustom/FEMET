#include "DriverLib.h"

AlarmSetting SystemAlarm;

#define EncodeMinute(H,M)   (unsigned long)((unsigned long)M + (unsigned long)H *60)%1440

void (*AlarmStartCallBackFP)(unsigned char AlarmID);  //�^�I��FUNCTION POINT
void (*AlarmStopCallBackFP)();  //�^�I��FUNCTION POINT


void InitAlarmTable(){
  unsigned long EncodeM;
  for(int i=0;i<1440;i++){
    SystemAlarm.AlarmTable[i]=0;
  }
  if(SystemAlarm.NO1_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO1_Hour,SystemAlarm.NO1_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO1_Contiune);i++){
      SystemAlarm.AlarmTable[i%1440]=1;
    }
  }
  if(SystemAlarm.NO2_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO2_Hour,SystemAlarm.NO2_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO2_Contiune);i++){
      SystemAlarm.AlarmTable[i%1440]=1;
    }
  }
  if(SystemAlarm.NO3_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO3_Hour,SystemAlarm.NO3_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO3_Contiune);i++){
      SystemAlarm.AlarmTable[i%1440]=1;
    }
  }
  if(SystemAlarm.NO4_Contiune!=0){
    EncodeM=EncodeMinute(SystemAlarm.NO4_Hour,SystemAlarm.NO4_Minute);
    for(int i=EncodeM;i<(EncodeM+SystemAlarm.NO4_Contiune);i++){
      SystemAlarm.AlarmTable[i%1440]=1;
    }
  }  
  
  SystemAlarm.AlarmStart[0]=EncodeMinute(SystemAlarm.NO1_Hour,SystemAlarm.NO1_Minute);
  SystemAlarm.AlarmStart[1]=EncodeMinute(SystemAlarm.NO2_Hour,SystemAlarm.NO2_Minute);
  SystemAlarm.AlarmStart[2]=EncodeMinute(SystemAlarm.NO3_Hour,SystemAlarm.NO3_Minute);
  SystemAlarm.AlarmStart[3]=EncodeMinute(SystemAlarm.NO4_Hour,SystemAlarm.NO4_Minute);
}

void InitAlarm(void (*AlarmStartCallBack)(unsigned char AlarmID),void (*AlarmStopCallBack)()){
  InitAlarmTable();
  AlarmStartCallBackFP=AlarmStartCallBack;
  AlarmStopCallBackFP=AlarmStopCallBack;
}

void StopAlarm(){
  SystemAlarm.RingISStart=0;
  SystemAlarm.CancelRing=0;
  SystemAlarm.AlarmTrigger[0]=0;
  SystemAlarm.AlarmTrigger[1]=0;
  SystemAlarm.AlarmTrigger[2]=0;
  SystemAlarm.AlarmTrigger[3]=0;
  if(AlarmStopCallBackFP!=0)AlarmStopCallBackFP();
}








void SyncAlarm(){   //�C���ˬd�@��

  if((SystemAlarm.CancelRing==1)&&(SystemAlarm.RingISStart==1)){        //�x�a�ɫ��F������
    StopAlarm();  
  }  
  
  if((SystemAlarm.SystemRingBack1==0)&&  //�����F���٨S������..�I�s�^�I�禡
     (SystemAlarm.SystemRingBack2==0)&&
     (SystemAlarm.SystemRingBack3==0)&&
     (SystemAlarm.SystemRingBack4==0)&&
     (SystemAlarm.CancelRing==0)&&
     (SystemAlarm.RingISStart==1)){
     StopAlarm();
  }
  
}

void CheckAlarm(){  //�C10���ˬd�@��
  unsigned long EncodeNow;
  
  if(SystemDateTime.Second%10!=0){  //�C10���ˬd�@��
    return;
  }
  
  EncodeNow=EncodeMinute(SystemDateTime.Hour,SystemDateTime.Minute)%1440;  //�s�X�ثe���ɶ�
  for(int i=0;i<4;i++){
    if((EncodeNow==SystemAlarm.AlarmStart[i])&&(SystemDateTime.Second==0)){
      SystemAlarm.AlarmTrigger[i]=1;
      SystemAlarm.RingISStart=1;
      if(AlarmStartCallBackFP!=0)AlarmStartCallBackFP(i);
    }
  }
  
  if((SystemAlarm.AlarmTable[EncodeNow]==1)&&(SystemAlarm.AlarmTrigger[0]==1)){  //��1��
    SystemAlarm.SystemRingBack1=1;
  }else{
    SystemAlarm.SystemRingBack1=0;
  }
  
  if((SystemAlarm.AlarmTable[EncodeNow]==1)&&(SystemAlarm.AlarmTrigger[1]==1)){  //��2��
    SystemAlarm.SystemRingBack2=1;
  }else{
    SystemAlarm.SystemRingBack2=0;
  }

  if((SystemAlarm.AlarmTable[EncodeNow]==1)&&(SystemAlarm.AlarmTrigger[2]==1)){  //��3��
    SystemAlarm.SystemRingBack3=1;
  }else{
    SystemAlarm.SystemRingBack3=0;
  }

  if((SystemAlarm.AlarmTable[EncodeNow]==1)&&(SystemAlarm.AlarmTrigger[3]==1)){  //��3��
    SystemAlarm.SystemRingBack4=1;
  }else{
    SystemAlarm.SystemRingBack4=0;
  }
  
}