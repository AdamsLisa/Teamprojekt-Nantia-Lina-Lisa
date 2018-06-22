#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QItemSelectionModel>
#include <QPushButton>


namespace Ui {
class table;
}

class table : public QMainWindow
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = 0);
    ~table();

public slots:
    void slotSelectionChange(const QItemSelection &, const QItemSelection &);
    void handleButton();

<<<<<<< HEAD
//signals:
//    selectionChanged(const QItemSelection &, const QItemSelection &);
=======
signals:
    selectionChanged(const QItemSelection &, const QItemSelection &);
    clicked();

>>>>>>> 7f66055644034ddc79719dfaa001cbfdbd4ae909

private:
    Ui::table *ui;
    QStandardItemModel *model;
    QStandardItemModel *modelpep;
    QStandardItem *item;
    QStandardItem *itempep;
    QItemSelectionModel *select;
    int TableRowPep;
    int TableColumnPep;



};

#endif // TABLE_H
