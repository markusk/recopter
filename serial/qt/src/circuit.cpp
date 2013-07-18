/*************************************************************************
 *   Copyright (C) Markus Knapp                                          *
 *   www.direcs.de                                                       *
 *                                                                       *
 *   This file is part of direcs.                                        *
 *                                                                       *
 *   direcs is free software: you can redistribute it and/or modify it   *
 *   under the terms of the GNU General Public License as published      *
 *   by the Free Software Foundation, version 3 of the License.          *
 *                                                                       *
 *   direcs is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of      *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        *
 *   GNU General Public License for more details.                        *
 *                                                                       *
 *   You should have received a copy of the GNU General Public License   *
 *   along with direcs. If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                       *
 *************************************************************************/

#include "circuit.h"

Circuit::Circuit(InterfaceAvr *i, QMutex *m)
{
	// copy the pointer from the original object
	interface1 = i;
	mutex = m;

	circuitState = true; // We think positive
	firstInitDone = false;
	compassCircuitState = false;
}


Circuit::~Circuit()
{
}


bool Circuit::initCircuit()
{
	QByteArray bytes;
	bytes.resize(255); // @todo: serial receive buffer large enough?


	if (circuitState) // maybe robot is already recognized as OFF by the interface class (e.g. path to serial port not found)!
	{
		// Lock the mutex. If another thread has locked the mutex then this call will block until that thread has unlocked it.
		mutex->lock();

		//-------------------------------------------------------
		// Basic init for all the bits on the robot circuit
		//-------------------------------------------------------

		// sending RESET (INIT) command
		if (interface1->sendString("$M<") == true)
		{
			// send 'length' in bytes
			if (interface1->sendChar(0) == true)
			{
				// MSP_IDENT
				if (interface1->sendChar(100) == true)
				{
					// CRC
					if (interface1->sendChar(100) == true)
					{
						// wait for correct answer (12 bytes)
						if (interface1->receiveBytes(bytes, 12) == true)
						{
							//
							// okay
							//

							// Unlock the mutex
							mutex->unlock();

							// ciruit init okay
							firstInitDone = true;
							circuitState = true;
							emit robotState(true);

							return true;
						}
					}
				}
			}
		}

		// Unlock the mutex.
		mutex->unlock();

	}

	qDebug("INFO from initCircuit: Copter is OFF.");
//	firstInitDone = true;
//	circuitState = false;
	emit robotState(false);

	return false;
}


bool Circuit::replyCircuit()
{
	QByteArray bytes;


	// MSP_IDENT (100) reply
	//
	bytes.append("$M>"); // answer string
	bytes.append(7);     // length of payload
	bytes.append(100);   // MSP_IDENT
	bytes.append(1);     // VERSION
	bytes.append(3);     // MULTITYPE    (3 = Quad X)
	bytes.append(3);     // MSP_VERSION  (serial protocoll version)
	bytes.append(42);    // Capability   (DWord)
	bytes.append(23);    // "
	bytes.append(42);    // "
	bytes.append(23);    // "
	bytes.append(99);    // CRC


/*
	//
	// buggy
	//
	if (circuitState) // maybe robot is already recognized as OFF by the interface class (e.g. path to serial port not found)!
	{
		// Lock the mutex. If another thread has locked the mutex then this call will block until that thread has unlocked it.
		mutex->lock();

		// sending RESET (INIT) command
		if (interface1->sendBytes(bytes) == true)
		{
			// okay

			// Unlock the mutex
			mutex->unlock();

			return true;
		}

		// Unlock the mutex.
		mutex->unlock();

	}
*/

	//
	// works
	//
	if (interface1->sendChar('$'))
		if (interface1->sendChar('M'))
			if (interface1->sendChar('>'))
				if (interface1->sendChar(1))
					if (interface1->sendChar(0))
						if (interface1->sendChar(0))
							if (interface1->sendChar(1))
								if (interface1->sendChar(3))
									if (interface1->sendChar(3))
										if (interface1->sendChar(42))
											if (interface1->sendChar(23))
												if (interface1->sendChar(42))
													if (interface1->sendChar(23))
														if (interface1->sendChar(99))
															return true;


	return false;
}


bool Circuit::initCompass()
{
	QString answer = "error";

/*
	if (circuitState) // maybe robot is already recognized as OFF by the interface class (e.g. path to serial port not found)!
	{
		// Lock the mutex. If another thread has locked the mutex then this call will block until that thread has unlocked it.
		mutex->lock();

		// check if the 3D compass sensor is connected to the Atmel board
		if (interface1->sendString("cc") == true)
		{
			// check if the robot answers with "ok"
			if ( interface1->receiveString(answer) == true)
			{
				if (answer == "*ok#")
				{
					// Unlock the mutex
					mutex->unlock();

					compassCircuitState = true;
					emit compassState(true);

					return true;
				}
			}
		}

		// Unlock the mutex.
		mutex->unlock();

	}

	compassCircuitState = false;
	emit compassState(false);
*/
	return false;
}


bool Circuit::isConnected()
{
	// if not tried to init hardware, do this!
	if (firstInitDone == false)
	{
		initCircuit();
		firstInitDone = true;
	}

	return circuitState;
}


bool Circuit::compassConnected()
{
	// if not tried to init the robots (and compass) hardware, do this!
	if (firstInitDone == false)
	{
		initCircuit();
		firstInitDone = true;
	}

	return compassCircuitState;
}


void Circuit::setRobotState(bool state)
{
	// store the state within this class
	circuitState = state;
}
