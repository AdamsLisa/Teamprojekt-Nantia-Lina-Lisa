#ifndef BUTTON_H
#define BUTTON_H
#include <QTableView>

class Button
{
public:
    Button();
public slots:
    //void slotSelectionChange(const QItemSelection &, const QItemSelection &);
    void handleButton(const QTableView);
};

#endif // BUTTON_H
