#include "table.h"
#include "ui_table.h"

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
    model = new QStandardItemModel(20,12,this);

    ui->tableView->setModel(model);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString ("")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString ("Pl")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString ("Accession")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString ("Description")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString ("Chr.")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString ("Coverage")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString ("#Peptides")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString ("#Spectra")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString ("MS2 Quant")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString ("MW")));
    model->setHorizontalHeaderItem(10, new QStandardItem(QString ("Confidence")));



}

table::~table()
{
    delete ui;
}
