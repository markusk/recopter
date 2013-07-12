/***************************************************************************
 *   Copyright (C) Markus Knapp                                            *
 *   www.direcs.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtGui>
#include "test.h"

#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>

test::test()
{
	textEdit = new QTextEdit;
	setCentralWidget(textEdit);

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	readSettings();

	createComboBox(); // for serial ports

	//---------------------------------------------------------------------------------------------------
	// AtmelBoard test stuff

	mutex = new QMutex();
	interface1 = new InterfaceAvr();
	circuit1 = new Circuit(interface1, mutex);

//	serialPortPath = "/dev/tty.SLAB_USBtoUART"; // Original driver "CP210x Macintosh OSX Driver v2." from SiLabs used.
//	serialPortPath = "/dev/tty.usbserial-A900J1TU"; // ARM board with STM32F4 and FTDI RS232R chip
	serialPortPath = "/dev/tty.USA19Hfa141P1.1"; // KEYSPAN Adapter

	// send messages from the other class to this class (to the GUI)
	connect(interface1, SIGNAL( message(QString) ), this, SLOT( appendLog(QString) ));

	//--------------------------------------------------------------------------
	// let some classes know the robots state
	//--------------------------------------------------------------------------
	// this is needed, when the first openCOMPort method fails:
	connect(interface1,	SIGNAL( robotState(bool) ), circuit1,		SLOT( setRobotState(bool) ));


	// find out serial devices
	textEdit->append("Searching serial ports...");
	readSerialDevices();

	textEdit->append("Opening serial port for microcontroller communication...");

	if (interface1->openComPort(serialPortPath, 115200) == false)
	{
		// ********************
		// * The robot is OFF *
		// ********************
		textEdit->append(QString("Error opening serial port '%1'").arg(serialPortPath));

	}
	else
	{
		// *******************
		// * The robot is ON *
		// *******************
		textEdit->append("Serial port opened.");


		//==========================
		// init the robots circuit
		//==========================
		textEdit->append("Searching robot...");

		if (circuit1->initCircuit() == true)
		{
			textEdit->append("Robot is <font color=\"#00FF00\">ON</font> and answers.");
		}
	}
	//---------------------------------------------------------------------------------------------------

}


test::~test()
{
	// AtmelBoard test stuff
	delete circuit1;
	delete interface1;
	delete mutex;
}


void test::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
}


void test::about()
{
	QMessageBox::about(this, tr("About Application"),
					   tr("The <b>Application</b> example demonstrates how to "
						  "write modern GUI applications using Qt, with a menu bar, "
						  "toolbars, and a status bar."));
}


void test::createActions()
{
	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	cutAct = new QAction(QIcon(":/editcut.xpm"), tr("Cu&t"), this);
	cutAct->setShortcut(tr("Ctrl+X"));
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
							"clipboard"));
	connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

	copyAct = new QAction(QIcon(":/editcopy.xpm"), tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+C"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
							 "clipboard"));
	connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

	pasteAct = new QAction(QIcon(":/editpaste.xpm"), tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+V"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
							  "selection"));
	connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	connect(textEdit, SIGNAL(copyAvailable(bool)),
			cutAct, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(copyAvailable(bool)),
			copyAct, SLOT(setEnabled(bool)));

	testAct = new QAction(QIcon(":/utilities-system-monitor-active.png"), tr("&Test"), this);
	testAct->setShortcut(tr("Ctrl+T"));
	testAct->setStatusTip(tr("Test"));
	connect(testAct, SIGNAL(triggered()), this, SLOT(testSlot()));
}


void test::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAct);
	editMenu->addAction(copyAct);
	editMenu->addAction(pasteAct);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);

	menuBar()->addSeparator();

	testMenu = menuBar()->addMenu(tr("&Test"));
	testMenu->addAction(testAct);
}


void test::createToolBars()
{
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);

	testToolBar = addToolBar(tr("Test"));
	testToolBar->addAction(testAct);
}


void test::createComboBox()
{
	serialPortBox = new QComboBox(this);
	serialPortBox->setParent(testToolBar);

	serialPortBox->addItem("test");
}


void test::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}


void test::readSettings()
{
	QSettings settings("Markus Knapp", "recopterGUItest");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}


void test::writeSettings()
{
	QSettings settings("Markus Knapp", "recopterGUItest");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}


void test::readSerialDevices()
{
	QDir dir = QDir::root();                 // "/"
	QFileInfoList devices;


	// set and change directory
	dir.cd("dev");

	// set filters
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::System);
	dir.setSorting(QDir::Name | QDir::DirsFirst);

	// check
	if (!dir.exists())
		qWarning("Cannot find directory!");

	// read directory
	devices = dir.entryInfoList();

	// show filenames
	for (int i = 0; i < devices.size(); ++i)
	{
		QFileInfo fileInfo = devices.at(i);
		QString test;

		test = QString("%1").arg(fileInfo.fileName());

		if (test.startsWith("tty"))
			textEdit->append(test);
	}
}


void test::appendLog(QString message)
{
	textEdit->append(message);
}


void test::testSlot()
{
	QString string;


	// clear content
	// textEdit->clear();

	/*
	// send re
	interface1->sendString("re");
	// debug msg
	textEdit->append( QString("%1: %2 sent").arg(QDateTime::currentDateTime().toString() ).arg(string) );

	// receive answer
	interface1->receiveString(string);
	// debug msg
	textEdit->append( QString("%1: %2 received.").arg(QDateTime::currentDateTime().toString() ).arg(string) );
*/


/*
	// send s7
	interface1->sendString("s7");
	// debug msg
	textEdit->append( QString("%1: %2 sent").arg(QDateTime::currentDateTime().toString() ).arg(string) );

	// receive answer
	interface1->receiveString(string);
	// debug msg
	textEdit->append( QString("%1: %2 received.").arg(QDateTime::currentDateTime().toString() ).arg(string) );
*/
}
