#ifndef FlowStruct
#define FlowStruct

/*************************************************************************
;                       STATE PIRORITY
*************************************************************************/
//---------�ݾ��Ҧ�---------------------------
#define State_NormalStandBy       10          //��l���A���ݾ��Ҧ�
//---------�C���m5�����۰ʱҰ�---------------
#define State_SystemCheck         60          //�t���˴��Ҧ�
//---------�t�Φ^��---------------------------
#define State_SystemReport        40          //�t�Φ^���Ҧ�
//---------�q�T�Ҧ�---------------------------
#define State_StartLine           30          //���X�q�T
//---------���Ĵ���---------------------------
#define State_Alarm               70          //���Ĵ����Ҧ�
//---------�ȪA�Ҧ�---------------------------
#define State_Service             80          //�ȪA�Ҧ�
//---------�Ͳz��ƶǿ�Ҧ�-------------------
#define State_HealthData          90          //�Ͳz��ƶǿ�Ҧ�

/*************************************************************************
;                       State Structure
*************************************************************************/
typedef struct{
    void (*OnEnter)(void);                       //�i�J�`�I��FUNTION POINT
    void (*OnExit)(void);                        //���}�`�I��FUNTION POINT
    void (*PreExit)(void);                       //�i�J�U�@�ӵ��I�᪺�e�@�ӵ��I�����}�ƥ�
    void (*OnWork)(void);                        //���}�`�I��FUNTION POINT
    void (*OnDTMF)(void);                        //����DTMF�ɪ�FUNTION POINT
    unsigned char *NAME;
    unsigned char State;
    unsigned char Step;                          //0:enter,1:work,2:dtmf,3:exit
}StateNode;

extern StateNode A002State;          //�y�z�ثe�t�Ω��ݪ��A�����c


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