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
#include <QDateTime>

//---------------------------------------------------------------------------------------------------

#include "circuit.h"
#include "interfaceAvr.h"
#include "simulationThread.h"

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

	/**
	Returns the status of the main program. True, if the simulationMode ist active.
	*/
	bool simulationMode() const;


protected:
	void closeEvent(QCloseEvent *event);


public slots:
	/**
	Appends text to the main log in the main window.
	@param text is the text to be displayed.
	@param CR adds a carriage return (CR) to the text, if true (default). This parameter is optional!
	@param sayIt If true, the text is also spoken (default=false). This parameter is optional!
	 */
	void appendLog(QString text, bool CR=true, bool sayIt=false, bool addTimestamp=true);


private slots:
	void about();
	void testSlot();      //    < < < <   this is the test slot where all magic happens
	void replySlot(); // second slot for testing
	void setSerialPort(QString port);

	/**
	This slot enables or disables the simulation mode.
	@param status
	*/
	void setSimulationMode(bool status);


signals:
	/**
	Emits a string to the GUI log / console.
	@param text is the message to be emitted
	*/
	void message(QString text, bool CR=true, bool sayIt=false, bool addTimestamp=true);

	/**
	Enables or disables the copter simulation mode.
	@param state can be true or false.
	@sa Direcs::setSimulationMode()
	*/
	void simulate(bool state);


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
	QAction *testAct;      //    < < < <   this is the test action for me and anyone who may need it ;-)  It calls the "testSlot" method.
	QAction *replyAct;    //    < < < <   this is the second action for me and anyone who may need it ;-)  It calls the "answerSlot" method.

	QList <float> pointerFloatList;
	QList <int *> pointerIntList;

	mutable QMutex *mutex; // make the threads thread-safe (e.g. senorThread, servo...)
	Circuit *circuit1;
	InterfaceAvr *interface1;
	QString serialPort; // something like /dev/ttyUSB0
	SimulationThread *simulationThread;
	bool robotSimulationMode; /// Stores the robots simulation state
};

#endif
