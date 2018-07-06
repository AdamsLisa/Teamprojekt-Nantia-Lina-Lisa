#ifndef PEPTIDTABELLE_H
#define PEPTIDTABELLE_H
#include <QTableView>


class Peptidtabelle : public QTableView
{
    Q_OBJECT
public:
    Peptidtabelle(QWidget *parent = 0);

public slots:
    void handleButton();
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // PEPTIDTABELLE_H
