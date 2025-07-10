#include <iostream>
#include <string>

using namespace std;

// 1. Дополнить определение класса (предыдущая лабораторная работа) следующими перегруженными операциями (+, - , <, >, =, +=).
// 2. Реализуйте эти операции.Выполните тестирование.Результаты тестирования представьте в отчете.

class worker
{
public:
	string name;
	int work_days;

	worker operator + (worker &other)
	{
		this->name = this->name + " & " + other.name;
		this->work_days += other.work_days;
		return *this;
	}
	worker operator - (worker &other)
	{
		int n;
		while ((n = this->name.find(other.name)) != this->name.npos)
		{
			this->name.erase(n, other.name.size());
		}
		this->work_days = this->work_days - other.work_days;
		return *this;
	}
	bool operator < (worker &other)
	{
		return (this->work_days < other.work_days) ? true : false;
	}
	bool operator > (worker &other)
	{
		return (this->work_days > other.work_days) ? true : false;
	}
	bool operator == (worker &other)
	{
		return (this->name == other.name && this->work_days == other.work_days) ? true : false;
	}
	worker operator = (worker other)
	{
		this->name = other.name;
		this->work_days = other.work_days;
		return *this;
	}
	worker operator += (worker &other)
	{
		this->name = this->name + " " + other.name;
		this->work_days += other.work_days;
		return *this;
	}
	worker operator -= (worker &other)
	{
		int n;
		while ((n = this->name.find(other.name)) != this->name.npos)
		{
			this->name.erase(n, other.name.size());
		}
		this->work_days -= other.work_days;
		return *this;
	}

	worker()
	{
		this->name = "ПУСТО";
		work_days = 0;
	}
	worker(string toname)
	{
		this->name = toname;
		work_days = 0;
	}
	worker(string toname, int days)
	{
		this->name = toname;
		work_days = days;
	}
	worker(const worker &other)
	{
		this->name = other.name;
		this->work_days = other.work_days;
	}
	void rename(string toname)
	{
		this->name = toname;
	}
	void next_day()
	{
		this->work_days++;
	}
	void display()
	{
		cout << "Имя: " << this->name << ", дней в штате: " << this->work_days << "\n";
	}
};

class department
{
private:
	worker **worker_group;
	int size;
public:
	~department()
	{
		for (int i = 0; i < this->size; ++i)
		{
			worker *todelete0 = this->worker_group[i];
			this->worker_group[i] = nullptr;
			delete todelete0;
		}
		worker ** todelete1 = worker_group;
		delete[] todelete1;
	}
	department()
	{
		this->worker_group = new worker*[0];
		this->size = 0;
	}
	department (const department &other)
	{
		this->size = 0;
		this->worker_group = new worker*[other.size];
		for (int i = 0; i < other.size; ++i)
		{
			this->pushback(other.worker_group[i]->name, other.worker_group[i]->work_days);
		}
		this->size = other.size;
	}
	department operator + (department other)
	{
		for (int i = 0; i < other.size; ++i)
		{
			this->pushback(other.worker_group[i]->name);
		}
		return *this;
	}
	bool operator < (department &other)
	{
		int this_hours_count = 0, other_hours_count = 0;
		for (int i = 0; i < this->size; ++i)
		{
			this_hours_count += this->worker_group[i]->work_days;
		}
		for (int i = 0; i < other.size; ++i)
		{
			other_hours_count += other.worker_group[i]->work_days;
		}
		if (this_hours_count > other_hours_count)
		{
			cout << "\nПервый Штат наработал " << this_hours_count << " часов, что на " << this_hours_count - other_hours_count << " часов больше второго\n";
		}
		else
		{
			cout << "\nВторой Штат наработал " << other_hours_count << " часов, что на " << other_hours_count - this_hours_count << " часов больше первого\n";
		}
		return (this_hours_count < other_hours_count) ? true : false;
	}
	bool operator > (department &other)
	{
		int this_hours_count = 0, other_hours_count = 0;
		for (int i = 0; i < this->size; ++i)
		{
			this_hours_count += this->worker_group[i]->work_days;
		}
		for (int i = 0; i < other.size; ++i)
		{
			other_hours_count += other.worker_group[i]->work_days;
		}
		if (this_hours_count > other_hours_count)
		{
			cout << "\nПервый Штат наработал " << this_hours_count << " часов, что на " << this_hours_count - other_hours_count << " часов больше второго\n";
		}
		else
		{
			cout << "\nВторой Штат наработал " << other_hours_count << " часов, что на " << other_hours_count - this_hours_count << " часов больше первого\n";
		}
		return (this_hours_count > other_hours_count) ? true : false;
	}
	department operator = (department &other)
	{
		for (int i = 0; i < this->size; ++i)
		{
			worker *todelete0 = this->worker_group[i];
			this->worker_group[i] = nullptr;
			delete todelete0;
		}
		this->size = 0;
		worker ** todelete1 = worker_group;
		worker_group = nullptr;
		delete[] todelete1;

		for (int i = 0; i < other.size; ++i)
		{
			this->pushback(other.worker_group[i]->name, other.worker_group[i]->work_days);
		}

		return *this;
	}
	department operator += (department &other)
	{
		for (int i = 0; i < other.size; ++i)
		{
			this->pushback(other.worker_group[i]->name, other.worker_group[i]->work_days);
		}

		return *this;
	}
	department operator -= (department &other)
	{
		for (int i = 0; i < other.size; ++i)
		{
			for (int j = 0; j < this->size; ++j)
			{
				if (this->worker_group[j]->name == other.worker_group[i]->name)
				{
					this->remove(other.worker_group[i]->name);
				}
			}
		}
		return *this;
	}

	void pushback(string toname, int days = 0)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
			//new_array[i] = new worker(this->worker_group[i]);
			//new_array[i] = new worker(this->worker_group[i]->name, this->worker_group[i]->work_days);
		}
		new_array[new_size - 1] = new worker(toname, days);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void remove(string todelete_name)
	{
		bool found_flag = false;
		string todelete_flag = "REMOVAL_INITIALIZATION_FLAG";
		for (int i = 0; i < this->size; ++i)
		{
			if (this->worker_group[i]->name == todelete_name)
			{
				this->worker_group[i]->name = todelete_flag;
				found_flag = true;
			}
		}
		if (found_flag)
		{
			int new_size = this->size - 1;
			worker ** new_array = new worker*[new_size];
			for (int i = 0, j = 0; i + j < new_size; ++i)
			{
				if (this->worker_group[i]->name == todelete_flag)
				{
					++j;
				}
				new_array[i] = this->worker_group[i];
				//new_array[i] = new worker(this->worker_group[i]);
				//new_array[i] = new worker(this->worker_group[i]->name, this->worker_group[i]->work_days);
			}
			this->worker_group = new_array;
			this->size--;
		}
	}
	void initiate_removal()
	{
		if (this->display())
		{
			if (this->size == 1)
			{
				worker *todelete0 = this->worker_group[0];
				delete todelete0;
				worker ** todelete1 = this->worker_group;
				this->worker_group = nullptr;
				delete[] todelete1;
				this->size--;
			}
			else
			{
				cout << "\nВыберите номер удаляемого элемента:\n";
				int answer;
				cin >> answer;
				while (answer < 1 || answer > this->size)
				{
					cout << ">> ";
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(256, '\n');
					}
					cin >> answer;
				}
				string todelete_flag = "REMOVAL_INITIALIZATION_FLAG";
				this->worker_group[answer - 1]->name = todelete_flag;
				int new_size = this->size - 1;
				worker ** new_array = new worker*[new_size];
				for (int i = 0, j = 0; i + j < new_size; ++i)
				{
					if (this->worker_group[i]->name == todelete_flag)
					{
						++j;
					}
					new_array[i] = this->worker_group[i];
					//new_array[i] = new worker(this->worker_group[i]);
					//new_array[i] = new worker(this->worker_group[i]->name, this->worker_group[i]->work_days);
				}
				this->worker_group = new_array;
				this->size--;
			}
		}
	}
	void initiate_next_day()
	{
		if (this->size == 0)
		{
			cout << "\nВ этом отделе пусто. Для начала наберите штат.\n";
		}
		else
		{
			for (int i = 0; i < this->size; ++i)
			{
				this->worker_group[i]->next_day();
			}
		}
	}
	bool display()
	{
		if (this->size > 0)
		{
			cout << "Текущий штат:\n";
			for (int i = 0; i < this->size; ++i)
			{
				cout << i + 1 << " - ";
				this->worker_group[i]->display();
			}
			return true;
		}
		else
		{
			cout << "\nШтат пуст\n";
			return false;
		}
	}
};


void display(worker a, worker b)
{
	cout << "\nРаботник а: " << a.name << ", " << a.work_days << " дней\nРаботник б: " << b.name << ", " << b.work_days << " дней";
}
void display(department *a, department *b)
{
	a->display();
	b->display();
}

int main()
{
	setlocale(LC_ALL, "");
	cout << "Операции над работниками\n";

	cout << "\n////////////////////////////////////\n";
	worker a1("Работник а", 100);
	worker b1("Работник б", 50);
	display(a1, b1);
	a1 = a1 + b1;
	cout << "\n+";
	display(a1, b1);

	cout << "\n////////////////////////////////////\n";
	worker a2("Работник а", 100);
	worker b2("Работник б", 50);
	display(a2, b2);
	a2 = a2 - b2;
	cout << "\n-";
	display(a2, b2);

	cout << "\n////////////////////////////////////\n";
	cout << "\n>\n";
	worker a3("Работник а", 100);
	worker b3("Работник б", 50);
	display(a3, b3);
	if (a3 > b3)
	{
		cout << a3.name << " работал больше на "<< a3.work_days - b3.work_days<<" дней, чем " << b3.name;
	}

	cout << "\n////////////////////////////////////\n";
	worker a4("Работник а", 100);
	worker b4(a4);
	display(a4, b4);
	a4 = b4;
	cout << "\n==\n";
	if (a4 == b4)
	{
		cout << "Равенство достигнуто, социализм, уравнение!";
	}

	cout << "\n////////////////////////////////////\n";
	worker a5("Работник а", 100);
	worker b5("Работник б", 50);
	display(a5, b5);
	a5 = b5;
	cout << "\n=";
	display(a5, b5);

	cout << "\n////////////////////////////////////\n";
	worker a6("Работник а", 100);
	worker b6("Работник б", 50);
	display(a6, b6);
	a6 += b6;
	cout << "\n+=";
	display(a6, b6);


	cout << "\n--------------------------------------------\nОперации над отделами\n";

	cout << "\n////////////////////////////////////\n";
	department *A1 = new department;
	A1->pushback("A1 worker", 1);
	department *B1 = new department;
	B1->pushback("B1 worker", 2);
	display(A1, B1);
	cout << "+=\n";
	*A1 += *B1;
	display(A1, B1);
	delete A1;
	delete B1;

	cout << "\n////////////////////////////////////\n";
	department *A2 = new department;
	A2->pushback("A1 worker", 1);
	department *B2 = new department;
	B2->pushback("A1 worker", 2);
	display(A2, B2);
	cout << "-";
	*A2 -= *B2;
	display(A2, B2);
	delete A2;
	delete B2;

	cout << "\n////////////////////////////////////\n";
	department *A3 = new department;
	A3->pushback("A1 worker", 666);
	department *B3 = new department;
	B3->pushback("B1 worker", 2);
	display(A3, B3);
	cout << ">\n";
	*A3 > *B3;
	delete A3;
	delete B3;

	cout << "\n////////////////////////////////////\n";
	department *A4 = new department;
	A4->pushback("A1 worker", 1);
	department *B4 = new department;
	B4->pushback("B1 worker", 2);
	display(A4, B4);
	cout << "=\n";
	*A4 = *B4;
	display(A4, B4);
	delete A4;
	delete B4;


	system("pause>>void");
	return 0;
}