/********************************************************************************
** Form generated from reading UI file 'dialog_db.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DB_H
#define UI_DIALOG_DB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_db
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *dbLineGroupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *dbAddress;
    QLabel *dbPort;
    QLabel *dbName;
    QLabel *dbUserName;
    QLabel *dbPassword;
    QGroupBox *dbLabelGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *dbAddrLine;
    QLineEdit *dbPortLine;
    QLineEdit *dbNameLine;
    QLineEdit *dbUserNameLine;
    QLineEdit *dbPwLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_db)
    {
        if (Dialog_db->objectName().isEmpty())
            Dialog_db->setObjectName(QStringLiteral("Dialog_db"));
        Dialog_db->resize(400, 300);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        Dialog_db->setFont(font);
        verticalLayout = new QVBoxLayout(Dialog_db);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 20, 20, 20);
        dbLineGroupBox = new QGroupBox(Dialog_db);
        dbLineGroupBox->setObjectName(QStringLiteral("dbLineGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dbLineGroupBox->sizePolicy().hasHeightForWidth());
        dbLineGroupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(dbLineGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        dbAddress = new QLabel(dbLineGroupBox);
        dbAddress->setObjectName(QStringLiteral("dbAddress"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dbAddress->sizePolicy().hasHeightForWidth());
        dbAddress->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dbAddress);

        dbPort = new QLabel(dbLineGroupBox);
        dbPort->setObjectName(QStringLiteral("dbPort"));
        sizePolicy1.setHeightForWidth(dbPort->sizePolicy().hasHeightForWidth());
        dbPort->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dbPort);

        dbName = new QLabel(dbLineGroupBox);
        dbName->setObjectName(QStringLiteral("dbName"));
        sizePolicy1.setHeightForWidth(dbName->sizePolicy().hasHeightForWidth());
        dbName->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dbName);

        dbUserName = new QLabel(dbLineGroupBox);
        dbUserName->setObjectName(QStringLiteral("dbUserName"));
        sizePolicy1.setHeightForWidth(dbUserName->sizePolicy().hasHeightForWidth());
        dbUserName->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dbUserName);

        dbPassword = new QLabel(dbLineGroupBox);
        dbPassword->setObjectName(QStringLiteral("dbPassword"));
        sizePolicy1.setHeightForWidth(dbPassword->sizePolicy().hasHeightForWidth());
        dbPassword->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dbPassword);


        horizontalLayout->addWidget(dbLineGroupBox);

        dbLabelGroupBox = new QGroupBox(Dialog_db);
        dbLabelGroupBox->setObjectName(QStringLiteral("dbLabelGroupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(6);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dbLabelGroupBox->sizePolicy().hasHeightForWidth());
        dbLabelGroupBox->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(dbLabelGroupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        dbAddrLine = new QLineEdit(dbLabelGroupBox);
        dbAddrLine->setObjectName(QStringLiteral("dbAddrLine"));
        sizePolicy1.setHeightForWidth(dbAddrLine->sizePolicy().hasHeightForWidth());
        dbAddrLine->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(dbAddrLine);

        dbPortLine = new QLineEdit(dbLabelGroupBox);
        dbPortLine->setObjectName(QStringLiteral("dbPortLine"));
        sizePolicy1.setHeightForWidth(dbPortLine->sizePolicy().hasHeightForWidth());
        dbPortLine->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(dbPortLine);

        dbNameLine = new QLineEdit(dbLabelGroupBox);
        dbNameLine->setObjectName(QStringLiteral("dbNameLine"));

        verticalLayout_3->addWidget(dbNameLine);

        dbUserNameLine = new QLineEdit(dbLabelGroupBox);
        dbUserNameLine->setObjectName(QStringLiteral("dbUserNameLine"));

        verticalLayout_3->addWidget(dbUserNameLine);

        dbPwLine = new QLineEdit(dbLabelGroupBox);
        dbPwLine->setObjectName(QStringLiteral("dbPwLine"));

        verticalLayout_3->addWidget(dbPwLine);


        horizontalLayout->addWidget(dbLabelGroupBox);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(Dialog_db);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog_db);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_db, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_db, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_db);
    } // setupUi

    void retranslateUi(QDialog *Dialog_db)
    {
        Dialog_db->setWindowTitle(QApplication::translate("Dialog_db", "Dialog", 0));
        dbAddress->setText(QApplication::translate("Dialog_db", "DATABASE ADDRESS", 0));
        dbPort->setText(QApplication::translate("Dialog_db", "DATABASE PORT", 0));
        dbName->setText(QApplication::translate("Dialog_db", "DATABASE NAME", 0));
        dbUserName->setText(QApplication::translate("Dialog_db", "USER NAME", 0));
        dbPassword->setText(QApplication::translate("Dialog_db", "PASSWORD", 0));
        dbAddrLine->setText(QApplication::translate("Dialog_db", "127.0.0.1", 0));
        dbPortLine->setText(QApplication::translate("Dialog_db", "59157", 0));
        dbNameLine->setText(QApplication::translate("Dialog_db", "master", 0));
        dbUserNameLine->setText(QApplication::translate("Dialog_db", "sa", 0));
        dbPwLine->setText(QApplication::translate("Dialog_db", "SINOBOB", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_db: public Ui_Dialog_db {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DB_H
