#ifndef TABLEPEPT_H
#define TABLEPEPT_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>


namespace Ui {
class tablepept;
}

class tablepept : public QMainWindow
{
    Q_OBJECT

public:
    explicit tablepept(QWidget *parent = 0);
    ~tablepept();

private:
    Ui::tablepept *ui;
    QStandardItemModel *model;
    QStandardItem *item;


};

#endif // TABLEPEPT_H


