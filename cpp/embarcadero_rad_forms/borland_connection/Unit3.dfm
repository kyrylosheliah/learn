object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1050#1072#1088#1090#1086#1095#1082#1072
  ClientHeight = 285
  ClientWidth = 477
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 11
    Width = 87
    Height = 13
    Caption = #1053#1086#1084#1077#1088' '#1082#1072#1090#1077#1075#1086#1088#1080#1080
  end
  object Label2: TLabel
    Left = 8
    Top = 38
    Width = 54
    Height = 13
    Caption = #1050#1072#1090#1077#1075#1086#1088#1080#1103
  end
  object Label3: TLabel
    Left = 8
    Top = 64
    Width = 48
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077
  end
  object Label4: TLabel
    Left = 8
    Top = 92
    Width = 93
    Height = 13
    Caption = #1053#1072#1091#1095#1085#1086#1077' '#1085#1072#1079#1074#1072#1085#1080#1077
  end
  object Label5: TLabel
    Left = 8
    Top = 120
    Width = 109
    Height = 13
    Caption = #1044#1083#1080#1085#1072' '#1074' '#1089#1072#1085#1090#1080#1084#1077#1090#1088#1072#1093
  end
  object Label6: TLabel
    Left = 8
    Top = 148
    Width = 84
    Height = 13
    Caption = #1044#1083#1080#1085#1072' '#1074' '#1076#1102#1081#1084#1072#1093
  end
  object Label7: TLabel
    Left = 8
    Top = 173
    Width = 61
    Height = 13
    Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
  end
  object DBEdit1: TDBEdit
    Left = 118
    Top = 7
    Width = 161
    Height = 21
    DataField = 'Species No'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 0
  end
  object DBEdit2: TDBEdit
    Left = 118
    Top = 34
    Width = 161
    Height = 21
    DataField = 'Category'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 1
  end
  object DBEdit3: TDBEdit
    Left = 118
    Top = 61
    Width = 161
    Height = 21
    DataField = 'Common_Name'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 2
  end
  object DBEdit4: TDBEdit
    Left = 118
    Top = 88
    Width = 161
    Height = 21
    DataField = 'Species Name'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 3
  end
  object DBEdit5: TDBEdit
    Left = 118
    Top = 115
    Width = 161
    Height = 21
    DataField = 'Length (cm)'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 4
  end
  object DBEdit6: TDBEdit
    Left = 118
    Top = 142
    Width = 161
    Height = 21
    DataField = 'Length_In'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 5
  end
  object DBMemo1: TDBMemo
    Left = 118
    Top = 169
    Width = 351
    Height = 110
    DataField = 'Notes'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 6
  end
  object DBImage1: TDBImage
    Left = 285
    Top = 7
    Width = 184
    Height = 156
    DataField = 'Graphic'
    DataSource = DataModule2.DataSource1
    ReadOnly = True
    TabOrder = 7
  end
end
