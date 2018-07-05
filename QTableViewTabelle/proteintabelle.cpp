#include "proteintabelle.h"
#include <QTableView>

Proteintabelle::Proteintabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Proteintabelle::handleButton()
{
    for (int i= 0; i<this->model()->rowCount(); i++){
       this->showRow(i);
    }
}
