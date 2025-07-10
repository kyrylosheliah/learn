#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <algorithm>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	QObject::connect(pushButton_1, SIGNAL(clicked()), this, SLOT(calculate_function_interval()));
	QObject::connect(pushButton_3, SIGNAL(clicked()), this, SLOT(find_last_peak()));
}

void Widget::calculate_function_interval(){
	double i = doubleSpinBox_1->value();
	double b = doubleSpinBox_2->value();
	double h = doubleSpinBox_3->value();
	this->last_calculation_X.clear();
	this->last_calculation_Y.clear();
	this->count += 1;
	double temp = .0;
	while (i <= b){
		temp = (i-8)/(1-qCos(2*i));
		this->last_calculation_X.push_back(i);
		this->last_calculation_Y.push_back(temp);
		textEdit_1->append("["+QString::number(this->count)+"]: |x="+QString::number(i)+"| |y="+QString::number(temp)+"|\n");
		i += h;
	}
}

void Widget::find_last_peak(){
	if(this->last_calculation_Y.size()){
		if(radioButton_1->isChecked()){
			auto tomax = std::max_element(this->last_calculation_Y.begin(), this->last_calculation_Y.end());
			textEdit_2->append("["+QString::number(this->count)+"]: Y MAX: |y="+QString::number(*tomax)+"| |x="+QString::number(this->last_calculation_X[std::distance(this->last_calculation_Y.begin(), tomax)])+"|\n");
		}else if(radioButton_2->isChecked()){
			auto tomin = std::min_element(this->last_calculation_Y.begin(), this->last_calculation_Y.end());
			textEdit_2->append("["+QString::number(this->count)+"]: Y MIN: |y="+QString::number(*tomin)+"| |x="+QString::number(this->last_calculation_X[std::distance(this->last_calculation_Y.begin(), tomin)])+"|\n");
		}else{
			textEdit_2->append("===\n[!] radioButton is not checked\n===\n");
		}
	}else{
		textEdit_2->append("===\n[!] last_calculation is empty\n===\n");
	}
}

Widget::~Widget()
{
	delete ui;
}

