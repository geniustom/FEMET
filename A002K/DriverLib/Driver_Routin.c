#include "DriverLib.h"


void DriverSecRoutin(){ //�C��]�@��
 
}

void DriverRoutin(){    //�C1ms �]�@��
  if(DriverFlag.NeedRoutin==0)return;
  
  if(msecCounter%1000==0){
    DriverSecRoutin();
  }

  if((SystemAlarm.CancelRing==0)&&(SystemAlarm.RingISStart==1)&&
     ((SystemAlarm.SystemRingBack1+SystemAlarm.SystemRingBack2+SystemAlarm.SystemRingBack3+SystemAlarm.SystemRingBack4)>0)){ //�䤤�@�Ӥ��O�s�[�_�ӴN�j��s
    BuzzerRing();
  }

  if ((DriverFlag.ResetSystem==1)){  
    DriverFlag.ResetSystem=0;
    ResetMCUByPMM();
  }
  
  //ReadRFID();
  DriverFlag.NeedRoutin=1;
}