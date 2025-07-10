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
	TAutoIncField *ADOTable1����;
	TWideStringField *ADOTable1�������;
	TWideStringField *ADOTable1���;
	TWideStringField *ADOTable1��������;
	TWideStringField *ADOTable1���;
	TBooleanField *ADOTable1���_�����;
	TWordField *ADOTable1�����;
	TDateTimeField *ADOTable1����_����;
	TDateTimeField *ADOTable1����_����;
	TWordField *ADOTable1����;
	TWideMemoField *ADOTable1�����������;
	TBooleanField *ADOTable1���������������;
	TIntegerField *ADOTable2���������;
	TWideStringField *ADOTable2������;
	TWideStringField *ADOTable2�����;
	TWideStringField *ADOTable2���_�����;
	TIntegerField *ADOTable3���������;
	TWideStringField *ADOTable3�������;
	TWideStringField *ADOTable3����������;
	TIntegerField *ADOTable4���������;
	TWideStringField *ADOTable4�����;
	TWideStringField *ADOTable4���������;

private: // User declarations
		public : // User declarations

	__fastcall TDataModule2(TComponent* Owner);

};

// ---------------------------------------------------------------------------
extern PACKAGE TDataModule2 *DataModule2;
// ---------------------------------------------------------------------------
#endif
