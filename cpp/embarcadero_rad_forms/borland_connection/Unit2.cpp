//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TDataModule2 *DataModule2;
//---------------------------------------------------------------------------
__fastcall TDataModule2::TDataModule2(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDataModule2::DataSource1DataChange(TObject *Sender, TField *Field)

{
	Form1->Panel1->Caption = "Позиция: " + IntToStr(Table1->RecNo) + " из " + IntToStr(Table1->RecordCount);
}
//---------------------------------------------------------------------------
