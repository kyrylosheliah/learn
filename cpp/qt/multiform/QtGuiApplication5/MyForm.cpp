#include "MyForm.h"

MyForm::MyForm(QWidget *pwgt) :QWidget(pwgt) {
	setupUi(this);
	connect(m_pcmdReset, SIGNAL(clicked()), SLOT(slotReset()));
}

void MyForm::slotReset() {
	m_lcd->display(0);
	m_sld->setValue(0);
}
