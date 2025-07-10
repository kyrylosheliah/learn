#pragma once
#pragma comment (lib, "Advapi32.lib")

#include <Windows.h>
#include <winreg.h>
#include <shlwapi.h>
#include <msclr\marshal_cppstd.h>

namespace oslab4 {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace Microsoft::Win32;
	using namespace Microsoft::Win32::SafeHandles;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			HKEY PREDEFINED_HKEY[9] = {
				HKEY_CLASSES_ROOT,
				HKEY_CURRENT_CONFIG,
				HKEY_CURRENT_USER,
				HKEY_CURRENT_USER_LOCAL_SETTINGS,
				HKEY_LOCAL_MACHINE,
				HKEY_PERFORMANCE_DATA,
				HKEY_PERFORMANCE_NLSTEXT,
				HKEY_PERFORMANCE_TEXT,
				HKEY_USERS };
			List<String^>^ PREDEFINED_HKEY_STRING = gcnew List<String^>();
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_CLASSES_ROOT"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_CURRENT_CONFIG"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_CURRENT_USER"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_CURRENT_USER_LOCAL_SETTINGS"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_LOCAL_MACHINE"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_PERFORMANCE_DATA"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_PERFORMANCE_NLSTEXT"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_PERFORMANCE_TEXT"));
			PREDEFINED_HKEY_STRING->Add(gcnew String("HKEY_USERS"));

			PreDefKeys = gcnew List<RegistryKey^>();
			HKEY KEY;
			treeView1->Nodes->Add(gcnew TreeNode("Этот компьютер"));
			for (int i = 0; i < 9; ++i)
			{
				if (ERROR_SUCCESS == RegOpenKeyEx(
					PREDEFINED_HKEY[i],
					NULL,
					NULL,
					KEY_READ,
					&KEY))
				{
					PreDefKeys->Add(RegistryKey::FromHandle(gcnew SafeRegistryHandle((IntPtr)KEY, false)));
					treeView1->Nodes[0]->Nodes->Add(PREDEFINED_HKEY_STRING[i]);
				}
			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			for (int i = 0; i < PreDefKeys->Count; ++i)
			{
				RegCloseKey((HKEY)PreDefKeys[i]->Handle->DangerousGetHandle().ToPointer());
			}
		}
	private: System::Windows::Forms::TreeView^ treeView1;
	protected:
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;






	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// treeView1
			// 
			this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView1->Location = System::Drawing::Point(3, 3);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(299, 571);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView1_AfterSelect);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->Location = System::Drawing::Point(12, 12);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->treeView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->dataGridView1);
			this->splitContainer1->Size = System::Drawing::Size(920, 577);
			this->splitContainer1->SplitterDistance = 305;
			this->splitContainer1->TabIndex = 1;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1,
					this->Column2, this->Column3
			});
			this->dataGridView1->Location = System::Drawing::Point(3, 3);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->Size = System::Drawing::Size(605, 571);
			this->dataGridView1->TabIndex = 0;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Имя";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Тип";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Значение";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(944, 601);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

	private: List<RegistryKey^>^ PreDefKeys;

	private: HKEY GetSubKeyHandle(TreeNode^ LastNode)
	{
		HKEY hMyKey;
		HKEY hSubKey;
		LPCWSTR SubKName;

		if (LastNode->Level > 1)
		{
			hMyKey = GetSubKeyHandle(LastNode->Parent);
			SubKName = (wchar_t*)(void*)Marshal::StringToHGlobalUni(LastNode->Text);
			RegOpenKeyEx(
				hMyKey,
				SubKName,
				NULL,
				KEY_READ,
				&hSubKey);
			RegCloseKey(hMyKey);
			return hSubKey;
		}
		else
		{
			hMyKey = (HKEY)PreDefKeys[LastNode->Index]->Handle->DangerousGetHandle().ToPointer();
			return hMyKey;
		}
	}

	private: System::Void treeView1_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
	{
		if ((e->Node->Level < 1) || (e->Node->Nodes->Count > 0))
		{
			return;
		}

		TCHAR achClass[MAX_PATH] = TEXT("");
		DWORD cchClassName = MAX_PATH;
		DWORD cSubKeys = 0;
		DWORD cbMaxSubKey;
		DWORD cchMaxClass;
		DWORD cValues;
		DWORD cchMaxValue;
		DWORD cbMaxValueData;
		DWORD cbSecurityDescriptor;

		DWORD i, retCode;

		HKEY hKey = GetSubKeyHandle(treeView1->SelectedNode);
		
		retCode = RegQueryInfoKeyW(
			hKey,
			achClass,
			&cchClassName,
			NULL,
			&cSubKeys,
			&cbMaxSubKey,
			&cchMaxClass,
			&cValues,
			&cchMaxValue,
			&cbMaxValueData,
			&cbSecurityDescriptor,
			NULL
		);

		dataGridView1->Rows->Clear();
		TCHAR achKey[MAX_KEY_LENGTH];
		DWORD cbName;

		if (cSubKeys)
		{
			for (i = 0; i < cSubKeys; i++)
			{
				cbName = MAX_KEY_LENGTH;
				if (ERROR_SUCCESS == RegEnumKeyEx(
					hKey,
					i,
					achKey,
					&cbName,
					NULL,
					NULL,
					NULL,
					NULL))
				{
					e->Node->Nodes->Add(gcnew String(achKey));
				}
			}
		}

		String^ StrValType = L"";
		String^ StrValData = L"";
		TCHAR achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;
		DWORD ValType;
		//array<BYTE>^ bDataSafe = gcnew array<BYTE>(cbMaxValueData); неправда
		//PBYTE bData = (PBYTE)(IntPtr)bDataSafe; дурочоq
		PBYTE bData = new BYTE[cbMaxValueData];
		//DWORD dwDataMaxSize; макс длина данных, получено в cbMaxValueData
		if (cValues)
		{
			for (i = 0; i < cValues; i++)
			{
				cchValue = MAX_VALUE_NAME;
				achValue[0] = '\0';
				if (ERROR_SUCCESS == RegEnumValue(
					hKey,
					i,
					achValue,
					&cchValue,
					NULL,
					NULL,  //&ValType, => RegQueryValueEx
					NULL,  ///bData,  => RegQueryValueEx
					NULL)) //&cbMaxValueData)) => RegQueryValueEx
				{
					if (ERROR_SUCCESS == RegQueryValueEx(
						hKey,
						achValue,
						NULL,
						&ValType,
						bData,
						&cbMaxValueData))
					{
						switch (ValType)
						{
						case REG_BINARY:
							StrValType = "REG_BINARY";
							StrValData = gcnew String(((PWCHAR)bData));
							break;
						case REG_DWORD:
							StrValType = "REG_DWORD";
							StrValData = gcnew String(((DWORD)bData).ToString());
							break;
						/*case REG_QWORD:
							StrValType = "REG_QWORD";
							StrValData = gcnew String(((QWORD)bData).ToString());
							break;*/
						case REG_DWORD_BIG_ENDIAN:
							StrValType = "REG_DWORD_BIG_ENDIAN";
							StrValData = gcnew String(((DWORD)bData).ToString());
							break;
						case REG_EXPAND_SZ:
							StrValType = "REG_EXPAND_SZ";
							StrValData = gcnew String((PWCHAR)bData);
							break;
						case REG_LINK:
							StrValType = "REG_LINK";
							StrValData = gcnew String((PWCHAR)bData);
							break;
						case REG_MULTI_SZ:
							StrValType = "REG_MULTI_SZ";
							StrValData = "PWCHAR[]";
							break;
						case REG_NONE:
							StrValType = "REG_NONE";
							StrValData = "Зашифровано";
							break;
						case REG_SZ:
							StrValType = "REG_SZ";
							StrValData = gcnew String((PWCHAR)bData);
							break;
						case REG_RESOURCE_LIST:
							StrValType = "REG_RESOURCE_LIST";
							StrValData = gcnew String((PWCHAR)bData);
							break;
						case REG_RESOURCE_REQUIREMENTS_LIST:
							StrValType = "REG_RESOURCE_REQUIREMENTS_LIST";
							StrValData = gcnew String((PWCHAR)bData);
							break;
						case REG_FULL_RESOURCE_DESCRIPTOR:
							StrValType = "REG_FULL_RESOURCE_DESCRIPTOR";
							StrValData = "Чел...";
							break;
						default:
							StrValType = "<Unknown>";
							StrValData = "";
						}
						dataGridView1->Rows->Add(gcnew String(achValue), StrValType, StrValData);
					}
				}
			}
		}
		
		delete[] bData;
		RegCloseKey(hKey);
	}
};
}
