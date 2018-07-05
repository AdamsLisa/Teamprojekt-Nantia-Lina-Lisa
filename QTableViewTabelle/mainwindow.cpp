#include "mainwindow.h"
#include <QItemSelection>
#include <QItemSelectionModel>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{}

void MainWindow::slotSelectionChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndex index;
    QModelIndexList items = selected.indexes();
    foreach(index,items){
        //QString text = QString("(%1, %2")).arg(index.row()).arg(index.column());
        //model->setData(index,text);
    }

}
