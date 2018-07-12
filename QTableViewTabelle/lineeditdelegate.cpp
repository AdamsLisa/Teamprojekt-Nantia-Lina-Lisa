#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QWidget>
#include <QSortFilterProxyModel>
#include <QCompleter>

lineEditdelegate::lineEditdelegate(QObject *parent )    //, QStyleOptionViewItem const& option, QModelIndex const& index)
    : QStyledItemDelegate(parent)
{

}


QWidget* lineEditdelegate::createEditor(QWidget* parent, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    QLineEdit *editor = new QLineEdit(parent);

//    QCompleter *completer = new QCompleter();
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    completer->setCompletionColumn(1);
//    completer->setFilterMode(Qt::MatchContains);
//    //completer->setMaxVisibleItems()
//    completer->setModelSorting(QCompleter::UnsortedModel);
//    editor->setCompleter(completer);

    editor->setPlaceholderText("suche");


   //connect(editor, SIGNAL(textChanged(QString)), this, SLOT(textFilterChanged(QString &newValue)));


    return editor;
}


void lineEditdelegate::setEditorData(QWidget* editor, QModelIndex const& index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QString currentText = index.model()->data(index, Qt::EditRole).toString();
    lineEdit->setText(currentText);

}



void lineEditdelegate::setModelData(QWidget* editor, QAbstractItemModel* model, QModelIndex const& index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text(), Qt::EditRole);




}



void lineEditdelegate::updateEditorGeometry(QWidget* editor, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    editor->setGeometry(option.rect);
}




