#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "Calculator.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Calculator calculator;

	calculator.setWindowTitle("Calculator");
    calculator.resize(230, 200);
	calculator.show();

	app.exec();
	return 0;
}
