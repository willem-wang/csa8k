/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_O;
    QAction *actionClose_C;
    QAction *actionNew_N;
    QAction *actionDatabase_D;
    QAction *actionMeasurment_M;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *MainLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *LeftLayout;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *ManualTestFrame;
    QHBoxLayout *horizontalLayout_control;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_command;
    QLineEdit *commandLine;
    QHBoxLayout *horizontalLayout_commandButton;
    QPushButton *pushButton_send;
    QPushButton *pushButton_read;
    QPushButton *pushButton_sendRead;
    QTextBrowser *textBrowser_control;
    QSpacerItem *verticalSpacer;
    QGroupBox *AutoTestFrame;
    QHBoxLayout *horizontalLayout_autoTest;
    QPushButton *pushButton_AutoTest;
    QVBoxLayout *verticalLayout_config;
    QHBoxLayout *horizontalLayout_configButton;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_configure;
    QTextBrowser *textBrowser;
    QSpacerItem *horizontalSpacer;
    QWidget *RightLayout;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabMeas;
    QGroupBox *measGroupBox;
    QVBoxLayout *verticalLayout;
    QLabel *measLabel;
    QFormLayout *MeasFormLayout;
    QCheckBox *EYE_WIDTH_chb;
    QCheckBox *EYE_HEIGHT_chb;
    QCheckBox *EYE_HIGH_chb;
    QCheckBox *EYE_LOW_chb;
    QCheckBox *EYE_AMPLITUDE_chb;
    QCheckBox *EYE_PCROSS_chb;
    QCheckBox *EYE_NCROSS_chb;
    QCheckBox *EYE_EXTICTRATIO_chb;
    QCheckBox *EYE_QFACTOR_chb;
    QCheckBox *EYE_AOPTPWRDBM_chb;
    QLineEdit *EYE_WIDTH_le;
    QLineEdit *EYE_HEIGHT_le;
    QLineEdit *EYE_HIGH_le;
    QLineEdit *EYE_LOW_le;
    QLineEdit *EYE_AMPLITUDE_le;
    QLineEdit *EYE_PCROSS_le;
    QLineEdit *EYE_NCROSS_le;
    QLineEdit *EYE_EXTICTRATIO_le;
    QLineEdit *EYE_QFACTOR_le;
    QLineEdit *EYE_AOPTPWRDBM_le;
    QWidget *tabVert;
    QGroupBox *verticalGroupBox_vert;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_selCh;
    QGroupBox *GroupBox_selCh;
    QHBoxLayout *horizontalLayout_selCh;
    QComboBox *comboBox_selCh;
    QCheckBox *checkBox_state;
    QLabel *label_setup;
    QGroupBox *GroupBox_setup;
    QFormLayout *formLayout_2;
    QLabel *label_wlength;
    QComboBox *comboBox_wl;
    QLabel *label_filter;
    QComboBox *comboBox_filter;
    QWidget *tab_mask;
    QGroupBox *verticalGroupBox_mask;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_src;
    QGroupBox *GroupBox_src;
    QHBoxLayout *horizontalLayout_selCh_2;
    QComboBox *comboBox_src;
    QCheckBox *checkBox_enable;
    QLabel *label_maskSetup;
    QGroupBox *GroupBox_maskSetup;
    QFormLayout *formLayout_3;
    QLabel *label_maskStd;
    QComboBox *comboBox_maskStd;
    QWidget *tab_acq;
    QGroupBox *verticalGroupBox_acq;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_stopAfter;
    QGroupBox *GroupBox_stopAfter;
    QFormLayout *formLayout_4;
    QLabel *label_mode;
    QComboBox *comboBox_mode;
    QLabel *label_cond;
    QComboBox *comboBox_cond;
    QLabel *label_count;
    QLineEdit *lineEdit_count;
    QWidget *tab_trig;
    QGroupBox *verticalGroupBox_trig;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_trigSrc;
    QGroupBox *GroupBox_trigSrc;
    QHBoxLayout *horizontalLayout_selCh_3;
    QLabel *label_trigSrc_2;
    QComboBox *comboBox_trigSrc;
    QLabel *label_clkrecSetup;
    QGroupBox *GroupBox_clkrec;
    QFormLayout *formLayout_5;
    QLabel *label_clkrecSrc;
    QComboBox *comboBox_clkrecSrc;
    QLabel *label_clkrecVal;
    QComboBox *comboBox_clkrecVal;
    QMenuBar *menuBar;
    QMenu *menuOption_O;
    QMenu *menuHelp_H;
    QMenu *menuFile_F;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1600, 900);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        MainWindow->setFont(font);
        MainWindow->setAutoFillBackground(false);
        actionOpen_O = new QAction(MainWindow);
        actionOpen_O->setObjectName(QStringLiteral("actionOpen_O"));
        actionClose_C = new QAction(MainWindow);
        actionClose_C->setObjectName(QStringLiteral("actionClose_C"));
        actionNew_N = new QAction(MainWindow);
        actionNew_N->setObjectName(QStringLiteral("actionNew_N"));
        actionDatabase_D = new QAction(MainWindow);
        actionDatabase_D->setObjectName(QStringLiteral("actionDatabase_D"));
        actionMeasurment_M = new QAction(MainWindow);
        actionMeasurment_M->setObjectName(QStringLiteral("actionMeasurment_M"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        MainLayout = new QWidget(centralWidget);
        MainLayout->setObjectName(QStringLiteral("MainLayout"));
        sizePolicy.setHeightForWidth(MainLayout->sizePolicy().hasHeightForWidth());
        MainLayout->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(MainLayout);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        LeftLayout = new QWidget(MainLayout);
        LeftLayout->setObjectName(QStringLiteral("LeftLayout"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(6);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LeftLayout->sizePolicy().hasHeightForWidth());
        LeftLayout->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(LeftLayout);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ManualTestFrame = new QGroupBox(LeftLayout);
        ManualTestFrame->setObjectName(QStringLiteral("ManualTestFrame"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(2);
        sizePolicy3.setHeightForWidth(ManualTestFrame->sizePolicy().hasHeightForWidth());
        ManualTestFrame->setSizePolicy(sizePolicy3);
        ManualTestFrame->setMinimumSize(QSize(0, 75));
        horizontalLayout_control = new QHBoxLayout(ManualTestFrame);
        horizontalLayout_control->setSpacing(6);
        horizontalLayout_control->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_control->setObjectName(QStringLiteral("horizontalLayout_control"));
        horizontalLayout_control->setContentsMargins(0, 0, 0, 0);
        pushButton_connect = new QPushButton(ManualTestFrame);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_connect->sizePolicy().hasHeightForWidth());
        pushButton_connect->setSizePolicy(sizePolicy4);
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_connect->setFont(font1);

        horizontalLayout_control->addWidget(pushButton_connect);

        pushButton_disconnect = new QPushButton(ManualTestFrame);
        pushButton_disconnect->setObjectName(QStringLiteral("pushButton_disconnect"));
        sizePolicy4.setHeightForWidth(pushButton_disconnect->sizePolicy().hasHeightForWidth());
        pushButton_disconnect->setSizePolicy(sizePolicy4);
        pushButton_disconnect->setFont(font1);

        horizontalLayout_control->addWidget(pushButton_disconnect);

        groupBox = new QGroupBox(ManualTestFrame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(8);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy5);
        groupBox->setAutoFillBackground(false);
        verticalLayout_command = new QVBoxLayout(groupBox);
        verticalLayout_command->setSpacing(6);
        verticalLayout_command->setContentsMargins(11, 11, 11, 11);
        verticalLayout_command->setObjectName(QStringLiteral("verticalLayout_command"));
        verticalLayout_command->setContentsMargins(0, 0, 0, 0);
        commandLine = new QLineEdit(groupBox);
        commandLine->setObjectName(QStringLiteral("commandLine"));
        sizePolicy.setHeightForWidth(commandLine->sizePolicy().hasHeightForWidth());
        commandLine->setSizePolicy(sizePolicy);
        commandLine->setFont(font);

        verticalLayout_command->addWidget(commandLine);

        horizontalLayout_commandButton = new QHBoxLayout();
        horizontalLayout_commandButton->setSpacing(6);
        horizontalLayout_commandButton->setObjectName(QStringLiteral("horizontalLayout_commandButton"));
        pushButton_send = new QPushButton(groupBox);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        sizePolicy.setHeightForWidth(pushButton_send->sizePolicy().hasHeightForWidth());
        pushButton_send->setSizePolicy(sizePolicy);
        pushButton_send->setFont(font1);

        horizontalLayout_commandButton->addWidget(pushButton_send);

        pushButton_read = new QPushButton(groupBox);
        pushButton_read->setObjectName(QStringLiteral("pushButton_read"));
        sizePolicy.setHeightForWidth(pushButton_read->sizePolicy().hasHeightForWidth());
        pushButton_read->setSizePolicy(sizePolicy);
        pushButton_read->setFont(font1);

        horizontalLayout_commandButton->addWidget(pushButton_read);

        pushButton_sendRead = new QPushButton(groupBox);
        pushButton_sendRead->setObjectName(QStringLiteral("pushButton_sendRead"));
        sizePolicy.setHeightForWidth(pushButton_sendRead->sizePolicy().hasHeightForWidth());
        pushButton_sendRead->setSizePolicy(sizePolicy);
        pushButton_sendRead->setFont(font1);

        horizontalLayout_commandButton->addWidget(pushButton_sendRead);


        verticalLayout_command->addLayout(horizontalLayout_commandButton);


        horizontalLayout_control->addWidget(groupBox);


        verticalLayout_3->addWidget(ManualTestFrame);

        textBrowser_control = new QTextBrowser(LeftLayout);
        textBrowser_control->setObjectName(QStringLiteral("textBrowser_control"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(8);
        sizePolicy6.setHeightForWidth(textBrowser_control->sizePolicy().hasHeightForWidth());
        textBrowser_control->setSizePolicy(sizePolicy6);
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(false);
        font2.setWeight(50);
        textBrowser_control->setFont(font2);

        verticalLayout_3->addWidget(textBrowser_control);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        AutoTestFrame = new QGroupBox(LeftLayout);
        AutoTestFrame->setObjectName(QStringLiteral("AutoTestFrame"));
        sizePolicy3.setHeightForWidth(AutoTestFrame->sizePolicy().hasHeightForWidth());
        AutoTestFrame->setSizePolicy(sizePolicy3);
        AutoTestFrame->setMinimumSize(QSize(0, 75));
        horizontalLayout_autoTest = new QHBoxLayout(AutoTestFrame);
        horizontalLayout_autoTest->setSpacing(6);
        horizontalLayout_autoTest->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_autoTest->setObjectName(QStringLiteral("horizontalLayout_autoTest"));
        horizontalLayout_autoTest->setContentsMargins(0, 0, 0, 0);
        pushButton_AutoTest = new QPushButton(AutoTestFrame);
        pushButton_AutoTest->setObjectName(QStringLiteral("pushButton_AutoTest"));
        sizePolicy.setHeightForWidth(pushButton_AutoTest->sizePolicy().hasHeightForWidth());
        pushButton_AutoTest->setSizePolicy(sizePolicy);
        pushButton_AutoTest->setFont(font1);

        horizontalLayout_autoTest->addWidget(pushButton_AutoTest);

        verticalLayout_config = new QVBoxLayout();
        verticalLayout_config->setSpacing(6);
        verticalLayout_config->setObjectName(QStringLiteral("verticalLayout_config"));
        horizontalLayout_configButton = new QHBoxLayout();
        horizontalLayout_configButton->setSpacing(6);
        horizontalLayout_configButton->setObjectName(QStringLiteral("horizontalLayout_configButton"));
        pushButton_Connect = new QPushButton(AutoTestFrame);
        pushButton_Connect->setObjectName(QStringLiteral("pushButton_Connect"));
        sizePolicy.setHeightForWidth(pushButton_Connect->sizePolicy().hasHeightForWidth());
        pushButton_Connect->setSizePolicy(sizePolicy);
        pushButton_Connect->setFont(font1);

        horizontalLayout_configButton->addWidget(pushButton_Connect);

        pushButton_reset = new QPushButton(AutoTestFrame);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        sizePolicy.setHeightForWidth(pushButton_reset->sizePolicy().hasHeightForWidth());
        pushButton_reset->setSizePolicy(sizePolicy);
        pushButton_reset->setFont(font1);

        horizontalLayout_configButton->addWidget(pushButton_reset);

        pushButton_configure = new QPushButton(AutoTestFrame);
        pushButton_configure->setObjectName(QStringLiteral("pushButton_configure"));
        sizePolicy.setHeightForWidth(pushButton_configure->sizePolicy().hasHeightForWidth());
        pushButton_configure->setSizePolicy(sizePolicy);
        pushButton_configure->setFont(font1);

        horizontalLayout_configButton->addWidget(pushButton_configure);


        verticalLayout_config->addLayout(horizontalLayout_configButton);


        horizontalLayout_autoTest->addLayout(verticalLayout_config);


        verticalLayout_3->addWidget(AutoTestFrame);

        textBrowser = new QTextBrowser(LeftLayout);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy6.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy6);

        verticalLayout_3->addWidget(textBrowser);


        horizontalLayout->addWidget(LeftLayout);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        RightLayout = new QWidget(MainLayout);
        RightLayout->setObjectName(QStringLiteral("RightLayout"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(4);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(RightLayout->sizePolicy().hasHeightForWidth());
        RightLayout->setSizePolicy(sizePolicy7);
        horizontalLayout_3 = new QHBoxLayout(RightLayout);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tabWidget = new QTabWidget(RightLayout);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy7.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy7);
        tabMeas = new QWidget();
        tabMeas->setObjectName(QStringLiteral("tabMeas"));
        measGroupBox = new QGroupBox(tabMeas);
        measGroupBox->setObjectName(QStringLiteral("measGroupBox"));
        measGroupBox->setGeometry(QRect(10, 10, 300, 300));
        verticalLayout = new QVBoxLayout(measGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        measLabel = new QLabel(measGroupBox);
        measLabel->setObjectName(QStringLiteral("measLabel"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(measLabel->sizePolicy().hasHeightForWidth());
        measLabel->setSizePolicy(sizePolicy8);
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        measLabel->setFont(font3);

        verticalLayout->addWidget(measLabel);

        MeasFormLayout = new QFormLayout();
        MeasFormLayout->setSpacing(6);
        MeasFormLayout->setObjectName(QStringLiteral("MeasFormLayout"));
        EYE_WIDTH_chb = new QCheckBox(measGroupBox);
        EYE_WIDTH_chb->setObjectName(QStringLiteral("EYE_WIDTH_chb"));

        MeasFormLayout->setWidget(0, QFormLayout::LabelRole, EYE_WIDTH_chb);

        EYE_HEIGHT_chb = new QCheckBox(measGroupBox);
        EYE_HEIGHT_chb->setObjectName(QStringLiteral("EYE_HEIGHT_chb"));

        MeasFormLayout->setWidget(1, QFormLayout::LabelRole, EYE_HEIGHT_chb);

        EYE_HIGH_chb = new QCheckBox(measGroupBox);
        EYE_HIGH_chb->setObjectName(QStringLiteral("EYE_HIGH_chb"));

        MeasFormLayout->setWidget(2, QFormLayout::LabelRole, EYE_HIGH_chb);

        EYE_LOW_chb = new QCheckBox(measGroupBox);
        EYE_LOW_chb->setObjectName(QStringLiteral("EYE_LOW_chb"));
        EYE_LOW_chb->setChecked(false);
        EYE_LOW_chb->setAutoRepeat(false);
        EYE_LOW_chb->setTristate(false);

        MeasFormLayout->setWidget(3, QFormLayout::LabelRole, EYE_LOW_chb);

        EYE_AMPLITUDE_chb = new QCheckBox(measGroupBox);
        EYE_AMPLITUDE_chb->setObjectName(QStringLiteral("EYE_AMPLITUDE_chb"));

        MeasFormLayout->setWidget(4, QFormLayout::LabelRole, EYE_AMPLITUDE_chb);

        EYE_PCROSS_chb = new QCheckBox(measGroupBox);
        EYE_PCROSS_chb->setObjectName(QStringLiteral("EYE_PCROSS_chb"));

        MeasFormLayout->setWidget(5, QFormLayout::LabelRole, EYE_PCROSS_chb);

        EYE_NCROSS_chb = new QCheckBox(measGroupBox);
        EYE_NCROSS_chb->setObjectName(QStringLiteral("EYE_NCROSS_chb"));

        MeasFormLayout->setWidget(6, QFormLayout::LabelRole, EYE_NCROSS_chb);

        EYE_EXTICTRATIO_chb = new QCheckBox(measGroupBox);
        EYE_EXTICTRATIO_chb->setObjectName(QStringLiteral("EYE_EXTICTRATIO_chb"));

        MeasFormLayout->setWidget(7, QFormLayout::LabelRole, EYE_EXTICTRATIO_chb);

        EYE_QFACTOR_chb = new QCheckBox(measGroupBox);
        EYE_QFACTOR_chb->setObjectName(QStringLiteral("EYE_QFACTOR_chb"));

        MeasFormLayout->setWidget(8, QFormLayout::LabelRole, EYE_QFACTOR_chb);

        EYE_AOPTPWRDBM_chb = new QCheckBox(measGroupBox);
        EYE_AOPTPWRDBM_chb->setObjectName(QStringLiteral("EYE_AOPTPWRDBM_chb"));

        MeasFormLayout->setWidget(9, QFormLayout::LabelRole, EYE_AOPTPWRDBM_chb);

        EYE_WIDTH_le = new QLineEdit(measGroupBox);
        EYE_WIDTH_le->setObjectName(QStringLiteral("EYE_WIDTH_le"));

        MeasFormLayout->setWidget(0, QFormLayout::FieldRole, EYE_WIDTH_le);

        EYE_HEIGHT_le = new QLineEdit(measGroupBox);
        EYE_HEIGHT_le->setObjectName(QStringLiteral("EYE_HEIGHT_le"));

        MeasFormLayout->setWidget(1, QFormLayout::FieldRole, EYE_HEIGHT_le);

        EYE_HIGH_le = new QLineEdit(measGroupBox);
        EYE_HIGH_le->setObjectName(QStringLiteral("EYE_HIGH_le"));

        MeasFormLayout->setWidget(2, QFormLayout::FieldRole, EYE_HIGH_le);

        EYE_LOW_le = new QLineEdit(measGroupBox);
        EYE_LOW_le->setObjectName(QStringLiteral("EYE_LOW_le"));

        MeasFormLayout->setWidget(3, QFormLayout::FieldRole, EYE_LOW_le);

        EYE_AMPLITUDE_le = new QLineEdit(measGroupBox);
        EYE_AMPLITUDE_le->setObjectName(QStringLiteral("EYE_AMPLITUDE_le"));

        MeasFormLayout->setWidget(4, QFormLayout::FieldRole, EYE_AMPLITUDE_le);

        EYE_PCROSS_le = new QLineEdit(measGroupBox);
        EYE_PCROSS_le->setObjectName(QStringLiteral("EYE_PCROSS_le"));

        MeasFormLayout->setWidget(5, QFormLayout::FieldRole, EYE_PCROSS_le);

        EYE_NCROSS_le = new QLineEdit(measGroupBox);
        EYE_NCROSS_le->setObjectName(QStringLiteral("EYE_NCROSS_le"));

        MeasFormLayout->setWidget(6, QFormLayout::FieldRole, EYE_NCROSS_le);

        EYE_EXTICTRATIO_le = new QLineEdit(measGroupBox);
        EYE_EXTICTRATIO_le->setObjectName(QStringLiteral("EYE_EXTICTRATIO_le"));

        MeasFormLayout->setWidget(7, QFormLayout::FieldRole, EYE_EXTICTRATIO_le);

        EYE_QFACTOR_le = new QLineEdit(measGroupBox);
        EYE_QFACTOR_le->setObjectName(QStringLiteral("EYE_QFACTOR_le"));

        MeasFormLayout->setWidget(8, QFormLayout::FieldRole, EYE_QFACTOR_le);

        EYE_AOPTPWRDBM_le = new QLineEdit(measGroupBox);
        EYE_AOPTPWRDBM_le->setObjectName(QStringLiteral("EYE_AOPTPWRDBM_le"));

        MeasFormLayout->setWidget(9, QFormLayout::FieldRole, EYE_AOPTPWRDBM_le);


        verticalLayout->addLayout(MeasFormLayout);

        tabWidget->addTab(tabMeas, QString());
        tabVert = new QWidget();
        tabVert->setObjectName(QStringLiteral("tabVert"));
        verticalGroupBox_vert = new QGroupBox(tabVert);
        verticalGroupBox_vert->setObjectName(QStringLiteral("verticalGroupBox_vert"));
        verticalGroupBox_vert->setGeometry(QRect(10, 10, 300, 200));
        verticalLayout_2 = new QVBoxLayout(verticalGroupBox_vert);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        label_selCh = new QLabel(verticalGroupBox_vert);
        label_selCh->setObjectName(QStringLiteral("label_selCh"));
        sizePolicy8.setHeightForWidth(label_selCh->sizePolicy().hasHeightForWidth());
        label_selCh->setSizePolicy(sizePolicy8);
        label_selCh->setFont(font3);

        verticalLayout_2->addWidget(label_selCh);

        GroupBox_selCh = new QGroupBox(verticalGroupBox_vert);
        GroupBox_selCh->setObjectName(QStringLiteral("GroupBox_selCh"));
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(GroupBox_selCh->sizePolicy().hasHeightForWidth());
        GroupBox_selCh->setSizePolicy(sizePolicy9);
        horizontalLayout_selCh = new QHBoxLayout(GroupBox_selCh);
        horizontalLayout_selCh->setSpacing(6);
        horizontalLayout_selCh->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_selCh->setObjectName(QStringLiteral("horizontalLayout_selCh"));
        horizontalLayout_selCh->setContentsMargins(10, 10, 10, 10);
        comboBox_selCh = new QComboBox(GroupBox_selCh);
        comboBox_selCh->setObjectName(QStringLiteral("comboBox_selCh"));
        sizePolicy9.setHeightForWidth(comboBox_selCh->sizePolicy().hasHeightForWidth());
        comboBox_selCh->setSizePolicy(sizePolicy9);
        comboBox_selCh->setMaxVisibleItems(10);

        horizontalLayout_selCh->addWidget(comboBox_selCh);

        checkBox_state = new QCheckBox(GroupBox_selCh);
        checkBox_state->setObjectName(QStringLiteral("checkBox_state"));
        sizePolicy9.setHeightForWidth(checkBox_state->sizePolicy().hasHeightForWidth());
        checkBox_state->setSizePolicy(sizePolicy9);

        horizontalLayout_selCh->addWidget(checkBox_state);


        verticalLayout_2->addWidget(GroupBox_selCh);

        label_setup = new QLabel(verticalGroupBox_vert);
        label_setup->setObjectName(QStringLiteral("label_setup"));
        sizePolicy8.setHeightForWidth(label_setup->sizePolicy().hasHeightForWidth());
        label_setup->setSizePolicy(sizePolicy8);
        label_setup->setFont(font3);

        verticalLayout_2->addWidget(label_setup);

        GroupBox_setup = new QGroupBox(verticalGroupBox_vert);
        GroupBox_setup->setObjectName(QStringLiteral("GroupBox_setup"));
        formLayout_2 = new QFormLayout(GroupBox_setup);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(10, 10, 10, 10);
        label_wlength = new QLabel(GroupBox_setup);
        label_wlength->setObjectName(QStringLiteral("label_wlength"));
        sizePolicy1.setHeightForWidth(label_wlength->sizePolicy().hasHeightForWidth());
        label_wlength->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_wlength);

        comboBox_wl = new QComboBox(GroupBox_setup);
        comboBox_wl->setObjectName(QStringLiteral("comboBox_wl"));
        sizePolicy9.setHeightForWidth(comboBox_wl->sizePolicy().hasHeightForWidth());
        comboBox_wl->setSizePolicy(sizePolicy9);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox_wl);

        label_filter = new QLabel(GroupBox_setup);
        label_filter->setObjectName(QStringLiteral("label_filter"));
        sizePolicy1.setHeightForWidth(label_filter->sizePolicy().hasHeightForWidth());
        label_filter->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_filter);

        comboBox_filter = new QComboBox(GroupBox_setup);
        comboBox_filter->setObjectName(QStringLiteral("comboBox_filter"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, comboBox_filter);


        verticalLayout_2->addWidget(GroupBox_setup);

        tabWidget->addTab(tabVert, QString());
        tab_mask = new QWidget();
        tab_mask->setObjectName(QStringLiteral("tab_mask"));
        verticalGroupBox_mask = new QGroupBox(tab_mask);
        verticalGroupBox_mask->setObjectName(QStringLiteral("verticalGroupBox_mask"));
        verticalGroupBox_mask->setGeometry(QRect(10, 10, 300, 200));
        verticalLayout_4 = new QVBoxLayout(verticalGroupBox_mask);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, 10, 10, 10);
        label_src = new QLabel(verticalGroupBox_mask);
        label_src->setObjectName(QStringLiteral("label_src"));
        sizePolicy8.setHeightForWidth(label_src->sizePolicy().hasHeightForWidth());
        label_src->setSizePolicy(sizePolicy8);
        label_src->setFont(font3);

        verticalLayout_4->addWidget(label_src);

        GroupBox_src = new QGroupBox(verticalGroupBox_mask);
        GroupBox_src->setObjectName(QStringLiteral("GroupBox_src"));
        sizePolicy9.setHeightForWidth(GroupBox_src->sizePolicy().hasHeightForWidth());
        GroupBox_src->setSizePolicy(sizePolicy9);
        horizontalLayout_selCh_2 = new QHBoxLayout(GroupBox_src);
        horizontalLayout_selCh_2->setSpacing(6);
        horizontalLayout_selCh_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_selCh_2->setObjectName(QStringLiteral("horizontalLayout_selCh_2"));
        horizontalLayout_selCh_2->setContentsMargins(10, 10, 10, 10);
        comboBox_src = new QComboBox(GroupBox_src);
        comboBox_src->setObjectName(QStringLiteral("comboBox_src"));
        sizePolicy9.setHeightForWidth(comboBox_src->sizePolicy().hasHeightForWidth());
        comboBox_src->setSizePolicy(sizePolicy9);
        comboBox_src->setMaxVisibleItems(10);

        horizontalLayout_selCh_2->addWidget(comboBox_src);

        checkBox_enable = new QCheckBox(GroupBox_src);
        checkBox_enable->setObjectName(QStringLiteral("checkBox_enable"));
        sizePolicy9.setHeightForWidth(checkBox_enable->sizePolicy().hasHeightForWidth());
        checkBox_enable->setSizePolicy(sizePolicy9);

        horizontalLayout_selCh_2->addWidget(checkBox_enable);


        verticalLayout_4->addWidget(GroupBox_src);

        label_maskSetup = new QLabel(verticalGroupBox_mask);
        label_maskSetup->setObjectName(QStringLiteral("label_maskSetup"));
        sizePolicy8.setHeightForWidth(label_maskSetup->sizePolicy().hasHeightForWidth());
        label_maskSetup->setSizePolicy(sizePolicy8);
        label_maskSetup->setFont(font3);

        verticalLayout_4->addWidget(label_maskSetup);

        GroupBox_maskSetup = new QGroupBox(verticalGroupBox_mask);
        GroupBox_maskSetup->setObjectName(QStringLiteral("GroupBox_maskSetup"));
        formLayout_3 = new QFormLayout(GroupBox_maskSetup);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setContentsMargins(10, 10, 10, 10);
        label_maskStd = new QLabel(GroupBox_maskSetup);
        label_maskStd->setObjectName(QStringLiteral("label_maskStd"));
        sizePolicy1.setHeightForWidth(label_maskStd->sizePolicy().hasHeightForWidth());
        label_maskStd->setSizePolicy(sizePolicy1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_maskStd);

        comboBox_maskStd = new QComboBox(GroupBox_maskSetup);
        comboBox_maskStd->setObjectName(QStringLiteral("comboBox_maskStd"));
        sizePolicy9.setHeightForWidth(comboBox_maskStd->sizePolicy().hasHeightForWidth());
        comboBox_maskStd->setSizePolicy(sizePolicy9);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, comboBox_maskStd);


        verticalLayout_4->addWidget(GroupBox_maskSetup);

        tabWidget->addTab(tab_mask, QString());
        tab_acq = new QWidget();
        tab_acq->setObjectName(QStringLiteral("tab_acq"));
        verticalGroupBox_acq = new QGroupBox(tab_acq);
        verticalGroupBox_acq->setObjectName(QStringLiteral("verticalGroupBox_acq"));
        verticalGroupBox_acq->setGeometry(QRect(10, 10, 300, 200));
        verticalLayout_5 = new QVBoxLayout(verticalGroupBox_acq);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(10, 10, 10, 10);
        label_stopAfter = new QLabel(verticalGroupBox_acq);
        label_stopAfter->setObjectName(QStringLiteral("label_stopAfter"));
        sizePolicy8.setHeightForWidth(label_stopAfter->sizePolicy().hasHeightForWidth());
        label_stopAfter->setSizePolicy(sizePolicy8);
        label_stopAfter->setFont(font3);

        verticalLayout_5->addWidget(label_stopAfter);

        GroupBox_stopAfter = new QGroupBox(verticalGroupBox_acq);
        GroupBox_stopAfter->setObjectName(QStringLiteral("GroupBox_stopAfter"));
        formLayout_4 = new QFormLayout(GroupBox_stopAfter);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setContentsMargins(10, 10, 10, 10);
        label_mode = new QLabel(GroupBox_stopAfter);
        label_mode->setObjectName(QStringLiteral("label_mode"));
        sizePolicy1.setHeightForWidth(label_mode->sizePolicy().hasHeightForWidth());
        label_mode->setSizePolicy(sizePolicy1);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_mode);

        comboBox_mode = new QComboBox(GroupBox_stopAfter);
        comboBox_mode->setObjectName(QStringLiteral("comboBox_mode"));
        sizePolicy9.setHeightForWidth(comboBox_mode->sizePolicy().hasHeightForWidth());
        comboBox_mode->setSizePolicy(sizePolicy9);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, comboBox_mode);

        label_cond = new QLabel(GroupBox_stopAfter);
        label_cond->setObjectName(QStringLiteral("label_cond"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_cond);

        comboBox_cond = new QComboBox(GroupBox_stopAfter);
        comboBox_cond->setObjectName(QStringLiteral("comboBox_cond"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, comboBox_cond);

        label_count = new QLabel(GroupBox_stopAfter);
        label_count->setObjectName(QStringLiteral("label_count"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_count);

        lineEdit_count = new QLineEdit(GroupBox_stopAfter);
        lineEdit_count->setObjectName(QStringLiteral("lineEdit_count"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, lineEdit_count);


        verticalLayout_5->addWidget(GroupBox_stopAfter);

        tabWidget->addTab(tab_acq, QString());
        tab_trig = new QWidget();
        tab_trig->setObjectName(QStringLiteral("tab_trig"));
        verticalGroupBox_trig = new QGroupBox(tab_trig);
        verticalGroupBox_trig->setObjectName(QStringLiteral("verticalGroupBox_trig"));
        verticalGroupBox_trig->setGeometry(QRect(10, 10, 300, 200));
        verticalLayout_6 = new QVBoxLayout(verticalGroupBox_trig);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(10, 10, 10, 10);
        label_trigSrc = new QLabel(verticalGroupBox_trig);
        label_trigSrc->setObjectName(QStringLiteral("label_trigSrc"));
        sizePolicy8.setHeightForWidth(label_trigSrc->sizePolicy().hasHeightForWidth());
        label_trigSrc->setSizePolicy(sizePolicy8);
        label_trigSrc->setFont(font3);

        verticalLayout_6->addWidget(label_trigSrc);

        GroupBox_trigSrc = new QGroupBox(verticalGroupBox_trig);
        GroupBox_trigSrc->setObjectName(QStringLiteral("GroupBox_trigSrc"));
        sizePolicy9.setHeightForWidth(GroupBox_trigSrc->sizePolicy().hasHeightForWidth());
        GroupBox_trigSrc->setSizePolicy(sizePolicy9);
        horizontalLayout_selCh_3 = new QHBoxLayout(GroupBox_trigSrc);
        horizontalLayout_selCh_3->setSpacing(6);
        horizontalLayout_selCh_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_selCh_3->setObjectName(QStringLiteral("horizontalLayout_selCh_3"));
        horizontalLayout_selCh_3->setContentsMargins(10, 10, 10, 10);
        label_trigSrc_2 = new QLabel(GroupBox_trigSrc);
        label_trigSrc_2->setObjectName(QStringLiteral("label_trigSrc_2"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(label_trigSrc_2->sizePolicy().hasHeightForWidth());
        label_trigSrc_2->setSizePolicy(sizePolicy10);

        horizontalLayout_selCh_3->addWidget(label_trigSrc_2);

        comboBox_trigSrc = new QComboBox(GroupBox_trigSrc);
        comboBox_trigSrc->setObjectName(QStringLiteral("comboBox_trigSrc"));
        sizePolicy1.setHeightForWidth(comboBox_trigSrc->sizePolicy().hasHeightForWidth());
        comboBox_trigSrc->setSizePolicy(sizePolicy1);

        horizontalLayout_selCh_3->addWidget(comboBox_trigSrc);


        verticalLayout_6->addWidget(GroupBox_trigSrc);

        label_clkrecSetup = new QLabel(verticalGroupBox_trig);
        label_clkrecSetup->setObjectName(QStringLiteral("label_clkrecSetup"));
        sizePolicy8.setHeightForWidth(label_clkrecSetup->sizePolicy().hasHeightForWidth());
        label_clkrecSetup->setSizePolicy(sizePolicy8);
        label_clkrecSetup->setFont(font3);

        verticalLayout_6->addWidget(label_clkrecSetup);

        GroupBox_clkrec = new QGroupBox(verticalGroupBox_trig);
        GroupBox_clkrec->setObjectName(QStringLiteral("GroupBox_clkrec"));
        formLayout_5 = new QFormLayout(GroupBox_clkrec);
        formLayout_5->setSpacing(6);
        formLayout_5->setContentsMargins(11, 11, 11, 11);
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        formLayout_5->setContentsMargins(10, 10, 10, 10);
        label_clkrecSrc = new QLabel(GroupBox_clkrec);
        label_clkrecSrc->setObjectName(QStringLiteral("label_clkrecSrc"));
        sizePolicy1.setHeightForWidth(label_clkrecSrc->sizePolicy().hasHeightForWidth());
        label_clkrecSrc->setSizePolicy(sizePolicy1);

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_clkrecSrc);

        comboBox_clkrecSrc = new QComboBox(GroupBox_clkrec);
        comboBox_clkrecSrc->setObjectName(QStringLiteral("comboBox_clkrecSrc"));
        sizePolicy9.setHeightForWidth(comboBox_clkrecSrc->sizePolicy().hasHeightForWidth());
        comboBox_clkrecSrc->setSizePolicy(sizePolicy9);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, comboBox_clkrecSrc);

        label_clkrecVal = new QLabel(GroupBox_clkrec);
        label_clkrecVal->setObjectName(QStringLiteral("label_clkrecVal"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_clkrecVal);

        comboBox_clkrecVal = new QComboBox(GroupBox_clkrec);
        comboBox_clkrecVal->setObjectName(QStringLiteral("comboBox_clkrecVal"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, comboBox_clkrecVal);


        verticalLayout_6->addWidget(GroupBox_clkrec);

        tabWidget->addTab(tab_trig, QString());

        horizontalLayout_3->addWidget(tabWidget);


        horizontalLayout->addWidget(RightLayout);


        horizontalLayout_2->addWidget(MainLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1600, 23));
        menuOption_O = new QMenu(menuBar);
        menuOption_O->setObjectName(QStringLiteral("menuOption_O"));
        menuHelp_H = new QMenu(menuBar);
        menuHelp_H->setObjectName(QStringLiteral("menuHelp_H"));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QStringLiteral("menuFile_F"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuOption_O->menuAction());
        menuBar->addAction(menuHelp_H->menuAction());
        menuOption_O->addAction(actionDatabase_D);
        menuOption_O->addAction(actionMeasurment_M);
        menuFile_F->addAction(actionNew_N);
        menuFile_F->addAction(actionOpen_O);
        menuFile_F->addAction(actionClose_C);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_O->setText(QApplication::translate("MainWindow", "Open(&O)", 0));
        actionClose_C->setText(QApplication::translate("MainWindow", "Close(&C)", 0));
        actionNew_N->setText(QApplication::translate("MainWindow", "New(&N)", 0));
        actionDatabase_D->setText(QApplication::translate("MainWindow", "Database(&D)", 0));
        actionMeasurment_M->setText(QApplication::translate("MainWindow", "Measurment(&M)", 0));
        pushButton_connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        pushButton_disconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        pushButton_send->setText(QApplication::translate("MainWindow", "Send Command", 0));
        pushButton_read->setText(QApplication::translate("MainWindow", "Read Response", 0));
        pushButton_sendRead->setText(QApplication::translate("MainWindow", "Send and Read", 0));
        pushButton_AutoTest->setText(QApplication::translate("MainWindow", "Auto Test", 0));
        pushButton_Connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        pushButton_reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        pushButton_configure->setText(QApplication::translate("MainWindow", "Configure", 0));
        measLabel->setText(QApplication::translate("MainWindow", "Select Meas", 0));
        EYE_WIDTH_chb->setText(QApplication::translate("MainWindow", "EYE_WIDTH", 0));
        EYE_HEIGHT_chb->setText(QApplication::translate("MainWindow", "EYE_HEIGHT", 0));
        EYE_HIGH_chb->setText(QApplication::translate("MainWindow", "EYE_HIGH", 0));
        EYE_LOW_chb->setText(QApplication::translate("MainWindow", "EYE_LOW", 0));
        EYE_AMPLITUDE_chb->setText(QApplication::translate("MainWindow", "EYE_AMPLITUDE", 0));
        EYE_PCROSS_chb->setText(QApplication::translate("MainWindow", "EYE_PCROSS", 0));
        EYE_NCROSS_chb->setText(QApplication::translate("MainWindow", "EYE_NCROSS", 0));
        EYE_EXTICTRATIO_chb->setText(QApplication::translate("MainWindow", "EYE_EXTICTRATIO", 0));
        EYE_QFACTOR_chb->setText(QApplication::translate("MainWindow", "EYE_QFACTOR", 0));
        EYE_AOPTPWRDBM_chb->setText(QApplication::translate("MainWindow", "EYE_AOPTPWRDBM", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabMeas), QApplication::translate("MainWindow", "Meas", 0));
        label_selCh->setText(QApplication::translate("MainWindow", "Select Channel", 0));
        comboBox_selCh->clear();
        comboBox_selCh->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Channel 1", 0)
         << QApplication::translate("MainWindow", "Channel 2", 0)
         << QApplication::translate("MainWindow", "Channel 3", 0)
         << QApplication::translate("MainWindow", "Channel 4", 0)
         << QApplication::translate("MainWindow", "Channel 5", 0)
         << QApplication::translate("MainWindow", "Channel 6", 0)
         << QApplication::translate("MainWindow", "Channel 7", 0)
         << QApplication::translate("MainWindow", "Channel 8", 0)
        );
        checkBox_state->setText(QApplication::translate("MainWindow", "ON", 0));
        label_setup->setText(QApplication::translate("MainWindow", "Setup", 0));
        label_wlength->setText(QApplication::translate("MainWindow", "Wave Length", 0));
        comboBox_wl->clear();
        comboBox_wl->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1550", 0)
        );
        label_filter->setText(QApplication::translate("MainWindow", "Filter", 0));
        comboBox_filter->clear();
        comboBox_filter->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "OC-48/STM-16", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tabVert), QApplication::translate("MainWindow", "Vert", 0));
        label_src->setText(QApplication::translate("MainWindow", "Source", 0));
        comboBox_src->clear();
        comboBox_src->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Channel 1 Main", 0)
         << QApplication::translate("MainWindow", "Channel 2 Main", 0)
         << QApplication::translate("MainWindow", "Channel 3 Main", 0)
         << QApplication::translate("MainWindow", "Channel 4 Main", 0)
         << QApplication::translate("MainWindow", "Channel 5 Main", 0)
         << QApplication::translate("MainWindow", "Channel 6 Main", 0)
         << QApplication::translate("MainWindow", "Channel 7 Main", 0)
         << QApplication::translate("MainWindow", "Channel 8 Main", 0)
        );
        checkBox_enable->setText(QApplication::translate("MainWindow", "Eable Mask Counts", 0));
        label_maskSetup->setText(QApplication::translate("MainWindow", "Setup", 0));
        label_maskStd->setText(QApplication::translate("MainWindow", "Mask Standard", 0));
        comboBox_maskStd->clear();
        comboBox_maskStd->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "OC-48/STM-16", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_mask), QApplication::translate("MainWindow", "Mask", 0));
        label_stopAfter->setText(QApplication::translate("MainWindow", "Stop After", 0));
        label_mode->setText(QApplication::translate("MainWindow", "Mode", 0));
        comboBox_mode->clear();
        comboBox_mode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Condition", 0)
        );
        label_cond->setText(QApplication::translate("MainWindow", "Condition", 0));
        comboBox_cond->clear();
        comboBox_cond->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Mask Wave Form", 0)
        );
        label_count->setText(QApplication::translate("MainWindow", "Count", 0));
        lineEdit_count->setText(QApplication::translate("MainWindow", "2000", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_acq), QApplication::translate("MainWindow", "Acq", 0));
        label_trigSrc->setText(QApplication::translate("MainWindow", "Trigger Source", 0));
        label_trigSrc_2->setText(QApplication::translate("MainWindow", "Trigger Source", 0));
        comboBox_trigSrc->clear();
        comboBox_trigSrc->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Clock Recover", 0)
        );
        label_clkrecSetup->setText(QApplication::translate("MainWindow", "Clock Recover Setup", 0));
        label_clkrecSrc->setText(QApplication::translate("MainWindow", "Clock Recover Source", 0));
        comboBox_clkrecSrc->clear();
        comboBox_clkrecSrc->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Channel 1", 0)
         << QApplication::translate("MainWindow", "Channel 2", 0)
         << QApplication::translate("MainWindow", "Channel 3", 0)
         << QApplication::translate("MainWindow", "Channel 4", 0)
         << QApplication::translate("MainWindow", "Channel 5", 0)
         << QApplication::translate("MainWindow", "Channel 6", 0)
         << QApplication::translate("MainWindow", "Channel 7", 0)
         << QApplication::translate("MainWindow", "Channel 8", 0)
        );
        label_clkrecVal->setText(QApplication::translate("MainWindow", "Clock Recover Value", 0));
        comboBox_clkrecVal->clear();
        comboBox_clkrecVal->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "OC-48/STM-16", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_trig), QApplication::translate("MainWindow", "Trig", 0));
        menuOption_O->setTitle(QApplication::translate("MainWindow", "Option(&O)", 0));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "Help(&H)", 0));
        menuFile_F->setTitle(QApplication::translate("MainWindow", "File(&F)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
