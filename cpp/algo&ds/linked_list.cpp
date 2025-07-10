#include <iostream>
using namespace std;

int catch_answer(int, int);
void menu0();
void menu1();
void display();
void pushfront(int);
void pushback(int);
void popfront();
void popback();
void clear();
void insert(int, int);
void removeat(int);
void swap(int, int);

struct node
{
	int data;
	node* next;
	node(int data, node *next = nullptr)
	{
		this->data = data;
		this->next = next;
	}
};
node *head = nullptr;

struct dnode
{
	int data;
	dnode* prev;
	dnode* next;
	dnode(int data, dnode *prev = nullptr, dnode *next = nullptr)
	{
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};
dnode *dhead = nullptr;
dnode *tail = nullptr;

int list_size = 0;
bool connection_is_single = false, connection_is_dual = false, single_list_is_empty = true, dual_list_is_empty = true;

int catch_answer(int from, int to)
{
	int answer;

	cin >> answer;
	while (answer < from || answer > to)
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

void menu0()
{
	clear();
	system("cls");

	connection_is_single = false;
	connection_is_dual = false;

	int answer;
	cout << "Выберите тип списка:\n1 - Односвязный список\n2 - Двусвязный список\n3 - Выход из программы\n>>";
	answer = catch_answer(1, 3);

	switch (answer)
	{
	case 1:
	{
		connection_is_single = true;
	}; break;

	case 2:
	{
		connection_is_dual = true;
	}; break;

	case 3:
	{
		return;
	}; break;
	}

	menu1();
}

void menu1()
{
	display();

	int answer;
	cout << "Выберите действие:\n1 - Вставить элемент\n2 - Удалить элемент\n3 - Очистить список\n4 - Поменять элементы местами\n5 - Назад\n";
	answer = catch_answer(1, 5);

	switch (answer)
	{
	case 1:
	{
		display();
		cout << "Введите значение value и позицию index размещаемого элемента\nvalue = ";
		int value;
		cin >> value;
		cout << "\nindex = ";
		int index;
		if (list_size == 0)
		{
			index = 0;
		}
		else
		{
			index = catch_answer(0, list_size);
		}
		insert(value, index);
		menu1();
	}break;

	case 2:
	{
		display();
		if (list_size == 0)
		{
			cout << "Нечего удалять\n";
		}
		else if (list_size == 1)
		{
			popfront();
		}
		else
		{
			cout << "Введите позицию index удаляемого элемента\nindex = ";
			int index = catch_answer(0, list_size - 1);
			removeat(index);
		}
		menu1();
	}break;

	case 3:
	{
		clear();
		menu1();
	}break;
	case 4:
	{
		display();
		if (list_size == 0 || list_size == 1)
		{
		}
		else if (list_size == 2)
		{
			swap(0, 1);
		}
		else
		{
			cout << "Введите номера обмениваемых элементов\nindex1 = ";
			int index1 = catch_answer(0, list_size - 1);
			cout << "\nindex2 = ";
			int index2 = catch_answer(0, list_size - 1);
			swap(index1, index2);
		}
		menu1();
	}break;
	case 5:
	{
		menu0();
	}break;
	}

}

void display()
{
	system("cls");
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			cout << "\n\tОдносвязный список пуст\n";
			single_list_is_empty = true;
		}
		else
		{
			single_list_is_empty = false;
			node *pointer = head;
			cout << "\n\tСписок:\n";
			for (int i = 0; i < list_size; ++i)
			{
				cout << "\t" << i << ": " << pointer->data << "\n";
				pointer = pointer->next;
			}
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			cout << "\n\tДвусвязный список пуст\n";
			dual_list_is_empty = true;
		}
		else
		{
			dual_list_is_empty = false;
			dnode *pointer = dhead;
			cout << "\n\tСписок:\n";
			for (int i = 0; i < list_size; i++)
			{
				cout << "\t" << i << ": " << pointer->data << "\n";
				pointer = pointer->next;
			}
		}
	}
	cout << "\n\tРазмер списка равен " << list_size << "\n\n";
}

void pushfront(int value)
{
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			head = new node(value);
		}
		else
		{
			head = new node(value, head);
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			dhead = new dnode(value);
		}
		else
		{
			dnode *toadd = new dnode(value);
			toadd->next = dhead;
			dhead->prev = toadd;
			dhead = toadd;
		}
	}
	list_size++;
}

void pushback(int value)
{
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			head = new node(value);
		}
		else
		{
			node * pointer = head;
			while (pointer->next != nullptr)
			{
				pointer = pointer->next;
			}
			pointer->next = new node(value);
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			dhead = new dnode(value);
		}
		else
		{
			dnode * pointer = dhead;
			while (pointer->next != nullptr)
			{
				pointer = pointer->next;
			}
			dnode *toadd = new dnode(value);
			pointer->next = toadd;
			toadd->prev = pointer;
		}
	}
	list_size++;
}

void popfront()
{
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			cout << "Нечего удалять\n";
		}
		else
		{
			node *todelete = head;
			if (head->next == nullptr)
			{
				head = nullptr;
			}
			else
			{
				head = head->next;
			}
			delete todelete;
			list_size--;
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			dnode *todelete = dhead;
			if (dhead->next == nullptr)
			{
				dhead = nullptr;
			}
			else
			{
				dhead = dhead->next;
				dhead->prev = nullptr;
			}
			delete todelete;
			list_size--;
		}
	}
}

void popback()
{
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			node * todelete = head;
			if (todelete->next == nullptr)
			{
				head = nullptr;
			}
			else
			{
				while ((todelete->next)->next != nullptr);
				{
					todelete = todelete->next;
				}
				node *pointer = todelete;
				todelete = todelete->next;
				pointer->next = nullptr;
			}
			delete todelete;
			list_size--;
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			dnode * todelete = dhead;
			if (todelete->next == nullptr)
			{
				dhead = nullptr;
			}
			else
			{
				while ((todelete->next)->next != nullptr);
				{
					todelete = todelete->next;
				}
				dnode *pointer = todelete;
				todelete = todelete->next;
				pointer->next = nullptr;
			}
			delete todelete;
			list_size--;
		}
	}
}

void clear()
{
	if (connection_is_single)
	{
		if (head == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			while (head != nullptr)
			{
				node * todelete = head;
				head = head->next;
				delete todelete;
			}
		}
	}
	else if (connection_is_dual)
	{
		if (dhead == nullptr)
		{
			cout << "Нечего удалять" << endl;
		}
		else
		{
			while (dhead != nullptr)
			{
				dnode * todelete = dhead;
				dhead = dhead->next;
				delete todelete;
			}
		}
	}
	list_size = 0;
}

void insert(int value, int index = 0)
{
	if (list_size == 0 || index == 0)
	{
		pushfront(value);
	}
	else if (index == list_size)
	{
		pushback(value);
	}
	else
	{
		if (connection_is_single)
		{
			node *toinsert = new node(value);
			node *pointer1 = nullptr;
			node *pointer2 = head;
			int i = 0;
			while (i != index)
			{
				if (i == index - 1)
				{
					pointer1 = pointer2;
				}
				pointer2 = pointer2->next;
				i++;
			}
			pointer1->next = toinsert;
			toinsert->next = pointer2;
		}
		else if (connection_is_dual)
		{
			dnode *toinsert = new dnode(value);
			dnode *pointer1 = nullptr;
			dnode *pointer2 = dhead;
			int i = 0;
			while (i != index)
			{
				if (i == index - 1)
				{
					pointer1 = pointer2;
				}
				pointer2 = pointer2->next;
				i++;
			}
			pointer1->next = toinsert;
			toinsert->prev = pointer1;
			toinsert->next = pointer2;
			pointer2->prev = toinsert;
		}
		list_size++;
	}
}

void removeat(int index)
{
	if (list_size == 0)
	{
		cout << "\nУдалять нечего\n";
	}
	else if (index == 0 || list_size == 1)
	{
		popfront();
	}
	else if (index == (list_size - 1))
	{
		popback();
	}
	else
	{
		if (connection_is_single)
		{
			node * temp1 = nullptr;
			node * temp2 = nullptr;
			node * todelete = nullptr;
			node * pointer = head;
			for (int i = 0; i <= index + 1; ++i)
			{
				if (i == index - 1)
				{
					temp1 = pointer;
				}
				else if (i == index)
				{
					todelete = pointer;
				}
				else if (i == index + 1)
				{
					temp2 = pointer;
				}
				pointer = pointer->next;
			}
			temp1->next = temp2;
			delete todelete;
			list_size--;
		}
		else if (connection_is_dual)
		{
			dnode * temp1 = nullptr;
			dnode * temp2 = nullptr;
			dnode * todelete = nullptr;
			dnode * pointer = dhead;
			for (int i = 0; i < index + 1; ++i)
			{
				if (i == index - 1)
				{
					temp1 = pointer;
				}
				else if (i == index)
				{
					todelete = pointer;
				}
				else if (i == index + 1)
				{
					temp2 = pointer;
				}
				pointer = pointer->next;
			}
			temp1->next = temp2;
			temp2->prev = temp1;
			delete todelete;
			list_size--;
		}
	}
}

void swap(int index1, int index2)
{
	if (index1 == index2)
	{
	}
	else
	{
		if (connection_is_single)
		{
			int i = 0;
			node * swap1 = head;
			while (i < index1 && i < list_size)
			{
				swap1 = swap1->next;
				i++;
			}
			node* swap2 = head;
			i = 0;
			while (i < index2 && i < list_size)
			{
				swap2 = swap2->next;
				i++;
			}
			int temp;
			temp = swap1->data;
			swap1->data = swap2->data;
			swap2->data = temp;
		}
		else if (connection_is_dual)
		{
			int i = 0;
			dnode * swap1 = dhead;
			while (i < index1 && i < list_size)
			{
				swap1 = swap1->next;
				i++;
			}
			dnode* swap2 = dhead;
			i = 0;
			while (i < index2 && i < list_size)
			{
				swap2 = swap2->next;
				i++;
			}
			int temp;
			temp = swap1->data;
			swap1->data = swap2->data;
			swap2->data = temp;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	clear();
}