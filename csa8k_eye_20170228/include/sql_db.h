#ifndef SQL_DB_H
#define SQL_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>

#include "csa8k_api.h"

bool creatDbHandle(const QString &address, const QString &port,const QString &name, const QString &user, const QString &pw);

bool updateValueByFilter(const QString &filter, meas_entry_t *meas_entry_first);

#endif // SQL_DB_H
