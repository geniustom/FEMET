unit Unit1;

interface

uses
    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, ExtCtrls, SPComm,inifiles, Uart_Mem, XPMan,
  Mask,DateUtils, OleCtrls, SHDocVw, Grids, Buttons;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    GroupBox8: TGroupBox;
    Label1: TLabel;
    COMPORT: TComboBox;
    Label42: TLabel;
    Baudrate: TComboBox;
    Button1: TButton;
    GroupBox9: TGroupBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    GroupBox10: TGroupBox;
    Button6: TButton;
    Button7: TButton;
    INIOPEN: TOpenDialog;
    INISAVE: TSaveDialog;
    Comm1: TComm;
    ProgressBar1: TProgressBar;
    Timer1: TTimer;
    Timer2: TTimer;
    Button8: TButton;
    Timer3: TTimer;
    ReportControl: TTabSheet;
    Label56: TLabel;
    Tel: TEdit;
    SuccMSGEn: TCheckBox;
    SUCCMSG: TMemo;
    Label57: TLabel;
    FailMSGEn: TCheckBox;
    Label58: TLabel;
    FAILMSG: TMemo;
    WEB: TWebBrowser;
    Button9: TButton;
    LogTab: TTabSheet;
    DataLog: TMemo;
    Panel3: TPanel;
    Button10: TButton;
    Panel2: TPanel;
    PageControl3: TPageControl;
    TabSheet6: TTabSheet;
    ARoundDevice: TTabSheet;
    GroupBox11: TGroupBox;
    Label41: TLabel;
    Label40: TLabel;
    Label39: TLabel;
    Label38: TLabel;
    Label37: TLabel;
    Label36: TLabel;
    Label35: TLabel;
    Label34: TLabel;
    Label48: TLabel;
    Label47: TLabel;
    Label11: TLabel;
    PAN_9: TEdit;
    PAN_0: TEdit;
    PAN_10: TEdit;
    PAN_1: TEdit;
    PAN_2: TEdit;
    PAN_3: TEdit;
    PAN_4: TEdit;
    PAN_5: TEdit;
    PAN_6: TEdit;
    PAN_7: TEdit;
    PAN_8: TEdit;
    GroupBox4: TGroupBox;
    TimeStr: TLabel;
    Label17: TLabel;
    Label53: TLabel;
    TimeLabel: TLabel;
    TimeDef: TLabel;
    Label59: TLabel;
    Button11: TButton;
    D2M: TRichEdit;
    GroupBox14: TGroupBox;
    DevLabel: TLabel;
    Label29: TLabel;
    Label51: TLabel;
    Label52: TLabel;
    PageControl2: TPageControl;
    TabSheet3: TTabSheet;
    Label13: TLabel;
    Label15: TLabel;
    GroupBox1: TGroupBox;
    CustomerID: TMaskEdit;
    GroupBox2: TGroupBox;
    BuzzerMode: TRadioButton;
    NonBuzzerMode: TRadioButton;
    GroupBox3: TGroupBox;
    Label20: TLabel;
    Label21: TLabel;
    Label23: TLabel;
    Label26: TLabel;
    Label19: TLabel;
    Label22: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label27: TLabel;
    Label44: TLabel;
    Label49: TLabel;
    Label50: TLabel;
    Alarm1_Hour: TComboBox;
    Alarm1_Minute: TComboBox;
    NonActiveAlarm_1: TCheckBox;
    Alarm2_Minute: TComboBox;
    Alarm2_Hour: TComboBox;
    NonActiveAlarm_2: TCheckBox;
    Alarm3_Minute: TComboBox;
    Alarm3_Hour: TComboBox;
    NonActiveAlarm_3: TCheckBox;
    Alarm1_Continue: TEdit;
    Continue_1: TUpDown;
    Continue_2: TUpDown;
    Alarm2_Continue: TEdit;
    Continue_3: TUpDown;
    Alarm3_Continue: TEdit;
    NonActiveAlarm_4: TCheckBox;
    Alarm4_Hour: TComboBox;
    Alarm4_Minute: TComboBox;
    Alarm4_Continue: TEdit;
    Continue_4: TUpDown;
    GroupBox5: TGroupBox;
    FirstReportDate: TDateTimePicker;
    FirstReportTime: TDateTimePicker;
    FirstReport: TCheckBox;
    GroupBox7: TGroupBox;
    Label43: TLabel;
    Label45: TLabel;
    Label46: TLabel;
    Label55: TLabel;
    LBL_SEC: TLabel;
    SystemReportDate: TDateTimePicker;
    SystemReportHour: TComboBox;
    SystemReportContinue: TEdit;
    UpDown5: TUpDown;
    GroupBox12: TGroupBox;
    BatchSend_0: TRadioButton;
    BatchSend_1: TRadioButton;
    SystemCheckTimeout: TComboBox;
    TabSheet4: TTabSheet;
    TabSheet5: TTabSheet;
    Label33: TLabel;
    CTIPreKey: TEdit;
    GroupBox6: TGroupBox;
    Label18: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    CTINum4: TEdit;
    CTINum3: TEdit;
    CTINum2: TEdit;
    CTINum1: TEdit;
    NeedPreKey: TCheckBox;
    GroupBox13: TGroupBox;
    Label2: TLabel;
    Label5: TLabel;
    Label7: TLabel;
    Label9: TLabel;
    DATATEL_4: TEdit;
    DATATEL_3: TEdit;
    DATATEL_2: TEdit;
    DATATEL_1: TEdit;
    TabSheet8: TTabSheet;
    GroupBox16: TGroupBox;
    DeviceMachineCode_8: TEdit;
    DeviceEnable_8: TCheckBox;
    DeviceEnable_7: TCheckBox;
    DeviceMachineCode_7: TEdit;
    DeviceMachineCode_6: TEdit;
    DeviceEnable_6: TCheckBox;
    DeviceEnable_5: TCheckBox;
    DeviceMachineCode_5: TEdit;
    DeviceMachineCode_4: TEdit;
    DeviceEnable_4: TCheckBox;
    DeviceEnable_3: TCheckBox;
    DeviceMachineCode_3: TEdit;
    DeviceMachineCode_2: TEdit;
    Label3: TLabel;
    DeviceEnable_2: TCheckBox;
    DeviceEnable_1: TCheckBox;
    Label4: TLabel;
    DeviceMachineCode_1: TEdit;
    GroupBox15: TGroupBox;
    DonLabel: TLabel;
    Label54: TLabel;
    Label65: TLabel;
    Label28: TLabel;
    Label60: TLabel;
    Don1: TLabel;
    Don2: TLabel;
    GroupBox18: TGroupBox;
    SPKSel4: TComboBox;
    Label64: TLabel;
    Label63: TLabel;
    SPKSel3: TComboBox;
    SPKSel2: TComboBox;
    Label62: TLabel;
    Label61: TLabel;
    SPKSel1: TComboBox;
    GroupBox17: TGroupBox;
    GroupBox19: TGroupBox;
    Label66: TLabel;
    Label67: TLabel;
    RetryCount: TUpDown;
    RetryCountT: TMaskEdit;
    MeasureAutoDel: TCheckBox;
    QueueTest: TTabSheet;
    Button12: TButton;
    BT_CleanQueue: TButton;
    BT_GetQueue: TButton;
    QueueMemo: TMemo;
    PageControl4: TPageControl;
    TabSheet9: TTabSheet;
    TabSheet10: TTabSheet;
    QueueList: TStringGrid;
    CreateTest: TTabSheet;
    SpeedButton1: TSpeedButton;
    BT_Next: TButton;
    GroupBox20: TGroupBox;
    Label71: TLabel;
    Memo1: TMemo;
    LB_DongleTest: TLabel;
    GroupBox21: TGroupBox;
    Label72: TLabel;
    Label70: TLabel;
    Label73: TLabel;
    Device_BP: TLabel;
    Device_SP: TLabel;
    Device_HR: TLabel;
    GroupBox22: TGroupBox;
    Label77: TLabel;
    Device_MA: TLabel;
    DeviceTestTimer: TTimer;
    Memo2: TMemo;
    K332TEST: TTabSheet;
    GroupBox23: TGroupBox;
    K332ROM: TRichEdit;
    DebugCheck: TCheckBox;
    Button13: TButton;
    QueueSize_LB: TLabel;
    Label68: TLabel;
    CTINAME: TEdit;
    Label69: TLabel;
    GroupBox24: TGroupBox;
    ToneTimeoutTEXT: TEdit;
    Label74: TLabel;
    ToneTimeout: TUpDown;
    Label75: TLabel;
    Button14: TButton;
    Button15: TButton;
    Panel4: TPanel;
    StatusBar1: TStatusBar;
    DonVer: TStatusBar;
    AutoSMS: TCheckBox;
    RFID_Code1: TMaskEdit;
    RFID_Code2: TMaskEdit;
    RFID_Code3: TMaskEdit;
    RFID_Code4: TMaskEdit;
    RFID_Code5: TMaskEdit;
    RFID_Code6: TMaskEdit;
    RFID_Code7: TMaskEdit;
    RFID_Code8: TMaskEdit;
    RFIDNUM: TMemo;
    Button16: TButton;
    RFIDSel: TComboBox;
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FirstReportClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Comm1ReceiveData(Sender: TObject; Buffer: Pointer;
      BufferLength: Word);
    procedure Timer1Timer(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure NeedPreKeyClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Timer2Timer(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
    procedure DeviceMachineCode_1KeyPress(Sender: TObject; var Key: Char);
    procedure DeviceMachineCode_1Change(Sender: TObject);
    procedure Panel2DblClick(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure BT_CleanQueueClick(Sender: TObject);
    procedure BT_GetQueueClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure DeviceTestTimerTimer(Sender: TObject);
    procedure BT_NextClick(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button16Click(Sender: TObject);
  private
    { Private declarations }
  public
    procedure MyException(Sender:TObject;E:Exception); 
  end;

var
  Form1: TForm1;
  ConfigINI:Tinifile;
  WriteReady:integer;
  WriteSuccess:integer;
  WriteFINISH:integer;
  WriteCheckSum:integer;
  ReadSuccessFlag:integer;
  function GetRadioChecked(TorF:boolean):integer;
  function SetRadioChecked(Oorl:integer):boolean;


implementation

uses unit2;

var
TaiDocBUF:array[0..31] of byte;
TaiDocBUFIndex:integer;
{$R *.dfm}
function CheckTaiDoc(BUF:byte):integer;
var
i,j:integer;
SendBUF:char;
const HealthData:array[0..7] of byte=($51,$26,$5D,$00,$3B,$4F,$A5,$03);
const HealthTime:array[0..7] of byte=($51,$25,$4B,$12,$AD,$09,$A5,$2E);
begin
   if BUF=$51 then
   begin
      for i:=0 to 31 do TaiDocBUF[i]:=0;
      TaiDocBUF[0]:=$51;
      TaiDocBUFIndex:=1;
   end
   else
   begin
      TaiDocBUF[TaiDocBUFIndex]:=BUF;
      TaiDocBUFIndex:=TaiDocBUFIndex+1;
      TaiDocBUFIndex:=TaiDocBUFIndex mod 32;
   end;

   if TaiDocBUFIndex=8 then
   begin
      //====收到取得血壓資料的CMD
      if (ord(TaiDocBUF[0])=$51) and (ord(TaiDocBUF[1])=$26) and (ord(TaiDocBUF[6])=$A3) then
      begin
         for j:=0 to 7 do
         begin
            SendBUF:=chr(HealthData[j]);
            sleep(5);
            if form1.Button1.Caption='斷線' then
               form1.Comm1.WriteCommData(@SendBUF,1);
         end;
      end;
      //====收到取得時間的CMD
      if (ord(TaiDocBUF[0])=$51) and (ord(TaiDocBUF[1])=$25)and (ord(TaiDocBUF[6])=$A3)  then
      begin
         for j:=0 to 7 do
         begin
            SendBUF:=chr(HealthTime[j]);
            sleep(5);
            if form1.Button1.Caption='斷線' then
               form1.Comm1.WriteCommData(@SendBUF,1);
         end;
      end;

   end;
end;

procedure Wait(timeout:integer);
var NowTime:integer;
begin
   NowTime:=windows.GetTickCount;
   while (windows.GetTickCount-NowTime)< timeout do
   begin
      application.ProcessMessages;
   end;
end;

function GetRadioChecked(TorF:boolean):integer;
begin
   if TorF then
      result:=1
   else
      result:=0;
end;

function SetRadioChecked(Oorl:integer):boolean;
begin
   if Oorl=1 then
      result:=true
   else
      result:=false;
end;

procedure TForm1.MyException(Sender:TObject;E:Exception);
begin
  if E is EDBEditError then
  BEGIN
    if TMaskEdit(Sender).Name='CustomerID'then
    begin
      showmessage('請輸入0000~9999的四位數字'+#13+'例如:13請輸入0013'+#13+'若要取消編輯,請按ESC鍵');
      TMaskEdit(Sender).SetFocus;
    end;
  end
  else
    Application.ShowException(E); {調用缺省的異常處理}
end; 


procedure TForm1.Button6Click(Sender: TObject);
begin
   PageControl1.TabIndex:=0;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
   PageControl1.TabIndex:=1;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
   if INIOPEN.Execute then
   begin
    INISAVE.FileName:=INIOPEN.FileName;
    ConfigINI:=tinifile.create(INISAVE.FileName);
    FormActivate(nil);
    StatusBar1.SimpleText:='設定檔載入完成';
   end;

end;

procedure TForm1.Button3Click(Sender: TObject);
var
PreLoad,Default:string;
begin
   if INISAVE.Execute then
   begin
   //ConfigINI:=tinifile.create(ExtractFilePath(Application.ExeName)+'\Config.ini');
   ConfigINI:=tinifile.create(INISAVE.FileName);

   GetMEMSetting();                      //將設定值轉MEM
   PreLoad:=MemToSTR();
   ConfigINI.WriteString('TaipeiCity','Setting',PreLoad);
   ConfigINI.WriteString('CTIName','Setting',CTINAME.Text);


   INIOPEN.FileName:= INISAVE.FileName;
   FormActivate(nil);
   StatusBar1.SimpleText:='設定檔儲存完成';
   end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   QueueList.Rows[0].Delimiter:=',';
   QueueList.Rows[0].DelimitedText:='ID,MSG';
   ConfigINI:=tinifile.create(ExtractFilePath(Application.ExeName)+'\Config.ini');
   Application.OnException :=MyException;
   ReportControl.TabVisible:=false;
   LogTab.TabVisible:=false;
end;

procedure TForm1.FirstReportClick(Sender: TObject);
begin
   GroupBox3.Visible:=BuzzerMode.Checked;

   FirstReportDate.Enabled:= FirstReport.Checked;
   FirstReportTime.Enabled:= FirstReport.Checked;
   
   Alarm1_Hour.Enabled:= NonActiveAlarm_1.Checked;
   Alarm1_Minute.Enabled:= NonActiveAlarm_1.Checked;
   Alarm1_Continue.Enabled:= NonActiveAlarm_1.Checked;
   Continue_1.Enabled:= NonActiveAlarm_1.Checked;
   if Continue_1.Enabled=false then Continue_1.Position:=0;

   Alarm2_Hour.Enabled:= NonActiveAlarm_2.Checked;
   Alarm2_Minute.Enabled:= NonActiveAlarm_2.Checked;
   Alarm2_Continue.Enabled:= NonActiveAlarm_2.Checked;
   Continue_2.Enabled:= NonActiveAlarm_2.Checked;
   if Continue_2.Enabled=false then Continue_2.Position:=0;

   Alarm3_Hour.Enabled:= NonActiveAlarm_3.Checked;
   Alarm3_Minute.Enabled:= NonActiveAlarm_3.Checked;
   Alarm3_Continue.Enabled:= NonActiveAlarm_3.Checked;
   Continue_3.Enabled:= NonActiveAlarm_3.Checked;
   if Continue_3.Enabled=false then Continue_3.Position:=0;

   Alarm4_Hour.Enabled:= NonActiveAlarm_4.Checked;
   Alarm4_Minute.Enabled:= NonActiveAlarm_4.Checked;
   Alarm4_Continue.Enabled:= NonActiveAlarm_4.Checked;
   Continue_4.Enabled:= NonActiveAlarm_4.Checked;
   if Continue_4.Enabled=false then Continue_4.Position:=0;

   CTIPreKey.Enabled:=NeedPreKey.Checked;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
   TimeDef.Caption:='尚未測試';
   DevLabel.Caption:='尚未測試';
   DonLabel.Caption:='尚未測試';
   Don1.Caption:='';
   Don2.Caption:='';

   Comm1.StopComm;
   Comm1.CommName:= '\\.\'+COMPORT.Text;
   Comm1.BaudRate:= strtoint(Baudrate.Text);
   if Button1.Caption='連線' then
   begin
      try
        Comm1.StartComm;
      finally
        Button1.Caption:='斷線';
      end;
   end
   else
      Button1.Caption:='連線';


   if Button1.Caption='連線' then
   begin
      Button4.Enabled:=false;
      Button5.Enabled:=false;
      Button8.Enabled:=true;
      SpeedButton1.Enabled:=false;
      DonVer.SimpleText:='';
   end;
   if Button1.Caption='斷線' then
   begin
      Button4.Enabled:=true;
      Button5.Enabled:=true;
      Button8.Enabled:=false;
      SpeedButton1.Enabled:=true;
   end;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
i,chksum:integer;
WriteCMD:pchar;
WriteData:char;
begin
   Button4.Enabled:=false;
   Button5.Enabled:=false;
   
   StatusBar1.SimpleText:='重新啟動宅端機以確保穩定更新';
   Button1Click(nil);
   Button1Click(nil);
   StatusBar1.SimpleText:='重新啟動宅端機等待中...';

   for i:=0 to 200 do
   begin
      Button4.Enabled:=false;
      Button5.Enabled:=false;
      wait(10);
   end;

   ProgressBar1.Position:=0;
   WriteReady:=0;
   WriteFINISH:=0;
   GetMEMSetting();
//===================================================
   WriteCMD:='@FEMET';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(1);
   end;
   wait(100);
//===================================================
   if WriteReady=1 then
   begin
      StatusBar1.SimpleText:='連線完成，開始傳送資料';
      for i:=0 to 255 do
      begin
        //windows.Beep(i*10+300,5);
        WriteData:=chr(DATABUF[i]);
        Comm1.WriteCommData(@WriteData,1);
        wait(1);
        ProgressBar1.Position:=ProgressBar1.Position+1;
      end;
      StatusBar1.SimpleText:='傳送資料完成，檢查資料中';
   end;
   WriteSuccess:=0;
   wait(500);
//===================================================
   if WriteSuccess=1 then
   begin
      chksum:=0;
      for i:=0 to 255 do
      begin
         chksum:=chksum xor DATABUF[i];
      end;
      if chksum=WriteCheckSum then
      begin
        WriteCMD:='@WRITE';
        for i:=1 to 6 do
        begin
          Comm1.WriteCommData(WriteCMD,1);
          inc(WriteCMD);
          wait(1);
        end;
      end;
      wait(500);
      if chksum=WriteCheckSum then
         StatusBar1.SimpleText:='寫入資料無誤,裝置更新中'
      else
      begin
         StatusBar1.SimpleText:='寫入有誤,請確認連線正常並重開裝置後再試一次';
         Button5.Enabled:=true;
         exit;
      end;
      //showmessage('PC:'+inttohex(chksum,2)+',MCU:'+inttohex(WriteCheckSum,2));
   end;
   wait(500);
   if WriteFINISH=1 then
      StatusBar1.SimpleText:='更新完成，裝置將會自動重新啟動'
   else
      StatusBar1.SimpleText:='更新失敗，請確認連線正常並重開裝置後再試一次';
   Button4.Enabled:=true;
   Button5.Enabled:=true;
end;

procedure SetState(Data:integer);
begin
   if Data=0 then
   begin
      Form1.PAN_0.Text:=' 已按下';
      Form1.PAN_0.Color:=clLime;
      Form1.PAN_0.Font.Color:=clBlack;
   end;
   if Data=1 then
   begin
      Form1.PAN_1.Text:=' 已按下';
      Form1.PAN_1.Color:=clLime;
      Form1.PAN_1.Font.Color:=clBlack;
   end;
   if Data=2 then
   begin
      Form1.PAN_2.Text:=' 已按下';
      Form1.PAN_2.Color:=clLime;
      Form1.PAN_2.Font.Color:=clBlack;
   end;
   if Data=3 then
   begin
      Form1.PAN_3.Text:=' 已按下';
      Form1.PAN_3.Color:=clLime;
      Form1.PAN_3.Font.Color:=clBlack;
   end;
   if Data=4 then
   begin
      Form1.PAN_4.Text:=' 已按下';
      Form1.PAN_4.Color:=clLime;
      Form1.PAN_4.Font.Color:=clBlack;
   end;
   if Data=5 then
   begin
      Form1.PAN_5.Text:=' 已按下';
      Form1.PAN_5.Color:=clLime;
      Form1.PAN_5.Font.Color:=clBlack;
   end;
   if Data=6 then
   begin
      Form1.PAN_6.Text:=' 已按下';
      Form1.PAN_6.Color:=clLime;
      Form1.PAN_6.Font.Color:=clBlack;
   end;
   if Data=7 then
   begin
      Form1.PAN_7.Text:=' 已按下';
      Form1.PAN_7.Color:=clLime;
      Form1.PAN_7.Font.Color:=clBlack;
   end;
   if Data=8 then
   begin
      Form1.PAN_8.Text:=' 已按下';
      Form1.PAN_8.Color:=clLime;
      Form1.PAN_8.Font.Color:=clBlack;
   end;
   if Data=9 then
   begin
      Form1.PAN_9.text:=' 已按下';
      Form1.PAN_9.Color:=clLime;
      Form1.PAN_9.Font.Color:=clBlack;
   end;

   if Data=10 then
   begin
      Form1.PAN_10.Text:=' 已按下';
      Form1.PAN_10.Color:=clLime;
      Form1.PAN_10.Font.Color:=clBlack;
   end;
   Form1.Timer1.Enabled:=true;
end;

procedure SendSMStoPhone(Num:string;MSG:string);
var
i:integer;
NumList:TstringList;
Delay:integer;
begin
  NumList:=TstringList.Create;
  NumList.Delimiter:=',';
  NumList.CommaText:=Num;
  for i:=0 to NumList.Count-1 do
  begin
   form1.WEB.Navigate('http://www.smsgo.com.tw/sms_gw/sendsms.asp?username=geniustom@gmail.com&password=femet&dstaddr='+NumList.Strings[i]
                    +'&smbody='+MSG);
    while form1.Web.ReadyState <> READYSTATE_COMPLETE do
      Application.ProcessMessages;
    Delay:=windows.GetTickCount;
    if windows.GetTickCount- Delay< 3000 then
      Application.ProcessMessages;
  end;
end;

procedure AddToRichEdit(S: string; FontColor: TColor);
var
  P: Integer;
begin
  P := Length(Form1.D2M.Text);//Keep Append Position
  with Form1.D2M do
  begin
    Lines.Add(Trim(S));
    SelStart := P;
    SelLength := Length(Trim(S));
    SelAttributes.Color := FontColor;
  end;
end;

procedure TForm1.Comm1ReceiveData(Sender: TObject; Buffer: Pointer;BufferLength: Word);
var
BUF:pchar;
BINData:array of byte;
chksum:byte;
Data,i,j:integer;
DataIndex:integer;
OutStr:string;
TEMPBUF:string;
TempStrList:Tstringlist;
begin
   BINData:=Buffer;
   BUF:=pchar(BINData);

   for i:=0 to BufferLength-1 do
   begin
      CheckTaiDoc(ord(BUF[i]));
   end;

   if BUF='WRITEREADY' then
   begin
      WriteReady:=1;
      exit;
   end;
   if pos('WRITEOK',BUF)>0 then
   begin
      WriteSuccess:=1;
      WriteCheckSum:= BINData[7];
      exit;
   end;

   if pos('FINISH',BUF)>0 then
   begin
      WriteFINISH:=1;
      exit;
   end;

   DataIndex:=pos('READREADY',BUF);
   if (DataIndex>0)then
   begin
      for j:=0 to 255 do
      begin
         DATABUF[j]:=BINData[DataIndex+8+j];
         chksum:= chksum xor DATABUF[j];
      end;

      //if chksum= BINData[DataIndex+8+j+256] then
      if BufferLength>=265 then
      begin
        ReadSuccessFlag:=1;
        SetMEMSetting();
      end;
      exit;
   end;

   DataIndex:=pos('TENDEF',BUF);
   if (DataIndex>0)then
   begin
      K332ROM.Lines.Clear;
      K332ROM.Lines.Text:=copy(BUF,9,(BufferLength-9));
      exit;
   end;

   DataIndex:=pos('RFIDNUM',BUF);
   if (DataIndex>0)then
   begin
      RFIDNUM.Lines.Clear;
      RFIDNUM.Hint:=copy(BUF,8,(BufferLength-7));
      RFIDNUM.Lines.Text:='['+formatdatetime('hh:mm:ss',now)+']：'+RFIDNUM.Hint;
      exit;
   end;


   if pos('CTISUCC',BUF)>0 then
   begin
      DataLog.Lines.Add(datetimetostr(now)+':'+'Gateway傳輸成功');
      if SuccMSGEn.Checked then
         SendSMStoPhone(Tel.Text,format(SUCCMSG.Text,[datetimetostr(now),CTINAME.Text]));
      if AutoSMS.Checked=true then  SuccMSGEn.Checked:=false;
      //exit;
   end;

   if pos('CTIFAIL',BUF)>0 then
   begin
      DataLog.Lines.Add(datetimetostr(now)+':'+'Gateway傳輸失敗');
      if FailMSGEn.Checked then
         SendSMStoPhone(Tel.Text,format(FAILMSG.Text,[datetimetostr(now),CTINAME.Text]));
      if AutoSMS.Checked=true then  SuccMSGEn.Checked:=true;
      //exit;
   end;

   if pos('QSIZE',BUF)>0 then
   begin
      TEMPBUF:=BUF;
      while length(TEMPBUF)>=6 do
      begin
        if(ord(TEMPBUF[6])-1)>64 then break;
        QueueSize_LB.Caption:= inttostr(ord(TEMPBUF[6])-1);
        delete(TEMPBUF,1,6);
      end;
      TEMPBUF:='';
      QueueMemo.Lines.Clear;
      QueueMemo.Text:='['+formatdatetime('hh:mm:ss',now)+']：Queue Size 更新完成';
   end;

   if pos('GETQU',BUF)>0 then
   begin
      TEMPBUF:=BUF;
      delete(TEMPBUF,1,5);
      TempStrList:=Tstringlist.Create;
      TempStrList.Delimiter:=',';
      TempStrList.DelimitedText:=TEMPBUF;

      QueueList.Rows[0].Delimiter:=',';
      QueueList.Rows[0].DelimitedText:='ID,MSG';
      
      for i:=1 to 64 do
      begin
         QueueList.Rows[i].Clear;
         QueueList.Rows[i].Delimiter:=',';
      end;

      for i:=1 to TempStrList.Count do
      begin
         QueueList.Rows[i].DelimitedText:=inttostr(i-1)+','+TempStrList[i-1];
      end;
      
      QueueMemo.Lines.Clear;
      QueueMemo.Text:='['+formatdatetime('hh:mm:ss',now)+']：Queue內容更新完成';
      //exit;
   end;

   if pos('RFPRESS',BUF)>0 then
   begin
      Data:= BINData[7];
      SetState(Data);
      Button13Click(nil);
      //exit;
   end;

   if pos('GWON',BUF)>0 then
   begin
      StatusBar1.SimpleText:='宅端主機韌體版本:'+copy(BUF,pos('GWON',BUF)+4,BufferLength);
      //exit;
   end;

   if pos('VERDO',BUF)>0 then
   begin
      DonVer.SimpleText :=copy(BUF,pos('VERDO',BUF)+5,BufferLength);
      //exit;
   end;

   if pos('DEV->MCU:',BUF)>0 then
   begin
      OutStr:='DEV->MCU:';
      for i:=0 to 7 do
      begin
         OutStr:=OutStr+inttohex(ord(BUF[i+9]),2);
         if i<7 then OutStr:=OutStr+',';
      end;
      if (ord(BUF[9])=$51) and (ord(BUF[15])=$A5) then
      begin
        DevLabel.Caption:='傳收皆正常';
        LB_DongleTest.Caption:='傳收皆正常';
      end;
      if (ord(BUF[9])=$AA) and (ord(BUF[10])=$01) then
      begin
        DonLabel.Caption:='傳收皆正常';
        LB_DongleTest.Caption:='傳收皆正常';
        if(ord(BUF[19])*256+ord(BUF[20])>0) then
          Don1.Caption:='OK';
        if(ord(BUF[17])*256+ord(BUF[18])>0) then
          Don2.Caption:='OK';
      end;
      AddToRichEdit(OutStr,clred);
      Button13Click(nil);
      //exit;
   end;

   if pos('MCU->DEV:',BUF)>0 then
   begin
      OutStr:='MCU->DEV:';
      for i:=0 to 7 do
      begin
         OutStr:=OutStr+inttohex(ord(BUF[i+9]),2);
         if i<7 then OutStr:=OutStr+',';
      end;
      AddToRichEdit(OutStr,clblue);
      Button13Click(nil);
      //exit;
   end;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
      Form1.PAN_0.Text:=' 未按下';
      Form1.PAN_0.Color:=clBlack;
      Form1.PAN_0.Font.Color:=clYellow;

      Form1.PAN_1.Text:=' 未按下';
      Form1.PAN_1.Color:=clBlack;
      Form1.PAN_1.Font.Color:=clYellow;

      Form1.PAN_2.Text:=' 未按下';
      Form1.PAN_2.Color:=clBlack;
      Form1.PAN_2.Font.Color:=clYellow;

      Form1.PAN_3.Text:=' 未按下';
      Form1.PAN_3.Color:=clBlack;
      Form1.PAN_3.Font.Color:=clYellow;

      Form1.PAN_4.Text:=' 未按下';
      Form1.PAN_4.Color:=clBlack;
      Form1.PAN_4.Font.Color:=clYellow;

      Form1.PAN_5.Text:=' 未按下';
      Form1.PAN_5.Color:=clBlack;
      Form1.PAN_5.Font.Color:=clYellow;

      Form1.PAN_6.Text:=' 未按下';
      Form1.PAN_6.Color:=clBlack;
      Form1.PAN_6.Font.Color:=clYellow;

      Form1.PAN_7.Text:=' 未按下';
      Form1.PAN_7.Color:=clBlack;
      Form1.PAN_7.Font.Color:=clYellow;

      Form1.PAN_8.Text:=' 未按下';
      Form1.PAN_8.Color:=clBlack;
      Form1.PAN_8.Font.Color:=clYellow;

      Form1.PAN_9.text:=' 未按下';
      Form1.PAN_9.Color:=clBlack;
      Form1.PAN_9.Font.Color:=clYellow;

      Form1.PAN_10.Text:=' 未按下';
      Form1.PAN_10.Color:=clBlack;
      Form1.PAN_10.Font.Color:=clYellow;

      Form1.Timer1.Enabled:=false;
      Button13Click(nil);
end;

procedure TForm1.Button4Click(Sender: TObject);
var
i,chksum:integer;
WriteCMD:pchar;
WriteData:char;
DelayCount:integer;
TA,TB:Tdatetime;
SEC:double;
begin
   Button4.Enabled:=false;
   Button5.Enabled:=false;
   WriteCMD:='@READ!';
   ReadSuccessFlag:=0;
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(5);
   end;
   DelayCount:=0;
   StatusBar1.SimpleText:='裝置讀取中..請稍候';
   while (DelayCount<30)and(ReadSuccessFlag=0) do
   begin
    application.ProcessMessages;
    wait(100);
    inc(DelayCount);
   end;
   if ReadSuccessFlag=1 then
   begin
    StatusBar1.SimpleText:='裝置資料讀取完成';
    SEC:=1/60/60/24;
    if TimeStr.Caption<>'' then
      TA:=strtodatetime(TimeStr.Caption);
    if TimeLabel.Caption<>'' then
      TB:=strtodatetime(TimeLabel.Caption);
    TimeDef.Caption:='差距：'+inttostr(abs(round((TA-TB)/ SEC)))+'秒';
   end
   else
    StatusBar1.SimpleText:='讀取有誤,請確認連線正常並重開裝置後再試一次';
   Button4.Enabled:=true;
   Button5.Enabled:=true;
end;

procedure TForm1.NeedPreKeyClick(Sender: TObject);
begin
   CTIPreKey.Enabled:= NeedPreKey.Checked;
end;

procedure TForm1.FormActivate(Sender: TObject);
var
PreLoad,Default:string;
begin
   GetMEMSetting();                      //將設定值轉MEM
   Default:=MemToSTR();                  //將MEM轉成預設字串
   PreLoad:=ConfigINI.ReadString('TaipeiCity','Setting',Default); //若讀的到檔載入預設字串
   CTINAME.Text:=ConfigINI.ReadString('CTIName','Setting','門諾醫院');
   GroupBox4.Visible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   GroupBox14.Visible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   GroupBox15.Visible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   QueueTest.TabVisible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   K332TEST.TabVisible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   ARoundDevice.TabVisible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);
   CreateTest.TabVisible:=ConfigINI.ReadBool('TaipeiCity','TestingMode',false);

   if StrToMem(PreLoad) then             //將設定值載入到MEM
    SetMEMSetting();                     //將MEM ASSIGN到元件
   ConfigINI.WriteString('TaipeiCity','Setting',PreLoad);
   ConfigINI.WriteString('CTIName','Setting',CTINAME.Text);
   ConfigINI.WriteBool('TaipeiCity','TestingMode',GroupBox4.Visible);
   FirstReportClick(nil);
end;


procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   ScanPort.Close;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
begin
      if self.Enabled=true then
      begin
         if ScanPort.Visible then Button8.Enabled:=true;
         ScanPort.Hide;
      end;
      
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
   Button8.Enabled:=false;
   self.Enabled:=false;
   ScanPort.Show;
end;

procedure TForm1.Timer3Timer(Sender: TObject);
begin
  TimeLabel.Caption:=datetimetostr(now);
  LBL_SEC.Caption:=inttostr(MinuteOf(FirstReportTime.Time));
  DeviceMachineCode_1.Enabled:=DeviceEnable_1.Checked;
  DeviceMachineCode_2.Enabled:=DeviceEnable_2.Checked;
  DeviceMachineCode_3.Enabled:=DeviceEnable_3.Checked;
  DeviceMachineCode_4.Enabled:=DeviceEnable_4.Checked;
  DeviceMachineCode_5.Enabled:=DeviceEnable_5.Checked;
  DeviceMachineCode_6.Enabled:=DeviceEnable_6.Checked;
  DeviceMachineCode_7.Enabled:=DeviceEnable_7.Checked;
  DeviceMachineCode_8.Enabled:=DeviceEnable_8.Checked;
end;

procedure TForm1.DeviceMachineCode_1KeyPress(Sender: TObject;
  var Key: Char);
begin
  if Not (Key in ['0'..'9', #8] ) then //#8代表后退鍵
  begin
    Key := #0;
    //messagebox(self.Handle ,'請輸入數字'+#13,'waring',mb_iconinformation);
  end
  else if ((Key=#8) and (Length(TEdit(Sender).Text)=1)) then
  begin
    Key := #0;
    TEdit(Sender).Text:='0';
    //messagebox(self.Handle ,'數值不可為空'+#13,'waring',mb_iconinformation);
  end
  else if ((Length(TEdit(Sender).Text)=4) and (Key<>#8)) then
  begin
    Key := #0;
    messagebox(self.Handle ,'僅能輸入四位數字'+#13,'waring',mb_iconinformation);
  end
  else if Key in ['0'..'9'] then
  begin
    if strtoint(TEdit(Sender).Text+Key)>=1024 then
    begin
      Key:= #0;
      messagebox(self.Handle ,'輸入不可大於1023'+#13,'waring',mb_iconinformation);
    end;
  end;
end;

procedure TForm1.DeviceMachineCode_1Change(Sender: TObject);
begin
  if TEdit(Sender).Text='' then TEdit(Sender).Text:='0';
end;

procedure TForm1.Panel2DblClick(Sender: TObject);
begin
ReportControl.TabVisible:=true;
LogTab.TabVisible:=true;
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
SendSMStoPhone(Tel.Text,format(FAILMSG.Text,[datetimetostr(now),CTINAME.Text]));
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
  Datalog.Clear;
end;

procedure TForm1.Button11Click(Sender: TObject);
begin
   D2m.Clear;
end;

procedure TForm1.Button12Click(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@QUEUE';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;
end;

procedure TForm1.Button13Click(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@QSIZE';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;

end;

procedure TForm1.BT_CleanQueueClick(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@CLEAR';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;
end;

procedure TForm1.BT_GetQueueClick(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@GETQU';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
   DeviceTestTimer.Enabled:=SpeedButton1.Down;
   if SpeedButton1.Down then
      SpeedButton1.Caption:= '關閉量產測試'
    else
      SpeedButton1.Caption:= '啟動量產測試';
end;

procedure TForm1.DeviceTestTimerTimer(Sender: TObject);
var
BPV,SPV,HRV:integer;
RefreshFlag:boolean;
i:integer;
begin

  BT_GetQueueClick(nil);
  if length(QueueList.Cells[1,1])<>28 then exit;
  if QueueList.Cells[1,1]='' then exit;

  if QueueList.Cells[1,1]='0000000000000000000000000000' then
  begin
    Device_BP.Caption:='等待中';
    Device_SP.Caption:='等待中';
    Device_HR.Caption:='等待中';
    Device_MA.Caption:='等待中';
    exit;
  end;

  if copy(QueueList.Cells[1,1],18,2)='50' then
  begin
    Device_BP.Caption:=copy(QueueList.Cells[1,1],6,3);
    Device_SP.Caption:=copy(QueueList.Cells[1,1],9,3);
    Device_HR.Caption:=copy(QueueList.Cells[1,1],12,3);
    DeviceTestTimer.Enabled:=false;
  end;
end;

procedure TForm1.BT_NextClick(Sender: TObject);
var i:integer;
begin
  DeviceTestTimer.Enabled:=false;
  Button1Click(nil);

  Device_BP.Caption:='';
  Device_SP.Caption:='';
  Device_HR.Caption:='';
  Device_MA.Caption:='';
  LB_DongleTest.Caption:='尚未測試';
  for i:=0 to QueueList.RowCount-1 do
    QueueList.Rows[i].Clear;

  sleep(200);
  Button1Click(nil);
  
  DeviceTestTimer.Enabled:=true;
end;

procedure TForm1.Button15Click(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@ICALL';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;

end;

procedure TForm1.Button14Click(Sender: TObject);
var
WriteCMD:pansichar;
i:integer;
begin
   WriteCMD:='@KILLD';
   for i:=1 to 6 do
   begin
      Comm1.WriteCommData(WriteCMD,1);
      inc(WriteCMD);
      wait(2);
   end;

end;


function GetRFIDSTR(S:string):string;
var i:integer;
begin
   result:='';
   result:=' '+S[1]+S[2]+' '+S[3]+S[4]+' '+S[5]+S[6]+' '+S[7]+S[8];
end;

procedure TForm1.Button16Click(Sender: TObject);
begin
   case RFIDSel.ItemIndex of
      0:   RFID_Code1.Text:= GetRFIDSTR(RFIDNUM.Hint);
      1:   RFID_Code2.Text:= GetRFIDSTR(RFIDNUM.Hint);
      2:   RFID_Code3.Text:= GetRFIDSTR(RFIDNUM.Hint);
      3:   RFID_Code4.Text:= GetRFIDSTR(RFIDNUM.Hint);
      4:   RFID_Code5.Text:= GetRFIDSTR(RFIDNUM.Hint);
      5:   RFID_Code6.Text:= GetRFIDSTR(RFIDNUM.Hint);
      6:   RFID_Code7.Text:= GetRFIDSTR(RFIDNUM.Hint);
      7:   RFID_Code8.Text:= GetRFIDSTR(RFIDNUM.Hint);
   end;

end;

end.


{
   ConfigINI.WriteInteger('Main','FirstReport',GetRadioChecked(FirstReport.Checked));
   ConfigINI.WriteString('Main','FirstReportDate',formatdatetime('yy/mm/dd',FirstReportDate.Date));
   ConfigINI.WriteString('Main','FirstReportTime',formatdatetime('hh:mm:ss',FirstReportTime.Time));

   ConfigINI.WriteString('Main','SystemReportDate',formatdatetime('yy/mm/dd',SystemReportDate.Date));
   ConfigINI.WriteInteger('Main','SystemReportTime',SystemReportHour.ItemIndex);
   ConfigINI.WriteInteger('Main','SystemReportContinue',strtoint(SystemReportContinue.Text));

   ConfigINI.WriteString('Main','CustomerID',CustomerID.Text);
   ConfigINI.WriteInteger('Main','RingCount',strtoint(RingCount.Text));
   ConfigINI.WriteInteger('Main','BuzzerMode',GetRadioChecked(BuzzerMode.Checked));

   ConfigINI.WriteInteger('Main','NonActiveAlarm_1',GetRadioChecked(NonActiveAlarm_1.Checked));
   ConfigINI.WriteInteger('Main','NonActiveAlarm_1_Hour',Alarm1_Hour.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_1_Minute',Alarm1_Minute.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_1_Continue',strtoint(Alarm1_Continue.text));

   ConfigINI.WriteInteger('Main','NonActiveAlarm_2',GetRadioChecked(NonActiveAlarm_2.Checked));
   ConfigINI.WriteInteger('Main','NonActiveAlarm_2_Hour',Alarm2_Hour.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_2_Minute',Alarm2_Minute.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_2_Continue',strtoint(Alarm2_Continue.text));

   ConfigINI.WriteInteger('Main','NonActiveAlarm_3',GetRadioChecked(NonActiveAlarm_3.Checked));
   ConfigINI.WriteInteger('Main','NonActiveAlarm_3_Hour',Alarm3_Hour.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_3_Minute',Alarm3_Minute.ItemIndex);
   ConfigINI.WriteInteger('Main','NonActiveAlarm_3_Continue',strtoint(Alarm3_Continue.text));

   ConfigINI.WriteInteger('Device','DeviceType_1',DeviceName_1.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_1',strtoint(DeviceMachineCode_1.Text));
   ConfigINI.WriteInteger('Device','DeviceType_2',DeviceName_2.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_2',strtoint(DeviceMachineCode_2.Text));
   ConfigINI.WriteInteger('Device','DeviceType_3',DeviceName_3.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_3',strtoint(DeviceMachineCode_3.Text));
   ConfigINI.WriteInteger('Device','DeviceType_4',DeviceName_4.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_4',strtoint(DeviceMachineCode_4.Text));
   ConfigINI.WriteInteger('Device','DeviceType_5',DeviceName_5.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_5',strtoint(DeviceMachineCode_5.Text));
   ConfigINI.WriteInteger('Device','DeviceType_6',DeviceName_6.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_6',strtoint(DeviceMachineCode_6.Text));
   ConfigINI.WriteInteger('Device','DeviceType_7',DeviceName_7.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_7',strtoint(DeviceMachineCode_7.Text));
   ConfigINI.WriteInteger('Device','DeviceType_8',DeviceName_8.ItemIndex);
   ConfigINI.WriteInteger('Device','DeviceMachineCode_8',strtoint(DeviceMachineCode_8.Text));

   ConfigINI.WriteInteger('CTI','NeedPreKey',GetRadioChecked(NeedPreKey.Checked));
   ConfigINI.WriteString('CTI','CTIPreKey',CTIPreKey.Text);
   ConfigINI.WriteString('CTI','CTINum1',CTINum1.Text);
   ConfigINI.WriteString('CTI','CTINum2',CTINum2.Text);
   ConfigINI.WriteString('CTI','CTINum3',CTINum3.Text);
   ConfigINI.WriteString('CTI','CTINum4',CTINum4.Text);





   FirstReport.Checked:=SetRadioChecked(ConfigINI.ReadInteger('Main','FirstReport',GetRadioChecked(FirstReport.Checked)));
   FirstReportDate.Date:=strtodatetime( ConfigINI.ReadString('Main','FirstReportDate',formatdatetime('yy/mm/dd',FirstReportDate.Date)) );
   FirstReportTime.Time:=strtodatetime( ConfigINI.ReadString('Main','FirstReportTime',formatdatetime('hh:mm:ss',FirstReportTime.Time)) );

   SystemReportDate.Date:=strtodatetime( ConfigINI.ReadString('Main','SystemReportDate',formatdatetime('yy/mm/dd',SystemReportDate.Date)) );
   SystemReportHour.ItemIndex:=ConfigINI.ReadInteger('Main','SystemReportTime',SystemReportHour.ItemIndex);
   SystemReportContinue.Text:=inttostr( ConfigINI.ReadInteger('Main','SystemReportContinue',strtoint(SystemReportContinue.Text)) );

   CustomerID.Text:=ConfigINI.ReadString('Main','CustomerID',CustomerID.Text);
   RingCount.Text:=inttostr( ConfigINI.ReadInteger('Main','RingCount',strtoint(RingCount.Text)) );
   BuzzerMode.Checked:=SetRadioChecked(ConfigINI.ReadInteger('Main','BuzzerMode',GetRadioChecked(BuzzerMode.Checked)));

   NonActiveAlarm_1.Checked:=SetRadioChecked(ConfigINI.ReadInteger('Main','NonActiveAlarm_1',GetRadioChecked(NonActiveAlarm_1.Checked)));
   Alarm1_Hour.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_1_Hour',Alarm1_Hour.ItemIndex);
   Alarm1_Minute.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_1_Minute',Alarm1_Minute.ItemIndex);
   Alarm1_Continue.text:=inttostr( ConfigINI.ReadInteger('Main','NonActiveAlarm_1_Continue',strtoint(Alarm1_Continue.text)) );
   NonActiveAlarm_1Click(nil);

   NonActiveAlarm_2.Checked:=SetRadioChecked(ConfigINI.ReadInteger('Main','NonActiveAlarm_2',GetRadioChecked(NonActiveAlarm_2.Checked)));
   Alarm2_Hour.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_2_Hour',Alarm2_Hour.ItemIndex);
   Alarm2_Minute.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_2_Minute',Alarm2_Minute.ItemIndex);
   Alarm2_Continue.text:=inttostr( ConfigINI.ReadInteger('Main','NonActiveAlarm_2_Continue',strtoint(Alarm2_Continue.text)));
   NonActiveAlarm_2Click(nil);

   NonActiveAlarm_3.Checked:=SetRadioChecked(ConfigINI.ReadInteger('Main','NonActiveAlarm_3',GetRadioChecked(NonActiveAlarm_3.Checked)));
   Alarm3_Hour.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_3_Hour',Alarm3_Hour.ItemIndex);
   Alarm3_Minute.ItemIndex:=ConfigINI.ReadInteger('Main','NonActiveAlarm_3_Minute',Alarm3_Minute.ItemIndex);
   Alarm3_Continue.text:=inttostr( ConfigINI.ReadInteger('Main','NonActiveAlarm_3_Continue',strtoint(Alarm3_Continue.text)) );
   NonActiveAlarm_3Click(nil);

   DeviceName_1.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_1',DeviceName_1.ItemIndex);
   DeviceMachineCode_1.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_1',strtoint(DeviceMachineCode_1.Text)) );
   DeviceName_2.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_2',DeviceName_2.ItemIndex);
   DeviceMachineCode_2.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_2',strtoint(DeviceMachineCode_2.Text)) );
   DeviceName_3.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_3',DeviceName_3.ItemIndex);
   DeviceMachineCode_3.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_3',strtoint(DeviceMachineCode_3.Text)) );
   DeviceName_4.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_4',DeviceName_4.ItemIndex);
   DeviceMachineCode_4.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_4',strtoint(DeviceMachineCode_4.Text)) );
   DeviceName_5.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_5',DeviceName_5.ItemIndex);
   DeviceMachineCode_5.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_5',strtoint(DeviceMachineCode_5.Text)) );
   DeviceName_6.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_6',DeviceName_6.ItemIndex);
   DeviceMachineCode_6.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_6',strtoint(DeviceMachineCode_6.Text)) );
   DeviceName_7.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_7',DeviceName_7.ItemIndex);
   DeviceMachineCode_7.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_7',strtoint(DeviceMachineCode_7.Text)) );
   DeviceName_8.ItemIndex:=ConfigINI.ReadInteger('Device','DeviceType_8',DeviceName_8.ItemIndex);
   DeviceMachineCode_8.Text:=inttostr( ConfigINI.ReadInteger('Device','DeviceMachineCode_8',strtoint(DeviceMachineCode_8.Text)) );

   NeedPreKey.Checked:=SetRadioChecked(ConfigINI.ReadInteger('CTI','NeedPreKey',GetRadioChecked(NeedPreKey.Checked)));
   CTIPreKey.Text:=ConfigINI.ReadString('CTI','CTIPreKey',CTIPreKey.Text);
   CTINum1.Text:=ConfigINI.ReadString('CTI','CTINum1',CTINum1.Text);
   CTINum2.Text:=ConfigINI.ReadString('CTI','CTINum2',CTINum2.Text);
   CTINum3.Text:=ConfigINI.ReadString('CTI','CTINum3',CTINum3.Text);
   CTINum4.Text:=ConfigINI.ReadString('CTI','CTINum4',CTINum4.Text);
}
