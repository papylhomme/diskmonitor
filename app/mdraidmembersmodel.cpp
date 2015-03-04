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


#include "mdraidmembersmodel.h"

#include "diskmonitor_settings.h"

#include <KLocalizedString>

#include <QFont>
#include <QColor>
#include <QBrush>


/*
 * Constructor
 */
MDRaidMembersModel::MDRaidMembersModel()
{
  headerLabels << i18nc("RAID member device", "Block device")
               << i18nc("RAID member slot", "Slot")
               << i18nc("RAID member state", "State")
               << i18nc("RAID member read errors count", "Read errors");
}



/*
 * Destructor
 */
MDRaidMembersModel::~MDRaidMembersModel()
{
}



/*
 * Retrieve the MDRaid associated to the model. Can be NULL
 */
MDRaid* MDRaidMembersModel::getMDRaid() const
{
  return (MDRaid*) this -> unit;
}



/*
 * Handler when StorageUnitPropertiesModel refresh the underlying unit
 */
void MDRaidMembersModel::updateInternalState()
{
  MDRaid* mdraid = getMDRaid();

  if(mdraid != NULL)
    members = mdraid -> getMembers();
  else
    members.clear();
}



/*
 * Get the number of rows contained in the model's data. Always 1
 */
int MDRaidMembersModel::rowCount(const QModelIndex& /*index*/) const
{
  return members.size();
}


/*
 * Get the number of column of the model
 */
int MDRaidMembersModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant MDRaidMembersModel::data(const QModelIndex& index, int role) const
{
  MDRaid* mdraid = getMDRaid();

  if(!index.isValid() || mdraid == NULL)
    return QVariant();

  MDRaidMember member = members.at(index.row());

  // Handle background colors
  if(role == Qt::BackgroundRole) {

    //set the row background to 'error' if device is faulty
    if(member.state.indexOf("faulty") >= 0) {
      QBrush brush(DiskMonitorSettings::errorColor());
      return QVariant(brush);

    //set the row background to 'warning' if read errors is positive
    } else if(member.numReadErrors > 0) {
      QBrush brush(DiskMonitorSettings::warningColor());
      return QVariant(brush);

    } else {
      return QVariant();
    }

  } else if(role == Qt::DisplayRole) {
    switch(index.column()) {
      case 0: return QVariant(member.block.path()); break;
      case 1: return QVariant(member.slot); break;
      case 2: return QVariant(member.state.join(", ")); break;
      case 3: return QVariant(member.numReadErrors); break;
      default: return QVariant(); break;
    }

  }

  return QVariant();
}



/*
 * Handle the headers of the model
 */
QVariant MDRaidMembersModel::headerData(int section, Qt::Orientation orientation, int role) const
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


