#ifndef BARDELEGATEPEP_H
#define BARDELEGATEPEP_H

#include <QStyledItemDelegate>

class bardelegatepep : public QStyledItemDelegate
{
    Q_OBJECT

public:
    bardelegatepep(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif
