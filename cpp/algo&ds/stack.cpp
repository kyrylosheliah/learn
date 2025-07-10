#include <iostream>
#include <stdlib.h>

using namespace std;

struct integer;
struct stack;
integer *input(void);
int catch_answer(int from, int to);
int catch_integer();
void push(integer *value);
void popfront();
void getsize();
void display();
void clear();
void menu();

struct integer
{
	int value;
};

struct stack
{
	integer *data;
	stack *next;
};

stack *first = nullptr;

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

void push(integer *value)
{
	stack *toinsert = new stack;
	toinsert->data = value;
	if (first == nullptr)
	{
		toinsert->next = nullptr;
		first = toinsert;
	}
	else
	{
		toinsert->next = first;
		first = toinsert;
	}
}

void popfront()
{
	if (first == nullptr)
	{
		cout << "\tУдалять нечего" << endl;
	}
	else if (first->next == nullptr)
	{
		stack *pointer = first;
		delete pointer;
		first = nullptr;
	}
	else
	{
		stack *pointer = first;
		first = first->next;
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
	stack *pointer = first;
	while (pointer != nullptr)
	{
		++i;
		pointer = pointer->next;
	}
	cout << "Размер очереди равен " << i << "\n\n\n";
}

void display()
{
	stack *pointer = first;
	if (pointer == nullptr)
	{
		cout << "\n\tСтек пуст\t";
	}
	else
	{
		cout << "\n\tСтек: ";
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
		stack *pointer = first;
		first = first->next;
		delete pointer;
	}
}

void menu()
{
	system("cls");
	display();
	int answer;
	cout << "Выберите действие:\n1 - Добавить элемент (начало)\n2 - Удалить элемент (начало)\n3 - Очистить\n4 - Назад\n\nanswer: ";
	answer = catch_answer(1, 4);
	switch (answer)
	{
	case 1:
	{
		push(input());
		menu();
	}break;
	case 2:
	{
		popfront();
		menu();
	}break;
	case 3:
	{
		clear();
		menu();
	}break;
	case 4:
	{
		return;
	}break;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	stack a;

	menu();

	system("pause");
}