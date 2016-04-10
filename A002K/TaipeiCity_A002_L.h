#ifndef TaipeiCityLib
#define TaipeiCityLib

#include "DriverLib\DriverLib.h"
#include "SystemConfig.h"
#include "Flow\FlowStruct.h"
#include "TENTEL\Tentel.h"
#include "Measuredev\Measuredev.h"

#define VER "4.30"

#define DS    1               //傳輸成功
#define DF    0               //傳輸失敗


#define CTIMessageQueueLength 64
#define UniqueMessage         100   //代表此事件不可重複
//========================================小事
#define CTIMSG_GatewayBTLow         1   +UniqueMessage
#define CTIMSG_GatewayPowerErr      2   +UniqueMessage
#define CTIMSG_GatewayLineErr       3   +UniqueMessage
//========================================單筆為大事，批次為小事
#define CTIMSG_HealthDataUpload     50
//========================================大事
#define CTIMSG_GatewayCall          52  
#define CTIMSG_SystemReport         53  +UniqueMessage
#define CTIMSG_DeviceBTLow          54  +UniqueMessage
#define CTIMSG_GetRFIDNum           55
   



typedef struct{
    unsigned int  GateWayID;           //主機編號
    unsigned char DeviceID;            //主機是0 第1~8組壓扣為1~8
    unsigned char MsgType;             //訊息種類
    unsigned long EncodeDateTime;     //編碼後的時間    
    unsigned long Data; //最多9位數字
    unsigned int  RetryCount;
    //================================最後輸出編碼=========
    unsigned char MessageStage1[14];   // *(主機編號)(資料)
    unsigned char MessageStage2[14];   // #(壓扣編號)(訊息種類)(時間)(CHKSUM)
}CTIMessage;

typedef struct{
    unsigned int Length;
    unsigned int QRear;
    unsigned int QFront;
    CTIMessage MSGList[CTIMessageQueueLength];
    unsigned char EmptyData[256];
}CTIMessageQueue;

extern unsigned long  EncodeNowDateTime();
extern unsigned long  EncodeDateTime(unsigned char EYear,unsigned char EMonth,unsigned char EDay,unsigned char EHour,unsigned char EMinute);
extern CTIMessageQueue CTIMSGQueue;
extern void CreateCTIMSGQueue(CTIMessageQueue *CQ);
extern void DeleteCTIMSG(CTIMessageQueue *CQ);
extern void DeleteLastMSG(CTIMessageQueue *CQ);
extern void DeleteAllCTIMSG(CTIMessageQueue *CQ);
extern void DeleteRetryData(CTIMessageQueue *CQ);

extern void SendQueueDataToFlash(int *CQ);
extern void GetQueueDataFromFlash(int *CQ);

extern void SendQueueDataToPc(CTIMessageQueue *CQ);
extern void SendQueueSizeToPC(CTIMessageQueue *CQ);
extern void PutCTIMSG(CTIMessageQueue *CQ,unsigned char DeviceID,unsigned char MSGType,unsigned long TimeEncode,unsigned long Data);
extern CTIMessage GetQueueNode(CTIMessageQueue *CQ);
extern unsigned char QueueNeedSendImportantData();
extern unsigned char DataCanRepeat(CTIMessageQueue *CQ,unsigned char DeviceID,unsigned char MSGType,unsigned long TimeEncode,unsigned long Data);


//===========================================CTI FUNCTION===============================================
extern unsigned char DataOut(unsigned char TelID);
extern unsigned char DataIn();
extern unsigned char NeedRemoteSetup;
extern unsigned char NeedSetupTime;
//===========================================Voice FUNCTION===============================================
extern void EnableSpeaker(unsigned char Level);
extern void DisableSpeaker();
extern void SubVoice();
extern void AddVoice();
//===========================================Remote Setup===============================================
extern void InitAllAlarm();
extern void ProcessFEMETCMD(unsigned char BUF);
extern void SendEventToPC(unsigned char EventNum);
extern void SendRFIDToPC(unsigned long RFID);
//===========================================SOP========================================================
extern void CheckSOPMode();
//===========================================MAIN=======================================================
extern void EnableP1P2Int();
//===========================================PC LINK====================================================
#define RS232BUFLength  512
#define PCRs232Port     COM3
#endif