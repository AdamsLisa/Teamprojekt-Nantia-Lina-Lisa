#ifndef PROTEINTABELLE_H
#define PROTEINTABELLE_H
#include <QTableView>


class Proteintabelle : public QTableView
{
    Q_OBJECT
public:
    Proteintabelle(QWidget *parent = 0);

public slots:
    void handleButton();
};

#endif // PROTEINTABELLE_H

