program A002_PC_V314;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  Uart_Mem in 'Uart_Mem.pas',
  Unit2 in 'Unit2.pas' {ScanPort};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '�v�ݥD���]�w�{��';
  Application.CreateForm(TScanPort, ScanPort);
  
  Application.Run;
end.
