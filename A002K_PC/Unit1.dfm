object Form1: TForm1
  Left = 224
  Top = 164
  BorderStyle = bsDialog
  Caption = #23429#31471#20027#27231#35373#23450#31243#24335'_Ver 3.15'
  ClientHeight = 397
  ClientWidth = 473
  Color = clBtnFace
  DefaultMonitor = dmDesktop
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  Visible = True
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 164
    Height = 376
    Align = alLeft
    TabOrder = 0
    object GroupBox8: TGroupBox
      Left = 8
      Top = 8
      Width = 149
      Height = 111
      Caption = #20659#36664#20171#38754
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 19
        Width = 36
        Height = 12
        Caption = #36899#25509#22496
      end
      object Label42: TLabel
        Left = 8
        Top = 45
        Width = 36
        Height = 12
        Caption = #20659#36664#29575
      end
      object Button8: TButton
        Left = 8
        Top = 74
        Width = 63
        Height = 27
        Caption = #33258#21205#20597#28204
        Enabled = False
        TabOrder = 3
        OnClick = Button8Click
      end
      object COMPORT: TComboBox
        Left = 50
        Top = 16
        Width = 91
        Height = 23
        Style = csDropDownList
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Consolas'
        Font.Style = []
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 15
        ItemIndex = 4
        ParentFont = False
        TabOrder = 0
        Text = 'COM5'
        Items.Strings = (
          'COM1'
          'COM2'
          'COM3'
          'COM4'
          'COM5'
          'COM6'
          'COM7'
          'COM8'
          'COM9'
          'COM10')
      end
      object Baudrate: TComboBox
        Left = 50
        Top = 42
        Width = 91
        Height = 23
        Style = csDropDownList
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Consolas'
        Font.Style = []
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 15
        ItemIndex = 3
        ParentFont = False
        TabOrder = 1
        Text = '19200'
        Items.Strings = (
          '1200'
          '2400'
          '9600'
          '19200'
          '38400'
          '57600'
          '115200'
          '230400'
          '')
      end
      object Button1: TButton
        Left = 76
        Top = 74
        Width = 64
        Height = 27
        Caption = #36899#32218
        TabOrder = 2
        OnClick = Button1Click
      end
    end
    object GroupBox9: TGroupBox
      Left = 8
      Top = 218
      Width = 149
      Height = 149
      Caption = #35373#23450#27284
      TabOrder = 1
      object Button2: TButton
        Left = 8
        Top = 16
        Width = 132
        Height = 27
        Caption = #36617#20837#35373#23450#27284
        TabOrder = 0
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 8
        Top = 42
        Width = 132
        Height = 27
        Caption = #20786#23384#35373#23450#27284
        TabOrder = 1
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 8
        Top = 68
        Width = 132
        Height = 28
        Caption = #36617#20837#20027#27231#35373#23450
        Enabled = False
        TabOrder = 2
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 8
        Top = 95
        Width = 132
        Height = 27
        Caption = #23531#20837#20027#27231#35373#23450
        Enabled = False
        TabOrder = 3
        OnClick = Button5Click
      end
      object ProgressBar1: TProgressBar
        Left = 8
        Top = 127
        Width = 132
        Height = 11
        Max = 256
        Smooth = True
        Step = 1
        TabOrder = 4
      end
    end
    object GroupBox10: TGroupBox
      Left = 8
      Top = 128
      Width = 149
      Height = 79
      Caption = #36984#25799#27169#24335
      TabOrder = 2
      object Button6: TButton
        Left = 9
        Top = 18
        Width = 133
        Height = 27
        Caption = #31995#32113#35373#23450#27169#24335
        TabOrder = 0
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 9
        Top = 44
        Width = 133
        Height = 27
        Caption = #31995#32113#28204#35430#27169#24335
        TabOrder = 1
        OnClick = Button7Click
      end
    end
    object Panel2: TPanel
      Left = 0
      Top = -1
      Width = 10
      Height = 13
      BevelOuter = bvNone
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnDblClick = Panel2DblClick
    end
  end
  object PageControl1: TPageControl
    Left = 164
    Top = 0
    Width = 309
    Height = 376
    ActivePage = TabSheet1
    Align = alClient
    HotTrack = True
    MultiLine = True
    Style = tsFlatButtons
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #31995#32113#35373#23450#27169#24335
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 301
        Height = 346
        ActivePage = TabSheet4
        Align = alClient
        Font.Charset = CHINESEBIG5_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#32048#26126#39636
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object TabSheet3: TTabSheet
          Caption = #20027#27231#35373#23450
          ImageIndex = 2
          object Label13: TLabel
            Left = 8
            Top = 8
            Width = 24
            Height = 12
            Caption = #27599#38548
          end
          object Label15: TLabel
            Left = 96
            Top = 8
            Width = 120
            Height = 12
            Caption = #20998#37912#36914#34892#31995#32113#33258#25105#27298#28204
          end
          object GroupBox1: TGroupBox
            Left = 6
            Top = 145
            Width = 65
            Height = 52
            Caption = #23458#25142#32232#34399
            TabOrder = 0
            object CustomerID: TMaskEdit
              Left = 9
              Top = 18
              Width = 45
              Height = 24
              Ctl3D = False
              EditMask = '0000;4;_'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Arial'
              Font.Style = []
              MaxLength = 4
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
              Text = '0001'
            end
          end
          object GroupBox2: TGroupBox
            Left = 77
            Top = 145
            Width = 82
            Height = 52
            Caption = #32882#38899#35373#23450
            TabOrder = 1
            object BuzzerMode: TRadioButton
              Left = 8
              Top = 16
              Width = 72
              Height = 15
              Caption = #26377#32882#27169#24335
              Checked = True
              TabOrder = 0
              TabStop = True
              OnClick = FirstReportClick
            end
            object NonBuzzerMode: TRadioButton
              Left = 8
              Top = 32
              Width = 72
              Height = 15
              Caption = #28961#32882#27169#24335
              TabOrder = 1
              OnClick = FirstReportClick
            end
          end
          object GroupBox3: TGroupBox
            Left = 3
            Top = 204
            Width = 285
            Height = 115
            Caption = #29992#34277#25552#37266'('#38920#38283#21855#26377#32882#27169#24335')'
            TabOrder = 2
            object Label20: TLabel
              Left = 103
              Top = 19
              Width = 12
              Height = 12
              Caption = #26178
            end
            object Label21: TLabel
              Left = 158
              Top = 19
              Width = 48
              Height = 12
              Caption = #20998#65292#25345#32396
            end
            object Label23: TLabel
              Left = 103
              Top = 42
              Width = 12
              Height = 12
              Caption = #26178
            end
            object Label26: TLabel
              Left = 103
              Top = 66
              Width = 12
              Height = 12
              Caption = #26178
            end
            object Label19: TLabel
              Left = 250
              Top = 19
              Width = 24
              Height = 12
              Caption = #20998#37912
            end
            object Label22: TLabel
              Left = 250
              Top = 42
              Width = 24
              Height = 12
              Caption = #20998#37912
            end
            object Label24: TLabel
              Left = 158
              Top = 42
              Width = 48
              Height = 12
              Caption = #20998#65292#25345#32396
            end
            object Label25: TLabel
              Left = 250
              Top = 66
              Width = 24
              Height = 12
              Caption = #20998#37912
            end
            object Label27: TLabel
              Left = 158
              Top = 66
              Width = 48
              Height = 12
              Caption = #20998#65292#25345#32396
            end
            object Label44: TLabel
              Left = 103
              Top = 91
              Width = 12
              Height = 12
              Caption = #26178
            end
            object Label49: TLabel
              Left = 158
              Top = 91
              Width = 48
              Height = 12
              Caption = #20998#65292#25345#32396
            end
            object Label50: TLabel
              Left = 250
              Top = 91
              Width = 24
              Height = 12
              Caption = #20998#37912
            end
            object Alarm1_Hour: TComboBox
              Left = 66
              Top = 16
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 8
              TabOrder = 0
              Text = '08'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23')
            end
            object Alarm1_Minute: TComboBox
              Left = 119
              Top = 16
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 0
              TabOrder = 1
              Text = '00'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23'
                '24'
                '25'
                '26'
                '27'
                '28'
                '29'
                '30'
                '31'
                '32'
                '33'
                '34'
                '35'
                '36'
                '37'
                '38'
                '39'
                '40'
                '41'
                '42'
                '43'
                '44'
                '45'
                '46'
                '47'
                '48'
                '49'
                '50'
                '51'
                '52'
                '53'
                '54'
                '55'
                '56'
                '57'
                '58'
                '59')
            end
            object NonActiveAlarm_1: TCheckBox
              Left = 8
              Top = 19
              Width = 56
              Height = 15
              Caption = #26178#27573#19968
              Checked = True
              State = cbChecked
              TabOrder = 2
              OnClick = FirstReportClick
            end
            object Alarm2_Minute: TComboBox
              Left = 119
              Top = 39
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 0
              TabOrder = 3
              Text = '00'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23'
                '24'
                '25'
                '26'
                '27'
                '28'
                '29'
                '30'
                '31'
                '32'
                '33'
                '34'
                '35'
                '36'
                '37'
                '38'
                '39'
                '40'
                '41'
                '42'
                '43'
                '44'
                '45'
                '46'
                '47'
                '48'
                '49'
                '50'
                '51'
                '52'
                '53'
                '54'
                '55'
                '56'
                '57'
                '58'
                '59')
            end
            object Alarm2_Hour: TComboBox
              Left = 66
              Top = 39
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 12
              TabOrder = 4
              Text = '12'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23')
            end
            object NonActiveAlarm_2: TCheckBox
              Left = 8
              Top = 42
              Width = 56
              Height = 15
              Caption = #26178#27573#20108
              Checked = True
              State = cbChecked
              TabOrder = 5
              OnClick = FirstReportClick
            end
            object Alarm3_Minute: TComboBox
              Left = 119
              Top = 64
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 0
              TabOrder = 6
              Text = '00'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23'
                '24'
                '25'
                '26'
                '27'
                '28'
                '29'
                '30'
                '31'
                '32'
                '33'
                '34'
                '35'
                '36'
                '37'
                '38'
                '39'
                '40'
                '41'
                '42'
                '43'
                '44'
                '45'
                '46'
                '47'
                '48'
                '49'
                '50'
                '51'
                '52'
                '53'
                '54'
                '55'
                '56'
                '57'
                '58'
                '59')
            end
            object Alarm3_Hour: TComboBox
              Left = 66
              Top = 64
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 16
              TabOrder = 7
              Text = '16'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23')
            end
            object NonActiveAlarm_3: TCheckBox
              Left = 8
              Top = 66
              Width = 56
              Height = 15
              Caption = #26178#27573#19977
              Checked = True
              State = cbChecked
              TabOrder = 8
              OnClick = FirstReportClick
            end
            object Alarm1_Continue: TEdit
              Left = 208
              Top = 16
              Width = 25
              Height = 20
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ReadOnly = True
              TabOrder = 9
              Text = '1'
            end
            object Continue_1: TUpDown
              Left = 233
              Top = 16
              Width = 16
              Height = 20
              Associate = Alarm1_Continue
              Max = 30
              Position = 1
              TabOrder = 10
            end
            object Continue_2: TUpDown
              Left = 233
              Top = 39
              Width = 16
              Height = 20
              Associate = Alarm2_Continue
              Max = 30
              Position = 1
              TabOrder = 11
            end
            object Alarm2_Continue: TEdit
              Left = 208
              Top = 39
              Width = 25
              Height = 20
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ReadOnly = True
              TabOrder = 12
              Text = '1'
            end
            object Continue_3: TUpDown
              Left = 233
              Top = 64
              Width = 16
              Height = 20
              Associate = Alarm3_Continue
              Max = 30
              Position = 1
              TabOrder = 13
            end
            object Alarm3_Continue: TEdit
              Left = 208
              Top = 64
              Width = 25
              Height = 20
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ReadOnly = True
              TabOrder = 14
              Text = '1'
            end
            object NonActiveAlarm_4: TCheckBox
              Left = 8
              Top = 91
              Width = 56
              Height = 15
              Caption = #26178#27573#22235
              Checked = True
              State = cbChecked
              TabOrder = 15
              OnClick = FirstReportClick
            end
            object Alarm4_Hour: TComboBox
              Left = 66
              Top = 89
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 20
              TabOrder = 16
              Text = '20'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23')
            end
            object Alarm4_Minute: TComboBox
              Left = 119
              Top = 89
              Width = 35
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 30
              TabOrder = 17
              Text = '30'
              Items.Strings = (
                '00'
                '01'
                '02'
                '03'
                '04'
                '05'
                '06'
                '07'
                '08'
                '09'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23'
                '24'
                '25'
                '26'
                '27'
                '28'
                '29'
                '30'
                '31'
                '32'
                '33'
                '34'
                '35'
                '36'
                '37'
                '38'
                '39'
                '40'
                '41'
                '42'
                '43'
                '44'
                '45'
                '46'
                '47'
                '48'
                '49'
                '50'
                '51'
                '52'
                '53'
                '54'
                '55'
                '56'
                '57'
                '58'
                '59')
            end
            object Alarm4_Continue: TEdit
              Left = 208
              Top = 89
              Width = 25
              Height = 20
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ReadOnly = True
              TabOrder = 18
              Text = '1'
            end
            object Continue_4: TUpDown
              Left = 233
              Top = 89
              Width = 16
              Height = 20
              Associate = Alarm4_Continue
              Max = 30
              Position = 1
              TabOrder = 19
            end
          end
          object GroupBox5: TGroupBox
            Left = 3
            Top = 31
            Width = 286
            Height = 51
            Caption = #20027#27231#23433#35037#24460#31532#19968#27425#28204#35430
            TabOrder = 3
            object FirstReportDate: TDateTimePicker
              Left = 53
              Top = 20
              Width = 68
              Height = 20
              Date = 40299.500000000000000000
              Format = 'yy/MM/dd'
              Time = 40299.500000000000000000
              Color = clBtnFace
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              TabOrder = 0
            end
            object FirstReportTime: TDateTimePicker
              Left = 131
              Top = 20
              Width = 53
              Height = 20
              Date = 39884.500000000000000000
              Format = 'HH:mm'
              Time = 39884.500000000000000000
              Color = clBtnFace
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              Kind = dtkTime
              TabOrder = 1
            end
            object FirstReport: TCheckBox
              Left = 10
              Top = 22
              Width = 41
              Height = 14
              Caption = #38283#21855
              Checked = True
              State = cbChecked
              TabOrder = 2
              OnClick = FirstReportClick
            end
          end
          object GroupBox7: TGroupBox
            Left = 3
            Top = 89
            Width = 285
            Height = 50
            Caption = #20027#27231#23450#26178#31995#32113#22238#22577'('#35373#23450#38291#38548'0'#23567#26178#28858#38364#38281#31995#32113#22238#22577')'
            TabOrder = 4
            object Label43: TLabel
              Left = 157
              Top = 23
              Width = 51
              Height = 12
              Caption = #20998#36215','#38291#38548
            end
            object Label45: TLabel
              Left = 256
              Top = 23
              Width = 24
              Height = 12
              Caption = #23567#26178
            end
            object Label46: TLabel
              Left = 7
              Top = 23
              Width = 12
              Height = 12
              Caption = #24478
            end
            object Label55: TLabel
              Left = 129
              Top = 23
              Width = 19
              Height = 22
              AutoSize = False
              Caption = #40670
            end
            object LBL_SEC: TLabel
              Left = 143
              Top = 23
              Width = 12
              Height = 12
              Caption = '00'
            end
            object SystemReportDate: TDateTimePicker
              Left = 21
              Top = 20
              Width = 70
              Height = 20
              Date = 40299.522835729160000000
              Format = 'yy/MM/dd'
              Time = 40299.522835729160000000
              Color = clBtnFace
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              TabOrder = 0
            end
            object SystemReportHour: TComboBox
              Left = 90
              Top = 19
              Width = 37
              Height = 20
              Style = csDropDownList
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ItemHeight = 12
              ItemIndex = 12
              TabOrder = 1
              Text = '12'
              Items.Strings = (
                '0'
                '1'
                '2'
                '3'
                '4'
                '5'
                '6'
                '7'
                '8'
                '9'
                '10'
                '11'
                '12'
                '13'
                '14'
                '15'
                '16'
                '17'
                '18'
                '19'
                '20'
                '21'
                '22'
                '23')
            end
            object SystemReportContinue: TEdit
              Left = 213
              Top = 20
              Width = 28
              Height = 20
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ReadOnly = True
              TabOrder = 2
              Text = '24'
            end
            object UpDown5: TUpDown
              Left = 241
              Top = 20
              Width = 16
              Height = 20
              Associate = SystemReportContinue
              Max = 255
              Position = 24
              TabOrder = 3
            end
          end
          object GroupBox12: TGroupBox
            Left = 166
            Top = 145
            Width = 123
            Height = 53
            Caption = #29983#29702#37327#28204#27169#24335#35373#23450
            TabOrder = 5
            object BatchSend_0: TRadioButton
              Left = 8
              Top = 16
              Width = 98
              Height = 15
              Caption = #37327#28204#21934#31558#20659#36865
              Checked = True
              TabOrder = 0
              TabStop = True
              OnClick = FirstReportClick
            end
            object BatchSend_1: TRadioButton
              Left = 8
              Top = 32
              Width = 98
              Height = 15
              Caption = #37327#28204#22810#31558#20659#36865
              TabOrder = 1
              OnClick = FirstReportClick
            end
          end
          object SystemCheckTimeout: TComboBox
            Left = 42
            Top = 6
            Width = 49
            Height = 20
            Style = csDropDownList
            ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
            ItemHeight = 12
            ItemIndex = 0
            TabOrder = 6
            Text = '1'
            Items.Strings = (
              '1'
              '2'
              '3'
              '4'
              '5'
              '6'
              '7'
              '8'
              '9'
              '10'
              '11'
              '12'
              '13'
              '14'
              '15'
              '16'
              '17'
              '18'
              '19'
              '20'
              '21'
              '22'
              '23'
              '24'
              '25'
              '26'
              '27'
              '28'
              '29'
              '30')
          end
        end
        object TabSheet4: TTabSheet
          Caption = #22739#25187#35373#23450
          object GroupBox16: TGroupBox
            Left = 3
            Top = 3
            Width = 286
            Height = 220
            Caption = #22739#25187#37197#23565#35373#23450
            TabOrder = 0
            object Label3: TLabel
              Left = 189
              Top = 19
              Width = 70
              Height = 11
              AutoSize = False
              Caption = #37197#23565'RFID'
            end
            object Label4: TLabel
              Left = 89
              Top = 19
              Width = 75
              Height = 12
              AutoSize = False
              Caption = #37197#23565#22739#25187#30908
            end
            object DeviceMachineCode_8: TEdit
              Left = 83
              Top = 184
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
              Text = '64'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceEnable_8: TCheckBox
              Left = 8
              Top = 187
              Width = 66
              Height = 15
              Caption = #22739#25187#20843
              Checked = True
              State = cbChecked
              TabOrder = 1
              OnClick = FirstReportClick
            end
            object DeviceEnable_7: TCheckBox
              Left = 8
              Top = 166
              Width = 66
              Height = 16
              Caption = #22739#25187#19971
              Checked = True
              State = cbChecked
              TabOrder = 2
              OnClick = FirstReportClick
            end
            object DeviceMachineCode_7: TEdit
              Left = 83
              Top = 163
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 3
              Text = '56'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceMachineCode_6: TEdit
              Left = 83
              Top = 142
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 4
              Text = '48'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceEnable_6: TCheckBox
              Left = 8
              Top = 145
              Width = 66
              Height = 16
              Caption = #22739#25187#20845
              Checked = True
              State = cbChecked
              TabOrder = 5
              OnClick = FirstReportClick
            end
            object DeviceEnable_5: TCheckBox
              Left = 8
              Top = 124
              Width = 66
              Height = 16
              Caption = #22739#25187#20116
              Checked = True
              State = cbChecked
              TabOrder = 6
              OnClick = FirstReportClick
            end
            object DeviceMachineCode_5: TEdit
              Left = 83
              Top = 121
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 7
              Text = '40'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceMachineCode_4: TEdit
              Left = 83
              Top = 100
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 8
              Text = '32'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceEnable_4: TCheckBox
              Left = 8
              Top = 103
              Width = 66
              Height = 16
              Caption = #22739#25187#22235
              Checked = True
              State = cbChecked
              TabOrder = 9
              OnClick = FirstReportClick
            end
            object DeviceEnable_3: TCheckBox
              Left = 8
              Top = 82
              Width = 66
              Height = 15
              Caption = #22739#25187#19977
              Checked = True
              State = cbChecked
              TabOrder = 10
              OnClick = FirstReportClick
            end
            object DeviceMachineCode_3: TEdit
              Left = 83
              Top = 79
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 11
              Text = '24'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceMachineCode_2: TEdit
              Left = 83
              Top = 58
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 12
              Text = '16'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object DeviceEnable_2: TCheckBox
              Left = 8
              Top = 61
              Width = 66
              Height = 16
              Caption = #22739#25187#20108
              Checked = True
              State = cbChecked
              TabOrder = 13
              OnClick = FirstReportClick
            end
            object DeviceEnable_1: TCheckBox
              Left = 8
              Top = 40
              Width = 66
              Height = 16
              Caption = #22739#25187#19968
              Checked = True
              State = cbChecked
              TabOrder = 14
              OnClick = FirstReportClick
            end
            object DeviceMachineCode_1: TEdit
              Left = 83
              Top = 37
              Width = 70
              Height = 21
              BiDiMode = bdLeftToRight
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ImeMode = imClose
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 15
              Text = '8'
              OnChange = DeviceMachineCode_1Change
              OnKeyPress = DeviceMachineCode_1KeyPress
            end
            object RFID_Code1: TMaskEdit
              Left = 168
              Top = 37
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 16
              Text = ' 00 00 00 00'
            end
            object RFID_Code2: TMaskEdit
              Left = 168
              Top = 58
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 17
              Text = ' 00 00 00 00'
            end
            object RFID_Code3: TMaskEdit
              Left = 168
              Top = 79
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 18
              Text = ' 00 00 00 00'
            end
            object RFID_Code4: TMaskEdit
              Left = 168
              Top = 100
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 19
              Text = ' 00 00 00 00'
            end
            object RFID_Code5: TMaskEdit
              Left = 168
              Top = 121
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 20
              Text = ' 00 00 00 00'
            end
            object RFID_Code6: TMaskEdit
              Left = 168
              Top = 142
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 21
              Text = ' 00 00 00 00'
            end
            object RFID_Code7: TMaskEdit
              Left = 168
              Top = 163
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 22
              Text = ' 00 00 00 00'
            end
            object RFID_Code8: TMaskEdit
              Left = 168
              Top = 184
              Width = 93
              Height = 21
              CharCase = ecUpperCase
              Ctl3D = False
              EditMask = ' !AA AA AA AA;1;'
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              MaxLength = 12
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 23
              Text = ' 00 00 00 00'
            end
          end
          object RFIDNUM: TMemo
            Left = 3
            Top = 228
            Width = 169
            Height = 25
            Color = clBlack
            Ctl3D = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clLime
            Font.Height = -13
            Font.Name = 'Comic Sans MS'
            Font.Style = [fsBold]
            ParentCtl3D = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 1
            WantReturns = False
            WordWrap = False
          end
          object Button16: TButton
            Left = 180
            Top = 228
            Width = 28
            Height = 25
            Caption = '>>'
            TabOrder = 2
            OnClick = Button16Click
          end
          object RFIDSel: TComboBox
            Left = 216
            Top = 228
            Width = 73
            Height = 25
            Style = csDropDownList
            Color = clBlack
            Font.Charset = ANSI_CHARSET
            Font.Color = clLime
            Font.Height = -13
            Font.Name = #24494#36575#27491#40657#39636
            Font.Style = [fsBold]
            ItemHeight = 17
            ItemIndex = 0
            ParentFont = False
            TabOrder = 3
            Text = #22739#25187#19968
            Items.Strings = (
              #22739#25187#19968
              #22739#25187#20108
              #22739#25187#19977
              #22739#25187#22235
              #22739#25187#20116
              #22739#25187#20845
              #22739#25187#19971
              #22739#25187#20843)
          end
        end
        object TabSheet5: TTabSheet
          Caption = #38651#35441#35373#23450
          ImageIndex = 1
          object Label33: TLabel
            Left = 10
            Top = 8
            Width = 149
            Height = 16
            AutoSize = False
          end
          object CTIPreKey: TEdit
            Left = 208
            Top = 6
            Width = 78
            Height = 21
            Ctl3D = False
            Enabled = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Arial'
            Font.Style = [fsBold]
            ImeMode = imDisable
            MaxLength = 8
            ParentCtl3D = False
            ParentFont = False
            TabOrder = 0
          end
          object GroupBox6: TGroupBox
            Left = 10
            Top = 32
            Width = 218
            Height = 116
            Caption = #23458#26381#38651#35441
            TabOrder = 1
            object Label18: TLabel
              Left = 10
              Top = 19
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#19968#23458#26381#38651#35441
            end
            object Label30: TLabel
              Left = 10
              Top = 42
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#20108#23458#26381#38651#35441
            end
            object Label31: TLabel
              Left = 10
              Top = 66
              Width = 73
              Height = 12
              AutoSize = False
              Caption = #31532#19977#23458#26381#38651#35441
            end
            object Label32: TLabel
              Left = 10
              Top = 90
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#22235#23458#26381#38651#35441
            end
            object CTINum4: TEdit
              Left = 84
              Top = 87
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
              Text = '89135683'
            end
            object CTINum3: TEdit
              Left = 84
              Top = 64
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 1
              Text = '89135683'
            end
            object CTINum2: TEdit
              Left = 84
              Top = 39
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 2
              Text = '89135683'
            end
            object CTINum1: TEdit
              Left = 84
              Top = 16
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 3
              Text = '89135683'
            end
          end
          object NeedPreKey: TCheckBox
            Left = 10
            Top = 8
            Width = 198
            Height = 15
            Caption = '['#20132#25563#27231#23560#29992']'#25765#34399#21069#38920#20808#25765#25171#34399#30908
            TabOrder = 2
            OnClick = NeedPreKeyClick
          end
          object GroupBox13: TGroupBox
            Left = 10
            Top = 153
            Width = 218
            Height = 116
            Caption = #36039#26009#20659#36664
            TabOrder = 3
            object Label2: TLabel
              Left = 10
              Top = 19
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#19968#20659#36664#38651#35441
            end
            object Label5: TLabel
              Left = 10
              Top = 42
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#20108#20659#36664#38651#35441
            end
            object Label7: TLabel
              Left = 10
              Top = 66
              Width = 73
              Height = 12
              AutoSize = False
              Caption = #31532#19977#20659#36664#38651#35441
            end
            object Label9: TLabel
              Left = 10
              Top = 90
              Width = 73
              Height = 11
              AutoSize = False
              Caption = #31532#22235#20659#36664#38651#35441
            end
            object DATATEL_4: TEdit
              Left = 84
              Top = 87
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
              Text = '89135683'
            end
            object DATATEL_3: TEdit
              Left = 84
              Top = 64
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 1
              Text = '89135683'
            end
            object DATATEL_2: TEdit
              Left = 84
              Top = 39
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 2
              Text = '89135683'
            end
            object DATATEL_1: TEdit
              Left = 84
              Top = 16
              Width = 123
              Height = 21
              Ctl3D = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeMode = imDisable
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 3
              Text = '89135683'
            end
          end
          object GroupBox24: TGroupBox
            Left = 9
            Top = 273
            Width = 220
            Height = 43
            Caption = #20659#36664'TIMEOUT'#35373#23450'(15-30 SEC)'
            TabOrder = 4
            object Label74: TLabel
              Left = 6
              Top = 18
              Width = 60
              Height = 12
              Caption = #25765#34399#24460#31561#24453
            end
            object Label75: TLabel
              Left = 114
              Top = 18
              Width = 97
              Height = 12
              AutoSize = False
              Caption = #31186#28961#22238#25033#21063#37325#25765
            end
            object ToneTimeoutTEXT: TEdit
              Left = 69
              Top = 15
              Width = 25
              Height = 20
              TabOrder = 0
              Text = '15'
            end
            object ToneTimeout: TUpDown
              Left = 94
              Top = 15
              Width = 16
              Height = 20
              Associate = ToneTimeoutTEXT
              Min = 15
              Max = 30
              Position = 15
              TabOrder = 1
            end
          end
        end
        object TabSheet8: TTabSheet
          Caption = #36914#38542#35373#23450
          ImageIndex = 3
          object GroupBox18: TGroupBox
            Left = 9
            Top = 138
            Width = 277
            Height = 115
            Caption = #21895#21485#38899#37327#35373#23450
            TabOrder = 0
            object Label64: TLabel
              Left = 12
              Top = 90
              Width = 55
              Height = 12
              AutoSize = False
              Caption = #23458#26381#36890#35441
            end
            object Label63: TLabel
              Left = 12
              Top = 66
              Width = 55
              Height = 12
              AutoSize = False
              Caption = #35486#38899#25552#31034
            end
            object Label62: TLabel
              Left = 12
              Top = 42
              Width = 55
              Height = 12
              AutoSize = False
              Caption = #20659'  '#36664'  '#38899
            end
            object Label61: TLabel
              Left = 12
              Top = 18
              Width = 55
              Height = 12
              AutoSize = False
              Caption = #25765'  '#30908'  '#38899
            end
            object SPKSel4: TComboBox
              Left = 66
              Top = 87
              Width = 106
              Height = 20
              Style = csDropDownList
              ItemHeight = 12
              ItemIndex = 7
              TabOrder = 0
              Text = #65288#65303#65289#26368#22823
              Items.Strings = (
                #65288#65296#65289#28961#32882
                #65288#65297#65289#26368#23567
                #65288#65298#65289#23567#32882
                #65288#65299#65289#20559#20302
                #65288#65300#65289#20013#31561
                #65288#65301#65289#20559#39640
                #65288#65302#65289#22823#32882
                #65288#65303#65289#26368#22823)
            end
            object SPKSel3: TComboBox
              Left = 66
              Top = 63
              Width = 106
              Height = 20
              Style = csDropDownList
              ItemHeight = 12
              ItemIndex = 7
              TabOrder = 1
              Text = #65288#65303#65289#26368#22823
              Items.Strings = (
                #65288#65296#65289#28961#32882
                #65288#65297#65289#26368#23567
                #65288#65298#65289#23567#32882
                #65288#65299#65289#20559#20302
                #65288#65300#65289#20013#31561
                #65288#65301#65289#20559#39640
                #65288#65302#65289#22823#32882
                #65288#65303#65289#26368#22823)
            end
            object SPKSel2: TComboBox
              Left = 66
              Top = 39
              Width = 106
              Height = 20
              Style = csDropDownList
              ItemHeight = 12
              ItemIndex = 1
              TabOrder = 2
              Text = #65288#65297#65289#26368#23567
              Items.Strings = (
                #65288#65296#65289#28961#32882
                #65288#65297#65289#26368#23567
                #65288#65298#65289#23567#32882
                #65288#65299#65289#20559#20302
                #65288#65300#65289#20013#31561
                #65288#65301#65289#20559#39640
                #65288#65302#65289#22823#32882
                #65288#65303#65289#26368#22823)
            end
            object SPKSel1: TComboBox
              Left = 66
              Top = 15
              Width = 106
              Height = 20
              Style = csDropDownList
              ItemHeight = 12
              ItemIndex = 3
              TabOrder = 3
              Text = #65288#65299#65289#20559#20302
              Items.Strings = (
                #65288#65296#65289#28961#32882
                #65288#65297#65289#26368#23567
                #65288#65298#65289#23567#32882
                #65288#65299#65289#20559#20302
                #65288#65300#65289#20013#31561
                #65288#65301#65289#20559#39640
                #65288#65302#65289#22823#32882
                #65288#65303#65289#26368#22823)
            end
          end
          object GroupBox17: TGroupBox
            Left = 9
            Top = 52
            Width = 277
            Height = 81
            Caption = #37327#28204#36039#26009#28165#38500
            TabOrder = 1
            object MeasureAutoDel: TCheckBox
              Left = 9
              Top = 18
              Width = 253
              Height = 19
              Caption = #30070#25353#19979#22739#25187#26178#33258#21205#28165#38500#34880#22739'/'#34880#31958#35336#30340#36039#26009
              Checked = True
              State = cbChecked
              TabOrder = 0
            end
            object Button14: TButton
              Left = 9
              Top = 45
              Width = 256
              Height = 25
              Caption = #31435#21363#21034#38500#25152#26377#20659#36664#27169#32068#30340#36039#26009
              TabOrder = 1
              OnClick = Button14Click
            end
          end
          object GroupBox19: TGroupBox
            Left = 9
            Top = 3
            Width = 277
            Height = 46
            Caption = #36039#26009#20659#36664#37325#35430#27425#25976#35373#23450
            TabOrder = 2
            object Label66: TLabel
              Left = 9
              Top = 21
              Width = 25
              Height = 16
              AutoSize = False
              Caption = #37325#35430
            end
            object Label67: TLabel
              Left = 102
              Top = 21
              Width = 160
              Height = 16
              AutoSize = False
              Caption = #27425#23559#26410#20659#36865#25104#21151#30340#35352#37636#21034#38500
            end
            object RetryCount: TUpDown
              Left = 76
              Top = 18
              Width = 16
              Height = 18
              Associate = RetryCountT
              Min = 1
              Max = 255
              Position = 20
              TabOrder = 0
            end
            object RetryCountT: TMaskEdit
              Left = 39
              Top = 18
              Width = 37
              Height = 18
              Ctl3D = False
              EditMask = '!099;1;_'
              MaxLength = 3
              ParentCtl3D = False
              TabOrder = 1
              Text = ' 20'
            end
          end
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #31995#32113#28204#35430#27169#24335
      ImageIndex = 1
      object PageControl3: TPageControl
        Left = 0
        Top = 0
        Width = 301
        Height = 346
        ActivePage = TabSheet6
        Align = alClient
        TabOrder = 0
        object TabSheet6: TTabSheet
          Caption = #23429#31471#27231
          object GroupBox11: TGroupBox
            Left = 5
            Top = 3
            Width = 104
            Height = 282
            Caption = #22739#25187#29376#24907#28204#35430
            TabOrder = 0
            object Label41: TLabel
              Left = 10
              Top = 255
              Width = 36
              Height = 12
              Caption = #22739#25187#20843
            end
            object Label40: TLabel
              Left = 10
              Top = 231
              Width = 36
              Height = 12
              Caption = #22739#25187#19971
            end
            object Label39: TLabel
              Left = 10
              Top = 207
              Width = 36
              Height = 12
              Caption = #22739#25187#20845
            end
            object Label38: TLabel
              Left = 10
              Top = 184
              Width = 36
              Height = 12
              Caption = #22739#25187#20116
            end
            object Label37: TLabel
              Left = 10
              Top = 159
              Width = 36
              Height = 12
              Caption = #22739#25187#22235
            end
            object Label36: TLabel
              Left = 10
              Top = 136
              Width = 36
              Height = 12
              Caption = #22739#25187#19977
            end
            object Label35: TLabel
              Left = 10
              Top = 113
              Width = 36
              Height = 12
              Caption = #22739#25187#20108
            end
            object Label34: TLabel
              Left = 10
              Top = 88
              Width = 36
              Height = 12
              Caption = #22739#25187#19968
            end
            object Label48: TLabel
              Left = 10
              Top = 42
              Width = 36
              Height = 12
              Caption = #21462#28040#37397
            end
            object Label47: TLabel
              Left = 10
              Top = 19
              Width = 36
              Height = 12
              Caption = #23458#26381#37397
            end
            object Label11: TLabel
              Left = 10
              Top = 65
              Width = 36
              Height = 12
              Caption = #22238#22577#37397
            end
            object PAN_9: TEdit
              Left = 52
              Top = 18
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 0
              Text = ' '#26410#25353#19979
            end
            object PAN_0: TEdit
              Left = 52
              Top = 41
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 1
              Text = ' '#26410#25353#19979
            end
            object PAN_10: TEdit
              Left = 52
              Top = 65
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 2
              Text = ' '#26410#25353#19979
            end
            object PAN_1: TEdit
              Left = 52
              Top = 88
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 3
              Text = ' '#26410#25353#19979
            end
            object PAN_2: TEdit
              Left = 52
              Top = 112
              Width = 45
              Height = 16
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 4
              Text = ' '#26410#25353#19979
            end
            object PAN_3: TEdit
              Left = 52
              Top = 135
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 5
              Text = ' '#26410#25353#19979
            end
            object PAN_4: TEdit
              Left = 52
              Top = 158
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 6
              Text = ' '#26410#25353#19979
            end
            object PAN_5: TEdit
              Left = 52
              Top = 182
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 7
              Text = ' '#26410#25353#19979
            end
            object PAN_6: TEdit
              Left = 52
              Top = 205
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 8
              Text = ' '#26410#25353#19979
            end
            object PAN_7: TEdit
              Left = 52
              Top = 229
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 9
              Text = ' '#26410#25353#19979
            end
            object PAN_8: TEdit
              Left = 52
              Top = 252
              Width = 45
              Height = 17
              AutoSelect = False
              AutoSize = False
              BevelInner = bvNone
              BevelOuter = bvNone
              BiDiMode = bdLeftToRight
              Color = clBlack
              Ctl3D = True
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = #24494#36575#27491#40657#39636
              Font.Style = []
              ParentBiDiMode = False
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ReadOnly = True
              ShowHint = False
              TabOrder = 10
              Text = ' '#26410#25353#19979
            end
          end
          object GroupBox4: TGroupBox
            Left = 114
            Top = 3
            Width = 175
            Height = 112
            Caption = #23429#31471#20027#27231'RTC'#28204#35430
            TabOrder = 1
            object TimeStr: TLabel
              Left = 23
              Top = 33
              Width = 143
              Height = 15
              AutoSize = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636'-ExtB'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label17: TLabel
              Left = 11
              Top = 17
              Width = 142
              Height = 12
              Caption = #35531#25353'"'#36617#20837#20027#27231#35373#23450'"'#35712#21462
              Font.Charset = ANSI_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636'-ExtB'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label53: TLabel
              Left = 11
              Top = 50
              Width = 147
              Height = 12
              Caption = #33287'PC'#26178#38291#24046'10'#31186#20839#28858#27491#24120
              Font.Charset = ANSI_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636'-ExtB'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object TimeLabel: TLabel
              Left = 23
              Top = 67
              Width = 143
              Height = 15
              AutoSize = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636'-ExtB'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object TimeDef: TLabel
              Left = 17
              Top = 83
              Width = 139
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Caption = #23578#26410#28204#35430
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
          end
          object GroupBox14: TGroupBox
            Left = 114
            Top = 117
            Width = 175
            Height = 91
            Caption = #27888#21338#34880#22739#35336#36890#35338#28204#35430
            TabOrder = 2
            object DevLabel: TLabel
              Left = 17
              Top = 62
              Width = 139
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Caption = #23578#26410#28204#35430
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Label29: TLabel
              Left = 8
              Top = 17
              Width = 160
              Height = 11
              AutoSize = False
              Caption = #35531#25509#22949#20659#36664#32218#24460#65292#25353#19979#22739#25187
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label51: TLabel
              Left = 8
              Top = 47
              Width = 160
              Height = 11
              AutoSize = False
              Caption = #20006#30906#35469#34880#22739#35336#20986#29694#24515#22411#38275#29197
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label52: TLabel
              Left = 8
              Top = 32
              Width = 160
              Height = 11
              AutoSize = False
              Caption = #33509#25353#19979#22739#25187#28961#21453#25033#20195#34920#30064#24120
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object GroupBox15: TGroupBox
            Left = 114
            Top = 210
            Width = 175
            Height = 109
            Caption = #20659#36664#27169#32068#36890#35338#28204#35430
            TabOrder = 3
            object DonLabel: TLabel
              Left = 17
              Top = 77
              Width = 139
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Caption = #23578#26410#28204#35430
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Label54: TLabel
              Left = 8
              Top = 17
              Width = 160
              Height = 12
              AutoSize = False
              Caption = #35531#25509#22949#20659#36664#27169#32068#65292#25353#19979#22739#25187
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label65: TLabel
              Left = 8
              Top = 32
              Width = 160
              Height = 12
              AutoSize = False
              Caption = #33509#25353#19979#22739#25187#28961#21453#25033#20195#34920#30064#24120
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label28: TLabel
              Left = 17
              Top = 56
              Width = 32
              Height = 12
              AutoSize = False
              Caption = #34880#22739
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label60: TLabel
              Left = 92
              Top = 56
              Width = 32
              Height = 12
              AutoSize = False
              Caption = #34880#31958
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Don1: TLabel
              Left = 48
              Top = 50
              Width = 34
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = 'Arial Narrow'
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Don2: TLabel
              Left = 123
              Top = 50
              Width = 34
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = 'Arial Narrow'
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
          end
        end
        object CreateTest: TTabSheet
          Caption = #37327#29986
          ImageIndex = 3
          object SpeedButton1: TSpeedButton
            Left = 36
            Top = 270
            Width = 85
            Height = 40
            AllowAllUp = True
            GroupIndex = 1
            Caption = #21855#21205#37327#29986#28204#35430
            Enabled = False
            OnClick = SpeedButton1Click
          end
          object BT_Next: TButton
            Left = 168
            Top = 270
            Width = 88
            Height = 40
            Caption = #19979#19968#21488
            TabOrder = 0
            OnClick = BT_NextClick
          end
          object GroupBox20: TGroupBox
            Left = 6
            Top = 6
            Width = 283
            Height = 88
            Caption = #20659#36664#27169#32068#36890#35338#28204#35430
            TabOrder = 1
            object Label71: TLabel
              Left = 8
              Top = 32
              Width = 160
              Height = 12
              AutoSize = False
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -12
              Font.Name = #26032#32048#26126#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object LB_DongleTest: TLabel
              Left = 9
              Top = 57
              Width = 265
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Caption = #23578#26410#28204#35430
              Color = clYellow
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -21
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Memo1: TMemo
              Left = 9
              Top = 15
              Width = 265
              Height = 37
              Ctl3D = False
              Enabled = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -16
              Font.Name = #27161#26999#39636
              Font.Style = []
              Lines.Strings = (
                #35531#25509#22949#20659#36664#27169#32068#65292#25353#19979#22739#25187#33509#28961
                #21453#25033#20195#34920#30064#24120)
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
            end
          end
          object GroupBox21: TGroupBox
            Left = 6
            Top = 99
            Width = 283
            Height = 106
            Caption = #34880#22739#35336#37327#29986#28204#35430
            TabOrder = 2
            object Label72: TLabel
              Left = 8
              Top = 45
              Width = 63
              Height = 19
              Caption = #25910#32302#22739
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label70: TLabel
              Left = 8
              Top = 72
              Width = 63
              Height = 19
              Caption = #33298#24373#22739
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label73: TLabel
              Left = 143
              Top = 72
              Width = 64
              Height = 19
              Caption = #24515'  '#36339
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Device_BP: TLabel
              Left = 75
              Top = 45
              Width = 60
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clBlue
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Device_SP: TLabel
              Left = 75
              Top = 72
              Width = 60
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clBlue
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Device_HR: TLabel
              Left = 213
              Top = 72
              Width = 60
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clBlue
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
            object Memo2: TMemo
              Left = 9
              Top = 18
              Width = 265
              Height = 22
              Ctl3D = False
              Enabled = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clBlue
              Font.Height = -16
              Font.Name = #27161#26999#39636
              Font.Style = []
              Lines.Strings = (
                #25353#22739#25187#24460#20843#31186#20839#26371#20986#29694#36039#26009#20195#34920#27491#24120)
              ParentCtl3D = False
              ParentFont = False
              TabOrder = 0
            end
          end
          object GroupBox22: TGroupBox
            Left = 6
            Top = 213
            Width = 283
            Height = 52
            Caption = #34880#31958#35336#37327#29986#28204#35430
            TabOrder = 3
            object Label77: TLabel
              Left = 11
              Top = 18
              Width = 64
              Height = 19
              Caption = #34880'  '#31958
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clPurple
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Device_MA: TLabel
              Left = 93
              Top = 18
              Width = 100
              Height = 22
              Alignment = taCenter
              AutoSize = False
              Color = clYellow
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clBlue
              Font.Height = -19
              Font.Name = #27161#26999#39636
              Font.Style = [fsBold]
              ParentColor = False
              ParentFont = False
            end
          end
        end
        object ARoundDevice: TTabSheet
          Caption = #36913#37002#35037#32622
          ImageIndex = 1
          object Label59: TLabel
            Left = 3
            Top = 6
            Width = 139
            Height = 12
            AutoSize = False
            Caption = #20027#27231#36865#32102#35037#32622#36039#26009
          end
          object Button11: TButton
            Left = 234
            Top = 3
            Width = 55
            Height = 19
            Caption = #28165#38500
            TabOrder = 0
            OnClick = Button11Click
          end
          object D2M: TRichEdit
            Left = 0
            Top = 27
            Width = 293
            Height = 293
            BevelInner = bvNone
            BevelOuter = bvNone
            Ctl3D = False
            Font.Charset = CHINESEBIG5_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = '@Fixedsys'
            Font.Style = []
            ParentCtl3D = False
            ParentFont = False
            ScrollBars = ssVertical
            TabOrder = 1
          end
        end
        object QueueTest: TTabSheet
          Caption = #31561#24453#20295#21015
          ImageIndex = 2
          object QueueSize_LB: TLabel
            Left = 174
            Top = 27
            Width = 49
            Height = 29
            AutoSize = False
            Color = clYellow
            Font.Charset = ANSI_CHARSET
            Font.Color = clNavy
            Font.Height = -21
            Font.Name = 'Comic Sans MS'
            Font.Style = [fsBold]
            ParentColor = False
            ParentFont = False
          end
          object Label68: TLabel
            Left = 3
            Top = 27
            Width = 163
            Height = 30
            Caption = #30446#21069'Queue Size'
            Font.Charset = ANSI_CHARSET
            Font.Color = clNavy
            Font.Height = -21
            Font.Name = 'Comic Sans MS'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object QueueMemo: TMemo
            Left = 6
            Top = 264
            Width = 283
            Height = 25
            Color = clBlack
            Ctl3D = False
            Font.Charset = ANSI_CHARSET
            Font.Color = clLime
            Font.Height = -13
            Font.Name = 'Comic Sans MS'
            Font.Style = [fsBold]
            ParentCtl3D = False
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
            WantReturns = False
            WordWrap = False
          end
          object Button12: TButton
            Left = 102
            Top = 291
            Width = 94
            Height = 25
            Caption = #23559'Queue'#22622#28415
            TabOrder = 0
            OnClick = Button12Click
          end
          object BT_CleanQueue: TButton
            Left = 201
            Top = 291
            Width = 88
            Height = 25
            Caption = #23559'Queue'#28165#31354
            TabOrder = 1
            OnClick = BT_CleanQueueClick
          end
          object BT_GetQueue: TButton
            Left = 3
            Top = 291
            Width = 94
            Height = 25
            Caption = #21462#24471'Queue'#20839#23481
            TabOrder = 2
            OnClick = BT_GetQueueClick
          end
          object PageControl4: TPageControl
            Left = 3
            Top = 57
            Width = 289
            Height = 205
            ActivePage = TabSheet9
            TabOrder = 4
            object TabSheet9: TTabSheet
              Caption = #21407#22987#36039#26009
              object QueueList: TStringGrid
                Left = 3
                Top = 6
                Width = 278
                Height = 169
                ColCount = 2
                Ctl3D = False
                DefaultRowHeight = 16
                FixedCols = 0
                RowCount = 17
                Font.Charset = CHINESEBIG5_CHARSET
                Font.Color = clWindowText
                Font.Height = -16
                Font.Name = '@Fixedsys'
                Font.Style = []
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goRowSelect]
                ParentCtl3D = False
                ParentFont = False
                ScrollBars = ssVertical
                TabOrder = 0
                ColWidths = (
                  41
                  252)
              end
            end
            object TabSheet10: TTabSheet
              Caption = #35299#30908#36039#26009
              ImageIndex = 1
            end
          end
          object DebugCheck: TCheckBox
            Left = 6
            Top = 3
            Width = 271
            Height = 22
            Caption = #21855#29992'DEBUG'#27169#24335#12304'FW3.3'#20197#19978#29256#26412#25165#21487#20351#29992#12305
            TabOrder = 5
          end
          object Button13: TButton
            Left = 231
            Top = 30
            Width = 58
            Height = 25
            Caption = #26356#26032#31558#25976
            TabOrder = 6
            OnClick = Button13Click
          end
        end
        object K332TEST: TTabSheet
          Caption = 'K332'#26495
          ImageIndex = 4
          object GroupBox23: TGroupBox
            Left = 6
            Top = 6
            Width = 280
            Height = 277
            Caption = 'K332 EEPROM DUMP'
            TabOrder = 0
            object K332ROM: TRichEdit
              Left = 6
              Top = 21
              Width = 262
              Height = 244
              BevelInner = bvNone
              BevelOuter = bvNone
              Color = clBlack
              Ctl3D = False
              Font.Charset = CHINESEBIG5_CHARSET
              Font.Color = clYellow
              Font.Height = -11
              Font.Name = '@Fixedsys'
              Font.Style = []
              ParentCtl3D = False
              ParentFont = False
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
        end
      end
    end
    object ReportControl: TTabSheet
      Caption = #20659#36664#22238#22577
      ImageIndex = 2
      object Label56: TLabel
        Left = 6
        Top = 246
        Width = 60
        Height = 12
        Caption = #20659#36865#38651#35441#65306
      end
      object Label57: TLabel
        Left = 3
        Top = 66
        Width = 60
        Height = 12
        Caption = #31777#35338#20839#23481#65306
      end
      object Label58: TLabel
        Left = 3
        Top = 162
        Width = 60
        Height = 12
        Caption = #31777#35338#20839#23481#65306
      end
      object Label69: TLabel
        Left = 3
        Top = 27
        Width = 79
        Height = 12
        Caption = 'CTI'#20027#27231#21517#31281#65306
      end
      object Tel: TEdit
        Left = 72
        Top = 243
        Width = 223
        Height = 18
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 0
        Text = '0917768975,0935194075,0929596483'
      end
      object SuccMSGEn: TCheckBox
        Left = 3
        Top = 48
        Width = 178
        Height = 17
        Caption = #38283#21855#20659#36664#25104#21151#31777#35338#22238#22577#21151#33021
        TabOrder = 1
      end
      object SUCCMSG: TMemo
        Left = 3
        Top = 81
        Width = 292
        Height = 55
        Ctl3D = False
        Lines.Strings = (
          '%s'#65306'%s'#23429#31471#27231#20659#36664#25104#21151#22238#22577#65292#30446#21069'CTI'#27794#21839#38988)
        ParentCtl3D = False
        TabOrder = 2
      end
      object FailMSGEn: TCheckBox
        Left = 3
        Top = 141
        Width = 178
        Height = 17
        Caption = #38283#21855#20659#36664#22833#25943#31777#35338#22238#22577#21151#33021
        TabOrder = 3
      end
      object FAILMSG: TMemo
        Left = 3
        Top = 177
        Width = 292
        Height = 55
        Ctl3D = False
        Lines.Strings = (
          '%s'#65306'%s'#23429#31471#27231#20659#36664#22833#25943#22238#22577#65292#35531#20760#36895#27298#26597#21407#22240)
        ParentCtl3D = False
        TabOrder = 4
      end
      object WEB: TWebBrowser
        Left = 6
        Top = 270
        Width = 289
        Height = 48
        TabOrder = 5
        ControlData = {
          4C000000DE1D0000F60400000000000000000000000000000000000000000000
          000000004C000000000000000000000001000000E0D057007335CF11AE690800
          2B2E126208000000000000004C0000000114020000000000C000000000000046
          8000000000000000000000000000000000000000000000000000000000000000
          00000000000000000100000000000000000000000000000000000000}
      end
      object Button9: TButton
        Left = 117
        Top = 324
        Width = 58
        Height = 22
        Caption = 'TEST'
        TabOrder = 6
        OnClick = Button9Click
      end
      object CTINAME: TEdit
        Left = 90
        Top = 24
        Width = 106
        Height = 18
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 7
        Text = #38272#35582#37291#38498
      end
      object Button15: TButton
        Left = 207
        Top = 18
        Width = 91
        Height = 25
        Caption = #25163#21205#24375#21046#22238#22577
        TabOrder = 8
        OnClick = Button15Click
      end
      object AutoSMS: TCheckBox
        Left = 3
        Top = 3
        Width = 175
        Height = 17
        Caption = #21855#21205#33258#21205#23433#24515#31777#35338
        Checked = True
        State = cbChecked
        TabOrder = 9
      end
    end
    object LogTab: TTabSheet
      Caption = 'LOG'
      ImageIndex = 3
      object DataLog: TMemo
        Left = 0
        Top = 0
        Width = 301
        Height = 305
        Align = alClient
        Ctl3D = False
        ParentCtl3D = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel3: TPanel
        Left = 0
        Top = 305
        Width = 301
        Height = 41
        Align = alBottom
        Caption = 'Panel3'
        TabOrder = 1
        object Button10: TButton
          Left = 3
          Top = 7
          Width = 289
          Height = 25
          Caption = #28165#38500#36039#26009
          TabOrder = 0
          OnClick = Button10Click
        end
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 376
    Width = 473
    Height = 21
    Align = alBottom
    BevelOuter = bvNone
    Caption = 'Panel4'
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
    object StatusBar1: TStatusBar
      Left = 0
      Top = 0
      Width = 337
      Height = 21
      Align = alLeft
      Font.Charset = CHINESEBIG5_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = #24494#36575#27491#40657#39636
      Font.Style = [fsBold]
      Panels = <>
      SimplePanel = True
      UseSystemFont = False
    end
    object DonVer: TStatusBar
      Left = 337
      Top = 0
      Width = 136
      Height = 21
      Align = alClient
      Font.Charset = CHINESEBIG5_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36575#27491#40657#39636
      Font.Style = [fsBold]
      Panels = <>
      SimplePanel = True
      UseSystemFont = False
    end
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 137
    Top = 315
  end
  object INISAVE: TSaveDialog
    Ctl3D = False
    DefaultExt = 'ini'
    FileName = 'C:\Documents and Settings\Administrator\'#26700#38754'\A002PC'#31471'\Config.ini'
    Filter = '*.ini|*.ini'
    Left = 222
    Top = 369
  end
  object INIOPEN: TOpenDialog
    Ctl3D = False
    FileName = 'C:\Documents and Settings\Administrator\'#26700#38754'\A002PC'#31471'\Config.ini'
    Filter = '*.ini|*.ini'
    Left = 252
    Top = 369
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
    Left = 192
    Top = 369
  end
  object Timer2: TTimer
    Interval = 100
    OnTimer = Timer2Timer
    Left = 138
    Top = 339
  end
  object Timer3: TTimer
    Interval = 100
    OnTimer = Timer3Timer
    Left = 137
    Top = 360
  end
  object DeviceTestTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = DeviceTestTimerTimer
    Left = 283
    Top = 370
  end
end
