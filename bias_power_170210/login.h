#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);

    ~Login();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_2_cancel_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
