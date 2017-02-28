#ifndef DIALOG_MEAS_H
#define DIALOG_MEAS_H

#include <QDialog>

namespace Ui {
class Dialog_Meas;
}

class Dialog_Meas : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Meas(QWidget *parent = 0);
    ~Dialog_Meas();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_Meas *ui;

signals:
    void sendData(QString);
};

#endif // DIALOG_MEAS_H
