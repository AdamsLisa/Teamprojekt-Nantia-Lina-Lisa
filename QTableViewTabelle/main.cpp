#include "bardelegate.h"
#include "bardelegatepep.h"
#include "proteintabelle.h"
#include "peptidtabelle.h"
#include <QApplication>
#include <QSplitter>
#include <QSplitterHandle>
#include <array>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <lineeditdelegate.h>
#include <QLineEdit>
#include <QFile>


int main(int argc, char *argv[])
{

//---------------------------------------------------------------
// Definition von Model, View, ...
//---------------------------------------------------------------

    //Instance for managing the GUI application
    QApplication a(argc, argv);


    //Open QFileDialog to select files
    QFile file(QFileDialog::getOpenFileName());

    //Split the window and create 2 tables
    QSplitter *splitter = new QSplitter;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelPep = new QStandardItemModel;
    QTableView *ProteinTable = new Proteintabelle;
    QTableView *PeptideTable = new Peptidtabelle;

    //add the two tables
    splitter->addWidget(ProteinTable);
    splitter->addWidget(PeptideTable);
    //set the orientation
    splitter->setOrientation(Qt::Vertical);

    //add deselect button
    QPushButton *deselectButton = new QPushButton(splitter);
    deselectButton->setText("SHOW ALL");

    //instance for protein table
    BarDelegate* barDelegate = new BarDelegate();
    ProteinTable->setItemDelegate(barDelegate);

    //instance for peptide table
    bardelegatepep* BarDelegatePep = new bardelegatepep();
    PeptideTable->setItemDelegate(BarDelegatePep);


//-------------------------------------------------------------------------------
//mzTab file parser
//--------------------------------------------------------------------------------


    //Variablen für Spalten
    int ProtCovIndex=0;
    int NumOfPept=0;
    int NumOfSpectra=0;
    int ms2Quant=0;
    int ConfidenceIndex=0;
    int AccessionIndex=0;
    int DescriptionIndex=0;
    int checkboxColumn=0;

    int SeqPepIndex=0;
    int StartPepIndex=0;
    int NumOfSpectrapep=0;
    int ConfidenceIndexpep=0;
    int checkboxColumnPep=0;
    int AccessionIndexpep=0;


    //QFile file("/home/nantia/Teamprojekt 2018/SILAC_mzTab");
    //QFile file("C:\\Users\\Lisa Adams\\Documents\\_Studium\\Teamprojekt\\SILAC_CQI.mzTab");
    //QFile file("/home/lina/Teamprojekt/examples/SILAC_CQI.mzTab");

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

            //Proteinheader; suche Spalten
            if (line.startsWith("PRH")) {
                QStringList Worter=line.split("\t");
                ProtCovIndex=Worter.indexOf("protein_coverage");
                NumOfPept=Worter.indexOf("num_peptides_distinct_ms_run[1]");
                NumOfSpectra=Worter.indexOf("num_psms_ms_run[1]");
                ms2Quant=Worter.indexOf("protein_abundance_assay[1]");
                ConfidenceIndex=Worter.indexOf("best_search_engine_score[1]");
                AccessionIndex=Worter.indexOf("accession");
                DescriptionIndex=Worter.indexOf("description");


            }

            //Proteine: werden eingelesen
            if (line.startsWith("PRT")) model->insertRow(model->rowCount(), standardItemsList);

            //Peptidheader; suche Spalten
            if (line.startsWith("PSH")){
                QStringList Worter=line.split("\t");
                SeqPepIndex=Worter.indexOf("sequence");
                ConfidenceIndexpep=Worter.indexOf("search_engine_score[1]");
                StartPepIndex=Worter.indexOf("start");
                AccessionIndexpep=Worter.indexOf("accession");
                //spectraref


            }

            //Peptide: werden eingelesen
            if (line.startsWith("PSM")) modelPep->insertRow(modelPep->rowCount(), standardItemsList);


        }

//------------------------------------------------------------------------------------------------------------------------
// FILTER
//-----------------------------------------------------------------------------------------------------------------------

//PROTEINTABELLE
//Accession
  QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
  QSortFilterProxyModel *proxyModelAccessionPep = new QSortFilterProxyModel;
  proxyModel->setSourceModel(model);
  QLineEdit *lineEditAccession = new QLineEdit;
  ProteinTable->setSortingEnabled(true);
  proxyModel->setFilterKeyColumn(AccessionIndex);
  lineEditAccession->setText("Proteintabelle: Accession");
  splitter->addWidget(lineEditAccession);
  //Signal Slot Connection für Filter
   QObject::connect(lineEditAccession, SIGNAL(textEdited(QString)),proxyModel,SLOT(setFilterFixedString(QString)));
   QObject::connect(lineEditAccession, SIGNAL(textEdited(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));

   //Description
   QLineEdit *lineEditDescription = new QLineEdit;
   QSortFilterProxyModel *proxyModelDescription = new QSortFilterProxyModel;
   proxyModelDescription->setSourceModel(proxyModel);
   proxyModelDescription->setFilterKeyColumn(DescriptionIndex);
   QObject::connect(lineEditDescription, SIGNAL(textEdited(QString)),proxyModelDescription,SLOT(setFilterFixedString(QString)));
   lineEditDescription->setText("Proteintabelle: Description");
   splitter->addWidget(lineEditDescription);

   ProteinTable->setModel(proxyModelDescription);

//PEPTIDTABELLE
//Accession

   proxyModelAccessionPep->setSourceModel(modelPep);
   QLineEdit *lineEditAccessionPep = new QLineEdit;
   PeptideTable->setSortingEnabled(true);
   proxyModelAccessionPep->setFilterKeyColumn(AccessionIndexpep);
   lineEditAccessionPep->setText("Peptidtabelle: Accession");
   splitter->addWidget(lineEditAccessionPep);
   //Signal Slot Connection für Filter
   QObject::connect(lineEditAccessionPep, SIGNAL(textEdited(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));

//Sequence
   QLineEdit *lineEditSequencePep = new QLineEdit;
   QSortFilterProxyModel *proxyModelSequencePep = new QSortFilterProxyModel;
   proxyModelSequencePep->setSourceModel(proxyModelAccessionPep);
   proxyModelSequencePep->setFilterKeyColumn(SeqPepIndex);
   QObject::connect(lineEditSequencePep, SIGNAL(textEdited(QString)),proxyModelSequencePep,SLOT(setFilterFixedString(QString)));
   lineEditSequencePep->setText("Peptidtabelle: Sequence");
   splitter->addWidget(lineEditSequencePep);

   PeptideTable->setModel(proxyModelSequencePep);


//--------------------------------------------------------------------------------------------------------
// CHECKBOXEN
//--------------------------------------------------------------------------------------------------------
   //Füge Spalte für Checkbox hinzu
   model->insertColumn(model->columnCount());
   modelPep->insertColumn(modelPep->columnCount());


   checkboxColumn=model->columnCount()-1;
   checkboxColumnPep=modelPep->columnCount()-1;

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

    for(int row = 0; row < modelPep->rowCount(); row++)
     {
        //instance of item
        QStandardItem* item;
        item = new QStandardItem(true);
        //set the box checkable
        item->setCheckable(true);
        //Sets the checkbox's check state to unchecked
        item->setCheckState(Qt::Unchecked);
        //put checkbox into each row of checkboxcolumn
        modelPep->setItem(row,checkboxColumnPep, item);
      }


//-----------------------------------------------------------------------------------------------------------
//ÜBERSCHRIFTEN
//-----------------------------------------------------------------------------------------------------------

//Überschriften Proteintabelle
    model->setHorizontalHeaderItem(AccessionIndex, new QStandardItem(QString ("Accession")));
    model->setHorizontalHeaderItem(ConfidenceIndex, new QStandardItem(QString ("Confidence")));
    model->setHorizontalHeaderItem(DescriptionIndex, new QStandardItem(QString ("Description")));
    model->setHorizontalHeaderItem(ms2Quant, new QStandardItem(QString ("MS2Quant")));
    model->setHorizontalHeaderItem(NumOfPept, new QStandardItem(QString ("# Peptides")));
    model->setHorizontalHeaderItem(NumOfSpectra, new QStandardItem(QString ("# Spectra")));
    model->setHorizontalHeaderItem(ProtCovIndex, new QStandardItem(QString ("Protein Coverage")));
    model->setHorizontalHeaderItem(checkboxColumn, new QStandardItem(QString("Checkbox")));


//Überschriften Peptidtabelle
    modelPep->setHorizontalHeaderItem(ConfidenceIndexpep, new QStandardItem(QString ("Confidence")));
    modelPep->setHorizontalHeaderItem(NumOfSpectrapep, new QStandardItem(QString("# Spectra")));
    modelPep->setHorizontalHeaderItem(SeqPepIndex, new QStandardItem(QString("Sequence")));
    modelPep->setHorizontalHeaderItem(AccessionIndexpep, new QStandardItem(QString("Accession")));
    modelPep->setHorizontalHeaderItem(StartPepIndex, new QStandardItem(QString("Start")));
    modelPep->setHorizontalHeaderItem(checkboxColumnPep, new QStandardItem(QString("Checkbox")));



//-----------------------------------------------------------------------------------------------------------------
//Zeige nur gewünschte Spalten an
//-----------------------------------------------------------------------------------------------------------------

    for (int i=0; i<model->columnCount(); i++)
    {
        if ((i != AccessionIndex) && (i != ConfidenceIndex) && (i != DescriptionIndex) && (i != ms2Quant)
                && (i != NumOfPept) && (i != NumOfSpectra) && (i != ProtCovIndex)
                && (i != checkboxColumn))
        ProteinTable->hideColumn(i);
    }

    for (int i = 0; i<modelPep->columnCount(); i++)
    {
        if ((i != SeqPepIndex) && (i != ConfidenceIndexpep) && (i != StartPepIndex) && (i != checkboxColumnPep)
                && (i != AccessionIndexpep))
        PeptideTable->hideColumn(i);
    }


//-----------------------------------------------------------------------------------------
//Maximumsbestimmung
//-----------------------------------------------------------------------------------------

// FÜR PROTEINTABELLE



    //gehe jede Spalte durch und suche jeweils das Maximum
    for (int j=0; j<model->columnCount(); j++)
    {
        float maximum =1;
        QModelIndex index;

    for (int i=0; i<(model->rowCount()); i++)
    {
        index = model->index(i,j,QModelIndex());
        if (index.data().canConvert<float>())
        {
            float wert = index.data().toFloat();
            if (wert > maximum) maximum = wert;
        }

    }

    //schreibe das Maximum in den Header
    //12: Description Role im Header
    model->setHeaderData(j, Qt::Horizontal, maximum, 12);
}


// FÜR PEPTIDTABELLE

    //gehe jede Spalte durch und suche jeweils das Maximum
    for (int j=0; j<modelPep->columnCount(); j++)
    {
        float maximum =1;
        QModelIndex index;
    for (int i=0; i<(modelPep->rowCount()); i++)
    {
        index = modelPep->index(i,j,QModelIndex());
        if (index.data().canConvert<float>())
        {
            float wert = index.data().toFloat();
            if (wert > maximum) maximum = wert;
        }

    }
    //schreibe das Maximum in den Header
    //12: Description role im Header
    modelPep->setHeaderData(j, Qt::Horizontal, maximum, 12);
}



//-------------------------------------------------------------------------------------------------------------------------
// SIGNALS UND SLOTS
//-------------------------------------------------------------------------------------------------------------------------
//Signal Slot Connection für Zeilenselektion
QObject::connect(ProteinTable->selectionModel(), SIGNAL (selectionChanged(const QItemSelection &, const QItemSelection &)),
                    PeptideTable , SLOT (slotSelectionChanged(const QItemSelection &, const QItemSelection &)));

//Signal Slot Connection für Deselect Button
QObject::connect(deselectButton, SIGNAL (clicked()), PeptideTable, SLOT (handleButton()));



splitter->show();
return a.exec();



}
