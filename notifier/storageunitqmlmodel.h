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


#ifndef STORAGEUNITQMLMODEL_H
#define STORAGEUNITQMLMODEL_H

#include <QAbstractListModel>

#include "storageunit.h"



/*
 * Model class for the plasma applet
 *
 * Provide a Qt Model to display the Storage units, and
 * global health status
 */
class StorageUnitQmlModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum ModelRoles {
    NameRole = Qt::UserRole + 1,
    DeviceRole,
    HealthStatusRole,
    PathRole,
    IconRole
  };

  StorageUnitQmlModel();
  ~StorageUnitQmlModel();

  virtual QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
  QList<StorageUnit*> storageUnits;

  QString getIconForUnit(StorageUnit* unit) const;

private slots:
  void storageUnitAdded(StorageUnit* unit);
  void storageUnitRemoved(StorageUnit* unit);

public slots:
  void refresh();
};

#endif // STORAGEUNITQMLMODEL_H
