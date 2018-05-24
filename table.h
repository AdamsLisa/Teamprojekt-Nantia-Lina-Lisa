#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
//#include> <QItemDelegate>

namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    ~table();

private:
    Ui::table *ui;
    QStandardItemModel *model;
};

#endif // TABLE_H
