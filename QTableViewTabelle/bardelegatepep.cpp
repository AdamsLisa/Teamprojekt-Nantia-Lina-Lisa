#include "bardelegatepep.h"
#include <QtWidgets>
#include <QSpinBox>
#include <iostream>

bardelegatepep::bardelegatepep(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


//paint function from QItemDelegate
void bardelegatepep::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    //saves the current painter state
    painter->save();
    //sets the given render hint on the painter
    painter->setRenderHint(QPainter::Antialiasing, true);

    //sets the color
    painter->setBrush(QBrush(Qt::green));

    float v=index.data().toFloat();
    QRect rect = option.rect;


    QString dataalsstring = index.data().toString();

    //da Qt anscheinend alle QStandarditems zu float konvertieren kann, hier nun die Abfrage, ob wir tatsächlich eine Zahl vorliegen haben
    if (dataalsstring.startsWith("0") || dataalsstring.startsWith("1") || dataalsstring.startsWith("2") || dataalsstring.startsWith("3")
            || dataalsstring.startsWith("4") || dataalsstring.startsWith("5") || dataalsstring.startsWith("6") || dataalsstring.startsWith("7")
            || dataalsstring.startsWith("8") || dataalsstring.startsWith("9")){


     //in last holen wir uns den Index der letzten Zeile der aktuellen Spalte
     QModelIndex last = index.model()->index((index.model()->rowCount())-1, index.column(), QModelIndex());
     //denn hier steht das Maximum
    float maximum = index.model()->data(last).toFloat();

  //dann zeichnen wir das Rechteck der Länge Datenwert/Maximum, um einen Faktor <= 1 zu erhalten, damit der Balken im Tabellenfeld gut dargestellt wird
        rect.setWidth(rect.width()*(v/maximum));
        painter->drawRect(rect);
    }

//NOCH TO DO: kleinerer Balken bei Start Column
    /*
     if (index.column() == 5)
    {
        float v=(index.data().toFloat())/40;
        QRect rect = option.rect;
        rect.setLeft(rect.left() + v);
        float rectanglesize = 10;
        rect.setWidth(rectanglesize);
        painter->drawRect(rect);
    }
*/



    else
    {
      QStyledItemDelegate::paint(painter, option, index);
    }

    //restores the current painter state
    painter->restore();



}

void bardelegatepep::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


