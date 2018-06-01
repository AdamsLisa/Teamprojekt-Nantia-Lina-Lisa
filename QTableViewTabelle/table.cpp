#include "table.h"
#include "ui_table.h"
#include "qpainter.h"
#include "myclass.h"


table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{

        ui->setupUi(this);
        //number of rows+columns of table
        int tableRow=20;
        int tableColumn=12;


        //Model wird erstellt mit Reihen und Spaltenzahl
        model = new QStandardItemModel(tableRow,tableColumn,this);
        //item = new QStandardItem(QString (""));

        ui->tableView->setModel(model);

        //Sets the horizontal header item for each column
        model.setHorizontalHeaderItem(0, new QStandardItem(QString ("")));
        model.setHorizontalHeaderItem(1, new QStandardItem(QString ("Pl")));
        model.setHorizontalHeaderItem(2, new QStandardItem(QString ("Accession")));
        model.setHorizontalHeaderItem(3, new QStandardItem(QString ("Description")));
        model.setHorizontalHeaderItem(4, new QStandardItem(QString ("Chr.")));
        model.setHorizontalHeaderItem(5, new QStandardItem(QString ("Coverage")));
        model.setHorizontalHeaderItem(6, new QStandardItem(QString ("#Peptides")));
        model.setHorizontalHeaderItem(7, new QStandardItem(QString ("#Spectra")));
        model.setHorizontalHeaderItem(8, new QStandardItem(QString ("MS2 Quant")));
        model.setHorizontalHeaderItem(9, new QStandardItem(QString ("MW")));
        model.setHorizontalHeaderItem(10, new QStandardItem(QString ("Confidence")));
        model.setHorizontalHeaderItem(11, new QStandardItem(QString ("Checkbox")));

        //column in which to display checkboxes
        int checkboxColumn=11;

        for(int row = 0; row < tableRow; row++)
            {
                //instance of item
                QStandardItem* item;
                item = new QStandardItem(true);
                //set the box checkable
                item->setCheckable(true);
                //Sets the checkbox's check state to unchecked
                item->setCheckState(Qt::Unchecked);
                //put checkbox into each row of checkboxcolumn
                model->setItem(row,checkboxColumn, item);
             }

         //for SpinBox(feature/Bars)
        int minC0l=2;
        int maxRow=4;
        for (int row = 0; row < maxRow; ++row) {
                for (int column = 0; column < maxCol; ++column) {
                     QModelIndex index = model.index(row, column, QModelIndex());
                     model.setData(index, QVariant((row + 1) * (column + 1)));
                 }
             }


 }

table::~table()
{
    delete ui;
}
