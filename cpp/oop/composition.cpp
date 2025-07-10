
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

// TODO: get rid of Windows API in favor of crossplatform terminal API

/*Для приведенных ниже заданий(задача 1 и задача 2) составить программы на языке С++, в которых производится формирование и вывод на экран движущихся графических фигур.В программе должно быть предусмотрено :
−	описание абстрактного класса, включающего виртуальные и чисто виртуальные методы для задания параметров графической фигуры, вывода её на экран;
−	определение необходимых производных классов, переопределение описанных выше виртуальных методов;
−	в главной функции необходимо создать класс - контейнер или массив указателей на объекты абстрактного класса, который заполнить массивами графических фигур;
−	вызвать переопределенные методы через объекты абстрактного класса.*/

// 20. Окружности и квадраты различных цветов и размеров, появляющиеся в различных местах экрана, трижды мигают на одном месте различными цветами и затем меняют свое местоположение.
// 20. Координатная сетка с расположенными на ней окружностями разного цвета разворачивается против часовой стрелки

class rgb
{
public:
	int r, g, b;
	rgb() { this->r = 0; this->g = 0; this->b = 0; }
	rgb(int R, int G, int B) { this->r = R; this->g = G; this->b = B; }
	rgb(const rgb &other) { this->r = other.r; this->g = other.g; this->b = other.b; }
};

class dot
{
public:
	int x, y;
	dot() { this->x = 0; this->y = 0; }
	dot(int X, int Y) { this->x = X; this->y = Y; }
	dot(const dot &other) { this->x = other.x; this->y = other.y; }
};

class coordinate_system_grid
{
public:
	dot **grid;
	int size;
	~coordinate_system_grid()
	{
		for (int i = 0; i < this->size; ++i)
		{
			delete[] grid[i];
		}
		delete[]grid;
	}
	void resize(int tosize)
	{
		this->size = tosize;
		grid = new dot*[tosize];
		for (int i = 0; i < tosize; ++i)
		{
			grid[i] = new dot[tosize];
		}
		int half = tosize / 2;
		int x_lower_value = -half;
		int y_lower_value = -half;

		for (int i = 0; i < tosize; ++i)
		{
			for (int j = 0; j < tosize; ++j)
			{
				grid[i][j].x = x_lower_value;
				grid[i][j].y = y_lower_value;
				++x_lower_value;
			}
			x_lower_value = -half;
			++y_lower_value;
		}
	}
};

class shape
{
public:
	int x_position, y_position, size;
	coordinate_system_grid xy_grid;
	bool **image_mask = new bool*[0];
	rgb color;
	shape(){}
	void define_location_and_color(dot A, rgb tocolor)
	{
		this->x_position = abs(A.x);
		this->y_position = abs(A.y);
		this->color.r = tocolor.r;
		this->color.g = tocolor.g;
		this->color.b = tocolor.b;
	}
	void display()
	{
		if (this->size > 0)
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			RECT window = {};
			for (int i = 0; i < this->size; ++i)
			{
				for (int j = 0; j < this->size; ++j)
				{
					if (this->image_mask[i][j])
					{
						SetPixel(hdc, (i + this->x_position), (j + this->y_position), RGB(this->color.r, this->color.g, this->color.b));
					}
				}
			}
			ReleaseDC(hwnd, hdc);
		}
	}
	virtual void render()
	{
	}
};

class rectangle : public shape
{
public:
	~rectangle()
	{
		for (int i = 0; i < this->size; ++i)
		{
			delete [] image_mask[i];
		}
		delete [] image_mask;
	}
	rectangle(dot A, int tosize, rgb tocolor)
	{
		define_location_and_color(A, tocolor);
		xy_grid.resize(tosize);
		this->size = tosize;
		this->image_mask = new bool*[tosize];
		for (int i = 0; i < tosize; ++i)
		{
			this->image_mask[i] = new bool[tosize];
			for (int j = 0; j < tosize; ++j)
			{
				this->image_mask[i][j] = false;
			}
		}
		render();
	}
	void render() override
	{
		for (int i = 0; i < this->size; ++i)
		{
			for (int j = 0; j < this->size; ++j)
			{
				this->image_mask[i][j] = true;
			}
		}
	}
};

class circle : public shape
{
public:
	int radius;
	~circle()
	{
		for (int i = 0; i < this->size; ++i)
		{
			delete [] image_mask[i];
		}
		delete [] image_mask;
	}
	circle(dot A, int tosize, rgb tocolor)
	{
		define_location_and_color(A, tocolor);
		this->xy_grid.resize(tosize);
		this->size = tosize;
		this->radius = tosize / 2;
		this->image_mask = new bool*[tosize];
		for (int i = 0; i < tosize; ++i)
		{
			this->image_mask[i] = new bool[tosize];
			for (int j = 0; j < tosize; ++j)
			{
				this->image_mask[i][j] = false;
			}
		}
		this->render();
	}
	void render() override
	{
		for (int i = 0; i < this->size; ++i)
		{
			for (int j = 0; j < this->size; ++j)
			{
				int x_radius = this->xy_grid.grid[i][j].x;
				int y_radius = this->xy_grid.grid[i][j].y;
				if (sqrt(pow(x_radius, 2) + pow(y_radius, 2)) <= this->radius)
				{
					this->image_mask[i][j] = true;
				}
			}
		}
	}
};

class grid_image : public shape
{
public:
	int frequency;
	~grid_image()
	{
		for (int i = 0; i < this->size; ++i)
		{
			delete [] image_mask[i];
		}
		delete [] image_mask;
	}
	grid_image(dot A, int tosize, rgb color, int tofrequent)
	{
		define_location_and_color(A, color);
		xy_grid.resize(tosize);
		this->size = tosize;
		this->frequency = tofrequent;
		this->image_mask = new bool*[tosize];
		for (int i = 0; i < tosize; ++i)
		{
			this->image_mask[i] = new bool[tosize];
			for (int j = 0; j < tosize; ++j)
			{
				this->image_mask[i][j] = false;
			}
		}
		this->render();
	}
	void render() override
	{
		for (int i = 0; i < this->size; ++i)
		{
			for (int j = 0; j < this->size; ++j)
			{
				if (!(i % this->frequency) || !(j % this->frequency))
				{
					this->image_mask[i][j] = true;
				}
			}
		}
	}
};

class operation1
{
public:
	int shapes_amount = 20;
	int task_x_size = 1000;
	int task_y_size = 500;
	shape **data;
	operation1()
	{
		this->data = new shape*[this->shapes_amount];
		for (int i = 0; i < this->shapes_amount; ++i)
		{
			this->data[i] = new shape();
		}
	}
	~operation1()
	{
		for (int i = 0; i < this->shapes_amount; ++i)
		{
			delete data[i];
		}
		delete [] data;
	}
	void refill()
	{
		for (int i = 0; i < this->shapes_amount; ++i)
		{
			shape *todelete = this->data[i];
			this->data[i] = nullptr; 
			delete todelete;
			srand(time(NULL) + rand()); bool random = rand() % 2; 
			srand(time(NULL) + rand()); int tosize = rand() % 101; 
			srand(time(NULL) + rand()); int tox = rand() % (task_x_size - tosize + 1);
			srand(time(NULL) + rand()); int toy = rand() % (task_y_size - tosize + 1); 
			srand(time(NULL) + rand()); int tor = rand() % 256; 
			srand(time(NULL) + rand()); int tog = rand() % 256; 
			srand(time(NULL) + rand()); int tob = rand() % 256;
			dot A(tox, toy);
			rgb tocolor(tor, tog, tob);
			if (random)
			{
				this->data[i] = new rectangle(A, tosize, tocolor);
			}
			else
			{
				this->data[i] = new circle(A, tosize, tocolor);
			}
		}
	}
	void proceed()
	{
		for (int i = 0; i < 3; ++i)
		{
			this->refill();
			for (int j = 0; j < this->shapes_amount; ++j)
			{
				this->data[j]->display();
			}
			Sleep(200);
			system("cls");
		}
	}
};

class operation2
{
public:
	int shapes_amount = 20;
	int task_size = 500;
	shape **data;
	operation2()
	{
		this->data = new shape*[this->shapes_amount];
		for (int i = 0; i < this->shapes_amount; ++i)
		{
			this->data[i] = new shape();
		}
		dot A(0, 0); rgb tocolor(127, 127, 127); int tofrequent = 25;
		this->data[0] = new grid_image(A, task_size, tocolor, tofrequent);
	}
	~operation2()
	{
		for (int i = 0; i < this->shapes_amount; ++i)
		{
			delete data[i];
		}
		delete[] data;
	}
	void refill()
	{
		for (int i = 1; i < this->shapes_amount; ++i)
		{
			shape *todelete = this->data[i];
			this->data[i] = nullptr;
			delete todelete;
			srand(time(NULL) + rand()); bool random = rand() % 2;
			srand(time(NULL) + rand()); int tosize = rand() % 101;
			srand(time(NULL) + rand()); int tox = rand() % (task_size - tosize + 1);
			srand(time(NULL) + rand()); int toy = rand() % (task_size - tosize + 1);
			srand(time(NULL) + rand()); int tor = rand() % 256;
			srand(time(NULL) + rand()); int tog = rand() % 256;
			srand(time(NULL) + rand()); int tob = rand() % 256;
			dot A(tox, toy);
			rgb tocolor(tor, tog, tob);
			if (random)
			{
				this->data[i] = new rectangle(A, tosize, tocolor);
			}
			else
			{
				this->data[i] = new circle(A, tosize, tocolor);
			}
		}
	}
	void rotate_to_angle_counter_clockwise()
	{
		float angle = 10 * 3.14159265358979323846 / 180;
		float s = sin(angle);
		float c = cos(angle);
		int half = this->task_size / 2;
		for (int i = 1; i < this->shapes_amount; ++i)
		{
			int x_temp = this->data[i]->x_position - half;
			int y_temp = -this->data[i]->y_position + half;
			float x_new = x_temp * c - y_temp * s;
			float y_new = x_temp * s + y_temp * c;
			this->data[i]->x_position = x_new + half;
			this->data[i]->y_position = half - y_new;
		}
	}
	void proceed()
	{
		this->refill();
		for (int i = 0; i < 10; ++i)
		{
			this->rotate_to_angle_counter_clockwise();
			for (int j = 0; j < this->shapes_amount; ++j)
			{
				this->data[j]->display();
			}
			Sleep(200);
			system("cls");
		}
	}
};

void menu0();
void menu1();
void menu2();

void menu0()
{
	while (true)
	{
		system("cls");
		cout << "_Вход\n| 1 - Задание 1 | 2 - Задание 2 | 3 - Выход | >> ";

		int start_answer;
		cin >> start_answer;
		while (start_answer < 1 || start_answer > 3)
		{
			cout << ">> ";
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
			}
			cin >> start_answer;
		}

		switch (start_answer)
		{
		case 1: { menu1(); }; break;
		case 2: { menu2(); }; break;
		default: { return; }; break;
		}
	}
}

void menu1()
{
	system("cls");
	operation1 A;
	A.proceed();
}

void menu2()
{
	system("cls");
	operation2 A;
	A.proceed();
}

int main()
{
	setlocale(LC_ALL, "");
	menu0();
	cout << "_Выход";
	system("pause>>void");
	return 0;
}