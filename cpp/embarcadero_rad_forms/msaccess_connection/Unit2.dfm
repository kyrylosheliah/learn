object DataModule2: TDataModule2
  OldCreateOrder = False
  Height = 402
  Width = 367
  object ADOConnection1: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\edu\6 semester\R' +
      'IAS\lab2\lab2.mdb;Persist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 224
    Top = 88
  end
  object ADOTable1: TADOTable
    Active = True
    Connection = ADOConnection1
    CursorType = ctStatic
    TableName = 'LichData'
    Left = 120
    Top = 16
    object ADOTable1Ключ: TAutoIncField
      FieldName = #1050#1083#1102#1095
      ReadOnly = True
      Visible = False
    end
    object ADOTable1Фамилия: TWideStringField
      FieldName = #1060#1072#1084#1080#1083#1080#1103
      Size = 25
    end
    object ADOTable1Имя: TWideStringField
      FieldName = #1048#1084#1103
      Size = 25
    end
    object ADOTable1Отчество: TWideStringField
      FieldName = #1054#1090#1095#1077#1089#1090#1074#1086
      Size = 25
    end
    object ADOTable1Пол: TWideStringField
      FieldName = #1055#1086#1083
      Size = 3
    end
    object ADOTable1Сем_Полож: TBooleanField
      FieldName = #1057#1077#1084'_'#1055#1086#1083#1086#1078
      DisplayValues = #1046#1077#1085#1072#1090';'#1061#1086#1083#1086#1089#1090
    end
    object ADOTable1Детей: TWordField
      FieldName = #1044#1077#1090#1077#1081
    end
    object ADOTable1Дата_Рожд: TDateTimeField
      FieldName = #1044#1072#1090#1072'_'#1056#1086#1078#1076
      EditMask = ' ##.##.####;1;_'
    end
    object ADOTable1Дата_Пост: TDateTimeField
      FieldName = #1044#1072#1090#1072'_'#1055#1086#1089#1090
      EditMask = ' ##.##.####;1;_'
    end
    object ADOTable1Стаж: TWordField
      FieldName = #1057#1090#1072#1078
    end
    object ADOTable1Образование: TWideMemoField
      FieldName = #1054#1073#1088#1072#1079#1086#1074#1072#1085#1080#1077
      BlobType = ftWideMemo
    end
    object ADOTable1Военнообязанный: TBooleanField
      FieldName = #1042#1086#1077#1085#1085#1086#1086#1073#1103#1079#1072#1085#1085#1099#1081
      DisplayValues = #1044#1072';'#1053#1077#1090
    end
  end
  object ADOTable2: TADOTable
    Active = True
    Connection = ADOConnection1
    CursorType = ctStatic
    TableName = 'Adres'
    Left = 120
    Top = 64
    object ADOTable2Сотрудник: TIntegerField
      FieldName = #1057#1086#1090#1088#1091#1076#1085#1080#1082
      Visible = False
    end
    object ADOTable2Страна: TWideStringField
      FieldName = #1057#1090#1088#1072#1085#1072
      Size = 15
    end
    object ADOTable2Город: TWideStringField
      FieldName = #1043#1086#1088#1086#1076
    end
    object ADOTable2Дом_Адрес: TWideStringField
      FieldName = #1044#1086#1084'_'#1040#1076#1088#1077#1089
      Size = 100
    end
  end
  object ADOTable3: TADOTable
    Active = True
    Connection = ADOConnection1
    CursorType = ctStatic
    TableName = 'Telephones'
    Left = 120
    Top = 112
    object ADOTable3Сотрудник: TIntegerField
      FieldName = #1057#1086#1090#1088#1091#1076#1085#1080#1082
      Visible = False
    end
    object ADOTable3Телефон: TWideStringField
      FieldName = #1058#1077#1083#1077#1092#1086#1085
      EditMask = '(##)###-###-##-##;1;_'
      Size = 17
    end
    object ADOTable3Примечание: TWideStringField
      FieldName = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
      Size = 10
    end
  end
  object ADOTable4: TADOTable
    Active = True
    Connection = ADOConnection1
    CursorType = ctStatic
    TableName = 'Doljnost'
    Left = 120
    Top = 160
    object ADOTable4Сотрудник: TIntegerField
      FieldName = #1057#1086#1090#1088#1091#1076#1085#1080#1082
      Visible = False
    end
    object ADOTable4Отдел: TWideStringField
      FieldName = #1054#1090#1076#1077#1083
      Size = 15
    end
    object ADOTable4Должность: TWideStringField
      FieldName = #1044#1086#1083#1078#1085#1086#1089#1090#1100
    end
  end
  object DataSource1: TDataSource
    DataSet = ADOTable1
    Left = 32
    Top = 16
  end
  object DataSource2: TDataSource
    DataSet = ADOTable2
    Left = 32
    Top = 64
  end
  object DataSource3: TDataSource
    DataSet = ADOTable3
    Left = 32
    Top = 112
  end
  object DataSource4: TDataSource
    DataSet = ADOTable4
    Left = 32
    Top = 160
  end
end
