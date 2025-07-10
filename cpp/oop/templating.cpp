#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

// TODO: get rid of ._Ptr usage in favor of crossplatform pointer resolution

/*
Задание и порядок выполнения работы

1.	Определить шаблон функции, которая выполняет указанные действия согласно варианту задания.
2.	Инстанцировать шаблон для стандартных типов данных (int, float, double). В тестовой программе предусмотреть явное и неявное инстанцирование.
3.	Инстанцировать шаблон для абстрактного типа данных. В абстрактном типе данных предусмотреть конструктор копирования, конструктор преобразования типа, перегруженные операции необходимые для решения задачи согласно индивидуальному заданию.
4.	Определить шаблонную функцию с несколькими параметрами. Провести отождествление типов аргументов тремя способами. Обосновать целесообразность использования каждого из способов.
5.	Описать прототипы шаблонов.
6.	Реализовать параметры-шаблоны.
*/

/*
20.	Поменять местами минимальный и максимальный элементы массива.
*/

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
	case 10: {return 'A'; } break;
	case 11: {return 'B'; } break;
	case 12: {return 'C'; } break;
	case 13: {return 'D'; } break;
	case 14: {return 'E'; } break;
	case 15: {return 'F'; } break;
	case 16: {return 'G'; } break;
	case 17: {return 'H'; } break;
	case 18: {return 'I'; } break;
	case 19: {return 'J'; } break;
	case 20: {return 'K'; } break;
	case 21: {return 'L'; } break;
	case 22: {return 'M'; } break;
	case 23: {return 'N'; } break;
	case 24: {return 'O'; } break;
	case 25: {return 'P'; } break;
	case 26: {return 'Q'; } break;
	case 27: {return 'R'; } break;
	case 28: {return 'S'; } break;
	case 29: {return 'T'; } break;
	case 30: {return 'U'; } break;
	case 31: {return 'V'; } break;
	case 32: {return 'W'; } break;
	case 33: {return 'X'; } break;
	case 34: {return 'Y'; } break;
	case 35: {return 'Z'; } break;
	default: {return '?'; } break;
	}
}

int to_int(char string_number)
{
	switch (string_number)
	{
	case '0': {return 0; } break;
	case '1': {return 1; } break;
	case '2': {return 2; } break;
	case '3': {return 3; } break;
	case '4': {return 4; } break;
	case '5': {return 5; } break;
	case '6': {return 6; } break;
	case '7': {return 7; } break;
	case '8': {return 8; } break;
	case '9': {return 9; } break;
	case 'A': {return 10; } break;
	case 'B': {return 11; } break;
	case 'C': {return 12; } break;
	case 'D': {return 13; } break;
	case 'E': {return 14; } break;
	case 'F': {return 15; } break;
	case 'G': {return 16; } break;
	case 'H': {return 17; } break;
	case 'I': {return 18; } break;
	case 'J': {return 19; } break;
	case 'K': {return 20; } break;
	case 'L': {return 21; } break;
	case 'M': {return 22; } break;
	case 'N': {return 23; } break;
	case 'O': {return 24; } break;
	case 'P': {return 25; } break;
	case 'Q': {return 26; } break;
	case 'R': {return 27; } break;
	case 'S': {return 28; } break;
	case 'T': {return 29; } break;
	case 'U': {return 30; } break;
	case 'V': {return 31; } break;
	case 'W': {return 32; } break;
	case 'X': {return 33; } break;
	case 'Y': {return 34; } break;
	case 'Z': {return 35; } break;
	default: {return -1; } break;
	}
}

class number_based_number
{
private:
	string number_string;
	int decimal_number;
	int base;
public:
	int get_int()
	{
		return this->decimal_number;
	}
	string string_reverse(string &str)
	{
		int temp_size = str.size();
		string temp;
		for (int j = temp_size - 1; j >= 0; --j)
		{
			temp += str[j];
		}
		return temp;
	}
	~number_based_number()
	{

	}
	number_based_number(string tonumber_string, int tobase)
	{
		int tonumber = 0;
		for (int i = 0; i < tonumber_string.size(); ++i)
		{
			tonumber += to_int(tonumber_string[i]) * 10 ^ (i);
		}
		this->decimal_number = tonumber;
		this->base = tobase;
		this->number_string = tonumber_string;
	}
	number_based_number(int tonumber, int tobase)
	{
		this->decimal_number = tonumber;
		this->base = tobase;
		decimal_to_numeric_based(this->number_string, tonumber, tobase);
		if (this->decimal_number < 0)
		{
			this->number_string += '-';
		}
		this->number_string = this->string_reverse(this->number_string);
	}
	number_based_number(const number_based_number &other)
	{
		this->decimal_number = other.decimal_number;
		this->number_string = other.number_string;
		this->base = other.base;
	}
	bool operator < (const int &other)
	{
		if (this->decimal_number < other)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator > (const int &other)
	{
		return !(this->operator<(other));
	}
	bool operator < (const number_based_number &other)
	{
		if (this->decimal_number < other.decimal_number)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator > (const number_based_number &other)
	{
		return !(this->operator<(other));
	}
	friend std::ostream &operator<< (std::ostream &out, const number_based_number &number)
	{
		out << "<" << number.number_string << ", " << number.base<<">";
		return out;
	}
	void decimal_to_numeric_based(string &number_string, int number, int base)
	{
		if (number < 0)
		{
			number = abs(number);
		}
		if (base > 1 && base < 37)
		{
			if ((1.0 * number / base) >= 1)
			{
				if (number % base == 0)
				{
					number_string += '0';
					decimal_to_numeric_based(number_string, number / base, base);
				}
				else
				{
					number_string += to_char(number % base);
					decimal_to_numeric_based(number_string, ((number - (number % base)) / base), base);
				}
			}
			else
			{
				number_string += to_char(number);
				return;
			}
		}
	}
};

template<typename typet>
class swap_min_with_max
{
public:
	void function(vector<typet> *data)
	{
		if (data->empty())
		{
			cout << "Массив пуст";
		}
		else if (data->size() == 1)
		{
			cout << "В массиве один элемент, менять нечего";
		}
		else
		{
			auto minimal_position = min_element(data->begin(), data->end());
			auto maximal_position = max_element(data->begin(), data->end());
			typet temp = *minimal_position;
			*minimal_position = *maximal_position;
			*maximal_position = temp;
			//cout << "Обмен позиций <" << minimal_position._Ptr << ">:["<< *minimal_position <<"] и <" << maximal_position._Ptr << ">:[" << *maximal_position << "]";
		}
	}
	void function(typet *data, int size)
	{
		if (size < 1)
		{
			cout << "Массив пуст";
		}
		else if (size == 1)
		{
			cout << "В массиве один элемент, менять нечего";
		}
		else
		{
			typet *minimal = data;
			int minimal_position = 0;
			typet *maximal = data;
			int maximal_position = 0;
			for (int i = 1; i < size; ++i)
			{
				if (*minimal > data[i])
				{
					minimal = &data[i];
					minimal_position = i;
				}
				if (*maximal < data[i])
				{
					maximal = &data[i];
					maximal_position = i;
				}
			}
			typet temp = data[minimal_position];
			data[minimal_position] = data[maximal_position];
			data[maximal_position] = temp;
			cout << "Обмен позиций <" << minimal << ">:[" << *minimal << "] и <" << maximal << ">:[" << *maximal << "]";
		}
	}
};

template <>
class swap_min_with_max<char>
{
public:
	void function(vector<char> *data)
	{
		if (data->empty())
		{
			cout << "Массив пуст";
		}
		else if (data->size() == 1)
		{
			cout << "В массиве один элемент, менять нечего";
		}
		else
		{
			auto minimal_position = min_element(data->begin(), data->end());
			auto maximal_position = max_element(data->begin(), data->end());
			char temp = *minimal_position;
			*minimal_position = *maximal_position;
			*maximal_position = temp;
			//cout << "Обмен позиций <" << (void*)minimal_position._Ptr << ">:[" << *minimal_position << "] и <" << (void*)maximal_position._Ptr << ">:[" << *maximal_position << "]";
		}
	}
};

template<typename typet>
void display(vector<typet> *data)
{
	cout << "\n";
	for (auto &it : *data)
	{
		cout << setw(4);
		cout << it;
	}
	cout << "\n";
}

template<typename typet>
void display(typet *data, int size)
{
	cout << "\n";
	for (int i = 0; i < size; ++i)
	{
		cout << setw(4);
		cout << data[i];
	}
	cout << "\n";
}

template<typename typet>
void swap_function(vector<typet> *data)
{
	display(data);
	swap_min_with_max<typet> operation;
	operation.function(data);
	display(data);
}

template<typename typet>
void swap_function(typet *data, int size)
{
	display(data, size);
	swap_min_with_max<typet> operation;
	operation.function(data, size);
	display(data, size);
}


int main()
{
	setlocale(LC_ALL, "");

	cout << "vector<int>============================================================================================";
	vector<int> V{ 1, 5, 2, 24, 3, 6, 8, 7, 9, 22, 23, 0, 3 };
	vector<int> *Vpointer = &V;
	swap_function<int>(Vpointer);
	cout << "=======================================================================================================\n";

	cout << "A[13]==================================================================================================";
	const int Asize = 13;
	int A[Asize] = { 1, 5, 2, 24, 3, 6, 8, 7, 9, 22, 23, 0, 3 };
	int *Apointer = &A[0];
	swap_function(Apointer, Asize);
	cout << "=======================================================================================================\n";

	cout << "vector<char>===========================================================================================";
	vector<char> C{ 'e', 'f', 'a', 'b', 'c', 'd', 'm', 'l', 'k', 'j', 'i', 'h', 'g'};
	vector<char> *Cpointer = &C;
	swap_function<char>(Cpointer);
	cout << "=======================================================================================================\n";

	cout << "vector<string>=========================================================================================";
	vector<string> S{ "e", "f", "a", "b", "c", "d", "m", "l", "k", "j", "i", "h", "g"};
	vector<string> *Spointer = &S;
	swap_function<string>(Spointer);
	cout << "=======================================================================================================\n";

	cout << "vector<number_based_number>============================================================================";
	vector<number_based_number> NBN{ {-1, 2}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {1, 2}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
	vector<number_based_number> *NBNpointer = &NBN;
	swap_function<number_based_number>(NBNpointer);
	cout << "=======================================================================================================\n";

	system("pause>>void");
	return 0;
}