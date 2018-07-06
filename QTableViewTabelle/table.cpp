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
        int tableRow=0;
        //const int tableColumn=12;
        //column in which to display checkboxes
        const int checkboxColumn=11;

        //create a list with all the needed strings
        /*QStringList list = { "", "Pl" , "Accession", "Description", "Chr" ,"Coverage","#Peptides","#Spectra",
                           "MS Quant", "MW","Confidence","Checkbox"};*/

        //create model with columns and rows
        model = new QStandardItemModel(this);

        ui->tableView->setModel(model);
        //Model wird erstellt mit rows and columns number
        modelpep = new QStandardItemModel(this);

        int indexofproteincoverage;
        int indexofnumberofpeptides;
        int indexofnumberofspectra;
        int indexofms2quant;
        int indexofconfidence;
        int indexofaccession;
        int indexofdescription;
       /* int worter[50];
        int indexworter=1;
        int laufindex=0;
        worter[0]=0;
        int leerzeichencount=0; */

        //--------------------------------------------------------------
                // PARSER
                model->setColumnCount(1);
                model->setHorizontalHeaderLabels(QStringList() << "Column");

                //open file
                //QFile file("/home/nantia/Teamprojekt 2018/SILAC_mzTab");
                QFile file("C:\\Users\\Lisa Adams\\Documents\\_Studium\\Teamprojekt\\SILAC_CQI.mzTab");
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
                            //if (item == " ") leerzeichencount++;
                        }
                        if (line.startsWith("PRH")) {
                           /* QString line2 = in.readLine();
                            QList<QStandardItem *> standardItemsList2;
                            for (QString item2 : line2.split("\t")){
                                if (item2 == " ") {worter[indexworter]=laufindex+1; indexworter++;}
                                laufindex++;
                            }*/

                            indexofproteincoverage=line.indexOf("protein_coverage");
                            indexofnumberofpeptides=line.indexOf("num_peptides_distinct_ms_run[1]");
                            indexofnumberofspectra=line.indexOf("num_psms_ms_run[1]");
                            indexofms2quant=line.indexOf("protein_abundance_assay[1]");
                            indexofconfidence=line.indexOf("best_search_engine_score[1]");
                            indexofaccession=line.indexOf("accession");
                            indexofdescription=line.indexOf("description");
                            model->insertRow(model->rowCount(), standardItemsList);
}

                        if (line.startsWith("PRT")) {model->insertRow(model->rowCount(), standardItemsList); tableRow++;}
                        if (line.startsWith("PSM")) modelpep->insertRow(modelpep->rowCount(), standardItemsList);

                    }
                    file.close();
                }

        //------------------------------------------------------------------------------------------------------------


        BarDelegate* bardelegate = new BarDelegate();
        ui->tableView->setItemDelegate(bardelegate);

// SIGNALS UND SLOTS
        //Signal Slot Connection für Zeilenselektion
        connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                     SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &)));

        //Signal Slot Connection für Deselect Button
        connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (handleButton()));
        
       /* for (int i=0; i<30; i++){
        if(worter[i]==indexofaccession){*/
         model->setHorizontalHeaderItem(indexofaccession, new QStandardItem(QString ("Accession")));
         model->setHorizontalHeaderItem(indexofconfidence, new QStandardItem(QString ("Confidence")));
         model->setHorizontalHeaderItem(indexofdescription, new QStandardItem(QString ("Description")));
         model->setHorizontalHeaderItem(indexofms2quant, new QStandardItem(QString ("MS2Quant")));
         model->setHorizontalHeaderItem(indexofnumberofpeptides, new QStandardItem(QString ("# Peptides")));
         model->setHorizontalHeaderItem(indexofnumberofspectra, new QStandardItem(QString ("# Spectra")));
         model->setHorizontalHeaderItem(indexofproteincoverage, new QStandardItem(QString ("Protein Coverage")));



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
    TableRowPep=1;
    TableColumnPep=6;
    //column in which to display checkboxes
    const int checkboxColumnPep=6;

    //create a list with all the needed strings
    QStringList listpep = { "", "Pl" , "Sequence", "Start", "#Spectra", "Confidence","Checkbox"};


    ui->tableView_2->setModel(modelpep);
    TableRowPep=modelpep->rowCount();

    bardelegatepep* bardelegatepe = new bardelegatepep();
    ui->tableView_2->setItemDelegate(bardelegatepe);

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
           // for(int i=0; i< selection.count(); i++)
           // {
                QString Code = model->data(selection.at(1)).toString();
                for (int j=0; j<TableRowPep; j++){
                    QModelIndex index = modelpep->index(j,3, QModelIndex());

                    if (modelpep->data(index).toString() != Code) ui->tableView_2->hideRow(j);
                    else ui->tableView_2->showRow(j);
                }

           // }

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
