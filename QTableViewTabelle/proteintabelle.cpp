#include "proteintabelle.h"
#include <QTableView>

Proteintabelle::Proteintabelle(QWidget *parent)
    : QTableView(parent)
{

}

void Proteintabelle::handleButton()
{
   this->hideRow(1);
}
