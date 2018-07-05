#include "peptidtabelle.h"
#include <QTableView>

Peptidtabelle::Peptidtabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Peptidtabelle::slotSelectionChange(const QItemSelection &selected, const QItemSelection &deselected)

{


            /*select = new QItemSelectionModel;
            QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
           // for(int i=0; i< selection.count(); i++)
           // {
                QString Code = model->data(selection.at(1)).toString();
                for (int j=0; j<TableRowPep; j++){
                    QModelIndex index = modelpep->index(j,3, QModelIndex());

                    if (modelpep->data(index).toString() != Code) ui->tableView_2->hideRow(j);
                    else ui->tableView_2->showRow(j);
                }

           // }*/

}

