// ---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>

// ---------------------------------------------------------------------------
class TDataModule2 : public TDataModule {
__published: // IDE-managed Components

	TADOConnection *ADOConnection1;
	TADOTable *ADOTable1;
	TADOTable *ADOTable2;
	TADOTable *ADOTable3;
	TADOTable *ADOTable4;
	TDataSource *DataSource1;
	TDataSource *DataSource2;
	TDataSource *DataSource3;
	TDataSource *DataSource4;
	TAutoIncField *ADOTable1Ключ;
	TWideStringField *ADOTable1Фамилия;
	TWideStringField *ADOTable1Имя;
	TWideStringField *ADOTable1Отчество;
	TWideStringField *ADOTable1Пол;
	TBooleanField *ADOTable1Сем_Полож;
	TWordField *ADOTable1Детей;
	TDateTimeField *ADOTable1Дата_Рожд;
	TDateTimeField *ADOTable1Дата_Пост;
	TWordField *ADOTable1Стаж;
	TWideMemoField *ADOTable1Образование;
	TBooleanField *ADOTable1Военнообязанный;
	TIntegerField *ADOTable2Сотрудник;
	TWideStringField *ADOTable2Страна;
	TWideStringField *ADOTable2Город;
	TWideStringField *ADOTable2Дом_Адрес;
	TIntegerField *ADOTable3Сотрудник;
	TWideStringField *ADOTable3Телефон;
	TWideStringField *ADOTable3Примечание;
	TIntegerField *ADOTable4Сотрудник;
	TWideStringField *ADOTable4Отдел;
	TWideStringField *ADOTable4Должность;

private: // User declarations
		public : // User declarations

	__fastcall TDataModule2(TComponent* Owner);

};

// ---------------------------------------------------------------------------
extern PACKAGE TDataModule2 *DataModule2;
// ---------------------------------------------------------------------------
#endif
