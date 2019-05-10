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


#include "mdraidpropertiesmodel.h"

#include <KLocalizedString>

#include <QFont>

#include "humanize.h"


/*
 * Constructor
 */
MDRaidPropertiesModel::MDRaidPropertiesModel()
{
  headerLabels << i18nc("RAID property UUID", "UUID")
               << i18nc("RAID level", "Level")
               << i18nc("RAID device's count", "Devices")
               << i18nc("RAID size", "Size")
               << i18nc("RAID current action", "Action")
               << i18nc("RAID current action remaining time", "Remaining time")
               << i18nc("RAID current action % completed", "Completed");
}



/*
 * Destructor
 */
MDRaidPropertiesModel::~MDRaidPropertiesModel()
{

}



/*
 * Retrieve the MDRaid associated to the model. Can be NULL
 */
MDRaid* MDRaidPropertiesModel::getMDRaid() const
{
  return static_cast<MDRaid*>(this -> unit);
}



/*
 * Get the number of rows contained in the model's data. Always 1
 */
int MDRaidPropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return 1;
}


/*
 * Get the number of column of the model
 */
int MDRaidPropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant MDRaidPropertiesModel::data(const QModelIndex& index, int role) const
{
  MDRaid* mdraid = getMDRaid();

  if(!index.isValid() || index.row() != 0 || mdraid == nullptr)
    return QVariant();


  if(role == Qt::DisplayRole) {
    switch(index.column()) {
      case 0: return QVariant(mdraid -> getUUID());
      case 1: return QVariant(mdraid -> getLevel());
      case 2: return QVariant(mdraid -> getNumDevices());
      case 3: return QVariant(Humanize::size(mdraid -> getSize()));
      case 4: return QVariant(mdraid -> getSyncAction());
      case 5: return QVariant(Humanize::duration(mdraid -> getSyncRemainingTime(), "us", "s"));
      case 6: return QVariant(Humanize::percentage(mdraid -> getSyncCompleted()));
      default: return QVariant();
    }

  } else if(role == Qt::ToolTipRole) {
    switch(index.column()) {
      case 3: return QVariant(i18n("Raw value: %1", QString::number(mdraid -> getSize())));
      case 5: return QVariant(i18n("Raw value: %1", QString::number(mdraid -> getSyncRemainingTime())));
      case 6: return QVariant(i18n("Raw value: %1", QString::number(mdraid -> getSyncCompleted())));
      default: return QVariant();
    }
  }

  return QVariant();
}



/*
 * Handle the headers of the model
 */
QVariant MDRaidPropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation != Qt::Horizontal)
    return QVariant();

  if(role == Qt::DisplayRole) {
      return QVariant(headerLabels.at(section));

  } else if(role == Qt::FontRole) {
    QFont font;
    font.setBold(true);
    return QVariant(font);
  }

  return QVariant();
}


