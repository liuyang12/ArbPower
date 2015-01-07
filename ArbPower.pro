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
    powP.cpp \
    Taylor.cpp \
    functions.cpp

HEADERS  += arbpower.h \
    functions.h \
    Taylor.h

FORMS    += arbpower.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=
