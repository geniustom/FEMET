#include "DriverLib.h"

extern void I2CCLOCK_INIT();
extern void I2CCLOCK_SET();
extern void I2CCLOCK_READTIME();
extern void SETRTC_To_S35390();

DateTime SystemDateTime;
DefaultDateTime DefDateTime;

#define EncodeMinute(H,M)   (unsigned long)((unsigned long)M + (unsigned long)H *60)%1440

/*******初始化時使用**********/
unsigned char RTC_RMem[7];   //S35390專用讀取記憶體
unsigned char RTC_WMem[7];   //S35390專用寫入記憶體

/*
unsigned long EncodeTotalMinute(Y,M,D,H,NN){
  unsigned long EnT= ((unsigned long)SystemDateTime.Year*365*1440)+
                     ((unsigned long)SystemDateTime.Month*12*30*1440)+
                     ((unsigned long)SystemDateTime.Day*1440)+
                     ((unsigned long)SystemDateTime.Hour*24)+
                     ((unsigned long)SystemDateTime.Minute);
  return EnT;
} 
*/

unsigned char BCD2INT(unsigned char BCD){
  return (BCD>>4)*10+(BCD&0x0f);
}

unsigned char INT2BCD(const unsigned char INT){
  return ((INT/10)<<4)+(INT%10);
}

void SetDefaultTime(unsigned int Y,unsigned char M,unsigned char D,unsigned char H,unsigned char NN,unsigned char S){
   DefDateTime.Year=Y;
   DefDateTime.Month=M;
   DefDateTime.Day=D;
   DefDateTime.Hour=H;
   DefDateTime.Minute=NN;
   DefDateTime.Second=S;
}


void SETRTC_To_S35390(){
  I2CCLOCK_INIT();
  asm("ADD  #002H,SP");  
  
  unsigned char TimeData[7]={INT2BCD((DefDateTime.Year-2000)),
                             INT2BCD((DefDateTime.Month&0xff)),
                             INT2BCD((DefDateTime.Day&0xff)),
                             INT2BCD((DefDateTime.Hour&0xff)),
                             INT2BCD((DefDateTime.Minute&0xff)),
                             INT2BCD((DefDateTime.Second&0xff))
                            };
//  0x09,0x12,0x31,0x22,0x59,0x49
  for(int i=0;i<7;i++){
    RTC_WMem[i]=TimeData[i];
  }
  

  I2CCLOCK_SET();
  asm("ADD  #002H,SP");  
}


void GETRTC_From_S35390(){
  
  P3DIR |= BIT1 | BIT2;
  I2CCLOCK_READTIME();
  asm("ADD  #002H,SP");
 
  if ((RTC_RMem[0]==0)&&(RTC_RMem[1]==0)&(RTC_RMem[2]==0)&&(RTC_RMem[3]==0)&&(RTC_RMem[4]==0)){   //代表RTC可能斷電了
      SystemDateTime.Year=DefDateTime.Year;
      SystemDateTime.Month=DefDateTime.Month;
      SystemDateTime.Day=DefDateTime.Day;
      SystemDateTime.Hour=DefDateTime.Hour;
      SystemDateTime.Minute=DefDateTime.Minute;
      SystemDateTime.Second=DefDateTime.Second; 
  }else{
      SystemDateTime.Year=BCD2INT(RTC_RMem[0]);
      SystemDateTime.Month=BCD2INT(RTC_RMem[1]);
      SystemDateTime.Day=BCD2INT(RTC_RMem[2]);
      SystemDateTime.Hour=BCD2INT(RTC_RMem[3]);
      SystemDateTime.Minute=BCD2INT(RTC_RMem[4]);
      SystemDateTime.Second=BCD2INT(RTC_RMem[5]);
  }
}


void SetRTCTime(unsigned int y,unsigned char m,unsigned char d,unsigned char h,unsigned char n,unsigned char s){

  RTCCTL01 |= RTCHOLD;               // Disable RTC
  // Init time
  RTCSEC =  s;                       // Set Seconds
  RTCMIN =  n;                       // Set Minutes
  RTCHOUR = h;                       // Set Hours

  // Init date
  RTCDOW =  3;                       // Set DOW
  RTCDAY =  d;                       // Set Day
  RTCMON =  m;                       // Set Month
  RTCYEAR = y;                       // Set Year
  
  RTCCTL01 &= ~RTCHOLD;                 // Enable RTC
}


void GetTimeFromRTC(){  //從430內部的RTC取得時間並更新
  SystemDateTime.Second=RTCSEC;                      // Set Seconds
  SystemDateTime.Minute=RTCMIN;                      // Set Minutes
  SystemDateTime.Hour=RTCHOUR;                       // Set Hours
  SystemDateTime.Day=RTCDAY;                         // Set Day
  SystemDateTime.Month=RTCMON;                       // Set Month
  SystemDateTime.Year=RTCYEAR;                       // Set Year
}


unsigned long  EncodeNow(){
  unsigned long EncodeData=0;
  EncodeData=((unsigned long)SystemDateTime.Year*13*32*24*60)+
             ((unsigned long)SystemDateTime.Month*32*24*60)+
             ((unsigned long)SystemDateTime.Day*24*60)+  
             ((unsigned long)SystemDateTime.Hour*60)+  
             (unsigned long)SystemDateTime.Minute;
  return EncodeData;
}

void Sync_Time(){
  
  GETRTC_From_S35390();
  //GetTimeFromRTC();
  
  SystemDateTime.SystemTotalMinute=EncodeMinute(SystemDateTime.Hour,SystemDateTime.Minute);
  
  SystemDateTime.SystemTotalHour=((unsigned long)SystemDateTime.Hour)+
                                 ((unsigned long)SystemDateTime.Day*24)+
                                 ((unsigned long)SystemDateTime.Month*720)+
                                 ((unsigned long)SystemDateTime.Year*8640);
  SystemDateTime.EncodeTime=EncodeNow();
  SystemDateTime.secCounter=secCounter;
}




void Init_RTC(){

  GETRTC_From_S35390();
  
  
  RTCCTL01 = //RTCBCD+                    //BCD mode
             RTCHOLD+                   // RTC enable
             RTCMODE+
             RTCTEVIE+                  // enable RTC interrupt
             RTCAIE;                    // alarm every Minute
                                   
                                        
  // Init time
  RTCSEC =  SystemDateTime.Second;                     // Set Seconds
  RTCMIN =  SystemDateTime.Minute;                     // Set Minutes
  RTCHOUR = SystemDateTime.Hour;                       // Set Hours

  // Init date
  RTCDOW =  3;                                        // Set DOW
  RTCDAY =  SystemDateTime.Day;                       // Set Day
  RTCMON =  SystemDateTime.Month;                     // Set Month
  RTCYEAR = SystemDateTime.Year;                      // Set Year

  RTCCTL01 &= ~RTCHOLD;                               // Enable RTC
}


#pragma vector=RTC_VECTOR
__interrupt void RTC(void)
{
  RTCCTL01 &= ~RTCTEVIFG;
  DriverFlag.RTCTriger=1;
}
