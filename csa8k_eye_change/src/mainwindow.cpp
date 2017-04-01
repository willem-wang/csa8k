#include <stdio.h>
#include <QDebug>
#include "visa.h"
#include "visatype.h"
#include "mainwindow.h"
#include "csa8k_api.h"
#include "ui_mainwindow.h"
#include "option_parser.h"
#include "qttelnet.h"
#include <unistd.h>
#include <QFile>
#include <QTime>
#include <QMessageBox>
#include <QDir>

gpib_proc_t gpib_proc;
char idn[IDN_STR_MAX];
meas_entry_t *meas_entry_first = NULL;
meas_config_t meas_config;
int index_sum;
char rps_value[MEAS_MAX][RES_STR_MAX] = {0};
unsigned int countResult[4] = {0};
static char filename[64] = {0};

BYTE databuf[128];


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),t(new QtTelnet),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial_PCBA = new QSerialPort;
    dialog_meas = new Dialog_Meas(this);
    dialog_meas->setModal(false);

    dialog_db = new Dialog_db(this);
    dialog_db->setModal(false);

    //t = new QtTelnet;
    connect(t, SIGNAL(message(const QString &)),this, SLOT(stripCR(const QString &)));
    connect(t, SIGNAL(connectionError(QAbstractSocket::SocketError)),
            this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));
    connect(t, SIGNAL(loginFailed()),this, SLOT(telnetLoginFailed()));
    connect(t, SIGNAL(loggedOut()),this, SLOT(telnetLoggedOut()));
    connect(t, SIGNAL(loggedIn()),this, SLOT(telnetLoggedIn()));


    connect(dialog_meas, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    connect(dialog_db, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    connect(this,SIGNAL(sendSnInfo(QString)),this,SLOT(getBoardSn(QString)));
    connect(this,SIGNAL(telnetmessage()),this, SLOT(loginState()));
    connect(this,SIGNAL(calibrate_data()),this, SLOT(deal_calibrate_data()));
    connect(this,SIGNAL(savedata(QString)),this, SLOT(on_pushButton_stop_clicked(QString)));
    connect(this,SIGNAL(totranslationdata()),this, SLOT(translation_data()));
    connect(this,SIGNAL(towritedata()),this, SLOT(write_calibrate_data()));
    connect(this,SIGNAL(toreaddata()),this, SLOT(read_calibrate_data()));
    connect(this,SIGNAL(todisablemode()),this, SLOT(disable_mod_set()));
    connect(this,SIGNAL(toorigionmod()),this, SLOT(get_origion_mod()));
    connect(this,SIGNAL(to_reset_csa8k()),this, SLOT(on_pushButton_reset_clicked()));

    ui->pushButton_AutoTest->setDisabled(true);
    ui->pushButton_Connect->setEnabled(true);
    ui->comboBox_signal_type->setDisabled(true);
    ui->pushButton_2_read_origion_mod->setDisabled(true);
    ui->pushButton_3_set_mod->setDisabled(true);
    ui->pushButton_bias_translate->setDisabled(true);
    ui->lineEdit_2_read_origion_mod->setDisabled(true);

    ui->lineEdit_saoma->clear();
    ui->lineEdit_saoma->setEnabled(true);
    ui->lineEdit_saoma->setFocus();

}

MainWindow::~MainWindow()
{
    delete serial_PCBA;
    delete ui;
}

/**
 * Slot function to receive the signal "sendData" from
 * 1.   dialog_db.cpp
 * 2.   dialog_meas.cpp
 *
 */
void MainWindow::receiveData(QString data)
{
    ui->textBrowser->append(data);
}

/**
 * Show dialog window when trigger the menu bar button
 * 1.   database connection config dialog
 * 2.   measurement entry config dialog
 *
 */
/*1. database connection config dialog*/
void MainWindow::on_actionDatabase_D_triggered()
{
    dialog_db->show();
}
/*2. measurement entry config dialog*/
void MainWindow::on_actionMeasurment_M_triggered()
{
    dialog_meas->show();
}

/**
 * These buttons are used to send gpib cmd line immediatly
 * 1.   connect button
 * 2.   disconnect button
 * 3.   send button
 * 4.   read button
 * 5.   send and read button
 *
 */

#if 0
/*1. connect button*/
void MainWindow::on_pushButton_connect_clicked()
{
    int rts;

    rts = gpib_connect_initialize(0, 1, &gpib_proc, idn);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->setText("%Connect Success!");
    else
        ui->textBrowser_control->setText("%Connect Fail!");
    ui->textBrowser_control->append(QString(QLatin1String(idn)));
}
/*2. disconnect button*/
void MainWindow::on_pushButton_disconnect_clicked()
{
    int rts;

    rts = gpib_connect_close(&gpib_proc);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->setText("%Disconnect Success!");
    else
        ui->textBrowser_control->setText("%Disconnect Fail!");
}
/*3. send button*/
void MainWindow::on_pushButton_send_clicked()
{
    int rts;

    const char *cmd = qPrintable(ui->commandLine->text());
    if (ui->commandLine->text().isEmpty()) {
        ui->textBrowser_control->setText("%Command Is Empty!");
        return;
    }
    rts = send_cmd(&gpib_proc.vi, cmd);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->setText("%Send Command Success!");
    else
        ui->textBrowser_control->setText("%Send Command Fail!");
}
/*4. read button*/
void MainWindow::on_pushButton_read_clicked()
{

    int rts;
    char rps[RES_STR_MAX] = {0};

    rts = read_rps(&gpib_proc.vi, rps);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->setText("%Read Response Success!");
    else
        ui->textBrowser_control->setText("%Read Response Fail!");
    ui->textBrowser_control->append(rps);
}
/*5. send and read button*/
void MainWindow::on_pushButton_sendRead_clicked()
{
    int rts;
    char rps[RES_STR_MAX] = {0};
    const char *cmd = qPrintable(ui->commandLine->text());
    //send command
    if (ui->commandLine->text().isEmpty()) {
        ui->textBrowser_control->setText("%Command Is Empty!");
        return;
    }
    rts = send_cmd(&gpib_proc.vi, cmd);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->setText("%Send Command Success!");
    else
        ui->textBrowser_control->setText("%Send Command Fail!");
    //read response
    rts = read_rps(&gpib_proc.vi, rps);
    if (rts == CMD_SUCCESS)
        ui->textBrowser_control->append("%Read Response Success!");
    else
        ui->textBrowser_control->append("%Read Response Fail!");
    ui->textBrowser_control->append(rps);
}
#endif

/**
 * These buttons are used to auto configure and auto test through csa8k instrument
 * 1.   auto test button
 * 2.   connect button
 * 3.   reset button
 * 4.   auto configure button
 *
 */
/*1. auto test button*/
void MainWindow::on_pushButton_AutoTest_clicked()
{
    memset(rps_value,0,sizeof(rps_value));
    memset(countResult,0,sizeof(countResult));

    QDateTime startTime = QDateTime::currentDateTime();
    QString strStartTime = startTime.toString("yyyy-MM-dd hh:mm:ss ddd");

    //emit runautoset();
    on_pushButton_2_run_clicked();
    on_pushButton_autoset_clicked();
    usleep(100000);
    set_wfmdbx_display(&gpib_proc.vi, 1, ON);
    //测试时间
    int count = 10;
    while(count){
        ui->textBrowser->append(QString("autotest is running...%1seconds").arg(count));
        sleep(1);
        count--;
    }

    //读取meas_value的值
    int index_num = index_sum;
    while (!list_empty(&meas_entry_first->list)) {
        if(index_num == 0)
            break;
        //qDebug() << meas_entry_first->meas_index;
        //qDebug() << meas_entry_first->meas_type;
        //qDebug() << meas_entry_first->meas_value;

        QString cmd_str = QString("MEASUREMENT:MEAS%1:VALUE?").arg(meas_entry_first->meas_index);
        QByteArray cmd_bype = cmd_str.toLatin1();
        const char *cmd_meas = cmd_bype.data();
        send_cmd(&gpib_proc.vi, cmd_meas);
        char rps[RES_STR_MAX] = {0};
        read_rps(&gpib_proc.vi, rps);
        memcpy(rps_value[meas_entry_first->meas_index-1],rps,RES_STR_MAX);
        qDebug() << rps;
        //qDebug() << rps_value[meas_entry_first->meas_index];
        switch(meas_entry_first->meas_type){
        case EYE_WIDTH:
            ui->EYE_WIDTH_le->setText(rps);
            break;
        case EYE_HEIGHT:
            ui->EYE_HEIGHT_le->setText(rps);
            break;
        case EYE_HIGH:
            ui->EYE_HIGH_le->setText(rps);
            break;
        case EYE_LOW:
            ui->EYE_LOW_le->setText(rps);
            break;
        case EYE_AMPLITUDE:
            ui->EYE_AMPLITUDE_le->setText(rps);
            break;
        case EYE_PCROSS:
            ui->EYE_PCROSS_le->setText(rps);
            break;
        case EYE_NCROSS:
            ui->EYE_NCROSS_le->setText(rps);
            break;
        case EYE_EXTICTRATIO:
            ui->EYE_EXTICTRATIO_le->setText(rps);
            break;
        case EYE_QFACTOR:
            ui->EYE_QFACTOR_le->setText(rps);
            break;
        case EYE_AOPTPWRDBM:
            ui->EYE_AOPTPWRDBM_le->setText(rps);
            break;
        case EYE_RMSJITTER:
            ui->EYE_RMSJITTER_le->setText(rps);
            break;
        case EYE_PKPKJITTER:
            ui->EYE_PKPKJITTER_le->setText(rps);
            break;
        case EYE_EXTINCTDB:
            ui->EYE_EXTINCTDB_le->setText(rps);
            break;
        case EYE_PCTCROSS:
            ui->EYE_PCTCROSS_le->setText(rps);
            break;
        default:
            break;
        }

        meas_entry_first = list_entry(meas_entry_first->list.next, meas_entry_t, list);
        qDebug() << "******************************";
        usleep(100000);
        index_num--;
    }


    //mask readout界面显示实现
    //unsigned int countResult = 0;

    if (get_mask_chx_count(&gpib_proc.vi, &meas_config, 1, &countResult[0]) == CMD_SUCCESS){
        ui->lineEdit_mask1->setText(QString::number(countResult[0],10));
    }
    else
        ui->textBrowser->append("mask1:count read fialed");

    if (get_mask_chx_count(&gpib_proc.vi, &meas_config, 2, &countResult[1]) == CMD_SUCCESS){
        ui->lineEdit_2_mask2->setText(QString::number(countResult[1],10));
    }
    else
        ui->textBrowser->append("mask2:count read fialed");

    if (get_mask_chx_count(&gpib_proc.vi, &meas_config, 3, &countResult[2]) == CMD_SUCCESS){
        ui->lineEdit_3_mask3->setText(QString::number(countResult[2],10));
    }
    else
        ui->textBrowser->append("mask3:count read fialed");

    if (get_mask_total_count(&gpib_proc.vi, &meas_config, &countResult[3]) == CMD_SUCCESS){
        ui->lineEdit_4_mask_total->setText(QString::number(countResult[3],10));
    }
    else
        ui->textBrowser->append("mask:total:count read fialed");

    usleep(10000);
    //on_pushButton_stop_clicked();

    emit savedata(strStartTime);
}

/*2. connnect button*/
void MainWindow::on_pushButton_Connect_clicked()
{
    int rts;

    rts = gpib_connect_initialize(0, 1, &gpib_proc, idn);
    if (rts == CMD_SUCCESS)
        ui->textBrowser->setText("%Connect Success!");
    else
        ui->textBrowser->setText("%Connect Fail!");
    ui->textBrowser->append(QString(QLatin1String(idn)));

    emit to_reset_csa8k();
}
/*3. reset button*/
void MainWindow::on_pushButton_reset_clicked()
{
    int rts;

    rts = reset_factory(&gpib_proc.vi);
    if (rts == CMD_SUCCESS)
        ui->textBrowser->setText("%Reset Success!");
    else
        ui->textBrowser->setText("%Reset Fail!");

    sleep(3);
    on_pushButton_configure_clicked();
}

/**
 * The configure button is used to set the CONFIG(test environment) of csa8k instrument
 *  and initialize the meas_entry list to record the test value
 * 1.   eye_width
 * 2.   eye_height
 * 3.   eye_high
 * 4.   eye_low
 * 5.   eye_amplitude
 * 6.   eye_pcross
 * 7.   eye_ncross
 * 8.   eye_extinctratio
 * 9.   eye_qfactor
 * 10.  eye_aoptpwrdbm
 * 11.  vert config
 * 12.  mask config
 * 13.  acq config
 * 14.  trig config
 *
 */
void MainWindow::on_pushButton_configure_clicked()
{
    ui->textBrowser->setText("%**************************************************%");

    /*15. meas donfig*/
    //QString meassel = ui->comboBox_2_meas_select->currentText();
    QString meassrc = ui->comboBox_signal_type->currentText();
    //char *measselect = measSignalParser(meassel);
    char *meassource = measSourceType(meassrc);

    /*config meas source type*/
    ui->textBrowser->append(QString("Meas: Meas source type is %1").arg(meassrc));
    if (set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, 1, 1, meassource) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Meas: Meas source type %1 has been synchronized to instrument").arg(meassrc));
    else
        ui->textBrowser->append(QString("Meas: Meas source type %1 can't be synchronized to instrument").arg(meassrc));
#if 0
    /*config meas type*/
    set_measurement_readout(&gpib_proc.vi, ON);
    ui->textBrowser->append(QString("Meas: Meas type is %1").arg(meassel));
    if (set_measurement_select_meas(&gpib_proc.vi, &meas_config, 1, measselect) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Meas: Meas type %1 has been synchronized to instrument").arg(meassel));
    else
        ui->textBrowser->append(QString("Meas: Meas type %1 can't be synchronized to instrument").arg(meassel));
#endif
    /*Delete existing measurement entry when reselected*/
    if (meas_entry_first != NULL) {
        while (!list_empty(&meas_entry_first->list)) {
            list_head_t *tmp = meas_entry_first->list.next;
            list_del(meas_entry_first->list.next);
            free(list_entry(tmp, meas_entry_t, list));
        }
        free(meas_entry_first);
        meas_entry_first = NULL;
    }
    /*Initialize the measurement entry when this type of meaurement is selected*/
    char res_str[RES_STR_MAX * MEAS_MAX] = {0};
    int str_len = 0;
    meas_entry_t *meas = NULL;
    int index = 0;
    char 	cmd_str[CMD_STR_MAX] = {0};
    /*1. eye_width*/
    if (ui->EYE_WIDTH_chb->isChecked()) {
        meas_entry_t *meas_eye_width = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_width,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_width, index, EYE_WIDTH);
        meas = meas_eye_width;
        str_len = snprintf(res_str, RES_STR_MAX, "Meas: index=%d; type=eyewidth\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type eyewidth",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*2. eye_height*/
    if (ui->EYE_HEIGHT_chb->isChecked()) {
        meas_entry_t *meas_eye_height = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_height,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_height, index, EYE_HEIGHT);
        if (meas != NULL)
            list_add(&meas_eye_height->list, &meas->list);
        meas = meas_eye_height;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=eyeheight\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type eyeheight",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*3. eye_high*/
    if (ui->EYE_HIGH_chb->isChecked()) {
        meas_entry_t *meas_eye_high = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_high,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_high, index, EYE_HIGH);
        if (meas != NULL)
            list_add(&meas_eye_high->list, &meas->list);
        meas = meas_eye_high;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=high\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type high",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*4. eye_low*/
    if (ui->EYE_LOW_chb->isChecked()) {
        meas_entry_t *meas_eye_low = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_low,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_low, index, EYE_LOW);
        if (meas != NULL)
            list_add(&meas_eye_low->list, &meas->list);
        meas = meas_eye_low;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=low\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type low",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*5. eye_amplitude*/
    if (ui->EYE_AMPLITUDE_chb->isChecked()) {
        meas_entry_t *meas_eye_amplitude = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_amplitude,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_amplitude, index, EYE_AMPLITUDE);
        if (meas != NULL)
            list_add(&meas_eye_amplitude->list, &meas->list);
        meas = meas_eye_amplitude;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; ype=amplitude\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type amplitude",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*6. eye_pcross*/
    if (ui->EYE_PCROSS_chb->isChecked()) {
        meas_entry_t *meas_eye_pcross = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_pcross,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_pcross, index, EYE_PCROSS);
        if (meas != NULL)
            list_add(&meas_eye_pcross->list, &meas->list);
        meas = meas_eye_pcross;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=pcross\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type pcross",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*7. eye_ncross*/
    if (ui->EYE_NCROSS_chb->isChecked()) {
        meas_entry_t *meas_eye_ncross = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_ncross,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_ncross, index, EYE_NCROSS);
        if (meas != NULL)
            list_add(&meas_eye_ncross->list, &meas->list);
        meas = meas_eye_ncross;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=ncross\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type ncross",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*8. eye_extictratio*/
    if (ui->EYE_EXTICTRATIO_chb->isChecked()) {
        meas_entry_t *meas_eye_extictratio = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_extictratio,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_extictratio, index, EYE_EXTICTRATIO);
        if (meas != NULL)
            list_add(&meas_eye_extictratio->list, &meas->list);
        meas = meas_eye_extictratio;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=extinctratio\n", index);

        set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
        sprintf(cmd_str,"measurement:meas%d:type extinctratio",index);
        send_cmd(&gpib_proc.vi, cmd_str);
    }
    /*9. eye_qfactor*/
    if (ui->EYE_QFACTOR_chb->isChecked()) {
        meas_entry_t *meas_eye_qfactor = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_qfactor,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_qfactor, index, EYE_QFACTOR);
            if (meas != NULL)
                list_add(&meas_eye_qfactor->list, &meas->list);
            meas = meas_eye_qfactor;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=qfactor\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type qfactor",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }
    /*10. eye_aoptpwrdbm*/
    if (ui->EYE_AOPTPWRDBM_chb->isChecked()) {
        meas_entry_t *meas_eye_aoptpwrdbm = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_aoptpwrdbm,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_aoptpwrdbm, index, EYE_AOPTPWRDBM);
            if (meas != NULL)
                list_add(&meas_eye_aoptpwrdbm->list, &meas->list);
            meas = meas_eye_aoptpwrdbm;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=aoptpwrdbm\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type aoptpwrdbm",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }
    /*11. eye_RMSJitter*/
    if (ui->EYE_RMSJITTER_chb->isChecked()){
        meas_entry_t *meas_eye_rmsjitter = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_rmsjitter,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_rmsjitter, index, EYE_RMSJITTER);
            if (meas != NULL)
                list_add(&meas_eye_rmsjitter->list, &meas->list);
            meas = meas_eye_rmsjitter;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=RMSJitter\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type RMSJitter",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }
    /*12. eye_PKPKJitter*/
    if (ui->EYE_PKPKJITTER_chb->isChecked()){
        meas_entry_t *meas_eye_pkpkjitter = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_pkpkjitter,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_pkpkjitter, index, EYE_PKPKJITTER);
            if (meas != NULL)
                list_add(&meas_eye_pkpkjitter->list, &meas->list);
            meas = meas_eye_pkpkjitter;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=PKPKJitter\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type PKPKJitter",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }

    /*13. eye_extinctdb*/
    if (ui->EYE_EXTINCTDB_chb->isChecked()){
        meas_entry_t *meas_eye_extinctdb = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_extinctdb,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_extinctdb, index, EYE_EXTINCTDB);
            if (meas != NULL)
                list_add(&meas_eye_extinctdb->list, &meas->list);
            meas = meas_eye_extinctdb;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=EXTINCTDB\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type EXTINCTDB",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }

    /*14. eye_pctcross*/
    if (ui->EYE_PCTCROSS_chb->isChecked()){
        meas_entry_t *meas_eye_pctcross = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_pctcross,0,sizeof(meas_entry_t));
        if (index < 8){
            index++;
            meas_entry_init(meas_eye_pctcross, index, EYE_PCTCROSS);
            if (meas != NULL)
                list_add(&meas_eye_pctcross->list, &meas->list);
            meas = meas_eye_pctcross;
            str_len += snprintf(res_str + str_len, RES_STR_MAX, "Meas: index=%d; type=PCTCROSS\n", index);

            set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, index, 1, meassource);
            sprintf(cmd_str,"measurement:meas%d:type PCTCROSS",index);
            send_cmd(&gpib_proc.vi, cmd_str);
        }
    }

    /*Show the result of measurement entry select*/
    if (meas != NULL) {
        meas_entry_first = list_entry(meas->list.next, meas_entry_t, list);    //the "next pointer" of last measurement entry (meas) list head always point to first entry
        ui->textBrowser->append(QString(QLatin1String(res_str)));
    } else {
        ui->textBrowser->append("%Meas: No measurement entry has been selected!");
    }
    //最大只能测量8项数据
    if (index > 8)
        index_sum = 8;
    else
        index_sum = index;

    /*11. vert config*/
    int selCh = ui->comboBox_selCh->currentIndex() + 1;
    QString wl = ui->comboBox_wl->currentText();
    QString cf = ui->comboBox_filter->currentText();
    char *filter = chxFilterParser(cf);
    meas_config.meas_config_vert.sel_chx_state[CHANNEL_MAX] = {OFF};
    if (ui->checkBox_state->isChecked()) {
        /*configure vert channel state*/
        meas_config.meas_config_vert.sel_chx_state[selCh - 1] = ON;
        ui->textBrowser->append(QString("Vert: Channel%1 state is enable").arg(selCh));
        if (set_select_chx(&gpib_proc.vi, &meas_config, selCh) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Vert: Channel%1 state has been synchronized to instrument").arg(selCh));
        else
            ui->textBrowser->append(QString("Vert: Channel%1 state can't be synchronized to instrument").arg(selCh));
        /*configure vert channel wave length*/
        meas_config.meas_config_vert.chx_wlength[selCh - 1] = wl.toInt();
        ui->textBrowser->append(QString("Vert: Channel%1 wlength is %2").arg(selCh).arg(wl));
        if (set_chx_wlength_value(&gpib_proc.vi, &meas_config, selCh, wl.toInt()) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Vert: Channel%1 wlength has been synchronized to instrument").arg(selCh));
        else
            ui->textBrowser->append(QString("Vert: Channel%1 wlength can't be synchronized to instrument").arg(selCh));
        /*configure vert channel filter*/
        snprintf(meas_config.meas_config_vert.chx_filter[selCh - 1], SHT_STR_MAX, cf.toStdString().c_str());
        ui->textBrowser->append(QString("Vert: Channel%1 filter is %2").arg(selCh).arg(cf));
        if (set_chx_filter_value(&gpib_proc.vi, &meas_config, selCh, filter) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Vert: Channel%1 filter has been synchronized to instrument").arg(selCh));
        else
            ui->textBrowser->append(QString("Vert: Channel%1 filter can't be synchronized to instrument").arg(selCh));
    } else {
        ui->textBrowser->append("%Vert: No channel has been selected!");

    }

    /*12. mask config*/
    QString msrc = ui->comboBox_src->currentText();
    QString mstd = ui->comboBox_maskStd->currentText();
    char *maskSource = maskSourceParser(msrc);
    char *maskStandard = maskStandardParser(mstd);

    /*configure mask source*/
    snprintf(meas_config.meas_config_mask.mask_source, SHT_STR_MAX, msrc.toStdString().c_str());
    ui->textBrowser->append(QString("Mask: Mask source %1 has been selected").arg(msrc));
    if (set_mask_source(&gpib_proc.vi, &meas_config, maskSource) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Mask: Mask source %1 has been synchronized to instrument").arg(msrc));
    else
        ui->textBrowser->append(QString("Mask: Mask source %1 can't be synchronized to instrument").arg(msrc));
    /*configure mask count state*/
    if (ui->checkBox_enable->isChecked()) {
        meas_config.meas_config_mask.mask_count_state = ON;
        ui->textBrowser->append(QString("Mask: Mask count state is enable"));
        if (set_mask_count_state(&gpib_proc.vi, &meas_config, ON) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Mask: Mask count state ON has been synchronized to instrument"));
        else
            ui->textBrowser->append(QString("Mask: Mask count state ON can't be synchronized to instrument"));
    } else {
        meas_config.meas_config_mask.mask_count_state = OFF;
        ui->textBrowser->append(QString("Mask: Mask count state is disable"));
        if (set_mask_count_state(&gpib_proc.vi, &meas_config, OFF) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Mask: Mask count state OFF has been synchronized to instrument"));
        else
            ui->textBrowser->append(QString("Mask: Mask count state OFF can't be synchronized to instrument"));
    }
    /*configure mask standard*/
    snprintf(meas_config.meas_config_mask.mask_standard, SHT_STR_MAX, mstd.toStdString().c_str());
    ui->textBrowser->append(QString("Mask: Mask standard is %1").arg(mstd));
    if (set_mask_standard(&gpib_proc.vi, &meas_config, maskStandard) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Mask: Mask standard %1 has been synchronized to instrument").arg(mstd));
    else
        ui->textBrowser->append(QString("Mask: Mask standard %1 can't be synchronized to instrument").arg(mstd));
    /*configure mask margin state*/
    if (ui->checkBox_maskmargins_enable->isChecked()){
        meas_config.meas_config_mask.mask_margins_state = ON;
        meas_config.meas_config_mask.mask_margins_percent = ui->doubleSpinBox_marginspercent->value();
        ui->textBrowser->append(QString("Mask: Mask margins state is enable"));
        if (set_mask_margins_state(&gpib_proc.vi, &meas_config, ON) == CMD_SUCCESS){
            ui->textBrowser->append(QString("Mask: Mask margins state ON has been synchronized to instrument"));
            if (set_mask_margins_percent(&gpib_proc.vi, &meas_config, ui->doubleSpinBox_marginspercent->value()) == CMD_SUCCESS)
                ui->textBrowser->append(QString("Mask: Mask margins percent has been synchronized to instrument"));
            else
                ui->textBrowser->append(QString("Mask: Mask margins percent can't be synchronized to instrument"));
        }else
            ui->textBrowser->append(QString("Mask: Mask margins state ON can't be synchronized to instrument"));
    }else {
        meas_config.meas_config_mask.mask_margins_state = OFF;
        ui->textBrowser->append(QString("Mask: Mask margins state is disable"));
        if (set_mask_margins_state(&gpib_proc.vi, &meas_config, OFF) == CMD_SUCCESS){
            ui->textBrowser->append(QString("Mask: Mask margins state OFF has been synchronized to instrument"));
        }else
            ui->textBrowser->append(QString("Mask: Mask margins state OFF can't be synchronized to instrument"));
    }
    /*configure mask margin percent*/

    /*13. acq config*/
    QString asmd = ui->comboBox_mode->currentText();
    QString ascd = ui->comboBox_cond->currentText();
    QString ascnt = ui->lineEdit_count->text();
    char *acqSaMode = acqSaModeParser(asmd);
    char *acqSaCon = acqSaConParser(ascd);

    /*configure acq stop after mode*/
    snprintf(meas_config.meas_config_acq.acq_sa_mode, SHT_STR_MAX, asmd.toStdString().c_str());
    ui->textBrowser->append(QString("Acq: Stop after mode is %1").arg(asmd));
    if (set_acq_stopafter_mode(&gpib_proc.vi, &meas_config, acqSaMode) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Acq: Stop after mode %1 has been synchronized to instrument").arg(asmd));
    else
        ui->textBrowser->append(QString("Acq: Stop after mode %1 can't be synchronized to instrument").arg(asmd));
    /*configure acq stop after condition*/
    snprintf(meas_config.meas_config_acq.acq_sa_condition, SHT_STR_MAX, ascd.toStdString().c_str());
    ui->textBrowser->append(QString("Acq: Stop after condition is %1").arg(ascd));
    if (set_acq_stopafter_condition(&gpib_proc.vi, &meas_config, acqSaCon) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Acq: Stop after condition %1 has been synchronized to instrument").arg(ascd));
    else
        ui->textBrowser->append(QString("Acq: Stop after condition %1 can't be synchronized to instrument").arg(ascd));
    /*configure acq stop after count*/
    if (ascnt.isEmpty()) {
        ui->textBrowser->append(QString("%Acq: Stop after count is empty!"));
    } else {
        meas_config.meas_config_acq.acq_sa_count = ascnt.toInt();
        ui->textBrowser->append(QString("Acq: Stop after count is %1").arg(ascnt));
        if (set_acq_stopafter_count(&gpib_proc.vi, &meas_config, ascnt.toInt()) == CMD_SUCCESS)
            ui->textBrowser->append(QString("Acq: Stop after count %1 has been synchronized to instrument").arg(ascnt));
        else
            ui->textBrowser->append(QString("Acq: Stop after count %1 can't be synchronized to instrument").arg(ascnt));
    }

    /*14. trig config*/
    int trigCh =ui->comboBox_trigSrc->currentIndex() + 1;
    QString tsrc = ui->comboBox_trigSrc->currentText();
    QString tclksrc = ui->comboBox_clkrecSrc->currentText();
    QString tclkval = ui->comboBox_clkrecVal->currentText();
    char *trigSrc = trigSrcParser(tsrc);
    char *trigClkSrc = trigClkSrcParser(tclksrc);
    char *trigClkVal = trigClkValParser(tclkval);

    /*configure trigger source*/
    snprintf(meas_config.meas_config_trig.trig_src, SHT_STR_MAX, tsrc.toStdString().c_str());
    ui->textBrowser->append(QString("Trig: Trigger source is %1").arg(tsrc));
    if (set_trig_source(&gpib_proc.vi, &meas_config, trigSrc) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Trig: Trigger source %1 has been synchronized to instrument").arg(tsrc));
    else
        ui->textBrowser->append(QString("Trig: Trigger source %1 can't be synchronized to instrument").arg(tsrc));
    /*configure trigger clock recover source*/
    snprintf(meas_config.meas_config_trig.trig_clkrec_src, SHT_STR_MAX, tclksrc.toStdString().c_str());
    ui->textBrowser->append(QString("Trig: Clock recover source is %1").arg(tclksrc));
    if (set_trig_clkrec_source(&gpib_proc.vi, &meas_config, trigClkSrc) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Trig: Clock recover source %1 has been synchronized to instrument").arg(tclksrc));
    else
        ui->textBrowser->append(QString("Trig: Clock recover source %1 can't be synchronized to instrument").arg(tclksrc));
    /*configure trigger clock recover value*/
    snprintf(meas_config.meas_config_trig.trig_chx_clkrec_value[trigCh - 1], SHT_STR_MAX, tclkval.toStdString().c_str());
    ui->textBrowser->append(QString("Trig: Clock recover source channel %1 value is %2").arg(trigCh).arg(tclkval));
    if (set_trig_chx_clkrec_value(&gpib_proc.vi, &meas_config, trigCh, trigClkVal) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Trig: Clock recover source channel %1 value %2 has been synchronized to instrument").arg(trigCh).arg(tclkval));
    else
        ui->textBrowser->append(QString("Trig: Clock recover source channel %1 value %2 can't be synchronized to instrument").arg(trigCh).arg(tclkval));

    /*设置好之后点mask中的autoset*/
    sleep(2);
    //emit runautoset();
}

void MainWindow::on_doubleSpinBox_marginspercent_valueChanged(double percent_value)
{
    //qDebug() << "marginspercent_valueChanged" << percent_value;
    if (set_mask_margins_percent(&gpib_proc.vi, &meas_config, percent_value) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Mask margins percent has been synchronized to instrument"));
    else
        ui->textBrowser->append(QString("Mask margins percent can't be synchronized to instrument"));

}

void MainWindow::on_comboBox_signal_type_currentTextChanged(const QString &arg1)
{
    QString meassrc = ui->comboBox_signal_type->currentText();
    char *meassource = measSourceType(meassrc);

    if (set_measurement_measx_sourcetype(&gpib_proc.vi, &meas_config, 1, 1, meassource) == CMD_SUCCESS)
        ui->textBrowser->append(QString("Meas: Meas source type %1 has been synchronized to instrument").arg(meassrc));
    else
        ui->textBrowser->append(QString("Meas: Meas source type %1 can't be synchronized to instrument").arg(meassrc));
}

void MainWindow::on_pushButton_autoset_clicked()
{
    set_mask_autoset(&gpib_proc.vi, &meas_config);
    sleep(4);
    ui->textBrowser->append(QString("Autoset finish..."));
    //set_measurement_readout(&gpib_proc.vi, ON);
}

void MainWindow::on_pushButton_2_run_clicked()
{
    set_acq_state_runstop(&gpib_proc.vi, &meas_config, ON);
}

void MainWindow::on_pushButton_stop_clicked(QString strStartTime)
{
    set_acq_state_runstop(&gpib_proc.vi, &meas_config, OFF);
    QDateTime endTime = QDateTime::currentDateTime();
    QString strEndTime = endTime.toString("yyyy-MM-dd hh:mm:ss ddd");
	//qDebug() << "strEndTime" << strEndTime;

    QDir *temp = new QDir;
    bool exist = temp->exists("./testResult");
    if(exist){
        qDebug() << "testResult 文件夹已经存在！";
        //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
    }
    else
    {
        bool ok = temp->mkdir("./testResult");
        if( ok )
            qDebug() << "testResult 文件夹创建成功！";
    }

    memset(filename,0,sizeof(filename));
    QByteArray namedata = name.toLatin1();
    char *ptr = namedata.data();
    sprintf(filename,"./testResult/%s.txt",ptr);
    //qDebug() << "stop_clicked" << filename;

    usleep(100000);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){		//以只写方式，文本格式打开
        qDebug() << "open file failed";
        return ;
    }

    QPalette pa;
    bool resultjudge = 0;
    int sum = 0;
    int i = index_sum;
    QTextStream out(&file);
    out << "Start: " << strStartTime << "\r\n";
    out << "MEASUREMENT: " << "\n";
    while(i){
        switch(meas_entry_first->meas_type){
        case EYE_WIDTH:
            out << "EYE_WIDTH: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_HEIGHT:
            out << "EYE_HEIGHT: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_HIGH:
            out << "EYE_HIGH: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_LOW:
            out << "EYE_LOW: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_AMPLITUDE:
            out << "EYE_AMPLITUDE: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_PCROSS:
            out << "EYE_PCROSS: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_NCROSS:
            out << "EYE_NCROSS: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_EXTICTRATIO:
            out << "EYE_EXTICTRATIO: " <<rps_value[meas_entry_first->meas_index-1] <<"\n";
            break;
        case EYE_QFACTOR:
            out << "EYE_QFACTOR: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_AOPTPWRDBM:
            out << "EYE_AOPTPWRDBM: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_RMSJITTER:
            out << "EYE_RMSJITTER: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_PKPKJITTER:
            out << "EYE_PKPKJITTER: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_EXTINCTDB:
            out << "EYE_EXTINCTDB: " <<rps_value[meas_entry_first->meas_index-1] << "\n";
            break;
        case EYE_PCTCROSS:
            out << "EYE_PCTCROSS: " <<rps_value[meas_entry_first->meas_index-1] <<"\n";
            break;
        default:
            break;
        }
        meas_entry_first = list_entry(meas_entry_first->list.next, meas_entry_t, list);
        i--;
    }

    out << "\n" << "MASK: " << "\n";
    out << "MASK1: " << countResult[0] << "\n";
    out << "MASK2: " << countResult[1] << "\n";
    out << "MASK3: " << countResult[2] << "\n";
    out << "MASK total: " << countResult[3] << "\n";

    resultjudge = testDataJudge();
    //qDebug() << "resultjudge" << resultjudge;
    if(resultjudge == 1){
        out << "\n" << "TEST RESULT: " << "PASS" << "\n";
        ui->label_2_judge_state->setText("pass");
        ui->label_2_judge_state->setFont(QFont("Arial",36,QFont::Bold));
        pa.setColor(QPalette::WindowText,Qt::green);
        ui->label_2_judge_state->setPalette(pa);
    }else {
        out << "\n" << "TEST RESULT: " << "FAIL" << "\n";
        ui->label_2_judge_state->setText("fail");
        ui->label_2_judge_state->setFont(QFont("Arial",36,QFont::Bold));
        pa.setColor(QPalette::WindowText,Qt::red);
        ui->label_2_judge_state->setPalette(pa);
    }

    out << "\n" << "PASS STANDARD: " << "\n";
    out << "PCTCROSS: 45% ~ 55%" << "\n";
    out << "RMSJitter * 14 + PKPKJitter < 260" << "\n";
    //out << "EXTICTRATIO: 14 dB >= EPON(MAX) >= 11dB ; 12.5 dB >= EPON(SEM) >= 10.5dB ; 14.5 dB >= GPON  >= 11.5dB ;" << "\n";
    out << "EXTICTRATIO: 17.8dB >= GPON  >= 11.2dB" << "\n";
    out << "MASK1=0,MASK2=0,MASK3=0 " << "\n";
    out << "End: " << strEndTime << "\r\n";

    usleep(100000);
    file.close();

    ui->lineEdit_saoma->clear();
    ui->lineEdit_saoma->setEnabled(true);
    ui->lineEdit_saoma->setFocus();
    ui->pushButton_AutoTest->setDisabled(true);
    ui->pushButton_Connect->setDisabled(true);

    t->socket()->close(); //该行关闭Telnet，点击stop后还想通过Telnet操作，应注释该行。
}

void MainWindow::on_lineEdit_saoma_returnPressed()
{
    QString SN= ui->lineEdit_saoma->text();
    qDebug()<<"SN = "<< SN;

    if(validate_MAC(SN))
    {
        ui->lineEdit_saoma->clear();
        return;
    }

    emit sendSnInfo(SN);
}

int MainWindow::validate_MAC(QString mac)
{
    QRegExp mac_exp("([0-9A-F]{2}[0-9A-F]{2}[0-9A-F]{2}[0-9A-F]{2}[0-9A-F]{2}[0-9A-F]{2})");//MAC鍦板潃鐨勬鍒欒〃杈惧紡
    QRegExpValidator *mac_validator = new QRegExpValidator(mac_exp);
    if(!mac_validator->regExp().exactMatch(mac))
        return 1;
    return 0;
}

void MainWindow::getBoardSn(QString Sn)
{
    char *str = NULL;
    bool state = false;

    name = Sn;

    state = telnet_login();
    if (state == 0){
        ui->label_2_jitter_state->clear();
        ui->label_2_extinctratio->clear();
        ui->label_4_pkpkjitter->clear();
        ui->label_3_rmsjitter->clear();
        ui->label_6_pctcross->clear();
        ui->label_2_mask1_state->clear();
        ui->label_3_mask2_state->clear();
        ui->label_4_mask3_state->clear();
        ui->label_2_judge_state->clear();

        ui->EYE_PCTCROSS_le->clear();
        ui->EYE_PKPKJITTER_le->clear();
        ui->EYE_EXTINCTDB_le->clear();
        ui->EYE_RMSJITTER_le->clear();
        ui->EYE_AOPTPWRDBM_le->clear();
        ui->EYE_QFACTOR_le->clear();
        ui->EYE_EXTICTRATIO_le->clear();
        ui->EYE_NCROSS_le->clear();
        ui->EYE_PCROSS_le->clear();
        ui->EYE_AMPLITUDE_le->clear();
        ui->EYE_HIGH_le->clear();
        ui->EYE_LOW_le->clear();
        ui->EYE_HEIGHT_le->clear();
        ui->EYE_WIDTH_le->clear();

        ui->pushButton_AutoTest->setEnabled(true);
        //ui->pushButton_Connect->setEnabled(true);
        ui->lineEdit_saoma->setDisabled(true);
        ui->pushButton_write_flash->setDisabled(true);
    }else {
        ui->lineEdit_saoma->clear();
        ui->lineEdit_saoma->setEnabled(true);
        ui->lineEdit_saoma->setFocus();
    }
}

int MainWindow::loginState()
{
    //QByteArray data = "";
    QString login = "tc login: ";
    QString pwd = "Password:";
    QString success = "#";

    //qDebug() << "loginState"<< msgGlobal;
    if (NULL == t){
        return 0;
    }

    if(msgGlobal.indexOf(success) >= 0)
    {
        qDebug()<< "alreay login->" << msgGlobal;
        return 0;
    }

    if (msgGlobal.indexOf(login) >= 0){
        t->sendData("admin");
        t->socket()->waitForBytesWritten(3000);
    }

    if (msgGlobal.indexOf(pwd,5) >= 0){
        t->sendData("1234");
        t->socket()->waitForBytesWritten(3000);
        t->sendData("echo GPON_pattern > /proc/pon_phy/debug");
		t->socket()->waitForBytesWritten(3000);
    }
}


bool MainWindow::telnet_login()
{
    int i = 1;
    //t->connectToHost("192.168.1.1");
    while (i){
        t->connectToHost("192.168.1.1");
        if (t->socket()->waitForConnected(3000)){
            qDebug() << "connected To Host";
            i = 0;
        }else{
            qDebug() << "not connect To Host";
            sleep(3);
        }
    }

    return i;
}

QString MainWindow::stripCR(const QString &msg)
{
    QString login = "tc login: ";
    QString pwd = "Password:";

    msgGlobal = msg;
    qDebug() << msg;
    QString nmsg(msg);
    nmsg.remove('\r');
    nmsg.remove(QRegExp("\033\\[[0-9;]*[A-Za-z]")); // Also remove terminal control codes

    if(msgGlobal.indexOf(login) >= 0){
        emit telnetmessage();
    }else if (msgGlobal.indexOf(pwd) >= 0){
        emit telnetmessage();
    }else if ((msgGlobal.indexOf("successfully") >= 0) && (msgGlobal.indexOf("00000081") >= 0)){
        emit todisablemode();
    }else if ((msgGlobal.indexOf("successfully") >= 0) && (msgGlobal.indexOf("00000087") >= 0)){
        emit toorigionmod();
    }else if ((msgGlobal.indexOf("00000080") >= 0) && (msgGlobal.indexOf("000000b4") >= 0)){
        emit calibrate_data();
    }else {

    }

    return nmsg;
}

void MainWindow::telnetConnectionError(QAbstractSocket::SocketError error)
{
    qDebug() << QString("Connection error: %1").arg(error);
    QMessageBox::warning(this,tr("error"),tr("Connection error: %1").arg(error),QMessageBox::Yes);
}

void MainWindow::telnetLoggedIn()
{
    qDebug() << "login in";
    //QMessageBox::warning(this,tr("error"),tr("login in"),QMessageBox::Yes);
}

void MainWindow::telnetLoggedOut()
{
    qDebug() << "login out";
    //QMessageBox::warning(this,tr("error"),tr("login out"),QMessageBox::Yes);
}

void MainWindow::telnetLoginFailed()
{
    qDebug() << "login failed";
    QMessageBox::warning(this,tr("error"),tr("login failed"),QMessageBox::Yes);
}

bool MainWindow::testDataJudge()
{
    bool ok;
    bool resultjudge = 0;
    bool extstate = 0;
    bool crostate = 0;
    bool rmsstate = 0;
    bool pkpkstate = 0;
    bool mask1state = 0;
    bool mask2state = 0;
    bool mask3state = 0;
    int maskindex = 0;
    QPalette pa;
    QString value;
    QString rmsjitter = "";
    QString pkpkjitter = "";
    double rmsdata;
    double pkpkdata;
    double data;

    int i = index_sum;
    while(i){
        switch(meas_entry_first->meas_type){
        case EYE_EXTICTRATIO:
#if 0
            value = QString(rps_value[meas_entry_first->meas_index-1]);
            //qDebug() << "EYE_EXTICTRATIO" <<value;
            data = value.toDouble(&ok);
            //qDebug() << "EYE_EXTICTRATIO" << data;
            if (qAbs(data*1.3 - 14.5) <= 3.3){
                ui->label_2_extinctratio->setText("pass");
                ui->label_2_extinctratio->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_2_extinctratio->setPalette(pa);
                extstate = 1;
            }else {
                ui->label_2_extinctratio->setText("fail");
                ui->label_2_extinctratio->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_2_extinctratio->setPalette(pa);
                extstate = 0;
            }
#endif
            break;
        case EYE_RMSJITTER:
            rmsjitter = QString(rps_value[meas_entry_first->meas_index-1]);
            if (rmsjitter == "error")
                rmsjitter = "";
            break;
        case EYE_PKPKJITTER:
            pkpkjitter = QString(rps_value[meas_entry_first->meas_index-1]);
            if (pkpkjitter == "error")
                pkpkjitter = "";
            break;
        case EYE_EXTINCTDB:
            break;
        case EYE_PCTCROSS:
            value = QString(rps_value[meas_entry_first->meas_index-1]);
            //qDebug() << "PCTCROSS" <<value;
            data = value.toDouble(&ok);
            //qDebug() << "PCTCROSS" << data;
            if (qAbs(data - 50.0) <= 5){
                ui->label_6_pctcross->setText("pass");
                ui->label_6_pctcross->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_6_pctcross->setPalette(pa);
                crostate = 1;
            }else {
                ui->label_6_pctcross->setText("fail");
                ui->label_6_pctcross->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_6_pctcross->setPalette(pa);
                crostate = 0;
            }
            break;
        default:
            break;
        }
        meas_entry_first = list_entry(meas_entry_first->list.next, meas_entry_t, list);
        i--;
    }

    if(!rmsjitter.isEmpty()){
        if (!pkpkjitter.isEmpty()){
            rmsdata = rmsjitter.toDouble(&ok);
            pkpkdata = pkpkjitter.toDouble(&ok);
            data = rmsdata*14 + pkpkdata;
            //qDebug() << "Jitter" << data;

            if (data < 260e-12){
                ui->label_2_jitter_state->setText("pass");
                ui->label_2_jitter_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_2_jitter_state->setPalette(pa);
                ui->lineEdit_jitter->setText(QString("%1").arg(data));

                ui->label_3_rmsjitter->setText("pass");
                ui->label_3_rmsjitter->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_3_rmsjitter->setPalette(pa);
                rmsstate = 1;

                ui->label_4_pkpkjitter->setText("pass");
                ui->label_4_pkpkjitter->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_4_pkpkjitter->setPalette(pa);
                pkpkstate = 1;
            }else {
                ui->label_2_jitter_state->setText("fail");
                ui->label_2_jitter_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_2_jitter_state->setPalette(pa);
                ui->lineEdit_jitter->setText(QString("%1").arg(data));

                ui->label_3_rmsjitter->setText("fail");
                ui->label_3_rmsjitter->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_3_rmsjitter->setPalette(pa);
                rmsstate = 0;

                ui->label_4_pkpkjitter->setText("fail");
                ui->label_4_pkpkjitter->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_4_pkpkjitter->setPalette(pa);
                pkpkstate = 0;

            }
        }else {
            //ui->label_4_pkpkjitter->setText("Not selected");
        }
    }else {
        //ui->label_3_rmsjitter->setText("Not selected");
    }
#if 0
    while (maskindex < 3){
        if (countResult[maskindex] == 0){
            switch(maskindex+1){
            case 1:
                ui->label_2_mask1_state->setText("pass");
                ui->label_2_mask1_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_2_mask1_state->setPalette(pa);
                mask1state = 1;
                break;
            case 2:
                ui->label_3_mask2_state->setText("pass");
                ui->label_3_mask2_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_3_mask2_state->setPalette(pa);
                mask2state = 1;
                break;
            case 3:
                ui->label_4_mask3_state->setText("pass");
                ui->label_4_mask3_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->label_4_mask3_state->setPalette(pa);
                mask3state = 1;
                break;
            default:
                break;
            }
        }else {
            switch(maskindex+1){
            case 1:
                ui->label_2_mask1_state->setText("fail");
                ui->label_2_mask1_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_2_mask1_state->setPalette(pa);
                mask1state = 0;
                break;
            case 2:
                ui->label_3_mask2_state->setText("fail");
                ui->label_3_mask2_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_3_mask2_state->setPalette(pa);
                mask2state = 0;
                break;
            case 3:
                ui->label_4_mask3_state->setText("fail");
                ui->label_4_mask3_state->setFont(QFont("Arial",16,QFont::Bold));
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->label_4_mask3_state->setPalette(pa);
                mask3state = 0;
                break;
            default:
                break;
            }
        }
        maskindex++;
    }
#endif

    //if (extstate == 1){
    if(crostate == 1){
        if (rmsstate == 1){
            if (pkpkstate == 1){
                //                    if (mask1state == 1){
                //                        if (mask2state == 1){
                //                            if (mask3state == 1){
                resultjudge = 1;
                //                            }else {
                //                                resultjudge = 0;
                //                            }
                //                        }else {
                //                            resultjudge = 0;
                //                        }
                //                    }else {
                //                        resultjudge = 0;
                //                    }
            }else {
                resultjudge = 0;
            }
        }else {
            resultjudge = 0;
        }
    }else {
        resultjudge = 0;
    }
    //    }else {
    //        resultjudge = 0;
    //    }

    return resultjudge;
}

void MainWindow::msec_sleep(int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::switch2table(int index)
{
    t->sendData("\n");
    t->socket()->waitForBytesWritten(30000);
    QByteArray CmdStringWr="sifm xw 0 0xc7 0xd1 1 0x7f 1 ";
    CmdStringWr.append(QString::number(index));
    t->sendData(CmdStringWr);
    t->socket()->waitForBytesWritten(30000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(30000);

    //emit toreaddata();
}

void MainWindow::read_calibrate_data()
{
    qDebug() << "read_calibrate_data";

    t->sendData("sifm xr 0 0xc7 0xd1 1 0x80 0x69");
    t->socket()->waitForBytesWritten(30000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(30000);

    //emit calibrate_data();
}

void MainWindow::on_pushButton_bias_translate_clicked()
{
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);
    //switch2table(5);

    emit toreaddata();
}

void MainWindow::deal_calibrate_data()
{
    int i=0;
    bool ok;

    memset(databuf,0,sizeof(databuf));
    QString Target_string  =  msgGlobal.mid(msgGlobal.indexOf("00000080") + 10,msgGlobal.length());
    //qDebug()<< "Target_string1" << Target_string;

    Target_string.replace(QString("\r\r\n00000080: "), QString(""));
    Target_string.replace(QString("\r\r\n00000084: "), QString(""));
    Target_string.replace(QString("\r\r\n00000088: "), QString(""));
    Target_string.replace(QString("\r\r\n0000008c: "), QString(""));
    Target_string.replace(QString("\r\r\n00000090: "), QString(""));
    Target_string.replace(QString("\r\r\n00000094: "), QString(""));
    Target_string.replace(QString("\r\r\n00000098: "), QString(""));
    Target_string.replace(QString("\r\r\n0000009c: "), QString(""));
    Target_string.replace(QString("\r\r\n000000a0: "), QString(""));
    Target_string.replace(QString("\r\r\n000000a4: "), QString(""));
    Target_string.replace(QString("\r\r\n000000a8: "), QString(""));
    Target_string.replace(QString("\r\r\n000000ac: "), QString(""));
    Target_string.replace(QString("\r\r\n000000b0: "), QString(""));
    Target_string.replace(QString("\r\r\n000000b4: "), QString(""));

    qDebug()<< "Target_string2" <<  Target_string;
    QString Target;
    for(i=0;i<0x69 ;i++)
    {
        Target="";
        QString Target = Target_string.mid(i*5+2,2);
        *(databuf+i) =Target.toInt(&ok,16);
    }

    emit totranslationdata();
}

void MainWindow::write_calibrate_data()
{
    int i=0, j=0;
    qDebug()<< "write_calibrate_data";

    QByteArray cmd_A0_wr("sifm xw 0 0xc7 0xd1 1 "); //A0闁告劖鐟ラ崣鍡涘川閹存帗濮?
    QByteArray target_cmd = "";
    BYTE address = 0x80;
    for (i = 0; i <= 6; i++)
    {
        target_cmd = cmd_A0_wr;
        target_cmd = target_cmd.append(" 0x");
        target_cmd = target_cmd.append(QByteArray::number(address, 16));
        address += 16;
        if (i == 6){
            target_cmd = target_cmd.append(" 0x09");
            for (j = 0; j < 9; j++)
            {

                target_cmd = target_cmd.append(" 0x");
                target_cmd = target_cmd.append(QByteArray::number(databuf[i *16+j], 16));
            }
        }else {
            target_cmd = target_cmd.append(" 0x10");
            for (j = 0; j < 16; j++)
            {
                target_cmd = target_cmd.append(" 0x");
                target_cmd = target_cmd.append(QByteArray::number(databuf[i *16+j], 16));
            }
        }
        qDebug()<< "target_cmd" << target_cmd;
        t->sendData(target_cmd);
        t->socket()->waitForBytesWritten(3000);
    }

    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);
    //    t->sendData("sifm xr 0 0xc7 0xd1 1 0x80 0x69");
    //    t->socket()->waitForBytesWritten(30000);
    //    t->sendData("dmesg -c");
    //    t->socket()->waitForBytesWritten(30000);

    ui->pushButton_write_flash->setEnabled(true);
}

void MainWindow::translation_data()
{
    int temp_data = 0x41;
    int i = 0;
    BYTE *p = databuf;
    BYTE *p1 = databuf;
    BYTE *p2 = p1+1;
    unsigned short num1change, num1result, num1reserve, num2change, num2result, num2reserve, result;
    bool ok;
    unsigned char index, index1, sum = 0;


    QString dataAdd = ui->lineEdit_diffrence->text();
    int dataAddNum = dataAdd.toInt(&ok,10);
    qDebug() << "dataAddNum" << dataAddNum;

    //while (i < 0x68){
    while (temp_data <= 0xE7){

        num1change = 0;
        num1result = 0;
        num1reserve = 0;
        num2change = 0;
        num2result = 0;
        num2reserve = 0;
        result = 0;

        index = temp_data - 65;
        //qDebug() << "temp_data" << QString::number(temp_data,16);
        index1 = index >> 1;

        sum = index1 & 0x03;
        //sum = (sum >> 6);
        qDebug() << sum;

        switch (sum) {
        case 0:
            num1change = *p1 << 2;
            num2reserve = *p2 & 0x3f;
            num2change = (*p2 >> 6) + dataAddNum;
            result = num1change + num2change;
            qDebug() << "result" << QString::number(result,16);
            if (result >= 0x3ff){
                num1result = 0xff;
                num2result = (0x03 << 6) | num2reserve;
            }else {
                num2change = result & 0x03;
                num1result = result >> 2;
                num2result = (num2change << 6) + num2reserve;
            }

            //qDebug() << *p1 << *p2;
            //p = (BYTE *)memcpy(p1,&num1result,1);
            //memcpy(p2,&num2result,1);
            *p1 = num1result;
            *p2 = num2result;
            //qDebug() << QString::number(*p1,16);
            //qDebug() << QString::number(*p2,16);
            break;
        case 1:
            num1reserve = *p1 & 0xc0;
            num1change = (*p1 & 0x3f) << 4;
            //num1change = num1change << 4;
            num2reserve = *p2 & 0x0f;
            num2change = (*p2 >> 4) + dataAddNum;
            result = num1change + num2change;
            qDebug() << "result" << QString::number(result,16);
            if (result >= 0x3ff){
                num1result = 0x03f | num1reserve;
                num2result = (0x0f << 4) | num2reserve;
            }else {
                num2change = result & 0x0f;
                num1result = (result >> 4) | num1reserve;
                num2result = (num2change << 4) + num2reserve;
            }

            //qDebug() << *p1 << *p2;
            //p = (BYTE *)memcpy(p1,&num1result,1);
            //memcpy(p2,&num2result,1);
            *p1 = num1result;
            *p2 = num2result;
            //qDebug() << QString::number(*p1,16);
            //qDebug() << QString::number(*p2,16);
            break;
        case 2:
            num1reserve = *p1 & 0xf0;
            num1change = (*p1 & 0x0f) << 6;
            num2reserve = *p2 & 0x03;
            num2change = (*p2 >> 2) + dataAddNum;
            result = num1change + num2change;
            qDebug() << "result" << QString::number(result,16);
            if (result >= 0x3ff){
                num1result = 0x0f | num1reserve;
                num2result = (0x3f << 2) | num2reserve;
            }else {
                num2change = result & 0x3f;
                num1result = (result >> 6) | num1reserve;
                num2result = (num2change << 2) + num2reserve;
            }

            //qDebug() << *p1 << *p2;
            //p = (BYTE *)memcpy(p1,&num1result,1);
            //memcpy(p2,&num2result,1);
            *p1 = num1result;
            *p2 = num2result;
            //qDebug() << QString::number(*p1,16);
            //qDebug() << QString::number(*p2,16);
            break;
        case 3:
            num1reserve = *p1 & 0xfc;
            num1change = (*p1 & 0x03) << 8;
            num2reserve = *p2 & 0x00;
            num2change = (*p2 >> 0) + dataAddNum;
            result = num1change + num2change;
            qDebug() << "result" << QString::number(result,16);
            if (result >= 0x3ff){
                num1result = 0x03 | num1reserve;
                num2result = (0xff << 0) | num2reserve;
            }else {
                num2change = result & 0xff;
                num1result = (result >> 8) | num1reserve;
                num2result = (num2change << 0) + num2reserve;
            }

            //qDebug() << *p1 << *p2;
            //p = (BYTE *)memcpy(p1,&num1result,1);
            //memcpy(p2,&num2result,1);
            *p1 = num1result;
            *p2 = num2result;
            //qDebug() << QString::number(*p1,16);
            //qDebug() << QString::number(*p2,16);
            break;
        default:
            qDebug() << "default";
            break;
        }

        p1++;
        p2++;
        if (sum == 3){
            p1++;
            p2++;
        }
        temp_data = temp_data + 2;
        i ++;
    }
    //    qDebug() << "i" << i;
    //    for (i = 0; i < 0x69; i++){
    //        qDebug() << QString::number(*p,16);
    //        p++;
    //    }
    emit towritedata();
}

void MainWindow::on_pushButton_write_flash_clicked()
{
    int i = 0, j = 0;
    //    BYTE *p = databuf;

    //    for (i = 0; i < 0x69; i++){
    //        qDebug() << QString::number(*p,16);
    //        p++;
    //    }

    QByteArray cmd_flash_wr("/userfs/bin/rw_table write /tmp/etc/MTK_A2.ini ");
    QByteArray target_cmd = "";
    unsigned short address = 384;

    for (i = 0; i <= 6; i++)
    {
        target_cmd = cmd_flash_wr;
        target_cmd = target_cmd.append(QByteArray::number(address, 10));
        address += 16;
        if (i == 6){
            target_cmd = target_cmd.append(" 9");
            for (j = 0; j < 9; j++)
            {
                target_cmd = target_cmd.append(" ");
                target_cmd = target_cmd.append(QByteArray::number(databuf[i *16+j], 16));
            }
        }else {
            target_cmd = target_cmd.append(" 16");
            for (j = 0; j < 16; j++)
            {
                target_cmd = target_cmd.append(" ");
                target_cmd = target_cmd.append(QByteArray::number(databuf[i *16+j], 16));
            }
        }
        qDebug()<< "target_cmd" << target_cmd;
        t->sendData(target_cmd);
        t->socket()->waitForBytesWritten(3000);
    }
    t->sendData("/userfs/bin/savedataTobob");
    t->socket()->waitForBytesWritten(3000);
    t->sendData("/userfs/bin/mtd -f write /tmp/etc/BOB.ini BOB");
    t->socket()->waitForBytesWritten(3000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);
}

void MainWindow::on_comboBox_tabel_switch_currentTextChanged(const QString &arg1)
{
    bool ok;
    int index = arg1.toInt(&ok,10);

    switch2table(index);
}

void MainWindow::on_pushButton_disable_mod_clicked()
{
    t->sendData("sifm xr 0 0xc7 0xd1 1 0x81 1");
    t->socket()->waitForBytesWritten(3000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);
}

void MainWindow::on_pushButton_2_read_origion_mod_clicked()
{
    t->sendData("sifm xr 0 0xc7 0xd1 1 0x87 1");
    t->socket()->waitForBytesWritten(3000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);
}

void MainWindow::on_pushButton_3_set_mod_clicked()
{
    bool ok;
    QString target = ui->lineEdit_3_set_mod->text();
    BYTE  data = target.toInt(&ok,16);

    QString cmd_A2_wr = QString("sifm xw 0 0xc7 0xd1 1 0x87 1 0x%1").arg(QString::number(data,16));
    t->sendData(cmd_A2_wr);
    t->socket()->waitForBytesWritten(3000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);

    QString mod_str = ui->lineEdit_2_read_origion_mod->text();
    BYTE  mod_data = mod_str.toInt(&ok,16);
    char diff = data - mod_data;
    qDebug() << "diff" << diff;
    ui->lineEdit_diffrence->setText(QString::number(diff,10));

    ui->pushButton_bias_translate->setEnabled(true);
}

void MainWindow::disable_mod_set()
{
    bool ok;

    QString target= msgGlobal.mid(msgGlobal.indexOf("00000081") + 12, 2);
    BYTE data = target.toInt(&ok,16);
    //qDebug() << "enable_mod_set" << data;

    data = data & 0xF7;
    //qDebug() << "disable_mod_set" << QString::number(data,16);
    QString cmd_A2_wr = QString("sifm xw 0 0xc7 0xd1 1 0x81 1 0x%1").arg(QString::number(data,16));
    t->sendData(cmd_A2_wr);
    t->socket()->waitForBytesWritten(3000);
    t->sendData("dmesg -c");
    t->socket()->waitForBytesWritten(3000);

    ui->lineEdit_disable_mod->setText(QString::number(data,16));
    ui->pushButton_2_read_origion_mod->setEnabled(true);
}

void MainWindow::get_origion_mod()
{
    QString target= msgGlobal.mid(msgGlobal.indexOf("00000087") + 12, 2);

    //qDebug() << "get_origion_mod" << target;
    ui->lineEdit_2_read_origion_mod->setText(target);
    ui->pushButton_3_set_mod->setEnabled(true);
}
