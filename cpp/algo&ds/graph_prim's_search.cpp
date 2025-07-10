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
	cout << "_Entrance\n";
	while (true)
	{
		cout << "|1 - Existing graph, 2 - Random graph, 3 - Exit| >> ";
		switch (int choise = get_number(1, 3))
		{
		case 1:
		{
			int matrix[tops][tops] = {
				{0, 5, 10, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 15, 12, 22, 0, 0, 0, 0},
				{0, 8, 0, 0, 6, 7, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 11, 0, 30, 0},
				{0, 0, 0, 17, 0, 0, 0, 9, 0, 0},
				{0, 0, 0, 0, 8, 0, 0, 18, 0, 35},
				{0, 0, 0, 0, 20, 0, 0, 18, 25, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
				{0, 0, 0, 0, 0, 0, 0, 14, 11, 0}};
			int **data = new int *[tops];
			for (int i = 0; i < tops; ++i)
			{
				data[i] = new int[tops];
				for (int j = 0; j < tops; ++j)
				{
					data[i][j] = matrix[i][j];
				}
			}
			menu1(data, tops);
			for (int i = 0; i < tops; ++i)
			{
				delete[] data[i];
			}
			delete[] data;
			cout << "\n";
		}
		break;
		case 2:
		{
			srand(time(NULL));
			int **data = new int *[tops];
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
			for (int i = 0; i < tops; ++i)
			{
				delete[] data[i];
			}
			delete[] data;
			cout << "\n";
		}
		break;
		default:
		{
			return;
		}
		break;
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

void menu1(int **data, int size)
{
	cout << "\nInput graph matrix\n";
	display(data, size);

	vector<edge> tree;

	int selected[tops];
	for (int i = 0; i < tops; ++i)
	{
		selected[i] = false;
	}
	selected[0] = true;

	int x;
	int y;
	int min;

	for (int k = 0; k < tops - 1; ++k)
	{
		min = infinity;
		x = 0;
		y = 0;

		for (int i = 0; i < tops; ++i)
		{
			if (selected[i])
			{
				for (int j = 0; j < tops; ++j)
				{
					if (!selected[j] && data[i][j])
					{
						if (min > data[i][j])
						{
							min = data[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		edge topush(x, y, data[x][y]);
		tree.push_back(topush);
		selected[y] = true;
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

	cout << "\nPrim algorithm minimal spanning tree graph matrix\n";
	display(data, size);
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	cout << "Exiting ...";
	system("pause>>void");
	return 0;
}