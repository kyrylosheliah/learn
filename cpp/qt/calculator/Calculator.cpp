#include <QtGui/QtGui>
#include <QtWidgets/QGridLayout>
#include <QtMath>
#include "Calculator.h"

Calculator::Calculator(QWidget* pwgt) : QWidget(pwgt)
{
	pointer_lcd = new QLCDNumber(12);
	pointer_lcd->setSegmentStyle(QLCDNumber::Flat);
	pointer_lcd->setMinimumSize(150, 50);

	QString aButtons[4][5] =	{{"pow","7", "8", "9", "/"},
								{"sqrt","4", "5", "6", "*"},
								{"sin",	"1", "2", "3", "-"},
								{"cos",	"0", ".", "=", "+"}
								};

    QGridLayout* ptopLayout = new QGridLayout;
	ptopLayout->addWidget(pointer_lcd, 0, 0, 1, 4);
	ptopLayout->addWidget(createButton("CE"), 0, 4, 1, 1);

    for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
		   ptopLayout->addWidget(createButton(aButtons[i][j]), i + 1, j);
        }
    }
    setLayout(ptopLayout);
}

QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}

void Calculator::calculate()
{
	if ((term_data.count() == 1)&&(string_data != "")) {
		term_data.push_back(string_data);
		string_data.clear();
	}
	if (string_operation_context.count() > 0) {
		double dResult = 0;
		switch (term_data.count()){
		case 1:{
			double dOperand1 = term_data[0].toDouble();
			switch (string_operation_context[0].unicode()) {
			case '+': case '-': case '/': case '*': case '^':
				dResult = dOperand1; break;
			default:
				if (string_operation_context == "pow") {
					dResult = dOperand1;
				} else if (string_operation_context == "sqrt"){
					dResult = qSqrt(dOperand1);
				} else if (string_operation_context == "sin"){
					dResult = qSin(dOperand1);
				} else if (string_operation_context == "cos"){
					dResult = qCos(dOperand1);
				}break;
			}
		}break;
		case 2:{
			double dOperand1 = term_data[0].toDouble();
			double dOperand2 = term_data[1].toDouble();
			switch (string_operation_context[0].unicode()) {
			case '+': dResult = dOperand1 + dOperand2; break;
			case '-': dResult = dOperand1 - dOperand2; break;
			case '/': dResult = dOperand1 / dOperand2; break;
			case '*': dResult = dOperand1 * dOperand2; break;
			default:
				if (string_operation_context == "pow") {
					dResult = qPow(dOperand1, dOperand2);
				} else if (string_operation_context == "sqrt"){
					dResult = dOperand1 * qSqrt(dOperand2);
				} else if (string_operation_context == "sin"){
					dResult = dOperand1 * qSin(dOperand2);
				} else if (string_operation_context == "cos"){
					dResult = dOperand1 * qCos(dOperand2);
				}break;
			}
		}break;
		default:
			term_data.clear();
			string_data = "";
			string_operation_context = "";
			pointer_lcd->display("ABOBA");
			return;
		}
		pointer_lcd->display(dResult);
		string_data = QString().setNum(dResult);
		term_data.clear();
		string_operation_context = "";
	} else {
		pointer_lcd->display(string_data);
		term_data.clear();
	}
}

void Calculator::slotButtonClicked()
{
	QString str = ((QPushButton*)sender())->text();

	if (str == "CE") {
		term_data.clear();
		string_data = "";
		string_operation_context = "";
		pointer_lcd->display("0");
	} else if (str.contains(QRegExp("[0-9]"))) {
		string_data += str;
		pointer_lcd->display(string_data.toDouble());
	}
	else if (str == ".") {
		if (!string_data.contains(".")) {
			string_data += str;
			pointer_lcd->display(string_data);
		}
	} else if (str == "=") {
		calculate();
	} else {
		if (term_data.count() == 0){
			string_operation_context = str;
			term_data.push_back(string_data);
			string_data.clear();
			pointer_lcd->display("");
		}else{
			term_data.clear();
			string_data = "";
			string_operation_context = "";
			pointer_lcd->display("ABOBA");
			return;
		}
	}
}
