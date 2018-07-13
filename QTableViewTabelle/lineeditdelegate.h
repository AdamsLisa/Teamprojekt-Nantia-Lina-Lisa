#ifndef FILTERDELEGATE_H
#define FILTERDELEGATE_H

#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>



class lineEditdelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    QWidget* createEditor(QWidget* parent, QStyleOptionViewItem const& option, QModelIndex const& index) const;
    void setEditorData(QWidget* editor, QModelIndex const& index) const;
    void setModelData(QWidget*editor, QAbstractItemModel* model, QModelIndex const& index) const;
    void updateEditorGeometry(QWidget* editor, QStyleOptionViewItem const& option, QModelIndex const& index ) const;

    lineEditdelegate(QObject* parent=0);
    QLineEdit *editor;
    QLineEdit *lineEd;
    lineEditdelegate* lineEdit;


//        ModelWithoutDuplicatesProxy *model_pr;
//        int col_proxy;//Only column from the recived
//                        //model that remains

public slots:
      //void textFilterChanged(QString);

signals:
       textChanged(const QString &newValue);

    };


#endif // FILTERDELEGATE_H
