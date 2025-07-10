#ifndef _InputDialog_h_
#define _InputDialog_h_

#include <QtGui/QtGui>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

class QLineEdit;

class InputDialog : public QDialog {
	Q_OBJECT
private:
	QLineEdit* m_ptxtFirstName;
	QLineEdit* m_ptxtLastName;

public:
	InputDialog(QWidget* pwgt/*= 0*/)
		: QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
	{
		m_ptxtFirstName = new QLineEdit;
		m_ptxtLastName  = new QLineEdit;

		QLabel* plblFirstName    = new QLabel("&Login");
		QLabel* plblLastName     = new QLabel("&Password");

		plblFirstName->setBuddy(m_ptxtFirstName);
		plblLastName->setBuddy(m_ptxtLastName);

		QPushButton* pcmdOk     = new QPushButton("&Ok");
		QPushButton* pcmdCancel = new QPushButton("&Cancel");

		connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
		connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

		QGridLayout* ptopLayout = new QGridLayout;
		ptopLayout->addWidget(plblFirstName, 0, 0);
		ptopLayout->addWidget(plblLastName, 1, 0);
		ptopLayout->addWidget(m_ptxtFirstName, 0, 1);
		ptopLayout->addWidget(m_ptxtLastName, 1, 1);
		ptopLayout->addWidget(pcmdOk, 2,0);
		ptopLayout->addWidget(pcmdCancel, 2, 1);
		setLayout(ptopLayout);
	}

	QString firstName() const
	{
		return m_ptxtFirstName->text();
	}
	QString lastName() const
	{
		return m_ptxtLastName->text();
	}
};

#endif  //_InputDialog_h_
