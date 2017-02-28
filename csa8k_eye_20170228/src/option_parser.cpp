#include "option_parser.h"
#include "csa8k_api.h"

char *chxFilterParser(QString &str)
{
    if (QString::compare(str, "OC-48/STM-16", Qt::CaseInsensitive) == 0) {
        sprintf(cmd_global,"oc48");
        return cmd_global;
        //return QString("oc48").toLatin1().data();//错误写法，返回为空，局部变量在函数调用结束时被回收
    }

    else
        return NULL;
}

char *maskSourceParser(QString &str)
{
    if (QString::compare(str, "Channel 1 Main", Qt::CaseInsensitive) == 0)
        return QString("ch1,main").toLatin1().data();
    else if (QString::compare(str, "Channel 2 Main", Qt::CaseInsensitive) == 0)
        return QString("ch2,main").toLatin1().data();
    else if (QString::compare(str, "Channel 3 Main", Qt::CaseInsensitive) == 0)
        return QString("ch3,main").toLatin1().data();
    else if (QString::compare(str, "Channel 4 Main", Qt::CaseInsensitive) == 0)
        return QString("ch4,main").toLatin1().data();
    else if (QString::compare(str, "Channel 5 Main", Qt::CaseInsensitive) == 0)
        return QString("ch5,main").toLatin1().data();
    else if (QString::compare(str, "Channel 6 Main", Qt::CaseInsensitive) == 0)
        return QString("ch6,main").toLatin1().data();
    else if (QString::compare(str, "Channel 7 Main", Qt::CaseInsensitive) == 0)
        return QString("ch7,main").toLatin1().data();
    else if (QString::compare(str, "Channel 8 Main", Qt::CaseInsensitive) == 0)
        return QString("ch8,main").toLatin1().data();

    else
        return NULL;
}

char *maskStandardParser(QString &str)
{
    if (QString::compare(str, "OC-48/STM-16", Qt::CaseInsensitive) == 0) {
        sprintf(cmd_global,"oc48");
        return cmd_global;
        //return QString("oc48").toLatin1().data();//错误写法，返回为空，局部变量在函数调用结束时被回收。
    }else if (QString::compare(str, "Gigabit Ethernet", Qt::CaseInsensitive) == 0){
        sprintf(cmd_global,"ENET1250");
        return cmd_global;
    }else
        return NULL;
}

char *acqSaModeParser(QString &str)
{
    if (QString::compare(str, "Condition", Qt::CaseInsensitive) == 0) {
        return QString("condition").toLatin1().data();
    }

    else
        return NULL;
}

char *acqSaConParser(QString &str)
{
    if (QString::compare(str, "Mask Wave Form", Qt::CaseInsensitive) == 0) {
        return QString("maskwaveform").toLatin1().data();
    }

    else
        return NULL;
}

char *trigSrcParser(QString &str)
{
    if (QString::compare(str, "Clock Recover", Qt::CaseInsensitive) == 0) {
        return QString("clkrecovery").toLatin1().data();
    }

    else
        return NULL;
}

char *trigClkSrcParser(QString &str)
{
    if (QString::compare(str, "Channel 1", Qt::CaseInsensitive) == 0)
        return QString("ch1").toLatin1().data();
    else if (QString::compare(str, "Channel 2", Qt::CaseInsensitive) == 0)
        return QString("ch2").toLatin1().data();
    else if (QString::compare(str, "Channel 3", Qt::CaseInsensitive) == 0)
        return QString("ch3").toLatin1().data();
    else if (QString::compare(str, "Channel 4", Qt::CaseInsensitive) == 0)
        return QString("ch4").toLatin1().data();
    else if (QString::compare(str, "Channel 5", Qt::CaseInsensitive) == 0)
        return QString("ch5").toLatin1().data();
    else if (QString::compare(str, "Channel 6", Qt::CaseInsensitive) == 0)
        return QString("ch6").toLatin1().data();
    else if (QString::compare(str, "Channel 7", Qt::CaseInsensitive) == 0)
        return QString("ch7").toLatin1().data();
    else if (QString::compare(str, "Channel 8", Qt::CaseInsensitive) == 0)
        return QString("ch8").toLatin1().data();

    else
        return NULL;
}

char *trigClkValParser(QString &str)
{
    if (QString::compare(str, "OC-48/STM-16", Qt::CaseInsensitive) == 0) {
        return QString("oc48").toLatin1().data();
    }

    else
        return NULL;
}


char *measSourceType(QString &str)
{
    if (QString::compare(str, "NRZ", Qt::CaseInsensitive) == 0) {
        sprintf(cmd_global,"EYE");
        return cmd_global;
    }else if (QString::compare(str, "Pulse", Qt::CaseInsensitive) == 0){
        sprintf(cmd_global,"PULSE");
        return cmd_global;
    }else if (QString::compare(str, "RZ", Qt::CaseInsensitive) == 0){
        sprintf(cmd_global,"RZ");
        return cmd_global;
    }else
        return NULL;
}
