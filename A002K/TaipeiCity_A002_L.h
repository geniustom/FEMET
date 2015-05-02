#ifndef TaipeiCityLib
#define TaipeiCityLib

#include "DriverLib\DriverLib.h"
#include "SystemConfig.h"
#include "Flow\FlowStruct.h"
#include "TENTEL\Tentel.h"
#include "Measuredev\Measuredev.h"

#define VER "4.20"

#define DS    1               //傳輸成功
#define DF    0               //傳輸失敗

//原共7583每個Queue node 42*16=678 byte 若採省DTMF方案 因28*64=1792 AlarmTable已省1260 =>7583-678-1260+1792=7437 夠用
//原共7583每個Queue node 42*16=678 byte DTMF不動 因42*64=2688 AlarmTable已省1260 => 7583-678-1260+2688=8333 還須瘦身750 byte

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
    unsigned char RetryCount;
    //================================最後輸出編碼=========
    unsigned char MessageStage1[7];   // *(主機編號)(資料)
    unsigned char MessageStage2[7];   // #(壓扣編號)(訊息種類)(時間)(CHKSUM)
    //unsigned char *MessageStage1;   // *(主機編號)(資料)
    //unsigned char *MessageStage2;   // #(壓扣編號)(訊息種類)(時間)(CHKSUM)
}CTIMessage;

typedef struct{
    CTIMessage MSGList[CTIMessageQueueLength];
    unsigned int Length;
    unsigned int QRear;
    unsigned int QFront;
}CTIMessageQueue;

extern unsigned long  EncodeNowDateTime();
extern unsigned long  EncodeDateTime(unsigned char EYear,unsigned char EMonth,unsigned char EDay,unsigned char EHour,unsigned char EMinute);
extern CTIMessageQueue CTIMSGQueue;
extern void CreateCTIMSGQueue(CTIMessageQueue *CQ);
extern void DeleteCTIMSG(CTIMessageQueue *CQ);
extern void DeleteLastMSG(CTIMessageQueue *CQ);
extern void DeleteAllCTIMSG(CTIMessageQueue *CQ);
extern void DeleteRetryData(CTIMessageQueue *CQ);

extern void GetQueueMessageStage(unsigned char souMS[7],unsigned char *des);
extern void SetQueueMessageStage(unsigned char sou[14],unsigned char *desMS);

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