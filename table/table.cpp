#include "table.h"
#include "ui_table.h"
#include <QAbstractTableModel>

Table
    ::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);

    // Create a new model
    // QStandardItemModel(int rows, int columns, QObject * parent = 0)
    model = new QStandardItemModel(4,2,this);

    // Attach the model to the view
    //ui->tableView->setModel(model);

    // Generate data
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 2; col++)
        {
            QModelIndex index
                    = model->index(row,col,QModelIndex());
            // 0 for all data
            model->setData(index,0);
        }
    }
}


Table::~Table()
{
    delete ui;
}
