#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <psapi.h>
#include <synchapi.h>
#include <msclr\marshal_cppstd.h>

namespace oslab2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
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
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button3;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Выберите файл:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(107, 14);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(352, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(465, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Обзор";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(465, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Mutex";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(384, 41);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Semaph x3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(552, 77);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void startProcess()
	{
		if (textBox1->Text != "")
		{
			DWORD fCreate;
			STARTUPINFO StartUp;
			PROCESS_INFORMATION ProcessInfo;
			LPCTSTR lpcPATH = (wchar_t*)(void*)Marshal::StringToHGlobalUni(textBox1->Text);
			LPTSTR targv = L"";
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
				/*MessageBox::Show(
					"PID: " + ProcessInfo.dwProcessId,
					"Процесс успешно создан",
					MessageBoxButtons::OK,
					MessageBoxIcon::Information,
					MessageBoxDefaultButton::Button1,
					MessageBoxOptions::DefaultDesktopOnly);*/
			}
			WaitForSingleObject(ProcessInfo.hThread, INFINITE);
			CloseHandle(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
	}

	private: System::Void tryOccupyStartProcessMutex()
	{
		HANDLE mute = CreateMutex(
			NULL,
			TRUE,
			L"startProcess_occupy_mutex");

		if (mute)
		{
			int rval = GetLastError();
			if (rval == ERROR_ALREADY_EXISTS)
			{
				if (System::Windows::Forms::DialogResult::Yes == MessageBox::Show(
					"Попробовать дождаться освобождения? (5 сек)",
					"Секция занята",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question,
					MessageBoxDefaultButton::Button1,
					MessageBoxOptions::DefaultDesktopOnly))
				{
					if (WaitForSingleObject(mute, 5000) == WAIT_TIMEOUT)
					{
						MessageBox::Show(
							"Не удалось дождаться освобождения.",
							"Секция занята",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information,
							MessageBoxDefaultButton::Button1,
							MessageBoxOptions::DefaultDesktopOnly);
					}
					else
					{
						startProcess();
						ReleaseMutex(mute);
					}
				}
			}
			else
			{
				startProcess();
				ReleaseMutex(mute);
			}
		}
		CloseHandle(mute);
	}

	private: System::Void tryOccupyStartProcessSemaphore3()
	{
		HANDLE mute = CreateSemaphore(
			NULL,
			2,
			2,
			L"startProcess_occupy_semaphore3");
		if (mute)
		{
			int rval = GetLastError();
			if (rval == ERROR_ALREADY_EXISTS)
			{
				if (WAIT_OBJECT_0 == WaitForSingleObject(mute, 0))
				{
					startProcess();
					ReleaseSemaphore(mute, 1, NULL);
				}
				else
				{
					if (System::Windows::Forms::DialogResult::Yes == MessageBox::Show(
						"Попробовать дождаться освобождения? (5 сек)",
						"Секция занята",
						MessageBoxButtons::YesNo,
						MessageBoxIcon::Question,
						MessageBoxDefaultButton::Button1,
						MessageBoxOptions::DefaultDesktopOnly))
					{
						DWORD waitResult = WaitForSingleObject(mute, 5000);
						if (waitResult == WAIT_TIMEOUT)
						{
							MessageBox::Show(
								"Не удалось дождаться освобождения.",
								"Секция занята",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information,
								MessageBoxDefaultButton::Button1,
								MessageBoxOptions::DefaultDesktopOnly);
						}
						else if (waitResult == WAIT_OBJECT_0)
						{
							startProcess();
							ReleaseSemaphore(mute, 1, NULL);
						}
					}
				}
			}
			else
			{
				startProcess();
				ReleaseSemaphore(mute, 1, NULL);
			}
		}
		CloseHandle(mute);
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			textBox1->Text = openFileDialog1->FileName;
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DWORD ThreadID;
		HANDLE aThread = CreateThread(
			NULL,
			NULL,
			(LPTHREAD_START_ROUTINE)(Marshal::GetFunctionPointerForDelegate(gcnew ThreadStart(this, &MyForm::tryOccupyStartProcessMutex)).ToPointer()),
			NULL,
			NULL,
			&ThreadID);
		CloseHandle(aThread);
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DWORD ThreadID;
		HANDLE aThread = CreateThread(
			NULL,
			NULL,
			(LPTHREAD_START_ROUTINE)(Marshal::GetFunctionPointerForDelegate(gcnew ThreadStart(this, &MyForm::tryOccupyStartProcessSemaphore3)).ToPointer()),
			NULL,
			NULL,
			&ThreadID);
		CloseHandle(aThread);
	}

};

}
