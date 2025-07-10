#include "dialog.h"
#include "ui_dialog.h"
#include <qtextcodec.h>
#include <QtWidgets\qmessagebox.h>
#define RUS(str) codec->toUnicode(str)

Dialog::Dialog(QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	connect(pushButton, SIGNAL(clicked()), this, SLOT(onExitClicked()));
}

void Dialog::onExitClicked()
{
	QTextCodec * codec = QTextCodec::codecForName("utf-8");
	auto exitq = QMessageBox::question(this, QString(), RUS("Завершить приложение?"), QMessageBox::Yes | QMessageBox::No);
	if (exitq == QMessageBox::Yes){
		exit(0);
	}
};
