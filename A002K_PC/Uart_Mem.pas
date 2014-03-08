unit Uart_Mem;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, ExtCtrls, XPMan, StdCtrls, Grids,inifiles, SPComm,DateUtils
  ,Mask;


var

DATABUF:array [0..257] of byte;
GateWayDateTime:TDatetime;

procedure GetMEMSetting();
procedure SetMEMSetting();
function MemToSTR():string;
function StrToMem(STR:string):boolean;

implementation
uses unit1;

procedure RDIFCode2BUF(BufStart:integer;RFCodeSTR:String);
var
  RFCode:integer;
begin
   RFCodeSTR:=StringReplace(RFCodeSTR,' ','',[rfReplaceAll]);
   if RFCodeSTR='' then
      RFCode:=0
   else
      RFCode:=strtoint('$'+RFCodeSTR);

   DATABUF[BufStart]:= RFCode mod 256;      RFCode:=RFCode shr 8;
   DATABUF[BufStart+1]:= RFCode mod 256;    RFCode:=RFCode shr 8;
   DATABUF[BufStart+2]:= RFCode mod 256;    RFCode:=RFCode shr 8;
   DATABUF[BufStart+3]:= RFCode mod 256;
end;

procedure BUF2RDIFCode(BufStart:integer;out RFCode_STR:TMaskEdit);
var
  RFCode:string;
  BufferValue:int64;
begin
   RFCode:=' ';
   BufferValue:= DATABUF[BufStart]+
                 DATABUF[BufStart+1]*256+
                 DATABUF[BufStart+2]*256*256+
                 DATABUF[BufStart+3]*256*256*256;
   if (BufferValue=0) or (BufferValue=4294967295) then
      RFCode:=' 00 00 00 00'
   else
   begin
      RFCode:=RFCode+ inttohex(DATABUF[BufStart+3],2)+ ' ';
      RFCode:=RFCode+ inttohex(DATABUF[BufStart+2],2)+ ' ';
      RFCode:=RFCode+ inttohex(DATABUF[BufStart+1],2)+ ' ';
      RFCode:=RFCode+ inttohex(DATABUF[BufStart+0],2);
   end;
   RFCode_STR.Text:=RFCode;

end;



procedure GetMEMSetting();
var
i:integer;
data:string;
NowTime:TDatetime;
RFID_Code:integer;
begin
   for i:=0 to 255 do
   begin
      DATABUF[i]:=$ff;
   end;

   DATABUF[$00]:= GetRadioChecked(form1.FirstReport.Checked);
   DatetimeToString(data,'yyyy',form1.FirstReportDate.Date);
   DATABUF[$02]:= strtoint(data) mod 256;
   DATABUF[$03]:= strtoint(data) div 256;
   DatetimeToString(data,'mm',form1.FirstReportDate.Date);
   DATABUF[$04]:= strtoint(data);
   DatetimeToString(data,'dd',form1.FirstReportDate.Date);
   DATABUF[$05]:= strtoint(data);
   DatetimeToString(data,'hh',form1.FirstReportTime.Time) ;
   DATABUF[$06]:= strtoint(data);
   DatetimeToString(data,'nn',form1.FirstReportTime.Time) ;
   DATABUF[$07]:= strtoint(data);
   DatetimeToString(data,'ss',form1.FirstReportTime.Time) ;
   DATABUF[$08]:= strtoint(data);

   
   DatetimeToString(data,'yyyy',form1.SystemReportDate.Date);
   DATABUF[$10]:= strtoint(data) mod 256;
   DATABUF[$11]:= strtoint(data) div 256;
   DatetimeToString(data,'mm',form1.SystemReportDate.Date);
   DATABUF[$12]:= strtoint(data);
   DatetimeToString(data,'dd',form1.SystemReportDate.Date);
   DATABUF[$13]:= strtoint(data);
   DATABUF[$14]:= form1.SystemReportHour.itemIndex;
   DATABUF[$15]:= strtoint(form1.SystemReportContinue.text);
   DATABUF[$16]:= strtoint(form1.SystemCheckTimeout.text);
   
   DATABUF[$20]:= strtoint(form1.CustomerID.text) mod 256;
   DATABUF[$21]:= strtoint(form1.CustomerID.text) div 256;
   
   if form1.BatchSend_0.Checked then
    DATABUF[$22]:=49
   else
    DATABUF[$22]:=51;

   DATABUF[$23]:= GetRadioChecked(form1.BuzzerMode.Checked);

   DATABUF[$24]:= form1.RetryCount.Position;
   DATABUF[$25]:=GetRadioChecked(form1.MeasureAutoDel.Checked);
   DATABUF[$26]:=GetRadioChecked(form1.DebugCheck.Checked);

   DATABUF[$30]:= form1.Alarm1_Hour.ItemIndex;
   DATABUF[$31]:= form1.Alarm1_Minute.ItemIndex;
   DATABUF[$32]:= form1.Continue_1.Position;

   DATABUF[$33]:= form1.Alarm2_Hour.ItemIndex;
   DATABUF[$34]:= form1.Alarm2_Minute.ItemIndex;
   DATABUF[$35]:= form1.Continue_2.Position;

   DATABUF[$36]:= form1.Alarm3_Hour.ItemIndex;
   DATABUF[$37]:= form1.Alarm3_Minute.ItemIndex;
   DATABUF[$38]:= form1.Continue_3.Position;

   DATABUF[$39]:= form1.Alarm4_Hour.ItemIndex;
   DATABUF[$3A]:= form1.Alarm4_Minute.ItemIndex;
   DATABUF[$3B]:= form1.Continue_4.Position;

   for i:= $40 to $4F do
   begin
      DATABUF[i]:=255;
   end;


   DATABUF[$40]:= strtoint(form1.DeviceMachineCode_1.text) mod 256;
   DATABUF[$41]:= strtoint(form1.DeviceMachineCode_1.text) div 256;
   if form1.DeviceEnable_1.Checked=false then DATABUF[$41]:=DATABUF[$41]+128;

   DATABUF[$42]:= strtoint(form1.DeviceMachineCode_2.text) mod 256;
   DATABUF[$43]:= strtoint(form1.DeviceMachineCode_2.text) div 256;
   if form1.DeviceEnable_2.Checked=false then DATABUF[$43]:=DATABUF[$43]+128;

   DATABUF[$44]:= strtoint(form1.DeviceMachineCode_3.text) mod 256;
   DATABUF[$45]:= strtoint(form1.DeviceMachineCode_3.text) div 256;
   if form1.DeviceEnable_3.Checked=false then DATABUF[$45]:=DATABUF[$45]+128;

   DATABUF[$46]:= strtoint(form1.DeviceMachineCode_4.text) mod 256;
   DATABUF[$47]:= strtoint(form1.DeviceMachineCode_4.text) div 256;
   if form1.DeviceEnable_4.Checked=false then DATABUF[$47]:=DATABUF[$47]+128;

   DATABUF[$48]:= strtoint(form1.DeviceMachineCode_5.text) mod 256;
   DATABUF[$49]:= strtoint(form1.DeviceMachineCode_5.text) div 256;
   if form1.DeviceEnable_5.Checked=false then DATABUF[$49]:=DATABUF[$49]+128;

   DATABUF[$4A]:= strtoint(form1.DeviceMachineCode_6.text) mod 256;
   DATABUF[$4B]:= strtoint(form1.DeviceMachineCode_6.text) div 256;
   if form1.DeviceEnable_6.Checked=false then DATABUF[$4B]:=DATABUF[$4B]+128;

   DATABUF[$4C]:= strtoint(form1.DeviceMachineCode_7.text) mod 256;
   DATABUF[$4D]:= strtoint(form1.DeviceMachineCode_7.text) div 256;
   if form1.DeviceEnable_7.Checked=false then DATABUF[$4D]:=DATABUF[$4D]+128;

   DATABUF[$4E]:= strtoint(form1.DeviceMachineCode_8.text) mod 256;
   DATABUF[$4F]:= strtoint(form1.DeviceMachineCode_8.text) div 256;
   if form1.DeviceEnable_8.Checked=false then DATABUF[$4F]:=DATABUF[$4F]+128;



   DATABUF[$50]:= GetRadioChecked(form1.NeedPreKey.Checked);
   for i:=1 to length(form1.CTIPreKey.Text) do
      DATABUF[$50+i]:=strtoint(form1.CTIPreKey.Text[i]);
   DATABUF[$59]:= form1.ToneTimeout.Position;


   for i:=1 to length(form1.CTINum1.Text) do
      DATABUF[$60+i-1]:=strtoint(form1.CTINum1.Text[i]);
   for i:=1 to length(form1.CTINum2.Text) do
      DATABUF[$70+i-1]:=strtoint(form1.CTINum2.Text[i]);
   for i:=1 to length(form1.CTINum3.Text) do
      DATABUF[$80+i-1]:=strtoint(form1.CTINum3.Text[i]);
   for i:=1 to length(form1.CTINum4.Text) do
      DATABUF[$90+i-1]:=strtoint(form1.CTINum4.Text[i]);

   for i:=1 to length(form1.DATATEL_1.Text) do
      DATABUF[$A0+i-1]:=strtoint(form1.DATATEL_1.Text[i]);
   for i:=1 to length(form1.DATATEL_2.Text) do
      DATABUF[$B0+i-1]:=strtoint(form1.DATATEL_2.Text[i]);
   for i:=1 to length(form1.DATATEL_3.Text) do
      DATABUF[$C0+i-1]:=strtoint(form1.DATATEL_3.Text[i]);
   for i:=1 to length(form1.DATATEL_4.Text) do
      DATABUF[$D0+i-1]:=strtoint(form1.DATATEL_4.Text[i]);

   NowTime:=IncSecond(now,6);

   datetimetostring(data,'yyyy',NowTime);
   DATABUF[$E0]:= strtoint(data) mod 256;
   DATABUF[$E1]:= strtoint(data)  div 256;
   datetimetostring(data,'mm',NowTime);
   DATABUF[$E2]:= strtoint(data) ;
   datetimetostring(data,'dd',NowTime);
   DATABUF[$E3]:= strtoint(data) ;
   datetimetostring(data,'hh',NowTime);
   DATABUF[$E4]:= strtoint(data) ;
   datetimetostring(data,'nn',NowTime);
   DATABUF[$E5]:= strtoint(data) ;
   datetimetostring(data,'ss',NowTime);
   DATABUF[$E6]:= strtoint(data) ;

   DATABUF[$E7]:= form1.SPKSel1.ItemIndex;
   DATABUF[$E8]:= form1.SPKSel2.ItemIndex;
   DATABUF[$E9]:= form1.SPKSel3.ItemIndex;
   DATABUF[$EA]:= form1.SPKSel4.ItemIndex;

   //RFID CODE==============================
   RDIFCode2BUF($0A,form1.RFID_Code1.Text);
   RDIFCode2BUF($18,form1.RFID_Code2.Text);
   RDIFCode2BUF($1C,form1.RFID_Code3.Text);
   RDIFCode2BUF($28,form1.RFID_Code4.Text);
   RDIFCode2BUF($2C,form1.RFID_Code5.Text);
   RDIFCode2BUF($3C,form1.RFID_Code6.Text);
   RDIFCode2BUF($5A,form1.RFID_Code7.Text);
   RDIFCode2BUF($EC,form1.RFID_Code8.Text);
end;


procedure SetMEMSetting();
var
i,j:integer;
data,tempstr:string;
RFID_Code:integer;
begin

   form1.FirstReport.Checked:=SetRadioChecked(DATABUF[$00]);
   //DATABUF[$00]:= GetRadioChecked(form1.FirstReport.Checked);

   form1.FirstReportDate.Date:=strtoDatetime(format('%d/%d/%d',[DATABUF[$03]*256+DATABUF[$02],
                                                                DATABUF[$04],
                                                                DATABUF[$05]]));
   //DatetimeToString(data,'yyyy',form1.FirstReportDate.Date);
   //DATABUF[$02]:= strtoint(data) mod 256;
   //DATABUF[$03]:= strtoint(data) div 256;
   //DatetimeToString(data,'mm',form1.FirstReportDate.Date);
   //DATABUF[$04]:= strtoint(data);
   //DatetimeToString(data,'dd',form1.FirstReportDate.Date);
   //DATABUF[$05]:= strtoint(data);
   form1.FirstReportTime.Time:=strtoDatetime(format('%d:%d:%d',[DATABUF[$06],
                                                                DATABUF[$07],
                                                                0]));
   //DatetimeToString(data,'hh',form1.FirstReportTime.Time) ;
   //DATABUF[$06]:= strtoint(data);
   //DatetimeToString(data,'nn',form1.FirstReportTime.Time) ;
   //DATABUF[$07]:= strtoint(data);
   //DatetimeToString(data,'ss',form1.FirstReportTime.Time) ;
   //DATABUF[$08]:= strtoint(data);

   form1.SystemReportDate.Date:=strtoDatetime(format('%d/%d/%d',[DATABUF[$11]*256+DATABUF[$10],
                                                                DATABUF[$12],
                                                                DATABUF[$13]]));
   //DatetimeToString(data,'yyyy',form1.SystemReportDate.Date);
   //DATABUF[$10]:= strtoint(data) mod 256;
   //DATABUF[$11]:= strtoint(data) div 256;
   //DatetimeToString(data,'mm',form1.SystemReportDate.Date);
   //DATABUF[$12]:= strtoint(data);
   //DatetimeToString(data,'dd',form1.SystemReportDate.Date);
   //DATABUF[$13]:= strtoint(data);

   form1.SystemReportHour.itemIndex:=DATABUF[$14];
   //DATABUF[$14]:= form1.SystemReportHour.itemIndex;
   form1.SystemReportContinue.text:=inttostr(DATABUF[$15]);
   //DATABUF[$15]:= strtoint(form1.SystemReportContinue.text);

   form1.SystemCheckTimeout.ItemIndex:=DATABUF[$16]-1;

   form1.CustomerID.text:=format('%4d',[DATABUF[$21]*256+DATABUF[$20]]);
   tempstr:=form1.CustomerID.text;
   for j:=1 to 4 do
   begin
      if tempstr[j]=' ' then tempstr[j]:='0';
   end;
   form1.CustomerID.text:=tempstr;
   //DATABUF[$20]:= strtoint(form1.CustomerID.text) mod 256;
   //DATABUF[$21]:= strtoint(form1.CustomerID.text) div 256;

   if DATABUF[$22]=49 then
    form1.BatchSend_0.Checked:=true
   else
    form1.BatchSend_0.Checked:=false;
   form1.BatchSend_1.Checked:=not(form1.BatchSend_0.Checked);

   form1.BuzzerMode.Checked:=SetRadioChecked(DATABUF[$23]);
   form1.NonBuzzerMode.Checked:=not(form1.BuzzerMode.Checked);
   //DATABUF[$23]:= GetRadioChecked(form1.BuzzerMode.Checked);

   form1.RetryCount.Position:= DATABUF[$24];
   form1.MeasureAutoDel.Checked:=SetRadioChecked(DATABUF[$25]);
   form1.DebugCheck.Checked:=SetRadioChecked(DATABUF[$26]);

   if DATABUF[$32]<>0 then
    form1.NonActiveAlarm_1.Checked:=true
   else
    form1.NonActiveAlarm_1.Checked:=false;
   form1.Alarm1_Hour.ItemIndex:=DATABUF[$30];
   form1.Alarm1_Minute.ItemIndex:=DATABUF[$31];
   form1.Continue_1.Position:=DATABUF[$32];

   if DATABUF[$35]<>0 then
    form1.NonActiveAlarm_2.Checked:=true
   else
    form1.NonActiveAlarm_2.Checked:=false;
   form1.Alarm2_Hour.ItemIndex:=DATABUF[$33];
   form1.Alarm2_Minute.ItemIndex:=DATABUF[$34];
   form1.Continue_2.Position:=DATABUF[$35];

   if DATABUF[$38]<>0 then
    form1.NonActiveAlarm_3.Checked:=true
   else
    form1.NonActiveAlarm_3.Checked:=false;
   form1.Alarm3_Hour.ItemIndex:=DATABUF[$36];
   form1.Alarm3_Minute.ItemIndex:=DATABUF[$37];
   form1.Continue_3.Position:=DATABUF[$38];

   if DATABUF[$3B]<>0 then
    form1.NonActiveAlarm_4.Checked:=true
   else
    form1.NonActiveAlarm_4.Checked:=false;
   form1.Alarm4_Hour.ItemIndex:=DATABUF[$39];
   form1.Alarm4_Minute.ItemIndex:=DATABUF[$3A];
   form1.Continue_4.Position:=DATABUF[$3B];

   form1.DeviceMachineCode_1.text:=inttostr((DATABUF[$41]*256+DATABUF[$40]) mod 1024);
   form1.DeviceMachineCode_2.text:=inttostr((DATABUF[$43]*256+DATABUF[$42]) mod 1024);
   form1.DeviceMachineCode_3.text:=inttostr((DATABUF[$45]*256+DATABUF[$44]) mod 1024);
   form1.DeviceMachineCode_4.text:=inttostr((DATABUF[$47]*256+DATABUF[$46]) mod 1024);
   form1.DeviceMachineCode_5.text:=inttostr((DATABUF[$49]*256+DATABUF[$48]) mod 1024);
   form1.DeviceMachineCode_6.text:=inttostr((DATABUF[$4B]*256+DATABUF[$4A]) mod 1024);
   form1.DeviceMachineCode_7.text:=inttostr((DATABUF[$4D]*256+DATABUF[$4C]) mod 1024);
   form1.DeviceMachineCode_8.text:=inttostr((DATABUF[$4F]*256+DATABUF[$4E]) mod 1024);

   if DATABUF[$41]>=128 then form1.DeviceEnable_1.Checked:=false
   else form1.DeviceEnable_1.Checked:=true;
   if DATABUF[$43]>=128 then form1.DeviceEnable_2.Checked:=false
   else form1.DeviceEnable_2.Checked:=true;
   if DATABUF[$45]>=128 then form1.DeviceEnable_3.Checked:=false
   else form1.DeviceEnable_3.Checked:=true;
   if DATABUF[$47]>=128 then form1.DeviceEnable_4.Checked:=false
   else form1.DeviceEnable_4.Checked:=true;
   if DATABUF[$49]>=128 then form1.DeviceEnable_5.Checked:=false
   else form1.DeviceEnable_5.Checked:=true;
   if DATABUF[$4B]>=128 then form1.DeviceEnable_6.Checked:=false
   else form1.DeviceEnable_6.Checked:=true;
   if DATABUF[$4D]>=128 then form1.DeviceEnable_7.Checked:=false
   else form1.DeviceEnable_7.Checked:=true;
   if DATABUF[$4F]>=128 then form1.DeviceEnable_8.Checked:=false
   else form1.DeviceEnable_8.Checked:=true;

   form1.NeedPreKey.Checked:=SetRadioChecked(DATABUF[$50]);

   form1.CTIPreKey.Text:='';
   for i:=$51 to $58 do
      if DATABUF[i]<>$ff then form1.CTIPreKey.Text:=form1.CTIPreKey.Text+inttostr(DATABUF[i]);
   form1.ToneTimeout.Position:=DATABUF[$59];

   form1.CTINum1.Text:='';
   for i:=$60 to $6f do
      if DATABUF[i]<>$ff then form1.CTINum1.Text:=form1.CTINum1.Text+inttostr(DATABUF[i]);
   form1.CTINum2.Text:='';
   for i:=$70 to $7f do
      if DATABUF[i]<>$ff then form1.CTINum2.Text:=form1.CTINum2.Text+inttostr(DATABUF[i]);
   form1.CTINum3.Text:='';
   for i:=$80 to $8f do
      if DATABUF[i]<>$ff then form1.CTINum3.Text:=form1.CTINum3.Text+inttostr(DATABUF[i]);
   form1.CTINum4.Text:='';
   for i:=$90 to $9f do
      if DATABUF[i]<>$ff then form1.CTINum4.Text:=form1.CTINum4.Text+inttostr(DATABUF[i]);

   form1.DATATEL_1.Text:='';
   for i:=$A0 to $Af do
      if DATABUF[i]<>$ff then form1.DATATEL_1.Text:=form1.DATATEL_1.Text+inttostr(DATABUF[i]);
   form1.DATATEL_2.Text:='';
   for i:=$B0 to $Bf do
      if DATABUF[i]<>$ff then form1.DATATEL_2.Text:=form1.DATATEL_2.Text+inttostr(DATABUF[i]);
   form1.DATATEL_3.Text:='';
   for i:=$C0 to $Cf do
      if DATABUF[i]<>$ff then form1.DATATEL_3.Text:=form1.DATATEL_3.Text+inttostr(DATABUF[i]);
   form1.DATATEL_4.Text:='';
   for i:=$D0 to $Df do
      if DATABUF[i]<>$ff then form1.DATATEL_4.Text:=form1.DATATEL_4.Text+inttostr(DATABUF[i]);

   GateWayDateTime:=strtodatetime(format('%d/%d/%d %d:%d:%d',
                                         [DATABUF[$E1]*256+DATABUF[$E0],              //年
                                          DATABUF[$E2],DATABUF[$E3],                  //月日
                                          DATABUF[$E4],DATABUF[$E5],DATABUF[$E6]      //時分秒
                                         ]));
   form1.TimeStr.Caption:=datetimetostr(GateWayDateTime);

   form1.SPKSel1.ItemIndex:=DATABUF[$E7];
   form1.SPKSel2.ItemIndex:=DATABUF[$E8];
   form1.SPKSel3.ItemIndex:=DATABUF[$E9];
   form1.SPKSel4.ItemIndex:=DATABUF[$EA];


   BUF2RDIFCode($0A,form1.RFID_Code1);
   BUF2RDIFCode($18,form1.RFID_Code2);
   BUF2RDIFCode($1C,form1.RFID_Code3);
   BUF2RDIFCode($28,form1.RFID_Code4);
   BUF2RDIFCode($2C,form1.RFID_Code5);
   BUF2RDIFCode($3C,form1.RFID_Code6);
   BUF2RDIFCode($5A,form1.RFID_Code7);
   BUF2RDIFCode($EC,form1.RFID_Code8);
end;

function MemToSTR():string;
var i:integer;
begin
  result:='';
  for i:=0 to 255 do
  begin
    result:=result+inttostr(DATABUF[i]);
    if i<>255 then result:=result+',';
  end;
end;

function StrToMem(STR:string):boolean;
var
i:integer;
OPTSTR:Tstringlist;
begin
  OPTSTR:=Tstringlist.Create;
  OPTSTR.Delimiter:=',';
  OPTSTR.DelimitedText:=STR;
  if OPTSTR.Count<>256 then
  begin
     result:=false;
     exit;
  end;
  for i:=0 to 255 do
  begin
    DATABUF[i]:=strtoint(OPTSTR.Strings[i]);
  end;
  result:=true;
end;

end.
