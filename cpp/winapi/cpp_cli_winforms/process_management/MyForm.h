#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <psapi.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>

namespace oslab1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;

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
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;



	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(642, 10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Обзор";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Выберите файл:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(132, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(504, 20);
			this->textBox1->TabIndex = 2;
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
			this->dataGridView1->Location = System::Drawing::Point(13, 126);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->Size = System::Drawing::Size(704, 317);
			this->dataGridView1->TabIndex = 3;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Имя процесса";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 200;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"PID";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 50;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Полный путь";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Width = 400;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(132, 41);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(504, 20);
			this->textBox2->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(113, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Параметры запуска:";
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(642, 39);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Выполнить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(13, 97);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(89, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Список задач";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button4->Location = System::Drawing::Point(619, 97);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(98, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Удалить задачу";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(729, 461);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->MinimumSize = System::Drawing::Size(745, 500);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			textBox1->Text = openFileDialog1->FileName;
		}
	}
	
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		startProcess();
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		getProcessList();
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
	{
		int selectedRowCount = dataGridView1->SelectedRows->Count;
		if (selectedRowCount > 0)
		{
			array<int>^ selectedRowIndexes = gcnew array<int>(selectedRowCount);
			for (int i = selectedRowCount - 1; i >= 0; --i)
			{
				selectedRowIndexes[i] = dataGridView1->SelectedRows[i]->Index;
			}
			Array::Sort(selectedRowIndexes);
			DWORD dProcessId;
			for (int i = selectedRowCount - 1; i >= 0; --i)
			{
				dProcessId = System::UInt32::Parse((String^)dataGridView1->Rows[selectedRowIndexes[i]]->Cells[1]->Value);
				if (endProcess(dProcessId))
				{
					MessageBox::Show(
						"PID: " + dProcessId,
						"Процесс успешно завершен",
						MessageBoxButtons::OK,
						MessageBoxIcon::Information,
						MessageBoxDefaultButton::Button1,
						MessageBoxOptions::DefaultDesktopOnly);
					dataGridView1->Rows->RemoveAt(selectedRowIndexes[i]);
				}
			}
		}
		
	}

	private: System::Void getProcessList()
	{
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		{
			return;
		}
		// Calculate how many process identifiers were returned.
		cProcesses = cbNeeded / sizeof(DWORD);
		std::stringstream ss;
		dataGridView1->Rows->Clear();
		// Print the name, process identifier and process path for each process.
		for (unsigned int i = 0; i < cProcesses; i++)
		{
			if (aProcesses[i] != 0)
			{
				TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
				TCHAR szProcessPath[MAX_PATH] = TEXT("<unknown>");
				// Get a handle to the process.
				HANDLE hProcess = OpenProcess(
					PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					FALSE,
					aProcesses[i]);
				// Get the process name.
				if (NULL != hProcess)
				{
					HMODULE hMod;
					DWORD cbNeeded;
					if (EnumProcessModules(
						hProcess,
						&hMod,
						sizeof(hMod),
						&cbNeeded))
					{
						GetModuleBaseName(
							hProcess,
							hMod,
							szProcessName,
							MAX_PATH);
						GetModuleFileNameEx(
							hProcess,
							hMod,
							szProcessPath,
							MAX_PATH);
						// Print the process name and identifier.
						ss << aProcesses[i];
						dataGridView1->Rows->Add(gcnew String(szProcessName), marshal_as<String^>(ss.str()), gcnew String(szProcessPath));
						ss.str(""); ss.clear();
					}
				}
				
				// Release the handle to the process.
				CloseHandle(hProcess);
			}
		}
	}

	private: System::Void startProcess()
	{
		if (!(textBox1->Text == ""))
		{
			DWORD fCreate;
			// Flags[0] ? CREATE_NEW_CONSOLE : Flags[1] ? DETACHED_PROCESS : 0;
			// | CREATE_SUSPENDED | CREATE_NEW_PROCESS_GROUP,
			STARTUPINFO StartUp;
			PROCESS_INFORMATION ProcessInfo;
			LPCTSTR lpcPATH = (wchar_t*)(void*)Marshal::StringToHGlobalUni(textBox1->Text);
			LPTSTR targv = (wchar_t*)(void*)Marshal::StringToHGlobalUni(textBox2->Text);
			GetStartupInfo(&StartUp);
			if (CreateProcess(
				lpcPATH,
				targv,
				NULL,
				NULL,
				FALSE,
				fCreate,
				NULL,
				NULL,
				&StartUp,
				&ProcessInfo))
			{
				MessageBox::Show(
					"PID: " + ProcessInfo.dwProcessId,
					"Процесс успешно создан",
					MessageBoxButtons::OK,
					MessageBoxIcon::Information,
					MessageBoxDefaultButton::Button1,
					MessageBoxOptions::DefaultDesktopOnly);
			}
			CloseHandle(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
	}

	private: bool endProcess(DWORD dProcessId)
	{
		bool exitState = true;
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dProcessId);
		if (hProcess == NULL)
		{
			exitState = false;
		}
		else
		{
			TerminateProcess(hProcess, 3);
		}
		CloseHandle(hProcess);
		return exitState;
	}
};
}
