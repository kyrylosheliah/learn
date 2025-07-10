#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;

void menu0();
void menu1(bool **data, int size);
void menu2(bool **data, int size, int sought_for);

int get_number(int from, int to)
{
	int answer;
	cin.clear();
	cin >> answer;
	while (answer < from || answer > to)
	{
		cout << ">> ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> answer;
	}
	return answer;
}

void display(bool **data, int size)
{
	for (int i = 0; i < size; ++i) 
	{ 
		cout << i + 1 << "\t";
		for (int j = 0; j < size; ++j) 
		{ 
			cout << setw(3);
			cout << data[i][j]; 
		} 
		cout << endl; 
	}
}

void menu0()
{
	const int tops = 16;
	bool matrix[tops][tops] = { // матрица смежности
	{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
	bool **data = new bool*[tops];
	for (int i = 0; i < tops; ++i)
	{
		data[i] = new bool[tops];
		for (int j = 0; j < tops; ++j)
		{
			data[i][j] = matrix[i][j];
		}
	}
	while (true)
	{
		//system("cls");
		cout << "\n_Вход\n|1 - Обход графа в глубину, 2 - Поиск вершины в глубину, 3 - Выход| >> ";

		int start_answer = get_number(1,3);
		switch (start_answer)
		{
		case 1: { menu1(data, tops); }; break;
		case 2: { 
			display(data, tops);
			cout << "Искомая вершина >> ";
			int sought_for = get_number(1, tops);
			menu2(data, tops, sought_for);
		}; break;
		default: { return; }; break;
		}
	}
	for (int i = 0; i < tops; ++i)
	{
		delete [] data[i];
	}
	delete [] data;
}

void menu1(bool **data, int size)
{
	// Обход графа в глубину
	//system("cls");
	display(data, size);

	int *visited = new int[size]; for (int i = 0; i < size; ++i) { visited[i] = 0; } // все не посещены
	stack<int> STACK;
	STACK.push(0);
	while (!STACK.empty())
	{
		int index = STACK.top();
		STACK.pop();
		visited[index] = 2; // 2 - посещенная
		for (int i = 0; i < size; ++i)
		{
			if (data[index][i] && !(visited[i]))
			{
				STACK.push(i);
				visited[i] = 1; // 1 - обнаруженная
			}
		}
		cout << "Посещена вершина " << index + 1 << "\n";
	}
}

class path 
{
public:
	int begin;
	int end;
};
void menu2(bool **data, int size, int sought_for)
{
	// Поиск вершины на графе в глубину
	//system("cls");
	stack<path> way_trace;
	path trace;
	int searching = sought_for - 1;
	int *visited = new int[size]; for (int i = 0; i < size; ++i) { visited[i] = 0; } // все не посещены
	stack<int> STACK;
	STACK.push(0);
	bool found_flag = false;
	while (!STACK.empty() && !found_flag)
	{
		int index = STACK.top(); STACK.pop();
		visited[index] = 2; // 2 - посещенная
		for (int i = size - 1; i >= 0; --i)
		{
			if (data[index][i] && !(visited[i]))
			{
				STACK.push(i);
				visited[i] = 1; // 1 - обнаруженная
				trace.begin = index; trace.end = i;
				way_trace.push(trace);
			}
		}
		if (index == searching)
		{
			found_flag = true;
			cout << "Найдена искомая вершина " << sought_for << ": \n";
			break;
		}
		cout << "Посещена вершина " << index + 1 << "\n";
	}
	cout << "Путь до вершины " << searching + 1 << ": ";
	cout << searching + 1;
	while (!way_trace.empty())
	{
		trace = way_trace.top(); way_trace.pop();
		if (trace.end == searching)
		{
			searching = trace.begin;
			cout << " - " << searching + 1;
		}
	}
	cout << "\n";
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	cout << "Выход_";
	system("pause>>void");
	return 0;
}
