#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <queue>
#include <vector>
#include <algorithm>
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
			cout << setw(3);
			cout << data[i][j];
		}
		cout << "\n";
	}
}

char to_char(int number)
{
	switch (number)
	{
	case 0: {return '0'; } break;
	case 1: {return '1'; } break;
	case 2: {return '2'; } break;
	case 3: {return '3'; } break;
	case 4: {return '4'; } break;
	case 5: {return '5'; } break;
	case 6: {return '6'; } break;
	case 7: {return '7'; } break;
	case 8: {return '8'; } break;
	case 9: {return '9'; } break;
	default: {return '?'; } break;
	}
}

class path
{
public:
	int cost;
	string trace;
};
class node
{
public:
	int cost;
	int number;
};

void menu0()
{
	while (true)
	{
		cout << "\n_Entrance |1 - Graph breadth first traversal, 2 - Vertex breadth first search, 3 - Exit| >> ";
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
		}break;
		default: { return; }break;
		}
	}
}

void menu1(int **data, int size)
{
	display(data, size);
	path *pathes = new path[tops];
	for (int i = 0; i < tops; ++i)
	{
		pathes[i].cost = infinity;
	}

	pathes[0].cost = 0;
	int visited[tops]; for (int i = 0; i < tops; ++i) { visited[i] = 0; }
	int minimal_cost;
	int minimal_index;

	pathes[0].cost = 0;

	int temp;
	do
	{
		minimal_index = infinity;
		minimal_cost = infinity;
		for (int i = 0; i < tops; ++i)
		{
			if (!visited[i] && (pathes[i].cost < minimal_cost))
			{
				minimal_cost = pathes[i].cost;
				minimal_index = i;
			}
		}
		if (minimal_index != infinity)
		{
			for (int i = 0; i < tops; ++i)
			{
				if (data[minimal_index][i])
				{
					temp = minimal_cost + data[minimal_index][i];
					if (temp < pathes[i].cost)
					{
						pathes[i].cost = temp;
						pathes[i].trace = pathes[minimal_index].trace + " - " + to_char(minimal_index + 1);
					}
				}
			}
			visited[minimal_index] = 1;
		}
	} while (minimal_index < infinity);

	for (int i = 0; i < tops; ++i)
	{
		pathes[i].trace = pathes[i].trace + " - " + to_char(i + 1);
	}

	for (int i = 0; i < tops; ++i)
	{
		cout << "Path to " << i + 1 << " weight: " << pathes[i].cost << "\t path " << pathes[i].trace << "\n";
	}
	delete[] pathes;
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	cout << "Exiting ...";
	system("pause>>void");
	return 0;
}