object PAddForm: TPAddForm
  Left = 223
  Top = 428
  Width = 705
  Height = 561
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1072#1076#1088#1077#1089#1072' '#1080' '#1087#1088#1077#1079#1077#1085#1090#1072#1094#1080#1080
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 16
    Top = 373
    Width = 163
    Height = 13
    Caption = #1044#1072#1090#1072' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1087#1088#1077#1079#1077#1085#1090#1072#1094#1080#1080' :'
    Visible = False
  end
  object SpeedButton1: TSpeedButton
    Left = 384
    Top = 56
    Width = 97
    Height = 23
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1092#1072#1081#1083
    Flat = True
    OnClick = SpeedButton1Click
  end
  object Label1: TLabel
    Left = 16
    Top = 20
    Width = 37
    Height = 13
    Caption = #1040#1076#1088#1077#1089' :'
  end
  object Label2: TLabel
    Left = 16
    Top = 56
    Width = 88
    Height = 13
    Caption = #1055#1083#1086#1097#1072#1076#1100' '#1074' '#1082#1074'.'#1084' :'
  end
  object Label4: TLabel
    Left = 16
    Top = 252
    Width = 37
    Height = 13
    Caption = #1056#1072#1081#1086#1085' :'
  end
  object Label5: TLabel
    Left = 16
    Top = 292
    Width = 82
    Height = 13
    Caption = #1057#1090#1072#1085#1094#1080#1103' '#1084#1077#1090#1088#1086' :'
  end
  object Label6: TLabel
    Left = 16
    Top = 332
    Width = 134
    Height = 13
    Caption = #1044#1072#1090#1072' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1072#1076#1088#1077#1089#1072' :'
  end
  object Label7: TLabel
    Left = 304
    Top = 61
    Width = 73
    Height = 13
    Caption = #1055#1088#1077#1079#1077#1085#1090#1072#1094#1080#1103' :'
  end
  object Image1: TImage
    Left = 304
    Top = 96
    Width = 369
    Height = 409
    Center = True
    Proportional = True
  end
  object SpeedButton2: TSpeedButton
    Left = 152
    Top = 80
    Width = 113
    Height = 23
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074' '#1089#1087#1080#1089#1086#1082
    Flat = True
    OnClick = SpeedButton2Click
  end
  object SpeedButton3: TSpeedButton
    Left = 152
    Top = 136
    Width = 113
    Height = 23
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1080#1079' '#1089#1087#1080#1089#1082#1072
    Flat = True
    OnClick = SpeedButton3Click
  end
  object SpeedButton4: TSpeedButton
    Left = 152
    Top = 176
    Width = 113
    Height = 23
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1087#1080#1089#1086#1082
    Flat = True
    OnClick = SpeedButton4Click
  end
  object SpeedButton5: TSpeedButton
    Left = 496
    Top = 56
    Width = 97
    Height = 23
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1092#1072#1081#1083
    Flat = True
    Visible = False
    OnClick = SpeedButton5Click
  end
  object DateTimePicker1: TDateTimePicker
    Left = 160
    Top = 328
    Width = 90
    Height = 21
    CalAlignment = dtaLeft
    Date = 41760
    Time = 41760
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
  end
  object Button1: TButton
    Left = 64
    Top = 472
    Width = 75
    Height = 25
    Caption = #1054#1082
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 152
    Top = 472
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 2
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 64
    Top = 16
    Width = 380
    Height = 21
    TabOrder = 3
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 16
    Top = 80
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object Edit3: TEdit
    Left = 64
    Top = 248
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object Edit4: TEdit
    Left = 112
    Top = 288
    Width = 160
    Height = 21
    TabOrder = 6
  end
  object DateTimePicker2: TDateTimePicker
    Left = 184
    Top = 368
    Width = 90
    Height = 21
    CalAlignment = dtaLeft
    Date = 41760
    Time = 41760
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 7
    Visible = False
  end
  object ListBox1: TListBox
    Left = 16
    Top = 112
    Width = 121
    Height = 113
    ItemHeight = 13
    TabOrder = 8
  end
end
