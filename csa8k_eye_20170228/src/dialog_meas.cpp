#include "dialog_db.h"
#include "ui_dialog_meas.h"
#include "dialog_meas.h"
#include "csa8k_api.h"

extern meas_entry_t *meas_entry_first;

Dialog_Meas::Dialog_Meas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Meas)
{
    ui->setupUi(this);
}

Dialog_Meas::~Dialog_Meas()
{
    delete ui;
}

void Dialog_Meas::on_buttonBox_accepted()
{
    char res_str[RES_STR_MAX * MEAS_MAX] = {0};
    int str_len = 0;
    meas_entry_t *meas = NULL;
    int index = 0;

    /**
     * Initialize the measurement entry when this type of meaurement is selected
     */
    if (ui->EYE_WIDTH_chb->isChecked()) {
        meas_entry_t *meas_eye_width = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_width,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_width, index, EYE_WIDTH);
        meas = meas_eye_width;
        str_len = snprintf(res_str, RES_STR_MAX, "measurement:index=%d;\t type=eyewidth\t has been selected\n", index);
    }

    if (ui->EYE_HEIGHT_chb->isChecked()) {
        meas_entry_t *meas_eye_height = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_height,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_height, index, EYE_HEIGHT);
        if (meas != NULL)
            list_add(&meas_eye_height->list, &meas->list);
        meas = meas_eye_height;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=eyeheight\t has been selected\n", index);
    }

    if (ui->EYE_HIGH_chb->isChecked()) {
        meas_entry_t *meas_eye_high = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_high,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_high, index, EYE_HIGH);
        if (meas != NULL)
            list_add(&meas_eye_high->list, &meas->list);
        meas = meas_eye_high;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=high\t\t has been selected\n", index);
    }

    if (ui->EYE_LOW_chb->isChecked()) {
        meas_entry_t *meas_eye_low = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_low,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_low, index, EYE_LOW);
        if (meas != NULL)
            list_add(&meas_eye_low->list, &meas->list);
        meas = meas_eye_low;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=low\t\t has been selected\n", index);
    }

    if (ui->EYE_AMPLITUDE_chb->isChecked()) {
        meas_entry_t *meas_eye_amplitude = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_amplitude,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_amplitude, index, EYE_AMPLITUDE);
        if (meas != NULL)
            list_add(&meas_eye_amplitude->list, &meas->list);
        meas = meas_eye_amplitude;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=amplitude\t has been selected\n", index);
    }

    if (ui->EYE_PCROSS_chb->isChecked()) {
        meas_entry_t *meas_eye_pcross = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_pcross,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_pcross, index, EYE_PCROSS);
        if (meas != NULL)
            list_add(&meas_eye_pcross->list, &meas->list);
        meas = meas_eye_pcross;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=pcross\t\t has been selected\n", index);
    }

    if (ui->EYE_NCROSS_chb->isChecked()) {
        meas_entry_t *meas_eye_ncross = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_ncross,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_ncross, index, EYE_NCROSS);
        if (meas != NULL)
            list_add(&meas_eye_ncross->list, &meas->list);
        meas = meas_eye_ncross;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=ncross\t\t has been selected\n", index);
    }

    if (ui->EYE_EXTICTRATIO_chb->isChecked()) {
        meas_entry_t *meas_eye_extictratio = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_extictratio,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_extictratio, index, EYE_EXTICTRATIO);
        if (meas != NULL)
            list_add(&meas_eye_extictratio->list, &meas->list);
        meas = meas_eye_extictratio;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=extinctratio\t has been selected\n", index);
    }

    if (ui->EYE_QFACTOR_chb->isChecked()) {
        meas_entry_t *meas_eye_qfactor = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_qfactor,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_qfactor, index, EYE_QFACTOR);
        if (meas != NULL)
            list_add(&meas_eye_qfactor->list, &meas->list);
        meas = meas_eye_qfactor;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=qfactor\t\t has been selected\n", index);
    }

    if (ui->EYE_AOPTPWRDBM_chb->isChecked()) {
        meas_entry_t *meas_eye_aoptpwrdbm = (meas_entry_t *)malloc(sizeof(meas_entry_t));
        memset(meas_eye_aoptpwrdbm,0,sizeof(meas_entry_t));
        index++;
        meas_entry_init(meas_eye_aoptpwrdbm, index, EYE_AOPTPWRDBM);
        if (meas != NULL)
            list_add(&meas_eye_aoptpwrdbm->list, &meas->list);
        meas = meas_eye_aoptpwrdbm;
        str_len += snprintf(res_str + str_len, RES_STR_MAX, "measurement:index=%d;\t type=aoptpwrdbm\t has been selected\n", index);
    }

    /**
     * Delete existing measurement entry when reselected
     */
    if (meas_entry_first != NULL) {
        while (!list_empty(&meas_entry_first->list)) {
            list_head_t *tmp = meas_entry_first->list.next;
            list_del(meas_entry_first->list.next);
            free(list_entry(tmp, meas_entry_t, list));
        }
        free(meas_entry_first);
        meas_entry_first = NULL;
    }
    
    /**
     * Show the result of measurement entry select
     */
    if (meas != NULL) {
        meas_entry_first = list_entry(meas->list.next, meas_entry_t, list);    //the "next pointer" of last measurement entry (meas) list head always point to first entry
        emit sendData(QString(QLatin1String(res_str)));
    } else {
        emit sendData("%No measurement entry has been selected!");
    }
}
