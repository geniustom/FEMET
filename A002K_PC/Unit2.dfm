object ScanPort: TScanPort
  Left = 279
  Top = 136
  BorderStyle = bsNone
  Caption = 'ScanPort'
  ClientHeight = 57
  ClientWidth = 472
  Color = clSkyBlue
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 0
    Top = 0
    Width = 472
    Height = 57
    Align = alClient
    Pen.Color = clSkyBlue
    Pen.Style = psDot
    Pen.Width = 5
    Shape = stRoundRect
  end
  object STAT: TLabel
    Left = 0
    Top = 0
    Width = 472
    Height = 57
    Align = alClient
    Alignment = taCenter
    AutoSize = False
    Caption = 'Scanning Port...'
    Font.Charset = ANSI_CHARSET
    Font.Color = 13008132
    Font.Height = -35
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Comm1: TComm
    CommName = 'COM2'
    BaudRate = 19200
    ParityCheck = False
    Outx_CtsFlow = False
    Outx_DsrFlow = False
    DtrControl = DtrEnable
    DsrSensitivity = False
    TxContinueOnXoff = False
    Outx_XonXoffFlow = False
    Inx_XonXoffFlow = False
    ReplaceWhenParityError = False
    IgnoreNullChar = False
    RtsControl = RtsEnable
    XonLimit = 500
    XoffLimit = 500
    ByteSize = _8
    Parity = None
    StopBits = _1
    XonChar = #17
    XoffChar = #19
    ReplacedChar = #0
    ReadIntervalTimeout = 5
    ReadTotalTimeoutMultiplier = 0
    ReadTotalTimeoutConstant = 0
    WriteTotalTimeoutMultiplier = 0
    WriteTotalTimeoutConstant = 0
    OnReceiveData = Comm1ReceiveData
    Left = 279
    Top = 117
  end
end
