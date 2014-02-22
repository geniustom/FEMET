#ifndef FlowStruct
#define FlowStruct

/*************************************************************************
;                       STATE PIRORITY
*************************************************************************/
//---------待機模式---------------------------
#define State_NormalStandBy       10          //初始狀態的待機模式
//---------每閒置5分鐘自動啟動---------------
#define State_SystemCheck         60          //系統檢測模式
//---------系統回報---------------------------
#define State_SystemReport        40          //系統回報模式
//---------通訊模式---------------------------
#define State_StartLine           30          //撥出通訊
//---------用藥提醒---------------------------
#define State_Alarm               70          //用藥提醒模式
//---------客服模式---------------------------
#define State_Service             80          //客服模式
//---------生理資料傳輸模式-------------------
#define State_HealthData          90          //生理資料傳輸模式

/*************************************************************************
;                       State Structure
*************************************************************************/
typedef struct{
    void (*OnEnter)(void);                       //進入節點的FUNTION POINT
    void (*OnExit)(void);                        //離開節點的FUNTION POINT
    void (*PreExit)(void);                       //進入下一個結點後的前一個結點的離開事件
    void (*OnWork)(void);                        //離開節點的FUNTION POINT
    void (*OnDTMF)(void);                        //當收到DTMF時的FUNTION POINT
    unsigned char *NAME;
    unsigned char State;
    unsigned char Step;                          //0:enter,1:work,2:dtmf,3:exit
}StateNode;

extern StateNode A002State;          //描述目前系統所屬狀態的結構


extern void InitFlow();
extern void GoToFlow(unsigned char StateID);

//==================================Flow_Service==============================
extern unsigned char ServiceCallIndex;
extern void Service_Enter();
extern void Service_Exit();
extern void Service_Work();
//==============================Flow_NormalStandby============================
extern void ServicePress();
extern void CancelPress();
extern void CancelLongPress();
extern void GetRF(unsigned char ID);
extern void NormalStandBy_Enter();
extern void NormalStandBy_Exit();
extern void NormalStandBy_Work();
extern void TestQueueSend();
//==================================Flow_Alarm================================
extern unsigned char NowIsAlarm;
extern void AlarmStart(unsigned char ID);
extern void AlarmStop();
extern void Alarm_Enter();
extern void Alarm_Exit();
extern void Alarm_Work();
//================================Flow_StartLine==============================
extern void StartLine_Enter();
extern void StartLine_Exit();
extern void StartLine_Work();
//==============================Flow_SystemCheck============================
extern unsigned char NowIsSystemCheck;
extern void SystemCheck_Enter();
extern void SystemCheck_Exit();
extern void SystemCheck_Work();
extern void CheckRFBTtoLED();
//==============================Flow_SystemReport============================

#endif