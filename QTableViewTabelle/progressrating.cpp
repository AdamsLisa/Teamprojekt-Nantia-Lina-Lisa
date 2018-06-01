#include <QtWidgets>
#include <cmath>
#include "progressrating.h"

const int PaintingScaleFactor = 20;

ProgressRating::ProgressRating(int progressCount, int maxProgressCount)
{
    myProgressCount = progressCount;
    myMaxProgressCount = maxProgressCount;

    progressPolygon << QPointF(1.0, 0.5);

    for (int i = 1; i < 5; ++i)
        progressPolygon << QPointF(0.5 + 0.5 * std::cos(0.8 * i * 3.14),
                               0.5 + 0.5 * std::sin(0.8 * i * 3.14));

        diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
                   << QPointF(0.6, 0.5) << QPointF(0.5, 0.6)
                   << QPointF(0.4, 0.5);
}

QSize ProgressRating::sizeHint() const
{
    return PaintingScaleFactor * QSize(myMaxProgressCount, 1);
}

void ProgressRating::paint(QPainter *painter, const QRect &rect, const QPalette &palette, EditMode mode) const
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

    for (int i = 0; i < myMaxProgressCount; ++i) {
        if (i < myProgressCount) {
            painter->drawPolygon(progressPolygon, Qt::WindingFill);
        } else if (mode == Editable) {
            painter->drawPolygon(diamondPolygon, Qt::WindingFill);
        }
        painter->translate(1.0, 0.0);
    }

    painter->restore();
}
