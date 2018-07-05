//#include "table.h"
#include "bardelegate.h"
#include "bardelegatepep.h"
#include "proteintabelle.h"
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

/*void slotSelectionChange(const QItemSelection &, const QItemSelection &)

{


            QModelIndexList selection = Proteintabelle->selectionModel();
           // for(int i=0; i< selection.count(); i++)
           // {
                QString Code = model->data(selection.at(1)).toString();
                for (int j=0; j<modelpep->rowcount(); j++){
                    QModelIndex index = modelpep->index(j,3, QModelIndex());

                    if (modelpep->data(index).toString() != Code) Peptidtabelle->hideRow(j);
                    else Peptidtabelle->showRow(j);
                }

           // }

}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplitter *splitter = new QSplitter;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItemModel *modelpep = new QStandardItemModel;
    QTableView *Proteintabelle2 = new Proteintabelle;
    QTableView *Peptidtabelle = new QTableView(splitter);
    Proteintabelle2->setModel(model);
    Peptidtabelle->setModel(modelpep);
    splitter->addWidget(Proteintabelle2);

    QPushButton *deselectbutton = new QPushButton(splitter);
    deselectbutton->setText("DESELECT");

    BarDelegate* bardelegate = new BarDelegate();
    Proteintabelle2->setItemDelegate(bardelegate);

    bardelegatepep* Bardelegatepep = new bardelegatepep();
    Peptidtabelle->setItemDelegate(Bardelegatepep);

    QItemSelectionModel *selectionModel = Proteintabelle2->selectionModel();


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
/*
                indexofproteincoverage=line.indexOf("protein_coverage");
                indexofnumberofpeptides=line.indexOf("num_peptides_distinct_ms_run[1]");
                indexofnumberofspectra=line.indexOf("num_psms_ms_run[1]");
                indexofms2quant=line.indexOf("protein_abundance_assay[1]");
                indexofconfidence=line.indexOf("best_search_engine_score[1]");
                indexofaccession=line.indexOf("accession");
                indexofdescription=line.indexOf("description");
                model->insertRow(model->rowCount(), standardItemsList);*/
}

            if (line.startsWith("PRT")) {model->insertRow(model->rowCount(), standardItemsList);}
            if (line.startsWith("PSM")) modelpep->insertRow(modelpep->rowCount(), standardItemsList);

        }
        file.close();
    }

    // SIGNALS UND SLOTS
            //Signal Slot Connection für Zeilenselektion
           // QObject::connect(Proteintabelle->selectionModel(), &QItemSelectionModel::selectionChanged(QItemSelection &, QItemSelection &), this ,slotSelectionChange(const QItemSelection &, const QItemSelection &));

            //Signal Slot Connection für Deselect Button
            QObject::connect(deselectbutton, SIGNAL (clicked()), Proteintabelle2, SLOT (handleButton()));



    splitter->show();
    return a.exec();
}


