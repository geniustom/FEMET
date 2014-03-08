#include <msp430x54x.h>

//--------------------------------P1-------------------------
#define RF_C8         BIT0    //I	RF掃描CODE的BIT8
#define RF_C9         BIT1    //I	RF掃描CODE的BIT9
#define RF_C10        BIT3    //I	RF接收(壓扣沒電)
#define RF_C11        BIT2    //I	RF接收(壓扣)
#define KEY_Help      BIT4    //I	客服按鈕
#define KEY_Cancel    BIT5    //I	取消按鈕
#define DET_Busy      BIT6    //I	忙音偵測PIN
#define DET_RF        BIT7    //I	RF偵測PIN(VT)
//--------------------------------P2-------------------------
#define DET_MeaDevice BIT5    //I       High：華廣血糖計，Low：百略血壓計
#define DET_Line      BIT7    //I       局線是否偵測到48V
//--------------------------------P3-------------------------
#define RTC_SDA       BIT1    //I/O	RTC的SDA
#define RTC_SCL       BIT2    //O	RTC的SCL
#define CON_DCDC      BIT3    //O	DC/DC的RESET PIN
#define UART0_TX      BIT4    //IO	UART0_TX  RFID
#define UART0_RX      BIT5    //IO	UART0_RX  RFID
#define CON_Buzzer    BIT6    //O	BUZZER警報器
#define CON_SPK       BIT7    //O       喇叭控制
//--------------------------------P4-------------------------
#define RF_C0         BIT0    //O	RF掃描CODE的BIT0
#define RF_C1         BIT1    //O	RF掃描CODE的BIT1
#define RF_C2         BIT2    //O	RF掃描CODE的BIT2
#define RF_C3         BIT3    //O	RF掃描CODE的BIT3
#define RF_C4         BIT4    //O	RF掃描CODE的BIT4
#define RF_C5         BIT5    //O	RF掃描CODE的BIT5
#define RF_C6         BIT6    //O	RF掃描CODE的BIT6
#define RF_C7         BIT7    //O	RF掃描CODE的BIT7
//--------------------------------P5-------------------------
#define CON_PorG      BIT4    //O	電話/主機切換PIN
#define CON_MIC       BIT5    //O	MIC開關
#define UART1_TX      BIT6    //IO	UART1_TX  血壓計
#define UART1_RX      BIT7    //IO	UART1_RX  血壓計

//--------------------------------P6-------------------------
#define DET_AC        BIT0    //I	外部電壓偵測PIN
#define DET_DC        BIT1    //I	電池電壓偵測PIN
#define LED_AC        BIT2    //O	電源指示LED
#define LED_DC        BIT3    //O	電池指示LED
#define LED_Call      BIT4    //O	警報救援LED
#define LED_RFLow     BIT5    //O	壓扣沒電LED
#define LED_LineErr   BIT6    //O	線路異常LED
#define LED_CallErr   BIT7    //O	外撥失敗LED

//--------------------------------P7-------------------------

//--------------------------------P8-------------------------

//--------------------------------P9-------------------------
#define UART2_TX      BIT4    //IO	UART2_TX  國洋話機
#define UART2_RX      BIT5    //IO	UART2_RX  國洋話機

//--------------------------------P10------------------------
#define UART3_TX      BIT4    //IO	UART2_TX  PC端程式
#define UART3_RX      BIT5    //IO	UART2_RX  PC端程式

//--------------------------------P11------------------------

//==============================================================================
