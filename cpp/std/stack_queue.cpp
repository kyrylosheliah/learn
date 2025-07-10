#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
1. Написать процедуру(ы), которая определяет, есть ли в стеке St1 элементы, которые не входят в стек St2.
2. Написать процедуру(ы), необходимые для определения среднего арифметического элементов очереди Queue между первым и последним вхождением элемента Е, если элемент Е входит в очередь не менее двух раз.
*/

int main()
{
	setlocale(LC_ALL, "");

	cout << "==================================================================\n";
	cout << "Элементы в STACK1, не входящие в STACK2\n";
	stack<string> STACK1;
	STACK1.push("a"); STACK1.push("b"); STACK1.push("c"); STACK1.push("d"); STACK1.push("e");
	stack<string> STACK2;
	STACK2.push("c"); STACK2.push("d"); STACK2.push("e"); STACK2.push("f"); STACK2.push("g");
	list<string> data_list;
	while (!STACK2.empty())
	{
		data_list.push_back(STACK2.top());
		STACK2.pop();
	}
	while (!STACK1.empty())
	{
		auto result = find(data_list.begin(), data_list.end(), STACK1.top());
		if (result == data_list.end())
		{
			cout << "Найдена строка " << STACK1.top() << "\n";
		}
		STACK1.pop();
	}
	cout << "==================================================================\n\n";
	
	cout << "==================================================================\n";
	queue<int> QUEUE;
	QUEUE.push(3); QUEUE.push(6); QUEUE.push(5); QUEUE.push(3); QUEUE.push(4); QUEUE.push(3); QUEUE.push(2); QUEUE.push(1);
	vector<vector<int>> VECTOR;
	int mark = 3;
	cout << "Очередь: ";
	while (!QUEUE.empty())
	{
		if (QUEUE.front() == mark)
		{
			VECTOR.push_back({ QUEUE.front() });
			cout << QUEUE.front() << " - ";
			QUEUE.pop();
		}
		else
		{
			VECTOR[VECTOR.size() - 1].push_back(QUEUE.front());
			cout << QUEUE.front() << " - ";
			QUEUE.pop();
		}
	}
	if (VECTOR.size() < 2)
	{
		cout << "\nВ очереди не существует хотя бы двух";
	}
	else
	{
		cout << "\nСумма чисел: ";
		int sum = 0;
		for (int i = 0; i < VECTOR.size() - 1; ++i)
		{
			for (int j = 0; j < VECTOR[i].size(); ++j)
			{
				cout << VECTOR[i][j] << " + ";
				sum += VECTOR[i][j];
			}
		}
		cout << mark;
		sum += mark;
		cout << "\nСумма = " << sum << "\n";
	}
	cout << "==================================================================\n";

	system("pause>>void");
	return 0;
}