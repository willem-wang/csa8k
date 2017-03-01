#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_db.h"
#include "dialog_meas.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qttelnet.h"

typedef unsigned char BYTE ;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void msec_sleep(int msec);
    ~MainWindow();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_sendRead_clicked();

    void on_actionDatabase_D_triggered();

    void on_actionMeasurment_M_triggered();

    void receiveData(QString);

    void on_pushButton_configure_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_AutoTest_clicked();

	bool testDataJudge();
	

    void on_doubleSpinBox_marginspercent_valueChanged(double arg1);

    void on_comboBox_signal_type_currentTextChanged(const QString &arg1);

    void on_pushButton_autoset_clicked();

    void on_pushButton_2_run_clicked();

    void on_pushButton_stop_clicked();

    void on_lineEdit_saoma_returnPressed();

    int validate_MAC(QString mac);

    void getBoardSn(QString);

    int loginState();

    bool telnet_login();

    void telnetConnectionError(QAbstractSocket::SocketError error);

    void telnetLoggedIn();

    void telnetLoggedOut();

    void telnetLoginFailed();

    QString stripCR(const QString &msg);

    void switch2table(int);

    void read_calibrate_data();

    void deal_calibrate_data();

    void write_calibrate_data();

    void translation_data();

    void on_pushButton_bias_translate_clicked();

    void on_pushButton_write_flash_clicked();

private:
    Ui::MainWindow *ui;
    Dialog_db *dialog_db;
    Dialog_Meas *dialog_meas;
    QSerialPort *serial_PCBA;
    QtTelnet *t;
    QString name;
    QString msgGlobal;

signals:
    void sendSnInfo(QString);
    void telnetmessage();
	void savedata();
    void calibrate_data();
    void totranslationdata();
    void towritedata();
    void toreaddata();
};

#endif // MAINWINDOW_H
