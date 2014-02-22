#include <MATH.h>
#include "DriverLib.h"

ButtonList DeviceButton;
//============================RD MODE�M��=============================
const unsigned char PWD_RDMode[6]={'L','L','R','R','L','R'};
unsigned char ButtonRDList[6];
unsigned char PWD_Index=0;
void InputButton(unsigned char ButtonID);
//====================================================================


void InitButton(unsigned long LongPressTime,void (*ServiceCallBack)(),void (*CancelCallBack)(),void (*ServiceLongCallBack)(),void (*CancelLongCallBack)()){
  DeviceButton.ServiceCallBack=ServiceCallBack;
  DeviceButton.CancelCallBack=CancelCallBack;
  DeviceButton.ServiceLongCallBack=ServiceLongCallBack;
  DeviceButton.CancelLongCallBack=CancelLongCallBack;
  DeviceButton.LongPressTime=LongPressTime;
  DeviceButton.ServicePressTime=0;
  DeviceButton.CancelPressTime=0;
}



void ButtonSignal(unsigned char ButtonID,unsigned char P0R1){ //���U��0,��}��1
  switch (ButtonID){
    case ServiceButton:
      if(P0R1==0){
        DeviceButton.ServicePressTime=msecCounter;
      }else{
        CheckButtonPress(ButtonID);
      }
      break;
    case CancelButton: 
      if(P0R1==0){
        DeviceButton.CancelPressTime=msecCounter;
      }else{
        CheckButtonPress(ButtonID);
      }
      if((SystemAlarm.RingISStart==1)){
        SystemAlarm.CancelRing=1;
      }
      break;
  }

}

void CheckButtonPress(unsigned char ButtonID){
  switch (ButtonID){
    case ServiceButton:
      if(msecCounter-DeviceButton.ServicePressTime<DeviceButton.LongPressTime){
        DriverFlag.ServicePress=1;
        //InputButton('R');
        if(DeviceButton.ServiceCallBack!=0)DeviceButton.ServiceCallBack();
      }else{
        DriverFlag.ServiceLongPress=1;
        if(DeviceButton.ServiceLongCallBack!=0)DeviceButton.ServiceLongCallBack();
      }
      DeviceButton.ServicePressTime=0;
      break;
    case CancelButton: 
      if(msecCounter-DeviceButton.CancelPressTime<DeviceButton.LongPressTime){
        DriverFlag.CancelPress=1;
        //InputButton('L');
        if(DeviceButton.CancelCallBack!=0)DeviceButton.CancelCallBack();
      }else{
        DriverFlag.CancelLongPress=1;
        if(DeviceButton.CancelLongCallBack!=0)DeviceButton.CancelLongCallBack();
      }
      DeviceButton.CancelPressTime=0;
      break;
  }
}



//============================RD MODE�M��=============================
void In_Out_RDMode(){
  for(int i=0;i<6;i++){
    unsigned char CheckSuccess=1;
    for(int j=0;j<6;j++){
      if(ButtonRDList[(i+j)%6]!=PWD_RDMode[j]){
        CheckSuccess=0;
        break;
      }
    }
    if(CheckSuccess==1){
      DriverFlag.RDModeStateChange=1;
      for(int k=0;k<6;k++)ButtonRDList[k]=0;
      PWD_Index=0;
      if(DriverFlag.RDMode==1){   //�Y�쥻��1..�hRESET
        DriverFlag.ResetSystem=1;
      }
      DriverFlag.RDMode^=BIT0;
      break;
    }
  }
}

void InputButton(unsigned char ButtonID){
  ButtonRDList[PWD_Index]=ButtonID;
  PWD_Index++;
  PWD_Index%=6;
  //In_Out_RDMode();
}







/*
void InitButton(void (*ServiceButtonCallBack)(),void (*CancelButtonCallBack)(),void (*SpecialButtonCallBack)()){
  DeviceButton.ServiceButtonCallBack=ServiceButtonCallBack;
  DeviceButton.CancelButtonCallBack=CancelButtonCallBack;
  DeviceButton.SpecialButtonCallBack=SpecialButtonCallBack;
  DeviceButton.ServicePressTime=0;
  DeviceButton.CancelPressTime=0;
}

void CheckButtonPress(){  //�Y�����s�A300ms�����ˬd�t�@�䦳�S���Q���U�A�Y���hĲ�o
  if(msecCounter-DeviceButton.PressTime<200)return;
  if(DeviceButton.NowButton==0)return;
  if((DeviceButton.ServicePressTime==0)&&(DeviceButton.CancelPressTime==0))return;
  
  if(fabs(DeviceButton.ServicePressTime-DeviceButton.CancelPressTime)<200){ //�P�_����P�ɫ��U
    if(DeviceButton.SpecialButtonCallBack!=0){
      DeviceButton.NowButton=0;
      DriverFlag.SpecialPress=1;
      DeviceButton.SpecialButtonCallBack();
    }
  }else{
    if(DeviceButton.NowButton==ServiceButton&&DeviceButton.ServiceButtonCallBack!=0){
      DeviceButton.NowButton=0;
      DriverFlag.ServicePress=1;
      DeviceButton.ServiceButtonCallBack();
    }
    if(DeviceButton.NowButton==CancelButton&&DeviceButton.CancelButtonCallBack!=0){
      DeviceButton.NowButton=0;
      DriverFlag.CancelPress=1;
      DeviceButton.CancelButtonCallBack();
    }
  }
  
}

void ButtonSignal(unsigned char ButtonID){
  DeviceButton.NowButton=ButtonID;
  DeviceButton.PressTime=msecCounter;
  switch (ButtonID){
    case ServiceButton:
      DeviceButton.ServicePressTime=msecCounter;
      break;
    case CancelButton: 
      DeviceButton.CancelPressTime=msecCounter;
      if((SystemAlarm.RingISStart==1)){
        SystemAlarm.CancelRing=1;
      }
      break;
  }
}
*/