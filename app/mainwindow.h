#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

#include "dbus_metatypes.h"
#include "storageunit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public KMainWindow
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
  void showSettings();
};

#endif // MAINWINDOW_H
