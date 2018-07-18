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
