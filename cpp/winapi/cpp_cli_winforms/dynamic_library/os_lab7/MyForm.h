#pragma once

#include <Windows.h>
typedef double(__cdecl* MYFUN)(double);

namespace oslab7 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
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

			
			HINSTANCE dllInstance = LoadLibrary(L"os_lab7_dll.dll");
			FARPROC dllFunction = GetProcAddress(dllInstance, "MYFUN");
			dllInstancePtr = (IntPtr)dllInstance;
			dllFunctionPtr = (IntPtr)dllFunction;
			
			PREDEFINED_RANGE = gcnew List<short>(13);
			PREDEFINED_RANGE->Add(-100);
			PREDEFINED_RANGE->Add(-50);
			PREDEFINED_RANGE->Add(-20);
			PREDEFINED_RANGE->Add(-15);
			PREDEFINED_RANGE->Add(-10);
			PREDEFINED_RANGE->Add(-5);
			PREDEFINED_RANGE->Add(0);
			PREDEFINED_RANGE->Add(5);
			PREDEFINED_RANGE->Add(10);
			PREDEFINED_RANGE->Add(15);
			PREDEFINED_RANGE->Add(20);
			PREDEFINED_RANGE->Add(50);
			PREDEFINED_RANGE->Add(100);
			for (int i = 0; i < PREDEFINED_RANGE->Count; ++i)
			{
				comboBox1->Items->Add(PREDEFINED_RANGE[i].ToString());
			}
			comboBox1->SelectedIndex = 0;
			comboBox3->Items->Add("0,05");
			comboBox3->Items->Add("0,1");
			comboBox3->Items->Add("0,2");
			comboBox3->Items->Add("0,25");
			comboBox3->Items->Add("0,5");
			comboBox3->Items->Add("1");
			comboBox3->Items->Add("2");
			comboBox3->Items->Add("5");
			comboBox3->Items->Add("10");
			comboBox3->SelectedIndex = 3;
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
			if (!(dllInstancePtr == IntPtr::Zero))
			{
				FreeLibrary((HINSTANCE)dllInstancePtr.ToPointer());
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			this->chart1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Location = System::Drawing::Point(0, 21);
			this->chart1->Name = L"chart1";
			series2->BorderWidth = 3;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Color = System::Drawing::Color::Fuchsia;
			series2->Name = L"Series1";
			series2->YValuesPerPoint = 4;
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(584, 540);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			title2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			title2->Name = L"Title1";
			title2->Text = L"os_lab7_dll.dll query following";
			this->chart1->Titles->Add(title2);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(29, 0);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(60, 21);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(120, 0);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(60, 21);
			this->comboBox2->TabIndex = 2;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(241, 0);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(60, 21);
			this->comboBox3->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(510, -1);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Построить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 4);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"От";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(95, 4);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(19, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"до";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(186, 4);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(49, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"с шагом";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(307, 4);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 13);
			this->label4->TabIndex = 8;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 561);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->chart1);
			this->MinimumSize = System::Drawing::Size(600, 600);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: IntPtr dllInstancePtr;
	private: IntPtr dllFunctionPtr;

	private: List<short>^ PREDEFINED_RANGE;

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (comboBox1->SelectedIndex >= 0)
		{
			comboBox2->Items->Clear();
			for (int i = comboBox1->SelectedIndex + 1; i < PREDEFINED_RANGE->Count; ++i)
			{
				comboBox2->Items->Add(PREDEFINED_RANGE[i].ToString());
			}
			if (comboBox2->Items->Count > 0)
			{
				comboBox2->SelectedIndex = 0;
			}
			else
			{
				comboBox2->Text = "";
			}
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (dllInstancePtr == IntPtr::Zero)
		{
			MessageBox::Show(
				"os_lab7_dll.dll не загружен",
				"Форма будет закрыта",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error,
				MessageBoxDefaultButton::Button1,
				MessageBoxOptions::DefaultDesktopOnly);
			this->Close();
			return;
		}
		if (dllFunctionPtr == IntPtr::Zero)
		{
			MessageBox::Show(
				"Функция MYFUN библиотеки os_lab7_dll.dll не загружена",
				"Форма будет закрыта",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error,
				MessageBoxDefaultButton::Button1,
				MessageBoxOptions::DefaultDesktopOnly);
			this->Close();
			return;
		}

		if (comboBox1->Text->Length && comboBox2->Text->Length)
		{
			MYFUN myfunInstance = (MYFUN)((FARPROC)dllFunctionPtr.ToPointer());

			label4->Text = "";
			double temp1;
			double temp2;
			
			double step;
			bool safeParse = true;
			if (!double::TryParse(comboBox1->Text, temp1))
			{
				safeParse = false;
			}
			if (!double::TryParse(comboBox2->Text, temp2))
			{
				safeParse = false;
			}
			if (!double::TryParse(comboBox3->Text, step))
			{
				safeParse = false;
			}
			if (safeParse)
			{
				//temp1 = double::Parse(comboBox1->Text);
				//temp2 = double::Parse(comboBox2->Text);
				//step = double::Parse(comboBox3->Text);
				double from_x = Math::Min(temp1, temp2);
				double to_x = Math::Max(temp1, temp2);

				chart1->Series[0]->Points->Clear();
				while (from_x <= to_x)
				{
					temp1 = myfunInstance(from_x);
					chart1->Series[0]->Points->AddXY(from_x, temp1);
					from_x += step;
				}
			}
			else
			{
				label4->Text = "[!] Ошибка парсинга входных значений";
			}
			
		}
		else
		{
			label4->Text = "[!] Не выбран диапазон";
		}
	}
};
}
