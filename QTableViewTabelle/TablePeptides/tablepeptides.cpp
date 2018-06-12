#include "tablepeptides.h"
#include "ui_tablepeptides.h"
#include "bardelegatepept.h"

tablepeptides::tablepeptides(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tablepeptides)
{
        ui->setupUi(this);
        //number of rows+columns of table
        const int tableRow=5;
        const int tableColumn=6;
        //column in which to display checkboxes
        const int checkboxColumn=6;

        //create a list with all the needed strings
        QStringList list = { "", "Pl" , "Sequence", "Start", "#Spectra", "Confidence","Checkbox"};

        //Model wird erstellt mit Reihen und Spaltenzahl
        model = new QStandardItemModel(tableRow,tableColumn,this);

        ui->tableView->setModel(model);

        BarDelegatePept* bardelegate = new BarDelegatePept();
        ui->tableView->setItemDelegate(bardelegate);


        //Sets the horizontal header item for each column
        for (int i=0; i<=tableColumn; i++){
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

        int columnstart = 3;
        //Testdaten
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,columnstart,QModelIndex());

                    int r = rand() %4000;
                    model->setData(index,r);

            }

        int columnspectra = 4;
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,columnspectra,QModelIndex());
                    int r = rand() % 2 +1;
                    model->setData(index,r);

            }


}

tablepeptides::~tablepeptides()
{
    delete ui;
}
