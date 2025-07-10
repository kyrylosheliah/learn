#include "MyForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyForm w;
	w.show();
	return a.exec();
}
