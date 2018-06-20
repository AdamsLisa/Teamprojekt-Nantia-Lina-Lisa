#include "BarDelegate.h"
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

    //sets in which columns the green bars should be drawn
    if (index.column() == numbers[1] || index.column() == numbers[10])
    {

        painter->drawRect(rect);
    }

    //Coverage
    if (index.column() == numbers[5] )
    {
        rect.setWidth(rect.width()*(0.001*v));
        painter->drawRect(rect);
    }

    //#Peptides
    if (index.column() == numbers[6] )
    {
    /*    painter->setBrush(QBrush(Qt::red));
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
        */
        rect.setWidth(rect.width()*(0.01*v));
        painter->drawRect(rect);

    }

    //#Spectra
    if (index.column() == numbers[7])
    {

        painter->setBrush(QBrush(Qt::red));
        rect2.setWidth(rect.width()*(v*0.1));
        painter->drawRect(rect);
        painter->setBrush(QBrush(Qt::yellow));
        rect3.setWidth(rect.width()*(v*0.01));
        painter->drawRect(rect3);

        painter->setBrush(QBrush(Qt::green));
        rect2.setWidth(rect.width()*(0.005*v));
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
