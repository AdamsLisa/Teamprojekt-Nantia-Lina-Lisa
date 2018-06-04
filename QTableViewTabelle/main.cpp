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
}

