#include "BarDelegate.h"
#include <QtWidgets>
#include <QSpinBox>
#include <iostream>

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

    //sets in which columns the green bars should be drawn
    //column #Peptides
    if (index.column() == 6)
    {
    float v=index.data().toFloat();
    QRect rect = option.rect;
    rect.setWidth(rect.width()*(0.01*v));
    painter->drawRect(rect);
    }

    //sets in which columns the green bars should be drawn
    //Column Coverage
    if (index.column() == 5)
    {
    float v=index.data().toFloat();
    QRect rect = option.rect;
    rect.setWidth(rect.width()*(0.001*v));
    painter->drawRect(rect);
    }

    //sets in which columns the green bars should be drawn
    //Column #Spectra
    if (index.column() == 7)
    {
    float v=index.data().toFloat();
    QRect rect = option.rect;
    rect.setWidth(rect.width()*(0.005*v));
    painter->drawRect(rect);
    }

    //sets in which columns the green bars should be drawn
    //Column MS2Quant
    if (index.column() == 8)
    {
    float v=index.data().toFloat();
    QRect rect = option.rect;
    rect.setWidth(rect.width()*(v*10));
    painter->drawRect(rect);
    }

    //sets in which columns the green bars should be drawn
    //Column MWQuant
    if (index.column() == 9)
    {
    float v=index.data().toFloat();
    QRect rect = option.rect;
    rect.setWidth(rect.width()*(v*0.001));
    painter->drawRect(rect);
    }

    if (index.column() == 1 || index.column() == 10)
    {

    QRect rect = option.rect;

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
