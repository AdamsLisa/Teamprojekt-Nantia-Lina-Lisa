#include "table.h"
#include "ui_table.h"
#include <QAbstractTableModel>

Table
    ::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);

}


Table::~Table()
{
    delete ui;
}


