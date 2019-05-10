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


#include "storageunitpanel.h"

#include "udisks2wrapper.h"

/*
 * Constructor
 */
StorageUnitPanel::StorageUnitPanel(StorageUnitPropertiesModel* model, QWidget* parent) : QWidget(parent)
{
  this -> model = model;

  connect(UDisks2Wrapper::instance(), SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));

  this -> autorefreshTimer = new QTimer();
  connect(autorefreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
}



/*
 * Destructor
 */
StorageUnitPanel::~StorageUnitPanel()
{
  delete model;
}



/*
 * Set the StorageUnit. Call updateUI and handle auto-refresh if needed
 */
void StorageUnitPanel::setStorageUnit(StorageUnit* unit)
{
  this -> model -> setStorageUnit(unit);
  updateUI();
  updateAutoRefreshTimer();
}



/*
 * Refresh the content of the panel (by refreshing the model's StorageUnit)
 */
void StorageUnitPanel::refresh()
{
  this -> model -> refreshAll();
  updateUI();
  updateAutoRefreshTimer();
}



/*
 * Handle hot unplug of current unit
 */
void StorageUnitPanel::storageUnitRemoved(StorageUnit* unit)
{
  if(this -> model -> getStorageUnit() == unit)
    setStorageUnit(nullptr);
}



/*
 * Auto-refresh enabling/disabling routine
 */
void StorageUnitPanel::updateAutoRefreshTimer()
{
  bool running = isOperationRunning();

  if(running && !autorefreshTimer -> isActive())
    autorefreshTimer -> start(1000);
  else if(!running && autorefreshTimer -> isActive())
    autorefreshTimer -> stop();
}


