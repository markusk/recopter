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


	mutex = new QMutex();
	interface1 = new InterfaceAvr();
	circuit1 = new Circuit(interface1, mutex);

//	serialPortPath = "/dev/tty.SLAB_USBtoUART"; // Original driver "CP210x Macintosh OSX Driver v2." from SiLabs used.
//	serialPortPath = "/dev/tty.usbserial-A900J1TU"; // ARM board with STM32F4 and FTDI RS232R chip
//	serialPortPath = "/dev/tty.USA19Hfa141P1.1"; // KEYSPAN Adapter


	//-----------------------------------------------
	QString mySerialPort = "tty.USA19H";
	serialPort = "undefined";

	// send messages from the other class to this class (to the GUI)
	connect(interface1, SIGNAL( message(QString) ), this, SLOT( appendLog(QString) ));

	//--------------------------------------------------------------------------
	// let some classes know the copters state
	//--------------------------------------------------------------------------
	// this is needed, when the first openCOMPort method fails:
	connect(interface1,	SIGNAL( robotState(bool) ), circuit1,		SLOT( setRobotState(bool) ));


	// find out serial devices
	textEdit->append("Searching serial ports...");
	readSerialDevices();

	// find specific adapter in combo box list
	int index = serialPortBox->findText(mySerialPort, Qt::MatchStartsWith);

	// port found
	if (index != -1)
	{
		// change port in GUI
		serialPortBox->setCurrentIndex(index);

		// set serial port
		setSerialPort(serialPortBox->itemText(index));
	} // port found
	else
	{
		textEdit->append(QString("Error: serial port '%1' not found in list / file system").arg(serialPort));
	}
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
	cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
	connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

	copyAct = new QAction(QIcon(":/editcopy.xpm"), tr("&Copy"), this);
	copyAct->setShortcut(tr("Ctrl+C"));
	copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
	connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

	pasteAct = new QAction(QIcon(":/editpaste.xpm"), tr("&Paste"), this);
	pasteAct->setShortcut(tr("Ctrl+V"));
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
	connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	connect(textEdit, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
	connect(textEdit, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));

	// first test action
	testAct = new QAction(QIcon(":/utilities-system-monitor-active.png"), tr("&Test"), this);
	testAct->setShortcut(tr("Ctrl+T"));
	testAct->setStatusTip(tr("Test"));
	connect(testAct, SIGNAL(triggered()), this, SLOT(testSlot()));

	// answer test action
	replyAct = new QAction(QIcon(":/system-switch-user.png"), tr("&Reply"), this);
	replyAct->setShortcut(tr("Ctrl+R"));
	replyAct->setStatusTip(tr("Reply"));
	connect(replyAct, SIGNAL(triggered()), this, SLOT(replySlot()));
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

	// test
	testMenu = menuBar()->addMenu(tr("&Test"));
	testMenu->addAction(testAct);
	testMenu->addAction(replyAct);
}


void test::createToolBars()
{
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(cutAct);
	editToolBar->addAction(copyAct);
	editToolBar->addAction(pasteAct);

	testToolBar = addToolBar(tr("Test"));
	testToolBar->addAction(testAct);
	testToolBar->addAction(replyAct);

	serialToolBar = addToolBar(tr("Serial Port Choice"));
}


void test::createComboBox()
{
	serialPortBox = new QComboBox(this);
	serialPortBox->setParent(serialToolBar);

	// change serial port name when selected in combo box
	connect(serialPortBox, SIGNAL(activated(QString)), this, SLOT(setSerialPort(QString)));
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

	// read serial port
//	settings.setValue("serialPort", serialPortPath);

//	textEdit->append(QString("Port %1 read from settings.").arg(serialPortPath));
}


void test::writeSettings()
{
	QSettings settings("Markus Knapp", "recopterGUItest");
	settings.setValue("pos", pos());
	settings.setValue("size", size());

	// serial port
//	settings.setValue("serialPort", serialPortPath);
}


void test::readSerialDevices()
{
	QDir dir = QDir::root();                 // "/"
	QFileInfoList devices;
	QFileInfo fileInfo;
	QString listItem;


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
		fileInfo = devices.at(i);

		listItem = QString("%1").arg(fileInfo.fileName());

		if (listItem.startsWith("tty"))
		{
//			textEdit->append(listItem);
			serialPortBox->addItem(listItem);
		}
	}
}


void test::appendLog(QString message)
{
	textEdit->append(message);
}


void test::setSerialPort(QString port)
{
	serialPort = QString("/dev/%1").arg(port);
	textEdit->append(QString("Port now set to %1.").arg(serialPort));
}


void test::testSlot()
{
	static bool portOpened = false;


	if (portOpened == false)
	{
		textEdit->append("Opening port for communication...");

		if (interface1->openComPort(serialPort, 115200) == false)
		{
			// ********************
			// * The copter is OFF *
			// ********************
			textEdit->append(QString("Error opening serial port '%1'").arg(serialPort));
		}
		else
		{
			// *******************
			// * The copter is ON *
			// *******************
			portOpened = true;
			textEdit->append("Serial port opened.");
		}
	}

	textEdit->append("Searching copter...");


	if (circuit1->initCircuit() == true)
	{
		textEdit->append("Copter is <font color=\"#00FF00\">ON</font> and answers.");
	}
	else
	{
		textEdit->append("Error initializing.");
	}
}


void test::replySlot()
{
	static bool portOpened = false;


	if (portOpened == false)
	{
		textEdit->append("Opening port for communication...");

		if (interface1->openComPort(serialPort, 115200) == false)
		{
			// ********************
			// * The copter is OFF *
			// ********************
			textEdit->append(QString("Error opening serial port '%1'").arg(serialPort));
		}
		else
		{
			// *******************
			// * The copter is ON *
			// *******************
			portOpened = true;
			textEdit->append("Serial port opened.");
		}
	}

	textEdit->append("Replying...");

	if (circuit1->replyCircuit() == true)
	{
		textEdit->append("replied.");
	}
	else
	{
		textEdit->append("Error replying.");
	}
}
