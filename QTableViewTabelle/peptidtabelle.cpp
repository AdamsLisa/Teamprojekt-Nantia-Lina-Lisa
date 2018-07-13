#include "peptidtabelle.h"
#include <QTableView>

Peptidtabelle::Peptidtabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Peptidtabelle::handleButton()
{

    //zeige alle Reihen der Peptidtabelle an
    for (int i= 0; i<this->model()->rowCount()-1; i++){
       this->showRow(i);
    }
}

void Peptidtabelle::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    QModelIndexList selection = selected.indexes();
    for (int l=0; l<this->model()->rowCount(); l++){
        this->hideRow(l);
    }
    for (int i=0; i<selection.count(); i++){
        for (int j=0; j<this->model()->rowCount(); j++){
            QModelIndex index = this->model()->index(j, (this->model()->columnCount())-1, QModelIndex());
            //suche passende Proteinindexe in letzter Spalte des Peptidmodels
            QList<QVariant> indexes = this->model()->data(index).toList();
            //vergleiche Proteinindizes mit Indizes von aktuell selektiertem
            for (int k=0; k<indexes.count(); k++){
                if (indexes.at(k) == selection.at(i)) this->showRow(j);
            }
        }

    }

}

