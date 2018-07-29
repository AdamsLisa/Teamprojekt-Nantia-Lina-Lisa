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

    //QSplitter splitter ist der Hauptsplitter, der auch später angezeigt werden wird
    QSplitter *splitter = new QSplitter;
    //hier werden wir die Filter für die Proteintabelle hinzufügen
    QSplitter *filterareaprotein= new QSplitter;
    //hier werden wir die Filter für die Peptidtabelle hinzufügen
    QSplitter *filterareapeptide = new QSplitter;

    //Model für die Proteintabelle
    QStandardItemModel *model = new QStandardItemModel;
    //Model für die Peptidtabelle
    QStandardItemModel *modelPep = new QStandardItemModel;
    //View für Proteintabelle
    QTableView *ProteinTable = new Proteintabelle;
    //View für Peptidtabelle
    QTableView *PeptideTable = new Peptidtabelle;

    //set the orientation
    splitter->setOrientation(Qt::Vertical);

    //reset Filter button, der alle Filter resettet
    QPushButton *resetFilter = new QPushButton(splitter);
    resetFilter->setText("RESET ALL FILTERS");

    //Aufbau des Splitters: erst "Reset all Filters"-Button, dann Filter für Proteintabelle, dann Proteintabelle,
    //dann Filter für Peptidtabelle, dann Show-All-Peptides-Button, dann Peptidtabelle
    splitter->addWidget(filterareaprotein);
    splitter->addWidget(ProteinTable);
    splitter->addWidget(filterareapeptide);
    //add deselect button
    QPushButton *deselectButton = new QPushButton(splitter);
    deselectButton->setText("SHOW ALL PEPTIDES");

    splitter->addWidget(PeptideTable);



    //Bardelegate zur Darstellung der Balken in Proteintabelle
    BarDelegate* barDelegate = new BarDelegate();
    ProteinTable->setItemDelegate(barDelegate);

    //Bardelegate zur Darstellung der Balken in Peptidtabelle
    bardelegatepep* BarDelegatePep = new bardelegatepep();
    PeptideTable->setItemDelegate(BarDelegatePep);


//-------------------------------------------------------------------------------
//mzTab file parser
//--------------------------------------------------------------------------------


    //Variablen für Spalten, die wir darstellen wollen (dabei gehören alle Variablen mit Zusatz Pep zur Peptidtabelle
    int PiIndex=0 , ProtCovIndex = 0 ,  NumOfPept = 0 , NumOfSpectra = 0 , ms2Quant = 0 ,  ConfidenceIndex = 0 ,
    AccessionIndex = 0 , DescriptionIndex = 0 , checkboxColumn = 0, SeqPepIndex = 0 , StartPepIndex = 0 ,
    NumOfSpectrapep = 0 ,  ConfidenceIndexpep = 0 , checkboxColumnPep = 0 , AccessionIndexpep = 0 ;



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

            //Proteinheader; suche Spaltenindizes für Spalten, die wir anzeigen wollen
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

            //Peptidheader; suche Spaltenindizes für Spalten, die wir anzeigen wollen
            if (line.startsWith("PSH")){
                QStringList Worter=line.split("\t");
                SeqPepIndex=Worter.indexOf("sequence");
                ConfidenceIndexpep=Worter.indexOf("search_engine_score[1]");
                StartPepIndex=Worter.indexOf("start");
                AccessionIndexpep=Worter.indexOf("accession");

            }

            //Peptide: werden eingelesen
            if (line.startsWith("PSM")) modelPep->insertRow(modelPep->rowCount(), standardItemsList);


        }

        file.close();

         }

//------------------------------------------------------------------------------------------------------------------------
// FILTER
//-----------------------------------------------------------------------------------------------------------------------

//PROTEINTABELLE

 //durch Klick auf Header kann Tabelle aufsteigend oder absteigend sortiert werden
 ProteinTable->setSortingEnabled(true);

//Accession

  //ProxyModel für Accession Spalte
  QSortFilterProxyModel *proxyModelAccession = new QSortFilterProxyModel;
  //bei dem ersten erstellten QSortFilterProxyModel wird noch das QStandardItemModel als SourceModel gesetzt
  proxyModelAccession->setSourceModel(model);
  //QLineEdit zum Filtern der Accession-Spalte
  QLineEdit *lineEditAccession = new QLineEdit;
  //hier wird festgelegt, welche Spalte sortiert wird
  proxyModelAccession->setFilterKeyColumn(AccessionIndex);
  lineEditAccession->setPlaceholderText("Proteintabelle: Accession");
  filterareaprotein->addWidget(lineEditAccession);
  //Signal Slot Connection für Filter
   QObject::connect(lineEditAccession, SIGNAL(textEdited(QString)),proxyModelAccession,SLOT(setFilterFixedString(QString)));

   //Reset all Filters Connection
   QObject::connect(resetFilter, SIGNAL (clicked()), lineEditAccession, SLOT(clear()));
   QObject::connect(lineEditAccession, SIGNAL(textChanged(QString)),proxyModelAccession,SLOT(setFilterFixedString(QString)));

   //Reset nur für Accessionfilter
   //erst wird ein Button erstellt
   QPushButton *resetFilterAccession = new QPushButton(filterareaprotein);
   resetFilterAccession->setText("Reset Accession Filter");
   //dann wird der Button mit dem LineEdit verbunden
   QObject::connect(resetFilterAccession, SIGNAL (clicked()), lineEditAccession, SLOT(clear()));
   QObject::connect(lineEditAccession, SIGNAL(textChanged(QString)),proxyModelAccession,SLOT(setFilterFixedString(QString)));




   //Description

   //QLineEdit für Description Spalte
   QLineEdit *lineEditDescription = new QLineEdit;
   //ProxyModel für Description Spalte
   QSortFilterProxyModel *proxyModelDescription = new QSortFilterProxyModel;
   //hier wird als Source Model jetzt das zuletzt erstellte ProxyModel (hier von der Accession-Spalte) gesetzt
   proxyModelDescription->setSourceModel(proxyModelAccession);
   //Spalte fürs Filtern wird festgelegt
   proxyModelDescription->setFilterKeyColumn(DescriptionIndex);

   //Verbindung des LineEdits mit dem ProxyModel
   QObject::connect(lineEditDescription, SIGNAL(textEdited(QString)),proxyModelDescription,SLOT(setFilterFixedString(QString)));

   lineEditDescription->setPlaceholderText("Proteintabelle: Description");
   //Hinzufügen zum Splitter
   filterareaprotein->addWidget(lineEditDescription);

   //Reset bei Reset all Filters
   QObject::connect(resetFilter, SIGNAL (clicked()), lineEditDescription, SLOT(clear()));
   QObject::connect(lineEditDescription, SIGNAL(textChanged(QString)),proxyModelDescription,SLOT(setFilterFixedString(QString)));

   //Reset nur von Description Filter
   QPushButton *resetFilterDescription = new QPushButton(filterareaprotein);
   resetFilterDescription->setText("Reset Description Filter");
   QObject::connect(resetFilterDescription, SIGNAL (clicked()), lineEditDescription, SLOT(clear()));
   QObject::connect(lineEditDescription, SIGNAL(textChanged(QString)),proxyModelDescription,SLOT(setFilterFixedString(QString)));


   //Am Ende wird nun das letzte ProxyModel als Model für die Tabelle gesetzt
   ProteinTable->setModel(proxyModelDescription);

//PEPTIDTABELLE

   //durch Klick auf Header kann Tabelle aufsteigend oder absteigend sortiert werden
      PeptideTable->setSortingEnabled(true);

//Accession


   //ProxyModel für AccessionSpalte
   QSortFilterProxyModel *proxyModelAccessionPep = new QSortFilterProxyModel;
   //da dies das erste erstelle ProxyModel ist, bekommt es als SourceModel das QStandardItemModel
   proxyModelAccessionPep->setSourceModel(modelPep);
   //QLineEdit für AccessionSpalte
   QLineEdit *lineEditAccessionPep = new QLineEdit;
   //lege Index der Spalte, die gefiltert werden soll, fest
   proxyModelAccessionPep->setFilterKeyColumn(AccessionIndexpep);
   lineEditAccessionPep->setPlaceholderText("Peptidtabelle: Accession");
   filterareapeptide->addWidget(lineEditAccessionPep);
   //Signal Slot Connection für Filter
   QObject::connect(lineEditAccessionPep, SIGNAL(textEdited(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));

   //Reset für Reset All Filters
   QObject::connect(resetFilter, SIGNAL (clicked()), lineEditAccessionPep, SLOT(clear()));
   QObject::connect(lineEditAccessionPep, SIGNAL(textChanged(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));

   //Reset des Filters bei Show All Peptides
   QObject::connect(deselectButton, SIGNAL (clicked()), lineEditAccessionPep, SLOT(clear()));
   QObject::connect(lineEditAccessionPep, SIGNAL(textChanged(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));

   //Reset für Accession
   QPushButton *resetFilterAccessionPep = new QPushButton(filterareapeptide);
   resetFilterAccessionPep->setText("Reset Accession Filter");
   QObject::connect(resetFilterAccessionPep, SIGNAL (clicked()), lineEditAccessionPep, SLOT(clear()));
   QObject::connect(lineEditAccessionPep, SIGNAL(textChanged(QString)),proxyModelAccessionPep,SLOT(setFilterFixedString(QString)));


//Sequence
   //LineEdit zum Filtern der Sequence Spalte
   QLineEdit *lineEditSequencePep = new QLineEdit;
   //ProxyModel für Sequence Spalte
   QSortFilterProxyModel *proxyModelSequencePep = new QSortFilterProxyModel;
   //als SourceModel wird das letzte ProxyModel erstellt
   proxyModelSequencePep->setSourceModel(proxyModelAccessionPep);
   //Index der zu filternden Spalte wird ProxyModel übergeben
   proxyModelSequencePep->setFilterKeyColumn(SeqPepIndex);

   //Signal-Slot Connection
   QObject::connect(lineEditSequencePep, SIGNAL(textEdited(QString)),proxyModelSequencePep,SLOT(setFilterFixedString(QString)));
   lineEditSequencePep->setPlaceholderText("Peptidtabelle: Sequence");
   filterareapeptide->addWidget(lineEditSequencePep);

    //Reset für Reset All Filters
   QObject::connect(resetFilter, SIGNAL (clicked()), lineEditSequencePep, SLOT(clear()));
   QObject::connect(lineEditSequencePep, SIGNAL(textChanged(QString)),proxyModelSequencePep,SLOT(setFilterFixedString(QString)));

   //Reset bei Show ALL Peptides
   QObject::connect(deselectButton, SIGNAL (clicked()), lineEditSequencePep, SLOT(clear()));
   QObject::connect(lineEditSequencePep, SIGNAL(textChanged(QString)),proxyModelSequencePep,SLOT(setFilterFixedString(QString)));

   //Reset für Sequenece-Filter
   QPushButton *resetFilterSequencePep = new QPushButton(filterareapeptide);
   resetFilterSequencePep->setText("Reset Sequence Filter");
   QObject::connect(resetFilterSequencePep, SIGNAL (clicked()), lineEditSequencePep, SLOT(clear()));
   QObject::connect(lineEditSequencePep, SIGNAL(textChanged(QString)),proxyModelSequencePep,SLOT(setFilterFixedString(QString)));


   //hier wird zusätzlich die Auswahl der Proteintabelle zurückgesetzt
   QObject::connect(resetFilterSequencePep, SIGNAL(clicked()), ProteinTable->selectionModel(), SLOT(clearSelection()));
   QObject::connect(resetFilterSequencePep, SIGNAL(clicked()), PeptideTable, SLOT(handleButton()));


   //abschließend wird das letzte ProxyModel als Model der Peptidtabelle gesetzt
   PeptideTable->setModel(proxyModelSequencePep);



//--------------------------------------------------------------------------------------------------------
// CHECKBOXEN
//--------------------------------------------------------------------------------------------------------
   //Füge Spalte für Checkbox hinzu
   model->insertColumn(model->columnCount());
   modelPep->insertColumn(modelPep->columnCount());


   //Checkbox soll in letzte Spalte eingefügt werden
   checkboxColumn=model->columnCount()-1;
   checkboxColumnPep=modelPep->columnCount()-1;

//Proteintabelle
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

 //Peptidtabelle
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
    model->setHorizontalHeaderItem(PiIndex,new QStandardItem(QString("PI")));
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

    //wenn Index der Spalte nicht mit einem der am Anfang definierten Indizes, die wir für Spalten die wir anzeigen wollen, definiert haben,
    //übereinstimmt, wird die Spalte versteckt

    //Proteintabelle
    for (int i=0; i<model->columnCount(); i++)
    {
        if ((i != AccessionIndex) && (i != ConfidenceIndex) && (i != DescriptionIndex) && (i != ms2Quant)
                && (i != NumOfPept) && (i != NumOfSpectra) && (i != ProtCovIndex)
                && (i != checkboxColumn) && (i != PiIndex))
        ProteinTable->hideColumn(i);
    }

    //Peptidtabelle
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

 //12: Accessible Description Role im Header
 int accessibledescriptionrole = 12;

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
    model->setHeaderData(j, Qt::Horizontal, maximum, accessibledescriptionrole);
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
    modelPep->setHeaderData(j, Qt::Horizontal, maximum, accessibledescriptionrole);
}



//-------------------------------------------------------------------------------------------------------------------------
// Verbinden der Tabellen
//-------------------------------------------------------------------------------------------------------------------------
//Signal Slot Connection für Zeilenselektion
QObject::connect(ProteinTable->selectionModel(), SIGNAL (selectionChanged(const QItemSelection &, const QItemSelection &)),
                    PeptideTable , SLOT (slotSelectionChanged(const QItemSelection &, const QItemSelection &)));

//Signal Slot Connection für Deselect Button
QObject::connect(deselectButton, SIGNAL (clicked()), PeptideTable, SLOT (handleButton()));


splitter->show();
return a.exec();



}
