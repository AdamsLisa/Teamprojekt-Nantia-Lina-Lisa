#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
#include <QItemSelectionModel>


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

signals:
    selectionChanged(const QItemSelection &, const QItemSelection &);


private:
    Ui::table *ui;
    QStandardItemModel *model;
    QStandardItemModel *modelpep;
    QStandardItem *item;
    QStandardItem *itempep;
    QItemSelectionModel *select;



};

#endif // TABLE_H
