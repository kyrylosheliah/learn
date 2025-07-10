object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1041#1044' '#1053#1072#1074#1080#1075#1072#1090#1086#1088
  ClientHeight = 518
  ClientWidth = 461
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    461
    518)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 54
    Height = 13
    Caption = #1053#1072#1074#1080#1075#1072#1094#1080#1103
  end
  object Label2: TLabel
    Left = 8
    Top = 70
    Width = 49
    Height = 13
    Caption = #1047#1072#1082#1083#1072#1076#1082#1072
  end
  object Button1: TButton
    Left = 68
    Top = 3
    Width = 75
    Height = 25
    Caption = '|< '#1053#1072#1095#1072#1083#1086
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 68
    Top = 34
    Width = 75
    Height = 25
    Caption = '<< '#1053#1072#1079#1072#1076
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 149
    Top = 34
    Width = 75
    Height = 25
    Caption = '>> '#1042#1087#1077#1088#1077#1076
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 149
    Top = 3
    Width = 75
    Height = 25
    Caption = #1050#1086#1085#1077#1094' >|'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Panel1: TPanel
    Left = 8
    Top = 96
    Width = 443
    Height = 48
    Anchors = [akLeft, akTop, akRight]
    Caption = #1055#1086#1079#1080#1094#1080#1103
    TabOrder = 4
    ExplicitWidth = 435
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 150
    Width = 443
    Height = 360
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
  end
  object Button5: TButton
    Left = 68
    Top = 65
    Width = 75
    Height = 25
    Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100
    TabOrder = 6
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 149
    Top = 65
    Width = 75
    Height = 25
    Caption = #1053#1072' '#1079#1072#1082#1083#1072#1076#1082#1091
    Enabled = False
    TabOrder = 7
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 230
    Top = 65
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    Enabled = False
    TabOrder = 8
    OnClick = Button7Click
  end
end
