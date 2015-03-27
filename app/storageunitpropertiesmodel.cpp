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


#include "storageunitpropertiesmodel.h"


#include "udisks2wrapper.h"


/*
 * Constructor
 */
StorageUnitPropertiesModel::StorageUnitPropertiesModel()
{

}



/*
 * Destructor
 */
StorageUnitPropertiesModel::~StorageUnitPropertiesModel()
{

}



/*
 * Update the model's storage unit, refreshing the model's internal data
 */
void StorageUnitPropertiesModel::setStorageUnit(StorageUnit* unit)
{
  beginResetModel();

  if(this -> unit != NULL)
    disconnect(this -> unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdate(StorageUnit*)));

  this -> unit = unit;

  if(this -> unit != NULL)
    connect(this -> unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdate(StorageUnit*)));


  updateInternalState();
  endResetModel();
}



/*
 * Retrieve the associated StorageUnit. Can be NULL
 */
StorageUnit* StorageUnitPropertiesModel::getStorageUnit()
{
  return this -> unit;
}



/*
 * Handle storage unit updated
 */
void StorageUnitPropertiesModel::storageUnitUpdate(StorageUnit* /*unit*/)
{
  beginResetModel();
  updateInternalState();
  endResetModel();
}



/*
 * Refresh the model's internal data
 */
void StorageUnitPropertiesModel::refreshAll()
{
  if(unit != NULL)
    unit -> update();
}

