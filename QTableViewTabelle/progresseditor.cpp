#include "progresseditor.h"
#include <QtWidgets>
#include "progressrating.h"

ProgressEditor::ProgressEditor(QWidget *parent)
    : QWidget(parent)
{

}

QSize ProgressEditor::sizeHint() const
{
    return myProgressRating.sizeHint();
}

void ProgressEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    myProgressRating.paint(&painter, rect(), this->palette(),
                       ProgressRating::Editable);
}


int ProgressEditor::progressAtPosition(int x)
{
    int progress = (x / (myProgressRating.sizeHint().width()
                     / myProgressRating.maxProgressCount())) + 1;
    if (progress <= 0 || progress > myProgressRating.maxProgressCount())
        return -1;

    return progress;
}
