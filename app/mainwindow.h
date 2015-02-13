#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

#include "storageunitmodel.h"
#include "iconprovider.h"

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
    StorageUnitModel* storageUnitModel;

    IconProvider iconProvider;

public slots:
  void unitSelected(const QModelIndex& index);
  void refreshDetails();
  void showSettings();
  void configChanged();
};

#endif // MAINWINDOW_H
