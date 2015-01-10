#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T21:40:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArbPower
TEMPLATE = app


SOURCES += main.cpp\
        arbpower.cpp \
    Taylor.cpp \
    functions.cpp \
    ode.cpp \
    integral.cpp \
    root.cpp

HEADERS  += arbpower.h \
    functions.h \
    Taylor.h \
    ode.h \
    integral.h \
    root.h

FORMS    += arbpower.ui

RESOURCES += \
    res.qrc

RC_FILE = myicon.rc

OTHER_FILES +=
