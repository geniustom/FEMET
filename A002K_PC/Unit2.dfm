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
end
