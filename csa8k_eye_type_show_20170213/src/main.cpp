#include "mainwindow.h"
#include <QApplication>
#include "telnet_login.h"
#include "qttelnet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
