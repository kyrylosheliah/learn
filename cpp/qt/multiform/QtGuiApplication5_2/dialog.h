#pragma once

#include <QDialog>
#include "ui_dialog.h"

class Dialog : public QDialog, public Ui::Dialog
{
	Q_OBJECT

public:
	Dialog(QWidget *parent = nullptr);
private slots:
	void onExitClicked();
};
