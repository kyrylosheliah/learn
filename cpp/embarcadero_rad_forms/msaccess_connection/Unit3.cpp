//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::GroupBox1Exit(TObject *Sender)
{
	if (DataModule2->ADOTable1->Modified)
	{
		DataModule2->ADOTable1->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::GroupBox2Exit(TObject *Sender)
{
	if (DataModule2->ADOTable4->Modified)
	{
		DataModule2->ADOTable4->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::GroupBox3Exit(TObject *Sender)
{
	if (DataModule2->ADOTable2->Modified)
	{
		DataModule2->ADOTable2->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::GroupBox4Exit(TObject *Sender)
{
	if (DataModule2->ADOTable3->Modified)
	{
		DataModule2->ADOTable3->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	if (DataModule2->ADOTable2->Modified)
	{
		DataModule2->ADOTable2->Post();
		DataModule2->ADOTable2->Append();
		DBEdit14->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
	if (DataModule2->ADOTable1->Modified)
	{
		DataModule2->ADOTable1->Post();
	}
	if (DataModule2->ADOTable2->Modified)
	{
		DataModule2->ADOTable2->Post();
	}
	if (DataModule2->ADOTable3->Modified)
	{
		DataModule2->ADOTable3->Post();
	}
	if (DataModule2->ADOTable4->Modified)
	{
		DataModule2->ADOTable4->Post();
	}
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
	DataModule2->ADOTable1->Append();
	DataModule2->ADOTable2->Append();
	DataModule2->ADOTable3->Append();
	DataModule2->ADOTable4->Append();
	DBEdit1->SetFocus();
}
//---------------------------------------------------------------------------

