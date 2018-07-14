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

    //creates an array with numbers from 1 to 10
    int numbers[] = {0,1,2,3,4,5,6,7,8,9,10};

    float v=index.data().toFloat();
    QRect rect = option.rect;
    QRect rect2 = option.rect;
    QRect rect3 = option.rect;

    /*
//********************************************************************
// getting the maximum value of a column

    //model instance
    QStandardItemModel *model = new QStandardItemModel;
    model->insertRow(model->rowCount());

    int dataColumn = 2; // The column with the data

    //current value
    QVariant content = index.data().toFloat();
    //last value
    QModelIndex last = index.model()->index((index.model()->rowCount())-1, index.column(), QModelIndex());
    //maximum value
    float maximum = index.model()->data(last).toFloat();


      for (int j=0; j<model->columnCount(); j++)
        {
                for (int i=0; i<(model->rowCount())-1; i++)
                    {
                        //QModelIndex index =  model->index(i,j,QModelIndex());
                        //QModelIndex idx = model->index(model->rowCount(), dataColumn);
                        //QVariant nextData = idx.data().toFloat();
                        // Comparison

                            if (content > maximum)
                            {
                                maximum == content;

                            }


                    }
            model->setData(index, maximum);
      }

//**************************************************************************

    //sets in which columns the green bars should be drawn
    if (index.column() == 1)
      {
          rect.setWidth(rect.width()*(v/maximum));
          painter->drawRect(rect);
      }

    //Coverage
    if (index.column() == numbers[5] )
    {

        rect.setWidth(rect.width()*(0.001*(v/maximum)));
        painter->drawRect(rect);
    }

    //#Peptides
    if (index.column() == numbers[6] )
    {
    /*  painter->setBrush(QBrush(Qt::red));
        rect2.setWidth(rect.width()*(v*0.1));
        painter->drawRect(rect);
        painter->setBrush(QBrush(Qt::yellow));
        rect3.setWidth(rect.width()*(v*0.05));
        painter->drawRect(rect3);

        painter->setBrush(QBrush(Qt::green));
        rect2.setWidth(rect.width()*(0.01*v));

        rect2.united(rect);
        rect2.united(rect3);

        painter->drawRect(rect3);
        
        rect.setWidth(rect.width()*(0.01*v));
        painter->drawRect(rect);

    }

    //#Spectra
    if (index.column() == numbers[7])
    {

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
        painter->drawRect(rect2);

    }

    //MS2Quant
    if (index.column() == numbers[8])
    {
        rect.setWidth(rect.width()*(v*10));
        painter->drawRect(rect);


    }

    //MWQuant
    if (index.column() == numbers[9])
    {
        rect.setWidth(rect.width()*(v*0.001));
        painter->drawRect(rect);
    }
*/

    QString dataalsstring = index.data().toString();

    //da Qt anscheinend alle QStandarditems zu float konvertieren kann, hier nun die Abfrage, ob wir tatsächlich eine Zahl vorliegen haben
    if (dataalsstring.startsWith("0") || dataalsstring.startsWith("1") || dataalsstring.startsWith("2") || dataalsstring.startsWith("3")
            || dataalsstring.startsWith("4") || dataalsstring.startsWith("5") || dataalsstring.startsWith("6") || dataalsstring.startsWith("7")
            || dataalsstring.startsWith("8") || dataalsstring.startsWith("9"))
    {


     //in last holen wir uns den Index der letzten Zeile der aktuellen Spalte
     //QModelIndex last = index.model()->index((index.model()->rowCount())-1, index.column(), QModelIndex());
     //denn hier steht das Maximum

        //Maximum im Header
     float maximum = index.model()->headerData(index.column(), Qt::Horizontal, 12).toFloat();
    //float maximum = index.model()->data(last).toFloat();

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
