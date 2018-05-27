#include "table.h"
#include "ui_table.h"
#include <QAbstractItemDelegate>

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
    ui->setupUi(this);
        
    //Model wird erstellt mit Reihen und Spaltenzahl
    model = new QStandardItemModel(20,12,this);

    ui->tableView->setModel(model);

    //Spaltennamen
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


/*    if(index.column()==3)
           {
       QProgressBar* item;
       item->setMinimum(0);
       item->setMaximum(100);
       item->setRange(0,100);

}
*/
}
void table::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if (index.column() == 2) { //for the third column

            QStyleOptionProgressBar progressBarOption;
            progressBarOption.rect = option.rect; //orientation
            progressBarOption.minimum = 0; //set minimum
            progressBarOption.maximum = 100; //set maximum
            QApplication::style()->drawControl(QStyle::CE_ProgressBar,&progressBarOption, painter); //draw the bars
        } else
            QStyledItemDelegate::paint(painter, option, index);
     }




table::~table()
{
    delete ui;
}
