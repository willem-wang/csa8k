#ifndef LOGIN_TELNET_H
#define LOGIN_TELNET_H

#include <QDialog>
#include "qttelnet.h"
//#include "telnet_login.h"

namespace Ui {
class login_telnet;
}

class login_telnet : public QDialog
{
    Q_OBJECT

public:
    explicit login_telnet(QWidget *parent = 0);
    ~login_telnet();
QtTelnet *t;
private slots:
    void on_pushButton_connnect_clicked();

    void telnetConnectionError(QAbstractSocket::SocketError error);

    void telnetLoggedIn();

    void telnetLoggedOut();

    void telnetLoginFailed();

    void telnetMessage(const QString &msg);

    void on_pushButton_3_cancel_clicked();

    void on_pushButton_user_ok_clicked();

    void on_pushButton_2_pwd_ok_clicked();

    void on_pushButton_light_clicked();

private:
    Ui::login_telnet *ui;
//    QtTelnet *t;
    QString stripCR(const QString &msg);

};

#endif // LOGIN_TELNET_H
