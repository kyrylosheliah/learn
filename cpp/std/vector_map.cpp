#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");

	cout << "Задача №1(вектор). В A = (a1, а2, ..., аn) все отрицательные элементы отправить в «хвост».\n";
	vector<int> A{ -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> Atemp;
	auto *Apointer = &A;
	cout << "\n";
	for (auto &it : A)
	{
		cout << setw(4);
		cout << it;
	}
	cout << "\n";
	for (vector<int>::iterator it = A.begin(); it != A.end(); ++it)
	{
		if (*it < 0)
		{
			Atemp.push_back(*it);
		}
	}
	for (auto &it : Atemp)
	{
		A.erase(find(A.begin(), A.end(), it));
		A.push_back(it);
	}
	cout << "\n";
	for (auto &it : A)
	{
		cout << setw(4);
		cout << it;
	}
	cout << "\n";


	cout << "=================================================";
	cout << "\nЗадача №2(список). Подсчитать количество слов списка, которые начинаются и оканчиваются одной и той же литерой.\n";
	map<string, int> count;
	list<string> B{
	"abcd",
	"bcde",
	"cdef",
	"defg",
	"efgh",
	"fghi",
	"ghij",
	"ghij",
	"fghi",
	"efgh",
	"defg",
	"cdef",
	"bcde",
	"abcd" };
	cout << "\n";
	for (auto &it : B)
	{
		cout << setw(8);
		cout << it;
	}
	cout << "\n";
	for (list<string>::iterator it = B.begin(); it != B.end(); ++it)
	{
		string tocount;
		tocount += it->at(0);
		tocount += it->at(it->size() - 1);
		map<string, int>::iterator sought_for = count.find(tocount);
		if (sought_for != count.end())
		{
			++sought_for->second;
		}
		else
		{
			count.insert(make_pair(tocount, 1));
		}
	}
	cout << "\nПервая и последняя буквы | количество вхождений\n";
	for (auto &it : count)
	{
		cout << setw(8) << it.first << setw(8) << it.second;
		cout << "\n";
	}

	system("pause>>void");
	return 0;
}