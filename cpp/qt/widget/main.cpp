#include <QApplication>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMainWindow>
int main (int argc, char * argv []) {

	QApplication app (argc, argv);

	QMainWindow * mainWidget = new QMainWindow(nullptr, Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
	mainWidget->setWindowTitle(QString::fromUtf8("MyWidget"));
	QPalette * widgetBoxPalette = new QPalette();
	widgetBoxPalette->setColor(mainWidget->backgroundRole(), QColor(127,0,0));
	mainWidget->setPalette(*widgetBoxPalette);

	QWidget * widgetBox = new QWidget(mainWidget);
	widgetBox->resize(300, 300);

	QFrame * frame = new QFrame(widgetBox);
	frame->resize(300, 300);
	frame->setLineWidth(10);
	frame->setStyleSheet("margin: 10; padding: 10");
	//frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	frame->setFrameShape(QFrame::Panel);
	frame->setFrameShadow(QFrame::Sunken);

	QScrollArea * scroll = new QScrollArea(widgetBox);
	scroll->setGeometry(frame->contentsRect());
	scroll->setBackgroundRole(QPalette::Dark);
	QPixmap * picture = new QPixmap("picture.png");
	QLabel * pictureLabelHolder = new QLabel();
	pictureLabelHolder->setPixmap(*picture);
	scroll->setWidget(pictureLabelHolder);

	QPixmap * cursorPixmap = new QPixmap("cursor256aboba.png");
	QCursor * cursor = new QCursor(*cursorPixmap, 1, 1);
	pictureLabelHolder->setCursor(*cursor);
	scroll->setCursor(*cursor);

	QLabel * labelTable = new QLabel(mainWidget);
	labelTable->setText("<table><tbody><tr><td><b>[Автор книги]</b></td><td><b>[Назва]</b></td><td><b>[рік випуску]</b></td><td><b>[Група]</b></td></tr><tr><td>Сенкевич</td><td>потоп</td><td>1978</td><td>Х</td></tr><tr><td>Ландау</td><td>механіка</td><td>1989</td><td>У</td></tr><tr><td>Дойль</td><td>сумчасті</td><td>1990</td><td>C</td></tr></tbody></table><ul>Примітка:<li>Х – художня література;</li><li>У – навчальна література;</li><li>З – довідкова література</li></ul>");
	labelTable->setStyleSheet("color: white");
	labelTable->setGeometry(10, 300, 300, 200);

	mainWidget->show();
	return app.exec();
}
