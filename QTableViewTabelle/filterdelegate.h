#ifndef FILTERDELEGATE_H
#define FILTERDELEGATE_H

#include <QStyledItemDelegate>


//namespace Ui {
//class table;
//}

class filterdelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
   filterdelegate(QObject* parent=0);
    QLineEdit *editor;
    //table *model;
    filterdelegate* filter;


        QWidget* createEditor(QWidget* parent, QStyleOptionViewItem const& option, QModelIndex const& index) const;
       void setEditorData(QWidget* editor, QModelIndex const& index) const;
        void setModelData(QWidget*editor, QAbstractItemModel* model, QModelIndex const& index) const;
        void updateEditorGeometry(QWidget* editor, QStyleOptionViewItem const& option, QModelIndex const& index ) const;

//        ModelWithoutDuplicatesProxy *model_pr;
//        int col_proxy;//Only column from the recived
//                        //model that remains
signals:
        textChanged();

    };


#endif // FILTERDELEGATE_H
