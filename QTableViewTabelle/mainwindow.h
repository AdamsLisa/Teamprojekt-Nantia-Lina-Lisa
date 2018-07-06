#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QObject>


class MainWindow : public QObject
{
    Q_OBJECT

public:
  explicit MainWindow(QObject *parent = 0);

public slots:
    void slotSelectionChange(const QItemSelection &, const QItemSelection &);
};

#endif // MAINWINDOW_H
