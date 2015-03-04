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


#ifndef STORAGEUNITPANEL_H
#define STORAGEUNITPANEL_H

#include <QWidget>
#include <QTimer>

#include "storageunitpropertiesmodel.h"



/*
 * Base class to implement a panel displaying information for a StorageUnit
 *
 * Handle refreshing the internal data, and auto refresh during a running operation
 */
class StorageUnitPanel : public QWidget
{
    Q_OBJECT
public:
  explicit StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget *parent = 0);
  ~StorageUnitPanel();

  void setStorageUnit(StorageUnit* unit);

protected:
  StorageUnitPropertiesModel* model = NULL;

  virtual bool isOperationRunning() { return false; }
  virtual void updateUI() { }

private:
  QTimer* autorefreshTimer;

  void updateAutoRefreshTimer();

public slots:
  void refresh();

};

#endif // STORAGEUNITPANEL_H
