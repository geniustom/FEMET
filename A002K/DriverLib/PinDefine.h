#include <msp430x54x.h>

//--------------------------------P1-------------------------
#define RF_C8         BIT0    //I	RF���yCODE��BIT8
#define RF_C9         BIT1    //I	RF���yCODE��BIT9
#define RF_C10        BIT3    //I	RF����(�����S�q)
#define RF_C11        BIT2    //I	RF����(����)
#define KEY_Help      BIT4    //I	�ȪA���s
#define KEY_Cancel    BIT5    //I	�������s
#define DET_Busy      BIT6    //I	��������PIN
#define DET_RF        BIT7    //I	RF����PIN(VT)
//--------------------------------P2-------------------------
#define DET_MeaDevice BIT5    //I       High�G�ؼs��}�p�ALow�G�ʲ������p
#define DET_Line      BIT7    //I       ���u�O�_������48V
//--------------------------------P3-------------------------
#define RTC_SDA       BIT1    //I/O	RTC��SDA
#define RTC_SCL       BIT2    //O	RTC��SCL
#define CON_DCDC      BIT3    //O	DC/DC��RESET PIN
#define UART0_TX      BIT4    //IO	UART0_TX  RFID
#define UART0_RX      BIT5    //IO	UART0_RX  RFID
#define CON_Buzzer    BIT6    //O	BUZZERĵ����
#define CON_SPK       BIT7    //O       ��z����
//--------------------------------P4-------------------------
#define RF_C0         BIT0    //O	RF���yCODE��BIT0
#define RF_C1         BIT1    //O	RF���yCODE��BIT1
#define RF_C2         BIT2    //O	RF���yCODE��BIT2
#define RF_C3         BIT3    //O	RF���yCODE��BIT3
#define RF_C4         BIT4    //O	RF���yCODE��BIT4
#define RF_C5         BIT5    //O	RF���yCODE��BIT5
#define RF_C6         BIT6    //O	RF���yCODE��BIT6
#define RF_C7         BIT7    //O	RF���yCODE��BIT7
//--------------------------------P5-------------------------
#define CON_PorG      BIT4    //O	�q��/�D������PIN
#define CON_MIC       BIT5    //O	MIC�}��
#define UART1_TX      BIT6    //IO	UART1_TX  �����p
#define UART1_RX      BIT7    //IO	UART1_RX  �����p

//--------------------------------P6-------------------------
#define DET_AC        BIT0    //I	�~���q������PIN
#define DET_DC        BIT1    //I	�q���q������PIN
#define LED_AC        BIT2    //O	�q������LED
#define LED_DC        BIT3    //O	�q������LED
#define LED_Call      BIT4    //O	ĵ���ϴ�LED
#define LED_RFLow     BIT5    //O	�����S�qLED
#define LED_LineErr   BIT6    //O	�u�����`LED
#define LED_CallErr   BIT7    //O	�~������LED

//--------------------------------P7-------------------------

//--------------------------------P8-------------------------

//--------------------------------P9-------------------------
#define UART2_TX      BIT4    //IO	UART2_TX  ��v�ܾ�
#define UART2_RX      BIT5    //IO	UART2_RX  ��v�ܾ�

//--------------------------------P10------------------------
#define UART3_TX      BIT4    //IO	UART2_TX  PC�ݵ{��
#define UART3_RX      BIT5    //IO	UART2_RX  PC�ݵ{��

//--------------------------------P11------------------------

//==============================================================================
