#include "table.h"
#include "ui_table.h"
#include "BarDelegate.h"
#include "bardelegatepep.h"
#include <array>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDebug>

table::table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::table)
{
        ui->setupUi(this);
        //number of rows+columns of table
        const int tableRow=1;
        const int tableColumn=12;
        //column in which to display checkboxes
        const int checkboxColumn=11;

        //create a list with all the needed strings
        QStringList list = { "", "Pl" , "Accession", "Description", "Chr" ,"Coverage","#Peptides","#Spectra",
                           "MS Quant", "MW","Confidence","Checkbox"};

        //create model with columns and rows
        model = new QStandardItemModel(tableRow,tableColumn,this);

        ui->tableView->setModel(model);
        
        //Model für Peptidtabelle
        TableRowPep=1;
    TableColumnPep=6;
    //column in which to display checkboxes
    const int checkboxColumnPep=6;

    //create a list with all the needed strings
    QStringList listpep = { "", "Pl" , "Sequence", "Start", "#Spectra", "Confidence","Checkbox"};

    //Model wird erstellt mit rows and columns number
    modelpep = new QStandardItemModel(TableRowPep,TableColumnPep,this);

    ui->tableView_2->setModel(modelpep);

    bardelegatepep* bardelegatepe = new bardelegatepep();
    ui->tableView_2->setItemDelegate(bardelegatepe);

        //--------------------------------------------------------------
                // PARSER
                model->setColumnCount(1);
                model->setHorizontalHeaderLabels(QStringList() << "Column");

                //open file
                QFile file("/home/nantia/Teamprojekt 2018/SILAC_mzTab");
                if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
                    qDebug() << "File does not exist";
                } else {
                    // Create a thread to retrieve data from a file
                    QTextStream in(&file);
                    //Reads the data up to the end of file
                    while (!in.atEnd())
                    {
                        QString line = in.readLine();
                        // Adding to the model in line with the elements
                        QList<QStandardItem *> standardItemsList;
                        // consider that the line separated by semicolons into columns
                        for (QString item : line.split("\t")) {
                            standardItemsList.append(new QStandardItem(item));
                        }
                          //Zeigt nur Reihen des Proteinteils an  
                        if (line.indexOf("PRT") >= 0){
                         model->insertRow(model->rowCount(), standardItemsList);}
                        //Zeigt nur Reihen der Proteintabelle an
                        if (line.startsWith("PSM")) {
                          modelpep->insertRow(modelpep->rowCount(), standardItemsList);
                    }
                        
                    file.close();
                }

        //------------------------------------------------------------------------------------------------------------

//aktualisiere Reihenzahl
      TableRow = TableRow + model->rowCount();
     TableRowPep = TableRowPep + modelpep->rowCount();

        BarDelegate* bardelegate = new BarDelegate();
        ui->tableView->setItemDelegate(bardelegate);

// SIGNALS UND SLOTS
        //Signal Slot Connection für Zeilenselektion
        connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                     SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &)));

        //Signal Slot Connection für Deselect Button
        connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (handleButton()));
        
        //Sets the horizontal header item for each column
        for (int i=0; i<tableColumn; i++)
         {
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

/*
 *
 *   Peptide Table
 *
 *
*/
    
    //Sets the horizontal header item for each column
    for (int i=0; i<=TableColumnPep; i++)
    {
        modelpep->setHorizontalHeaderItem(i, new QStandardItem(QString (listpep.at(i))));
    }

    for(int row = 0; row < TableRowPep; row++)
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

   

    //--------------------------------------------------------------------------------
    // Push Button für Deselect
    //--------------------------------------------------------------------------------

    ui->pushButton->setText("DESELECT");

}

//Slot: die Reihe, die oben angezeigt wird, wird auch unten angezeigt.
void table::slotSelectionChange(const QItemSelection &, const QItemSelection &)

{

            select = new QItemSelectionModel;
            QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
            for(int i=0; i< selection.count(); i++)
            {


                for (int j=0; j<TableRowPep; j++){
                    if (j != selection.at(i).row()) ui->tableView_2->hideRow(j);
                    else ui->tableView_2->showRow(j);
                }

            }

}

void table::handleButton()
{
    for (int j=0; j<TableRowPep; j++){
        ui->tableView_2->showRow(j);
    }
}

table::~table()
{
    delete ui;
}
