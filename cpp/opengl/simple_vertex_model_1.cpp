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

double LookAtPointX = 0.0;
double LookAtPointY = 0.0;
double LookAtPointZ = 0.0;

double RotPointX = 0.0;
double RotPointY = 0.0;
double RotPointZ = 0.0;

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

void MoveRotate()
{
	if ( (RotPointX != 0.0) || (RotPointY != 0.0 )|| (RotPointZ != 0.0))
	{
		glTranslated(RotPointX, RotPointY, RotPointZ);
		if (RotPointX != 0.0) { glRotated(-AngleX, 1.0, 0.0, 0.0); }
		if (RotPointY != 0.0) { glRotated(-AngleY, 0.0, 1.0, 0.0); }
		if (RotPointZ != 0.0) { glRotated(-AngleZ, 0.0, 0.0, 1.0); }
		glTranslated(RotPointX, RotPointY, RotPointZ);
	}
	else
	{
		glRotated(AngleX, 1.0, 0.0, 0.0);
		glRotated(AngleY, 0.0, 1.0, 0.0);
		glRotated(AngleZ, 0.0, 0.0, 1.0);
		glTranslated(tx, ty, tz);
	}
}

void Before()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0 * (Height / 1080.0 + Width / 1920.0) / 2.0, (double)Width / Height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(100.0, 100.0, 100.0, LookAtPointX, LookAtPointY, LookAtPointZ, 0.0, 1.0, 0.0);
	MoveRotate();

	glScaled(ZoomX, ZoomY, ZoomZ);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void After()
{
	glFlush();
	glutSwapBuffers();
}

void Init(void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-50, 50, -50, 50, -50, 50);
}

void idle(void)
{
}

void Display1(void)
{
	Before();

	glColor3d(1.0, 1.0, 1.0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex3d(-50.0, 0.0, -25.0);
	glVertex3d(-50.0, 0.0, 25.0);
	glVertex3d(-25.0, 25.0, 12.5);
	glVertex3d(-25.0, 25.0, -12.5);
	glVertex3d(-50.0, 0.0, -25.0);
	glVertex3d(50.0, 0.0, 0.0);
	glVertex3d(-50.0, 0.0, 25.0);
	glVertex3d(-25.0, 25.0, 12.5);
	glVertex3d(-25.0, 25.0, -12.5);
	glVertex3d(25.0, 25.0, 0.0);
	glVertex3d(50.0, 0.0, 0.0);
	glEnd();

	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3d(50.0, 0.0, 0.0);
	glVertex3d(-50.0, 0.0, -25.0);
	glVertex3d(-50.0, 0.0, 25.0);
	glVertex3d(25.0, 25.0, 0.0);
	glVertex3d(-25.0, 25.0, -12.5);
	glVertex3d(-25.0, 25.0, 12.5);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(-50.0, 0.0, -25.0);
	glVertex3d(-50.0, 0.0, 25.0);
	glVertex3d(-25.0, 25.0, 12.5);
	glVertex3d(-25.0, 25.0, -12.5);
	glVertex3d(-50.0, 0.0, 25.0);
	glVertex3d(-25.0, 25.0, 12.5);
	glVertex3d(25.0, 25.0, 0.0);
	glVertex3d(50.0, 0.0, 0.0);
	glVertex3d(-50.0, 0.0, -25.0);
	glVertex3d(-25.0, 25.0, -12.5);
	glVertex3d(25.0, 25.0, 0.0);
	glVertex3d(50.0, 0.0, 0.0);
	glEnd();

	After();
}

void Display2(void)
{
	Before();

	glColor4ub(255, 0, 0, 255);
	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 0.0);
	glColor4ub(0, 255, 0, 255);
	glVertex3d(50.0, 0.0, 0.0);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3d(50.0, 50.0, 0.0);
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


void Display3(void)
{
	Before();

	//glLoadIdentity();
	glTranslatef(-150.0, 0.0, -60.0);

	glBegin(GL_TRIANGLES);
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 50.0, 0.0);     
	glColor3d(0.0, 1.0, 0.0);       
	glVertex3d(-50.0, -50.0, 50.0); 
	glColor3d(0.0, 0.0, 1.0);       
	glVertex3d(50.0, -50.0, 50.0);  
	glColor3d(1.0, 0.0, 0.0);       
	glVertex3d(0.0, 50.0, 0.0);     
	glColor3d(0.0, 0.0, 1.0);       
	glVertex3d(50.0, -50.0, 50.0);  
	glColor3d(0.0, 1.0, 0.0);       
	glVertex3d(50.0, -50.0, -50.0); 
	glColor3d(1.0, 0.0, 0.0);       
	glVertex3d(0.0, 50.0, 0.0);     
	glColor3d(0.0, 1.0, 0.0);       
	glVertex3d(50.0, -50.0, -50.0); 
	glColor3d(0.0, 0.0, 1.0);       
	glVertex3d(-50.0, -50.0, -50.0);
	glColor3d(1.0, 0.0, 0.0);       
	glVertex3d(0.0, 50.0, 0.0);     
	glColor3d(0.0, 0.0, 1.0);       
	glVertex3d(-50.0, -50.0, -50.0);
	glColor3d(0.0, 1.0, 0.0);       
	glVertex3d(-50.0, -50.0, 50.0); 
	glEnd();

	//glLoadIdentity();
	glTranslatef(150.0, 0.0, -70.0);
	MoveRotate();

	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(50.0, 50.0, -50.0); 
	glVertex3d(-50.0, 50.0, -50.0);
	glVertex3d(-50.0, 50.0, 50.0); 
	glVertex3d(50.0, 50.0, 50.0);
	glColor3d(1.0, 0.5f, 0.0);
	glVertex3d(50.0, -50.0, 50.0); 
	glVertex3d(-50.0, -50.0, 50.0);
	glVertex3d(-50.0, -50.0, -50.0);
	glVertex3d(50.0, -50.0, -50.0);
	
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(50.0, 50.0, 50.0); 
	glVertex3d(-50.0, 50.0, 50.0);
	glVertex3d(-50.0, -50.0, 50.0);
	glVertex3d(50.0, -50.0, 50.0);
	
	glColor3d(1.0, 1.0, 0.0);
	glVertex3d(50.0, -50.0, -50.0);
	glVertex3d(-50.0, -50.0, -50.0);
	glVertex3d(-50.0, 50.0, -50.0); 
	glVertex3d(50.0, 50.0, -50.0);
	
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(-50.0, 50.0, 50.0);
	glVertex3d(-50.0, 50.0, -50.0); 
	glVertex3d(-50.0, -50.0, -50.0);
	glVertex3d(-50.0, -50.0, 50.0); 
	
	glColor3d(1.0, 0.0, 1.0);
	glVertex3d(50.0, 50.0, -50.0);
	glVertex3d(50.0, 50.0, 50.0);
	glVertex3d(50.0, -50.0, 50.0);
	glVertex3d(50.0, -50.0, -50.0); 
	glEnd();

	After();
}

void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLdouble)w / h, 1.0, 100.0);

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
	case '4':
		LookAtPointX -= 10;
		break;
	case '6':
		LookAtPointX += 10;
		break;
	case '8':
		LookAtPointY += 10;
		break;
	case '2':
		LookAtPointY -= 10;
		
		break;
	case 'o':
		ZoomX += 0.1;
		if (ZoomX >= 3) { ZoomX = 1; }
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
	case 'z':
		if (RotPointX) { RotPointX = 0.0; }
		else { RotPointX = 100.0; }
		break;
	case 'x':
		if (RotPointY) { RotPointY = 0.0; }
		else { RotPointY = 100.0; }
		break;
	case 'c':
		if (RotPointZ) { RotPointZ = 0.0; }
		else { RotPointZ = 100.0; }
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
	case GLUT_KEY_HOME:
		tx = ty = tz = AngleX = AngleY = AngleZ = 0.0;
		ZoomX = ZoomY = ZoomZ = 1.0;
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
	glutInit(&argc, argv);
	glutInitWindowPosition(250, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
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