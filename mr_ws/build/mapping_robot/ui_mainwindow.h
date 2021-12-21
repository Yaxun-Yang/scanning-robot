/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *buttonWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startSensorBtn;
    QPushButton *stopSensorBtn;
    QPushButton *startRecordBtn;
    QPushButton *stopRecordBtn;
    QPushButton *parseDataBtn;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *viewer;
    QWidget *aaa;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonWidget = new QWidget(widget);
        buttonWidget->setObjectName(QStringLiteral("buttonWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonWidget->sizePolicy().hasHeightForWidth());
        buttonWidget->setSizePolicy(sizePolicy1);
        buttonWidget->setMinimumSize(QSize(200, 0));
        verticalLayout = new QVBoxLayout(buttonWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        startSensorBtn = new QPushButton(buttonWidget);
        startSensorBtn->setObjectName(QStringLiteral("startSensorBtn"));

        verticalLayout->addWidget(startSensorBtn);

        stopSensorBtn = new QPushButton(buttonWidget);
        stopSensorBtn->setObjectName(QStringLiteral("stopSensorBtn"));

        verticalLayout->addWidget(stopSensorBtn);

        startRecordBtn = new QPushButton(buttonWidget);
        startRecordBtn->setObjectName(QStringLiteral("startRecordBtn"));

        verticalLayout->addWidget(startRecordBtn);

        stopRecordBtn = new QPushButton(buttonWidget);
        stopRecordBtn->setObjectName(QStringLiteral("stopRecordBtn"));

        verticalLayout->addWidget(stopRecordBtn);

        parseDataBtn = new QPushButton(buttonWidget);
        parseDataBtn->setObjectName(QStringLiteral("parseDataBtn"));

        verticalLayout->addWidget(parseDataBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(buttonWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        viewer = new QGridLayout();
        viewer->setObjectName(QStringLiteral("viewer"));
        aaa = new QWidget(widget);
        aaa->setObjectName(QStringLiteral("aaa"));

        viewer->addWidget(aaa, 0, 0, 1, 1);


        horizontalLayout->addLayout(viewer);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        startSensorBtn->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\344\274\240\346\204\237\345\231\250", Q_NULLPTR));
        stopSensorBtn->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\344\274\240\346\204\237\345\231\250", Q_NULLPTR));
        startRecordBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\275\225\345\210\266", Q_NULLPTR));
        stopRecordBtn->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\345\275\225\345\210\266", Q_NULLPTR));
        parseDataBtn->setText(QApplication::translate("MainWindow", "\350\247\243\345\214\205", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
