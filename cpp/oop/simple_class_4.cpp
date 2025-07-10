/*
7.
Метод поиска программы телепередач с минимальным количеством телепередач;
метод выводящий сведения о телепередачах, входящих в программы телепередач;
метод перемещающий телепередачу из программы в другую.
*/

#include <iostream>
#include <string>

using namespace std;

class program {
public:
	string **broadcast = nullptr;		// ассоциативный массив строк с названиями программ на канале. первый указатель обозначает, что это указатель на сам массив, а второй указатель подменяет операции между объектами string на операции между указателями.
	int size = 0;

	~program() {										// деструктор program
		for (int i = 0; i < this->size; ++i) {			// так как указатель двойной, то удаляем данные об объектах по указателям массива
			string *temp = this->broadcast[i];
			this->broadcast[i] = nullptr;
			delete temp;
		}
		string **temp = broadcast;
		this->broadcast = nullptr;
		delete temp;						// и только потом удаляем сам массив
	}

	program() {		// конструктор по умолчанию
		string **broadcast = nullptr;
		int size = 0;
	}
	program(string initialize) {		// конструктор-инициализатор
		this->size = 0;
		this->add(initialize);		// добавляет одно значение типа, массив из которого собирается хранить
	}
	program(program &other) {		// конструктор копирования
		for (int i = 0; i < other.size; ++i) {
			this->add(*other.broadcast[i]);
		}
	}
	void print() {		// метод вывода того, что находится в ассоциативном массиве данного класса
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
	void add(string new_cast) {	// метод добавления одного значение типа, массив из которого хранит, в конец
		int new_size = this->size + 1;
		string **new_broadcast = new string*[new_size];
		for (int i = 0; i < this->size; ++i) {		// в новом массиве переписываем все старые позиции
			new_broadcast[i] = this->broadcast[i];
		}
		new_broadcast[new_size - 1] = new string(new_cast);		// на последней позиции, так как new_size = this->size + 1, то там добавлемый элемент
		string **temp = this->broadcast;
		this->broadcast = new_broadcast;
		temp = nullptr;		// старый массив стираем
		this->size++;
	}
	string remove(int id) {		// метод удаления согласно позиции в массиве id 
		if ((id >= 0) && (id <= this->size)) {
			string toreturn = *this->broadcast[id];
			if (this->size == 1) {		// при условии, что элемент один
				string *temp1 = this->broadcast[0];
				delete temp1;
				string **temp2 = this->broadcast;
				this->broadcast = nullptr;
				delete[] temp2;
				this->size--;
			}
			else {		// при условии, что элементов > 1
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
		else {		// при условии, что индекс неверный, возвращаем отмеченный произвольным сигналом экземпляр возвращаемого типа
			string fail("-1");
			return fail;
		}
	}

};

class TV {
public:
	program **channel = nullptr;		// ассоциативный массив каналов с массивами-перечнями программ в нем. первый указатель обозначает, что это указатель на сам массив, а второй указатель подменяет операции между объектами program на операции между указателями.
	int size = 0;

	~TV() {									// деструктор TV
		for (int i = 0; i < this->size; ++i)		// так как указатель двойной, то удаляем данные об объектах по указателям массива
		{
			program *temp = this->channel[i];
			this->channel[i] = nullptr;
			delete temp;
		}
		program ** temp = channel;
		delete temp;					// и только потом удаляем сам массив
	}

	void print() {		// метод вывода ассоциативных масивов другого класса, которые находятся в ассоциативном массиве данного, путем вызова метода у такого класса
		if (this->size > 0) {
			cout << "Каналы в телевизоре:\n";
			for (int i = 0; i < this->size; ++i) {
				cout << "Канал №" << i + 1 << ":\n";
				this->channel[i]->print();		// медод другого класса
			}
		}
		else {
			cout << "Cписок каналов пуст\n";
		}
	}
	program *get_minimal() {		// метод нахождения канала с минимальным количеством программ в нем
		if (this->size > 0) {
			int min_index = INT_MAX;
			int min_number = INT_MAX;
			for (int i = 0; i < this->size; ++i) {
				if (this->channel[i]->size < min_number) {	// пока проходим по массиву, запоминаем позицию и значение только что обнаруженного минимального
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
	void add(program new_cast) {		// аналогично классу program
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
	program remove(int id) {		// аналогично классу program
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
	void move_broadcast(int from, int to, int broadcast_number) {		// метод перемещения из program под индексом from в program под индексом to строки с передачей под индексом broadcast_number
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

	program a("dada");
	a.add("dada");
	program b;
	b.add("adad");
	b.add("adad");
	a.print();
	b.print();
	cout << "||||||||||||||||||||||||||||||||||||||||||\n";
	TV box;
	box.add(a);
	box.add(b);
	box.print();
	cout << "||||||||||||||||||||||||||||||||||||||||||\n";
	box.move_broadcast(1, 2, 1);
	box.print();

	system("pause>>void");
}