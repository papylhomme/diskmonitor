#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KMainWindow>

#include "storageunitmodel.h"
#include "iconprovider.h"

namespace Ui {
class MainWindow;
}


/*
 * Main application window
 */
class MainWindow : public KMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void setSelectedUnit(const QString& path);


private:
  Ui::MainWindow* ui;

  StorageUnit* currentUnit = NULL;
  StorageUnitModel* storageUnitModel;

  Settings::IconProvider iconProvider;

public slots:
  void unitSelected(const QModelIndex& index);
  void updateHealthStatus(StorageUnit*);

  void refreshDetails();
  void showSettings();
  void configChanged();
};

#endif // MAINWINDOW_H
