#include <QDebug>

#include "sql_db.h"
#include "csa8k_api.h"

QString getMeasTypeStr(int measType)
{
    switch(measType) {
        case 1: return "eyeWidth";
        case 2: return "eyeHeight";
        case 3: return "eyeHigh";
        case 4: return "eyeLow";
        case 5: return "eyeAmplitude";
        case 6: return "eyePcross";
        case 7: return "eyeNcross";
        case 8: return "eyeExtinctratio";
        case 9: return "eyeQfactor";
        case 10: return "eyeAoptpwrdbm";
        default: return NULL;
    }
}

bool creatDbHandle(const QString &address, const QString &port,const QString &name, const QString &user, const QString &pw)
{
    if (!QSqlDatabase::drivers().contains("QODBC"))
        qDebug()<< "Unable to load database, This demo needs the QODBC driver";
    else
        qDebug()<< "QODBC driver is ready";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "csa8kEyeDb");
    QString dsn = QString("DRIVER=SQL SERVER;"
                          "SERVER=%1,%2;"
                          "DATABASE=%3;"
                          "UID=%4;"
                          "PWD=%5;").arg(address).arg(port).arg(name).arg(user).arg(pw);
    qDebug()<< dsn;
    db.setDatabaseName(dsn);
    db.setUserName(user);
    db.setPassword(pw);
    if (!db.open()) {
        qDebug()<< "db.lastError().text()";
        return false;
    } else {
        qDebug()<< "Connect is successful";
        db.close();
        return true;
    }
}

bool updateValueByFilter(const QString &filter, meas_entry_t *meas_entry_first)
{
    QSqlDatabase db = QSqlDatabase::database("csa8kEyeDb");
    QSqlQuery query(db);
    QString cmd;
    list_head_t *tmpHead = &meas_entry_first->list;
    meas_entry_t *tmpMeas = meas_entry_first;

    if(!db.open())
        return false;
    else
        qDebug()<< "Connect is successful";

    /*insert query.prepare*/
/*
    if (tmpMeas != NULL) {
        cmd = "insert into EyeRecord(";
        cmd += getMeasTypeStr(tmpMeas->meas_type);
        while (!list_is_last(tmpHead, &meas_entry_first->list)) {
            tmpHead = tmpHead->next;
            tmpMeas = list_entry(tmpHead, meas_entry_t, list);
            cmd += ",";
            cmd += getMeasTypeStr(tmpMeas->meas_type);
        }
        cmd += ") values(?";
        for (int i = tmpMeas->meas_index; i > 1; i--)
            cmd += ",?";
        cmd += ")";
        qDebug()<< cmd;
        query.prepare(cmd);
    } else {
        qDebug()<< "Meas entry has not been selected";
        return false;
    }
*/
    /*update query.prepare*/
    if (tmpMeas != NULL) {
        cmd = "update EyeRecord set ";
        cmd = cmd + getMeasTypeStr(tmpMeas->meas_type) + "=?";
        while (!list_is_last(tmpHead, &meas_entry_first->list)) {
            tmpHead = tmpHead->next;
            tmpMeas = list_entry(tmpHead, meas_entry_t, list);
            cmd += ",";
            cmd = cmd + getMeasTypeStr(tmpMeas->meas_type) + "=?";
        }
        cmd = cmd + " where sn=" + filter;
        qDebug()<< cmd;
        query.prepare(cmd);
    } else {
        qDebug()<< "Meas entry has not been selected";
        return false;
    }

    /*query.bindValue*/
    tmpHead = &meas_entry_first->list;
    tmpMeas = meas_entry_first;
    if (tmpMeas != NULL) {
        query.bindValue(tmpMeas->meas_index-1, tmpMeas->meas_value);
        qDebug()<< QString("query.bindValue(%1,%2)").arg(tmpMeas->meas_index-1).arg(tmpMeas->meas_value);
        while (!list_is_last(tmpHead, &meas_entry_first->list)) {
            tmpHead = tmpHead->next;
            tmpMeas = list_entry(tmpHead, meas_entry_t, list);
            query.bindValue(tmpMeas->meas_index-1, tmpMeas->meas_value);
            qDebug()<< QString("query.bindValue(%1,%2)").arg(tmpMeas->meas_index-1).arg(tmpMeas->meas_value);
        }
        if (!query.exec())
            return false;
        else
            qDebug()<< "Update is successful";
    }

    db.close();
    return true;
}
