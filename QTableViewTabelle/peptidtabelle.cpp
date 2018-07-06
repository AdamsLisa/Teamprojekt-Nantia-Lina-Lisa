#include "peptidtabelle.h"
#include <QTableView>

Peptidtabelle::Peptidtabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Peptidtabelle::handleButton()
{
    for (int i= 0; i<this->model()->rowCount(); i++){
       this->showRow(i);
    }
}

void Peptidtabelle::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    QModelIndexList selection = selected.indexes();

            for(int i=0; i< selection.count(); i++)
            {
                this->hideRow(selection.at(i).row());
            }

               /* QString Code = model->data(selection.at(1)).toString();
                for (int j=0; j<TableRowPep; j++){
                    QModelIndex index = modelpep->index(j,3, QModelIndex());

                    if (modelpep->data(index).toString() != Code) ui->tableView_2->hideRow(j);
                    else ui->tableView_2->showRow(j);
                }

           // }*/

}

