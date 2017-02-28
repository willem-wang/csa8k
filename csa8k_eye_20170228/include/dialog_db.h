#ifndef DIALOG_DB_H
#define DIALOG_DB_H

#include <QDialog>

namespace Ui {
class Dialog_db;
}

class Dialog_db : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_db(QWidget *parent = 0);
    ~Dialog_db();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_db *ui;

signals:
    void sendData(QString);
};

#endif // DIALOG_DB_H
