#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <psapi.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>

#include <namedpipeapi.h>
#include <fileapi.h>
#include <strsafe.h>
#include <handleapi.h>

namespace oslab3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	public ref class WrapHANDLE
	{
	public:
		HANDLE data = NULL;
		WrapHANDLE(HANDLE input)
		{
			data = input;
		}
	};

	/// <summary>
	/// Сводка для oslab3_server
	/// </summary>
	public ref class oslab3_server : public System::Windows::Forms::Form
	{
	public:
		oslab3_server(void)
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
		~oslab3_server()
		{
			if (components)
			{
				delete components;
			}
			serverStop();
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;


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
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 426);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &oslab3_server::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(397, 426);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &oslab3_server::button2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 32);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(460, 388);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(285, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Сервер именованного канала по адресу:         \\\\.\\pipe\\";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(304, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(168, 20);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = L"OSLab3Pipe";
			// 
			// oslab3_server
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 461);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"oslab3_server";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"oslab3_server";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#define BUFSIZE 512

	private: LPCTSTR lpszPipename;
	private: System::String^ ServerLog = gcnew System::String("");
	public: System::Void LogUpdate()
	{
		BeginInvoke(gcnew ThreadStart(this, &oslab3_server::LUWorker));
	}
	private: System::Void LUWorker()
	{
		richTextBox1->Text = ServerLog;
	}
	private: HANDLE hListingJob = NULL;
	private: BOOL serverUp = FALSE;

	private: System::Void serverStart()
	{
		if (hListingJob == NULL)
		{
			serverUp = FALSE;
			hListingJob = CreateThread(
				NULL,
				NULL,
				(LPTHREAD_START_ROUTINE)(Marshal::GetFunctionPointerForDelegate(gcnew ThreadStart(this, &oslab3_server::serverListing)).ToPointer()),
				NULL,
				NULL,
				NULL);
			if (hListingJob != NULL)
			{
				ServerLog += String::Format(gcnew String("[???] Запущен сервер по адресу {0}\n"), gcnew String(lpszPipename)); LogUpdate();
			}
			ServerLog = "";
		}
		else
		{
			ServerLog += String::Format(gcnew String("[!!!] Сервер уже запущен\n")); LogUpdate();
		}
	}

	private: bool serverStop()
	{
		if (hListingJob != NULL)
		{
			HANDLE hPipe = CreateFile(
				lpszPipename,
				PIPE_ACCESS_OUTBOUND,
				FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			if (hPipe == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			serverUp = FALSE;
			TCHAR* lpvMessage = L"MAIN THREAD: serverUp = FALSE;";
			DWORD cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
			DWORD cbWritten;
			BOOL result = WriteFile(
				hPipe,
				lpvMessage,
				cbToWrite,
				&cbWritten,
				NULL);
			CloseHandle(hPipe);
			CloseHandle(hListingJob);
			hListingJob = NULL;
			return true;
		}
		return false;
	}

	private: System::Void serverListing()
	{

		if (textBox1->Text->Length == 0)
		{
			ServerLog += String::Format(gcnew String("[!!!] Отсутствует входное значение имени сервера\n")); LogUpdate();
			return;
		}
		msclr::interop::marshal_context context;
		lpszPipename = context.marshal_as<const TCHAR*>(L"\\\\.\\pipe\\" + textBox1->Text);;

		BOOL fConnected = FALSE;
		DWORD dwThreadId = 0;
		HANDLE hPipe = INVALID_HANDLE_VALUE;
		HANDLE hThread = NULL;

		serverUp = TRUE;

		while (serverUp)
		{
			hPipe = CreateNamedPipe(
				lpszPipename,
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
				PIPE_UNLIMITED_INSTANCES,
				BUFSIZE,
				BUFSIZE,
				50,
				NULL);

			if (hPipe == INVALID_HANDLE_VALUE)
			{
				ServerLog += String::Format(gcnew String("[!!!] Could not create pipe {0}\n"), GetLastError().ToString()); LogUpdate();
				return;
			}

			ServerLog += String::Format(gcnew String("[???] Готовность и ожидание подключения клиентов\n")); LogUpdate();
			fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

			if (fConnected)
			{
				ServerLog += String::Format(gcnew String("[???] Подключение клиента\n")); LogUpdate();

				Thread^ connection = gcnew Thread(gcnew ParameterizedThreadStart(this, &oslab3_server::serverRoutine));
				HANDLE Duplicate = NULL;
				DuplicateHandle(
					GetCurrentProcess(),
					hPipe,
					GetCurrentProcess(),
					&Duplicate,
					0,
					FALSE,
					DUPLICATE_SAME_ACCESS);
				connection->Start(gcnew WrapHANDLE(Duplicate));

				if (connection == nullptr)
				{
					ServerLog += String::Format(gcnew String("[!!!] Could not create thread {0}\n"), GetLastError().ToString()); LogUpdate();
					return;
				}
			}
			CloseHandle(hPipe);
		}
	}

	private: System::Void serverRoutine(Object^ parameter)
	{
		HANDLE hHeap = GetProcessHeap();
		TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

		DWORD cbBytesRead = 0;
		DWORD cbReplyBytes = 0;
		DWORD cbWritten = 0;
		BOOL fSuccess = FALSE;
		HANDLE hPipe = (dynamic_cast<WrapHANDLE^>(parameter))->data;

		DWORD IdCurrentThread = GetCurrentThreadId();

		if (parameter == nullptr)
		{
			ServerLog += String::Format(gcnew String("[ID|{0}] NULL parameter; returning...\n"), IdCurrentThread.ToString()); LogUpdate();
			return;
		}

		ServerLog += String::Format(gcnew String("[ID|{0}] Создано клиентское соединение\n"), IdCurrentThread.ToString()); LogUpdate();

		while (TRUE)
		{
			while (fSuccess = ReadFile(
				hPipe,
				pchRequest,
				BUFSIZE * sizeof(TCHAR),
				&cbBytesRead,
				NULL))
			{
				if (cbBytesRead == 0)
				{
					ServerLog += String::Format(gcnew String("[ID|{1}] ReadFile fail {0}\n"), GetLastError().ToString(), IdCurrentThread.ToString()); LogUpdate();
				}
				else
				{
					ServerLog += String::Format(gcnew String("[ID|{1}] Получено сообщение от клиента '{0}'\n"), gcnew String(pchRequest), IdCurrentThread.ToString()); LogUpdate();
					break;
				}
			}
			if (!fSuccess)
			{
				ServerLog += String::Format(gcnew String("[ID|{1}] ReadFile fail {0}\n"), GetLastError().ToString(), IdCurrentThread.ToString()); LogUpdate();
			}

			msclr::interop::marshal_context context;
			String^ responce;
			if (wcscmp(pchRequest, L"DateTime") == 0)
			{
				SYSTEMTIME st = { 0 };
				GetLocalTime(&st);
				responce = gcnew String(String::Format("{0}/{1}/{2} {3}:{4}:{5}\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond));
			}
			else if (wcscmp(pchRequest, L"HELP") == 0)
			{
				responce = gcnew String("|DateTime;HELP|");
			}
			else
			{
				responce = gcnew String(String::Format("{0} символов", lstrlen(pchRequest)));
			}
			TCHAR* pchReply = (wchar_t*)(void*)Marshal::StringToHGlobalUni(gcnew String(pchRequest) + ": " + responce);
			cbReplyBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);
			ServerLog += String::Format(gcnew String("[ID|{1}] Отправка {2} байт сообщения '{0}'\n"), gcnew String(pchReply), IdCurrentThread.ToString(), cbReplyBytes); LogUpdate();

			fSuccess = WriteFile(
				hPipe,
				pchReply,
				cbReplyBytes,
				&cbWritten,
				NULL);
			if (fSuccess)
			{
			}
			else
			{
				ServerLog += String::Format(gcnew String("[ID|{1}] WriteFile failed {0}\n"), GetLastError().ToString(), IdCurrentThread.ToString()); LogUpdate();
				break;
			}
		}

		// Flush the pipe to allow the client to read the pipe's contents 
		// before disconnecting. Then disconnect the pipe, and close the 
		// handle to this pipe instance. 

		FlushFileBuffers(hPipe);
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);

		HeapFree(hHeap, 0, pchRequest);

		ServerLog += String::Format(gcnew String("[ID|{0}] Завершение клиентской сессии\n"), GetCurrentThreadId().ToString()); LogUpdate();
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		serverStart();
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (serverStop())
		{
			ServerLog += String::Format(gcnew String("[???] Сервер остановлен\n")); LogUpdate();
		}
		else
		{
			ServerLog += String::Format(gcnew String("[!!!] Сервер еще не запущен\n")); LogUpdate();
		}
	}

};
}
