#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include "mainwindow.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv) 
{
    QApplication app(argc, argv);

	QSplashScreen splash(QPixmap("splash.png"));
	splash.show();
	QElapsedTimer time;
	time.start();
	for (int i = 0; i < 100; ) {
		if (time.elapsed() > 40) { time.start(); ++i; }
		splash.showMessage("Loading modules: " + QString::number(i) + "%", Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
	}
	splash.finish(nullptr);

	MainWindow window;
	window.show();
    return app.exec();
}
