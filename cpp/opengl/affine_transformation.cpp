#include "Windows.h"
#include "glut.h"
#include "math.h"
#include <vector>
#define M_PI 3.14159265358979323846
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#define rotate_point(c,angle,p) Point2d((cos(angle) * (p.x - c.x) - sin(angle) * (p.y - c.y) + c.x), (sin(angle)* (p.x - c.x) + cos(angle) * (p.y - c.y) + c.y))

std::vector<void(*)(void)> funcVector;
int funcVectorCur = 0;
GLint Width = 512, Height = 512;

double tx = 0;
double ty = 0;
double tz = 0;
double AngleX = 0.0;
double AngleY = 0.0;
double AngleZ = 0.0;
double ZoomX = 1.0;
double ZoomY = 1.0;
double ZoomZ = 1.0;

struct Point2d
{
	double x;
	double y;
	Point2d() {}
	Point2d(double X, double Y)
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

void Before()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double) Width / Height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotated(AngleX, 1.0, 0.0, 0.0);
	glRotated(AngleY, 0.0, 1.0, 0.0);
	glRotated(AngleZ, 0.0, 0.0, 1.0);
	glTranslated(tx, ty, tz);

	glScaled(ZoomX, ZoomY, ZoomZ);
}

void After()
{
	glFlush();
	glutSwapBuffers();
}

void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -250, 250);
}

void idle(void)
{
}

void Display1(void)
{
	Before();


	glColor4ub(255, 0, 0, 255);
	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor4ub(0, 255, 0, 255);
	glVertex3f(50.0, 0.0, 0.0);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3f(50.0, 50.0, 0.0);
	glEnd();

	GLint lineWidth = 11;
	glLineWidth(lineWidth);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 58360);
	glColor3d(1, 1, 1);
	Point2d next, center(0, 0);
	for (int i = 0; i < 10; ++i)
	{
		next = Point2d(center.x, center.y - (100.0 / (i + 1)));
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

	After();
}

void Display2(void)
{
	Before();

	Point2d topLeft(-50.0, 50.0),
			bottomLeft(-50.0, -50.0),
			centerLeft(50.0, 0),
			centerRight(-50.0, 0);
	glLineWidth(4);

	glColor3d((GLdouble)28 / 255, (GLdouble)146 / 255, (GLdouble)210 / 255);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 19568);
	glBegin(GL_LINES);
	 glVertex3i(centerLeft.x, centerLeft.y, 0);
	 glColor3d((GLdouble)242 / 255, (GLdouble)252 / 255, (GLdouble)254 / 255);
	 glVertex3i(centerRight.x, centerRight.y, 0);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);

	glColor3d((GLdouble)28 / 255, (GLdouble)146 / 255, (GLdouble)210 / 255);
	glBegin(GL_LINES);
	glVertex3i(topLeft.x, topLeft.y, 0);
	glVertex3i(bottomLeft.x, bottomLeft.y, 0);
	glEnd();

	After();
}


void Display3(void)
{
	Before();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-75.0f, 0.0f, -50.0f);
	glVertex3f(-75.0f, 0.0f, 50.0f);
	glVertex3f(75.0f, 0.0f, 50.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-75.0f, 0.0f, -50.0f);
	glVertex3f(75.0f, 0.0f, -50.0f);
	glVertex3f(75.0f, 0.0f, 50.0f);
	glEnd();

	After();
}

void Display4(void)
{
	Before();

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(25.0, 0, 0);
	glVertex3d(25.0, 0, -25.0);
	glVertex3d(0, 0, -25.0);
	glVertex3d(0, 0, -50.0);
	glVertex3d(-25.0, 0, -50.0);
	glVertex3d(-25.0, 0, 25.0);
	glVertex3d(0, 0, 25.0);
	glEnd();

	After();
}

void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0, w, 0, h, -1.0, 1.0);
	gluPerspective(60.0, (GLdouble)w / h, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		ty += 10;
		break;
	case 's':
		ty -= 10;
		break;
	case 'a':
		tx -= 10;
		break;
	case 'd':
		tx += 10;
		break;
	case 'r':
		tz += 10;
		break;
	case 'f':
		tz -= 10;
		break;
	case 'o':
		ZoomX += 0.1;
		if (ZoomX >= 3) { ZoomX = 1;}
		break;
	case 'l':
		ZoomX -= 0.1;
		if (ZoomX <= 0.1) { ZoomX = 1; }
		break;
	case 'p':
		ZoomY += 0.1;
		if (ZoomY >= 3) { ZoomY = 1; }
		break;
	case ';':
		ZoomY -= 0.1;
		if (ZoomY <= 0.1) { ZoomY = 1; }
		break;
	case '[':
		ZoomZ += 0.1;
		if (ZoomZ >= 3) { ZoomZ = 1; }
		break;
	case '\'':
		ZoomZ -= 0.1;
		if (ZoomZ <= 0.1) { ZoomZ = 1; }
		break;
	case '\033': // ESCAPE '\033'
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void SpKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		AngleY += 18.0;
		break;
	case GLUT_KEY_RIGHT:
		AngleY -= 18.0;
		break;
	case GLUT_KEY_UP:
		AngleX += 18.0;
		break;
	case GLUT_KEY_DOWN:
		AngleX -= 18.0;
		break;
	case GLUT_KEY_END:
		glutDisplayFunc(funcVector[funcVectorCur]);
		++funcVectorCur;
		if (funcVectorCur >= funcVector.size())
		{
			funcVectorCur = 0;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	funcVector.push_back(&Display1);
	funcVector.push_back(&Display2);
	funcVector.push_back(&Display3);
	funcVector.push_back(&Display4);
	glutInit(&argc, argv);
	glutInitWindowPosition(250, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // 
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
