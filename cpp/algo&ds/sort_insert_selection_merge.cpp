#include <ctime>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;
const int array_max_size = 10000;
int counter = 0;

void insert_sort(int *data, int size);
void selection_sort(int *data, int size);
void merge(int *A, int first, int last);
void merge_sort(int *A, int first, int last);
void display(int *data, int size);
void menu0();
void menu1();
void menu2(int *data, int size, int algorythm_answer);

void insert_sort(int *data, int size)
{
	for (int i = 1; i < size; ++i)
	{
		for (int j = i; j > 0 && data[j - 1] > data[j]; --j) // пока j>0 и элемент j-1 > j, x-массив int
		{
			int temp = data[j - 1];
			data[j - 1] = data[j];
			data[j] = temp;
			++counter;
		}
	}
}

void selection_sort(int *data, int size)
{
	int temp;
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (data[i] > data[j])
			{
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
				++counter;
			}
		}
	}
}

void merge(int *data, int begin, int end)
{
	int i = begin;
	int middle = begin + (end - begin) / 2;
	int j = middle + 1;
	int t = 0;
	int d[array_max_size];

	while (i <= middle && j <= end) 
	{
		if (data[i] <= data[j])
		{
			d[t] = data[i]; i++;
		}
		else 
		{
			d[t] = data[j]; j++;
		}
		t++;
	}

	while (i <= middle) 
	{
		d[t] = data[i]; i++; t++;
	}

	while (j <= end) 
	{
		d[t] = data[j]; j++; t++;
	}

	for (i = 0; i < t; i++)
	{
		data[begin + i] = d[i];
		++counter;
	}
}

void merge_sort(int *data, int left, int right)
{
	if (left < right)
	{
		if (right - left == 1)
		{
			if (data[left] > data[right])
			{
				int temp = data[left];
				data[left] = data[right];
				data[right] = temp;
				++counter;
			}
		}
		else
		{
			merge_sort(data, left, left + (right - left) / 2);
			merge_sort(data, left + (right - left) / 2 + 1, right);
			merge(data, left, right);
		}
	}
}

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
	int *array = new int[array_max_size];
	for (int i = 0; i < array_max_size; ++i)
	{
		array[i] = (rand() % 1000);
	}
	display(array, array_max_size);

	cout << "Выберите алгортм:\n1 - insert_sort\n2 - selection_sort\n3 - merge_sort\n>> ";
	int algorythm_answer;
	cin >> algorythm_answer;
	while (algorythm_answer < 1 || algorythm_answer > 3)
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
	delete[] array;
}

void menu2(int *data, int size, int algorythm_answer)
{
	switch (algorythm_answer)
	{
	case 1:
	{
		insert_sort(data, size);
	}; break;
	case 2:
	{
		selection_sort(data, size);
	}; break;
	case 3:
	{
		merge_sort(data, 0, size - 1);
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