#include "Bardelegate.h"
#include <QtWidgets>
#include <QSpinBox>

BarDelegate::BarDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    starPolygon << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
    {
      starPolygon << QPointF(0.5 + 0.5 * std::cos(0.8 * i * 3.14), 0.5 + 0.5 * std::sin(0.8 * i * 3.14));

      diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4) << QPointF(0.6, 0.5) << QPointF(0.5, 0.6) << QPointF(0.4, 0.5);
    }
}
/*
QWidget *BarDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
}
*/

/*void BarDelegate::paintEvent(QPaintEvent *event) const
{
    QPainter painter;
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
void BarDelegate::paint(QPainter *painter, const QRect &rect,
                       const QPalette &palette, EditMode mode) const
{

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if (mode == Editable) {
        painter->setBrush(palette.highlight());
    } else {
        painter->setBrush(palette.foreground());
    }

    int yOffset = (rect.height() - PaintingScaleFactor) / 2;
    painter->translate(rect.x(), rect.y() + yOffset);
    painter->scale(PaintingScaleFactor, PaintingScaleFactor);

    for (int i = 0; i < myMaxStarCount; ++i) {
        if (i < myStarCount) {
            painter->drawPolygon(starPolygon, Qt::WindingFill);
        } else if (mode == Editable) {
            painter->drawPolygon(diamondPolygon, Qt::WindingFill);
        }
        painter->translate(1.0, 0.0);
    }

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
