#include <iostream>
#include <string>

using namespace std;
// 20.	Классы цех и сотрудник(старший мастер, рабочий).
// Класс - обработчик должен вывести на экран список сотрудников, 
// которые работают в цеху более заданного количества лет и 
// обеспечить перевод сотрудника из цеха в цех.

/*Заданием на лабораторную работу является расширение программы, созданной на лабораторной работе №2.Необходимо, в соответствии с вариантом, найти сущности, для которых можно выделить базовый и производный классы.Требуется расширить программу на С++, обеспечив следующее :
−	определить базовый и производный классы;
−	выделить их общие методы;
−	определить в производном классе переопределение(замещение) некоторых методов.В переопределенном методе предусмотреть вызов метода базового класса;
−	в базовом классе предусмотреть конструктор с аргументами;
−	в производном классе задать конструктор со списком аргументов, включающим значения для передачи конструктору базового класса, конструктор базового класса вызвать в списке инициализации;
−	создать виртуальный деструктор базового класса с освобождением динамической памяти;
−	создать деструкторы в производных классах;
−	определить виртуальные методы в базовом классе; произвести их замещение в производном классе;
−	выполнить создание класса обработчика согласно варианту задания;
−	создать массив указателей на тип базового класса; определить полиморфные объекты; наполнить массив указателями на полиморфные объекты производных классов; вызвать виртуальные методы для элементов массива и проследить результат;
−	все методы классов сопровождать соответствующими комментариями, которые выводятся в поток вывода.*/

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
	virtual void next_day()
	{
		this->work_days++;
	}
	virtual bool display()
	{
		cout << "Работник. Имя: " << this->name << ", дней в штате: " << this->work_days << "\n";
		return (this->name == "ПУСТО") ? false : true;
	}
};

class security : public worker
{
public:
	security()
	{
		this->name = "ПУСТО";
		this->work_days = 0;
	}
	security(string toname, int days = 0)
	{
		this->name = toname;
		this->work_days = days;
	}
	bool display() override
	{
		cout << "Охранник. Имя: " << this->name << ", дней на посту: " << this->work_days << "\n";
		return (this->name == "ПУСТО") ? false : true;
	}
};

class trainee : public worker
{
public:
	trainee()
	{
		this->name = "ПУСТО";
		this->work_days = 0;
	}
	trainee(string toname, int days = 0)
	{
		this->name = toname;
		this->work_days = days;
	}
	bool display() override
	{
		cout << "Стажер. Имя: " << this->name << ", дней стажировки: " << this->work_days << "\n";
		return (this->name == "ПУСТО") ? false : true;
	}
};

class manager : public worker
{
private:
	worker **worker_group;
	int size;
public:
	~manager()
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
	manager()
	{
		this->name = "ПУСТО";
		this->work_days = 0;
		this->worker_group = new worker*[0];
		this->size = 0;
	}
	manager(const manager &other)
	{
		this->name = other.name;
		this->work_days = other.work_days;
		this->size = 0;
		this->worker_group = new worker*[other.size];
		for (int i = 0; i < other.size; ++i)
		{
			this->pushback(other.worker_group[i]->name, other.worker_group[i]->work_days);
		}
		this->size = other.size;
	}

	void pushback(string toname, int days = 0)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
		}
		new_array[new_size - 1] = new worker(toname, days);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void pushback(worker staff, int days = 0)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
		}
		new_array[new_size - 1] = new worker(staff.name, days);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void pushback(security staff, int days = 0)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
		}
		new_array[new_size - 1] = new security(staff.name, days);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void pushback(trainee staff, int days = 0)
	{
		int new_size = this->size + 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->worker_group[i];
		}
		new_array[new_size - 1] = new trainee(staff.name, days);
		worker ** todelete = this->worker_group;
		this->worker_group = new_array;
		delete[] todelete;
		this->size++;
	}
	void remove(string todelete_name)
	{
		string todelete_flag = "REMOVAL_INITIALIZATION_FLAG";
		int removal_amount = 0;
		for (int i = 0; i < this->size; ++i)
		{
			if (this->worker_group[i]->name == todelete_name)
			{
				this->worker_group[i]->name = todelete_flag;
				++removal_amount;
			}
		}
		if (removal_amount)
		{
			this->del(todelete_flag, removal_amount);
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
				this->del(todelete_flag, 1);
			}
		}
	}
	void del(string todelete_flag, int removal_amount)
	{
		int new_size = this->size - 1;
		worker ** new_array = new worker*[new_size];
		for (int i = 0, j = 0; i < this->size; ++i)
		{
			if (this->worker_group[i]->name == todelete_flag && removal_amount)
			{
				worker * todelete0 = this->worker_group[i];
				this->worker_group[i] = nullptr;
				delete todelete0;
				++j;
				--removal_amount;
			}
			new_array[i] = this->worker_group[i + j];
			this->worker_group[i] = nullptr;
		}
		this->worker_group = new_array;
		this->size--;
	}
	void next_day() override
	{
		this->work_days++;
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
		cout << "Ответственный за отдел - " << this->name << " со стажем " << this->work_days << "д.\n";
		for (int i = 0; i < this->size; ++i)
		{
			if (this->worker_group[i]->work_days >= days)
			{
				this->worker_group[i]->display();
			}
		}
	}
	bool display() override
	{
		cout << "Ответственный за отдел - " << this->name << " со стажем " << this->work_days << "д.\n";
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
			cout << "Штат пуст\n";
			return false;
		}
	}
};

class director : public worker
{
public:
	void next_day(manager *toincrement)
	{
		this->work_days++;
		toincrement->next_day();
	}
	void next_day(manager *toincrement_first, manager *toincrement_second)
	{
		this->work_days++;
		toincrement_first->next_day();
		toincrement_second->next_day();
	}
	void move(string first_worker_to_swap_name, string second_worker_to_swap_name, manager *first_worker_department, manager *second_worker_department)
	{
		cout << "\n" << this->name << " что-то мутит...\n";
		string worker1 = first_worker_to_swap_name;
		string worker2 = second_worker_to_swap_name;
		first_worker_department->remove(worker1);
		second_worker_department->remove(worker2);
		first_worker_department->pushback(worker2);
		second_worker_department->pushback(worker1);
	}
	void display(manager *in_which_i_look, int expirience_days)
	{
		cout << "\n" << this->name << ", управляющий со стажем "<<this->work_days<< " д., ищет людей со стажем больше, чем "<<expirience_days<<" д., по данному отделу:\n";
		if (in_which_i_look->expirienced_count(expirience_days))
		{
			in_which_i_look->expirienced_display(expirience_days);
		}
		else
		{
			cout << "\nВ данном отделе пусто. У " << this->name << " беды с башкой.\n";
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");

	cout << "\n/////////////////////\nНаследование полей\n";
	int slavery = 1000;
	double death_factor = 1.0;
	double death_increment = 0.01;

	manager *A = new manager;
	manager *b = new manager;
	A->rename("Вазген Большой");
	b->rename("Вазген Малый");
	director C;
	C.rename("Вазген Царь Людей Царь Зверей");

	A->pushback("Первый А");
	b->pushback("Первый Б");
	for (int i = 0; i < slavery / death_factor; ++i)
	{
		C.next_day(A, b);
		death_factor += death_increment;
	}
	A->pushback("Второй А");
	b->pushback("Второй Б");
	for (int i = 0; i < slavery / death_factor; ++i)
	{
		C.next_day(A, b);
		death_factor += death_increment;
	}
	A->pushback("Третий А");
	b->pushback("Третий Б");
	for (int i = 0; i < slavery / death_factor; ++i)
	{
		C.next_day(A, b);
		death_factor += death_increment;
	}

	C.display(A, slavery/death_factor);
	C.display(b, slavery/death_factor);

	cout << "\n/////////////////////\nОбмен между отделами\n";
	C.move("Первый А", "Первый Б", A, b);
	C.display(A, 0);
	C.display(b, 0);

	cout << "\n/////////////////////\nПолиморфизм полей\n";
	manager *D = new manager;
	D->rename("Вазген Корпоративнич");
	worker new_worker1("Рабочий отдела Д", 100);
	security new_worker2("Охранник отдела Д", 200);
	trainee new_worker3("Стажер отдела Д", 300);
	D->pushback(new_worker1);
	D->pushback(new_worker2);
	D->pushback(new_worker3);
	C.display(D, 0);

	delete A;
	delete b;
	system("pause>>void");
}