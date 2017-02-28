#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T10:22:58
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csa8k_eye
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/csa8k_api_eye_pattern.c \
    src/dialog_db.cpp \
    src/dialog_meas.cpp \
    src/sql_db.cpp \
    src/option_parser.cpp \
    src/qttelnet.cpp


HEADERS += include/mainwindow.h \
    include/visa.h \
    include/visatype.h \
    include/csa8k_api.h \
    build/ui_mainwindow.h \
    include/dialog_db.h \
    include/list.h \
    include/dialog_meas.h \
    include/sql_db.h \
    include/option_parser.h \
    include/qttelnet.h

FORMS += src/mainwindow.ui \
    src/dialog_db.ui \
    src/dialog_meas.ui

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lvisa32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lvisa32
else:unix: LIBS += -L$$PWD/lib/ -lvisa32

#win32:LIBS += -lWs2_32
LIBS += -lpthread libwsock32 libws2_32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
