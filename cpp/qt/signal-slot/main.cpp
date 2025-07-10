#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLCDNumber>
#include <QProgressBar>
#include <QLabel>
#include <QTextCodec>
#include <random>
#include <chrono>
constexpr char __globalNumberToChar[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
QString* QStringRandom(int size){
	QString * toreturn = new QString();
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < size; ++i){
		std::srand(rand());
		toreturn->push_back(__globalNumberToChar[(rand() % 62)]);
	}
	return toreturn;
}
int main (int argc, char * argv []) {
	int years = 130;

	QApplication app (argc, argv);
	QTextCodec * codec = QTextCodec::codecForName("utf-8");
	QGridLayout * layout = new QGridLayout;
	layout->setSpacing(10);

	QWidget * hbox = new QWidget();
	hbox->setWindowTitle(codec->toUnicode("Введіть Ваш Вік"));
	hbox->resize(300, 100);

	QSpinBox * spinBox = new QSpinBox(hbox);
	spinBox->setRange(0, years);
	spinBox->setValue(0);
	layout->addWidget(spinBox, 0, 0);

	QSlider * slider = new QSlider(Qt::Horizontal, hbox);
	slider->setRange(0, years);
	layout->addWidget(slider, 1, 0, 1, 2);

	QPushButton * btn = new QPushButton(codec->toUnicode("Завершення"), hbox);
	layout->addWidget(btn, 0, 1);

	QComboBox * list = new QComboBox(hbox);
	for (int i = 0; i < years + 1; ++i){
		list->addItem(QString::number(i));
	}
	layout->addWidget(list, 2, 0, 1, 2);

	QLCDNumber * lcd = new QLCDNumber(hbox);
	lcd->setStyleSheet("color:black");
	lcd->setStyleSheet("background:white");
	lcd->setFixedHeight(100);
	layout->addWidget(lcd, 3, 0, 1, 2);

	QProgressBar * linebar = new QProgressBar(hbox);
	linebar->setRange(0,years);
	linebar->setMaximum(years);
	layout->addWidget(linebar, 4, 0, 1, 2);

	QLabel * text = new QLabel(codec->toUnicode("Просто ничего не трогай"), hbox);
	layout->addWidget(text, 5, 0, 1, 2);

	hbox->setLayout(layout);

	QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), list, SLOT(setCurrentIndex(int)));
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
	QObject::connect(spinBox, SIGNAL(valueChanged(int)), linebar, SLOT(setValue(int)));
	QObject::connect(spinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), text, [text](int number){
		text->setText(*QStringRandom(number));
	});

	QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), list, SLOT(setCurrentIndex(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
	QObject::connect(slider, SIGNAL(valueChanged(int)), linebar, SLOT(setValue(int)));
	QObject::connect(slider, static_cast<void(QSlider::*)(int)>(&QSlider::valueChanged), text, [text](int number){
		text->setText(*QStringRandom(number));
	});

	QObject::connect(list, SIGNAL(currentIndexChanged(int)), spinBox, SLOT(setValue(int)));
	QObject::connect(list, SIGNAL(currentIndexChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(list, SIGNAL(currentIndexChanged(int)), lcd, SLOT(display(int)));
	QObject::connect(list, SIGNAL(currentIndexChanged(int)), linebar, SLOT(setValue(int)));
	QObject::connect(list, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), text, [text](int number){
		text->setText(*QStringRandom(number));
	});

	QObject::connect(btn, SIGNAL(clicked(bool)), hbox, SLOT(close()));
	
	hbox->show();
	return app.exec();
}
