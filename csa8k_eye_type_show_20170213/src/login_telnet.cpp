#include "login_telnet.h"
#include "ui_login_telnet.h"
#include "mainwindow.h"
#include <unistd.h>
#include <windows.h>

login_telnet::login_telnet(QWidget *parent) :
    QDialog(parent),t(new QtTelnet),
    ui(new Ui::login_telnet)
{
    ui->setupUi(this);
    ui->lineEdit_host->setText("192.168.1.1");
    //QString IP("192.168.1.1");
    ui->lineEdit_user->setText("admin");
    ui->lineEdit_2_pwd->setText("1234");

    connect(t, SIGNAL(message(const QString &)),this, SLOT(telnetMessage(const QString &)));
    connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),
            this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));
    connect(t, SIGNAL(message(const QString &)),this, SLOT(telnetMessage(const QString &)));
    connect(t, SIGNAL(loginRequired()),this, SLOT(telnetLoginRequired()));
    connect(t, SIGNAL(loginFailed()),this, SLOT(telnetLoginFailed()));
    connect(t, SIGNAL(loggedOut()),this, SLOT(telnetLoggedOut()));
    connect(t, SIGNAL(loggedIn()),this, SLOT(telnetLoggedIn()));

    //t->connectToHost("192.168.1.1");
    emit ui->pushButton_connnect->clicked(true);
}

login_telnet::~login_telnet()
{
    delete ui;
}

void login_telnet::on_pushButton_connnect_clicked()
{
//    QString host = ui->lineEdit_host->text();
//    host = host.trimmed();
//    if (!host.isEmpty())
//        t->connectToHost(host);
//    else
//        ui->label_statue->setText("host is empty");

    t->connectToHost("192.168.1.1");
    t->socket()->waitForBytesWritten(30000);
    if (t->socket()->waitForConnected(20000)){
        emit ui->pushButton_user_ok->clicked(true);
    }

    //emit ui->pushButton_user_ok->clicked(true);
}

#if 0
void login_telnet::telnetConnectionError(QAbstractSocket::SocketError error)
{
    ui->label_statue->setText(QString("Connection error: %1").arg(error));
}

void login_telnet::telnetLoggedIn()
{
    ui->label_statue->setText("login in");
}

void login_telnet::telnetLoggedOut()
{
    ui->label_statue->setText("Logged Out");
}

void login_telnet::telnetLoginFailed()
{
    ui->label_statue->setText("telnet Login Failed");
}

void login_telnet::telnetMessage(const QString &msg)
{
    //textEdit->append(stripCR(msg));
    ui->label_statue->setText(stripCR(msg));
    qDebug() << stripCR(msg);
    //QScrollBar *s = textEdit->verticalScrollBar();
    //s->setValue(s->maximum());
}

QString login_telnet::stripCR(const QString &msg)
{
    qDebug() << msg;
    QString nmsg(msg);
    nmsg.remove('\r');
    nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes
    return nmsg;
}
#endif
void login_telnet::on_pushButton_3_cancel_clicked()
{
    this->close();
}

void login_telnet::on_pushButton_user_ok_clicked()
{
    t->sendData("admin");
    t->socket()->waitForBytesWritten(20000);
    emit ui->pushButton_2_pwd_ok->clicked(true);
}

void login_telnet::on_pushButton_2_pwd_ok_clicked()
{
    t->sendData("1234");
    t->socket()->waitForBytesWritten(20000);
    ui->pushButton_light->clicked(true);
}

void login_telnet::on_pushButton_light_clicked()
{
    t->sendData("echo GPON_pattern > /proc/pon_phy/debug");
    t->socket()->waitForBytesWritten(20000);
}
