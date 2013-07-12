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


#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QtDebug>
#include <QMutex>
#include <QMetaType> // for qRegisterMetaType
#include <QDir>

//---------------------------------------------------------------------------------------------------

#include "circuit.h"
#include "interfaceAvr.h"

//---------------------------------------------------------------------------------------------------


class QAction;
class QMenu;
class QTextEdit;
class QComboBox;

class test:public QMainWindow
{
	Q_OBJECT

public:
	test();
	~test();

protected:
	void closeEvent(QCloseEvent *event);

public slots:
	void appendLog(QString message);

private slots:
	void about();
	void testSlot();      //    < < < <   this is the test slot where all magic happens
	void setSerialPort(QString serialPort);

signals:
	/**
	  Emits a string to the GUI log / console.
	  @sa this::appendLog()
	  @param text is the message to be emitted
	  */
	void message(QString text);

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createComboBox();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	void readSerialDevices();

	QTextEdit *textEdit;
	QString curFile;
	QString mSerialPort;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QMenu *testMenu;
	QToolBar *editToolBar;
	QToolBar *testToolBar;
	QToolBar *serialToolBar;
	QComboBox *serialPortBox;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
//	QAction *portSelectedAct;
	QAction *testAct;      //    < < < <   this is the test action for me and anyone who may need it ;-)  It calls the "testSlot" method.

	QList <float> pointerFloatList;
	QList <int *> pointerIntList;

	mutable QMutex *mutex; // make the threads thread-safe (e.g. senorThread, servo...)
	Circuit *circuit1;
	InterfaceAvr *interface1;
	QString serialPortPath; // something like /dev/ttyUSB0

};

#endif
