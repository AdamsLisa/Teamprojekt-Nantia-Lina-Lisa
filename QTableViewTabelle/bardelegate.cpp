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


    float v=index.data().toFloat();
   QRect rect = option.rect;
    //QRect rect2 = option.rect;
    //QRect rect3 = option.rect;

    /*

        painter->setBrush(QBrush(Qt::red));
        //rect2.setWidth(rect.width()*(v*0.1));
        rect2.setWidth(rect.width()*(v*0.005));
        painter->drawRect(rect);
        painter->setBrush(QBrush(Qt::yellow));
        //rect3.setWidth(rect.width()*(v*0.01));
        rect3.setWidth(rect.width()*(v*0.004));
        painter->drawRect(rect3);

        painter->setBrush(QBrush(Qt::green));
        //rect2.setWidth(rect.width()*(0.005*v));
        rect2.setWidth(rect.width()*(0.003*v));
        rect2.united(rect);
        rect2.united(rect3);
        painter->drawRect(rect2);*/



    QString dataalsstring = index.data().toString();

    //da Qt anscheinend alle QStandarditems zu float konvertieren kann, hier nun die Abfrage, ob wir tatsächlich eine Zahl vorliegen haben
    if (dataalsstring.startsWith("0") || dataalsstring.startsWith("1") || dataalsstring.startsWith("2") || dataalsstring.startsWith("3")
            || dataalsstring.startsWith("4") || dataalsstring.startsWith("5") || dataalsstring.startsWith("6") || dataalsstring.startsWith("7")
            || dataalsstring.startsWith("8") || dataalsstring.startsWith("9"))
    {


     //Maximum im Header
     float maximum = index.model()->headerData(index.column(), Qt::Horizontal, 12).toFloat();


  //dann zeichnen wir das Rechteck der Länge Datenwert/Maximum, um einen Faktor <= 1 zu erhalten, damit der Balken im Tabellenfeld gut dargestellt wird
        rect.setWidth(rect.width()*(v/maximum));
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
