#include  "msp430x23x0.h"


#define GateWayUart     0
#define MicroLifeUart   1
#define WakemaUart      2


/***************************************************    Main.c    ********************************************
***************************************************************************************************************/
extern unsigned char NeedTx;
/***************************************************    HWUart.c    ********************************************
***************************************************************************************************************/
#define HWUartBufLen    16     
#define DongleVER       "3.70百略血壓+華廣血糖          "

typedef struct{
  unsigned int  BufferIndex;
  unsigned long Baudrate;
  void (*CallBackFunction)(unsigned char RX);  //回呼的FUNCTION POINT
  unsigned char HW_UartBUF[HWUartBufLen];
}HW_Uart;

extern HW_Uart HW_UartPort;

extern void SetupHwUart(HW_Uart *HW_UartPort,unsigned long BD);
extern void ResetHWUartBuf(HW_Uart *HW_UartPort);

//extern void SentTextToHwUart(HW_Uart *HW_UartPort,unsigned char *Data,unsigned int length);
//extern void SentByteToHwUart(HW_Uart *HW_UartPort,unsigned char Data);

/***************************************************    MuxUart.c    ********************************************
***************************************************************************************************************/
typedef struct{
  unsigned char NowUsePort;
  HW_Uart *CurrentPort;
  HW_Uart Port[4];
}Mux_Uart;

extern Mux_Uart DongleUart;

extern void InitMuxUart(unsigned char MuxID,unsigned long BD,void (*CF)(unsigned char),unsigned char Init);
extern void ProcessHWUart(unsigned char Rx);
extern void SetupMuxUArt(unsigned char MuxID,unsigned char Init);
extern void SentByteToMuxUart(unsigned char MuxID,unsigned char Data);
extern void SentTextToMuxUart(unsigned char MuxID,unsigned char *Data,unsigned int length);


/***************************************************  DongleLib.c  ********************************************
***************************************************************************************************************/
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

extern DateTime SystemDateTime;

extern unsigned long  EncodeDateTime(unsigned char EYear,unsigned char EMonth,unsigned char EDay,unsigned char EHour,unsigned char EMinute);
extern unsigned long  EncodeNowDateTime();
extern void ShowDataToPC(unsigned long Data,unsigned int len);
extern void ProcessGateWayData(unsigned char Rx);
extern void SendMeasureData(unsigned long M,unsigned long W);
extern void ClearGatewayBuffer();
/*******************************************************  Clock.c   ********************************************
***************************************************************************************************************/
extern void InitCLK();
extern void InitWDT();
extern void Delayms(unsigned long ms);