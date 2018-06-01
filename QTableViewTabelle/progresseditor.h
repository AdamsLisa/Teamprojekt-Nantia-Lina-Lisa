#ifndef PROGRESSEDITOR_H
#define PROGRESSEDITOR_H
#include <QWidget>
#include "progressrating.h"

class ProgressEditor : public QWidget
{
    Q_OBJECT

public:
    ProgressEditor(QWidget *parent = 0);

    QSize sizeHint() const override;
    void setProgressRating(const ProgressRating &progressRating) {
        myProgressRating = progressRating;
    }
    ProgressRating progressRating() { return myProgressRating; }

signals:
    void editingFinished();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int progressAtPosition(int x);

    ProgressRating myProgressRating;
};

#endif
