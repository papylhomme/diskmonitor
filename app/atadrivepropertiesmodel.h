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


#ifndef ATADRIVEPROPERTIESMODEL_H
#define ATADRIVEPROPERTIESMODEL_H

#include "storageunitpropertiesmodel.h"
#include "atadrive.h"


/*
 * A Qt model to display smart attributes in a table
 */
class AtaDrivePropertiesModel : public StorageUnitPropertiesModel
{
  Q_OBJECT

public:
  AtaDrivePropertiesModel();
  ~AtaDrivePropertiesModel() override;

  AtaDrive* getAtaDrive() const;

  virtual int rowCount(const QModelIndex& index) const override;
  virtual int columnCount(const QModelIndex& index) const override;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

protected:
  virtual void updateInternalState() override;

  QVariant humanizeSmartAttribute(const AtaSmartAttribute& attr) const;

private:
  QStringList headerLabels;
  QList<int> sensitiveAttributes;
  AtaSmartAttributesList attributes;

public slots:
  void configChanged();
};

#endif // ATADRIVEPROPERTIESMODEL_H
