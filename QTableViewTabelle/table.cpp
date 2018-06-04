#include "table.h"
#include "ui_table.h"
#include "Bardelegate.h"

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
        ui->setupUi(this);
        //number of rows+columns of table
        const int tableRow=20;
        const int tableColumn=12;
        //column in which to display checkboxes
        const int checkboxColumn=11;
        //column and row for green bars
        const int maxCol=2;
        const int maxRow=20;

        //create a list with all the needed strings
        QStringList list = { "", "Pl" , "Accession", "Description", "Chr" ,"Coverage","#Peptides","#Spectra",
                           "MS Quant", "MW","Confidence","Checkbox"};

        //Model wird erstellt mit Reihen und Spaltenzahl
        model = new QStandardItemModel(tableRow,tableColumn,this);

        ui->tableView->setModel(model);

        BarDelegate* bardelegate = new BarDelegate();
        ui->tableView->setItemDelegate(bardelegate);


        //Sets the horizontal header item for each column
        for (int i=0; i<tableColumn; i++){
            model->setHorizontalHeaderItem(i, new QStandardItem(QString (list.at(i))));
        }

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
        for (int row = 0; row < maxRow; ++row)
            {
                    for (int column = 1; column < maxCol; ++column)
                    {
                         QModelIndex index = model->index(row, column, QModelIndex());
                         model->setData(index, QVariant((row + 1) * (column + 1)));
                     }
             }

}

table::~table()
{
    delete ui;
}
