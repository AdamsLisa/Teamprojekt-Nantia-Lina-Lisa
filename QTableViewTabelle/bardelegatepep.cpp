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

    //data to float
    float dataToFloat =index.data().toFloat();
    QRect rect = option.rect;

    //convert data to string
    QString dataToString = index.data().toString();

    //da Qt anscheinend alle QStandarditems zu float konvertieren kann, hier nun die Abfrage, ob wir tatsächlich eine Zahl vorliegen haben
    if (dataToString.startsWith("0") || dataToString.startsWith("1") || dataToString.startsWith("2") || dataToString.startsWith("3")
            || dataToString.startsWith("4") || dataToString.startsWith("5") || dataToString.startsWith("6") || dataToString.startsWith("7")
            || dataToString.startsWith("8") || dataToString.startsWith("9")){


        float maximum = index.model()->headerData(index.column(), Qt::Horizontal, 12).toFloat();

        if ((index.model()->headerData(index.column(),Qt::Horizontal)).toString() == "Start")
        {
            float s=(index.data().toFloat())/10;
            QRect rect = option.rect;
            rect.setLeft(rect.left() + s);
            float rectanglesize = 10;
            rect.setWidth(rectanglesize);
            painter->drawRect(rect);
        }

        else{


  //dann zeichnen wir das Rechteck der Länge Datenwert/Maximum, um einen Faktor <= 1 zu erhalten, damit der Balken im Tabellenfeld gut dargestellt wird
        rect.setWidth(rect.width()*(dataToFloat/maximum));
        painter->drawRect(rect);}
    }


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


