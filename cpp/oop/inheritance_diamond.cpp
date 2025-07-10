#include <random>

#include <iomanip>
#include <iostream>
////////////////////////////////////////
// Задание 1

class nucleon
{
private:
	int fundamentality;
public:
	nucleon()
	{
		std::cout << "\nConstructor for <nucleon>" << this;
		this->fundamentality = 0;
		create_matter();
	}
	~nucleon()
	{
		std::cout << "\nDestructor for <nucleon>" << this;
	}
	void create_matter()
	{
		this->fundamentality++;
	}
	int borrow_matter()
	{
		return this->fundamentality;
	}
	void display()
	{
		std::cout << "\nНуклон: " << this->fundamentality;
	}
};

class electron
{
private:
	int fundamentality;
public:
	electron()
	{
		std::cout << "\nConstructor for <electron>" << this;
		this->fundamentality = 0;
		create_matter();
	}
	~electron()
	{
		std::cout << "\nDestructor for <electron>" << this;
	}
	void create_matter()
	{
		this->fundamentality++;
	}
	int borrow_matter()
	{
		return this->fundamentality;
	}
	void display()
	{
		std::cout << "\nЭлектрон: " << this->fundamentality;
	}
};

class atom1 : public nucleon
{
private:
	int fundamentality;
public:
	atom1()
	{
		std::cout << "\nConstructor for <atom1>" << this;
		this->fundamentality = 0;
		create_matter();
	}
	~atom1()
	{
		std::cout << "\nDestructor for <atom1>" << this;
	}
	void create_matter()
	{
		atom1 *pointer = this;
		nucleon *nucleon_parent = dynamic_cast<nucleon*>(pointer);
		this->fundamentality += nucleon_parent->borrow_matter();
	}
	void display()
	{
		this->nucleon::display();
		std::cout << "\nАтом 1: " << this->fundamentality;
	}
};

class atom2 : protected nucleon, public electron
{
private:
	int fundamentality;
public:
	atom2()
	{
		std::cout << "\nConstructor for <atom2>" << this;
		this->fundamentality = 0;
		create_matter();
	}
	~atom2()
	{
		std::cout << "\nDestructor for <atom2>" << this;
	}
	void create_matter()
	{
		atom2 *pointer = this;
		nucleon *nucleon_parent = dynamic_cast<nucleon*>(pointer);
		this->fundamentality += nucleon_parent->borrow_matter();
		electron *electron_parent = dynamic_cast<electron*>(pointer);
		this->fundamentality += electron_parent->borrow_matter();
	}
	int borrow_matter()
	{
		int toreturn = 0;
		toreturn += this->nucleon::borrow_matter();
		toreturn += this->electron::borrow_matter();
		return toreturn;
	}
	void display()
	{
		this->nucleon::display();
		this->electron::display();
		std::cout << "\nАтом 2: " << this->fundamentality;
	}
};

class molecule : public atom1, protected atom2
{
private:
	int fundamentality;
public:
	molecule()
	{
		std::cout << "\nConstructor for <molecule>" << this;
		this->fundamentality = 0;
		create_matter();
	}
	~molecule()
	{
		std::cout << "\nDestructor for <molecule>" << this;
	}
	void create_matter()
	{
		molecule *pointer = this;
		atom1 *atom1_parent = dynamic_cast<atom1*>(pointer);
		this->fundamentality += atom1_parent->atom1::borrow_matter();
		atom2 *atom2_parent = dynamic_cast<atom2*>(pointer);
		this->fundamentality += atom2_parent->borrow_matter();
	}
	void display()
	{
		this->atom1::display();
		this->atom2::display();
		std::cout << "\nМолекула: " << this->fundamentality;
	}
};

////////////////////////////////////////
// Задание 2

class output
{
public:
	output() { std::cout << "\nConstructor for <output>" << this; }
	~output() { std::cout << "\nDestructor for <output>" << this; }
	virtual void print(int **toprint, int size) = 0;
};

class output_as_table : virtual public output
{
public:
	output_as_table() { std::cout << "\nConstructor for <output_as_table>" << this; }
	~output_as_table() { std::cout << "\nDestructor for <output_as_table>" << this; }
	void print(int **toprint, int size) override
	{
		std::cout << "\nБудьте спокойны, табличный вывод следует далее\n";
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				std::cout << std::setw(3);
				std::cout << toprint[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};

class output_as_string : virtual public output
{
public:
	output_as_string() { std::cout << "\nConstructor for <output_as_string>" << this; }
	~output_as_string() { std::cout << "\nDestructor for <output_as_string>" << this; }
	void print(int **toprint, int size) override
	{
		std::cout << "\nБудьте осторожны, строковый вывод следует далее\n";
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				std::cout << toprint[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
};

class every_output_possible : public output_as_table, public output_as_string
{
public:
	every_output_possible() { std::cout << "\nConstructor for <every_output_possible>" << this; }
	~every_output_possible() { std::cout << "\nDestructor for <every_output_possible>" << this; }
	void print(int **toprint, int size)
	{
		std::cout << "Осторожно, класс проявляет фУНкЦиоНальНОсть";
		this->output_as_string::print(toprint, size);
		this->output_as_table::print(toprint, size);
	}
	void print_table(int **toprint, int size)
	{
		std::cout << "Класс функционирует";
		this->output_as_table::print(toprint, size);
	}
	void print_string(int **toprint, int size)
	{
		std::cout << "Класс рассматривается к удалению";
		this->output_as_string::print(toprint, size);
	}
};


void menu0();
void menu1();
void menu2();
void menu_molecule();
void menu_atom1();
void menu_atom2();
void menu_electron();
void menu_nucleon();

int get_number(int from, int to)
{
	std::cin.clear();
	int answer;
	std::cin >> answer;
	while (answer < from || answer > to)
	{
		std::cout << ">> ";
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		std::cin >> answer;
	}
	return answer;
}

void menu0()
{
	while (true)
	{
		system("cls");
		std::cout << "\n_Вход |1 - Задание 1, 2 - Задание 2, 3 - Выход| >> ";
		switch (int choise = get_number(1, 3))
		{
		case 1:
		{
			menu1();
			system("pause>>void");
		}break;
		case 2:
		{
			menu2();
			system("pause>>void");
		}break;
		default: { return; }break;
		}
	}
}

void menu1()
{
	menu_molecule();
	menu_atom1();
	menu_atom2();
	menu_electron();
	menu_nucleon();
}

void menu2()
{
	srand(time(NULL));
	int size = 1 + rand() % 10;
	int **data = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			data[i][j] = rand() % 100;
		}
	}

	every_output_possible THE_HOLY_OUTPUT;
	while (true)
	{
		std::cout << "\n_Вход |1 - Воскресное поведение, 2 - Дефективное поведение, 3 - Работа класса вывода, 4 - Выход| >> ";
		switch (int choise = get_number(1, 4))
		{
		case 1:
		{
			THE_HOLY_OUTPUT.print(data, size);
		}break;
		case 2:
		{
			THE_HOLY_OUTPUT.print_string(data, size);
		}break;
		case 3:
		{
			THE_HOLY_OUTPUT.print_table(data, size);
		}break;
		default: { return; }break;
		}
	}

	for (int i = 0; i < size; ++i) { delete[] data[i]; }
	delete[] data;
}

void menu_molecule()
{
	std::cout << "\n-----------------------------\nСтруктура памяти и иерархия класса <molecule> по количеству включаемых классов\n";
	molecule m;
	m.display();
}
void menu_atom1()
{
	std::cout << "\n-----------------------------\nСтруктура памяти и иерархия класса <atom1> по количеству включаемых классов\n";
	atom1 a1;
	a1.display();
}
void menu_atom2()
{
	std::cout << "\n-----------------------------\nСтруктура памяти и иерархия класса <atom2> по количеству включаемых классов\n";
	atom2 a2;
	a2.display();
}
void menu_electron()
{
	std::cout << "\n-----------------------------\nСтруктура памяти и иерархия класса <electron> по количеству включаемых классов\n";
	electron e;
	e.display();
}
void menu_nucleon()
{
	std::cout << "\n-----------------------------\nСтруктура памяти и иерархия класса <nucleon> по количеству включаемых классов\n";
	nucleon n;
	n.display();
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	system("pause>>void");
	std::cout << "\nВыход_";
	return 0;
}