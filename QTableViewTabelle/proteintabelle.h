#ifndef PROTEINTABELLE_H
#define PROTEINTABELLE_H
#include <QWidget>
#include <QTableView>



class Proteintabelle : public QTableView
{

    Q_OBJECT
public:
    Proteintabelle(QObject *parent = 0);
};

#endif // PROTEINTABELLE_H
