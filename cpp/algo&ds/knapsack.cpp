#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

void read_data();
void greedy_algorythm();
void iterational_algorythm();

struct item
{
	int item_weight;
	int item_number;
};

int knapsack_weight;
int item_count;
const int my_item_count = 30;
item weight_array[my_item_count];

void read_data()
{
	item_count = 0;
	ifstream FILE("input.txt");
	FILE >> knapsack_weight;
	while (FILE >> weight_array[item_count].item_weight)
	{
		weight_array[item_count].item_number = item_count;
		item_count++;
	}
	FILE.close();
}

void greedy_algorythm()
{
	item temporary;
	for (int i = 0; i < item_count; i++)
	{
		for (int j = 0; j < item_count - 1; j++)
		{
			if (weight_array[j].item_weight < weight_array[j + 1].item_weight)
			{
				temporary = weight_array[j];
				weight_array[j] = weight_array[j + 1];		// ���������� �� �������� � �������� � weight_array[]
				weight_array[j + 1] = temporary;
			}
		}
	}

	int best_weight = 0, set_number = 0;

	while (knapsack_weight)
	{
		if ((weight_array[set_number].item_weight + best_weight) < knapsack_weight) // ���� ���������� � ������
		{
			best_weight += weight_array[set_number].item_weight;	// �������� �������� �� ������� �� �������� � ��������
		}
		else
		{
			break;
		}
		set_number++;
	}

	bitset<my_item_count> bit_combination = 0;
	for (int i = 0; i < set_number; i++)	// �.�. ��������� ����� ������� ����������, ������� ����������,
	{
		bit_combination[weight_array[i].item_number] = true; // �� �������� ��� ������ set_number ���������
	}
	cout << "������ ���������� ��������� : " << bit_combination << "\n";
	cout << "��� ���������:\t";
	for (int i = 0; i < set_number; i++)
	{
		cout << weight_array[i].item_weight << "\t";
	}
	system("pause>>void");
}

void iterational_algorythm()
{
	unsigned long iterations_count = 1 << item_count;
	int weight = 0, best_weight = 0;
	bitset<my_item_count> bit_combination;
	bitset<my_item_count> best_bit_combination;

	for (int i = 0; i < iterations_count; i++)
	{
		unsigned long bit_position;
		_BitScanForward(&bit_position, i);
		bit_combination[bit_position] = !bit_combination[bit_position];
		if (bit_combination[bit_position])
		{
			weight += weight_array[bit_position].item_weight;
		}
		else
		{
			weight -= weight_array[bit_position].item_weight;
		}
		if (weight > knapsack_weight)
		{
			continue;
		}
		else if (weight > best_weight)
		{
			best_weight = weight;
			best_bit_combination = bit_combination;
		}
	}
	cout << "������ ���������� ���������: " << best_bit_combination << "\n��� ���������: \n";
	for (int i = 0; i < my_item_count; i++)
	{
		if (best_bit_combination[i])
		{
			cout << weight_array[i].item_weight << "\t";
		}
	}
	system("pause>>void");
}

void menu()
{
	int answer = 0;
	bool exit_flag = true;
	while (exit_flag)
	{
		system("cls");
		cout << "�������� ��������\n1 - �������� ��������\n2 - ������ ��������\n3 - �����\n";
		cin >> answer;
		switch (answer)
		{
		case 1:
			read_data();
			iterational_algorythm();
			system("pause>>void");
			break;
		case 2:
			read_data();
			greedy_algorythm();
			system("pause>>void");
			break;
		case 3:
			exit_flag = false;
			break;
		default:
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	
	menu();
}