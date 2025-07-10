#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <utility>
using namespace std;

constexpr int coutW = 16;
constexpr int coutP = 12;
constexpr long double calc_step = 0.5;
constexpr int calc_row_depth = 21;

int get_user_int(const int &, const int &);
long double get_user_double(const long double &, const long double &);
pair<long double, long double> get_user_interval();
void tabulate_list(const list<vector<long double>> &);
unsigned long long factorial(const unsigned long long &);
long double sin_Tailor_row(const long double &, const int&);
long double sin_builtin_holder(const long double &);
long double get0(const long double &) { return 0; }
long double get0(const long double &, const int &) { return 0; }
void menu0();
void menu1();
void menu2(const pair<long double, long double> &, list<vector<long double>> &, long double(*)(const long double &), long double(*)(const long double &, const int &));

int get_user_int(const int &from, const int &to)
{
	cout << "[!] Введите число от " << from << " до " << to << ":\n>> ";
	unsigned long long answer;
	cin >> answer;
	while (answer < from || answer > to)
	{
		cout << "WRONG VALUE >> ";
		if (cin.fail()) { cin.clear(); }
		cin.ignore(INT_MAX, '\n');
		cin >> answer;
	}
	return answer;
}

long double get_user_double(const long double &from, const long double &to)
{
	cout << "[!] Введите число от " << from << " до " << to << ":\n>> ";
	long double answer;
	cin >> answer;
	while (answer < from || answer > to)
	{
		cout << "WRONG VALUE >> ";
		if (cin.fail()) { cin.clear(); }
		cin.ignore(INT_MAX, '\n');
		cin >> answer;
	}
	return answer;
}

pair<long double, long double> get_user_interval()
{
	cout << "[!] Введите интервал:\n[!] from >> ";
	long double from_ans = get_user_double(-INT_MAX, INT_MAX);
	cout << "[!] to >> ";
	long double to_ans = get_user_double(-INT_MAX, INT_MAX);
	pair<long double, long double> toreturn = make_pair(from_ans, to_ans);
	return toreturn;
}

void tabulate_list(const list<vector<long double>> & data)
{
	cout.precision(coutP);
	cout << setw(coutW) << "x |" << setw(coutW) << "y built-in |" << setw(coutW) << "y Tailor |";
	for (auto iterator_list : data)
	{
		cout << "\n";
		for (auto iterator_vector : iterator_list)
		{
			cout << setw(coutW) << iterator_vector;
		}
	}
}

unsigned long long factorial(const unsigned long long &x)
{
	
	switch (x)
	{
	case 2: { return 2; }; break;
	case 3: { return 6; }; break;
	case 4: { return 24; }; break;
	case 5: { return 120; }; break;
	case 6: { return 720; }; break;
	case 7: { return 5040; }; break;
	case 8: { return 40320; }; break;
	case 9: { return 362880; }; break;
	case 10: { return 3628800; }; break;
	case 11: { return 39916800; }; break;
	case 12: { return 479001600; }; break;
	case 13: { return 6227020800; }; break;
	case 14: { return 87178291200; }; break;
	case 15: { return 1307674368000; }; break;
	case 16: { return 20922789888000; }; break;
	case 17: { return 355687428096000; }; break;
	case 18: { return 6402373705728000; }; break;
	case 19: { return 121645100408832000; }; break;
	case 20: { return 2432902008176640000; }; break;
	default: 
	{
		if (x < 2) { return 1; }
		else { return 18446744073709551615; }
	}; break;
	}
	/*
	if (x < 2) { return 1; }
	unsigned long long result{ 1 };
	for (unsigned long long i = x; i >= 2; --i) { result *= i; }
	return result;
	*/
}

long double sin_Tailor_row(const long double &x, const int &precision)
{
	long double result{ 0 };
	for (int i = 0; i < precision; ++i)
	{
		result += pow(-1, i) * pow(x, ((2 * i) + 1)) / factorial((2 * i) + 1);
	}
	return result;
}

long double sin_builtin_holder(const long double &x)
{
	return sin(x);
}

void menu0()
{
	while (true)
	{
		system("cls");
		cout << "Вход:\n1 - Начало\n2 - Выход\n";
		unsigned long long input_answer = get_user_int(1, 2);
		if (input_answer == 1) { menu1(); }
		else { break; }
	}
	cout << "[!] Выход из menu0\n";
	system("pause>>void");
}

void menu1()
{
	cout << "menu1()\n";
	pair<long double, long double> answer = get_user_interval();
	//pair<long double, long double> answer{ -1.5707963267, 1.5707963267 };
	list<vector<long double>> data;

	cout << "===\n";
	auto start = chrono::steady_clock::now();
	menu2(answer, data, sin_builtin_holder, sin_Tailor_row);
	auto end = chrono::steady_clock::now();
	auto diff1 = end - start;
	tabulate_list(data);
	data.clear();
	cout << "\nВременная сложность выполенения: " << chrono::duration <long double, nano>(diff1).count() << " ns\n";
	cout << "Временная сложность выполенения: " << chrono::duration <long double, milli>(diff1).count() << " ms\n";

	cout << "===\n";
	start = chrono::steady_clock::now();
	menu2(answer, data, sin_builtin_holder, get0);
	end = chrono::steady_clock::now();
	auto diff2 = end - start;
	tabulate_list(data);
	data.clear();
	cout << "\nВременная сложность выполенения: " << chrono::duration <long double, nano>(diff2).count() << " ns\n";
	cout << "Временная сложность выполенения: " << chrono::duration <long double, milli>(diff2).count() << " ms\n";

	cout << "===\n";
	start = chrono::steady_clock::now();
	menu2(answer, data, get0, sin_Tailor_row);
	end = chrono::steady_clock::now();
	auto diff3 = end - start;
	tabulate_list(data);
	data.clear();
	cout << "\nВременная сложность выполенения: " << chrono::duration <long double, nano>(diff3).count() << " ns\n";
	cout << "Временная сложность выполенения: " << chrono::duration <long double, milli>(diff3).count() << " ms\n";

	cout << "\n";
	auto time_sin = diff1 - diff3;
	auto time_Tailor = diff1 - diff2;
	cout << "\nВременная сложность sin(): " << chrono::duration <long double, nano>(time_sin).count() << " ns\n";
	cout << "Временная сложность sin(): " << chrono::duration <long double, milli>(time_sin).count() << " ms\n";
	cout << "\nВременная сложность sin_Tailor_row(): " << chrono::duration <long double, nano>(time_Tailor).count() << " ns\n";
	cout << "Временная сложность sin_Tailor_row(): " << chrono::duration <long double, milli>(time_Tailor).count() << " ms\n";
	cout << "\n";

	cout << "[!] Выход из menu1\n";
	system("pause>>void");
}

void menu2(const pair<long double, long double> &answer, list<vector<long double>> & data, long double(*sin_bi)(const long double&), long double(*sin_T)(const long double&, const int&))
{
	for (long double x = answer.first; x <= answer.second; x += calc_step)
	{
		data.push_back(vector<long double>(3));
		data.back().at(0) = x;
		data.back().at(1) = sin_bi(x);
		data.back().at(2) = sin_T(x, calc_row_depth);
	}
}

int main()
{
	setlocale(LC_ALL, "");
	menu0();
	cout << "[!] Выход из main\n";
	system("pause>>void");
	return 0;
}