#include "table.h"
#include <QApplication>
#include <QtWidgets>
#include "bardelegate.h"

#include <QHeaderView>
#include <QStandardItemModel>
#include <QTableView>
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        table w;
        w.show();
        return a.exec();
    /*    QStandardItemModel model(20, 12);
        QTableView tableView;
        tableView.setModel(&model);

        BarDelegate delegate;
        tableView.setItemDelegate(&delegate);

        tableView.horizontalHeader()->setStretchLastSection(true);


                //Spaltennamen
                model.setHorizontalHeaderItem(0, new QStandardItem(QString ("")));
                model.setHorizontalHeaderItem(1, new QStandardItem(QString ("Pl")));
                model.setHorizontalHeaderItem(2, new QStandardItem(QString ("Accession")));
                model.setHorizontalHeaderItem(3, new QStandardItem(QString ("Description")));
                model.setHorizontalHeaderItem(4, new QStandardItem(QString ("Chr.")));
                model.setHorizontalHeaderItem(5, new QStandardItem(QString ("Coverage")));
                model.setHorizontalHeaderItem(6, new QStandardItem(QString ("#Peptides")));
                model.setHorizontalHeaderItem(7, new QStandardItem(QString ("#Spectra")));
                model.setHorizontalHeaderItem(8, new QStandardItem(QString ("MS2 Quant")));
                model.setHorizontalHeaderItem(9, new QStandardItem(QString ("MW")));
                model.setHorizontalHeaderItem(10, new QStandardItem(QString ("Confidence")));
                model.setHorizontalHeaderItem(11, new QStandardItem(QString ("Checkbox")));


        for(int row = 0; row < 20; row++)
         {
             QStandardItem* item;
             item = new QStandardItem(true);
             item->setCheckable(true);
             item->setCheckState(Qt::Unchecked);
             model.setItem(row,11, item);
         }
        for (int row = 0; row < 20; row++){
            for(int column =1; column < 2; ++column){
                QModelIndex index = model.index(row,column, QModelIndex());
              model.setData(index,QVariant((row + 1)*(column +1)));
            }
        }

        tableView.setWindowTitle(QObject::tr("Our Delegate"));
        tableView.show();
        return a.exec();
        */

}

