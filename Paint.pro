# https://doc.qt.io/qt-6/qmake-variable-reference.html
CONFIG += console
QT += core widgets gui
DEFINES += QT_WIDGETS_LIB
#LIBS += 
INCLUDEPATH += .

HEADERS += paint.h \
           canvas.h  \
           circle.h \
           freeform.h \
           graphobj.h \
           line.h \
           nonsolidobj.h \
           polygon.h \
           rectangle.h \
           scene.h \
           solidobj.h \
           triangle.h
SOURCES += paint.cpp \
           canvas.cpp \
           circle.cpp \
           freeform.cpp \
           graphobj.cpp \
           line.cpp \
           main.cpp \
           nonsolidobj.cpp \
           polygon.cpp \
           rectangle.cpp \
           scene.cpp \
           solidobj.cpp \
           triangle.cpp

DISTFILES += \
    Paint.pro.user \
    buildXCode.sh
