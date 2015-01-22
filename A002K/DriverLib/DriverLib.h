#ifndef DriverLib
#define DriverLib

#include <msp430x54x.h>
#include "PinDefine.h"
#include "SystemCLK.h"

/*
########################################################################################
                                        �n�餶��API
########################################################################################
*/
#define MSP430Clock 8000000

//==========================================================����FLASH�s��
extern void  flash_write_word (unsigned int value,unsigned int address);
extern void  flash_write_Block (unsigned int address,unsigned char const *FBuf,unsigned int Length);
extern void flash_erase_multi_segments (unsigned int Seg_Address,unsigned int Number_of_segments);
//===========================AllDriver=========================
extern void DriverRoutin();
//===========================�����˴�==========================
extern unsigned char DetBusy();
extern void DetBusyLo();
extern void DetBusyHi();
//============================Button===========================
#define ServiceButton 1
#define CancelButton  2

typedef struct{
  void (*ServiceCallBack)();        //��A�ȶs���U�S��}�ްʪ�CALL BACK FUNCTION
  void (*CancelCallBack)();         //������s���U�S��}�ްʪ�CALL BACK FUNCTION
  void (*ServiceLongCallBack)();    //��A�ȶs���W�L3��ްʪ�CALL BACK FUNCTION
  void (*CancelLongCallBack)();     //������s���W�L3��ްʪ�CALL BACK FUNCTION
  unsigned long ServicePressTime;
  unsigned long CancelPressTime;
  unsigned long LongPressTime;
}ButtonList;
extern ButtonList DeviceButton;
extern void ButtonSignal(unsigned char ButtonID,unsigned char P0R1); //���U��0,��}��1
extern void CheckButtonPress(unsigned char ButtonID);
extern void InitButton(unsigned long LongPressTime,void (*ServiceCallBack)(),void (*CancelCallBack)(),void (*ServiceLongCallBack)(),void (*CancelLongCallBack)());
//==============================RF=============================
typedef struct{
  unsigned int Code[8];                 //8�������s�X
  unsigned char ISEnable[8];            //8�������}��
  unsigned char RFBtIsLow[8];           //8�������q�� 0:���q 1:�S�q
  unsigned int SwitchInterval;          //���y���jms
  unsigned char ScanIndex;              //�ثe���y�쪺�էO
  unsigned char LockKey;                //��w�ثe��KEY �����ܴ�
  void(*RFCallBack)(unsigned char ID); //��RF�ްʮɪ�CALL BACK FUNCTION�A�æ^�Ǥްʪ������s��
}RFStruct;  
extern RFStruct RF;
extern void SwitchRFCode();
extern void DetRF_VT();
extern void InitRF(void(*RFCallBack)(unsigned char ID));
extern unsigned char ByteReverse(unsigned char Input);  //�줸����
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
    unsigned long secCounter;   //�}������Ҹg�L�����
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
    
    unsigned char AlarmTable[1440]; //1�Ѧ�1440�����A�C���}���ɡA�N�|�s�������Ƽg�J�o�Ӫ��
    unsigned int  AlarmStart[4];    //0~3�վx�a���Ұʮɶ�
    unsigned char AlarmTrigger[4];  //0~3�վx�a���O�_�w�Ұ�
    
    unsigned char SystemRingBack1;   //�x�a�}��1
    unsigned char SystemRingBack2;   //�x�a�}��2
    unsigned char SystemRingBack3;   //�x�a�}��3
    unsigned char SystemRingBack4;   //�x�a�}��3
    unsigned char CancelRing;        //�����x�a
    unsigned char RingISStart;       //�x�a�ƥ�Ĳ�o
    
    unsigned long SystemReportStartTime;  //�t�Φ^���}�l��������
}AlarmSetting;
extern AlarmSetting SystemAlarm;
extern void InitAlarm(void (*AlarmStartCallBack)(unsigned char AlarmID),void (*AlarmStopCallBack)());
extern void CheckAlarm();
extern void SyncAlarm();
extern void StopAlarm();  //Program�ݭn�����x�a�ɡA�I�s�����
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
                                        �����w�餶��Interface
########################################################################################
*/
typedef struct{
    unsigned char ResetSystem; 
    unsigned char NeedRoutin;                       //RW       ��t�λݶi��Ҧ�u�ƮɡA������
//------------------------�˴���J(IO)---------------------
    unsigned char ACState;                          //R        AC�q���O�_���` 0=�����` 1=���`
    unsigned char BTState;                          //R        �q���q���O�_���` 0=�����` 1=���`
    unsigned char RFBTIsErr;                        //R        �����q���q���O�_���` 0=�����` 1=���`
    unsigned char LineIsErr;                        //R        ���u�O�_�S��
    unsigned char MeaDev;                           //R        High�G�ؼs��}�p�ALow�G�ʲ������p
//------------------------��J�T��(IO)----------------- 
    unsigned char ServicePress;                     //R        �D�϶s�Q���U
    unsigned char CancelPress;                      //R        �����s�Q���U
    unsigned char ServiceLongPress;                 //R        �����D�϶s
    unsigned char CancelLongPress;                  //R        �����D�϶s
    unsigned char RFPress;                          //R        �����s�Q���U
    unsigned char RFLock;                           //RW       �����Q���U���ɭԡA�n�Ҧ�IO PORT�����A
    //unsigned char RFBTIsErr;                      //R        �����즣��
    unsigned int  RFIN_Code;                        //RW       ���������U�ɡA�b���_�����oADDRESS
//-----------------------�D���u������(IO)----------------------
    unsigned char Phone0Gateway1;                   //R/W      �q�ܽu�ϥ��v 0=�q�� 1=GATEWAY
    unsigned char TentelOn;                         //R/W      �}�Ұ�v�ܾ�
//-----------------------�K������(IO)----------------------
    unsigned char MicState;                         //R/W     �K��ť�������J���O�_�}�� 0=���� 1=�}��
    unsigned char SpeakState;                       //R/W     �K��ť������z�O�_�}�� 0=���� 1=�}��
    unsigned char KeepAllAlarm;                     //R/W     ���U����{�������A
//-----------------------BUZZER����(IO)----------------------
    unsigned char BuzzerState;                       //R/W     BUZZER�O�_�o�n 0=���� 1=�}��
    unsigned char BuzzerOn;
//-----------------------RTC����(IO)----------------------
    unsigned char RTCTriger;
//-----------------------�����˴�/�������˴�--------------
    unsigned char PhoneBusy;
    unsigned char NowIsDialTone;
//-----------------------RD�Ҧ�---------------------------
    unsigned char RDMode;
    unsigned char RDModeStateChange;
//-----------------------�D���ݭn����----------------------
    unsigned char NeedReport;
//-----------------------RFID��T--------------------------
    unsigned long RFIDCardNumber;           //Ū�쪺RFID�d��
    unsigned long RFIDCardNumber8dig;       //Ū�쪺RFID�d��8�X
    unsigned char RFIDCardDetect;         //���_��s�A�Y������h��1
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