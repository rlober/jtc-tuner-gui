#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T14:45:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jtcTunerGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    jtcparameters.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lYARP_OS

unix|win32: LIBS += -lYARP_dev

unix|win32: LIBS += -lYARP_sig
unix|win32: LIBS += -lYARP_init
unix|win32: LIBS += -lYARP_math
unix|win32: LIBS += -lYARP_name
