#include <ctime>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;
const int array_max_size = 10000;
int counter = 0;

void display(int *data, int size);

void menu0();
void menu1();
void menu2(int *data, int size, int algorythm_answer);

void display(int *data, int size)
{
	cout << setw(3);
	cout << "Array size: " << size << "\n";
	for (int i = 0; i < size; ++i)
	{
		cout << data[i] << "\t";
	}
	cout << "\n\n";
}

void shell_sort(int *data, int size)
{
	int step;
	int temp;
	for (step = size / 2; step >= 1; step /= 2)
	{
		for (int i = step; i < size; i++)
		{
			for (int j = i - step; j >= 0 && data[j] > data[j + step]; j -= step)
			{
				temp = data[j];
				data[j] = data[j + step];
				data[j + step] = temp;
				++counter;
			}
		}
	}
}

int partition(int *data, int size, int left, int right)
{
	int middle = data[(left + right) / 2];
	int i = left;
	int j = right;
	while (i <= j)
	{
		while (data[i] < middle)
		{
			++i;
		}
		while (data[j] > middle)
		{
			--j;
		}
		if (i >= j)
		{
			break;
		}
		int temp = data[i];
		data[i] = data[j];
		data[j] = temp;
		++i; --j;
		++counter;
	}
	return j;
}

void quick_sort(int *data, int size, int left, int right)
{
	if (left < right)
	{
		int q = partition(data, size, left, right);
		quick_sort(data, size, left, q);
		quick_sort(data, size, q + 1, right);
	}
}

void menu0()
{
	while (true)
	{
		system("cls");
		cout << "Вход:\n1 - Начало\n2 - Выход\n>> ";

		int input_answer;
		cin >> input_answer;
		while (!(input_answer == 1 || input_answer == 2))
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> input_answer;
		}

		if (input_answer == 1)
		{
			system("cls");
			menu1();
		}
		else
		{
			break;
		}
	}
}

void menu1()
{
	srand(time(NULL));
	const int arrsize = 10000;
	int array[arrsize];
	for (int i = 0; i < arrsize; ++i)
	{
		array[i] = (rand() % 1000);
	}
	display(array, arrsize);

	cout << "Выберите алгортм:\n1 - shell_sort\n2 - quick_sort\n>> ";
	int algorythm_answer;
	cin >> algorythm_answer;
	while (algorythm_answer < 1 || algorythm_answer > 2)
	{
		cout << ">> ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> algorythm_answer;
	}

	counter = 0;
	auto start = chrono::steady_clock::now();
	menu2(array, array_max_size, algorythm_answer);
	auto end = chrono::steady_clock::now();
	auto diff = end - start;

	display(array, array_max_size);
	cout << "arrsize = " << array_max_size << "\n";
	cout << "Вычислительная сложность алгоритма: " << counter << " операций перестановки элементов\n";
	cout << "Временная сложность алгоритма: " << chrono::duration <double, nano>(diff).count() << " ns\n";
	cout << "Временная сложность алгоритма: " << chrono::duration <double, milli>(diff).count() << " ms\n";

	cout << "_Выход";
	system("pause>>void");
}

void menu2(int *data, int size, int algorythm_answer)
{
	switch (algorythm_answer)
	{
	case 1:
	{
		shell_sort(data, size);
	}; break;
	case 2:
	{
		quick_sort(data, size, 0, size - 1);
	}; break;
	default: {}; break;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	return 0;
}