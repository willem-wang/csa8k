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
    //void on_pushButton_connect_clicked();

    //void on_pushButton_disconnect_clicked();

    //void on_pushButton_send_clicked();

    //void on_pushButton_read_clicked();

    //void on_pushButton_sendRead_clicked();

    int validate_MAC(QString);

    void on_actionDatabase_D_triggered();

    void on_actionMeasurment_M_triggered();

    void receiveData(QString);

    void on_pushButton_configure_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_AutoTest_clicked();

    int testDataJudge();
	

    void on_doubleSpinBox_marginspercent_valueChanged(double arg1);

    void on_comboBox_signal_type_currentTextChanged(const QString &arg1);

    void on_pushButton_autoset_clicked();

    void on_pushButton_2_run_clicked();

    void on_pushButton_stop_clicked(QString);

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

    void on_comboBox_tabel_switch_currentTextChanged(const QString &arg1);

    void on_pushButton_disable_mod_clicked();

    void on_pushButton_2_read_origion_mod_clicked();

    void on_pushButton_3_set_mod_clicked();

    void disable_mod_set();

    void get_origion_mod();

    void ping_state_deal();
    void getONUMac();

    void on_pushButton_start_test_clicked();

	void calibrator82h(int );

    void on_pushButton_table_clicked();
	void getE5Index();
	void readTableIndex();
	void getTableIndex();
	

    void on_comboBox_onu_type_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Dialog_db *dialog_db;
    Dialog_Meas *dialog_meas;
    QSerialPort *serial_PCBA;
    QtTelnet *t;
    QString name;
    QString msgGlobal;
	QString E5Index;
	QString targetIndex;

signals:
    void sendSnInfo(QString);
    void telnetmessage();
    void savedata(QString);
    void calibrate_data();
    void totranslationdata();
    void towritedata();
    void toreaddata();
    void todisablemode();
    void toorigionmod();
    void to_reset_csa8k();
    void toPing();
    void tologin();
    void getMAC();
	void toautotest();
	void tocalibrator82h(int );
	void toE5Index();
	void toTableIndex();
	void togetTableIndex();
};

#endif // MAINWINDOW_H
