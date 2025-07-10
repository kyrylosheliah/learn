#pragma once

#include <QtWidgets/QWidget>
#include "ui_MyForm.h"


class MyForm : public QWidget, Ui::MyForm {
	Q_OBJECT
public:
	MyForm(QWidget *pwgt = Q_NULLPTR);
public slots:
	void slotReset();
};
