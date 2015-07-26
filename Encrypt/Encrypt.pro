#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T20:37:29
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Encrypt
TEMPLATE = app


SOURCES += main.cpp\
        encrypt.cpp \
    botanwrapper.cpp

HEADERS  += encrypt.h \
    botanwrapper.h

FORMS    += encrypt.ui
include(botan/botan.pri)

OTHER_FILES += \
    C:/Users/Alex/Desktop 3/JesusHolding.jpg \
    C:/Users/Alex/Desktop 3/MARY_CHILD2.jpg

RESOURCES += \
    Resoucer.qrc
