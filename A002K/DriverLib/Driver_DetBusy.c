#include "DriverLib.h"
#define ToneBufferLength 12
#define DetCount     6     //��6�n
unsigned long BusyToneList[ToneBufferLength];
unsigned char BusyToneIndex=0;
unsigned long LastToneTime=0;

/*
��z:
����:500ms,���_��:250ms,�ʱ���:125ms
�N��ƥk��5�쵥�P��32�A�۷�󤹳\6%���~�t
����:15~16 ���_��: 8 �ʱ���: 4
*/

unsigned long TempToneList[ToneBufferLength]; //���ؤ@���V��C

/*
unsigned char DetBusy(){ // 2016/03/21 �e���Y�Ԫ�����
  
  for(int i=0;i<ToneBufferLength;i++)TempToneList[i]=0;
//==================================�Τ@�^�X�N��C�ѱߨ즭�ƦC
  for(int i=0;i<ToneBufferLength;i++){
    unsigned char CycleIndex=(BusyToneIndex+ToneBufferLength-i-1)%ToneBufferLength;
    TempToneList[i]=BusyToneList[CycleIndex];
  }
//==================================�Τ@�^�X������Ҧ��ǦC�A���ۦP�^0
  for(int i=0;i<DetCount;i++){
    if(TempToneList[i]!=TempToneList[0])
       return 0;
  }
//==================================�̫�@���A����>=4�B<=16
  if((TempToneList[0]>=4)&&(TempToneList[0]<=16)){  
    return 1;
  }else{
    return 0;
  }
}
*/

double dabs(double data){
  if (data>0){ 
    return data;
  }else{
    return -data;
  }
}

unsigned char DetBusy(){
  for(int i=0;i<ToneBufferLength;i++)TempToneList[i]=0;
//==================================���N��C�ѱߨ즭�ƦC6��
  for(int i=0;i<ToneBufferLength;i++){
    unsigned char CycleIndex=(BusyToneIndex+ToneBufferLength-i-1)%ToneBufferLength;
    TempToneList[i]=BusyToneList[CycleIndex];
  }
//==================================��1,3,5 ���۵� �B��2,4,6���۵�
  if ((TempToneList[0]!=TempToneList[2])||(TempToneList[2]!=TempToneList[4])) return 0;
  if ((TempToneList[1]!=TempToneList[3])||(TempToneList[3]!=TempToneList[5])) return 0;
//==================================1~6�������P 1,3,5 & 2,4,6 ����ۮt�Ӥj  
  double avg=0;
  for(int i=0;i<DetCount;i++){
    avg+=TempToneList[i];
  }
  avg=avg/DetCount;
  for(int i=0;i<DetCount;i++){
    if (dabs(TempToneList[i]-avg)>1) return 0;
  }
//==================================�̫�@���A����>=4�B<=16
  if((TempToneList[0]>=4)&&(TempToneList[0]<=16)){  
    return 1;
  }else{
    return 0;
  }
}

void DetBusyLo(){
  BusyToneList[BusyToneIndex]=(msecCounter-LastToneTime)>>5;
  BusyToneIndex++;
  BusyToneIndex%=ToneBufferLength;
  LastToneTime=msecCounter;
  
  if(DetBusy()==1){
    DriverFlag.PhoneBusy=1;
  }
}

void DetBusyHi(){
  BusyToneList[BusyToneIndex]=(msecCounter-LastToneTime)>>5;
  BusyToneIndex++;
  BusyToneIndex%=ToneBufferLength;
  LastToneTime=msecCounter;
  
  if(DetBusy()==1){
    DriverFlag.PhoneBusy=1;
  }
}