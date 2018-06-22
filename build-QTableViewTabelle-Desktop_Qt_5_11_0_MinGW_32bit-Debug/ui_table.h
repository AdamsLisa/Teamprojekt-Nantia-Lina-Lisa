/********************************************************************************
** Form generated from reading UI file 'table.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_H
#define UI_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_table
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QTableView *tableView_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *table)
    {
        if (table->objectName().isEmpty())
            table->setObjectName(QStringLiteral("table"));
        table->resize(1367, 692);
        centralWidget = new QWidget(table);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 1301, 321));
        tableView_2 = new QTableView(centralWidget);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(0, 320, 971, 461));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(990, 340, 181, 71));
        table->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(table);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1367, 26));
        table->setMenuBar(menuBar);
        mainToolBar = new QToolBar(table);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        table->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(table);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        table->setStatusBar(statusBar);

        retranslateUi(table);

        QMetaObject::connectSlotsByName(table);
    } // setupUi

    void retranslateUi(QMainWindow *table)
    {
        table->setWindowTitle(QApplication::translate("table", "table", nullptr));
        pushButton->setText(QApplication::translate("table", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class table: public Ui_table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_H
