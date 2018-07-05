#ifndef PEPTIDTABELLE_H
#define PEPTIDTABELLE_H
#include <QTableView>


class Peptidtabelle : public QTableView
{
    Q_OBJECT
public:
    Peptidtabelle(QWidget *parent = 0);
public slots:
    void slotSelectionChange(const QItemSelection &, const QItemSelection &);
};

#endif // PEPTIDTABELLE_H
