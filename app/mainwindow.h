/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/


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

  void updateCurrentUnit(StorageUnit* unit);

public slots:
  void unitSelected(const QModelIndex& index);
  void storageUnitRemoved(StorageUnit* unit);
  void updateHealthStatus(StorageUnit* unit);

  void refreshDetails();
  void showSettings();
  void configChanged();
};

#endif // MAINWINDOW_H
