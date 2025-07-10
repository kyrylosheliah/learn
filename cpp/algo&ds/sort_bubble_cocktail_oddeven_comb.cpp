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
void bubble_sort(int *data, int size);
void cocktail_sort(int *data, int size);
void odd_even_sort(int *data, int size);
void comb_sort(int *data, int size);
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

void bubble_sort(int *data, int size)
{
	int temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				++counter;
			}
		}
	}
}

void cocktail_sort(int *data, int size)
{
	int left = 0, right = size - 1;         
	bool movements_flag = true;
	int temp;
	while ((left < right) && movements_flag == true)
	{
		movements_flag = false;
		for (int i = left; i < right; i++)  //слева направо
		{
			if (data[i] > data[i + 1]) 
			{ 
				temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
				movements_flag = true;
				++counter;
			}
		}
		right--; // сдвигаем правую границу на предыдущий элемент
		for (int i = right; i > left; i--)  //справа налево
		{
			if (data[i - 1] > data[i])
			{
				temp = data[i];
				data[i] = data[i - 1];
				data[i - 1] = temp;
				movements_flag = true;
				++counter;
			}
		}
		left++; // сдвигаем левую границу на следующий элемент
	}
}

void odd_even_sort(int *data, int size)
{
	bool movements_flag = true;
	int temp;
	while (movements_flag == true)
	{
		movements_flag = false;
		for (int i = 0; i < size - 1; i += 2)
		{
			if (data[i] > data[i + 1]) 
			{
				temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
				movements_flag = true;
				++counter;
			}
		}
		for (int i = 1; i < size - 2; i += 2)
		{
			if (data[i] > data[i + 1])
			{
				temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
				movements_flag = true;
				++counter;
			}
		}
	}
}

void comb_sort(int *data, int size)
{
	double factor = 1.247;
	double gapfactor = size / factor;
	int gap = gapfactor;
	int temp;
	while (gapfactor > 1) 
	{
		for (int i = 0, j = gap; j < size; ++i, ++j)
		{
			if (data[i] > data[j]) 
			{
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
				++counter;
			}
		}
		gapfactor = gapfactor / factor;
		gap = gapfactor;
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
	int array[array_max_size];
	for (int i = 0; i < array_max_size; ++i)
	{
		array[i] = (rand() % 1000);
	}
	display(array, array_max_size);

	cout << "Выберите алгортм:\n1 - Bubble\n2 - Cocktail\n3 - Odd-Even\n4 - Comb\n>> ";
	int algorythm_answer;
	cin >> algorythm_answer;
	while (algorythm_answer < 1 || algorythm_answer > 4)
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
		bubble_sort(data, size);
	}; break;
	case 2:
	{
		cocktail_sort(data, size);
	}; break;
	case 3:
	{
		odd_even_sort(data, size);
	}; break;
	case 4:
	{
		comb_sort(data, size);
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