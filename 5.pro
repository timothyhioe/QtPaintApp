QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    circle.cpp \
    freeform.cpp \
    graphobj.cpp \
    line.cpp \
    main.cpp \
    nonsolidobj.cpp \
    paint.cpp \
    polygon.cpp \
    rectangle.cpp \
    scene.cpp \
    solidobj.cpp \
    triangle.cpp

HEADERS += \
    canvas.h \
    circle.h \
    freeform.h \
    graphobj.h \
    line.h \
    nonsolidobj.h \
    paint.h \
    polygon.h \
    rectangle.h \
    scene.h \
    solidobj.h \
    triangle.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Paint.pro

DISTFILES += \
    .gitignore \
    5.pro.user \
    buildXCode.sh
