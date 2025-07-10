#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void newFile();
	void open();
	void save();
	void saveAs();
	void print();
	void exit();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void bold();
	void italic();
	void leftAlign();
	void rightAlign();
	void justify();
	void center();
	void setLineSpacing();
	void setParagraphSpacing();
	void about();
	void aboutQt();

private:
	void createActions();
	void createMenus();
	void createToolBars();


	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QActionGroup *fontStyleGroup;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *printAct;
	QAction *exitAct;
	QAction *undoAct;
	QAction *redoAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *boldAct;
	QAction *italicAct;
	QAction *leftAlignAct;
	QAction *rightAlignAct;
	QAction *justifyAct;
	QAction *centerAct;
	QAction *setLineSpacingAct;
	QAction *setParagraphSpacingAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
	QLabel *infoLabel;
};

#endif
