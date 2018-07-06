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
    QApplication a(argc, argv);
    QSplitter *splitter = new QSplitter;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelpep = new QStandardItemModel;
    QTableView *Proteintabelle1 = new Proteintabelle;
    QTableView *Peptidtabelle1 = new Peptidtabelle;
    Proteintabelle1->setModel(model);
    Peptidtabelle1->setModel(modelpep);
    splitter->addWidget(Proteintabelle1);
    splitter->addWidget(Peptidtabelle1);

    QPushButton *deselectbutton = new QPushButton(splitter);
    deselectbutton->setText("DESELECT");

    BarDelegate* bardelegate = new BarDelegate();
    Proteintabelle1->setItemDelegate(bardelegate);

    bardelegatepep* Bardelegatepep = new bardelegatepep();
    Peptidtabelle1->setItemDelegate(Bardelegatepep);

    QItemSelectionModel *selectionModel = Proteintabelle1->selectionModel();

    int indexofproteincoverage;
    int indexofnumberofpeptides;
    int indexofnumberofspectra;
    int indexofms2quant;
    int indexofconfidence;
    int indexofaccession;
    int indexofdescription;


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
               /*QString line2 = in.readLine();
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

            if (line.startsWith("PRT")) {model->insertRow(model->rowCount(), standardItemsList);}
            if (line.startsWith("PSM")) modelpep->insertRow(modelpep->rowCount(), standardItemsList);

        }
        file.close();
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


