#-------------------------------------------------
#
# Project created by QtCreator 2017-02-05T16:47:34
#
#-------------------------------------------------
# sifm xw 0 0xc7 0xd1 1 0x7f 1 0x02
# sifm xr 0 0xc7 0xd1 1 0xEC 1
#开启长发光
#echo GPON_pattern > /proc/pon_phy/debug
#关闭长发��#echo dis_pattern > /proc/pon_phy/debug
#http://docs.huihoo.com/qt/solutions/4/qttelnet/qttelnet.html
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bias_power
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
