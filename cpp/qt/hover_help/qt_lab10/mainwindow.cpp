#include <QtWidgets>
#include "mainwindow.h"
#include "InputDialog.h"
#include "HelpBrowser.h"

MainWindow::MainWindow()
{
	QWidget *widget = new QWidget(0);
	setCentralWidget(widget);

	infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
	infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setWhatsThis("<I>This is the Label</I><BR><B>Class QLabel</B>");
	infoLabel->setToolTip(tr("QLabel"));
	infoLabel->setStatusTip(tr("QLabel"));

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);
	layout->addWidget(infoLabel);
	m_pma = new QMdiArea;
	m_pma->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pma->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pma->setWhatsThis("<I>This is the MDI area</I><BR><B>Class QMdiArea</B>");
	m_pma->setToolTip(tr("QMdiArea"));
	m_pma->setStatusTip(tr("QMdiArea"));
	layout->addWidget(m_pma);
	widget->setLayout(layout);

	createActions();
	createMenus();
	createToolBars();

	menuBar()->setWhatsThis("<I>This is the menu bar</I><BR><B>Class QMenuBar</B>");
	menuBar()->setToolTip(tr("QMenuBar"));
	menuBar()->setStatusTip(tr("QMenuBar"));

	m_psigMapper = new QSignalMapper(this);
	connect(m_psigMapper, SIGNAL(mapped(QWidget*)), this, SLOT(slotSetActiveSubWindow(QWidget*)));

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);
	statusBar()->setWhatsThis("<I>This is the status bar</I><BR><B>Class QStatusBar</B>");
	statusBar()->setToolTip(tr("QStatusBar"));
	statusBar()->setStatusTip(tr("QStatusBar"));

	setWindowTitle(tr("qt lab10"));
	setMinimumSize(160, 160);
	setWindowFlags(Qt::Window | Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
	resize(480, 320);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	int stay = QMessageBox::warning(0, "Warning" , "Program will close\nDo you really want to quit?", "Yes", "No", QString(), 1, 1);
	//QMessageBox::information(0, "Information", "stay = " + QString::number(stay));
	if (!stay) {
		event->accept();
	} else {
		event->ignore();
	}
}

void MainWindow::slotChangeWindowTitle(const QString& str){
	qobject_cast<DocWindow*>(sender())->setWindowTitle(str);
}
void MainWindow::slotSetActiveSubWindow(QWidget* pwgt){
	if (pwgt) { m_pma->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(pwgt)); }
}
DocWindow* MainWindow::createNewDoc(){
	DocWindow* pdoc = new DocWindow;
	m_pma->addSubWindow(pdoc);
	pdoc->setAttribute(Qt::WA_DeleteOnClose);
	pdoc->setWindowTitle("Unnamed Document");
	pdoc->setWindowIcon(QIcon("images/new.png"));
	connect(pdoc, SIGNAL(changeWindowTitle(QString&)), SLOT(slotChangeWindowTitle(QString&)));
	return pdoc;
}

void MainWindow::newFile() {
	infoLabel->setText(tr("Invoked <b>File|New</b>"));
	createNewDoc()->show();}
void MainWindow::open(){
	infoLabel->setText(tr("Invoked <b>File|Open</b>"));
	DocWindow* pdoc = new DocWindow;
	m_pma->addSubWindow(pdoc);
	pdoc->slotLoad();
	pdoc->show();}
void MainWindow::save(){
	infoLabel->setText(tr("Invoked <b>File|Save</b>"));
	DocWindow* pdoc = qobject_cast<DocWindow*>(m_pma->activeSubWindow());
	if (pdoc) { pdoc->slotSave(); }}
void MainWindow::saveAs(){
	infoLabel->setText(tr("Invoked <b>File|Save As</b>"));
	DocWindow* pdoc = qobject_cast<DocWindow*>(m_pma->activeSubWindow());
	if (pdoc) { pdoc->slotSaveAs(); }}
void MainWindow::print(){infoLabel->setText(tr("Invoked <b>File|Print</b>"));}
void MainWindow::exit(){infoLabel->setText(tr("Invoked <b>File|Exit</b>"));
	QMessageBox::critical(0, "Error", "Feature not allowed", "Yes", "No", QString(), 1, 1);}
void MainWindow::undo(){infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));}
void MainWindow::redo(){infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));}
void MainWindow::cut(){infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));}
void MainWindow::copy(){infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));}
void MainWindow::paste(){infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));}
void MainWindow::bold(){infoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));}
void MainWindow::italic(){infoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));}
void MainWindow::leftAlign(){infoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));}
void MainWindow::rightAlign(){infoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));}
void MainWindow::justify(){infoLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));}
void MainWindow::center(){infoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));}
void MainWindow::setLineSpacing(){infoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));}
void MainWindow::setParagraphSpacing(){infoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));}
void MainWindow::login(){
	InputDialog* pInputDialog = new InputDialog(this);
	if (pInputDialog->exec() == QDialog::Accepted) {
		QMessageBox::information(0, "Information", "First Name: " + pInputDialog->firstName() + "\nLast Name: " + pInputDialog->lastName()); }
	delete pInputDialog;}
void MainWindow::helpBrowser(){
	HelpBrowser* helpBrowser = new HelpBrowser("doc", "index.htm");
	helpBrowser->resize(400, 300);
	helpBrowser->show();}
void MainWindow::about(){
	infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, "My application", "qt lab9");}
void MainWindow::aboutQt(){
	infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
	QApplication::aboutQt();}

void MainWindow::createActions()
{
	const QIcon newIcon = QIcon::fromTheme("document-new", QIcon("images/new.png"));
	newAct = new QAction(newIcon, tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setToolTip(tr("Create a new file"));
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	const QIcon openIcon = QIcon::fromTheme("document-open", QIcon("images/open.png"));
	openAct = new QAction(openIcon, tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setToolTip(tr("Open an existing file"));
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon("images/save.png"));
	saveAct = new QAction(saveIcon, tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
	saveAsAct = new QAction(saveAsIcon, tr("Save As..."), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setToolTip(tr("Save the document under a new name"));
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	const QIcon printIcon = QIcon::fromTheme("document-print", QIcon("images/printer.png"));
	printAct = new QAction(printIcon, tr("&Print"), this);
	printAct->setShortcuts(QKeySequence::Print);
	printAct->setToolTip(tr("Print document"));
	printAct->setStatusTip(tr("Print document"));
	connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

	const QIcon exitIcon = QIcon::fromTheme("application-exit");
	exitAct = new QAction(exitIcon, tr("&Exit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setToolTip(tr("Exit the application"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));



	const QIcon undoIcon = QIcon::fromTheme("edit-cut", QIcon("images/undo.png"));
	undoAct = new QAction(undoIcon, tr("&Undo"), this);
	undoAct->setShortcuts(QKeySequence::Undo);
	undoAct->setToolTip(tr("Undo"));
	undoAct->setStatusTip(tr("Undo"));
	connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

	const QIcon redoIcon = QIcon::fromTheme("edit-cut", QIcon("images/redo.png"));
	redoAct = new QAction(redoIcon, tr("&Redo"), this);
	redoAct->setShortcuts(QKeySequence::Redo);
	redoAct->setToolTip(tr("Redo"));
	redoAct->setStatusTip(tr("Redo"));
	connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

	const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon("images/cut.png"));
	cutAct = new QAction(cutIcon, tr("&Cut"), this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setToolTip(tr("Cut the current selection's contents to the clipboard"));
	cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
	connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

	const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon("images/copy.png"));
	copyAct = new QAction(copyIcon, tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setToolTip(tr("Copy the current selection's contents to the clipboard"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
	connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

	const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon("images/paste.png"));
	pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setToolTip(tr("Paste the clipboard's contents into the current selection"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
	connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));



	boldAct = new QAction(tr("Bold"), this);
	QFont font = boldAct->font();
	font.setBold(true);
	boldAct->setFont(font);
	boldAct->setShortcuts(QKeySequence::Bold);
	boldAct->setToolTip(tr("Bold"));
	boldAct->setStatusTip(tr("Bold"));
	boldAct->setCheckable(true);
	connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));
	italicAct = new QAction(tr("Italic"), this);
	font = italicAct->font();
	font.setItalic(true);
	italicAct->setFont(font);
	italicAct->setShortcuts(QKeySequence::Italic);
	italicAct->setToolTip(tr("Italic"));
	italicAct->setStatusTip(tr("Italic"));
	italicAct->setCheckable(true);
	connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));
	fontStyleGroup = new QActionGroup(this);
	fontStyleGroup->addAction(boldAct);
	fontStyleGroup->addAction(italicAct);
	fontStyleGroup->setExclusive(true);

	leftAlignAct = new QAction(tr("Left Align"), this);
	leftAlignAct->setShortcuts(QList<QKeySequence>{Qt::CTRL+Qt::Key_L});
	leftAlignAct->setToolTip(tr("Left Align"));
	leftAlignAct->setStatusTip(tr("Left Align"));
	leftAlignAct->setCheckable(true);
	connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));
	rightAlignAct = new QAction(tr("Right Align"), this);
	rightAlignAct->setShortcuts(QList<QKeySequence>{Qt::CTRL+Qt::Key_R});
	rightAlignAct->setToolTip(tr("Right Align"));
	rightAlignAct->setStatusTip(tr("Right Align"));
	rightAlignAct->setCheckable(true);
	connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));
	justifyAct = new QAction(tr("Justify"), this);
	justifyAct->setShortcuts(QList<QKeySequence>{Qt::CTRL+Qt::Key_J});
	justifyAct->setStatusTip(tr("Justify"));
	justifyAct->setCheckable(true);
	connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));
	centerAct = new QAction(tr("Center"), this);
	centerAct->setShortcuts(QList<QKeySequence>{Qt::CTRL+Qt::Key_E});
	centerAct->setToolTip(tr("Center"));
	centerAct->setStatusTip(tr("Center"));
	centerAct->setCheckable(true);
	connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

	setLineSpacingAct = new QAction(tr("Set Line Spacing..."), this);
	setLineSpacingAct->setToolTip(tr("Set Line Spacing..."));
	setLineSpacingAct->setStatusTip(tr("Set Line Spacing..."));
	connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

	setParagraphSpacingAct = new QAction(tr("Set Paragraph Spacing..."), this);
	setParagraphSpacingAct->setToolTip(tr("Set Paragraph Spacing..."));
	setParagraphSpacingAct->setStatusTip(tr("Set Paragraph Spacing..."));
	connect(setParagraphSpacingAct, SIGNAL(triggered()), this, SLOT(setParagraphSpacing()));


	loginAct = new QAction(tr("Log In"), this);
	loginAct->setToolTip(tr("Log In"));
	loginAct->setStatusTip(tr("Log In"));
	connect(loginAct, SIGNAL(triggered()), this, SLOT(login()));
	helpBrowserAct = new QAction(tr("Open help browser"), this);
	helpBrowserAct->setToolTip(tr("Help browser"));
	helpBrowserAct->setStatusTip(tr("Help browser"));
	connect(helpBrowserAct, SIGNAL(triggered()), this, SLOT(helpBrowser()));
	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setToolTip(tr("Show the application's About box"));
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	aboutQtAct = new QAction(tr("About &Qt"), qApp);
	aboutQtAct->setToolTip(tr("Show the Qt library's About box"));
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addSeparator();
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);
	editMenu->addSeparator();

	formatMenu = editMenu->addMenu(tr("&Format"));
	formatMenu->addAction(boldAct);
	formatMenu->addAction(italicAct);
	formatMenu->addSeparator()->setText(tr("&Alignment"));
	formatMenu->addAction(leftAlignAct);
	formatMenu->addAction(rightAlignAct);
	formatMenu->addAction(justifyAct);
	formatMenu->addAction(centerAct);
	formatMenu->addSeparator();
	formatMenu->addAction(setLineSpacingAct);
	formatMenu->addAction(setParagraphSpacingAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(loginAct);
	helpMenu->addAction(helpBrowserAct);
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(newAct);
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);
	fileToolBar->addSeparator();
	fileToolBar->setWhatsThis("<I>This is the file tool bar</I><BR><B>Class QToolBar</B>");
	fileToolBar->setToolTip(tr("QToolBar"));
	fileToolBar->setStatusTip(tr("QToolBar"));
	editToolBar = addToolBar(tr("&Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);
	editToolBar->setWhatsThis("<I>This is the edit tool bar</I><BR><B>Class QToolBar</B>");
	editToolBar->setToolTip(tr("QToolBar"));
	editToolBar->setStatusTip(tr("QToolBar"));
}
