#include <iostream>
#include <string>
using namespace std;

void menu0();
void menu1();
void menu2(int number, int base);

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

char to_char(int number)
{
	char letter;
	switch (number)
	{
	case 0: {return '0'; } break;
	case 1: {return '1';} break;
	case 2: {return '2';} break;
	case 3: {return '3';} break;
	case 4: {return '4';} break;
	case 5: {return '5';} break;
	case 6: {return '6';} break;
	case 7: {return '7';} break;
	case 8: {return '8';} break;
	case 9: {return '9';} break;
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
	case 35: {return 'Z';} break;
	default: {return '?'; } break;
	}
}

void decimal_to_numeric_based(string &number_string, int number, int base)
{
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

void menu0()
{
	while (true)
	{
		cout << "Вход: |1 - Начало, 2 - Выход| >> ";

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
	int int_answer;
	cout << "Введите десятичное число >> ";
	cin >> int_answer;
	cout << "Выберите систему счисления: |2 - Двоичная, ..., 36 - Тридцатишестиричная| >> ";
	int base_answer;
	cin >> base_answer;
	while (base_answer < 2 || base_answer > 36)
	{
		cout << ">> ";
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		cin >> base_answer;
	}

	menu2(int_answer, base_answer);

	cout << "\n_Выход\n\n";
	system("pause>>void");
}

void menu2(int int_answer, int base_answer)
{
	if (base_answer > 1 && base_answer < 37)
	{
		string number_string;
		decimal_to_numeric_based(number_string, int_answer, base_answer);
		number_string = string_reverse(number_string);
		cout << "В системе счисления с основанием " << base_answer << " это число будет: " << number_string;
	}
	else
	{
		return;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	menu0();

	return 0;
}