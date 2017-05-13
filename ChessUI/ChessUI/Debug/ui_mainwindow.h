/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView_10;
    QGraphicsView *graphicsView_11;
    QGraphicsView *graphicsView_17;
    QGraphicsView *graphicsView_18;
    QGraphicsView *graphicsView_19;
    QGraphicsView *graphicsView_16;
    QGraphicsView *graphicsView_20;
    QGraphicsView *graphicsView_29;
    QGraphicsView *graphicsView_23;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QGraphicsView *graphicsView_21;
    QGraphicsView *graphicsView_9;
    QGraphicsView *graphicsView_14;
    QGraphicsView *graphicsView_15;
    QGraphicsView *graphicsView_13;
    QGraphicsView *graphicsView_12;
    QGraphicsView *graphicsView_4;
    QGraphicsView *graphicsView_6;
    QGraphicsView *graphicsView_5;
    QGraphicsView *graphicsView_8;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_28;
    QGraphicsView *graphicsView_22;
    QGraphicsView *graphicsView_26;
    QGraphicsView *graphicsView_25;
    QGraphicsView *graphicsView_24;
    QGraphicsView *graphicsView_27;
    QGraphicsView *graphicsView_30;
    QGraphicsView *graphicsView_31;
    QGraphicsView *graphicsView_66;
    QGraphicsView *graphicsView_65;
    QGraphicsView *graphicsView_61;
    QGraphicsView *graphicsView_55;
    QGraphicsView *graphicsView_59;
    QGraphicsView *graphicsView_60;
    QGraphicsView *graphicsView_57;
    QGraphicsView *graphicsView_58;
    QGraphicsView *graphicsView_49;
    QGraphicsView *graphicsView_41;
    QGraphicsView *graphicsView_51;
    QGraphicsView *graphicsView_50;
    QGraphicsView *graphicsView_44;
    QGraphicsView *graphicsView_43;
    QGraphicsView *graphicsView_53;
    QGraphicsView *graphicsView_54;
    QGraphicsView *graphicsView_48;
    QGraphicsView *graphicsView_45;
    QGraphicsView *graphicsView_52;
    QGraphicsView *graphicsView_56;
    QGraphicsView *graphicsView_46;
    QGraphicsView *graphicsView_47;
    QGraphicsView *graphicsView_37;
    QGraphicsView *graphicsView_34;
    QGraphicsView *graphicsView_33;
    QGraphicsView *graphicsView_39;
    QGraphicsView *graphicsView_36;
    QGraphicsView *graphicsView_35;
    QGraphicsView *graphicsView_32;
    QGraphicsView *graphicsView_38;
    QGraphicsView *graphicsView_67;
    QGraphicsView *graphicsView_40;
    QGraphicsView *graphicsView_42;
    QGraphicsView *graphicsView_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QGraphicsView *graphicsView_7;
    QFrame *line;
    QPushButton *initButton;
    QPushButton *ok_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(761, 543);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(490, 10, 191, 431));
        tableWidget->setMaximumSize(QSize(250, 16777215));
        tableWidget->setLineWidth(1);
        tableWidget->setColumnCount(3);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(80, 450, 601, 31));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1, Qt::AlignHCenter);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 0, 4, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 3, 1, 1);

        comboBox_3 = new QComboBox(gridLayoutWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 0, 5, 1, 1);

        comboBox_4 = new QComboBox(gridLayoutWidget);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 0, 6, 1, 1);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 10, 421, 431));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView_10 = new QGraphicsView(layoutWidget);
        graphicsView_10->setObjectName(QStringLiteral("graphicsView_10"));
        graphicsView_10->setMaximumSize(QSize(50, 50));
        graphicsView_10->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_10, 1, 9, 1, 1);

        graphicsView_11 = new QGraphicsView(layoutWidget);
        graphicsView_11->setObjectName(QStringLiteral("graphicsView_11"));
        graphicsView_11->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_11, 1, 4, 1, 1);

        graphicsView_17 = new QGraphicsView(layoutWidget);
        graphicsView_17->setObjectName(QStringLiteral("graphicsView_17"));
        graphicsView_17->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_17, 6, 3, 1, 1);

        graphicsView_18 = new QGraphicsView(layoutWidget);
        graphicsView_18->setObjectName(QStringLiteral("graphicsView_18"));
        graphicsView_18->setMaximumSize(QSize(50, 50));
        graphicsView_18->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_18, 5, 3, 1, 1);

        graphicsView_19 = new QGraphicsView(layoutWidget);
        graphicsView_19->setObjectName(QStringLiteral("graphicsView_19"));
        graphicsView_19->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_19, 4, 3, 1, 1);

        graphicsView_16 = new QGraphicsView(layoutWidget);
        graphicsView_16->setObjectName(QStringLiteral("graphicsView_16"));
        graphicsView_16->setMaximumSize(QSize(50, 50));
        graphicsView_16->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_16, 7, 3, 1, 1);

        graphicsView_20 = new QGraphicsView(layoutWidget);
        graphicsView_20->setObjectName(QStringLiteral("graphicsView_20"));
        graphicsView_20->setMaximumSize(QSize(50, 50));
        graphicsView_20->setStyleSheet(QLatin1String("background-color: rgb(108, 108, 108);\n"
""));

        gridLayout->addWidget(graphicsView_20, 3, 3, 1, 1);

        graphicsView_29 = new QGraphicsView(layoutWidget);
        graphicsView_29->setObjectName(QStringLiteral("graphicsView_29"));
        graphicsView_29->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_29, 7, 4, 1, 1);

        graphicsView_23 = new QGraphicsView(layoutWidget);
        graphicsView_23->setObjectName(QStringLiteral("graphicsView_23"));
        graphicsView_23->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_23, 2, 5, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_4, 0, Qt::AlignHCenter);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QLatin1String("font: 26pt \"Tahoma\";\n"
""));

        verticalLayout->addWidget(label_5, 0, Qt::AlignHCenter);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_6, 0, Qt::AlignHCenter);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setStyleSheet(QLatin1String("font: 26pt \"Tahoma\";\n"
""));

        verticalLayout->addWidget(label_7, 0, Qt::AlignHCenter);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_8, 0, Qt::AlignHCenter);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_9, 0, Qt::AlignHCenter);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_10, 0, Qt::AlignHCenter);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        verticalLayout->addWidget(label_11, 0, Qt::AlignHCenter);


        gridLayout->addLayout(verticalLayout, 1, 0, 8, 1);

        graphicsView_21 = new QGraphicsView(layoutWidget);
        graphicsView_21->setObjectName(QStringLiteral("graphicsView_21"));
        graphicsView_21->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_21, 2, 3, 1, 1);

        graphicsView_9 = new QGraphicsView(layoutWidget);
        graphicsView_9->setObjectName(QStringLiteral("graphicsView_9"));
        graphicsView_9->setMaximumSize(QSize(50, 50));
        graphicsView_9->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_9, 8, 1, 1, 1);

        graphicsView_14 = new QGraphicsView(layoutWidget);
        graphicsView_14->setObjectName(QStringLiteral("graphicsView_14"));
        graphicsView_14->setMaximumSize(QSize(50, 50));
        graphicsView_14->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_14, 1, 7, 1, 1);

        graphicsView_15 = new QGraphicsView(layoutWidget);
        graphicsView_15->setObjectName(QStringLiteral("graphicsView_15"));
        graphicsView_15->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_15, 1, 6, 1, 1);

        graphicsView_13 = new QGraphicsView(layoutWidget);
        graphicsView_13->setObjectName(QStringLiteral("graphicsView_13"));
        graphicsView_13->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_13, 1, 8, 1, 1);

        graphicsView_12 = new QGraphicsView(layoutWidget);
        graphicsView_12->setObjectName(QStringLiteral("graphicsView_12"));
        graphicsView_12->setMaximumSize(QSize(50, 50));
        graphicsView_12->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_12, 1, 5, 1, 1);

        graphicsView_4 = new QGraphicsView(layoutWidget);
        graphicsView_4->setObjectName(QStringLiteral("graphicsView_4"));
        graphicsView_4->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_4, 3, 1, 1, 1);

        graphicsView_6 = new QGraphicsView(layoutWidget);
        graphicsView_6->setObjectName(QStringLiteral("graphicsView_6"));
        graphicsView_6->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_6, 5, 1, 1, 1);

        graphicsView_5 = new QGraphicsView(layoutWidget);
        graphicsView_5->setObjectName(QStringLiteral("graphicsView_5"));
        graphicsView_5->setMaximumSize(QSize(50, 50));
        graphicsView_5->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_5, 4, 1, 1, 1);

        graphicsView_8 = new QGraphicsView(layoutWidget);
        graphicsView_8->setObjectName(QStringLiteral("graphicsView_8"));
        graphicsView_8->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_8, 7, 1, 1, 1);

        graphicsView_2 = new QGraphicsView(layoutWidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setMaximumSize(QSize(50, 50));
        graphicsView_2->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_2, 1, 3, 1, 1);

        graphicsView = new QGraphicsView(layoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView, 1, 1, 1, 1);

        graphicsView_28 = new QGraphicsView(layoutWidget);
        graphicsView_28->setObjectName(QStringLiteral("graphicsView_28"));
        graphicsView_28->setMaximumSize(QSize(50, 50));
        graphicsView_28->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_28, 6, 4, 1, 1);

        graphicsView_22 = new QGraphicsView(layoutWidget);
        graphicsView_22->setObjectName(QStringLiteral("graphicsView_22"));
        graphicsView_22->setMaximumSize(QSize(50, 50));
        graphicsView_22->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_22, 3, 5, 1, 1);

        graphicsView_26 = new QGraphicsView(layoutWidget);
        graphicsView_26->setObjectName(QStringLiteral("graphicsView_26"));
        graphicsView_26->setMaximumSize(QSize(50, 50));
        graphicsView_26->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_26, 4, 4, 1, 1);

        graphicsView_25 = new QGraphicsView(layoutWidget);
        graphicsView_25->setObjectName(QStringLiteral("graphicsView_25"));
        graphicsView_25->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_25, 3, 4, 1, 1);

        graphicsView_24 = new QGraphicsView(layoutWidget);
        graphicsView_24->setObjectName(QStringLiteral("graphicsView_24"));
        graphicsView_24->setMaximumSize(QSize(50, 50));
        graphicsView_24->setStyleSheet(QLatin1String("background-color: rgb(108, 108, 108);\n"
""));

        gridLayout->addWidget(graphicsView_24, 2, 4, 1, 1);

        graphicsView_27 = new QGraphicsView(layoutWidget);
        graphicsView_27->setObjectName(QStringLiteral("graphicsView_27"));
        graphicsView_27->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_27, 5, 4, 1, 1);

        graphicsView_30 = new QGraphicsView(layoutWidget);
        graphicsView_30->setObjectName(QStringLiteral("graphicsView_30"));
        graphicsView_30->setMaximumSize(QSize(50, 50));
        graphicsView_30->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_30, 8, 4, 1, 1);

        graphicsView_31 = new QGraphicsView(layoutWidget);
        graphicsView_31->setObjectName(QStringLiteral("graphicsView_31"));
        graphicsView_31->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_31, 8, 3, 1, 1);

        graphicsView_66 = new QGraphicsView(layoutWidget);
        graphicsView_66->setObjectName(QStringLiteral("graphicsView_66"));
        graphicsView_66->setMaximumSize(QSize(50, 50));
        graphicsView_66->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_66, 7, 9, 1, 1);

        graphicsView_65 = new QGraphicsView(layoutWidget);
        graphicsView_65->setObjectName(QStringLiteral("graphicsView_65"));
        graphicsView_65->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_65, 6, 9, 1, 1);

        graphicsView_61 = new QGraphicsView(layoutWidget);
        graphicsView_61->setObjectName(QStringLiteral("graphicsView_61"));
        graphicsView_61->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_61, 4, 5, 1, 1);

        graphicsView_55 = new QGraphicsView(layoutWidget);
        graphicsView_55->setObjectName(QStringLiteral("graphicsView_55"));
        graphicsView_55->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_55, 7, 6, 1, 1);

        graphicsView_59 = new QGraphicsView(layoutWidget);
        graphicsView_59->setObjectName(QStringLiteral("graphicsView_59"));
        graphicsView_59->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_59, 6, 5, 1, 1);

        graphicsView_60 = new QGraphicsView(layoutWidget);
        graphicsView_60->setObjectName(QStringLiteral("graphicsView_60"));
        graphicsView_60->setMaximumSize(QSize(50, 50));
        graphicsView_60->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_60, 5, 5, 1, 1);

        graphicsView_57 = new QGraphicsView(layoutWidget);
        graphicsView_57->setObjectName(QStringLiteral("graphicsView_57"));
        graphicsView_57->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_57, 8, 5, 1, 1);

        graphicsView_58 = new QGraphicsView(layoutWidget);
        graphicsView_58->setObjectName(QStringLiteral("graphicsView_58"));
        graphicsView_58->setMaximumSize(QSize(50, 50));
        graphicsView_58->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_58, 7, 5, 1, 1);

        graphicsView_49 = new QGraphicsView(layoutWidget);
        graphicsView_49->setObjectName(QStringLiteral("graphicsView_49"));
        graphicsView_49->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_49, 2, 7, 1, 1);

        graphicsView_41 = new QGraphicsView(layoutWidget);
        graphicsView_41->setObjectName(QStringLiteral("graphicsView_41"));
        graphicsView_41->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_41, 7, 8, 1, 1);

        graphicsView_51 = new QGraphicsView(layoutWidget);
        graphicsView_51->setObjectName(QStringLiteral("graphicsView_51"));
        graphicsView_51->setMaximumSize(QSize(50, 50));
        graphicsView_51->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_51, 2, 6, 1, 1);

        graphicsView_50 = new QGraphicsView(layoutWidget);
        graphicsView_50->setObjectName(QStringLiteral("graphicsView_50"));
        graphicsView_50->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_50, 3, 6, 1, 1);

        graphicsView_44 = new QGraphicsView(layoutWidget);
        graphicsView_44->setObjectName(QStringLiteral("graphicsView_44"));
        graphicsView_44->setMaximumSize(QSize(50, 50));
        graphicsView_44->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_44, 7, 7, 1, 1);

        graphicsView_43 = new QGraphicsView(layoutWidget);
        graphicsView_43->setObjectName(QStringLiteral("graphicsView_43"));
        graphicsView_43->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_43, 8, 7, 1, 1);

        graphicsView_53 = new QGraphicsView(layoutWidget);
        graphicsView_53->setObjectName(QStringLiteral("graphicsView_53"));
        graphicsView_53->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_53, 5, 6, 1, 1);

        graphicsView_54 = new QGraphicsView(layoutWidget);
        graphicsView_54->setObjectName(QStringLiteral("graphicsView_54"));
        graphicsView_54->setMaximumSize(QSize(50, 50));
        graphicsView_54->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_54, 6, 6, 1, 1);

        graphicsView_48 = new QGraphicsView(layoutWidget);
        graphicsView_48->setObjectName(QStringLiteral("graphicsView_48"));
        graphicsView_48->setMaximumSize(QSize(50, 50));
        graphicsView_48->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_48, 3, 7, 1, 1);

        graphicsView_45 = new QGraphicsView(layoutWidget);
        graphicsView_45->setObjectName(QStringLiteral("graphicsView_45"));
        graphicsView_45->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_45, 6, 7, 1, 1);

        graphicsView_52 = new QGraphicsView(layoutWidget);
        graphicsView_52->setObjectName(QStringLiteral("graphicsView_52"));
        graphicsView_52->setMaximumSize(QSize(50, 50));
        graphicsView_52->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_52, 4, 6, 1, 1);

        graphicsView_56 = new QGraphicsView(layoutWidget);
        graphicsView_56->setObjectName(QStringLiteral("graphicsView_56"));
        graphicsView_56->setMaximumSize(QSize(50, 50));
        graphicsView_56->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_56, 8, 6, 1, 1);

        graphicsView_46 = new QGraphicsView(layoutWidget);
        graphicsView_46->setObjectName(QStringLiteral("graphicsView_46"));
        graphicsView_46->setMaximumSize(QSize(50, 50));
        graphicsView_46->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_46, 5, 7, 1, 1);

        graphicsView_47 = new QGraphicsView(layoutWidget);
        graphicsView_47->setObjectName(QStringLiteral("graphicsView_47"));
        graphicsView_47->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_47, 4, 7, 1, 1);

        graphicsView_37 = new QGraphicsView(layoutWidget);
        graphicsView_37->setObjectName(QStringLiteral("graphicsView_37"));
        graphicsView_37->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_37, 3, 8, 1, 1);

        graphicsView_34 = new QGraphicsView(layoutWidget);
        graphicsView_34->setObjectName(QStringLiteral("graphicsView_34"));
        graphicsView_34->setMaximumSize(QSize(50, 50));
        graphicsView_34->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_34, 3, 9, 1, 1);

        graphicsView_33 = new QGraphicsView(layoutWidget);
        graphicsView_33->setObjectName(QStringLiteral("graphicsView_33"));
        graphicsView_33->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_33, 4, 9, 1, 1);

        graphicsView_39 = new QGraphicsView(layoutWidget);
        graphicsView_39->setObjectName(QStringLiteral("graphicsView_39"));
        graphicsView_39->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_39, 5, 8, 1, 1);

        graphicsView_36 = new QGraphicsView(layoutWidget);
        graphicsView_36->setObjectName(QStringLiteral("graphicsView_36"));
        graphicsView_36->setMaximumSize(QSize(50, 50));
        graphicsView_36->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_36, 2, 8, 1, 1);

        graphicsView_35 = new QGraphicsView(layoutWidget);
        graphicsView_35->setObjectName(QStringLiteral("graphicsView_35"));
        graphicsView_35->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_35, 2, 9, 1, 1);

        graphicsView_32 = new QGraphicsView(layoutWidget);
        graphicsView_32->setObjectName(QStringLiteral("graphicsView_32"));
        graphicsView_32->setMaximumSize(QSize(50, 50));
        graphicsView_32->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_32, 5, 9, 1, 1);

        graphicsView_38 = new QGraphicsView(layoutWidget);
        graphicsView_38->setObjectName(QStringLiteral("graphicsView_38"));
        graphicsView_38->setMaximumSize(QSize(50, 50));
        graphicsView_38->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_38, 4, 8, 1, 1);

        graphicsView_67 = new QGraphicsView(layoutWidget);
        graphicsView_67->setObjectName(QStringLiteral("graphicsView_67"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView_67->sizePolicy().hasHeightForWidth());
        graphicsView_67->setSizePolicy(sizePolicy);
        graphicsView_67->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(graphicsView_67, 8, 9, 1, 1);

        graphicsView_40 = new QGraphicsView(layoutWidget);
        graphicsView_40->setObjectName(QStringLiteral("graphicsView_40"));
        graphicsView_40->setMaximumSize(QSize(50, 50));
        graphicsView_40->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_40, 6, 8, 1, 1);

        graphicsView_42 = new QGraphicsView(layoutWidget);
        graphicsView_42->setObjectName(QStringLiteral("graphicsView_42"));
        graphicsView_42->setMaximumSize(QSize(50, 50));
        graphicsView_42->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_42, 8, 8, 1, 1);

        graphicsView_3 = new QGraphicsView(layoutWidget);
        graphicsView_3->setObjectName(QStringLiteral("graphicsView_3"));
        graphicsView_3->setMaximumSize(QSize(50, 50));
        graphicsView_3->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_3, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_12, 0, Qt::AlignHCenter);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_13, 0, Qt::AlignHCenter);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_14, 0, Qt::AlignHCenter);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setStyleSheet(QLatin1String("font: 26pt \"Tahoma\";\n"
""));

        horizontalLayout->addWidget(label_15, 0, Qt::AlignHCenter);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_16, 0, Qt::AlignHCenter);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_17, 0, Qt::AlignHCenter);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_18, 0, Qt::AlignHCenter);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setStyleSheet(QStringLiteral("font: 26pt \"Tahoma\";"));

        horizontalLayout->addWidget(label_19, 0, Qt::AlignHCenter);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 9);

        graphicsView_7 = new QGraphicsView(layoutWidget);
        graphicsView_7->setObjectName(QStringLiteral("graphicsView_7"));
        graphicsView_7->setMaximumSize(QSize(50, 50));
        graphicsView_7->setStyleSheet(QStringLiteral("background-color: rgb(108, 108, 108);"));

        gridLayout->addWidget(graphicsView_7, 6, 1, 1, 1);

        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 10, 1, 1);

        initButton = new QPushButton(centralWidget);
        initButton->setObjectName(QStringLiteral("initButton"));
        initButton->setGeometry(QRect(690, 70, 61, 23));
        ok_button = new QPushButton(centralWidget);
        ok_button->setObjectName(QStringLiteral("ok_button"));
        ok_button->setGeometry(QRect(700, 450, 41, 23));
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        tableWidget->raise();
        gridLayoutWidget->raise();
        initButton->raise();
        ok_button->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 761, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(graphicsView_2, graphicsView_3);
        QWidget::setTabOrder(graphicsView_3, graphicsView_4);
        QWidget::setTabOrder(graphicsView_4, graphicsView_5);
        QWidget::setTabOrder(graphicsView_5, graphicsView_6);
        QWidget::setTabOrder(graphicsView_6, graphicsView_7);
        QWidget::setTabOrder(graphicsView_7, graphicsView_8);
        QWidget::setTabOrder(graphicsView_8, graphicsView_9);
        QWidget::setTabOrder(graphicsView_9, graphicsView_10);
        QWidget::setTabOrder(graphicsView_10, graphicsView_11);
        QWidget::setTabOrder(graphicsView_11, graphicsView_12);
        QWidget::setTabOrder(graphicsView_12, graphicsView_13);
        QWidget::setTabOrder(graphicsView_13, graphicsView_14);
        QWidget::setTabOrder(graphicsView_14, graphicsView_15);
        QWidget::setTabOrder(graphicsView_15, graphicsView_16);
        QWidget::setTabOrder(graphicsView_16, graphicsView_17);
        QWidget::setTabOrder(graphicsView_17, graphicsView_18);
        QWidget::setTabOrder(graphicsView_18, graphicsView_19);
        QWidget::setTabOrder(graphicsView_19, graphicsView_20);
        QWidget::setTabOrder(graphicsView_20, graphicsView_21);
        QWidget::setTabOrder(graphicsView_21, graphicsView_22);
        QWidget::setTabOrder(graphicsView_22, graphicsView_23);
        QWidget::setTabOrder(graphicsView_23, graphicsView_24);
        QWidget::setTabOrder(graphicsView_24, graphicsView_25);
        QWidget::setTabOrder(graphicsView_25, graphicsView_26);
        QWidget::setTabOrder(graphicsView_26, graphicsView_27);
        QWidget::setTabOrder(graphicsView_27, graphicsView_28);
        QWidget::setTabOrder(graphicsView_28, graphicsView_29);
        QWidget::setTabOrder(graphicsView_29, graphicsView_30);
        QWidget::setTabOrder(graphicsView_30, graphicsView_31);
        QWidget::setTabOrder(graphicsView_31, graphicsView_32);
        QWidget::setTabOrder(graphicsView_32, graphicsView_33);
        QWidget::setTabOrder(graphicsView_33, graphicsView_34);
        QWidget::setTabOrder(graphicsView_34, graphicsView_35);
        QWidget::setTabOrder(graphicsView_35, graphicsView_36);
        QWidget::setTabOrder(graphicsView_36, graphicsView_37);
        QWidget::setTabOrder(graphicsView_37, graphicsView_38);
        QWidget::setTabOrder(graphicsView_38, graphicsView_39);
        QWidget::setTabOrder(graphicsView_39, graphicsView_40);
        QWidget::setTabOrder(graphicsView_40, graphicsView_41);
        QWidget::setTabOrder(graphicsView_41, graphicsView_42);
        QWidget::setTabOrder(graphicsView_42, graphicsView_43);
        QWidget::setTabOrder(graphicsView_43, graphicsView_44);
        QWidget::setTabOrder(graphicsView_44, graphicsView_45);
        QWidget::setTabOrder(graphicsView_45, graphicsView_46);
        QWidget::setTabOrder(graphicsView_46, graphicsView_47);
        QWidget::setTabOrder(graphicsView_47, graphicsView_48);
        QWidget::setTabOrder(graphicsView_48, graphicsView_49);
        QWidget::setTabOrder(graphicsView_49, graphicsView_50);
        QWidget::setTabOrder(graphicsView_50, graphicsView_51);
        QWidget::setTabOrder(graphicsView_51, graphicsView_52);
        QWidget::setTabOrder(graphicsView_52, graphicsView_53);
        QWidget::setTabOrder(graphicsView_53, graphicsView_54);
        QWidget::setTabOrder(graphicsView_54, graphicsView_55);
        QWidget::setTabOrder(graphicsView_55, graphicsView_56);
        QWidget::setTabOrder(graphicsView_56, graphicsView_57);
        QWidget::setTabOrder(graphicsView_57, graphicsView_58);
        QWidget::setTabOrder(graphicsView_58, graphicsView_59);
        QWidget::setTabOrder(graphicsView_59, graphicsView_60);
        QWidget::setTabOrder(graphicsView_60, graphicsView_61);
        QWidget::setTabOrder(graphicsView_61, graphicsView_65);
        QWidget::setTabOrder(graphicsView_65, graphicsView_66);
        QWidget::setTabOrder(graphicsView_66, graphicsView_67);
        QWidget::setTabOrder(graphicsView_67, tableWidget);
        QWidget::setTabOrder(tableWidget, graphicsView);

        retranslateUi(MainWindow);

        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Joueur :", Q_NULLPTR));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Coup \303\240 jouer :", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "A", Q_NULLPTR)
         << QApplication::translate("MainWindow", "B", Q_NULLPTR)
         << QApplication::translate("MainWindow", "C", Q_NULLPTR)
         << QApplication::translate("MainWindow", "D", Q_NULLPTR)
         << QApplication::translate("MainWindow", "E", Q_NULLPTR)
         << QApplication::translate("MainWindow", "F", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G", Q_NULLPTR)
         << QApplication::translate("MainWindow", "H", Q_NULLPTR)
        );
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "A", Q_NULLPTR)
         << QApplication::translate("MainWindow", "B", Q_NULLPTR)
         << QApplication::translate("MainWindow", "C", Q_NULLPTR)
         << QApplication::translate("MainWindow", "D", Q_NULLPTR)
         << QApplication::translate("MainWindow", "E", Q_NULLPTR)
         << QApplication::translate("MainWindow", "F", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G", Q_NULLPTR)
         << QApplication::translate("MainWindow", "H", Q_NULLPTR)
        );
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("MainWindow", "A", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "C", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "D", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "E", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "F", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "G", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "H", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "7", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "8", Q_NULLPTR));
        initButton->setText(QApplication::translate("MainWindow", "Init", Q_NULLPTR));
        ok_button->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
