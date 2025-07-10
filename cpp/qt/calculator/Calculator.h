#ifndef _Calculator_h_
#define _Calculator_h_

#include <QtWidgets/QWidget>
#include <QVector>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QString>

class Calculator : public QWidget {
	Q_OBJECT
private:
	QLCDNumber *pointer_lcd;
	QVector<QString> term_data;
	QString string_operation_context;
	QString string_data;
public:
	Calculator(QWidget *pwgt = nullptr);
	QPushButton *createButton(const QString &str);
	void calculate();
public slots:
	void slotButtonClicked();
};

#endif