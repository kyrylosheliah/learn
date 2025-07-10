#pragma once

#include <Windows.h>
#include <fstream>
#include <random>
#include <sstream>
#include <msclr\marshal.h>
#include <msclr\marshal_windows.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_atl.h>

namespace oslab6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
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

			for (DWORD i = 0; i < 20; ++i)
			{
				comboBox1->Items->Add(i + 1);
			}
			comboBox1->SelectedIndex = 3;
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
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ comboBox1;


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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(312, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Обзор...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(12, 41);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(400, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(228, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Выберите *.txt";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Текстовый файл (*.txt)|*.txt";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Записать in.txt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(118, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"___";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->richTextBox1->Location = System::Drawing::Point(12, 67);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(400, 455);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button3->Location = System::Drawing::Point(12, 557);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 23);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Задание";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(118, 562);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(25, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"___";
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button4->Location = System::Drawing::Point(12, 586);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Записать out.txt";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(118, 591);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"___";
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 530);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(100, 21);
			this->comboBox1->TabIndex = 10;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(424, 621);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->MinimumSize = System::Drawing::Size(440, 660);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void DoTask()
	{
		msclr::interop::marshal_context context;
		HANDLE hInputFile = CreateFile(
			context.marshal_as<const TCHAR*>(textBox1->Text),
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_READ_ONLY,
			NULL);
		TCHAR* outputFilePath = L"out.txt";
		HANDLE hOutputFile = CreateFile(
			outputFilePath,
			GENERIC_READ | GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if ((INVALID_HANDLE_VALUE == hInputFile) || (INVALID_HANDLE_VALUE == hOutputFile))
		{
			label3->Text = "[!] Файлы не открыты";
			CloseHandle(hOutputFile);
			CloseHandle(hInputFile);
			return;
		}

		HANDLE hInputMap = CreateFileMapping(
			hInputFile,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL);
		DWORD dwFileSizeLow = GetFileSize(
			hInputFile,
			NULL);
		HANDLE hOutputMap = CreateFileMappingW(
			hOutputFile,
			NULL,
			PAGE_READWRITE,
			0,
			dwFileSizeLow,
			NULL);
		if ((INVALID_HANDLE_VALUE == hInputMap) || (INVALID_HANDLE_VALUE == hOutputMap))
		{
			label3->Text = "[!] Отображения на ВАП не созданы";
			CloseHandle(hOutputMap);
			CloseHandle(hInputMap);
			CloseHandle(hOutputFile);
			CloseHandle(hInputFile);
			return;
		}

		LPWSTR pInputMapView = (LPWSTR)MapViewOfFile(
			hInputMap,
			FILE_MAP_READ,
			0,
			0,
			0);
		LPWSTR pOutputMapView = (LPWSTR)MapViewOfFile(
			hOutputMap,
			FILE_MAP_WRITE,
			0,
			0,
			0);

		DWORD wordSizeCondition = (DWORD)comboBox1->SelectedItem;
		DWORD wordCounter = 0;
		DWORD chCounter = 0;
		DWORD i;
		DWORD j;
		TCHAR* dataTemp;

		LPWSTR pOut = pOutputMapView;
		LPWSTR pInputMapEnd = pInputMapView + (dwFileSizeLow/sizeof(wchar_t));
		for (LPWSTR pIn = pInputMapView; pIn < pInputMapEnd-1; ++pIn)
		{
			if (*pIn == 32)
			{
				if (chCounter <= wordSizeCondition)
				{
					++wordCounter;
					dataTemp = context.marshal_as<TCHAR*>(String::Format("{0}+\t", chCounter));
					j = lstrlen(dataTemp);
					for (i = 0; i < j; ++i)
					{
						*pOut = dataTemp[i];
						++pOut;
					}
				}
				else
				{
					dataTemp = context.marshal_as<TCHAR*>(String::Format("{0}\t", chCounter));
					j = lstrlen(dataTemp);
					for (i = 0; i < j; ++i)
					{
						*pOut = dataTemp[i];
						++pOut;
					}
				}
				chCounter = 0;
			}
			else
			{
				++chCounter;
			}
			
		}
		dataTemp = context.marshal_as<TCHAR*>(String::Format("\n=========\n===Насчитано слов: {0}\n=========\n", wordCounter));
		j = lstrlen(dataTemp);
		for (i = 0; i < j; ++i)
		{
			*pOut = dataTemp[i];
			++pOut;
		}
		label3->Text = "out.txt записан";
		richTextBox1->Text = gcnew String(pOutputMapView);

		UnmapViewOfFile(pOutputMapView);
		UnmapViewOfFile(pInputMapView);
		CloseHandle(hOutputMap);
		CloseHandle(hInputMap);
		CloseHandle(hOutputFile);
		CloseHandle(hInputFile);
	}

	private: System::Void SomeFileSomeWrite(String^ writeWhere, String^ writeWhat, Label^ log)
	{
		marshal_context context;
		TCHAR* writePath = context.marshal_as<TCHAR*>(writeWhere);

		HANDLE hFile = CreateFile(
			writePath,
			GENERIC_READ | GENERIC_WRITE,
			NULL,
			NULL, // для записи EOF: ИЛИ FILE_APPEND_DATA
			CREATE_ALWAYS, // OPEN_ALWAYS запись поверх старых данных
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			log->Text = "[!] out.txt не создан";
		}
		else
		{
			TCHAR* toWrite = context.marshal_as<TCHAR*>(writeWhat);
			DWORD dwToWrite = lstrlen(toWrite) * sizeof(wchar_t);
			DWORD dwCountWritten;
			if (WriteFile(
				hFile,
				toWrite,
				dwToWrite,
				&dwCountWritten,
				NULL)) // для записи EOF: ИЛИ OVERLAPPED::Offset и OVERLAPPED::OffsetHigh как 0xFFFFFFFF
			{
				if (dwCountWritten)
				{
					if (dwCountWritten == dwToWrite)
					{
						log->Text = "[!] " + writeWhere + " записан";
					}
					else
					{
						log->Text = String::Format(writeWhere + " записано {0} из {1} байт", dwCountWritten, dwToWrite);
					}
				}
				else
				{
					log->Text = writeWhere + " записано 0 байт";
				}
			}
			else
			{
				log->Text = "[!] " + writeWhere + " не записан";
			}
		}

		CloseHandle(hFile);
	}

	private: System::Void GenerateThenWriteInputData()
	{
		std::stringstream buffer;
		std::random_device rnd;
		std::mt19937 mersenne(rnd());
		std::uniform_int_distribution<> distr(1, 20);

		buffer.str(std::string());
		buffer.clear();
		for (int i = 0; i < distr(mersenne); ++i)
		{
			buffer << (char)('a' + (char)(rnd() % 26));
		}
		for (int i = 0; i < 10240; ++i)
		{
			//buffer.str(std::string());
			//buffer.clear();
			buffer << ' ';
			for (int i = 0; i < distr(mersenne); ++i)
			{
				buffer << (char)('a' + (char)(rnd() % 26));
			}
		}

		SomeFileSomeWrite("in.txt", marshal_as<String^>(buffer.str()), label2);
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
		GenerateThenWriteInputData();
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (textBox1->Text->Length)
		{
			label3->Text = "___";
			DoTask();
		}
		else
		{
			label3->Text = "[!] Файл не выбран";
		}
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (richTextBox1->Text->Length)
		{
			label4->Text = "___";
			SomeFileSomeWrite("out.txt", richTextBox1->Text, label4);
		}
		else
		{
			label4->Text = "[!] Данные не выведены";
		}
	}
	};
}
