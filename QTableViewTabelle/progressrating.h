#ifndef PROGRESSRATING_H
#define PROGRESSRATING_H

#include <QMetaType>
#include <QPointF>
#include <QVector>

class ProgressRating
{
public:
    enum EditMode { Editable, ReadOnly };

    explicit ProgressRating(int progressCount = 1, int maxProgressCount = 5);

    void paint(QPainter *painter, const QRect &rect,const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;
    int progressCount() const { return myProgressCount; }
    int maxProgressCount() const { return myMaxProgressCount; }
    void setProgressCount(int progressCount) { myProgressCount = progressCount; }
    void setMaxProgressCount(int maxProgressCount) { myMaxProgressCount = maxProgressCount; }

private:
    QPolygonF progressPolygon;
    QPolygonF diamondPolygon;
    int myProgressCount;
    int myMaxProgressCount;
};

Q_DECLARE_METATYPE(ProgressRating)

#endif
