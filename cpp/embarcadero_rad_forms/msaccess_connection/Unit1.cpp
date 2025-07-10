//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    DataModule2->ADOTable1->Append();
	DataModule2->ADOTable2->Append();
	DataModule2->ADOTable3->Append();
	DataModule2->ADOTable4->Append();
    Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
	if (RadioButton1->Checked)
	{
		DBGrid2->DataSource = DataModule2->DataSource2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
	if (RadioButton2->Checked)
	{
		DBGrid2->DataSource = DataModule2->DataSource3;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
	if (RadioButton3->Checked)
	{
		DBGrid2->DataSource = DataModule2->DataSource4;
	}
}
//---------------------------------------------------------------------------

