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


    //sets in which columns the green bars should be drawn
    if (index.column() == 3)
    {
        float v=(index.data().toFloat())/40;
        QRect rect = option.rect;
        rect.setLeft(rect.left() + v);
        float rectanglesize = 10;
        rect.setWidth(rectanglesize);
     /*   if(rect.width()>2000)
      * {
            painter->setBrush(QBrush(Qt::yellow));

        }
        */
        painter->drawRect(rect);
    }

    if (index.column() == 4 )
    {

    if (v == 1.0) rect.setWidth(rect.width()*0.5);

    painter->drawRect(rect);

    }


    if (index.column() == 1 || index.column() == 5)
    {

    painter->drawRect(rect);

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


