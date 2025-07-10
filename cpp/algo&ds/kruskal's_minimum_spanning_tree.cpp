#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;
const int infinity = INT_MAX;
const int tops = 10;

void menu0();
void menu1(int **data, int size);

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

void display(int **data, int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << i + 1 << "\t";
		for (int j = 0; j < size; ++j)
		{
			cout << setw(6);
			if (data[i][j] == infinity)
			{
				cout << "INF";
			}
			else
			{
				cout << data[i][j];
			}
		}
		cout << "\n";
	}
}

void menu0()
{
	cout << "_Вход\n";
	while (true)
	{
		cout << "|1 - Граф задан, 2 - Случайный граф, 3 - Выход| >> ";
		switch (int choise = get_number(1, 3))
		{
		case 1:
		{
			int matrix[tops][tops] = {
			{ 0, 5, 10, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 15, 12, 22, 0, 0, 0, 0},
			{ 0, 8, 0, 0, 6, 7, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 11, 0, 30, 0},
			{ 0, 0, 0, 17, 0, 0, 0, 9, 0, 0},
			{ 0, 0, 0, 0, 8, 0, 0, 18, 0, 35},
			{ 0, 0, 0, 0, 20, 0, 0, 18, 25, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
			{ 0, 0, 0, 0, 0, 0, 0, 14, 11, 0} };
			int **data = new int*[tops];
			for (int i = 0; i < tops; ++i)
			{
				data[i] = new int[tops];
				for (int j = 0; j < tops; ++j)
				{
					data[i][j] = matrix[i][j];
				}
			}
			menu1(data, tops);
			for (int i = 0; i < tops; ++i) { delete[] data[i]; }
			delete[] data;
			cout << "\n";
		}break;
		case 2:
		{
			srand(time(NULL));
			int **data = new int*[tops];
			for (int i = 0; i < tops; ++i)
			{
				data[i] = new int[tops];
				for (int j = 0; j < tops; ++j)
				{
					data[i][j] = rand() % 100;
				}
			}
			for (int i = 0; i < tops; ++i)
			{
				data[i][i] = 0;
			}
			menu1(data, tops);
			for (int i = 0; i < tops; ++i) { delete[] data[i]; }
			delete[] data;
			cout << "\n";
		}break;
		default: { return; }break;
		}
	}
}

class edge
{
public:
	int from, to, weight;
	edge() {}
	edge(int tofrom, int toto, int toweight)
	{
		this->from = tofrom;
		this->to = toto;
		this->weight = toweight;
	}
};

bool less_than(const edge& a, const edge& b)
{
	return a.weight < b.weight;
}

vector<int> leader;

int get_leader(int x)
{
	if (x == leader[x])
		return x;

	return leader[x] = get_leader(leader[x]);
}

bool check_root(int x, int y)
{
	x = get_leader(x);
	y = get_leader(y);

	if (x == y)
	{
		return false;
	}

	leader[x] = y;
	return true;
}

void menu1(int **data, int size)
{
	cout << "\nНачальная матрица графа\n";
	display(data, size);

	leader.resize(tops);
	for (int i = 0; i < tops; ++i)
	{
		leader[i] = i;
	}

	// const int tops // кол-во вершин
	// graph<edge>::size() // кол-во ребер изначального графа
	// tree<edge>::size() == tops - 1 // кол-во ребер минимального дерева
	vector<edge> graph;
	vector<edge> tree;
	for (int i = 0; i < tops; ++i)
	{
		for (int j = 0; j < tops; ++j)
		{
			if (data[i][j])
			{
				edge topush(i, j, data[i][j]);
				graph.push_back(topush);
			}
		}
	}
	sort(graph.begin(), graph.end(), less_than);
	/*
	for (int i = 0; i < tree_edges_number; ++i)
	{
		cout << "from " << graph[i].from + 1 << " to " << graph[i].to + 1 << " at a cost of " << graph[i].weight << "\n";
	}
	*/

	//int counter = 1;
	for (auto &it : graph)
	{
		if (check_root(it.from, it.to))
		{
			/*
			cout << "=///= counter = " << counter << "\n";
			++counter;
			for (auto &it : leader)
			{
				cout << it + 1 << "\n";
			}
			cout << "===\n";
			*/
			tree.push_back(it);
		}
	}
	int sum = 0;
	for (auto &it : tree)
	{
		sum += it.weight;
		cout << "from " << it.from + 1 << " to " << it.to + 1 << " at a cost of " << it.weight << "\n";
	}
	cout << "sum = " << sum << "\n";

	for (int i = 0; i < tops; ++i)
	{
		for (int j = 0; j < tops; ++j)
		{
			data[i][j] = 0;
		}
	}
	for (auto &it : tree)
	{
		data[it.from][it.to] = it.weight;
	}
	cout << "\nМинимальный остов алгоритму Крускала\n";
	display(data, size);
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	cout << "Выход_";
	system("pause>>void");
	return 0;
}