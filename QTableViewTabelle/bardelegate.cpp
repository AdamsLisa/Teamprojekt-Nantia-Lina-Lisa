#include "BarDelegate.h"
#include <QtWidgets>
#include <QSpinBox>
#include <iostream>

BarDelegate::BarDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

/*
QWidget *BarDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
>>>>>>> master
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
}
*/

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
    if (index.column() == 1 || index.column() == 5 || index.column() == 6 || index.column() == 7
                            || index.column() == 8 || index.column() == 9 || index.column() == 10)
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

/*
void BarDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

void BarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}
*/

void BarDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
