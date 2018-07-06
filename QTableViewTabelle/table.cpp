#include "table.h"
#include "ui_table.h"
#include "bardelegate.h"
#include "BarDelegatepep.h"
#include <array>
#include <QGridLayout>
#include <QPushButton>
#include <QSortFilterProxyModel>
//#include <QObject>
//#include <QAbstractItemModel>
//#include <QLineEdit>
#include "lineEditdelegate.h"


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

        //create model with columns and rows
        model = new QStandardItemModel(tableRow,tableColumn,this);



      //Filter


        QStandardItemModel *sourceModel = model;
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);

        proxyModel->setSourceModel(sourceModel);
        ui->tableView->setModel(proxyModel);


    //    QString search = ui->tableView->model()->data(ui->tableView->model()->index(1,3)).toString();
   //     QString search = "drei";
 //         QString search = model->index(3,1).data(Qt::DisplayRole).toString();

       // proxyModel->setDynamicSortFilter(true);
       // proxyModel->setFilterFixedString(search);
        //proxyModel->setFilterFixedString(proxyModel->index(1,3).data().toString());


        //proxyModel->sort(5, Qt::AscendingOrder);


 //       model->setHorizontalHeaderItem(3, description);


        QStringList test = {"eins", "zwei", "drei", "vier", "fünf", "drei"};

        for(int row = 0; row <= 5; row++)
         {
            QModelIndex index = model->index(row,3,QModelIndex());
            QString s = test[row];
            model->setData(index,s);

         }



//        for(int column = 0; column <= 3; column++)
//         {
//            QLineEdit *lineEd = new QLineEdit;
//            lineEd->setPlaceholderText("suche");
//            QModelIndex index = model->index(0,column,QModelIndex());
//            ui->tableView->setIndexWidget(index, lineEd);
//            connect(lineEd, SIGNAL(textChanged(const QString &)),SLOT(textFilterChanged(const QString &)));

//         }




        proxyModel->insertRow(0);

        lineEditdelegate* lineEdit = new lineEditdelegate;
        ui->tableView->setItemDelegate(lineEdit);

        proxyModel->insertRow(0);
        ui->tableView->setItemDelegateForRow(0,lineEdit);

        QModelIndex index = model->index(0,3,QModelIndex());
        connect(this->~QObject(),SIGNAL (itemChanged(QStandardItem *item)),this, SLOT(textFilterChanged()));
//        proxyModel->setFilterKeyColumn(3);

       //connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(textFilterChanged(const QString&)));


//        QString search = model->index(0,3).data().toString();
//        proxyModel->setFilterFixedString(search);







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

        //creates an array
        int numArray[] = {5,6,7,8,9};


        //Testdata for #Peptides
        for(int row = 0; row <= tableRow; row++)
         {
            QModelIndex index = model->index(row,numArray[1],QModelIndex());
            int r = rand() % 20 +20;
            model->setData(index,r);
         }

        //Testdata for Coverage
        for(int row = 0; row <= tableRow; row++)
         {
            QModelIndex index = model->index(row,numArray[0],QModelIndex());
            int r = rand() % 60 *10;
            model->setData(index,r);
         }

        //Testdata for #Spectra
        for(int row = 0; row <= tableRow; row++)
         {
            QModelIndex index = model->index(row,numArray[2],QModelIndex());
            int r = rand() % 160 +40;
            model->setData(index,r);
         }

        //Testdata for MS2Quant
        for(int row = 0; row <= tableRow; row++)
         {
            QModelIndex index = model->index(row,numArray[3],QModelIndex());
            float r = rand() % 3 * 0.01;
            model->setData(index,r);

         }

        //Testdata for MW
        for(int row = 0; row <= tableRow; row++)
          {
            QModelIndex index = model->index(row,numArray[4],QModelIndex());
            int r = rand() % 560 +40;
            model->setData(index,r);
          }

/*
 *
 *   Peptide Table
 *
 *
*/
    TableRowPep=5;
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

    int columnstart = 3;
    //Testdata
    for(int row = 0; row <= TableRowPep; row++)
        {
            QModelIndex index = modelpep->index(row,columnstart,QModelIndex());
            int r = rand() %4000;
            modelpep->setData(index,r);
        }

    int columnspectra = 4;
    for(int row = 0; row <= TableRowPep; row++)
        {
            QModelIndex index = model->index(row,columnspectra,QModelIndex());
            int r = rand() % 2 +1;
            modelpep->setData(index,r);
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

void table::textFilterChanged(){

    newValue = lineEd->text();
    proxyModel->setFilterKeyColumn(3);
    proxyModel->setFilterFixedString(newValue);

}

//void table::textFilterChanged2(const QString &newValue){


//    proxyModel->setFilterRegExp(newValue);
//    //proxyModel->setFilterKeyColumn(3);
//}



table::~table()
{
    delete ui;
}
