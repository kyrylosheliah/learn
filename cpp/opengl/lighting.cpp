#include "Windows.h"
#include "glut.h"
#include "math.h"
#include <vector>
#define M_PI 3.14159265358979323846
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

std::vector<void(*)(void)> funcVector;
int funcVectorCur = 0;
GLint Width = 512, Height = 512;
int mButton = 0;

double mouseX = 0.0;
double mouseY = 0.0;
double LookAngleX = 0.0;
double LookAngleY = 0.0;
double LookAngleZ = 0.0;
double LookDistZ = -15.0;
double mSensitivity = 0.2;

static double FigAnglePurpose = 0;

double tx = 0;
double ty = 0;
double tz = 0;
double AngleX = 0.0;
double AngleY = 0.0;
double AngleZ = 0.0;
double ZoomX = 1.0;
double ZoomY = 1.0;
double ZoomZ = 1.0;

double RotPointX = 0.0;
double RotPointY = 0.0;
double RotPointZ = 0.0;

void MoveRotate()
{
	if ((RotPointX != 0.0) || (RotPointY != 0.0) || (RotPointZ != 0.0))
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
	FigAnglePurpose += 0.03;

	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat light_diffuse[] = { 0.0f, 0.0f, 0.0f, 0.0f }; 
	GLfloat light_specular[] = { 0.5f, 0.2f, 0.2f, 1.0f };
	GLfloat light_position[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	// glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
	// glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0 * (Height / 1080.0 + Width / 1920.0) / 2.0, (double)Width / Height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, LookDistZ);  // камера з початку координат зсуваЇтьс€ на distZ, 
	glRotated(LookAngleX, 0.0, 1.0, 0.0);  // пот≥м повертаЇтьс€ по ос≥ Oy
	glRotated(LookAngleY, 1.0, 0.0, 0.0);  // пот≥м повертаЇтьс€ по ос≥ Ox

	glScaled(ZoomX, ZoomY, ZoomZ);

	MoveRotate();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	//gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void After()
{
	glColor3d(1.0, 1.0, 1.0);

	//малюЇмо л≥н≥ю 1
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(3 * sin(FigAnglePurpose + M_PI / 2), 3 * cos(FigAnglePurpose + M_PI / 2), 0);
	glVertex3f(3 * sin(FigAnglePurpose - M_PI / 2), 3 * cos(FigAnglePurpose - M_PI / 2), 0);
	glEnd();
	glPopMatrix();

	// малюЇмо л≥н≥ю 2
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(3 * sin(FigAnglePurpose), 3 * cos(FigAnglePurpose), 0);
	glVertex3f(3 * sin(FigAnglePurpose + M_PI), 3 * cos(FigAnglePurpose + M_PI), 0);
	glEnd();
	glPopMatrix();

	// малюЇмо л≥н≥ю 3
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);
	glEnd();
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers();
}

void idle(void)
{
}

void Display1(void)
{
	Before();

	float material_spec[] = { 1.0, 1.0, 1.0 };
	float material_shininess = 64.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
	glColor3d(0.2, 0.8, 0.3);
	glPushMatrix();
	glTranslatef(2 * sin(FigAnglePurpose - M_PI / 2), 2 * cos(FigAnglePurpose - M_PI / 2), 0);
	glutSolidOctahedron();
	glPopMatrix();

	After();
}

void Display2(void)
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


void Display3(void)
{
	Before();

	glPushMatrix();
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
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150.0, 0.0, -70.0);
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
	glPopMatrix();

	After();
}

void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
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
}

void Motion(int x, int y)
{
	switch (mButton) {
	case 0:
		LookAngleX += (x - mouseX) * mSensitivity;
		LookAngleY += (y - mouseY) * mSensitivity;
		mouseX = x;
		mouseY = y;
		break;
	case 2:
		LookDistZ += y - mouseY;
		mouseY = y;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (state == 1) {
		mButton = -1;
		return;
	}
	switch (mButton = button) {
	case 0: mouseX = x; mouseY = y; break;
	case 2: LookAngleX = 0; LookAngleY = 0; LookDistZ = -15; break;
	}
}

void Timed(int value)
{
	funcVector[funcVectorCur]();                     // перемалюЇмо екран
	glutTimerFunc(20, Timed, 0); // через 33мс викличетьс€ ц€ функц≥€
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
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);

	glutTimerFunc(20, Timed, 0);

	glutMainLoop();
	return 0;
}
