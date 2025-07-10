#pragma once

#include <Windows.h>

namespace ossrs {

	using namespace System;
	using namespace System::ComponentModel;
	//using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	public ref struct STRING_INT
	{
		STRING_INT(String^ toStr, int toLevel)
		{
			str = toStr;
			level = toLevel;
		}
		String^ str;
		int level;
	};

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

			int range = 10;
			array<String^>^ stringRange = gcnew array<String^>(range);
			for (int i = 1; i <= range; ++i)
			{
				stringRange[i - 1] = i.ToString();
			}
			comboBox1->Items->AddRange(stringRange);
			comboBox1->SelectedIndex = 3;

			DWORD step;
			DWORD dwSize = MAX_PATH;
			TCHAR szLogicalDrives[MAX_PATH] = { 0 };
			DWORD dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);
			if (dwResult > 0 && dwResult <= MAX_PATH)
			{
				TCHAR* szSingleDrive = szLogicalDrives;
				while (*szSingleDrive)
				{
					step = sizeof(szSingleDrive);
					szSingleDrive[step - 1] = '\0';
					szSingleDrive[step - 2] = '\0';
					treeView2->Nodes->Add(gcnew TreeNode(gcnew String(szSingleDrive)));
					szSingleDrive += step;
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
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TreeView^ treeView1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TreeView^ treeView2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->treeView2 = (gcnew System::Windows::Forms::TreeView());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(603, 426);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Поиск";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(40, 400);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(638, 20);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(40, 428);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(436, 20);
			this->textBox2->TabIndex = 2;
			// 
			// treeView1
			// 
			this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView1->Location = System::Drawing::Point(12, 25);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(330, 369);
			this->treeView1->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 403);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Где:";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 431);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Что:";
			// 
			// treeView2
			// 
			this->treeView2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->treeView2->Location = System::Drawing::Point(348, 12);
			this->treeView2->Name = L"treeView2";
			this->treeView2->Size = System::Drawing::Size(330, 382);
			this->treeView2->TabIndex = 6;
			this->treeView2->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView2_AfterSelect);
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(539, 428);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(58, 21);
			this->comboBox1->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(482, 431);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Глубина:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(219, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"В последний раз найдено: ___ элементов";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(694, 461);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->treeView2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->treeView1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->MinimumSize = System::Drawing::Size(706, 500);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: String^ DefineFolder(TreeNode^ outputNode, bool job)
	{
		String^ toPath = "";
		TreeNode^ pNode = outputNode;
		if (pNode->Parent != nullptr && pNode->Text->Contains("."))
		{
			toPath = pNode->Text;
			pNode = pNode->Parent;
		}
		while (pNode->Parent != nullptr)
		{
			toPath = pNode->Text + "\\" + toPath;
			pNode = pNode->Parent;
		}
		toPath = pNode->Text + "\\" + toPath;

		if (job)
		{
			FolderListing(toPath, outputNode->Nodes);
		}

		return toPath;
	}

	private: System::Void FolderListing(System::String^ path, TreeNodeCollection^ outputCollection)
	{
		WIN32_FIND_DATA wfd;
		LPCWSTR folder = (wchar_t*)(void*)Marshal::StringToHGlobalUni(path + "\\*");
		HANDLE const hFind = FindFirstFile(folder, &wfd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
			{
				if (wfd.cFileName[0] != '.')
				{
					outputCollection->Add(gcnew TreeNode(gcnew String(&wfd.cFileName[0])));
				}
			} while (NULL != FindNextFile(hFind, &wfd));

			FindClose(hFind);
		}
	}

	private: System::Void AutoNodeTreePush(String^ foundPath)
	{
		array<String^>^ toNodes = foundPath->Split('\\');
		TreeNode^ currentNode = treeView1->Nodes[treeView1->Nodes->Count - 1];
		for each (String^ toNode in toNodes)
		{
			bool notFoundFlag = true;
			for each (TreeNode^ node in currentNode->Nodes)
			{
				if (node->Text == toNode)
				{
					currentNode = node;
					notFoundFlag = false;
					break;
				}
			}
			if (notFoundFlag)
			{
				currentNode = currentNode->Nodes->Add(toNode);
			}
		}
	}

	private: int searchCounter = 1;
	private: System::Void FindFilesMasked()
	{
		String^ mask = (String^)textBox2->Text->Clone();
		String^ startPath = (String^)textBox1->Text->Clone();
		int depth = int::Parse((String^)comboBox1->SelectedItem);
		int foundCounter = 0;
		Stack<STRING_INT^>^ pathStack = gcnew Stack<STRING_INT^>();
		STRING_INT^ pathStackPop;
		WIN32_FIND_DATA wfd;
		LPCWSTR path;
		HANDLE hFind;

		treeView1->Nodes->Add(L"Поиск " + searchCounter.ToString());
		++searchCounter;
		pathStack->Clear();
		pathStack->Push(gcnew STRING_INT(startPath, 1));

		while (pathStack->Count > 0)
		{
			pathStackPop = pathStack->Pop();

			
			path = (wchar_t*)(void*)Marshal::StringToHGlobalUni(pathStackPop->str + "*");
			hFind = FindFirstFile(path, &wfd);
			if (INVALID_HANDLE_VALUE != hFind)
			{

				do
				{
					if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (wfd.cFileName[0] != '.') && (pathStackPop->level + 1 <= depth))
					{
						pathStack->Push(gcnew STRING_INT(pathStackPop->str + gcnew String(&wfd.cFileName[0]) + "\\", pathStackPop->level + 1));
					}
				} while (NULL != FindNextFile(hFind, &wfd));
				FindClose(hFind);

				path = (wchar_t*)(void*)Marshal::StringToHGlobalUni(pathStackPop->str + mask);
				hFind = FindFirstFile(path, &wfd);
				if (INVALID_HANDLE_VALUE != hFind)
				{
					do
					{
						AutoNodeTreePush(pathStackPop->str + gcnew String(&wfd.cFileName[0]));
						++foundCounter;
					} while (NULL != FindNextFile(hFind, &wfd));
				}
				FindClose(hFind);
				hFind = NULL;
			}
			if (hFind != NULL)
			{
				FindClose(hFind);
			}
		}
		label4->Text = "В последний раз найдено: " + foundCounter.ToString() + " эл.";
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if ((textBox1->Text->Length > 0) && (textBox2->Text->Length > 0))
		{
			FindFilesMasked();
		}
	}

	private: System::Void treeView2_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
	{
		bool job = true;

		if (e->Node->Nodes->Count > 0)
		{
			job = false;
		}

		textBox1->Text = DefineFolder(e->Node, job);
	}
};
}
