#ifndef TABLEPEPTIDES_H
#define TABLEPEPTIDES_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QWidget>
namespace Ui {
class tablepeptides;
}

class tablepeptides : public QMainWindow
{
    Q_OBJECT

public:
    explicit tablepeptides(QWidget *parent = 0);
    ~tablepeptides();

private:
    Ui::tablepeptides *ui;
    QStandardItemModel *model;
    QStandardItem *item;
};

#endif // TABLEPEPTIDES_H
