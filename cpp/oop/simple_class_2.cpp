//20.	Классы цех и сотрудник. Класс-обработчик должен вывести на экран список сотрудников, 
//которые работают в цеху более заданного количества лет и обеспечить перевод сотрудника из цеха в цех. 

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
		this->name = "blank";
		work_days = 0;
	}
	worker(string toname)
	{
		this->name = toname;
		work_days = 0;
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
		delete[] todelete1;
	}
	int getsize()
	{
		return this->size;
	}
	void pushback(string toname)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
		}
		new_array[new_size - 1] = new worker;
		new_array[new_size - 1]->work_days = 0;
		new_array[new_size - 1]->name = toname;
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void initiate_removal(string todelete_name)
	{
		if (this->size == 0)
		{
			cout << "\nЦех пуст\n";
		}
		else if (this->size == 1)
		{
			if (this->worker_group[0]->name == todelete_name)
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
				cout << "\nРаботник не найден\n";
			}
		}
		else
		{
			string todelete_flag = "removal_initialization_flag";
			bool worker_found_flag = false;
			for (int i = 0; i < this->size; ++i)
			{
				if (this->worker_group[i]->name == todelete_name)
				{
					this->worker_group[i]->name = todelete_flag;
					worker_found_flag = true;
				}
			}
			if (worker_found_flag)
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
				}
				this->worker_group = new_array;
				this->size--;
			}
			else
			{
				cout << "\nРаботник не найден\n";
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
	int expirienced_count(int days)
	{
		if (this->size == 0)
		{
			return 0;
		}
		else
		{
			int counter = 0;
			for (int i = 0; i < this->size; ++i)
			{
				if (this->worker_group[i]->work_days >= days)
				{
					++counter;
				}
			}
			return counter;
		}
	}
	void expirienced_display(int days)
	{
		if (this->expirienced_count(days))
		{
			for (int i = 0; i < this->size; ++i)
			{
				if (this->worker_group[i]->work_days >= days)
				{
					this->worker_group[i]->display();
				}
			}
		}
		else
		{
			cout << "\nРезультаты поиска неутешительны\n";
		}
	}
	void display()
	{
		for (int i = 0; i < this->size; ++i)
		{
			cout << "Штат сотрудников:\n";
			cout << i+1 << " - ";
			this->worker_group[i]->display();
		}
	}
};

class director
{
public:
	void initiate_next_day(department *toincrement)
	{
		toincrement->initiate_next_day();
	}
	void move(string first_worker_to_swap_name, string second_worker_to_swap_name, department *first_worker_department, department *second_worker_department)
	{
		string worker1 = first_worker_to_swap_name;
		string worker2 = second_worker_to_swap_name;
		first_worker_department->initiate_removal(worker1);
		second_worker_department->initiate_removal(worker2);
		first_worker_department->pushback(worker2);
		second_worker_department->pushback(worker1);
	}
	void display_by_expirience_term(department *in_which_i_look, int expirience_days)
	{
		cout << "Результат поиска по данному отделу:\n";
		if (in_which_i_look->expirienced_count(expirience_days))
		{
			in_which_i_look->expirienced_display(expirience_days);
		}
		else
		{
			cout << "\nВ этом отделе пусто. Для начала наберите штат.\n";
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");

	department *A = new department;
	director C;

	A->pushback("Vasya0");
	A->pushback("Vasya1");
	A->pushback("Vaz2109");
	C.initiate_next_day(A);
	C.initiate_next_day(A);
	C.initiate_next_day(A);
	A->pushback("Vazbergerg");
	A->pushback("Vazelopa");
	C.initiate_next_day(A);
	C.initiate_next_day(A);
	C.initiate_next_day(A);
	C.initiate_next_day(A);
	A->pushback("Vazgena");
	C.initiate_next_day(A);
	A->pushback("Vazgen");

	C.display_by_expirience_term(A, 5);
	
	cout << "\n//////////////////////////////////////////////////////////////\n\n";

	department *B = new department;

	string A_test = "A_worker";
	string B_test = "B_worker";
	A->pushback(A_test);
	B->pushback(B_test);

	C.move(A_test, B_test, A, B);
	cout << "��������� ������ A\n";
	C.display_by_expirience_term(A, 0);
	cout << "\n��������� ������ B\n";
	C.display_by_expirience_term(B, 0);

	delete A;
	delete B;
	system("pause>>void");
	return 0;
}