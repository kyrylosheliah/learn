#include <iostream>
#include <istream>
#include <string>

using namespace std;

//Структура – Студент.  Структура должна включать соответствующие поля: факультет, код группы, ФИО, дата поступления (массив из трех чисел), 
//список оценок за последнюю сессию. Простейшие функции: перевод на другой факультет, перевод в другую группу, изменение фамилии, 
//изменение даты, добавление оценки, удаление из списка оценки, вывод на экран информации о студенте.

struct node
{
	int grade;
	string subject;
	node * next;
};

struct list
{
	node * first = nullptr;
	int size = 0;
	~list()
	{
		node * pointer = first;
		first = nullptr;
		while (pointer)
		{
			node * todelete = pointer;
			pointer = pointer->next;
			delete todelete;
		}
	}
	void pushfront(string subject_data, int grade_data)
	{
		node * pointer = new node;
		pointer->subject = subject_data;
		pointer->grade = grade_data;
		pointer->next = this->first;
		this->first = pointer;
		size++;
	}
	void popfront()
	{
		if (first == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			node * todelete = first;
			first = first->next;
			delete todelete;
			this->size--;
		}
	}
	void popback()
	{
		if (first == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			node * pointer = this->first;
			node * todelete = pointer->next;
			while (todelete->next != nullptr)
			{
				pointer = pointer->next;
				todelete = todelete->next;
			}
			pointer->next = nullptr;
			delete todelete;
			this->size--;
		}
	}
	void initiate_removal()
	{
		if (this->first == nullptr)
		{
			cout << "\nСписок пуст\n";
		}
		else
		{
			if (display())
			{
				int index;
				cout << "\nВведите номер удаляемой строки: ";
				cin >> index;
				if (index == 1 || this->size == 1)
				{
					popfront();
				}
				else if (index == (this->size))
				{
					popback();
				}
				else
				{
					node * temp1 = nullptr;
					node * temp2 = nullptr;
					node * todelete = nullptr;
					node * pointer = this->first;
					for (int i = 0; i < index; ++i)
					{
						if (i == index - 1)
						{
							temp1 = pointer;
							pointer = pointer->next;
							todelete = pointer;
							pointer = pointer->next;
							temp2 = pointer;
						}
						else
						{
							pointer = pointer->next;
						}
					}
					temp1->next = temp2;
					delete todelete;
					this->size--;
				}

			}
		}
	}
	int display()
	{
		if (this->first == nullptr)
		{
			cout << "\nСписок пуст\n";
			return 0;
		}
		else
		{
			int i = 1;
			node *pointer = this->first;
			do
			{
				cout << "\n" << i << " - " << pointer->subject << ": " << pointer->grade << "\n";
				++i;
				pointer = pointer->next;
			} while (pointer != nullptr);
			return 1;
		}
	}
};

struct student
{
	string faculty;
	string group;
	string full_name[3];
	int addmission_date[3];
	list grades;

	//перевод на другой факультет, перевод в другую группу, изменение фамилии,
	//изменение даты, добавление оценки, удаление из списка оценки, вывод на экран информации о студенте
	void change_faculty();
	void change_group();
	void change_full_name();
	void change_second_name();
	void change_addmission_date();
	void add_grade();
	void remove_grade();
	void display();
	void redefine();
};

void student::change_faculty()
{
	cout << "\nТекущий факультет: ";
	cout << this->faculty;
	string ans;
	cout << "\nВведите новый факультет: ";
	getline(cin, ans);
	this->faculty = ans;
	cout << "\nfaculty изменено\n";
	cin.ignore(1, '\n');
}

void student::change_group()
{
	cout << "\nТекущая группа: ";
	cout << this->group;
	string ans;
	cout << "\nВведите новую группу: ";
	getline(cin, ans);
	this->group = ans;
	cout << "\ngroup изменено\n";
	cin.ignore(1, '\n');
}

void student::change_full_name()
{
	cout << "\nТекущее именование: ";
	cout << this->full_name[0] << " " << this->full_name[1] << " " << this->full_name[2];
	string ans;
	cout << "\nВведите новое Имя: ";
	getline(cin, ans);
	this->full_name[0] = ans;
	cout << "\nВведите новую Фамилию: ";
	getline(cin, ans);
	this->full_name[1] = ans;
	cout << "\nВведите новое Отчество: ";
	getline(cin, ans);
	this->full_name[2] = ans;
	cout << "\nfull_name изменено\n";
	cin.ignore(1, '\n');
}

void student::change_second_name()
{
	cout << "\nТекущая Фамилия: ";
	cout << this->full_name[1];
	string ans;
	cout << "\nВведите новую Фамилию: ";
	getline(cin, ans);
	this->full_name[1] = ans;
	cin.ignore(1, '\n');
	cout << "\nfull_name[1] изменено\n";
	cin.ignore(1, '\n');
}

void student::change_addmission_date()
{
	cout << "\nТекущая дата поступления: ";
	cout << this->addmission_date[0] << "." << this->addmission_date[1] << "." << this->addmission_date[2];
	int ans;
	cout << "\nВведите новый День: ";
	cin >> ans;
	this->addmission_date[0] = ans;
	cin.ignore(1, '\n');
	cout << "\nВведите новый месяц: ";
	cin >> ans;
	this->addmission_date[1] = ans;
	cin.ignore(1, '\n');
	cout << "\nВведите новый год: ";
	cin >> ans;
	this->addmission_date[2] = ans;
	cin.ignore(1, '\n');
	cout << "\naddmission_date изменено\n";
}

void student::add_grade()
{
	string subject_name;
	int subject_grade;
	cout << "\nВведите название предмета: ";
	getline(cin, subject_name);
	cout << "\nВведите оценку: ";
	cin >> subject_grade;
	this->grades.pushfront(subject_name, subject_grade);
	cout << "\ngrades: item added\n";
	cin.ignore(1, '\n');
}

void student::remove_grade()
{
	this->grades.initiate_removal();
}

void student::display()
{
	//system("cls");

	cout << "\n\tВы просматриваете информацию о ";
	cout << this->full_name[0] << " " << this->full_name[1] << " " << this->full_name[2];

	cout << "\nДата поступления: ";
	cout << this->addmission_date[0] << "." << this->addmission_date[1] << "." << this->addmission_date[2];

	cout << "\nФакультет: " << this->faculty;

	cout << "\nГруппа: " << this->group;

	cout << "\nПредметы:\n";
	this->grades.display();
}

void student::redefine()
{
	this->change_full_name();
	this->change_addmission_date();
	this->change_faculty();
	this->change_group();
}

int main()
{
	setlocale(LC_ALL, "");
	student A;
	A.redefine();
	A.display();
	A.add_grade();
	A.add_grade();
	A.add_grade();
	A.display();

	system("pause>>void");
}