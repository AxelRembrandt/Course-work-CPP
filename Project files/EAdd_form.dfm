object EAddForm: TEAddForm
  Left = 238
  Top = 421
  Width = 417
  Height = 608
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1085#1086#1074#1086#1081' '#1079#1072#1087#1080#1089#1080
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
  object Label1: TLabel
    Left = 16
    Top = 20
    Width = 34
    Height = 13
    Caption = 'E-mail :'
  end
  object Label2: TLabel
    Left = 16
    Top = 60
    Width = 42
    Height = 13
    Caption = #1060'.'#1048'.'#1054'. :'
  end
  object Label3: TLabel
    Left = 16
    Top = 100
    Width = 57
    Height = 13
    Caption = #1050#1086#1084#1087#1072#1085#1080#1103' :'
  end
  object Label4: TLabel
    Left = 16
    Top = 220
    Width = 95
    Height = 13
    Caption = #1044#1072#1090#1072' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' :'
  end
  object Label5: TLabel
    Left = 16
    Top = 256
    Width = 68
    Height = 13
    Caption = #1050#1086#1084#1077#1085#1090#1072#1088#1080#1081' :'
  end
  object Label6: TLabel
    Left = 16
    Top = 140
    Width = 112
    Height = 13
    Caption = #1057#1092#1077#1088#1072' '#1076#1077#1103#1090#1077#1083#1100#1085#1086#1089#1090#1080' :'
  end
  object Label7: TLabel
    Left = 16
    Top = 180
    Width = 51
    Height = 13
    Caption = #1058#1077#1083#1077#1092#1086#1085' :'
  end
  object Edit1: TEdit
    Left = 64
    Top = 16
    Width = 180
    Height = 21
    TabOrder = 0
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 64
    Top = 56
    Width = 320
    Height = 21
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 80
    Top = 96
    Width = 150
    Height = 21
    TabOrder = 2
  end
  object Memo1: TMemo
    Left = 16
    Top = 280
    Width = 369
    Height = 225
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object Button2: TButton
    Left = 208
    Top = 528
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 4
    OnClick = Button2Click
  end
  object DateTimePicker1: TDateTimePicker
    Left = 128
    Top = 216
    Width = 121
    Height = 21
    CalAlignment = dtaLeft
    Date = 41760
    Time = 41760
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 5
  end
  object Button1: TButton
    Left = 120
    Top = 528
    Width = 75
    Height = 25
    Caption = #1054#1082
    TabOrder = 6
    OnClick = Button1Click
  end
  object Edit4: TEdit
    Left = 136
    Top = 136
    Width = 150
    Height = 21
    TabOrder = 7
  end
  object Edit5: TEdit
    Left = 80
    Top = 176
    Width = 150
    Height = 21
    TabOrder = 8
  end
end
