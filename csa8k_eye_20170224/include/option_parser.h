#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <QString>

char *chxFilterParser(QString &str);
char *maskSourceParser(QString &str);
char *maskStandardParser(QString &str);
char *acqSaModeParser(QString &str);
char *acqSaConParser(QString &str);
char *trigSrcParser(QString &str);
char *trigClkSrcParser(QString &str);
char *trigClkValParser(QString &str);
char *measSourceType(QString &str);

#endif // OPTION_PARSER_H
