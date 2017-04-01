#include "dialog_db.h"
#include "ui_dialog_db.h"
#include "sql_db.h"

extern meas_entry_t *meas_entry_first;

Dialog_db::Dialog_db(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_db)
{
    ui->setupUi(this);
}

Dialog_db::~Dialog_db()
{
    delete ui;
}

void Dialog_db::on_buttonBox_accepted()
{
    if (creatDbHandle(ui->dbAddrLine->text(), ui->dbPortLine->text(),
                      ui->dbNameLine->text(), ui->dbUserNameLine->text(),
                      ui->dbPwLine->text()) == true)
        sendData("Connect is successful");
    else
        sendData("Connect is failed");
    if (updateValueByFilter("111", meas_entry_first) == true)
        sendData("Update is successful");
    else
        sendData("Update is failed, Database not open or Meas entry has not been selected");
}
