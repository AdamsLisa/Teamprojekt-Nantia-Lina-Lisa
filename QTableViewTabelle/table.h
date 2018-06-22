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


//signals:
//    selectionChanged(const QItemSelection &, const QItemSelection &);

signals:
    selectionChanged(const QItemSelection &, const QItemSelection &);
    clicked();



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
