#include <iostream>
#include <string>
using namespace std;

void menu1();
void menu2();
void menu3();
void menu4();
void menu5();

class node
{
public:
	string data;
	node()
	{
		this->data = "";
	}
	node(string todata)
	{
		this->data = todata;
	}
	node(node &other)
	{
		this->data = other.data;
	}
	void rewrite(string towrite)
	{
		this->data = towrite;
	}
	void display()
	{
		cout << "узел: " << this->data << "\n";
	}
};

class list
{
private:
	node **node_container;
	int size;
public:
	~list()
	{
		for (int i = 0; i < this->size; ++i)
		{
			node *todelete0 = this->node_container[i];
			this->node_container[i] = nullptr;
			delete todelete0;
		}
		node ** todelete1 = node_container;
		delete[] todelete1;
	}
	list()
	{
		this->node_container = new node*[0];
		this->size = 0;
	}
	void pushfront(string todata)
	{
		int new_size = this->size + 1;
		node ** new_array = new node*[new_size];
		new_array[0] = new node(todata);
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i + 1] = this->node_container[i];
		}
		node ** todelete = this->node_container;
		this->node_container = new_array;
		delete[] todelete;
		this->size++;
	}
	void pushback(string todata)
	{
		int new_size = this->size + 1;
		node ** new_array = new node*[new_size];
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->node_container[i];
		}
		new_array[new_size - 1] = new node(todata);
		node ** todelete = this->node_container;
		this->node_container = new_array;
		delete[] todelete;
		this->size++;
	}
	string popfront()
	{
		string toreturn;
		int new_size = this->size - 1;
		node ** new_array = new node*[new_size];
		node * todelete1 = this->node_container[0];
		toreturn = this->node_container[0]->data;
		this->node_container[0] = nullptr;
		delete todelete1;
		for (int i = 0; i < this->size; ++i)
		{
			new_array[i] = this->node_container[i + 1];
		}
		node ** todelete0 = this->node_container;
		this->node_container = new_array;
		delete[] todelete0;
		this->size--;
		return toreturn;
	}
	string popback()
	{
		string toreturn;
		int new_size = this->size - 1;
		node ** new_array = new node*[new_size];
		for (int i = 0; i < new_size; ++i)
		{
			new_array[i] = this->node_container[i];
		}
		node * todelete1 = this->node_container[new_size];
		toreturn = this->node_container[new_size]->data;;
		this->node_container[new_size] = nullptr;
		delete todelete1;
		node ** todelete0 = this->node_container;
		this->node_container = new_array;
		delete[] todelete0;
		this->size--;
		return toreturn;
	}
	void remove(string todelete_value)
	{
		int found_index;
		bool found_flag = false;
		for (int i = 0; i < this->size; ++i)
		{
			if (this->node_container[i]->data == todelete_value)
			{
				found_index = i;
				found_flag = true;
				break;
			}
		}
		if (found_flag)
		{
			int new_size = this->size - 1;
			node ** new_array = new node*[new_size];
			for (int i = 0, j = 0; i < new_size; ++i)
			{
				if (i == found_index)
				{
					node *todelete = this->node_container[i];
					this->node_container[i] = nullptr;
					delete todelete;
					j = 1;
				}
				new_array[i] = this->node_container[i + j];
			}
			this->node_container = new_array;
			this->size--;
		}
	}
	string peekfront()
	{
		if (this->size)
		{
			return this->node_container[0]->data;
		}
		else
		{
			return "EMPTY";
		}
	}
	string peekback()
	{
		if (this->size)
		{
			return this->node_container[this->size - 1]->data;
		}
		else
		{
			return "EMPTY";
		}
	}
	int get_size()
	{
		return this->size;
	}
	bool is_empty()
	{
		return !(this->size);
	}
	bool display()
	{
		if (this->size)
		{
			cout << "\nТекущий список:\n";
			for (int i = 0; i < this->size; ++i)
			{
				cout << i + 1 << " - ";
				this->node_container[i]->display();
			}
			return true;
		}
		else
		{
			cout << "\nСписок пуст\n";
			return false;
		}
	}
};

class stack
{
public:
	list nlist;
	void pushfront(string toadd)
	{
		this->nlist.pushfront(toadd);
	}
	string popfront()
	{
		return this->nlist.popfront();
	}
	string peekfront()
	{
		return this->nlist.peekfront();
	}
	int get_size()
	{
		return this->nlist.get_size();
	}
	bool is_empty()
	{
		return this->nlist.is_empty();
	}
	bool display()
	{
		return this->nlist.display();
	}
};

class queue
{
public:
	list nlist;
	void pushfront(string toadd)
	{
		this->nlist.pushfront(toadd);
	}
	string popback()
	{
		return this->nlist.popback();
	}
	string peekback()
	{
		return this->nlist.peekback();
	}
	int get_size()
	{
		return this->nlist.get_size();
	}
	bool is_empty()
	{
		return this->nlist.is_empty();
	}
	bool display()
	{
		return this->nlist.display();
	}
};

class dequeue
{
public:
	list nlist;
	void pushfront(string toadd)
	{
		this->nlist.pushfront(toadd);
	}
	void pushback(string toadd)
	{
		this->nlist.pushback(toadd);
	}
	string popfront()
	{
		return this->nlist.popfront();
	}
	string popback()
	{
		return this->nlist.popback();
	}
	string peekfront()
	{
		return this->nlist.peekfront();
	}
	string peekback()
	{
		return this->nlist.peekback();
	}
	int get_size()
	{
		return this->nlist.get_size();
	}
	bool is_empty()
	{
		return this->nlist.is_empty();
	}
	bool display()
	{
		return this->nlist.display();
	}
};

// 5, 20 Взять из очереди r-й и s-й элементы и добавить в конец дека
class OPERATOR
{
public:
	void R_AND_S_FROM_QUEUE_TO_DEQUEUE_BACK(int r_number, int s_number, queue * FROM, dequeue * TO)
	{
		if (r_number == s_number)
		{
			cout << "\nУказанные номера совпадают\n";
		}
		else if ((r_number <= FROM->get_size()) && (s_number <= FROM->get_size()))
		{
			int first, second;
			if (r_number < s_number) { first = r_number; second = s_number; }
			else { first = s_number; second = r_number; }
			int qsize = FROM->get_size();
			for (int i = 0; i < qsize; ++i)
			{
				if ((i + 1) == first)
				{
					TO->pushback(FROM->popback());
				}
				else if ((i + 1) == second)
				{
					TO->pushback(FROM->popback());
					break;
				}
				else
				{
					FROM->popback();
				}
			}
		}
		else
		{
			cout << "\nУказанные номера вне диапазона размера очереди\n";
		}
	}
};

void menu0()
{
	while (true)
	{
		//system("cls");
		cout << "_Вход\n|1 - Работа с классами, 2 - Задание, 3 - Выход| >> ";

		int start_answer;
		cin >> start_answer;
		while (start_answer < 1 || start_answer > 3)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> start_answer;
		}

		switch (start_answer)
		{
		case 1: { menu1(); }; break;
		case 2: { menu5(); }; break;
		default: { return; }; break;
		}
	}
}

void menu1()
{
	//system("cls");
	cout << "\n|1 - stack, 2 - queue, 3 - dequeue, 4 - Назад| >> ";

	int class_answer;
	cin >> class_answer;
	while (class_answer < 1 || class_answer > 4)
	{
		cout << ">> ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> class_answer;
	}
	switch (class_answer)
	{
	case 1: { menu2(); }; break;
	case 2: { menu3(); }; break;
	case 3: { menu4(); }; break;
	default: { return; }; break;
	}
}

void menu2()
{
	stack data;
	while (true)
	{
		//system("cls");
		cout << "\n\tТип данных <stack>\nПервый элемент: " << data.peekfront();
		data.display();

		cout << "|1 - pushfront, 2 - popfront, 3 - Назад| >> ";

		int operation_answer;
		cin >> operation_answer;
		while (operation_answer < 1 || operation_answer > 3)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> operation_answer;
		}
		switch (operation_answer)
		{
		case 1: {
			cin.ignore(256, '\n');
			cout << "toadd >> ";
			string answer;
			getline(cin, answer);
			data.pushfront(answer);
		}; break;
		case 2: {
			data.popfront();
		}; break;
		default: { return; }; break;
		}
	}
}

void menu3()
{
	queue data;
	while (true)
	{
		//system("cls");
		cout << "\n\tТип данных <queue>\nПоследний элемент: " << data.peekback();
		data.display();

		cout << "|1 - pushfront, 2 - popback, 3 - Назад| >> ";

		int operation_answer;
		cin >> operation_answer;
		while (operation_answer < 1 || operation_answer > 3)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> operation_answer;
		}
		switch (operation_answer)
		{
		case 1: {
			cin.ignore(256, '\n');
			cout << "toadd >> ";
			string answer;
			getline(cin, answer);
			data.pushfront(answer);
		}; break;
		case 2: {
			data.popback();
		}; break;
		default: { return; }; break;
		}
	}
}

void menu4()
{
	dequeue data;
	while (true)
	{
		//system("cls");
		cout << "\n\tТип данных <dequeue>\nПервый элемент: " << data.peekfront() << "\nПоследний элемент: " << data.peekback();
		data.display();

		cout << "|1 - pushfront, 2 - pushfront, 3 - popfront, 4 - popback, 5 - Назад| >> ";

		int operation_answer;
		cin >> operation_answer;
		while (operation_answer < 1 || operation_answer > 5)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> operation_answer;
		}

		switch (operation_answer)
		{
		case 1: {
			cin.ignore(256, '\n');
			cout << "toadd >> ";
			string answer;
			getline(cin, answer);
			data.pushfront(answer);
		}; break;
		case 2: {
			cin.ignore(256, '\n');
			cout << "toadd >> ";
			string answer;
			getline(cin, answer);
			data.pushback(answer);
		}; break;
		case 3: {
			data.popfront();
		}; break;
		case 4: {
			data.popback();
		}; break;
		default: { return; }; break;
		}
	}
}

void menu5()
{
	queue *data1 = new queue;
	dequeue *data2 = new dequeue;
	while (true)
	{
		//system("cls");
		cout << "\n\tСодержимое <queue>:\nПоследний элемент: " << data1->peekback();
		data1->display();
		cout << "\tСодержимое <dequeue>:\nПервый элемент: " << data2->peekfront() << "\nПоследний элемент: " << data2->peekback();
		data2->display();

		cout << "|1 - push to queue, 2 - R_AND_S_FROM_QUEUE_TO_DEQUEUE_BACK, 3 - Назад| >> ";

		int operation_answer;
		cin >> operation_answer;
		while (operation_answer < 1 || operation_answer > 3)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> operation_answer;
		}

		switch (operation_answer)
		{
		case 1: {
			cin.ignore(256, '\n');
			cout << "toadd >> ";
			string answer;
			getline(cin, answer);
			data1->pushfront(answer);
		}; break;
		case 2: {
			OPERATOR RS_to_DEQ;
			int R, S;
			cout << "Введите номер числа r >> ";
			cin >> R;
			cout << "Введите номер числа s >> ";
			cin >> S;
			RS_to_DEQ.R_AND_S_FROM_QUEUE_TO_DEQUEUE_BACK(R, S, data1, data2);
		}; break;
		default: {
			delete data1;
			delete data2;
			return;
		}; break;
		}
	}
	delete data1;
	delete data2;
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	cout << "Выход_";
	system("pause>>void");
	return 0;
}