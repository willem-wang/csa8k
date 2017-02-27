#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QIODevice>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>

#define PROVER_SW_DELAY 300

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void msec_sleep(int msec);
    QString target_string;
    ~MainWindow();

private slots:
    void on_pushButton_temp_clicked();

    void on_pushButton_2_power_clicked();

    void on_pushButton_3_bias_read_clicked();

    void on_pushButton_4_bias_write_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_translation_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial_PCBA;
};

#endif // MAINWINDOW_H
