unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, SPComm, StdCtrls, ExtCtrls;

type
  TScanPort = class(TForm)
    Comm1: TComm;
    Shape1: TShape;
    STAT: TLabel;

    procedure Comm1ReceiveData(Sender: TObject; Buffer: Pointer;
      BufferLength: Word);
    procedure FormActivate(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    FFinish:integer;
    { Public declarations }
  end;

var
  ScanPort: TScanPort;
  ScanCom:integer;
  FindCom:integer;
  ComCount:integer;
  CommArray:array[1..32] of TComm;
implementation
uses Unit1;
{$R *.dfm}

procedure TScanPort.Comm1ReceiveData(Sender: TObject; Buffer: Pointer;
  BufferLength: Word);
var
BUF:pchar;
BINData:array of byte;
chksum:byte;
Data,j:integer;
DataIndex:integer;
begin
   BINData:=Buffer;
   BUF:=pchar(BINData);
   if pos('GWON',BUF)>0 then
   begin
      //showmessage(inttostr(TComm(Sender).Tag));
      ScanCom:=TComm(Sender).Tag;
      exit;
   end;
end;

function GetComPortName(Port:integer):String;
begin

end;


procedure TScanPort.FormActivate(Sender: TObject);
var
i:integer;
succ:integer;
Delay:integer;
begin
   ScanCom:=0;
   FindCom:=0;
   FFinish:=0;
   ComCount:=0;
   Form1.COMPORT.Clear;
   Form1.COMPORT.AddItem('Scanning..',nil);
   Form1.COMPORT.ItemIndex:=0;
   Form1.Enabled:=false;
   for i:=1 to 32 do
   begin
      CommArray[i]:=TComm.Create(nil);
      CommArray[i].CommName:='\\.\COM'+inttostr(i);
      CommArray[i].BaudRate:=19200;
      CommArray[i].Tag:=i;
      CommArray[i].OnReceiveData:=Comm1ReceiveData;
      succ:=1;
      STAT.Caption:='Scanning Port..'+'COM'+inttostr(i);
      sleep(20);
      application.ProcessMessages;
      try
        CommArray[i].StartComm;
      except
        succ:=0;
      end;
      if succ=1 then
      begin
         ComCount:=ComCount+1;
         Form1.COMPORT.AddItem('COM'+inttostr(i),nil);
       end;
      application.ProcessMessages;
   end;
   STAT.Caption:='Detecting Gateway..';
   application.ProcessMessages;
   sleep(2500);
   application.ProcessMessages;
   if ScanCom=0 then
   begin
      STAT.Caption:='No Gateway found!!'
   end
   else
   begin
      STAT.Caption:='Gateway found on COM'+inttostr(ScanCom);
   end;

   Delay:=windows.GetTickCount;
   while(windows.GetTickCount-Delay<800) do
   begin
      application.ProcessMessages;
      sleep(1);
   end;
   Form1.COMPORT.Items.Delete(0);
   Form1.COMPORT.ItemIndex:=Form1.COMPORT.Items.IndexOf('COM'+inttostr(ScanCom));
   Form1.StatusBar1.SimpleText:=STAT.Caption;
   Form1.Button1.Enabled:=true;
   if ScanCom=0 then
   begin
      Form1.COMPORT.ItemIndex:=0;
      if Form1.COMPORT.Items.Count=0 then
         Form1.Button1.Enabled:=false;
   end;

   for i:=1 to 32 do
   begin
      CommArray[i].StopComm;
      CommArray[i].Free;
   end;
   Form1.Enabled:=true;
   FFinish:=1;
end;

procedure TScanPort.FormCreate(Sender: TObject);
begin
  Application.CreateForm(TForm1, Form1);
end;

end.
