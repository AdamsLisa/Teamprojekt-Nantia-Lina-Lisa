#include "myclass.h"
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>


void myClass::myFunction(int number, QStandardItemModel model, QString string){
        model->setHorizontalHeaderItem(number, new QStandardItem(string));

}



