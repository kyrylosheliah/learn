#include <iostream>
#include <stdlib.h>

using namespace std;

struct integer;
struct queue;
integer *input(void);
int catch_answer(int from, int to);
int catch_integer();
void pushfront(integer *value);
void pushback(integer *value);
void popfront();
void popback();
void getsize();
void display();
void clear();
void menu();
void queue_menu();
void dequeue_menu();

struct integer
{
	int value;
};

struct queue
{
	integer *data;
	queue *next;
};

queue *first = nullptr;
queue *last = nullptr;

integer *input(void)
{
	integer *data = new integer;
	cout << "Введите значение: ";
	data->value = catch_integer();
	return data;
}

int catch_answer(int from, int to)
{
	int answer;

	cin >> answer;
	while (answer == 0 || answer < from || answer > to)
	{
		cout << "Неверное значение\n>>";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> answer;
	}

	return answer;
}

int catch_integer()
{
	int number;

	cin >> number;
	while (number == 0)
	{
		cout << "Неверное значение\n>>";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> number;
	}

	return number;
}

void pushfront(integer *value)
{
	queue *toinsert = new queue;
	toinsert->data = value;
	if (first == nullptr && last == nullptr)
	{
		toinsert->next = nullptr;
		first = toinsert;
		last = toinsert;
	}
	else
	{
		toinsert->next = first;
		first = toinsert;
	}
}

void pushback(integer *value)
{
	queue *toinsert = new queue;
	toinsert->data = value;
	if (first == nullptr && last == nullptr)
	{
		toinsert->next = nullptr;
		first = toinsert;
		last = toinsert;
	}
	else if (first->next == nullptr)
	{
		toinsert->next = nullptr;
		first->next = toinsert;
		last = toinsert;
	}
	else
	{
		toinsert->next = nullptr;
		last->next = toinsert;
		last = toinsert;
	}
}

void popfront()
{
	if (first == nullptr && last == nullptr)
	{
		cout << "\tУдалять нечего" << endl;
	}
	else if (first->next == nullptr && last->next == nullptr)
	{
		queue *pointer = first;
		delete pointer;
		first = nullptr;
		last = nullptr;
	}
	else
	{
		queue *pointer = first;
		first = first->next;
		delete pointer;
	}
}

void popback()
{
	if (last == nullptr && last == nullptr)
	{
		cout << "\tУдалять нечего" << endl;
	}
	else if (first->next == nullptr && last->next == nullptr)
	{
		queue *pointer = first;
		delete pointer;
		first = nullptr;
		last = nullptr;
	}
	else if ((first->next)->next == nullptr && last->next == nullptr)
	{
		last = first;
		last->next = nullptr;
		queue *pointer = first;
		pointer = pointer->next;
		delete pointer;
	}
	else
	{
		queue *pointer = first;
		while ((pointer->next)->next != nullptr)
		{
			pointer = pointer->next;
		}
		last = pointer;
		last->next = nullptr;
		pointer = pointer->next;
		delete pointer;
	}
}

void getsize()
{
	if (first == nullptr)
	{
		cout << "Размер очереди равен 0\n\n\n";
		return;
	}
	int i = 0;
	queue *pointer = first;
	while (pointer != nullptr)
	{
		++i;
		pointer = pointer->next;
	}
	cout << "Размер очереди равен " << i << "\n\n\n";
}


void display()
{
	queue *pointer = first;
	if (pointer == nullptr)
	{
		cout << "\n\tОчередь пуста\t";
	}
	else
	{
		cout << "\n\tОчередь: ";
		while (pointer != nullptr)
		{
			cout << pointer->data->value << " - ";
			pointer = pointer->next;
		}
	}
	getsize();
}

void clear()
{
	while (first != nullptr)
	{
		queue *pointer = first;
		first = first->next;
		delete pointer;
	}
	last = nullptr;
}

void menu()
{
	system("cls");
	int answer;
	cout << "Выберите действие:\n1 - queue\n2 - dequeue\n3 - Выход\n\nanswer: ";
	answer = catch_answer(1, 3);
	switch (answer)
	{
	case 1: 
	{
		queue_menu();
	}break;
	case 2:
	{
		dequeue_menu();
	}break;
	}
}

void queue_menu()
{
	system("cls");
	display();
	int answer;
	cout << "Выберите действие:\n1 - Добавить элемент (конец)\n2 - Удалить элемент (начало)\n3 - Очистить\n4 - Назад\n\nanswer: ";
	answer = catch_answer(1, 4);
	switch (answer)
	{
	case 1:
	{
		pushback(input());
		queue_menu();
	}break;
	case 2:
	{
		popfront();
		queue_menu();
	}break;
	case 3:
	{
		clear();
		queue_menu();
	}break;
	case 4:
	{
		menu();
	}break;
	}
}

void dequeue_menu()
{
	system("cls");
	display();
	int answer;
	cout << "Выберите действие:\n1 - Добавить элемент в начало\n2 - Добавить элемент в конец\n3 - Удалить элемент в начале\n4 - Удалить элемент в конце\n5 - Очистить\n6 - Выход\n\nanswer: ";
	answer = catch_answer(1, 6);
	switch (answer)
	{
	case 1:
	{
		pushfront(input());
		dequeue_menu();
	}break;
	case 2:
	{
		pushback(input());
		dequeue_menu();
	}break;
	case 3:
	{
		popfront();
		dequeue_menu();
	}break;
	case 4:
	{
		popback();
		dequeue_menu();
	}break;
	case 5:
	{
		clear();
		dequeue_menu();
	}break;
	case 6:
	{
		menu();
	}break;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	queue a;

	menu();

	system("pause");
}