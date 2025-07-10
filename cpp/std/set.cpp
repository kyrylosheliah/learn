/*
20.	Вариант: Контрольная по ударениям
Учительница задала Пете домашнее задание — в заданном тексте расставить ударения в словах, после чего поручила Васе проверить это домашнее задание. Вася очень плохо знаком с данной темой, поэтому он нашел словарь, в котором указано, как ставятся ударения в словах. К сожалению, в этом словаре присутствуют не все слова. Вася решил, что в словах, которых нет в словаре, он будет считать, что Петя поставил ударения правильно, если в этом слове Петей поставлено ровно одно ударение.
Оказалось, что в некоторых словах ударение может быть поставлено больше, чем одним способом. Вася решил, что в этом случае если то, как Петя поставил ударение, соответствует одному из приведенных в словаре вариантов, он будет засчитывать это как правильную расстановку ударения, а если не соответствует, то как ошибку.
Вам дан словарь, которым пользовался Вася и домашнее задание, сданное Петей. Ваша задача — определить количество ошибок, которое в этом задании насчитает Вася.
Вводится сначала число N — количество слов в словаре (0≤N≤20000).
Далее идет N строк со словами из словаря. Каждое слово состоит не более чем из 30 символов. Все слова состоят из маленьких и заглавных латинских букв. В каждом слове заглавная ровно одна буква — та, на которую попадает ударение. Слова в словаре расположены в алфавитном порядке. Если есть несколько возможностей расстановки ударения в одном и том же слове, то эти варианты в словаре идут в произвольном порядке.
Далее идет упражнение, выполненное Петей. Упражнение представляет собой строку текста, суммарным объемом не более 300000 символов. Строка состоит из слов, которые разделяются между собой ровно одним пробелом. Длина каждого слова не превышает 30 символов. Все слова состоят из маленьких и заглавных латинских букв (заглавными обозначены те буквы, над которыми Петя поставил ударение). Петя мог по ошибке в каком-то слове поставить более одного ударения или не поставить ударения вовсе.
Выведите количество ошибок в Петином тексте, которые найдет Вася.

<Ввод>
4
cAnnot
cannOt
fOund
pAge
thE pAge cAnnot be fouNd
<Вывод>
2
<Комментарии>
В слове cannot, согласно словарю возможно два варианта расстановки ударения. Эти варианты в словаре могут быть перечислены в любом порядке (т.е. как сначала cAnnot, а потом cannOt, так и наоборот).
Две ошибки, совершенные Петей — это слова be (ударение вообще не поставлено) и fouNd (ударение поставлено неверно). Слово thE отсутствует в словаре, но поскольку в нем Петя поставил ровно одно ударение, признается верным.

<Ввод>
4
cAnnot
cannOt
fOund
pAge
The PAGE cannot be found
<Вывод>
4
<Комментарии>
Неверно расставлены ударения во всех словах, кроме The (оно отсутствует в словаре, в нем поставлено ровно одно ударение). В остальных словах либо ударные все буквы (в слове PAGE), либо не поставлено ни одного ударения.

*/
#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;

int to_int(char letter)
{
	switch(letter)
	{
	case 'a': { return 1; }; break;
	case 'b': { return 2; }; break;
	case 'c': { return 3; }; break;
	case 'd': { return 4; }; break;
	case 'e': { return 5; }; break;
	case 'f': { return 6; }; break;
	case 'g': { return 7; }; break;
	case 'h': { return 8; }; break;
	case 'i': { return 9; }; break;
	case 'j': { return 10; }; break;
	case 'k': { return 11; }; break;
	case 'l': { return 12; }; break;
	case 'm': { return 13; }; break;
	case 'n': { return 14; }; break;
	case 'o': { return 15; }; break;
	case 'p': { return 16; }; break;
	case 'q': { return 17; }; break;
	case 'r': { return 18; }; break;
	case 's': { return 19; }; break;
	case 't': { return 20; }; break;
	case 'u': { return 21; }; break;
	case 'v': { return 22; }; break;
	case 'w': { return 23; }; break;
	case 'x': { return 24; }; break;
	case 'y': { return 25; }; break;
	case 'z': { return 26; }; break;
	case 'A': { return 27; }; break;
	case 'B': { return 28; }; break;
	case 'C': { return 29; }; break;
	case 'D': { return 30; }; break;
	case 'E': { return 31; }; break;
	case 'F': { return 32; }; break;
	case 'G': { return 33; }; break;
	case 'H': { return 34; }; break;
	case 'I': { return 35; }; break;
	case 'J': { return 36; }; break;
	case 'K': { return 37; }; break;
	case 'L': { return 38; }; break;
	case 'M': { return 39; }; break;
	case 'N': { return 40; }; break;
	case 'O': { return 41; }; break;
	case 'P': { return 42; }; break;
	case 'Q': { return 43; }; break;
	case 'R': { return 44; }; break;
	case 'S': { return 45; }; break;
	case 'T': { return 46; }; break;
	case 'U': { return 47; }; break;
	case 'V': { return 48; }; break;
	case 'W': { return 49; }; break;
	case 'X': { return 50; }; break;
	case 'Y': { return 51; }; break;
	case 'Z': { return 52; }; break;
	default: { return -1; }; break;
	}
}

bool is_stress_and_vowel(char letter)
{
	int number = to_int(letter);
	switch (number)
	{
	case 27: { return true; }; break;
	case 31: { return true; }; break;
	case 35: { return true; }; break;
	case 41: { return true; }; break;
	case 47: { return true; }; break;
	case 51: { return true; }; break;
	default: { return false; }; break;
	}
}

void fill_with_strings(string &input_from, list<string> &text_to)
{
	while (!input_from.empty())
	{
		string temp;
		int size = input_from.size();
		for (int i = 0; i < size; ++i)
		{
			if (input_from[0] != ' ')
			{
				temp += input_from[0];
				input_from.erase(input_from.begin());
			}
			else
			{
				input_from.erase(input_from.begin());
				break;
			}
		}
		text_to.push_back(temp);
	}
}

void display_set_list(set<string> &dictionary, list<string> &text)
{
	cout << "Введено:\n{dictionary}: ";
	for (auto &it : dictionary)
	{
		cout << "<" << it << ">, ";
	}
	cout << "\n{text}: ";
	for (auto &it : text)
	{
		cout << "<" << it << ">, ";
	}
	cout << "\n";
}

int сount_stress(set<string> &dictionary, list<string> &text)
{
	int mistake_count = 0;
	for (auto &it : text)
	{
		int stress_counter = 0;
		for (int i = 0; i < it.size(); ++i)
		{
			if (is_stress_and_vowel(it[i]))
			{
				++stress_counter;
			}
		}
		bool found_flag = false;
		if (dictionary.find(it) != dictionary.end())
		{
			found_flag = true;
		}
		if (found_flag)
		{
			continue;
		}
		else if (stress_counter == 1)
		{
			continue;
		}
		else
		{
			++mistake_count;
		}
	}
	return mistake_count;
}

int main()
{
	setlocale(0, "");

	set<string> dictionary;
	list<string> text;

	dictionary.insert("cAnnot");
	dictionary.insert("cannOt");
	dictionary.insert("fOund");
	dictionary.insert("pAge");

	string input{ "thE pAge cAnnot be fouNd" };
	fill_with_strings(input, text);
	display_set_list(dictionary, text);
	int text_1st_mistake_count = сount_stress(dictionary, text);
	cout << "Ошибки в первом тексте: " << text_1st_mistake_count <<"\n\n";

	text.clear();
	input = "The PAGE cannot be found";
	fill_with_strings(input, text); 
	display_set_list(dictionary, text);
	int text_2nd_mistake_count = сount_stress(dictionary, text);
	cout << "Ошибки во втором тексте: " << text_2nd_mistake_count;

	system("pause>>void");
	return 0;
}