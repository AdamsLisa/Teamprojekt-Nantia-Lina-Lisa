#include "table.h"
#include "ui_table.h"
#include "BarDelegate.h"
#include "bardelegatepep.h"
#include <array>
#include <QTableView>

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

        //creates an array
        int numArray[] = {5,6,7,8,9};


        //Testdaten für Spalte #Peptides
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,numArray[1],QModelIndex());
                    //Zahlen zwischen 20 und 40
                    int r = rand() % 20 +20;
                    model->setData(index,r);

            }

        //Testdaten für Spalte Coverage
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,numArray[0],QModelIndex());
                    //Zahlen zwischen 1000 und 6000
                    int r = rand() % 60 *10;
                    model->setData(index,r);

            }

        //Testdaten für #Spectra
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,numArray[2],QModelIndex());
                    //Zahlen zwischen 40 und 200
                    int r = rand() % 160 +40;
                    model->setData(index,r);

            }

        //Testdaten für MS2Quant
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,numArray[3],QModelIndex());
                    //Zahlen zwischen 0 und 0.02
                    float r = rand() % 3 * 0.01;
                    model->setData(index,r);

            }

        //Testdaten für MW
        for(int row = 0; row <= tableRow; row++)
            {

                    QModelIndex index
                            = model->index(row,numArray[4],QModelIndex());
                    //Zahlen zwischen 40 und 600
                    int r = rand() % 560 +40;
                    model->setData(index,r);

            }


 //--------------------------------------------------------------------------------------------------------------------
 // HIER BEGINNT DIE PEPTIDTABELLE

        const int tableRowPep=5;
        const int tableColumnPep=6;
        //column in which to display checkboxes
        const int checkboxColumnPep=6;

        //create a list with all the needed strings
        QStringList listpep = { "", "Pl" , "Sequence", "Start", "#Spectra", "Confidence","Checkbox"};

        //Model wird erstellt mit Reihen und Spaltenzahl
        modelpep = new QStandardItemModel(tableRowPep,tableColumnPep,this);

        ui->tableView_2->setModel(modelpep);

        bardelegatepep* bardelegatepe = new bardelegatepep();
        ui->tableView_2->setItemDelegate(bardelegatepe);


        //Sets the horizontal header item for each column
        for (int i=0; i<=tableColumnPep; i++){
            model->setHorizontalHeaderItem(i, new QStandardItem(QString (listpep.at(i))));
        }

        for(int row = 0; row < tableRowPep; row++)
            {
                //instance of item
                QStandardItem* itempep;
                itempep = new QStandardItem(true);
                //set the box checkable
                itempep->setCheckable(true);
                //Sets the checkbox's check state to unchecked
                itempep->setCheckState(Qt::Unchecked);
                //put checkbox into each row of checkboxcolumn
                modelpep->setItem(row,checkboxColumnPep, itempep);
             }

int columnstart = 3;
        //Testdaten
        for(int row = 0; row <= tableRowPep; row++)
            {

                    QModelIndex index
                            = modelpep->index(row,columnstart,QModelIndex());

                    int r = rand() %4000;
                    modelpep->setData(index,r);

            }

        int columnspectra = 4;
        for(int row = 0; row <= tableRowPep; row++)
            {

                    QModelIndex index
                            = model->index(row,columnspectra,QModelIndex());
                    int r = rand() % 2 +1;
                    modelpep->setData(index,r);

            }


}

table::~table()
{
    delete ui;
}
