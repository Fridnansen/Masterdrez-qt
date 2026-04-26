#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T09:19:55
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG+=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Masterdrez-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml2.cpp \
    myopengl.cpp \
    graficos.cpp \
    masterdrez.cpp

HEADERS  += mainwindow.h \
    tinyxml2.h \
    myopengl.h \
    qdebugstream.h \
    graficos.h \
    masterdrez.h \
    lcdnumber.h \
    masterdrez-ia4x4.h \
    masterdrez-ia6x6.h \
    masterdrez-axiomas.h \
    masterdrez-movimientos.h \
    masterdrez-manejoxml.h \
    masterdrez-tablero.h \
    masterdrez-resetvar.h \
    masterdrez-aperturas.h \
    mtrand.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/GL/ -lglut32

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/GL/glut32.lib
