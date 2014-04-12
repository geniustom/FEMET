#include "DriverLib.h"


void DriverSecRoutin(){ //每秒跑一次
 
}

void DriverRoutin(){    //每1ms 跑一次
  if(DriverFlag.NeedRoutin==0)return;
  
  if(msecCounter%1000==0){
    DriverSecRoutin();
  }

  if((SystemAlarm.CancelRing==0)&&(SystemAlarm.RingISStart==1)&&
     ((SystemAlarm.SystemRingBack1+SystemAlarm.SystemRingBack2+SystemAlarm.SystemRingBack3+SystemAlarm.SystemRingBack4)>0)){ //其中一個不是零加起來就大於零
    BuzzerRing();
  }

  if ((DriverFlag.ResetSystem==1)){  
    DriverFlag.ResetSystem=0;
    ResetMCUByPMM();
  }
  
  //ReadRFID();
  DriverFlag.NeedRoutin=1;
}