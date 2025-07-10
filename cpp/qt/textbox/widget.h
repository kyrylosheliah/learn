#pragma once

#include <QWidget>
#include <QString>
#include "ui_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget, public Ui::Widget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();
public slots:
	void calculate_function_interval();
	void find_last_peak();
private:
	int count = 0;
	QList<double> last_calculation_X{};
	QList<double> last_calculation_Y{};
	Ui::Widget *ui;
};
