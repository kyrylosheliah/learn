#include <iostream>
#include <string>

using namespace std;

class worker
{
public:
	string name;
	int work_days;
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
	worker **worker_group = new worker*[0];
	int size = 0;
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
		delete todelete1;
	}
	void pushback(string toname)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
			//new_array[i] = new worker(this->worker_group[i]);
			//new_array[i] = new worker(this->worker_group[i]->name, this->worker_group[i]->work_days);
		}
		new_array[new_size - 1] = new worker(toname);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void initiate_removal(string todelete_name)
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
			for (int i = 0; i < this->size; ++i)
			{
				cout << "Текущий штат:\n";
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

int main()
{
	setlocale(LC_ALL, "");

	department A;

	A.pushback("Sergay");
	A.pushback("Sirgay");
	A.pushback("Esargay");
	A.pushback("gaymer");
	A.initiate_next_day();
	A.initiate_next_day();
	A.initiate_next_day();
	A.pushback("Vazgen");

	worker B("Rhino", 345);
	worker C;
	worker D("Elephant");
	worker E(B);


	cout << "////////////////////////\n";
	cout << "department A:\n";
	A.display();
	cout << "////////////////////////\n";
	cout << "worker B:\n";
	B.display();
	cout << "////////////////////////\n";
	cout << "worker C:\n";
	C.display();
	cout << "////////////////////////\n";
	cout << "worker D:\n";
	D.display();
	cout << "////////////////////////\n";
	cout << "worker E:\n";
	E.display();
	cout << "worker B:\n";
	B.display();
	cout << "////////////////////////\n";


	system("pause>>void");
	return 0;
}