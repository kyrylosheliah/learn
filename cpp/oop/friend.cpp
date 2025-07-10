/*
Описать класс, содержащий:
1.	указатель на матрицу;
2.	размер матрицы;
3.	конструктор с параметрами, определяющими размер матрицы. На основании заданных размеров выделяется место в «куче» и вызывается функция формирования элементов матрицы с помощью генератора случайных чисел. Выводится сообщение о работе конструктора.
4.	Деструктор, освобождающий память в «куче». Выводится сообщение о работе деструктора.
5.	Конструктор копии с выводом сообщения о своей работе.
6.	Дружественные функции формирования элементов матрицы и вывода матрицы на печать.
7.	Переопределенные операции:
−	присваивания;
−	заданные, в индивидуальном варианте.
Если в состав переопределения операции входит стандартный алгоритм (определение суммы, максимума, минимума, сортировка и т.п.), то их необходимо оформить дружественными функциями и вызывать в переопределенных операциях.
Функции переопределения операций, должны содержать проверку соответствия размеров операндов, участвующих в операции (если это необходимо). В случае различия доопределять операнды до максимального размера нулями (либо усекать до минимального размера).
В функции main создается необходимое количество экземпляра объектов вышеописанного класса и вычисляется выражение, заданное вариантом. На экран выводятся все промежуточные результаты (т.е результаты работы каждой операции).
Условные обозначения:
М – матрица
V – одномерный массив
К – числовое значение
А, В и С – экземпляры класса (объекты).
Тип элементов объектов выбирается в соответствии с переопределяемыми операциями (если используются побитовые операции, то тип int, в противном случае float).
*/
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>

class linear_matrix_algebra
{
private:
	int **data = nullptr;
	int height = 0;
	int width = 0;
public:
	friend void display_matrix(const linear_matrix_algebra*);
	friend linear_matrix_algebra *operation1(linear_matrix_algebra*, linear_matrix_algebra*);
	friend linear_matrix_algebra *operation2(linear_matrix_algebra*, linear_matrix_algebra*);
	friend linear_matrix_algebra *operation3(linear_matrix_algebra*, linear_matrix_algebra*);
	~linear_matrix_algebra()
	{
		std::cout << "Destructor for <linear_matrix_algebra>[" << this << "]\n";
		for (int i = 0; i < this->height; ++i)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
	}
	linear_matrix_algebra() { }
	linear_matrix_algebra(int towidth, int toheight)
	{
		std::cout << "Constructor for <linear_matrix_algebra>[" << this << "]\n";
		this->height = toheight;
		this->width = towidth;
		int **todata = new int*[toheight];
		for (int i = 0; i < toheight; ++i)
		{
			todata[i] = new int[towidth];
			for (int j = 0; j < towidth; ++j)
			{
				srand(rand());
				todata[i][j] = (rand() % 200) - 100;
			}
		}
		this->data = todata;
		display_matrix(this);
	}
	linear_matrix_algebra(int **todata, int towidth, int toheight)
	{
		std::cout << "Constructor for <linear_matrix_algebra>[" << this << "]\n";
		this->height = toheight;
		this->width = towidth;
		int **tempdata = new int*[toheight];
		for (int i = 0; i < toheight; ++i)
		{
			tempdata[i] = new int[towidth];
			for (int j = 0; j < towidth; ++j)
			{
				tempdata[i][j] = todata[i][j];
			}
		}
		this->data = tempdata;
		display_matrix(this);
	}
	linear_matrix_algebra(const linear_matrix_algebra &other)
	{
		std::cout << "Copy constructor for <linear_matrix_algebra>[" << this << "] from [" << &other << "]\n";
		this->height = other.height;
		this->width = other.width;
		int **todata = new int*[this->height];
		for (int i = 0; i < this->height; ++i)
		{
			todata[i] = new int[this->width];
			for (int j = 0; j < this->width; ++j)
			{
				todata[i][j] = other.data[i][j];
			}
		}
		this->data = todata;
		display_matrix(this);
	}
	/*
М3=М1>>М2 - циклический сдвиг столбцов двух матриц вправо до тех пор пока на первую позицию не станет столбец, содержащий наибольший элемент двух матриц. М3 равна результату (двойная матрица);
М3=М1|М2 – М3 формируется из столбцов М1 и М2, удовлетворяющих условию: количество положительных элементов в столбце больше отрицательных;
М3=М1<М2 – М3[i,j] = M1[i,j], если i<=j, иначе М3[i,j]=M2[i,j].
	*/
	linear_matrix_algebra &operator=(const linear_matrix_algebra &other)
	{
		this->height = other.height;
		this->width = other.width;
		for (int i = 0; i < this->height; ++i)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
		int **todata = new int*[this->height];
		for (int i = 0; i < this->height; ++i)
		{
			todata[i] = new int[this->width];
			for (int j = 0; j < this->width; ++j)
			{
				todata[i][j] = other.data[i][j];
			}
		}
		this->data = todata;
	}
	linear_matrix_algebra &operator>>(linear_matrix_algebra &other)
	{
		return *operation1(this, &other);
	}
	linear_matrix_algebra &operator|(linear_matrix_algebra &other)
	{
		return *operation2(this, &other);
	}
	linear_matrix_algebra &operator<(linear_matrix_algebra &other)
	{
		return *operation3(this, &other);
	}
};

void display_matrix(const linear_matrix_algebra *todisplay)
{
	std::cout << "Выводится [" << todisplay << "]\n";
	for (int i = 0; i < todisplay->height; ++i)
	{
		for (int j = 0; j < todisplay->width; ++j)
		{
			std::cout << std::setw(4) << todisplay->data[i][j];
		}
		std::cout << "\n";
	}
}

linear_matrix_algebra *operation1(linear_matrix_algebra *left, linear_matrix_algebra *right)
{
	int toheight = std::max(left->height, right->height);
	int towidth = left->width + right->width;
	int **todata = new int*[toheight];
	for (int i = 0; i < toheight; ++i)
	{
		todata[i] = new int[towidth];
		for (int j = 0; j < towidth; ++j)
		{
			todata[i][j] = 0;
		}
	}
	for (int i = 0; i < left->height; ++i)
	{
		for (int j = 0; j < left->width; ++j)
		{
			todata[i][j] = left->data[i][j];
		}
	}
	for (int i = 0; i < toheight; ++i)
	{
		for (int j = 0; j < right->width; ++j)
		{
			todata[i][j + left->width] = right->data[i][j];
		}
	}
	int max = todata[0][0], max_j = 0;
	for (int i = 0; i < toheight; ++i)
	{
		for (int j = 0; j < towidth; ++j)
		{
			if (max < todata[i][j])
			{
				max = todata[i][j];
				max_j = j;
			}
		}
	}
	std::cout << "Отработал operator>>, максимальный элемент = " << max << ", в столбце " << max_j << "\n";
	int second_chunk_size = towidth - max_j;
	int first_chunk_size = towidth - second_chunk_size;
	int *first_chunk = new int[first_chunk_size];
	int *second_chunk = new int[second_chunk_size];
	for (int i = 0; i < toheight; ++i)
	{
		for (int j = 0; j < first_chunk_size; ++j)
		{
			first_chunk[j] = todata[i][j];
		}
		for (int j = first_chunk_size; j < towidth; ++j)
		{
			second_chunk[j - first_chunk_size] = todata[i][j];
		}
		for (int j = 0; j < first_chunk_size; ++j)
		{
			todata[i][j + second_chunk_size - 1] = first_chunk[j];
		}
		for (int j = 0; j < second_chunk_size; ++j)
		{
			todata[i][j] = second_chunk[j];
		}
	}
	delete[] first_chunk;
	delete[] second_chunk;
	for (int i = 0; i < left->height; ++i)
	{
		delete[] left->data[i];
	}
	delete[] left->data;
	left->height = toheight;
	left->width = towidth;
	left->data = todata;
	return left;
}

linear_matrix_algebra *operation2(linear_matrix_algebra *left, linear_matrix_algebra *right)
{
	int toheight = std::max(left->height, right->height);
	int tempwidth = left->width + right->width;
	int **tempdata = new int*[toheight];
	for (int i = 0; i < toheight; ++i)
	{
		tempdata[i] = new int[tempwidth];
		for (int j = 0; j < tempwidth; ++j)
		{
			tempdata[i][j] = 0;
		}
	}
	for (int i = 0; i < left->height; ++i)
	{
		for (int j = 0; j < left->width; ++j)
		{
			tempdata[i][j] = left->data[i][j];
		}
	}
	for (int i = 0; i < toheight; ++i)
	{
		for (int j = 0; j < right->width; ++j)
		{
			tempdata[i][j + left->width] = right->data[i][j];
		}
	}

	int **todata = new int*[toheight];
	for (int i = 0; i < toheight; ++i)
	{
		todata[i] = new int[0];
	}
	int towidth = 0;
	int positive_count, negative_count;
	for (int i = 0; i < tempwidth; ++i)
	{
		positive_count = negative_count = 0;
		for (int j = 0; j < toheight; ++j)
		{
			if (tempdata[j][i] > 0) { ++positive_count; }
			if (tempdata[j][i] < 0) { ++negative_count; }
		}
		if (positive_count > negative_count)
		{
			++towidth;
			int **temp = new int*[toheight];
			for (int j = 0; j < toheight; ++j)
			{
				temp[j] = new int[towidth];
			}
			for (int j = 0; j < toheight; ++j)
			{
				for (int k = 0; k < towidth - 1; ++k)
				{
					temp[j][k] = todata[j][k];
				}
			}
			for (int j = 0; j < toheight; ++j)
			{
				temp[j][towidth - 1] = tempdata[j][i];
				delete[] todata[j];
			}
			delete[] todata;
			todata = temp;
		}
	}

	for (int i = 0; i < toheight; ++i)
	{
		delete[] tempdata[i];
	}
	delete[] tempdata;
	for (int i = 0; i < left->height; ++i)
	{
		delete[] left->data[i];
	}
	delete[] left->data;
	left->height = toheight;
	left->width = towidth;
	left->data = todata;
	return left;
}

linear_matrix_algebra *operation3(linear_matrix_algebra *left, linear_matrix_algebra *right)
{
	int toheight = std::max(left->height, right->height);
	int towidth = std::max(left->width, right->width);
	int **todata = new int*[toheight];
	for (int i = 0; i < toheight; ++i)
	{
		todata[i] = new int[towidth];
		for (int j = 0; j < towidth; ++j) { todata[i][j] = 0; }
	}
	for (int i = 0; i < left->height; ++i)
	{
		for (int j = 0; j < left->width; ++j)
		{
			if (i <= j)
			{
				todata[i][j] = left->data[i][j];
			}
		}
	}
	for (int i = 0; i < right->height; ++i)
	{
		for (int j = 0; j < right->width; ++j)
		{
			if (i > j)
			{
				todata[i][j] = right->data[i][j];
			}
		}
	}
	left->height = toheight;
	left->width = towidth;
	left->data = todata;
	return left;
}

void menu0()
{
	std::cout << "===	A(3, 9)\n";
	linear_matrix_algebra A(3, 9);
	std::cout << "===	B(9, 3)\n";
	linear_matrix_algebra B(9, 3);
	std::cout << "===	C = B >> A\n";
	linear_matrix_algebra C = B >> A;
	std::cout << "===	D = B | A\n";
	linear_matrix_algebra D = B | A;
	std::cout << "===	E = B < A\n";
	linear_matrix_algebra E = B < A;
	std::cout << "===	F = B|(C>>A)<A\n";
	linear_matrix_algebra F = B|(C>>A)<A;
	std::cout << "===\n";
}

int main()
{
	setlocale(0, "");
	srand(time(0));

	menu0();

	system("pause>>void");
	return 0;
}