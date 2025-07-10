object DataModule2: TDataModule2
  OldCreateOrder = False
  Height = 431
  Width = 468
  object Table1: TTable
    DatabaseName = 'MYDB1'
    TableName = 'biolife.db'
    Left = 120
    Top = 16
  end
  object DataSource1: TDataSource
    DataSet = Table1
    OnDataChange = DataSource1DataChange
    Left = 64
    Top = 16
  end
end
