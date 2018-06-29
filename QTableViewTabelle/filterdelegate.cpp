#include "filterdelegate.h"
#include <QLineEdit>
#include <QWidget>
#include "table.h"
#include <QSortFilterProxyModel>

filterdelegate::filterdelegate(QObject *parent )    //, QStyleOptionViewItem const& option, QModelIndex const& index)
    : QStyledItemDelegate(parent)
{
//       proxy = new QSortFilterProxyModel;
//       proxy->setSourceModel(model);
}


QWidget* filterdelegate::createEditor(QWidget* parent, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    QLineEdit *editor = new QLineEdit(parent);

//    QCompleter *completer = new QCompleter(option);

//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    completer->setCompletionColumn(3);
//    completer->setFilterMode(Qt::MatchContains);
//    //completer->setMaxVisibleItems()
//    completer->setModelSorting(QCompleter::UnsortedModel);

//    editor->setCompleter(completer);

    editor->setPlaceholderText("suche");


    return editor;
}


void filterdelegate::setEditorData(QWidget* editor, QModelIndex const& index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QString currentText = index.model()->data(index, Qt::EditRole).toString();
    lineEdit->setText(currentText);
}



void filterdelegate::setModelData(QWidget* editor, QAbstractItemModel* model, QModelIndex const& index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text(), Qt::EditRole);

}



void filterdelegate::updateEditorGeometry(QWidget* editor, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    editor->setGeometry(option.rect);
}




