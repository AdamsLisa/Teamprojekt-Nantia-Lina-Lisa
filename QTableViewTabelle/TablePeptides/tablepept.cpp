#include "tablepept.h"
#include "ui_tablepept.h"
#include "bardelegatepept.h"

tablepept::tablepept(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tablepept)
{
        ui->setupUi(this);
        //number of rows+columns of table
        const int tableRow=20;
        const int tableColumn=12;
        //column in which to display checkboxes
        const int checkboxColumn=11;

        //create a list with all the needed strings
        QStringList list = { "", "Pl" , "Accession", "Description", "Chr" ,"Coverage","#Peptides","#Spectra",
                           "MS Quant", "MW","Confidence","Checkbox"};

        //Model wird erstellt mit Reihen und Spaltenzahl
        model = new QStandardItemModel(tableRow,tableColumn,this);

        ui->tableView->setModel(model);

        BarDelegatePept* bardelegate = new BarDelegatePept();
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


}


tablepept::~tablepept()
{
    delete ui;
}
