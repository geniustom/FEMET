#ifndef DriverLib
#define DriverLib

#include <msp430x54x.h>
#include "PinDefine.h"
#include "SystemCLK.h"

/*
########################################################################################
                                        軟體介面API
########################################################################################
*/
#define MSP430Clock 8000000

//==========================================================內部FLASH存取
extern void  flash_write_word (unsigned int value,unsigned int address);
extern void  flash_write_Block (unsigned int address,unsigned char const *FBuf,unsigned int Length);
extern void flash_erase_multi_segments (unsigned int Seg_Address,unsigned int Number_of_segments);
//===========================AllDriver=========================
extern void DriverRoutin();
//===========================忙音檢測==========================
extern unsigned char DetBusy();
extern void DetBusyLo();
extern void DetBusyHi();
//============================Button===========================
#define ServiceButton 1
#define CancelButton  2

typedef struct{
  void (*ServiceCallBack)();        //當服務鈕按下又放開引動的CALL BACK FUNCTION
  void (*CancelCallBack)();         //當取消鈕按下又放開引動的CALL BACK FUNCTION
  void (*ServiceLongCallBack)();    //當服務鈕按超過3秒引動的CALL BACK FUNCTION
  void (*CancelLongCallBack)();     //當取消鈕按超過3秒引動的CALL BACK FUNCTION
  unsigned long ServicePressTime;
  unsigned long CancelPressTime;
  unsigned long LongPressTime;
}ButtonList;
extern ButtonList DeviceButton;
extern void ButtonSignal(unsigned char ButtonID,unsigned char P0R1); //按下為0,放開為1
extern void CheckButtonPress(unsigned char ButtonID);
extern void InitButton(unsigned long LongPressTime,void (*ServiceCallBack)(),void (*CancelCallBack)(),void (*ServiceLongCallBack)(),void (*CancelLongCallBack)());
//==============================RF=============================
typedef struct{
  unsigned int Code[8];                 //8組壓扣編碼
  unsigned char ISEnable[8];            //8組壓扣開關
  unsigned char RFBtIsLow[8];           //8組壓扣電池 0:有電 1:沒電
  unsigned int SwitchInterval;          //掃描間隔ms
  unsigned char ScanIndex;              //目前掃描到的組別
  unsigned char LockKey;                //鎖定目前的KEY 不予變換
  void(*RFCallBack)(unsigned char ID); //當RF引動時的CALL BACK FUNCTION，並回傳引動的壓扣編號
}RFStruct;  
extern RFStruct RF;
extern void SwitchRFCode();
extern void DetRF_VT();
extern void InitRF(void(*RFCallBack)(unsigned char ID));
extern unsigned char ByteReverse(unsigned char Input);  //位元反轉
//=============================UART============================
#define COM0  0
#define COM1  1
#define COM2  2
#define COM3  3
extern void OpenUart(unsigned char Port,unsigned long Baudrate,void (*CallBackFunction)(unsigned char));
extern void SendTextToUart(unsigned char Port,const unsigned char *SBUF,unsigned int length);
extern void SendByteToUart(unsigned char Port,unsigned char SBUF);
//=============================RTC============================

typedef struct{
    unsigned int Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
    unsigned long SystemTotalMinute;
    unsigned long SystemTotalHour;
    unsigned long SystemReportHour;
    unsigned long EncodeTime;
    unsigned long secCounter;   //開機之後所經過的秒數
}DateTime;

typedef struct{
    unsigned int Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
}DefaultDateTime;

extern DefaultDateTime DefDateTime;
extern DateTime SystemDateTime;
extern void Init_RTC();
extern void Sync_Time();
extern void SETRTC_To_S35390();
extern void SetDefaultTime(unsigned int Y,unsigned char M,unsigned char D,unsigned char H,unsigned char NN,unsigned char S);
//=============================Alarm============================
typedef struct{
    unsigned char NO1_Hour;
    unsigned char NO1_Minute;
    unsigned char NO1_Contiune;
    unsigned char NO2_Hour;
    unsigned char NO2_Minute;
    unsigned char NO2_Contiune;
    unsigned char NO3_Hour;
    unsigned char NO3_Minute;
    unsigned char NO3_Contiune;
    unsigned char NO4_Hour;
    unsigned char NO4_Minute;
    unsigned char NO4_Contiune;
    
    unsigned char AlarmTable[1440]; //1天有1440分鐘，每次開機時，將會叫的分鐘數寫入這個表格
    unsigned int  AlarmStart[4];    //0~3組鬧鈴的啟動時間
    unsigned char AlarmTrigger[4];  //0~3組鬧鈴的是否已啟動
    
    unsigned char SystemRingBack1;   //鬧鈴開關1
    unsigned char SystemRingBack2;   //鬧鈴開關2
    unsigned char SystemRingBack3;   //鬧鈴開關3
    unsigned char SystemRingBack4;   //鬧鈴開關3
    unsigned char CancelRing;        //關閉鬧鈴
    unsigned char RingISStart;       //鬧鈴事件觸發
    
    unsigned long SystemReportStartTime;  //系統回報開始的分鐘數
}AlarmSetting;
extern AlarmSetting SystemAlarm;
extern void InitAlarm(void (*AlarmStartCallBack)(unsigned char AlarmID),void (*AlarmStopCallBack)());
extern void CheckAlarm();
extern void SyncAlarm();
extern void StopAlarm();  //Program端要結束鬧鈴時，呼叫此函數
//=============================LED============================
typedef struct{
  unsigned char LEDType;
  unsigned char LEDEnable;
  unsigned int  Darkms;
  unsigned int  Lightms;  
  unsigned long DelayLms; 
  unsigned long DelayDms; 
}LED;

#define LED_Power       LEDList[0]
#define LED_BT          LEDList[1]
#define LED_RFBT        LEDList[2]
#define LED_NowIsHelp   LEDList[3]
#define LED_LineError   LEDList[4]
#define LED_HelpError   LEDList[5]

extern LED LEDList[6];
extern void InitLEDState();
extern void SyncLED();
extern void SetLEDState(LED *LEDA,unsigned int LightDealyms,unsigned int DarkDealyms);

//=============================WDT============================
extern unsigned long long msecCounter;
extern unsigned long long secCounter;
extern void ResetMCUByPC();
extern void ResetMCUByPMM();
extern void ResetMCUByWDT();
extern void InitWDT();
extern void Delayms(unsigned long ms);
//===========================BUZZER==========================
extern void InitBuzzer(unsigned char BuzzerOn);
extern void BuzzerBeep(unsigned long time);
extern void BuzzerRing();
extern void TelRing();
/*
########################################################################################
                                        內部硬體介面Interface
########################################################################################
*/
typedef struct{
    unsigned char ResetSystem; 
    unsigned char NeedRoutin;                       //RW       當系統需進行例行工事時，須執行
//------------------------檢測輸入(IO)---------------------
    unsigned char ACState;                          //R        AC電源是否正常 0=不正常 1=正常
    unsigned char BTState;                          //R        電池電源是否正常 0=不正常 1=正常
    unsigned char RFBTIsErr;                        //R        壓扣電池電源是否正常 0=不正常 1=正常
    unsigned char LineIsErr;                        //R        局線是否沒接
    unsigned char MeaDev;                           //R        High：華廣血糖計，Low：百略血壓計
//------------------------輸入訊號(IO)----------------- 
    unsigned char ServicePress;                     //R        求救鈕被按下
    unsigned char CancelPress;                      //R        取消鈕被按下
    unsigned char ServiceLongPress;                 //R        長按求救鈕
    unsigned char CancelLongPress;                  //R        長按求救鈕
    unsigned char RFPress;                          //R        壓扣鈕被按下
    unsigned char RFLock;                           //RW       壓扣被按下的時候，要所住IO PORT的狀態
    //unsigned char RFBTIsErr;                      //R        偵測到忙音
    unsigned int  RFIN_Code;                        //RW       當壓扣按下時，在中斷中取得ADDRESS
//-----------------------主機線路控制(IO)----------------------
    unsigned char Phone0Gateway1;                   //R/W      電話線使用權 0=電話 1=GATEWAY
    unsigned char TentelOn;                         //R/W      開啟國洋話機
//-----------------------免持控制(IO)----------------------
    unsigned char MicState;                         //R/W     免持聽筒的麥克風是否開啟 0=關閉 1=開啟
    unsigned char SpeakState;                       //R/W     免持聽筒的喇叭是否開啟 0=關閉 1=開啟
    unsigned char KeepAllAlarm;                     //R/W     輔助控制程式的狀態
//-----------------------BUZZER控制(IO)----------------------
    unsigned char BuzzerState;                       //R/W     BUZZER是否發聲 0=關閉 1=開啟
    unsigned char BuzzerOn;
//-----------------------RTC控制(IO)----------------------
    unsigned char RTCTriger;
//-----------------------忙音檢測/撥號音檢測--------------
    unsigned char PhoneBusy;
    unsigned char NowIsDialTone;
//-----------------------RD模式---------------------------
    unsigned char RDMode;
    unsigned char RDModeStateChange;
//-----------------------主機需要撥號----------------------
    unsigned char NeedReport;
//-----------------------RFID資訊--------------------------
    unsigned long RFIDCardNumber;           //讀到的RFID卡號
    unsigned long RFIDCardNumber8dig;       //讀到的RFID卡號8碼
    unsigned char RFIDCardDetect;         //不斷更新，若偵測到則為1
}IOFlag;

extern IOFlag DriverFlag;
extern void InitInterruptIO();
extern void InitPort();
extern void SetPinSync(IOFlag *Flag);
extern void GetPinSync(IOFlag *Flag);
//=============================LED============================
extern void SetVoice(unsigned char VLevel);
extern unsigned char GetVoice();
//============================VOICE===========================
extern void InitRFID();
extern void ReadRFID();
//============================RFID===========================

#endif