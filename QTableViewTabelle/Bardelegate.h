#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>

class BarDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    BarDelegate(QObject *parent = 0);
    enum EditMode { Editable, ReadOnly };

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                      const QModelIndex &index) const override;
    void paint(QPainter *painter, const QRect &rect,
                   const QPalette &palette, EditMode mode) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;
protected slots:
 //void paintEvent(QPaintEvent *event) const;
private:
    QPolygonF starPolygon;
    QPolygonF diamondPolygon;
    int myStarCount;
    int myMaxStarCount;
};

#endif
