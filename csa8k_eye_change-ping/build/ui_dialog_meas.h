/********************************************************************************
** Form generated from reading UI file 'dialog_meas.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_MEAS_H
#define UI_DIALOG_MEAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Meas
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLeft;
    QCheckBox *EYE_WIDTH_chb;
    QCheckBox *EYE_HEIGHT_chb;
    QCheckBox *EYE_HIGH_chb;
    QCheckBox *EYE_LOW_chb;
    QCheckBox *EYE_AMPLITUDE_chb;
    QCheckBox *EYE_PCROSS_chb;
    QCheckBox *EYE_NCROSS_chb;
    QCheckBox *EYE_EXTICTRATIO_chb;
    QVBoxLayout *verticalRight;
    QCheckBox *EYE_QFACTOR_chb;
    QCheckBox *EYE_AOPTPWRDBM_chb;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_Meas)
    {
        if (Dialog_Meas->objectName().isEmpty())
            Dialog_Meas->setObjectName(QStringLiteral("Dialog_Meas"));
        Dialog_Meas->resize(400, 301);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        Dialog_Meas->setFont(font);
        verticalLayout = new QVBoxLayout(Dialog_Meas);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 20, 20, 20);
        verticalLeft = new QVBoxLayout();
        verticalLeft->setObjectName(QStringLiteral("verticalLeft"));
        verticalLeft->setContentsMargins(10, 10, 10, 10);
        EYE_WIDTH_chb = new QCheckBox(Dialog_Meas);
        EYE_WIDTH_chb->setObjectName(QStringLiteral("EYE_WIDTH_chb"));

        verticalLeft->addWidget(EYE_WIDTH_chb);

        EYE_HEIGHT_chb = new QCheckBox(Dialog_Meas);
        EYE_HEIGHT_chb->setObjectName(QStringLiteral("EYE_HEIGHT_chb"));

        verticalLeft->addWidget(EYE_HEIGHT_chb);

        EYE_HIGH_chb = new QCheckBox(Dialog_Meas);
        EYE_HIGH_chb->setObjectName(QStringLiteral("EYE_HIGH_chb"));

        verticalLeft->addWidget(EYE_HIGH_chb);

        EYE_LOW_chb = new QCheckBox(Dialog_Meas);
        EYE_LOW_chb->setObjectName(QStringLiteral("EYE_LOW_chb"));
        EYE_LOW_chb->setChecked(false);
        EYE_LOW_chb->setAutoRepeat(false);
        EYE_LOW_chb->setTristate(false);

        verticalLeft->addWidget(EYE_LOW_chb);

        EYE_AMPLITUDE_chb = new QCheckBox(Dialog_Meas);
        EYE_AMPLITUDE_chb->setObjectName(QStringLiteral("EYE_AMPLITUDE_chb"));

        verticalLeft->addWidget(EYE_AMPLITUDE_chb);

        EYE_PCROSS_chb = new QCheckBox(Dialog_Meas);
        EYE_PCROSS_chb->setObjectName(QStringLiteral("EYE_PCROSS_chb"));

        verticalLeft->addWidget(EYE_PCROSS_chb);

        EYE_NCROSS_chb = new QCheckBox(Dialog_Meas);
        EYE_NCROSS_chb->setObjectName(QStringLiteral("EYE_NCROSS_chb"));

        verticalLeft->addWidget(EYE_NCROSS_chb);

        EYE_EXTICTRATIO_chb = new QCheckBox(Dialog_Meas);
        EYE_EXTICTRATIO_chb->setObjectName(QStringLiteral("EYE_EXTICTRATIO_chb"));

        verticalLeft->addWidget(EYE_EXTICTRATIO_chb);


        horizontalLayout->addLayout(verticalLeft);

        verticalRight = new QVBoxLayout();
        verticalRight->setSpacing(6);
        verticalRight->setObjectName(QStringLiteral("verticalRight"));
        verticalRight->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalRight->setContentsMargins(10, 10, 10, 10);
        EYE_QFACTOR_chb = new QCheckBox(Dialog_Meas);
        EYE_QFACTOR_chb->setObjectName(QStringLiteral("EYE_QFACTOR_chb"));

        verticalRight->addWidget(EYE_QFACTOR_chb);

        EYE_AOPTPWRDBM_chb = new QCheckBox(Dialog_Meas);
        EYE_AOPTPWRDBM_chb->setObjectName(QStringLiteral("EYE_AOPTPWRDBM_chb"));

        verticalRight->addWidget(EYE_AOPTPWRDBM_chb);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalRight->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalRight);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(Dialog_Meas);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog_Meas);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_Meas, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_Meas, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_Meas);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Meas)
    {
        Dialog_Meas->setWindowTitle(QApplication::translate("Dialog_Meas", "Dialog", 0));
        EYE_WIDTH_chb->setText(QApplication::translate("Dialog_Meas", "EYE_WIDTH", 0));
        EYE_HEIGHT_chb->setText(QApplication::translate("Dialog_Meas", "EYE_HEIGHT", 0));
        EYE_HIGH_chb->setText(QApplication::translate("Dialog_Meas", "EYE_HIGH", 0));
        EYE_LOW_chb->setText(QApplication::translate("Dialog_Meas", "EYE_LOW", 0));
        EYE_AMPLITUDE_chb->setText(QApplication::translate("Dialog_Meas", "EYE_AMPLITUDE", 0));
        EYE_PCROSS_chb->setText(QApplication::translate("Dialog_Meas", "EYE_PCROSS", 0));
        EYE_NCROSS_chb->setText(QApplication::translate("Dialog_Meas", "EYE_NCROSS", 0));
        EYE_EXTICTRATIO_chb->setText(QApplication::translate("Dialog_Meas", "EYE_EXTICTRATIO", 0));
        EYE_QFACTOR_chb->setText(QApplication::translate("Dialog_Meas", "EYE_QFACTOR", 0));
        EYE_AOPTPWRDBM_chb->setText(QApplication::translate("Dialog_Meas", "EYE_AOPTPWRDBM", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Meas: public Ui_Dialog_Meas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_MEAS_H
