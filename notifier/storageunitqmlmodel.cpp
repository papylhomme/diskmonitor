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


#include "storageunitqmlmodel.h"

#include "udisks2wrapper.h"




/*
 * Constructor
 */
StorageUnitQmlModel::StorageUnitQmlModel()
{
  UDisks2Wrapper* udisks2 = UDisks2Wrapper::instance();
  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));

  storageUnits = udisks2 -> listStorageUnits();
}



/*
 * Destructor
 */
StorageUnitQmlModel::~StorageUnitQmlModel()
{
}



/*
 * Return a list of available roles for this model
 */
QHash<int, QByteArray> StorageUnitQmlModel::roleNames() const
{
  QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[NameRole] = "name";
  roles[IconRole] = "icon";
  roles[DeviceRole] = "device";
  roles[HealthStatusRole] = "healthStatus";
  roles[PathRole] = "path";
  return roles;
}



/*
 * Get the number of rows in the model
 */
int StorageUnitQmlModel::rowCount(const QModelIndex& /*parent*/) const
{
  return storageUnits.size();
}



/*
 * Get the data for the specified index and role
 */
QVariant StorageUnitQmlModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid())
    return QVariant();

  StorageUnit* unit = storageUnits.at(index.row());

  switch(role) {
    case NameRole: return QVariant(unit -> getShortName()); break;
    case IconRole: return QVariant(getIconForUnit(unit)); break;
    case DeviceRole: return QVariant(unit -> getDevice()); break;
    case HealthStatusRole: return QVariant(unit -> getHealthStatus()); break;
    case PathRole: return QVariant(unit -> getPath()); break;
    default: return QVariant(); break;
  }

  return QVariant();
}



/*
 * Retrieve an icon name for the given StorageUnit
 */
QString StorageUnitQmlModel::getIconForUnit(StorageUnit* unit) const
{
  QString icon;
  if(unit -> isMDRaid())
    icon = "drive-harddisk";
  else if(unit -> isDrive() && ((Drive*) unit) -> isRemovable())
    icon = "drive-removable-media";
  else
    icon = "drive-harddisk";

  return icon;
}



/*
 * Handle StorageUnit added
 */
void StorageUnitQmlModel::storageUnitAdded(StorageUnit* unit)
{
  int idx = storageUnits.size();

  beginInsertRows(QModelIndex(), idx, idx);
  storageUnits.append(unit);
  endInsertRows();
}



/*
 * Handle StorageUnit removed
 */
void StorageUnitQmlModel::storageUnitRemoved(StorageUnit* unit)
{
  int idx = storageUnits.indexOf(unit);

  beginRemoveRows(QModelIndex(), idx, idx);
  storageUnits.removeAt(idx);
  endRemoveRows();
}



/*
 * Refresh the model
 */
void StorageUnitQmlModel::refresh()
{
  beginResetModel();
  foreach(StorageUnit* unit, storageUnits) {
    unit -> update();
  }
  endResetModel();
}

