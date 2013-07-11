SOURCES += test.cpp \
	laser.cpp \
	laserSickS300.cpp \
        main.cpp \
        direcsSerial.cpp \
        inifile.cpp \
        interfaceAvr.cpp \
        circuit.cpp
HEADERS += test.h \
	laser.h \
	laserSickS300.h \
	laserThread.h
        direcsSerial.h \
        inifile.h \
        interfaceAvr.h \
        circuit.h
TEMPLATE = app
CONFIG += warn_on \
        thread \
        qt \
        release
TARGET = test
DESTDIR = ../bin
RESOURCES = application.qrc
FORMS +=

# QMAKE_CXXFLAGS+= -m32

MOC_DIR = ../tmp

OBJECTS_DIR = ../tmp

