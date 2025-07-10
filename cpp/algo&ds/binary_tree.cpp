
// 21 -	Написати функцію, яка визначає, чи є у бінарному дереві хоч би два однакові елементи

#include <iostream>

using namespace std;

struct node 
{
	int data;
	node *left = nullptr, *right = nullptr;
};
node *root = nullptr;

void tree_walk_straight(node *pointer);
void tree_walk_reverse(node *pointer);
void tree_walk_ending(node *pointer);
node *push(int value, node *pointer);
node *search(int value, node *pointer);
void continuous_queue_pop(node *pointer, int mem[], const int size);
void pop_value(int value, node *pointer);
void display(node *pointer);
int node_number(node* tree);
int leaf_count(node* pointer);
void clear(node *pointer);
void occurences_counting(int **arr, const int size, node *pointer);
void menu();

void tree_walk_straight(node *pointer = root)		//Обход дерева сверху вниз (прямой обход, префиксная форма)
{
	if (pointer)
	{
		cout << pointer->data<<" ";
		tree_walk_straight(pointer->left);
		tree_walk_straight(pointer->right);
	}
}

void tree_walk_reverse(node *pointer = root)		//Обод дерева снизу вверх (обратный обход, инфиксная форма)
{
	if (pointer)
	{
		tree_walk_reverse(pointer->left);
		cout << pointer->data << " ";
		tree_walk_reverse(pointer->right);
	}
}

void tree_walk_ending(node *pointer = root)	//Обход дерева слева направо (конечный порядок, постфиксная форма)
{
	if (pointer)
	{
		tree_walk_ending(pointer->left);
		tree_walk_ending(pointer->right);
		cout << pointer->data << " ";
	}
}

node *push(int value, node *pointer = root)	//Добавление листка величины x 
{
	if (root == nullptr) 
	{
		node *toadd = new node;
		toadd->data = value;
		toadd->left = nullptr;
		toadd->right = nullptr;
		root = toadd;
	}
	else if (value < pointer->data || value == pointer->data)
	{
		if (pointer->left == nullptr)
		{
			node *toadd = new node;
			toadd->data = value;
			toadd->left = nullptr;
			toadd->right = nullptr;
			pointer->left = toadd;
		}
		else
		{
			pointer->left = push(value, pointer->left);
		}
	}
	else if (value > pointer->data)
	{
		if (pointer->right == nullptr)
		{
			node *toadd = new node;
			toadd->data = value;
			toadd->left = nullptr;
			toadd->right = nullptr;
			pointer->right = toadd;
		}
		else
		{
			pointer->right = push(value, pointer->right);
		}
	}
	return pointer;
}

node* search(int value, node* pointer = root)
{
	if (pointer == nullptr)
	{
		cout << "Такое число не найдено\n";
		return nullptr;
	}
	else if (pointer)
	{
		if (value < pointer->data)
		{
			if (pointer->left == nullptr)
			{
				cout << "Такое число не найдено";
				return nullptr;
			}
			else
			{
				search(value, pointer->left);
			}
		}
		else if (value > pointer->data)
		{
			if (pointer->right == nullptr)
			{
				cout << "такое число не найдено";
				return nullptr;
			}
			else
			{
				search(value, pointer->right);
			}
		}
		else if (value == pointer->data)
		{
			cout << "\nНайден адресс " << pointer << "\n";
			return pointer;
		}
	}
	return pointer;
}

void continuous_queue_pop(node *pointer, int mem[], const int size)
{
	if (pointer)
	{
		int i = 0;
		while (mem[i] != 0 && i < size)
		{
			i++;
		}
		mem[i] = pointer->data;
		continuous_queue_pop(pointer->left, mem, size);
		continuous_queue_pop(pointer->right, mem, size);
		delete pointer;
	}
}

void pop_value(int value, node *pointer = root)
{
	if (pointer == nullptr)
	{
		cout << "Такое число не найдено\n";
	}
	else
	{
		if (value == pointer->data && root == pointer)
		{
			int counter = node_number(root) - 1;
			int *mem = new int[counter];
			for (int i = 0; i < counter; i++)
			{
				mem[i] = 0;
			}
			continuous_queue_pop(pointer->left, mem, counter);
			continuous_queue_pop(pointer->right, mem, counter);
			root->left = nullptr;
			root->right = nullptr;
			root = nullptr;
			delete pointer;
			int i = 0;
			while (i < counter)
			{
				if (mem[i])
				{
					push(mem[i]);
				}
				i++;
			}
			delete mem;
		}
		else if (value < pointer->data)
		{
			if (pointer->left == nullptr)
			{
				cout << "Такое число не найдено";
			}
			else if (pointer->left->data == value)
			{
				node *todelete = pointer->left;
				int counter = node_number(todelete) - 1;
				int *mem = new int[counter];
				for (int i = 0; i < counter; i++)
				{
					mem[i] = 0;
				}
				continuous_queue_pop(todelete->left, mem, counter);
				continuous_queue_pop(todelete->right, mem, counter);
				pointer->left = nullptr;
				delete todelete;
				int i = 0;
				while (i < counter)
				{
					if (mem[i])
					{
						push(mem[i]);
					}
					i++;
				}
				delete mem;
			}
			else
			{
				pop_value(value, pointer->left);
			}
		}
		else if (value > pointer->data)
		{
			if (pointer->right == nullptr)
			{
				cout << "такое число не найдено";
			}
			else if (pointer->right->data == value)
			{
				node *todelete = pointer->right;
				int counter = node_number(todelete) - 1;
				int *mem = new int[counter];
				for (int i = 0; i < counter; i++)
				{
					mem[i] = 0;
				}
				continuous_queue_pop(todelete->left, mem, counter);
				continuous_queue_pop(todelete->right, mem, counter);
				pointer->right = nullptr;
				delete todelete;
				int i = 0;
				while (i < counter)
				{
					if (mem[i])
					{
						push(mem[i]);
					}
					i++;
				}
				delete mem;
			}
			else
			{
				pop_value(value, pointer->right);
			}
		}
	}
}

void display(node *pointer = root)
{
	if (pointer)
	{
		if (pointer->left)
		{
			display(pointer->left);
		}
		cout<< pointer->data << ' ';
		if (pointer->right)
		{
			display(pointer->right);
		}
	}
}

int node_number(node* tree) 
{
	if (tree == nullptr) return 0;
	return node_number(tree->left) + 1 + node_number(tree->right);
}

int leaf_count(node* pointer)
{
	if (!pointer)
		return 0;
	if (!pointer->left && !pointer->right)
		return 1;
	return  leaf_count(pointer->left) + leaf_count(pointer->right);
}

void clear(node *pointer = root) 
{
	if (pointer) 
	{
		clear(pointer->left);
		clear(pointer->right);
		delete pointer;
	}
	root = nullptr;
}

void occurences_counting(int **arr, const int size, node *pointer = root)
{
	if (pointer)
	{
		bool isnt_visited = true;
		for (int i = 0; i < size; i++)
		{
			if (arr[i][0] == pointer->data)
			{
				arr[i][1]++;
				isnt_visited = false;
			}
		}
		if (isnt_visited)
		{
			int i = 0;

			while (arr[i][0] != 0 && i < size)
			{
				i++;
			}
			arr[i][0] = pointer->data;
			arr[i][1]++;
		}
		occurences_counting(arr, size, pointer->left);
		occurences_counting(arr, size, pointer->right);
	}
}

void menu() 
{
	system("cls");
	tree_walk_straight();
	cout << "\n\n";

	int answer;
	cout << "Выберите действие над упорядоченным бинарным деревом:\n1 - Добавить элемент\n2 - Удалить элемент по значению\n3 - Найти адресс элемента\n4 - Очистить дерево\n5 - Количество вхождений\n6 - Выход\nanswer: ";
	cin >> answer;
	
	switch (answer)
	{
	case 1: 
	{
		int value;
		cout << "Введите значение: ";
		cin >> value;
		push(value);
		menu();
	}break;	
	case 2: 
	{
		int value;
		cout << "Введите значение: ";
		cin >> value;
		pop_value(value);
		menu();
	}break;	
	case 3: 
	{
		int value;
		cout << "Введите значение: ";
		cin >> value;
		search(value);
		system("pause>>void");
		menu();
	}break;	
	case 4: 
	{
		clear();
		menu();
	}break;	
	case 5:
	{
		int counter = node_number(root);
		int **mem = new int*[counter];
		for (int i = 0; i < counter; i++)
		{
			mem[i] = new int[2];
		}
		for (int i = 0; i < counter; i++)
		{
			mem[i][0] = 0;
			mem[i][1] = 0;
		}
		occurences_counting(mem, counter);
		for (int i = 0; i < counter; i++)
		{
			cout << "\nЧисло вхождений числа <" << mem[i][0] << "> - " << mem[i][1] << "\n";
		}
		for (int i = 0; i < counter; i++)
		{
			delete mem[i];
		}
		system("pause>>void");
		menu();
	}break;
	case 6: 
	{
		return;
	}break;
	default: 
	{
		return;
	}break;
	}
	menu();
}

int main() 
{
	setlocale(LC_ALL, "");

	menu();

	clear();

	system("pause>>void");
}