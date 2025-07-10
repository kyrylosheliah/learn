/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLCDNumber *m_lcd;
    QSlider *m_sld;
    QVBoxLayout *verticalLayout_2;
    QPushButton *m_pcmdReset;
    QPushButton *m_pcmdQuit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(800, 600);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_lcd = new QLCDNumber(MyForm);
        m_lcd->setObjectName(QString::fromUtf8("m_lcd"));

        verticalLayout->addWidget(m_lcd);

        m_sld = new QSlider(MyForm);
        m_sld->setObjectName(QString::fromUtf8("m_sld"));
        m_sld->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(m_sld);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_pcmdReset = new QPushButton(MyForm);
        m_pcmdReset->setObjectName(QString::fromUtf8("m_pcmdReset"));

        verticalLayout_2->addWidget(m_pcmdReset);

        m_pcmdQuit = new QPushButton(MyForm);
        m_pcmdQuit->setObjectName(QString::fromUtf8("m_pcmdQuit"));

        verticalLayout_2->addWidget(m_pcmdQuit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(MyForm);
        QObject::connect(m_sld, SIGNAL(valueChanged(int)), m_lcd, SLOT(display(int)));
        QObject::connect(m_pcmdQuit, SIGNAL(clicked()), MyForm, SLOT(close()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "MainWidget", nullptr));
        m_pcmdReset->setText(QCoreApplication::translate("MyForm", "&Reset", nullptr));
        m_pcmdQuit->setText(QCoreApplication::translate("MyForm", "&Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
