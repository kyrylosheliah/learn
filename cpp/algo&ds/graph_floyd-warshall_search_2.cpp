#include <iostream>
#include <iomanip>
#include <string>
#include <string>
#include <random>
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

string tostring(int number)
{
	switch (number)
	{
	case 0: {return "0"; } break;
	case 1: {return "1"; } break;
	case 2: {return "2"; } break;
	case 3: {return "3"; } break;
	case 4: {return "4"; } break;
	case 5: {return "5"; } break;
	case 6: {return "6"; } break;
	case 7: {return "7"; } break;
	case 8: {return "8"; } break;
	case 9: {return "9"; } break;
	default: {return "?"; } break;
	}
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
	while (true)
	{
		cout << "\n_Entrance |1 - Existing graph, 2 - Random graph, 3 - Exit| >> ";
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

class path
{
public:
	int cost;
	string trace;
};

void menu1(int **data, int size)
{
	cout << "\nInput graph matrix\n";
	display(data, size);

	path pathes[tops][tops];
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			pathes[i][j].cost = infinity;
			if (data[i][j])
			{
				pathes[i][j].cost = data[i][j];
				pathes[i][j].trace = tostring(i + 1) + tostring(j + 1);
			}
		}
		pathes[i][i].cost = 0;
		pathes[i][i].trace = tostring(i + 1);
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (data[i][j] == 0)
			{
				data[i][j] = infinity;
			}
		}
		data[i][i] = 0;
	}

	for (int k = 0; k < size; ++k)
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if ((data[i][k] != infinity) && (data[k][j] != infinity) && (i != j))
				{
					if (data[i][k] + data[k][j] < data[i][j])
					{
						data[i][j] = data[i][k] + data[k][j];
						pathes[i][j].cost = data[i][j];
						pathes[i][j].trace = pathes[i][k].trace + pathes[k][j].trace;
					}
				}
			}
		}
	}

	cout << "\nFloyd-Warshall algorythm matrix\n";
	display(data, size);
	for (int i = 0; i < tops; ++i)
	{
		for (int j = 0; j < tops; ++j)
		{
			if (pathes[i][j].trace.empty()) { }
			else
			{
				cout << "\n|" << i + 1 << "->" << j + 1 << ": ";
				cout << pathes[i][j].trace<<"|";
				(pathes[i][j].trace.size() >= 7) ? (cout << "\t") : (cout << "\t\t");
				pathes[i][j].trace.erase(unique(pathes[i][j].trace.begin(), pathes[i][j].trace.end()), pathes[i][j].trace.end());
				cout << i + 1 << "->" << j + 1 << ": ";
				cout << pathes[i][j].trace;
			}
		}
	}
}

int main()
{
	menu0();
	cout << "Exiting ...";
	system("pause>>void");
	return 0;
}