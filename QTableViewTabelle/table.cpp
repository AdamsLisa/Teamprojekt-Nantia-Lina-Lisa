#include "table.h"
#include "ui_table.h"
#include "BarDelegate.h"

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
   /*   //column and row for green bars
        const int maxCol=2;
        const int maxRow=20;
   */
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

 //Testdaten für Spalte #Peptides
        int anzpeptidescolumn = 6;

        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,anzpeptidescolumn,QModelIndex());
                    //Zahlen zwischen 20 und 40
                    int r = rand() % 20 +20;
                    model->setData(index,r);

            }
        //Testdaten für Spalte Coverage
        int coveragercolumn = 5;

        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,coveragercolumn,QModelIndex());
                    //Zahlen zwischen 1000 und 6000
                    int r = rand() % 60 *10;
                    model->setData(index,r);

            }

        //Testdaten für #Spectra
        int anzspectracolumn = 7;

        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,anzspectracolumn,QModelIndex());
                    //Zahlen zwischen 40 und 200
                    int r = rand() % 160 +40;
                    model->setData(index,r);

            }

        //Testdaten für MS2Quant
        int ms2quantcolumn = 8;

        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,ms2quantcolumn,QModelIndex());
                    //Zahlen zwischen 0 und 0.02
                    float r = rand() % 3 * 0.01;
                    model->setData(index,r);

            }

        //Testdaten für MW
        int mwquantcolumn = 9;

        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,mwquantcolumn,QModelIndex());
                    //Zahlen zwischen 40 und 600
                    int r = rand() % 560 +40;
                    model->setData(index,r);

            }

}

table::~table()
{
    delete ui;
}
