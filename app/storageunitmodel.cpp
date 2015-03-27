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


#include "storageunitmodel.h"

#include "udisks2wrapper.h"

#include <QPixmap>
#include <KIconLoader>

#include <QDebug>


/*
 * Constructor
 */
StorageUnitModel::StorageUnitModel()
{
  init();

  UDisks2Wrapper* udisks2 = UDisks2Wrapper::instance();
  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));
}



/*
 * Destructor
 */
StorageUnitModel::~StorageUnitModel()
{

}



/*
 * Init the internal state of the model
 */
void StorageUnitModel::init() {
  UDisks2Wrapper* udisks2 = UDisks2Wrapper::instance();

  inhibitUpdate = true;
  beginResetModel();

  storageUnits.clear();
  QList<StorageUnit*> units = udisks2 -> listStorageUnits();

  foreach(StorageUnit* u, units) {
    u -> update();
    storageUnits.append(u);
    connect(u, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdated(StorageUnit*)));
  }

  endResetModel();
  inhibitUpdate = false;
}



/*
 * Refresh the internal state
 */
void StorageUnitModel::refresh() {
  qDebug() << "DiskMonitor::StorageUnitModel - refreshing...";

  inhibitUpdate = true;
  beginResetModel();
  foreach(StorageUnit* u, storageUnits) {
    u -> update();
  }
  endResetModel();
  inhibitUpdate = false;
}



/*
 * Get the number of rows contained in the model's data.
 */
int StorageUnitModel::rowCount(const QModelIndex&) const
{
  return storageUnits.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant StorageUnitModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid())
    return QVariant();

  StorageUnit* u = storageUnits[index.row()];

  if(role == Qt::DisplayRole) {
    return QVariant(u -> getName());

  } else if(role == Qt::ToolTipRole) {
    return QVariant(u -> getName());

  } else if(role == Qt::DecorationRole) {

    //define health status overlay
    QStringList overlays;
    if(!u -> isFailingStatusKnown())
      overlays.append(iconProvider.unknown());
    else if(u -> isFailing())
      overlays.append(iconProvider.failing());
    else
      overlays.append(iconProvider.healthy());

    //define icon
    QString icon;
    if(u -> isMDRaid())
      icon = "drive-harddisk";
    else if(u -> isDrive() && ((Drive*) u) -> isRemovable())
      icon = "drive-removable-media";
    else
      icon = "drive-harddisk";

    return QVariant(KIconLoader::global() -> loadIcon(icon, KIconLoader::Desktop, 64, KIconLoader::DefaultState, overlays));

  } else if(role == Qt::UserRole) {
    QVariant v;
    v.setValue(u);
    return v;
  }


  return QVariant();
}



/*
 * Handle new StorageUnit
 */
void StorageUnitModel::storageUnitAdded(StorageUnit* unit)
{
  int idx = storageUnits.size();

  beginInsertRows(QModelIndex(), idx, idx);
  storageUnits.append(unit);
  endInsertRows();

  connect(unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdated(StorageUnit*)));
}



/*
 * Handle removal of StorageUnit
 */
void StorageUnitModel::storageUnitRemoved(StorageUnit* unit)
{
  int idx = storageUnits.indexOf(unit);

  if(idx >= 0) {
    disconnect(unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdated(StorageUnit*)));

    beginRemoveRows(QModelIndex(), idx, idx);
    storageUnits.removeAt(idx);
    endRemoveRows();
  }
}



/*
 * Handle StorageUnit updated signal and update the display accordingly
 */
void StorageUnitModel::storageUnitUpdated(StorageUnit* unit)
{
  if(inhibitUpdate)
    return;

  /*
   * TODO FixThis
   *
   * Somehow emitting the dataChanged signal break the grid layout (items
   * updated do not wrap anymore until the layout is resetted)
   * So we go for the hammer and reset the model...
   */
  //beginResetModel();
  //endResetModel();


  QVector<int> roles;
  roles << Qt::DisplayRole << Qt::DecorationRole << Qt::ToolTipRole;
  int index = storageUnits.indexOf(unit);

  if(index >= 0) {
    QModelIndex idx = createIndex(index, 0);
    emit dataChanged(idx, idx, roles);
  }
}
