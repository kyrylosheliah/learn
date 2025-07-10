#include <iostream>
#include <conio.h>
#include <random>
#include <time.h>
char name1[30];
char name2[30];
char table[3][3];
bool step;
int moves_done = 0; // как вариант счетчик ходов и возвращение win() как значений победы и проигрыша, так и отсутствия комбинации
// при условии, что совершено 9 ходов и было возвращено значение отсутствия ряда, делаем ветвление ничьей
void instruction()
{
	std::cout << "\t\t*** Крестики-Нолики***\n\n";
	std::cout << "Правила:\n";
	std::cout << "Играют 2 игрока на поле 3х3\n";
	std::cout << "Побеждает тот, кто составит выйгрышную комбинацию\n";
	std::cout << "Вид поля:\n\n";
	int l = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << "|" << l + 1 << ' ';
			table[i][j] = char(49 + l);
			++l;
		}
		std::cout << "|\n";
	}
	std::cout << "\nДля хода нажмите цифру ячейки поля\n";
	std::cout << "Для начала игры нажмите клавишу:";
	system("pause>>void");
}
bool input()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << "|" << table[i][j] << " ";
		}
		std::cout << "|\n";
	}
	std::cout << "\n";
	if (step)
	{
		std::cout << "Ходит " << name1 << " : ";
	}
	else
	{ 
		std::cout << "Ходит " << name2 << " : ";
	}
	int n;
	std::cin >> n;
	if (n < 1 || n > 9) // ввод удачный
	{
		return false;
	}
	int i, j;
	if (n % 3 == 0)
	{
		i = n / 3 - 1;
		j = 2;
	}
	else
	{
		j = n % 3 - 1;
		i = n / 3;
	}
	if (table[i][j] == 'O' || table[i][j] == 'X') 
	{
		return false;
	}
	if (step)
	{
		table[i][j] = 'X';
		step = false;
	}
	else
	{
		table[i][j] = 'O';
		step = true;
	}
	++moves_done; // тогда засчитываем шаг
	return true;
}
char win() // можно возвращать все что угодно, пусть будет символы 'O', 'X' из таблицы и '-'
{
	for (int i = 0; i < 3; ++i)
	{
		if ((table[i][0] == table[i][1]) && (table[i][0] == table[i][2]))
		{
			return table[i][0];
		}
		else
		{
			if ((table[0][i] == table[1][i]) && (table[0][i] == table[2][i])) 
			{
				return table[0][i];
			}
			else if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2]))
			{
				return table[0][0];
			}
			else if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0])) 
			{
				return table[0][2];
			}
		}
	}
	return '-';
}
int main()
{
	setlocale(LC_ALL, "Russian");
	instruction();

	//system("cls");
	std::cout << "\n===\n";
	std::cout << "Введите имя 1 игрока:";
	std::cin.getline(name1, 30);
	std::cout << "Введите имя 2 игрока:";
	std::cin.getline(name2, 30);
	srand(time(NULL));
	if (rand() & 1) 
	{
		step = true;
	}
	else
	{
		step = false;
	}
	char winner = win();
	while (winner == '-')
	{
		//system("cls");
		if (moves_done > 8) // мониторинг стадии игры
		{
			break;
		}
		std::cout << "\n===\n";
		if (!input())
		{
			std::cout << "Вы ввели неверные данные повторите!";
			system("pause>>void");
		}
		winner = win();
	}
	//system("cls");
	std::cout << "\n===\n";
	if ((moves_done > 8) && (winner == '-'))
	{
		std::cout << "Вас подебил и просто уничтожил Понасенков Евгений Николаевич\n";
	}
	else
	{
		if (step)
		{
			std::cout << "Победил " << name2 << "\n";
		}
		else
		{
			std::cout << "Победил " << name1 << "\n";
		}
	}

	system("pause>>void");
	return 0;
}
