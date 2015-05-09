
#ifndef SystemConfig_H

#define SystemConfig_H

#define QueueData_Addr 0xE000
const unsigned char QueueDataBackup[2048]                @QueueData_Addr;

#define Emergency_Addr 0xF600
const unsigned char Emergency_Flag                       @Emergency_Addr=0;
const unsigned char RFBTLow_Flag[8]                      @Emergency_Addr+0x01;

#define SystemConfig_BackAddr 0xF800
const unsigned char SystemConfig_BackData[256]           @SystemConfig_BackAddr;

#define SystemConfig_Addr 0xFA00

const unsigned char SystemConfig_FirstReport             @SystemConfig_Addr+0x00=0; 
const unsigned int  SystemConfig_FirstReportYear         @SystemConfig_Addr+0x02=2010; 
const unsigned char SystemConfig_FirstReportMonth        @SystemConfig_Addr+0x04=1; 
const unsigned char SystemConfig_FirstReportDate         @SystemConfig_Addr+0x05=1; 
const unsigned char SystemConfig_FirstReportHour         @SystemConfig_Addr+0x06=12; 
const unsigned char SystemConfig_FirstReportMinute       @SystemConfig_Addr+0x07=0; 
const unsigned char SystemConfig_FirstReportSecond       @SystemConfig_Addr+0x08=0; 

const unsigned int  SystemConfig_SystemReportYear        @SystemConfig_Addr+0x10=2010;
const unsigned char SystemConfig_SystemReportMonth       @SystemConfig_Addr+0x12=1;
const unsigned char SystemConfig_SystemReportDate        @SystemConfig_Addr+0x13=1;
const unsigned char SystemConfig_SystemReportHour        @SystemConfig_Addr+0x14=12;
const unsigned char SystemConfig_SystemReportContinue    @SystemConfig_Addr+0x15=24;

const unsigned char SystemConfig_SystemCheckTimeout      @SystemConfig_Addr+0x16=30;   //系統自我檢測時間

const unsigned int  SystemConfig_CustomerID              @SystemConfig_Addr+0x20=0;
const unsigned char SystemConfig_BatchTransfer           @SystemConfig_Addr+0x22=49;  //49:單筆傳送,51:批次傳送
const unsigned char SystemConfig_BuzzerMode              @SystemConfig_Addr+0x23=1;
const unsigned char SystemConfig_QueueRetryCount         @SystemConfig_Addr+0x24=10;
const unsigned char SystemConfig_DataAutoDelete          @SystemConfig_Addr+0x25=1;   //按下壓扣自動刪除 0否 1是
const unsigned char SystemConfig_DebugModeEnable         @SystemConfig_Addr+0x26=0;

const unsigned char SystemConfig_AlarmHour1              @SystemConfig_Addr+0x30=8;
const unsigned char SystemConfig_AlarmMinute1            @SystemConfig_Addr+0x31=0;
const unsigned char SystemConfig_AlarmContinue1          @SystemConfig_Addr+0x32=1;

const unsigned char SystemConfig_AlarmHour2              @SystemConfig_Addr+0x33=12;
const unsigned char SystemConfig_AlarmMinute2            @SystemConfig_Addr+0x34=0;
const unsigned char SystemConfig_AlarmContinue2          @SystemConfig_Addr+0x35=1;

const unsigned char SystemConfig_AlarmHour3              @SystemConfig_Addr+0x36=16;
const unsigned char SystemConfig_AlarmMinute3            @SystemConfig_Addr+0x37=0;
const unsigned char SystemConfig_AlarmContinue3          @SystemConfig_Addr+0x38=1;

const unsigned char SystemConfig_AlarmHour4              @SystemConfig_Addr+0x39=20;
const unsigned char SystemConfig_AlarmMinute4            @SystemConfig_Addr+0x3A=0;
const unsigned char SystemConfig_AlarmContinue4          @SystemConfig_Addr+0x3B=1;

const unsigned int  SystemConfig_MachineID1              @SystemConfig_Addr+0x40=8;
const unsigned int  SystemConfig_MachineID2              @SystemConfig_Addr+0x42=16;
const unsigned int  SystemConfig_MachineID3              @SystemConfig_Addr+0x44=24;
const unsigned int  SystemConfig_MachineID4              @SystemConfig_Addr+0x46=32;
const unsigned int  SystemConfig_MachineID5              @SystemConfig_Addr+0x48=40;
const unsigned int  SystemConfig_MachineID6              @SystemConfig_Addr+0x4A=48;
const unsigned int  SystemConfig_MachineID7              @SystemConfig_Addr+0x4C=56;
const unsigned int  SystemConfig_MachineID8              @SystemConfig_Addr+0x4E=64;

const unsigned char SystemConfig_CTINeedPreKey           @SystemConfig_Addr+0x50=0;
const unsigned char SystemConfig_CTIPreKey[8]            @SystemConfig_Addr+0x51={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_ToneTimeout             @SystemConfig_Addr+0x59=15;


//0,8,0,0,3,8,9,8,9,9
const unsigned char SystemConfig_CTIHelpTel1[16]         @SystemConfig_Addr+0x60={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel2[16]         @SystemConfig_Addr+0x70={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel3[16]         @SystemConfig_Addr+0x80={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel4[16]         @SystemConfig_Addr+0x90={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};


/*
const unsigned char SystemConfig_CTIHelpTel1[16]         @SystemConfig_Addr+0x60={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel2[16]         @SystemConfig_Addr+0x70={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel3[16]         @SystemConfig_Addr+0x80={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIHelpTel4[16]         @SystemConfig_Addr+0x90={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
*/
/*
//89135452
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,9,1,3,5,4,5,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,9,1,3,5,4,5,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,9,1,3,5,4,5,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,9,1,3,5,4,5,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
*/
/*
//89135468
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
*/
/*
//89135682
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,9,1,3,5,6,8,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,9,1,3,5,6,8,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,9,1,3,5,6,8,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,9,1,3,5,6,8,2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
*/

//89135911
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,9,1,3,5,9,1,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,9,1,3,5,9,1,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,9,1,3,5,9,1,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,9,1,3,5,9,1,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

/*
//0,8,0,0,3,8,9,8,9,9
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={0,8,0,0,3,8,9,8,9,9,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={0,8,0,0,3,8,9,8,9,9,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={0,8,0,0,3,8,9,8,9,9,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={0,8,0,0,3,8,9,8,9,9,0xff,0xff,0xff,0xff,0xff,0xff};
*/
/*
const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,0,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,0,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,0,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,0,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
*/

const unsigned int  SystemConfig_NowYear                 @SystemConfig_Addr+0xE0=2009; 
const unsigned char SystemConfig_NowMonth                @SystemConfig_Addr+0xE2=3; 
const unsigned char SystemConfig_NowDay                  @SystemConfig_Addr+0xE3=15; 
const unsigned char SystemConfig_NowHour                 @SystemConfig_Addr+0xE4=12; 
const unsigned char SystemConfig_NowMinute               @SystemConfig_Addr+0xE5=0; 
const unsigned char SystemConfig_NowSecond               @SystemConfig_Addr+0xE6=0; 

const unsigned char SystemConfig_SPK_Dial                @SystemConfig_Addr+0xE7=1; 
const unsigned char SystemConfig_SPK_DTMF                @SystemConfig_Addr+0xE8=1; 
const unsigned char SystemConfig_SPK_Voice               @SystemConfig_Addr+0xE9=6; 
const unsigned char SystemConfig_SPK_Talk                @SystemConfig_Addr+0xEA=6; 


//用零散片段的空間來塞
const unsigned long SystemConfig_RfidCode1               @SystemConfig_Addr+0x0A=0;
const unsigned long SystemConfig_RfidCode2               @SystemConfig_Addr+0x18=0;
const unsigned long SystemConfig_RfidCode3               @SystemConfig_Addr+0x1C=0;
const unsigned long SystemConfig_RfidCode4               @SystemConfig_Addr+0x28=0;
const unsigned long SystemConfig_RfidCode5               @SystemConfig_Addr+0x2C=0;
const unsigned long SystemConfig_RfidCode6               @SystemConfig_Addr+0x3C=0;
const unsigned long SystemConfig_RfidCode7               @SystemConfig_Addr+0x5A=0;
const unsigned long SystemConfig_RfidCode8               @SystemConfig_Addr+0xEC=0;
#endif


extern unsigned char Init_PCRS232();



//const unsigned char SystemConfig_CTIHelpTel1[16]         @SystemConfig_Addr+0x60={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIHelpTel2[16]         @SystemConfig_Addr+0x70={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIHelpTel3[16]         @SystemConfig_Addr+0x80={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIHelpTel4[16]         @SystemConfig_Addr+0x90={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

//const unsigned char SystemConfig_CTIDataTel1[16]         @SystemConfig_Addr+0xA0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIDataTel2[16]         @SystemConfig_Addr+0xB0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIDataTel3[16]         @SystemConfig_Addr+0xC0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//const unsigned char SystemConfig_CTIDataTel4[16]         @SystemConfig_Addr+0xD0={8,9,1,3,5,4,6,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
