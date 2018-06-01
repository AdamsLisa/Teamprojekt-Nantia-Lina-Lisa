#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QString>

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
    QStandardItem *item;
    QString PL;

};

#endif // TABLE_H
