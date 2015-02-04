#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbus_metatypes.h"
#include "storageunit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void updateHealthStatus(StorageUnit*);


private:
    Ui::MainWindow* ui;

public slots:
  void unitSelected(const QModelIndex& index);
  void refreshDetails();
};

#endif // MAINWINDOW_H
