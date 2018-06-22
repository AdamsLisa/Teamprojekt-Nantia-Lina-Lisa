#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create a data model
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(1);
    csvModel->setHorizontalHeaderLabels(QStringList() << "Column");
    ui->tableView->setModel(csvModel);


    //open file
    QFile file("/home/nantia/Teamprojekt 2018/SILAC_mzTab");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        //Reads the data up to the end of file
        while (!in.atEnd())
        {
            QString line = in.readLine();
            // Adding to the model in line with the elements
            QList<QStandardItem *> standardItemsList;
            // consider that the line separated by semicolons into columns
            for (QString item : line.split("\t")) {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}
