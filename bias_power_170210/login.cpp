#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);
        ui->comboBox_com_select->addItem(info.portName());
    }
    //set_serial_port();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    if (ui->lineEdit_username->text().trimmed() == tr("admin") &&
            ui->lineEdit_2_password->text().trimmed() == tr("1234")){
        accept();

        this->ui->lineEdit_username->setEnabled(false);
        this->ui->lineEdit_2_password->setEnabled(false);
        this->ui->comboBox_com_select->setEnabled(false);
        this->ui->pushButton_login->setEnabled(false);
        this->ui->pushButton_2_cancel->setEnabled(false);

        //open_serial_port();
    }else{
        QMessageBox::warning(this,tr("错误"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->lineEdit_username->clear();
        this->ui->lineEdit_2_password->clear();
        this->ui->lineEdit_username->setFocus();
    }
}

void Login::on_pushButton_2_cancel_clicked()
{
    this->close();
}
