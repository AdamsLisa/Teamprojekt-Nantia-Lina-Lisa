#include "Bardelegate.h"
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
<<<<<<< HEAD
void BarDelegate::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
=======
*/

/*void BarDelegate::paintEvent(QPaintEvent *event) const
{
    QPainter painter;
>>>>>>> master
    QRect r1 = rect().adjusted(10,10,-10,-10);
    painter.setPen(QColor("#33B5E5"));
    painter.drawRect(r1);
    QRect r2(QPoint(0,0),QSize(40,40));
    if(m_lastPos.isNull()) {
        r2.moveCenter(r1.center());
    } else {
        r2.moveCenter(m_lastPos);
    }
    painter.fillRect(r2, QColor("#FFBB33"));
}
*/
const int PaintingScaleFactor = 20;
void BarDelegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(QBrush(Qt::green));

    QRect rect = option.rect;
    painter->drawRect(rect);
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
