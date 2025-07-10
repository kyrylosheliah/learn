#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <psapi.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>

namespace oslab3client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Сводка для oslab3_client
	/// </summary>
	public ref class oslab3_client : public System::Windows::Forms::Form
	{
	public:
		oslab3_client(void)
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
		~oslab3_client()
		{
			if (components)
			{
				delete components;
			}
			connectionStop();
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(278, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Клиент именованого канала по адресу:         \\\\.\\pipe\\";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 32);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(460, 388);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 426);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &oslab3_client::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(397, 426);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Disconnect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &oslab3_client::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(138, 426);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"command:";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &oslab3_client::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(219, 428);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(136, 20);
			this->textBox1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(304, 6);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(168, 20);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"OSLab3Pipe";
			// 
			// oslab3_client
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 461);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"oslab3_client";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"oslab3_client";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#define BUFSIZE 512

	private: LPCTSTR lpszPipename;
	
	private: HANDLE hConnection = NULL;

	private: System::Void connectionStart()
	{
		richTextBox1->Text = "";

		if (hConnection == NULL)
		{
			if (textBox2->Text->Length == 0)
			{
				richTextBox1->Text += String::Format(gcnew String("[!!!] Отсутствует входное значение имени сервера\n"));
				return;
			}
			msclr::interop::marshal_context context;
			lpszPipename = context.marshal_as<const TCHAR*>(L"\\\\.\\pipe\\" + textBox2->Text);;

			while (TRUE)
			{
				hConnection = CreateFile(
					lpszPipename,
					GENERIC_READ | GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
				if (hConnection != INVALID_HANDLE_VALUE)
				{
					break;
				}
				if (GetLastError() != ERROR_PIPE_BUSY)
				{
					richTextBox1->Text += String::Format(gcnew String("[!!!] Could not open pipe {0}\n"), GetLastError().ToString());
					return;
				}
				if (!WaitNamedPipe(lpszPipename, 2000))
				{
					richTextBox1->Text += String::Format(gcnew String("[!!!] Could not open pipe: 2 seconds wait timed out\n"));
					return;
				}
			}

			richTextBox1->Text += String::Format(gcnew String("[???] Установлено соединение с сервером\n"));

			DWORD dwMode = PIPE_READMODE_MESSAGE;
			SetNamedPipeHandleState(
				hConnection,
				&dwMode,
				NULL,
				NULL);
		}
		else
		{
			richTextBox1->Text += String::Format(gcnew String("[!!!] Соединение уже установлено\n"));
		}
	}

	private: System::Void connectionStop()
	{
		if (hConnection == NULL)
		{
			richTextBox1->Text += String::Format(gcnew String("[!!!] Соединение еще не установлено\n"));
		}
		else
		{
			CloseHandle(hConnection);
			hConnection = NULL;
			richTextBox1->Text += String::Format(gcnew String("[!!!] Соединение с сервером разорвано\n"));
		}
	}

	private: System::Void Message()
	{
		if (hConnection == NULL)
		{
			richTextBox1->Text += String::Format(gcnew String("[!!!] Соединение еще не установлено\n"));
		}
		else
		{
			if (textBox1->Text->Length == 0)
			{
				richTextBox1->Text += String::Format(gcnew String("[!!!] Отсутствует входное значение команды\n"));
				return;
			}
			msclr::interop::marshal_context context;
			LPTSTR lpvMessage = (wchar_t*)(void*)Marshal::StringToHGlobalUni(textBox1->Text);

			HANDLE hHeap = GetProcessHeap();
			TCHAR* chBuf = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

			BOOL fSuccess = FALSE;
			DWORD cbRead, cbToWrite, cbWritten, dwMode;

			cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
			richTextBox1->Text += String::Format(gcnew String("\n[...] Отправка {0} байт сообщения '{1}'\n"), cbToWrite.ToString(), gcnew String(lpvMessage));

			fSuccess = WriteFile(
				hConnection,
				lpvMessage,
				cbToWrite,
				&cbWritten,
				NULL);

			if (!fSuccess)
			{
				richTextBox1->Text += String::Format(gcnew String("[!!!] WriteFile to pipe failed {0}\n"), GetLastError().ToString());
				return;
			}

			while (ReadFile(
				hConnection,
				chBuf,
				BUFSIZE * sizeof(TCHAR),
				&cbRead,
				NULL))
			{
				if (cbRead == 0)
				{
					richTextBox1->Text += String::Format(gcnew String("[!!!] ReadFile from pipe failed {0}\n"), GetLastError().ToString());
					break;
				}
				else
				{
					richTextBox1->Text += String::Format(gcnew String("[...] Получено сообщение от сервера '{0}'\n"), gcnew String(chBuf));
					break;
				}
			}

			richTextBox1->Text += String::Format(gcnew String("[...] Конец ответа\n\n"));

			HeapFree(hHeap, 0, chBuf);
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		connectionStart();
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Message();
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		connectionStop();
	}

};
}
