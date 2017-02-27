#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial_PCBA = new QSerialPort();
    ui->lineEdit_temp->setText("");
    ui->lineEdit_2_power->setText("");
    ui->lineEdit_3_bias_read->setText("");
    ui->lineEdit_4_bias_write->setText("");

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);

        ui->comboBox->addItem(info.portName());
    }
    serial_PCBA->setPortName(ui->comboBox->currentText());
    //serial_PCBA->setPortName("COM23");
    if (serial_PCBA->open(QIODevice::ReadWrite))
    {
        //设置串口
        serial_PCBA->setBaudRate(QSerialPort::Baud115200);
        serial_PCBA->setParity(QSerialPort::NoParity);
        serial_PCBA->setDataBits(QSerialPort::Data8);
        serial_PCBA->setStopBits(QSerialPort::OneStop);
        serial_PCBA->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() <<"open  serial_PCBA success";
    }
    else
    {
        qDebug() << "open  serial_PCBA failure";
    }
    ui->comboBox->setEnabled(true);
#if 1
    serial_PCBA->write("\n");
    //msec_sleep(500);
    serial_PCBA->waitForBytesWritten(500);
    serial_PCBA->write("admin");
    serial_PCBA->write("\n");
    serial_PCBA->waitForBytesWritten(500);
    //msec_sleep(500);
    serial_PCBA->write("1234");
    serial_PCBA->write("\n");
    serial_PCBA->waitForBytesWritten(500);
    msec_sleep(500);

#endif

    serial_PCBA->write("\n");
    msec_sleep(PROVER_SW_DELAY);
    serial_PCBA->write("sifm xw 0 0xc7 0xd1 1 0x7f 1 4");
    serial_PCBA->write("\n");
    msec_sleep(PROVER_SW_DELAY);
    QString data2 = serial_PCBA->readAll();
    qDebug() << data2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_temp_clicked()
{
    QString data;
    QSerialPort *serial_MTK = serial_PCBA;
    //QByteArray cmd_A2_wr("sifm xr 0 0xc7 0xd1 1 0xE5 1");

    serial_MTK->write("\n");
    serial_MTK->write("\n");
    serial_MTK->write("sifm xr 0 0xc7 0xd1 1 0xE5 1");
    serial_MTK->write("\n");
    msec_sleep(PROVER_SW_DELAY);

    data = serial_MTK->readAll();
    //qDebug() << data;
    target_string = data.mid(data.indexOf("000000e5") + 10, 4);
    qDebug() << target_string;
    ui->lineEdit_temp->setText(target_string);
}

void MainWindow::on_pushButton_2_power_clicked()
{

}

void MainWindow::on_pushButton_3_bias_read_clicked()
{
    QString data, target_data, target_data1, target_data2;
    bool ok;
    unsigned char index, index1, add0, add1, sum = 0;
    char bufadd0[4] = {0};
    char bufadd1[4] = {0};

    QSerialPort *serial_MTK = serial_PCBA;
    int temp_data = target_string.toInt(&ok,16);


    if (temp_data < 0x41){

        serial_MTK->write("sifm xr 0 0xc7 0xd1 1 0x80 0x02");
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;

        target_data = data.mid(data.indexOf("00000080") + 10, 9);
        qDebug() << target_data;
#if 0
        target_data1 = target_data.mid(0,4);
        qDebug() << target_data1;
        //qDebug() << target_data1.toInt(&ok,16);
        target_data2 = target_data.mid(5,4);
        qDebug() << target_data2;
#endif
        ui->lineEdit_3_bias_read->setText("[7:0-7:6]"+target_data);
    }else if (temp_data > 0xE7){

        serial_MTK->write("sifm xr 0 0xc7 0xd1 1 0xE7 0x02");
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;

        target_data = data.mid(data.indexOf("000000e7") + 10, 9);
        qDebug() << target_data;
        ui->lineEdit_3_bias_read->setText("[1:0-7:0]"+target_data);

    }else {
        //计算原始温度ADC的高8位对应的电流查找表DAC地址
        index = temp_data - 65;
        index1 = index >> 1;
        add0 = index1 + (index1 >> 2) + 0x80;
        sprintf(bufadd0,"%x",add0);
        add1 = add0 + 1;
        sprintf(bufadd1,"%x",add0 + 1);

        //读取相应的DAC地址中的数据
        QString cmd_A2_wr_str = QString("sifm xr 0 0xc7 0xd1 1 0x%1 0x02").arg(bufadd0);
        //qDebug() << cmd_A2_wr_str;
        QByteArray cmd_A2_wr = cmd_A2_wr_str.toLatin1();
        //qDebug() << cmd_A2_wr;
        serial_MTK->write(cmd_A2_wr);
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;

        target_data = data.mid(data.indexOf("000000") + 10, 9);
        qDebug() << target_data;

        //索引值index1的低两位与查找表对应的地址
        sum = (index1 << 6);
        sum = (sum >> 6);
        qDebug() << sum;
        switch (sum) {
        case 0:
            ui->lineEdit_3_bias_read->setText("[7:0-7:6]"+target_data);
            break;
        case 1:
            ui->lineEdit_3_bias_read->setText("[5:0-7:4]"+target_data);
            break;
        case 2:
            ui->lineEdit_3_bias_read->setText("[3:0-7:2]"+target_data);
            break;
        case 3:
            ui->lineEdit_3_bias_read->setText("[1:0-7:0]"+target_data);
            break;
        default:
            break;
        }
    }

}

void MainWindow::on_pushButton_4_bias_write_clicked()
{
    bool ok;
    unsigned char index, index1, add0, add1, sum = 0;
    char add0set[8], add1set[8];
    char bufadd0[8] = {0};
    char bufadd1[8] = {0};
    char *data_num = NULL;
    QSerialPort *serial_MTK = serial_PCBA;
    QString data;

    int temp_data = target_string.toInt(&ok,16);
    QString data_str = ui->lineEdit_4_bias_write->text();    
    QByteArray data_set = data_str.toLatin1();
    data_num = data_set.data();
    qDebug() << data_num;
    memcpy(add0set,data_num,4);
    bufadd0[4] = '\0';
    memcpy(add1set,data_num+5,4);
    bufadd1[4] = '\0';
    qDebug() << add0set;
    qDebug() << add1set;


    if (temp_data < 0x41){

        QString cmd_A2_wr_str = QString("sifm xw 0 0xc7 0xd1 1 0x80 2 %1 %2").arg(add0set).arg(add1set);
        //qDebug() << cmd_A2_wr_str;
        QByteArray cmd_A2_wr = cmd_A2_wr_str.toLatin1();
        //qDebug() << cmd_A2_wr;
        serial_MTK->write(cmd_A2_wr);
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;
    }else if (temp_data > 0xE7){

        QString cmd_A2_wr_str = QString("sifm xw 0 0xc7 0xd1 1 0xE7 2 %1 %2").arg(add0set).arg(add1set);
        //qDebug() << cmd_A2_wr_str;
        QByteArray cmd_A2_wr = cmd_A2_wr_str.toLatin1();
        //qDebug() << cmd_A2_wr;
        serial_MTK->write(cmd_A2_wr);
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;
    }else {
        //计算原始温度ADC的高8位对应的电流查找表DAC地址
        index = temp_data - 65;
        index1 = index >> 1;
        add0 = index1 + (index1 >> 2) + 0x80;
        sprintf(bufadd0,"%x",add0);
        add1 = add0 + 1;
        sprintf(bufadd1,"%x",add0 + 1);

        QString cmd_A2_wr_str = QString("sifm xw 0 0xc7 0xd1 1 0x%1 2 %2 %3").arg(bufadd0).arg(add0set).arg(add1set);
        //qDebug() << cmd_A2_wr_str;
        QByteArray cmd_A2_wr = cmd_A2_wr_str.toLatin1();
        //qDebug() << cmd_A2_wr;
        serial_MTK->write(cmd_A2_wr);
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        qDebug() << data;
    }

}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(serial_PCBA->isOpen())
        serial_PCBA->close();
    serial_PCBA->setPortName(ui->comboBox->currentText());

    if (serial_PCBA->open(QIODevice::ReadWrite))
    {
        serial_PCBA->setBaudRate(QSerialPort::Baud115200);
        serial_PCBA->setParity(QSerialPort::NoParity);
        serial_PCBA->setDataBits(QSerialPort::Data8);
        serial_PCBA->setStopBits(QSerialPort::OneStop);
        serial_PCBA->setFlowControl(QSerialPort::NoFlowControl);
        //qDebug() <<"open  serial_PCBA success";
    }
    else
    {
        qDebug() << "open  serial_PCBA failure";
    }
}

void MainWindow::msec_sleep(int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

void MainWindow::on_pushButton_translation_clicked()
{
    bool ok;
    unsigned char index, index1, add0, add1, sum = 0;
    char bufadd0[8] = {0};
    char bufadd1[8] = {0};
    QString data, target_data, target_data1, target_data2;
    char databuf1[4], databuf2[4], databufsum[8];
    QSerialPort *serial_MTK = serial_PCBA;
    unsigned int reserve, change, result;
    QString cmd_A2_wr_str, cmd_A2_wr_str0, cmd_A2_wr_str1, cmd_A2_wr_str2, cmd_A2_wr_str3;
    QByteArray cmd_A2_wr, cmd_A2_wr0, cmd_A2_wr1, cmd_A2_wr2, cmd_A2_wr3;

    QString dataAdd = ui->lineEdit_translation->text();
    int dataAddNum = dataAdd.toInt(&ok,16);
    int temp_data = 65;

    while (temp_data < 232){

        serial_MTK->write("\n");
        qDebug() << temp_data;

        index = temp_data - 65;
        index1 = index >> 1;
        add0 = index1 + (index1 >> 2) + 0x80;
        sprintf(bufadd0,"%x",add0);
        add1 = add0 + 1;
        sprintf(bufadd1,"%x",add0 + 1);
        msec_sleep(PROVER_SW_DELAY);

        cmd_A2_wr_str = QString("sifm xr 0 0xc7 0xd1 1 0x%1 2").arg(bufadd0);
        //qDebug() << cmd_A2_wr_str;
        cmd_A2_wr = cmd_A2_wr_str.toLatin1();
        qDebug() << cmd_A2_wr;
        serial_MTK->write(cmd_A2_wr);
        //serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        data = serial_MTK->readAll();
        serial_MTK->write("\n");
        msec_sleep(PROVER_SW_DELAY);
        qDebug() << data;

        target_data = data.mid(data.indexOf("000000") + 10, 9);
        qDebug() << target_data;
        target_data1 = target_data.mid(2,2);
        qDebug() << target_data1;
        target_data2 = target_data.mid(7,2);
        qDebug() << target_data2;
        QString target = QString(target_data1+target_data2);
        qDebug() << target;
        int targetnumber = target.toInt(&ok,16);

        memset(databuf1,0,4);
        memset(databuf2,0,4);
        memset(databufsum,0,8);

        sum = (index1 << 6);
        sum = (sum >> 6);
        qDebug() << sum;
        switch (sum) {
        case 0:
            //reserve = targetnumber & 0x003f;
            //change = (targetnumber >> 6) + dataAddNum;
            //result = (change << 6) || reserve;
            //qDebug() << result;

            reserve = targetnumber & 0x003f;
            change = targetnumber >> 6;
            change = change + dataAddNum;
            result = change << 6;
            result = result || reserve;

            sprintf(databufsum,"%x",result);
            qDebug() << databufsum;
            memcpy(databuf1,databufsum,2);
            databuf1[2] = '\0';
            memcpy(databuf2,databufsum+2,2);
            databuf2[2] = '\0';
            qDebug() << databuf1;
            qDebug() << databuf2;

            cmd_A2_wr_str0 = QString("sifm xw 0 0xc7 0xd1 1 0x%1 2 %2 %3").arg(bufadd0).arg(databuf1).arg(databuf2);
            qDebug() << cmd_A2_wr_str0;
            cmd_A2_wr0 = cmd_A2_wr_str0.toLatin1();
            //qDebug() << cmd_A2_wr;
            serial_MTK->write(cmd_A2_wr0);
            serial_MTK->write("\n");
            msec_sleep(PROVER_SW_DELAY);
            //data = serial_MTK->readAll();
            //qDebug() << data;
            break;
        case 1:
            reserve = targetnumber & 0x0f;
            change = (targetnumber >> 4) + dataAddNum;
            result = (change << 4) || reserve;
            //qDebug() << result;
            sprintf(databufsum,"%x",result);
            qDebug() << databufsum;
            memcpy(databuf1,databufsum,2);
            databuf1[2] = '\0';
            memcpy(databuf2,databufsum+2,2);
            databuf2[2] = '\0';
            qDebug() << databuf1;
            qDebug() << databuf2;

            cmd_A2_wr_str1 = QString("sifm xw 0 0xc7 0xd1 1 0x%1 2 %2 %3").arg(bufadd0).arg(databuf1).arg(databuf2);
            qDebug() << cmd_A2_wr_str1;
            cmd_A2_wr1 = cmd_A2_wr_str1.toLatin1();
            //qDebug() << cmd_A2_wr;
            serial_MTK->write(cmd_A2_wr1);
            serial_MTK->write("\n");
            msec_sleep(PROVER_SW_DELAY);
            //data = serial_MTK->readAll();
            //qDebug() << data;
            break;
        case 2:
            reserve = targetnumber & 0x03;
            change = (targetnumber >> 2) + dataAddNum;
            result = (change << 2) || reserve;
            //qDebug() << result;
            sprintf(databufsum,"%x",result);
            qDebug() << databufsum;
            memcpy(databuf1,databufsum,2);
            databuf1[2] = '\0';
            memcpy(databuf2,databufsum+2,2);
            databuf2[2] = '\0';
            qDebug() << databuf1;
            qDebug() << databuf2;

            cmd_A2_wr_str2 = QString("sifm xw 0 0xc7 0xd1 1 0x%1 2 %2 %3").arg(bufadd0).arg(databuf1).arg(databuf2);
            qDebug() << cmd_A2_wr_str2;
            cmd_A2_wr2 = cmd_A2_wr_str2.toLatin1();
            //qDebug() << cmd_A2_wr;
            serial_MTK->write(cmd_A2_wr2);
            serial_MTK->write("\n");
            msec_sleep(PROVER_SW_DELAY);
            //data = serial_MTK->readAll();
            //qDebug() << data;
            break;
        case 3:
            //reserve = targetnumber & 0x3f;
            //change = targetnumber + dataAddNum;
            result = targetnumber + dataAddNum;
            //qDebug() << result;
            sprintf(databufsum,"%x",result);
            qDebug() << databufsum;
            memcpy(databuf1,databufsum,2);
            databuf1[2] = '\0';
            memcpy(databuf2,databufsum+2,2);
            databuf2[2] = '\0';
            qDebug() << databuf1;
            qDebug() << databuf2;

            cmd_A2_wr_str3 = QString("sifm xw 0 0xc7 0xd1 1 0x%1 2 %2 %3").arg(bufadd0).arg(databuf1).arg(databuf2);
            qDebug() << cmd_A2_wr_str3;
            cmd_A2_wr3 = cmd_A2_wr_str3.toLatin1();
            //qDebug() << cmd_A2_wr;
            serial_MTK->write(cmd_A2_wr3);
            serial_MTK->write("\n");
            msec_sleep(PROVER_SW_DELAY);
            //data = serial_MTK->readAll();
            //qDebug() << data;
            break;
        default:
            qDebug() << "default quit";
            break;
        }

        temp_data = temp_data + 2;
    }
}
