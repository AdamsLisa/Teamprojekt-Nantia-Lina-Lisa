#ifndef BARDELEGATEPEP_H
#define BARDELEGATEPEP_H

#include <QStyledItemDelegate>

class bardelegatepep : public QStyledItemDelegate
{
    Q_OBJECT

public:
    bardelegatepep(QObject *parent = 0);

 // QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
  //void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  //void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif
