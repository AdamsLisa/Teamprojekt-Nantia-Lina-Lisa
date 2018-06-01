#include "progressdelegate.h"

#include "progresseditor.h"
#include "progressrating.h"

#include <QtWidgets>
#include <cmath>


void BarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (index.data().canConvert<ProgressRating>()) {
        ProgressRating progressRating = qvariant_cast<ProgressRating>(index.data());

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

       progressRating.paint(painter, option.rect, option.palette,
                         ProgressRating::ReadOnly);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize BarDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data().canConvert<ProgressRating>()) {
        ProgressRating progressRating = qvariant_cast<ProgressRating>(index.data());
        return progressRating.sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}


QWidget *BarDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const

    {
        if (index.data().canConvert<ProgressRating>()) {
            ProgressEditor *editor = new ProgressEditor(parent);
            return editor;
        } else {
            return QStyledItemDelegate::createEditor(parent, option, index);
        }
    }


void BarDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    if (index.data().canConvert<ProgressRating>()) {
        ProgressRating progressRating = qvariant_cast<ProgressRating>(index.data());
        ProgressEditor *progressEditor = qobject_cast<ProgressEditor *>(editor);
        progressEditor->setProgressRating(progressRating);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void BarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    if (index.data().canConvert<ProgressRating>()) {
        ProgressEditor *progressEditor = qobject_cast<ProgressEditor *>(editor);
        model->setData(index, QVariant::fromValue(progressEditor->progressRating()));
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}
