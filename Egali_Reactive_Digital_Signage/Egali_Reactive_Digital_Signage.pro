#-------------------------------------------------
#
# Project created by QtCreator 2017-03-24T22:59:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Egali_Reactive_Digital_Signage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        egalisignage.cpp \
    qrreaderthread.cpp \
    depthdetectorthread.cpp

HEADERS  += egalisignage.h \
    qrreaderthread.h \
    depthdetectorthread.h

FORMS    += egalisignage.ui

DISTFILES += \
    Config.xml \
    NOTICE \
    images/english/dys/guidance/0.jpg \
    images/english/dys/main/0.jpg \
    images/english/dys/secondary/0.jpg \
    images/english/std/guidance/0.jpg \
    images/english/std/main/0.jpg \
    images/english/std/main/1.jpg \
    images/english/std/main/2.jpg \
    images/english/vis/guidance/0.jpg \
    images/english/vis/main/0.jpg \
    images/english/vis/secondary/0.jpg \
    images/russian/dys/guidance/0.jpg \
    images/russian/dys/main/0.jpg \
    images/russian/dys/secondary/0.jpg \
    images/russian/std/guidance/0.jpg \
    images/russian/std/main/0.jpg \
    images/russian/std/secondary/0.jpg \
    images/russian/vis/guidance/0.jpg \
    images/russian/vis/main/0.jpg \
    images/russian/vis/secondary/0.jpg

INCLUDEPATH += /usr/include/ni
INCLUDEPATH += /usr/local/include
QMAKE_LFLAGS = -L/usr/local/lib -lzbar -lOpenNI

# The following lines tells Qmake to use pkg-config for opencv
QT_CONFIG -= no-pkg-config
CONFIG  += link_pkgconfig
PKGCONFIG += opencv
