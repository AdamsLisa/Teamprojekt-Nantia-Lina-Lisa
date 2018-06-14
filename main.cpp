#include "table.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    table t;
    t.show();

    return a.exec();
}

