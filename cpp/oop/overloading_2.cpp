/*   7.
Метод поиска программы телепередач с минимальным количеством телепередач;
метод выводящий сведения о телепередачах, входящих в программы телепередач;
метод перемещающий телепередачу из программы в другую.

Дополнить определение класса (предыдущая лабораторная работа) следующими перегруженными операциями (+, - , <, >, =, +=).
*/

#include <iostream>
#include <string>
using namespace std;

class program {
public:
	string **broadcast = nullptr;
	int size = 0;

	~program() {
		for (int i = 0; i < this->size; ++i) {
			string *temp = this->broadcast[i];
			this->broadcast[i] = nullptr;
			delete temp;
		}
		string **temp = broadcast;
		this->broadcast = nullptr;
		delete temp;
	}

	program &operator + (const program &other)	// т.к. оба класса program содержат массивы, то создадим новый класс в памяти с элементами из массивов обоих классов
	{
		program *toreturn = new program;
		for (int i = 0; i < this->size; ++i) {
			toreturn->add(*this->broadcast[i]);
		}
		for (int i = 0; i < other.size; ++i) {
			toreturn->add(*other.broadcast[i]);
		}
		return *toreturn;
	}
	program &operator - (const program &other)		// т.к. оба класса program содержат массивы, то создадим новый класс в памяти с удаленим из него элемента, который совпадает
	{
		program *toreturn = new program(*this);
		bool found_flag;
		do {
			found_flag = 0;
			for (int i = 0; i < toreturn->size; ++i) {
				for (int j = 0; j < other.size; ++j) {
					if (*toreturn->broadcast[i] == *other.broadcast[j]) {		// разовое удаление обусловлено циклом do{}while; и применением флага
						found_flag = 1;
						toreturn->remove(i + 1);
					}
				}
			}
		} while (found_flag);
		return *toreturn;
	}
	bool operator < (const program &other)		// сравним размеры массивов в классах - program::size
	{
		return this->size < other.size;
	}
	bool operator > (const program &other)		// сравним размеры массивов в классах - program::size
	{
		return this->size > other.size;
	}
	bool operator == (const program &other)		// сравним размеры массивов в классах - program::size
	{
		return this->size == other.size;
	}
	program &operator = (const program other)		// добавим элементы массива правостороннего значения левостороннему, т.е. this
	{
		// забыл дописать предварительную очистку
		for (int i = 0; i < other.size; ++i) {
			this->add(*other.broadcast[i]);
		}
		return *this;
	}
	program &operator += (const program &other)		// добавим элементы массива правостороннего значения левостороннему, т.е. this
	{
		for (int i = 0; i < other.size; ++i) {
			this->add(*other.broadcast[i]);
		}
		return *this;
	}
	program &operator -= (const program &other)		// т.к. оба класса program содержат массивы, то удалим из массива левостороннего program элемент, который совпадает с таковым в правостороннем
	{
		bool found_flag;
		do {
			found_flag = 0;
			for (int i = 0; i < this->size; ++i) {
				for (int j = 0; j < other.size; ++j) {
					if (*this->broadcast[i] == *other.broadcast[j]) {		// разовое удаление обусловлено циклом do{}while; и применением флага
						found_flag = 1;
						this->remove(i + 1);
						i = this->size; j = other.size;
					}
				}
			}
		} while (found_flag);
		return *this;
	}

	program() {
		string **broadcast = nullptr;
		int size = 0;
	}
	program(string initialize) {
		this->size = 0;
		this->add(initialize);
	}
	program(program &other) {
		for (int i = 0; i < other.size; ++i) {
			this->add(*other.broadcast[i]);
		}
	}
	void print() {
		if (this->size > 0) {
			cout << "Телепередачи на канале:\n";
			for (int i = 0; i < this->size; ++i) {
				cout << i + 1 << ") " << *this->broadcast[i] << "\n";
			}
		}
		else {
			cout << "Канал пуст\n";
		}
	}
	void add(string new_cast) {
		int new_size = this->size + 1;
		string **new_broadcast = new string*[new_size];
		for (int i = 0; i < this->size; ++i) {
			new_broadcast[i] = this->broadcast[i];
		}
		new_broadcast[new_size - 1] = new string(new_cast);
		string **temp = this->broadcast;
		this->broadcast = new_broadcast;
		temp = nullptr;
		this->size++;
	}
	string remove(int id) {
		if ((id >= 0) && (id <= this->size)) {

			string toreturn = *this->broadcast[id];
			if (this->size == 1) {
				string *temp1 = this->broadcast[0];
				delete temp1;
				string **temp2 = this->broadcast;
				this->broadcast = nullptr;
				delete[] temp2;
				this->size--;
			}
			else {
				int new_size = this->size - 1;
				string ** new_array = new string*[new_size];
				for (int i = 0, j = 0; i < new_size; ++i) {
					if (i == id - 1) {
						++j;
					}
					new_array[i] = this->broadcast[i + j];
				}
				this->broadcast = new_array;
				this->size--;
			}
			return toreturn;
		}
		else {
			string fail("-1");
			return fail;
		}
	}

};

class TV {
public:
	program **channel = nullptr;
	int size = 0;

	~TV() {
		for (int i = 0; i < this->size; ++i)
		{
			program *temp = this->channel[i];
			this->channel[i] = nullptr;
			delete temp;
		}
		program ** temp = channel;
		delete temp;
	}

	void print() {
		if (this->size > 0) {
			cout << "Каналы в телевизоре:\n";
			for (int i = 0; i < this->size; ++i) {
				cout << "Канал №" << i + 1 << ":\n";
				this->channel[i]->print();
			}
		}
		else {
			cout << "Cписок каналов пуст\n";
		}
	}
	program *get_minimal() {
		if (this->size > 0) {
			int min_index = INT_MAX;
			int min_number = INT_MAX;
			for (int i = 0; i < this->size; ++i) {
				if (this->channel[i]->size < min_number) {
					min_index = i;
					min_number = this->channel[i]->size;
				}
			}
			return this->channel[min_index];
		}
		else {
			cout << "\nПрограмма пуста, выбрать нечего\n";
		}
	}
	void add(program new_cast) {
		int new_size = this->size + 1;
		program **new_broadcast = new program*[new_size];
		for (int i = 0; i < this->size; ++i) {
			new_broadcast[i] = this->channel[i];
		}
		new_broadcast[new_size - 1] = new program(new_cast);
		program **temp = this->channel;
		this->channel = new_broadcast;
		delete[] temp;
		this->size++;
	}
	program remove(int id) {
		if ((id >= 0) && (id < this->size)) {
			program toreturn = *this->channel[id];
			if (this->size == 1) {
				program *temp1 = this->channel[0];
				delete temp1;
				program **temp2 = this->channel;
				this->channel = nullptr;
				delete[] temp2;
				this->size--;
			}
			else {
				int new_size = this->size - 1;
				program ** new_array = new program*[new_size];
				for (int i = 0, j = 0; i < new_size; ++i) {
					if (i == id - 1) {
						++j;
					}
					new_array[i] = this->channel[i + j];
				}
				this->channel = new_array;
				this->size--;
			}
			return toreturn;
		}
		else {
			program fail("-1");
			return fail;
		}
	}
	void move_broadcast(int from, int to, int broadcast_number) {
		if ((from > 0) && (from <= this->size) && (to > 0) && (to - 1 < this->size)) {
			int size_from = this->channel[from - 1]->size;
			if ((broadcast_number > 0) && (broadcast_number - 1 < size_from)) {
				string swap = this->channel[from - 1]->remove(broadcast_number);
				this->channel[to - 1]->add(swap);
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "");

	program a("a");
	program b("b");
	program r1 = a + b;
	r1.print();
	cout << "||||||||||||||||||||||||||||||||||||||||||\n";
	program r2 = r1 - a;
	r2.print();
	cout << "||||||||||||||||||||||||||||||||||||||||||\n";
	bool r3 = r1 > r2;
	cout << "r3 = r1 > r2 = " << r3;
	cout << "\n||||||||||||||||||||||||||||||||||||||||||\n";
	bool r4 = r2 == b;
	cout << "r4 = r2 == b = " << r4;
	cout << "\n||||||||||||||||||||||||||||||||||||||||||\n";
	program c;
	c += a; c += b; c += r1; c += r2;
	c.print();
	cout << "||||||||||||||||||||||||||||||||||||||||||\n";
	c -= a;
	c.print();

	system("pause>>void");
}