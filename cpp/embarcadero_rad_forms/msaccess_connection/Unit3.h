//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TButton *Button1;
	TDBCheckBox *DBCheckBox1;
	TDBCheckBox *DBCheckBox2;
	TDBEdit *DBEdit1;
	TDBEdit *DBEdit2;
	TDBEdit *DBEdit3;
	TDBComboBox *DBComboBox1;
	TDBEdit *DBEdit4;
	TDBEdit *DBEdit5;
	TDBEdit *DBEdit6;
	TDBEdit *DBEdit7;
	TDBEdit *DBEdit8;
	TDBEdit *DBEdit9;
	TDBEdit *DBEdit10;
	TDBEdit *DBEdit11;
	TDBEdit *DBEdit12;
	TDBEdit *DBEdit13;
	TDBEdit *DBEdit14;
	TDBComboBox *DBComboBox2;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall GroupBox1Exit(TObject *Sender);
	void __fastcall GroupBox2Exit(TObject *Sender);
	void __fastcall GroupBox3Exit(TObject *Sender);
	void __fastcall GroupBox4Exit(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
