#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>

class BarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    BarDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif
