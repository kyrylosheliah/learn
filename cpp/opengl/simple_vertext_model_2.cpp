#include "Windows.h"
#include "glut.h"
#include "math.h"
#include <stdio.h>
#include <malloc.h>
#include <vector>
#define M_PI 3.14159265358979323846
#define GL_BGR 0x80E0
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

GLuint texture_id;
struct texture_struct
{
	int W;
	int H;
	unsigned char* Image;
}texture_instance;

int LoadTexture(char* FileName)
{
	FILE* F;
	if ((fopen_s(&F, FileName, "r")) != NULL)
		return 0;
	fseek(F, 18, SEEK_SET);
	fread(&(texture_instance.W), 2, 1, F);
	fseek(F, 2, SEEK_CUR);
	fread(&(texture_instance.H), 2, 1, F);

	printf("%d x %d\n", texture_instance.W, texture_instance.H);

	// Выделяем память под изображение. Если память не выделилась, закрываем файл и выходим с ошибкой
	if ((texture_instance.Image = (unsigned char*)malloc(sizeof(unsigned char) * 3 * texture_instance.W * texture_instance.H)) == NULL)
	{
		fclose(F);
		return 0;
	}
	// Считываем изображение в память по 3 бита, то бишь RGB для каждого пикселя 
	fseek(F, 30, SEEK_CUR);
	fread(texture_instance.Image, 3, texture_instance.W * texture_instance.H, F);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture_instance.W, texture_instance.H, GL_BGR, GL_UNSIGNED_BYTE, texture_instance.Image);


	free(texture_instance.Image);
	fclose(F);

	return 1;
}

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

	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины

	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0 * (Height / 1080.0 + Width / 1920.0) / 2.0, (double)Width / Height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, LookDistZ);  // камера з початку координат зсуваЇтьс¤ на distZ, 
	glRotated(LookAngleX, 0.0, 1.0, 0.0);  // пот≥м повертаЇтьс¤ по ос≥ Oy
	glRotated(LookAngleY, 1.0, 0.0, 0.0);  // пот≥м повертаЇтьс¤ по ос≥ Ox

	glScaled(ZoomX, ZoomY, ZoomZ);

	MoveRotate();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	//glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslatef(40 * cos(FigAnglePurpose - M_PI / 2), 40 * sin(FigAnglePurpose - M_PI / 2), 40 * cos(FigAnglePurpose - M_PI / 2));
	GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat light_specular[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
	// glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	// glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);
	// glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
	// glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-5, 0, 0);
	glVertex3f(5, 0, 0);
	glVertex3f(0, -5, 0);
	glVertex3f(0, 5, 0);
	glVertex3f(0, 0, -5);
	glVertex3f(0, 0, 5);
	glEnd();
	glPopMatrix();

	//gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// Полир, золото
	// {0.25, 0.22, 0.06, 1.00}
	// {0.35, 0.31, 0.09, 1.00}
	// {0.80, 0.72, 0.21, 1.00}
	// 83.2
	float material_ambient[] = { 0.25, 0.22, 0.06, 1.00 };
	float material_diffuse[] = { 0.35, 0.31, 0.09, 1.00 };
	float material_specular[] = { 0.80, 0.72, 0.21, 1.00 };
	float material_shininess = 83.2;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
}

void After()
{
	// glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT1);
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

	glColor3d(1.0, 1.0, 1.0);

	glColor3d(0.2, 0.8, 0.3);
	glPushMatrix();
	glTranslatef(2 * sin(FigAnglePurpose - M_PI / 2), 2 * cos(FigAnglePurpose - M_PI / 2), 0);
	glutSolidOctahedron();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	//glutSolidTeapot(2);

	// glBegin(GL_POLYGON);
	// glVertex3d(0, 0, 0);
	// glTexCoord2d(0, 0); glVertex3d(25.0, 0, 0);
	// glTexCoord2d(0, 1); glVertex3d(25.0, 0, -25.0);
	// glVertex3d(0, 0, -25.0);
	// glVertex3d(0, 0, -50.0);
	// glVertex3d(-25.0, 0, -50.0);
	// glTexCoord2d(1, 1); glVertex3d(-25.0, 0, 25.0);
	// glTexCoord2d(1, 0); glVertex3d(0, 0, 25.0);
	// glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(0, 0, 0);
	glTexCoord2d(1, 2); glVertex3d(25.0, 0, 0);
	glTexCoord2d(2, 2); glVertex3d(25.0, 0, -25.0);
	glTexCoord2d(2, 1); glVertex3d(0, 0, -25.0);
	glTexCoord2d(3, 1); glVertex3d(0, 0, -50.0);
	glTexCoord2d(3, 0); glVertex3d(-25.0, 0, -50.0);
	glTexCoord2d(0, 0); glVertex3d(-25.0, 0, 25.0);
	glTexCoord2d(0, 1); glVertex3d(0, 0, 25.0);
	glEnd();

	glTranslated(0, 20, 0);
	glRotated(FigAnglePurpose, 1, 0, 0);

	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_2D);

	After();
}

void Display2(void)
{
	Before();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	//glColor3d(1.0, 1.0, 1.0);
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

	//glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0, 0); glVertex3d(50.0, 0.0, 0.0);
	glTexCoord2d(0, 1); glTexCoord2d(1, 1); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(1, 0); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(0, 0); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(0, 1); glTexCoord2d(1, 1); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(1, 0); glVertex3d(-25.0, 25.0, 12.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(0, 1); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(1, 1); glVertex3d(-25.0, 25.0, 12.5);
	glTexCoord2d(1, 0); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(0, 1); glVertex3d(-25.0, 25.0, 12.5);
	glTexCoord2d(1, 1); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(1, 0); glVertex3d(50.0, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(0, 1); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(1, 1); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(1, 0); glVertex3d(50.0, 0.0, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);

	glDisable(GL_TEXTURE_2D);

	After();
}

void Display3(void)
{
	Before();

	//glColor3d(1.0, 1.0, 1.0);
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

	//glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0, 0); glVertex3d(50.0, 0.0, 0.0);
	glTexCoord2d(0, 1); glTexCoord2d(1, 1); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(1, 0); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(0, 0); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(0, 1); glTexCoord2d(1, 1); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(1, 0); glVertex3d(-25.0, 25.0, 12.5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(0, 1); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(1, 1); glVertex3d(-25.0, 25.0, 12.5);
	glTexCoord2d(1, 0); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, 25.0);
	glTexCoord2d(0, 1); glVertex3d(-25.0, 25.0, 12.5);
	glTexCoord2d(1, 1); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(1, 0); glVertex3d(50.0, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3d(-50.0, 0.0, -25.0);
	glTexCoord2d(0, 1); glVertex3d(-25.0, 25.0, -12.5);
	glTexCoord2d(1, 1); glVertex3d(25.0, 25.0, 0.0);
	glTexCoord2d(1, 0); glVertex3d(50.0, 0.0, 0.0);
	glEnd();

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
	glutTimerFunc(20, Timed, 0); // через 33мс викличетьс¤ ц¤ функц≥¤
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

	if (LoadTexture((char*)"images.bmp") != 1) { printf("Не удалось загрузить изображение\n"); }

	glutTimerFunc(20, Timed, 0);

	glutMainLoop();
	return 0;
}