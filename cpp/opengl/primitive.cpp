#include "Windows.h"
#include "glut.h"
#include "math.h"
#define M_PI 3.14159265358979323846
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#define rotate_point(c,angle,p) Point2d((cos(angle) * (p.x - c.x) - sin(angle) * (p.y - c.y) + c.x), (sin(angle)* (p.x - c.x) + cos(angle) * (p.y - c.y) + c.y))

GLint Width = 512, Height = 512;

struct Point2d
{
	int x;
	int y;
	Point2d() {}
	Point2d(int X, int Y)
	{
		this->x = X;
		this->y = Y;
	}
	Point2d(Point2d& other)
	{
		x = other.x;
		y = other.y;
	}
};

void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void idle(void)
{
}

void Display1(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3ub(0, 255, 0);
	glVertex3f(Width, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(Width, Height, 0.0);
	glEnd();
	
	GLint lineWidth = 11;
	glLineWidth(lineWidth);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 58360);
	glColor3d(1, 1, 1);
	Point2d next, center(Width / 2, Height / 2);
	for (int i = 0; i < 10; ++i)
	{
		next = Point2d(center.x, center.y - (center.y / (i + 1)));
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 3; ++j)
		{
			//g.DrawLine(p, prev, next);
			glVertex3i(next.x, next.y, 0);
			next = rotate_point(center, 60 * M_PI / 90, next);
		}
		glEnd();
		if (lineWidth)
		{
			glLineWidth(----lineWidth);
		}
		
	}
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);

	glFinish();
}

void Display2(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLint lineWidth = 20;
	Point2d topLeft(lineWidth / 2, Height - lineWidth / 2),
			bottomLeft(lineWidth / 2, lineWidth / 2),
			centerLeft(Width - lineWidth / 2, Height / 2),
			centerRight(lineWidth / 2, Height / 2);
	glLineWidth(lineWidth);

	glColor3d((double)28 / 255, (double)146 / 255, (double)210 / 255);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 19568);
	glBegin(GL_LINES);
	 glVertex3i(centerLeft.x, centerLeft.y, 0);
	 glColor3d((double)242 / 255, (double)252 / 255, (double)254 / 255);
	 glVertex3i(centerRight.x, centerRight.y, 0);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);

	glColor3d((double)28 / 255, (double)146 / 255, (double)210 / 255);
	glBegin(GL_LINES);
	glVertex3i(topLeft.x, topLeft.y, 0);
	glVertex3i(bottomLeft.x, bottomLeft.y, 0);
	glEnd();
	
	glFinish();
}

void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\033': // ESCAPE '\033'
		exit(0);
		break;
	default:
		break;
	}
}

void SpKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_END:
		glutDisplayFunc(Display2);
		Display2();
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(250, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB); // A | GLUT_DOUBLE
	glutCreateWindow("OpenGL");
	glutIdleFunc(idle);
	glutDisplayFunc(Display1);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpKeyboard);
	Init();
	glutMainLoop();
	return 0;
}