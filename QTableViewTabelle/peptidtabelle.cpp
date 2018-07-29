#include "peptidtabelle.h"
#include <QTableView>

Peptidtabelle::Peptidtabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Peptidtabelle::handleButton()
{

    //zeige alle Reihen der Peptidtabelle an
    for (int i= 0; i<this->model()->rowCount(); i++){
       this->showRow(i);
    }
}

void Peptidtabelle::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    QModelIndexList selection = selected.indexes();

    for (int l=0; l<this->model()->rowCount(); l++){
        //hide row
        this->hideRow(l);
    }


int Accessionspalte = 0;
for (int i=0; i<this->model()->columnCount(); i++){
    QString headerdata = this->model()->headerData(i,Qt::Horizontal).toString();
    if (headerdata == new QString("Accession")) Accessionspalte=i;
}


    for (int i=0; i<selection.count(); i++){
        for (int j=0; j<this->model()->rowCount(); j++){
            QVariant daten = selection.at(i).data();
            QModelIndex index = this->model()->index(j,Accessionspalte,QModelIndex());
            QVariant datenpep= this->model()->data(index);
            if (daten.toString() == datenpep.toString()) this->showRow(j);
        }
    }



}

