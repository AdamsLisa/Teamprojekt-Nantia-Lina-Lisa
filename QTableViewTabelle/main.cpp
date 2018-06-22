#include "table.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    table w;
    w.show();

    MainWindow m;
    m.show();


    return a.exec();
}
