#include "bardelegate.h"
#include "bardelegatepep.h"
#include "proteintabelle.h"
#include "peptidtabelle.h"
#include <QApplication>
#include <QSplitter>
#include <QSplitterHandle>
#include <array>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QItemSelection>
#include <QItemSelectionModel>



int main(int argc, char *argv[])
{
    //Instance for managing the GUI application
    QApplication a(argc, argv);

    //Split the window and create 2 tables
    QSplitter *splitter = new QSplitter;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelpep = new QStandardItemModel;
    QTableView *Proteintabelle1 = new Proteintabelle;
    QTableView *Peptidtabelle1 = new Peptidtabelle;
    Proteintabelle1->setModel(model);
    Peptidtabelle1->setModel(modelpep);
    //add the two tables
    splitter->addWidget(Proteintabelle1);
    splitter->addWidget(Peptidtabelle1);
    //set the orientation
    splitter->setOrientation(Qt::Vertical);

    //add deselect button
    QPushButton *deselectbutton = new QPushButton(splitter);
    deselectbutton->setText("DESELECT");

    //instance for protein table
    BarDelegate* bardelegate = new BarDelegate();
    Proteintabelle1->setItemDelegate(bardelegate);

    //instance for peptide table
    bardelegatepep* Bardelegatepep = new bardelegatepep();
    Peptidtabelle1->setItemDelegate(Bardelegatepep);

    QItemSelectionModel *selectionModel = Proteintabelle1->selectionModel();

    int indexofproteincoverage=0;
    int indexofnumberofpeptides=0;
    int indexofnumberofspectra=0;
    int indexofms2quant=0;
    int indexofconfidence=0;
    int indexofaccession=0;
    int indexofdescription=0;
    int checkboxColumn=0;

    int indexofsequencepep=0;
    int indexofstartpep=0;
    int indexofnumberofspectrapep=0;
    int indexofconfidencepep=0;
    int checkboxColumnPep=0;
    int indexofaccessionpep=0;

    //mzTab file parser
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
                QStringList Worter=line.split("\t");
                indexofproteincoverage=Worter.indexOf("protein_coverage");
                indexofnumberofpeptides=Worter.indexOf("num_peptides_distinct_ms_run[1]");
                indexofnumberofspectra=Worter.indexOf("num_psms_ms_run[1]");
                indexofms2quant=Worter.indexOf("protein_abundance_assay[1]");
                indexofconfidence=Worter.indexOf("best_search_engine_score[1]");
                indexofaccession=Worter.indexOf("accession");
                indexofdescription=Worter.indexOf("description");


            }

            if (line.startsWith("PRT")) model->insertRow(model->rowCount(), standardItemsList);

            if (line.startsWith("PSH")){
                QStringList Worter=line.split("\t");
                indexofsequencepep=Worter.indexOf("sequence");
                indexofconfidencepep=Worter.indexOf("search_engine_score[1]");
                indexofstartpep=Worter.indexOf("start");
                indexofaccessionpep=Worter.indexOf("accession");
                //spectraref


            }
            if (line.startsWith("PSM")) modelpep->insertRow(modelpep->rowCount(), standardItemsList);


        }
        //Füge Spalte für Checkbox hinzu
        model->insertColumn(model->columnCount());
        modelpep->insertColumn(modelpep->columnCount());


        checkboxColumn=model->columnCount()-1;
        checkboxColumnPep=modelpep->columnCount()-1;

        file.close();
    }

    //Checkboxen
    for(int row = 0; row < model->rowCount(); row++)
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

    for(int row = 0; row < modelpep->rowCount(); row++)
     {
        //instance of item
        QStandardItem* item;
        item = new QStandardItem(true);
        //set the box checkable
        item->setCheckable(true);
        //Sets the checkbox's check state to unchecked
        item->setCheckState(Qt::Unchecked);
        //put checkbox into each row of checkboxcolumn
        modelpep->setItem(row,checkboxColumnPep, item);
      }

//Überschriften Proteintabelle
    model->setHorizontalHeaderItem(indexofaccession, new QStandardItem(QString ("Accession")));
    model->setHorizontalHeaderItem(indexofconfidence, new QStandardItem(QString ("Confidence")));
    model->setHorizontalHeaderItem(indexofdescription, new QStandardItem(QString ("Description")));
    model->setHorizontalHeaderItem(indexofms2quant, new QStandardItem(QString ("MS2Quant")));
    model->setHorizontalHeaderItem(indexofnumberofpeptides, new QStandardItem(QString ("# Peptides")));
    model->setHorizontalHeaderItem(indexofnumberofspectra, new QStandardItem(QString ("# Spectra")));
    model->setHorizontalHeaderItem(indexofproteincoverage, new QStandardItem(QString ("Protein Coverage")));
    model->setHorizontalHeaderItem(checkboxColumn, new QStandardItem(QString("Checkbox")));


//Überschriften Peptidtabelle
    modelpep->setHorizontalHeaderItem(indexofconfidencepep, new QStandardItem(QString ("Confidence")));
    modelpep->setHorizontalHeaderItem(indexofnumberofspectrapep, new QStandardItem(QString("# Spectra")));
    modelpep->setHorizontalHeaderItem(indexofsequencepep, new QStandardItem(QString("Sequence")));
    modelpep->setHorizontalHeaderItem(indexofaccessionpep, new QStandardItem(QString("Accession")));
    modelpep->setHorizontalHeaderItem(checkboxColumnPep, new QStandardItem(QString("Checkbox")));


    //füge Spalte für Proteinreferenz hinzu
    modelpep->insertColumn(modelpep->columnCount());

    for (int i=0; i<modelpep->rowCount(); i++){
        QModelIndex index = modelpep->index(i, indexofaccessionpep, QModelIndex());
        QString data = modelpep->data(index).toString();
        QList<QVariant> indexlist;
        for (int j=0; j<model->rowCount(); j++){
            QModelIndex indexpro = model->index(j, indexofaccession,QModelIndex());
            if (model->data(indexpro) == data) indexlist.append(indexpro);
        }
        QModelIndex datenindex = modelpep->index(i, modelpep->columnCount()-1, QModelIndex());
        modelpep->setData(datenindex, indexlist);
    }

    for (int i=0; i<model->columnCount(); i++){
        if ((i != indexofaccession) && (i != indexofconfidence) && (i != indexofdescription) && (i != indexofms2quant)
                && (i != indexofnumberofpeptides) && (i != indexofnumberofspectra) && (i != indexofproteincoverage)
                && (i != checkboxColumn))
            Proteintabelle1->hideColumn(i);
    }

    for (int i = 0; i<modelpep->columnCount(); i++){
        if ((i != indexofsequencepep) && (i != indexofconfidencepep) && (i != indexofstartpep) && (i != checkboxColumnPep)
                && (i != indexofaccessionpep))
            Peptidtabelle1->hideColumn(i);
    }

    // SIGNALS UND SLOTS
            //Signal Slot Connection für Zeilenselektion
           QObject::connect(selectionModel, SIGNAL (selectionChanged(const QItemSelection &, const QItemSelection &)),
                            Peptidtabelle1 , SLOT (slotSelectionChanged(const QItemSelection &, const QItemSelection &)));

            //Signal Slot Connection für Deselect Button
            QObject::connect(deselectbutton, SIGNAL (clicked()), Peptidtabelle1, SLOT (handleButton()));



    splitter->show();
    return a.exec();
}


