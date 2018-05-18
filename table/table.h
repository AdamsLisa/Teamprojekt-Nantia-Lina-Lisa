#ifndef TABLE_H
#define TABLE_H
#include <QWidget>
#include <QStandardItemModel>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>

namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0);
    ~Table();

private:
    Ui::Table *ui;
    // QStandardItemModel provides a classic
    // item-based approach to working with the model.
    QStandardItemModel *model;
};

#endif // TABLE_H
