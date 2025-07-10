object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
  ClientHeight = 540
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 265
    Height = 289
    Caption = #1051#1080#1095#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
    TabOrder = 0
    OnExit = GroupBox1Exit
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 44
      Height = 13
      Caption = #1060#1072#1084#1072#1083#1080#1103
    end
    object Label2: TLabel
      Left = 16
      Top = 50
      Width = 19
      Height = 13
      Caption = #1048#1084#1103
    end
    object Label3: TLabel
      Left = 16
      Top = 78
      Width = 49
      Height = 13
      Caption = #1054#1090#1095#1077#1089#1090#1074#1086
    end
    object Label4: TLabel
      Left = 16
      Top = 106
      Width = 19
      Height = 13
      Caption = #1055#1086#1083
    end
    object Label5: TLabel
      Left = 16
      Top = 132
      Width = 80
      Height = 13
      Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103
    end
    object Label6: TLabel
      Left = 16
      Top = 159
      Width = 94
      Height = 13
      Caption = #1044#1072#1090#1072' '#1087#1086#1089#1090#1091#1087#1083#1077#1085#1080#1103
    end
    object Label7: TLabel
      Left = 16
      Top = 186
      Width = 69
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1076#1077#1090#1077#1081
    end
    object Label8: TLabel
      Left = 16
      Top = 213
      Width = 92
      Height = 13
      Caption = #1057#1090#1072#1076' '#1088#1072#1073#1086#1090#1099', '#1083#1077#1090
    end
    object Label9: TLabel
      Left = 16
      Top = 240
      Width = 67
      Height = 13
      Caption = #1054#1073#1088#1072#1079#1086#1074#1072#1085#1080#1077
    end
    object DBCheckBox1: TDBCheckBox
      Left = 20
      Top = 264
      Width = 97
      Height = 17
      Caption = #1046#1077#1085#1072#1090'/'#1047#1072#1084#1091#1078#1077#1084
      DataField = #1057#1077#1084'_'#1055#1086#1083#1086#1078
      DataSource = DataModule2.DataSource1
      TabOrder = 0
    end
    object DBCheckBox2: TDBCheckBox
      Left = 128
      Top = 264
      Width = 116
      Height = 17
      Caption = #1042#1086#1077#1085#1085#1086#1086#1073#1103#1079#1072#1085#1085#1099#1081
      DataField = #1042#1086#1077#1085#1085#1086#1086#1073#1103#1079#1072#1085#1085#1099#1081
      DataSource = DataModule2.DataSource1
      TabOrder = 1
    end
    object DBEdit1: TDBEdit
      Left = 128
      Top = 21
      Width = 121
      Height = 21
      DataField = #1060#1072#1084#1080#1083#1080#1103
      DataSource = DataModule2.DataSource1
      TabOrder = 2
    end
    object DBEdit2: TDBEdit
      Left = 128
      Top = 48
      Width = 121
      Height = 21
      DataField = #1048#1084#1103
      DataSource = DataModule2.DataSource1
      TabOrder = 3
    end
    object DBEdit3: TDBEdit
      Left = 128
      Top = 75
      Width = 121
      Height = 21
      DataField = #1054#1090#1095#1077#1089#1090#1074#1086
      DataSource = DataModule2.DataSource1
      TabOrder = 4
    end
    object DBComboBox1: TDBComboBox
      Left = 128
      Top = 102
      Width = 121
      Height = 21
      DataField = #1055#1086#1083
      DataSource = DataModule2.DataSource1
      Items.Strings = (
        #1084#1091#1078
        #1078#1077#1085)
      TabOrder = 5
    end
    object DBEdit4: TDBEdit
      Left = 128
      Top = 129
      Width = 117
      Height = 21
      DataField = #1044#1072#1090#1072'_'#1056#1086#1078#1076
      DataSource = DataModule2.DataSource1
      MaxLength = 11
      TabOrder = 6
    end
    object DBEdit5: TDBEdit
      Left = 128
      Top = 156
      Width = 117
      Height = 21
      DataField = #1044#1072#1090#1072'_'#1055#1086#1089#1090
      DataSource = DataModule2.DataSource1
      MaxLength = 11
      TabOrder = 7
    end
    object DBEdit6: TDBEdit
      Left = 128
      Top = 183
      Width = 121
      Height = 21
      DataField = #1044#1077#1090#1077#1081
      DataSource = DataModule2.DataSource1
      TabOrder = 8
    end
    object DBEdit7: TDBEdit
      Left = 128
      Top = 210
      Width = 121
      Height = 21
      DataField = #1057#1090#1072#1078
      DataSource = DataModule2.DataSource1
      TabOrder = 9
    end
    object DBEdit8: TDBEdit
      Left = 128
      Top = 237
      Width = 121
      Height = 21
      DataField = #1054#1073#1088#1072#1079#1086#1074#1072#1085#1080#1077
      DataSource = DataModule2.DataSource1
      TabOrder = 10
    end
  end
  object GroupBox2: TGroupBox
    Left = 279
    Top = 8
    Width = 202
    Height = 82
    Caption = #1044#1086#1083#1078#1085#1086#1089#1090#1100
    TabOrder = 1
    OnExit = GroupBox2Exit
    object Label10: TLabel
      Left = 11
      Top = 25
      Width = 33
      Height = 13
      Caption = #1054#1090#1076#1077#1083
    end
    object Label11: TLabel
      Left = 11
      Top = 51
      Width = 57
      Height = 13
      Caption = #1044#1086#1083#1078#1085#1086#1089#1090#1100
    end
    object DBEdit9: TDBEdit
      Left = 78
      Top = 20
      Width = 121
      Height = 21
      DataField = #1054#1090#1076#1077#1083
      DataSource = DataModule2.DataSource4
      TabOrder = 0
    end
    object DBEdit10: TDBEdit
      Left = 78
      Top = 47
      Width = 121
      Height = 21
      DataField = #1044#1086#1083#1078#1085#1086#1089#1090#1100
      DataSource = DataModule2.DataSource4
      TabOrder = 1
    end
  end
  object GroupBox3: TGroupBox
    Left = 279
    Top = 136
    Width = 202
    Height = 113
    Caption = #1044#1086#1084#1072#1096#1085#1080#1081' '#1072#1076#1088#1077#1089
    TabOrder = 2
    OnExit = GroupBox3Exit
    object Label12: TLabel
      Left = 18
      Top = 30
      Width = 37
      Height = 13
      Caption = #1057#1090#1088#1072#1085#1072
    end
    object Label13: TLabel
      Left = 18
      Top = 68
      Width = 31
      Height = 13
      Caption = #1040#1076#1088#1077#1089
    end
    object Label14: TLabel
      Left = 18
      Top = 49
      Width = 31
      Height = 13
      Caption = #1043#1086#1088#1086#1076
    end
    object DBEdit11: TDBEdit
      Left = 78
      Top = 29
      Width = 121
      Height = 21
      DataField = #1057#1090#1088#1072#1085#1072
      DataSource = DataModule2.DataSource2
      TabOrder = 0
    end
    object DBEdit12: TDBEdit
      Left = 78
      Top = 56
      Width = 121
      Height = 21
      DataField = #1043#1086#1088#1086#1076
      DataSource = DataModule2.DataSource2
      TabOrder = 1
    end
    object DBEdit13: TDBEdit
      Left = 78
      Top = 83
      Width = 121
      Height = 21
      DataField = #1044#1086#1084'_'#1040#1076#1088#1077#1089
      DataSource = DataModule2.DataSource2
      TabOrder = 2
    end
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 303
    Width = 473
    Height = 202
    Caption = #1058#1077#1083#1077#1092#1086#1085#1099
    TabOrder = 3
    OnExit = GroupBox4Exit
    object Label15: TLabel
      Left = 16
      Top = 24
      Width = 44
      Height = 13
      Caption = #1058#1077#1083#1077#1092#1086#1085
    end
    object Label16: TLabel
      Left = 198
      Top = 24
      Width = 61
      Height = 13
      Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
    end
    object Button1: TButton
      Left = 392
      Top = 16
      Width = 75
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 0
      OnClick = Button1Click
    end
    object DBEdit14: TDBEdit
      Left = 71
      Top = 16
      Width = 117
      Height = 21
      DataField = #1058#1077#1083#1077#1092#1086#1085
      DataSource = DataModule2.DataSource3
      MaxLength = 17
      TabOrder = 1
    end
    object DBComboBox2: TDBComboBox
      Left = 265
      Top = 19
      Width = 121
      Height = 21
      DataField = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
      DataSource = DataModule2.DataSource3
      Items.Strings = (
        #1056#1072#1073#1086#1095#1080#1081
        #1044#1086#1084#1072#1096#1085#1080#1081
        #1052#1086#1073#1080#1083#1100#1085#1099#1081)
      TabOrder = 2
    end
    object DBGrid1: TDBGrid
      Left = 3
      Top = 46
      Width = 467
      Height = 153
      DataSource = DataModule2.DataSource3
      TabOrder = 3
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
    end
  end
  object DBNavigator1: TDBNavigator
    Left = 278
    Top = 511
    Width = 204
    Height = 25
    DataSource = DataModule2.DataSource1
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
    TabOrder = 4
  end
  object Button2: TButton
    Left = 8
    Top = 511
    Width = 129
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080' '#1074#1099#1081#1090#1080
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 143
    Top = 511
    Width = 129
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1086#1090#1088#1091#1076#1085#1080#1082#1072
    TabOrder = 6
    OnClick = Button3Click
  end
end
