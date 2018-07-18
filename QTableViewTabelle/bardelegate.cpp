#include "bardelegate.h"
#include <QtWidgets>
#include <QSpinBox>
#include <iostream>
#include <array>

BarDelegate::BarDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

//paint function from QItemDelegate
void BarDelegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

    //saves the current painter state
    painter->save();
    //sets the given render hint on the painter
    painter->setRenderHint(QPainter::Antialiasing, true);
    //sets the color
    painter->setBrush(QBrush(Qt::green));

    //convert data to float
    float dataToFloat =index.data().toFloat();
    QRect rect = option.rect;
    QRect rect2 = option.rect;
    QRect rect3 = option.rect;

    //convert data to string
    QString dataToString = index.data().toString();


    //If-Bedingung, damit nur bestimmte Spalten Balken anzeigen
    if (((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "Confidence")||
        ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "# Peptides") ||
        ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "MS2Quant") ||
        ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "# Spectra") ||
        ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "Protein Coverage"))
    {


         //Maximum im Header
         float maximum = index.model()->headerData(index.column(), Qt::Horizontal, 12).toFloat();


         //dann zeichnen wir das Rechteck der Länge Datenwert/Maximum, um einen Faktor <= 1 zu erhalten,
         //damit der Balken im Tabellenfeld gut dargestellt wird
         rect.setWidth(rect.width()*(dataToFloat/maximum));
         painter->drawRect(rect);
         if (((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "# Peptides") ||
              ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "# Spectra"))
               {

                   painter->setBrush(QBrush(Qt::green));
                   //rect2.setWidth(rect.width()*(v*0.1));
                   rect2.setWidth(rect.width()*(dataToFloat/maximum*0.05));
                   painter->drawRect(rect);
                   painter->setBrush(QBrush(Qt::yellow));
                   //rect3.setWidth(rect.width()*(v*0.01));
                   rect3.setWidth(rect.width()*(dataToFloat/maximum*0.4));
                   painter->drawRect(rect3);

                   painter->setBrush(QBrush(Qt::red));
                   //rect2.setWidth(rect.width()*(0.005*v));
                   rect2.setWidth(rect.width()*(0.1*dataToFloat/maximum));
                   rect2.united(rect);
                   rect2.united(rect3);
                   painter->drawRect(rect2);



               }
    }


    else
    {
      QStyledItemDelegate::paint(painter, option, index);
    }

    //restores the current painter state
    painter->restore();

}


void BarDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
