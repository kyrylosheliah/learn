// 21 - Посчитайте количество ребер в графе, заданном матрицей инцидентности. 

#include <iostream>
using namespace std;

const int tops = 6;

int incidence_matrix_relative_count(int mass[][tops])
{
	int summ = 0;
	int top1 = 0, top2 = 0;
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (mass[j][i] == 1)
			{
				summ += 1;
				top2 = j + 1;
			}
			else if (mass[j][i] == -1)
			{
				summ += 1;
				top1 = j + 1;
			}
		}
		if (top1 && top2)
		{
			cout << "Найдено ребро из X"<<top1<<" в X"<<top2<<"\n";
		}
		top1 = top2 = 0;
	}
	return summ / 2;
}

int incidence_matrix_relative_count(bool mass[tops][tops])
{
	int summ = 0;
	int top1 = 0, top2 = 0;
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (mass[j][i] == 1)
			{
				summ += 1;
				if (top1 == 0)
				{
					top1 = j + 1;
				}
				else
				{
					top2 = j + 1;
				}
			}
		}
		if (top1 && top2)
		{
			cout << "Найдено ребро из X" << top1 << " в X" << top2 << "\n";
		}
		top1 = top2 = 0;
	}
	return summ / 2;
}

void main()
{
	int matr_orgraph[tops][tops] = { { -1, -1, 0, 0, 0, 0 }, // матрица инцидентности для орграфа
	{ 0, 0, -1, 1, 0, 0 },
	{ 1, 0, 0, 0, -1, 0 },
	{ 0, 0, 1, 0, 0, 1 },
	{ 0, 1, 0, -1, 0, 0 },
	{ 0, 0, 0, 0, 1, -1 } };
	
	bool matr_neorgraph[tops][tops] = { { 1, 1, 0, 0, 0, 0 }, // матрица инцидентности для неорграфа
	{ 0, 0, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 1 } };

	// количесиво ребер равно кратности того, сколько в матрице инцидентности в столбцах попарных комбинаций 1 и -1
	// т.е. два числа в столбце, отличных от нуля, означают наличие ребра
	// поэтому число ребер равно количеству ненулевых чисел деленных пополам

	int count;

	cout << "Матрица орграфа:\n";
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			cout << matr_orgraph[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	count = incidence_matrix_relative_count(matr_orgraph);
	cout << "Количество ребер - " <<count<<"\n\n\n";


	cout << "Матрица неорграфа:\n";
	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			cout << matr_neorgraph[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	count = incidence_matrix_relative_count(matr_neorgraph);
	cout << "Количество ребер - " << count << "\n\n\n";

	system("pause");
}