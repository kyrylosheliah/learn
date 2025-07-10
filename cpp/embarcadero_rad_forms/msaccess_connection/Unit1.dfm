object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1054#1090#1076#1077#1083' '#1082#1072#1076#1088#1086#1074
  ClientHeight = 535
  ClientWidth = 393
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 318
    Width = 393
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 321
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 393
    Height = 105
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 17
      Top = 15
      Width = 51
      Height = 13
      Caption = #1044#1086#1087'. '#1080#1085#1092'.'
    end
    object Label2: TLabel
      Left = 128
      Top = 15
      Width = 92
      Height = 13
      Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1092#1072#1084#1080#1083#1080#1080
    end
    object RadioButton1: TRadioButton
      Left = 17
      Top = 34
      Width = 81
      Height = 17
      Caption = #1040#1076#1088#1077#1089
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 17
      Top = 57
      Width = 81
      Height = 17
      Caption = #1058#1077#1083#1077#1092#1086#1085#1099
      TabOrder = 1
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 17
      Top = 80
      Width = 81
      Height = 17
      Caption = #1044#1086#1083#1078#1085#1086#1089#1090#1100
      TabOrder = 2
      OnClick = RadioButton3Click
    end
    object Button1: TButton
      Left = 128
      Top = 74
      Width = 75
      Height = 25
      Caption = #1053#1072#1081#1090#1080
      TabOrder = 3
    end
    object Button2: TButton
      Left = 256
      Top = 74
      Width = 121
      Height = 25
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
      TabOrder = 4
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 256
      Top = 43
      Width = 121
      Height = 25
      Caption = #1053#1086#1074#1099#1081' '#1089#1086#1090#1088#1091#1076#1085#1080#1082
      TabOrder = 5
      OnClick = Button3Click
    end
    object Edit1: TEdit
      Left = 128
      Top = 34
      Width = 92
      Height = 21
      TabOrder = 6
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 105
    Width = 393
    Height = 213
    Align = alClient
    TabOrder = 1
    object DBGrid1: TDBGrid
      Left = 1
      Top = 1
      Width = 391
      Height = 211
      Align = alClient
      DataSource = DataModule2.DataSource1
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 321
    Width = 393
    Height = 214
    Align = alBottom
    TabOrder = 2
    object DBGrid2: TDBGrid
      Left = 1
      Top = 1
      Width = 391
      Height = 212
      Align = alClient
      DataSource = DataModule2.DataSource2
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
    end
  end
end
