#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <ctime>

using namespace std;
const int SIZE = 20;

/*
Выбрать из таблицы 9.1 три вида контейнеров, для каждого вида выполнить, если это возможно следующие задания:
1.	Создать контейнер соответствии с вариантом в таблице 9.1 (СТОЛБЕЦ «Вид контейнера»)
2.	Заполнить его элементами использовать алгоритмы (generate(), fill(), iota())
3.	Заменить элементы в соответствии с вариантом (СТОЛБЕЦ «Задание 3») (использовать алгоритмы replace_if(), replace_copy(), replace_copy_if(), fill()).
4.	Удалить элементы в соответствии с вариантом в таблице 9.1 (СТОЛБЕЦ «Задание 4») (использовать алгоритмы remove(),remove_if(), remove_copy_if(),remove_copy())
5.	Отсортировать контейнер по убыванию и по возрастанию ключевого поля (использовать алгоритм sort()).
6.	Найти в контейнере заданный элемент (использовать алгоритмы find(), find_if(), count(), count_if()).
7.	Выполнить задание варианта в таблице 9.1 (СТОЛБЕЦ Задание «7») для полученного контейнера (использовать алгоритм for_each()) .
8.	Для выполнения всех заданий использовать стандартные алгоритмы библиотеки STL и желательно аннонимные (лямда) функции.
9.	Сделать вывод о возможностях и ограничениях использования алгоритмов для разных контейнеров.

20) Контейнер - список.
Адаптер контейнера - вектор. 
Ассоциативный контейнер - множество.
Задание 3. Найти минимальный элемент и добавить его на заданную позицию контейнера.
Задание 4. Найти элементы большие среднего арифметического и удалить их из контейнера.
Задание 7. Каждый элемент домножить на максимальный элемент контейнера.
*/

bool less_than(int a, int b)
{
	return a < b;
}

bool bigger_than(int a, int b)
{
	return a > b;
}

template<class classt>
void display(classt &t)
{
	cout << "\n{Содержание}: ";
	for (auto &it : t)
	{
		cout << "<"<< it << "> ";
	}
	cout << "\n";
}

int main()
{
	setlocale(LC_ALL, "");

	srand(time(NULL));

	cout << "=========================list<int>========================\n";
	list<int> LIST;
	cout << "\n\tgenerate()";
	for (int i = 0; i < SIZE; ++i) { LIST.push_back(0); }
	generate(LIST.begin(), LIST.end(), []()
	{
		srand(rand());
		return rand() % 900 + 100;
	});
	display(LIST);
	cout << "\n\tremove_if()\n";
	int LIST_avg = 0;
	for (auto &it : LIST)
	{
		LIST_avg += it;
	}
	LIST_avg /= LIST.size();
	cout << "\tLIST_avg = " << LIST_avg << "\n";
	cout << "Удаляются: ";
	auto less_than_avg_LIST = [LIST_avg](const int &a) { return a < LIST_avg; };
	auto it_LIST = find_if(LIST.begin(), LIST.end(), less_than_avg_LIST);
	while (it_LIST != LIST.end())
	{
		cout << "<" << *it_LIST << "> ";
		LIST.erase(remove(LIST.begin(), LIST.end(), *it_LIST));
		it_LIST = find_if(LIST.begin(), LIST.end(), less_than_avg_LIST);
	}
	display(LIST);
	cout << "\n\treplace(*min_element(), .front())";
	auto min_LIST = min_element(LIST.begin(), LIST.end());
	cout << "\n\tmin_LIST = " << *min_LIST;
	replace(LIST.begin(), LIST.end(), *min_LIST, LIST.front());
	display(LIST);
	cout << "\n\tsort()\n";
	cout << "\t.sort(less_than)";
	LIST.sort(less_than);
	display(LIST);
	cout << "\t.sort(bigger_than)";
	LIST.sort(bigger_than);
	display(LIST);
	cout << "\n\tit = (*it) * (*max_element())";
	auto LIST_max = max_element(LIST.begin(), LIST.end());
	for (auto &it : LIST)
	{
		it *= *LIST_max;
	}
	display(LIST);
	cout << "==========================================================\n\n";

	cout << "========================vector<int>=======================\n";
	vector<int> VECTOR;
	cout << "\n\tgenerate()";
	for (int i = 0; i < SIZE; ++i) { VECTOR.push_back(0); }
	generate(VECTOR.begin(), VECTOR.end(), []()
	{
		srand(rand());
		return rand() % 900 + 100;
	});
	display(VECTOR);
	cout << "\n\tremove_if()\n";
	int VECTOR_avg = 0;
	for (auto &it : VECTOR)
	{
		VECTOR_avg += it;
	}
	VECTOR_avg /= VECTOR.size();
	cout << "\tVECTOR_avg = " << VECTOR_avg << "\n";
	cout << "Удаляются: ";
	auto less_than_avg_VECTOR = [VECTOR_avg](const int &a) { return a < VECTOR_avg; };
	auto it_VECTOR = find_if(VECTOR.begin(), VECTOR.end(), less_than_avg_VECTOR);
	while (it_VECTOR != VECTOR.end())
	{
		cout << "<" << *it_VECTOR << "> ";
		VECTOR.erase(remove(VECTOR.begin(), VECTOR.end(), *it_VECTOR));
		it_VECTOR = find_if(VECTOR.begin(), VECTOR.end(), less_than_avg_VECTOR);
	}
	display(VECTOR);
	cout << "\n\treplace(*min_element(), .front())";
	auto min_VECTOR = min_element(VECTOR.begin(), VECTOR.end());
	cout << "\n\tmin_VECTOR = " << *min_VECTOR;
	replace(VECTOR.begin(), VECTOR.end(), *min_VECTOR, VECTOR.front());
	display(VECTOR);
	cout << "\n\tsort()\n";
	cout << "\t.sort(less_than)";
	sort(VECTOR.begin(), VECTOR.end(), less_than);
	display(VECTOR);
	cout << "\t.sort(bigger_than)";
	sort(VECTOR.begin(), VECTOR.end(), bigger_than);
	display(VECTOR);
	cout << "\n\tit = (*it) * (*max_element())";
	auto VECTOR_max = max_element(VECTOR.begin(), VECTOR.end());
	for (auto &it : VECTOR)
	{
		it *= (*VECTOR_max);
	}
	display(VECTOR);
	cout << "==========================================================\n\n";

	cout << "==========================set<int>========================\n";
	set<int> SET;
	cout << "\n\t.insert(rand())";
	for (int i = 0; i < SIZE; ++i) { SET.insert(rand()%900 + 100); }
	display(SET);
	cout << "\n\tremove_if()\n";
	int SET_avg = 0;
	for (auto &it : SET)
	{
		SET_avg += it;
	}
	SET_avg /= SET.size();
	cout << "\tSET_avg = " << SET_avg << "\n";
	cout << "Удаляются: ";
	auto less_than_avg_SET = [SET_avg](const int &a) { return a < SET_avg; };
	bool SET_success = true;
	while (SET_success)
	{
		SET_success = false;
		auto it_SET = find_if(SET.begin(), SET.end(), less_than_avg_SET);
		if (it_SET != SET.end())
		{
			cout << "<" << *it_SET << "> ";
			SET.erase(it_SET);
			SET_success = true;
		}
	}
	display(SET);
	cout << "==========================================================";

	system("pause>>void");
	return 0;
}