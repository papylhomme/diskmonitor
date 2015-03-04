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


#ifndef STORAGEUNITMODEL_H
#define STORAGEUNITMODEL_H

#include <QAbstractListModel>

#include "drive.h"

#include "iconprovider.h"

class StorageUnitModel : public QAbstractListModel
{
  Q_OBJECT

public:
    StorageUnitModel();
    ~StorageUnitModel();

    virtual int rowCount(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void refresh();

private:
    bool inhibitUpdate = false;
    Settings::IconProvider iconProvider;
    QList<StorageUnit*> storageUnits;

    void init();

private slots:
    void storageUnitAdded(StorageUnit* unit);
    void storageUnitRemoved(StorageUnit* unit);
    void storageUnitUpdated(StorageUnit* unit);
};

#endif // STORAGEUNITMODEL_H
