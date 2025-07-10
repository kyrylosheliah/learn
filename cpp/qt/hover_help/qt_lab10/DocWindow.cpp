#include <QtGui>
#include "DocWindow.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>

DocWindow::DocWindow(QWidget* pwgt/*=0*/) : QTextEdit(pwgt) { }

void DocWindow::slotLoad()
{
    QString str = QFileDialog::getOpenFileName();
    if (str.isEmpty()) {
        return;
    }

    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();

        m_strFileName = str;
		emit changeWindowTitle(m_strFileName);
    }
}

void DocWindow::slotSave()
{
    if (m_strFileName.isEmpty()) {
		slotSaveAs();
        return;
    }

    QFile file(m_strFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << toPlainText();
        file.close();
		emit changeWindowTitle(m_strFileName);
    }
}

void DocWindow::slotSaveAs() 
{
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if (!str.isEmpty()) {
        m_strFileName = str;
        slotSave();
    }
}
