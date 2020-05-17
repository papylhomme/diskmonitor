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


#include "drivepropertiesmodel.h"

#include "diskmonitor_settings.h"

#include <KLocalizedString>

#include <QFont>
#include <QBrush>
#include <QColor>
#include <QPalette>

#include "humanize.h"


/*
 * Constructor
 */
DrivePropertiesModel::DrivePropertiesModel()
{
  sensitiveAttributes = DiskMonitorSettings::sensitiveAttributes();
  headerLabels << i18nc("Attribute's id", "Id")
               << i18nc("Attribute's name", "Name")
               << i18nc("Attribute's flags", "Flags")
               << i18nc("Worst known value for this attribute", "Worst")
               << i18nc("Threshold value for this attribute", "Threshold")
               << i18nc("Normalized value for this attribute", "Normalized value")
               << i18nc("Human friendly value for this attribute", "Value");

  connect(DiskMonitorSettings::self(), SIGNAL(configChanged()), this, SLOT(configChanged()));
}



/*
 * Destructor
 */
DrivePropertiesModel::~DrivePropertiesModel()
{
}



/*
 * Retrieve the Drive associated to the model. Can be NULL
 */
Drive* DrivePropertiesModel::getDrive() const
{
  return static_cast<Drive*>(this -> unit);
}



/*
 * Handler when StorageUnitPropertiesModel refresh the underlying unit
 */
void DrivePropertiesModel::updateInternalState()
{
  Drive* drive = getDrive();

  if(drive != nullptr)
    attributes = drive -> getSMARTAttributes();
  else
    attributes.clear();
}



/*
 * Get the number of rows contained in the model's data
 */
int DrivePropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return attributes.size();
}



/*
 * Get the number of column of the model
 */
int DrivePropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant DrivePropertiesModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid() || unit == nullptr)
    return QVariant();

  SmartAttribute attr = attributes.at(index.row());

  // Handle background colors
  if(role == Qt::BackgroundRole) {
    //value is unknown
    if(attr.value == -1)
      return QVariant(QBrush());

    //set the row background to 'error' if value < threshold
    if(attr.value <= attr.threshold) {
      QBrush brush(DiskMonitorSettings::errorColor());
      return QVariant(brush);

    //set the row background to 'warning' if value is non 0 for sensitive attributes
    } else if(attr.pretty != 0 && sensitiveAttributes.contains(attr.id)) {
      QBrush brush(DiskMonitorSettings::warningColor());
      return QVariant(brush);

    } else {
      return QVariant();
    }


  // Handle text colors
  } else if(role == Qt::ForegroundRole) {
    QPalette palette;

    if(attr.value == -1) {
      return QVariant(palette.brush(QPalette::Disabled, QPalette::Text));
    } else
      return QVariant(palette.brush(QPalette::Text));

  // Handle display value
  } else if(role == Qt::DisplayRole) {
    switch(index.column()) {
    case 0: return QVariant(attr.id);
    case 1: return QVariant(attr.name);
    case 2: return QVariant(attr.flags);
    case 3: return QVariant(attr.worst);
    case 4: return QVariant(attr.threshold);
    case 5: return QVariant(attr.value);
    case 6: return humanizeSmartAttribute(attr);
    //case 7: return QVariant(attr.pretty_unit); break;
    default: return QVariant();
    }


  // Handle tooltips
  } else if(index.column() == 6 && role == Qt::ToolTipRole)
    return QVariant(i18n("Raw value: %1", QString::number(attr.pretty)));

  return QVariant();
}



/*
 * Format the 'pretty' value for human readability
 */
QVariant DrivePropertiesModel::humanizeSmartAttribute(const SmartAttribute& attr) const
{
  switch(attr.pretty_unit) {
    case 0: return QVariant(i18nc("value type is unknown", "unknown"));
    case 1: return QVariant(attr.pretty);
    case 2: return QVariant(Humanize::duration(attr.pretty, "ms"));
    case 3: return QVariant(i18n("%1 sectors", QString::number(attr.pretty)));
    case 4: return QVariant(Humanize::temperature(attr.pretty));
    default: return QVariant();
  }
}



/*
 * Handle the headers of the model
 */
QVariant DrivePropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
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



/*
 * Handle config change
 */
void DrivePropertiesModel::configChanged()
{
  sensitiveAttributes = DiskMonitorSettings::sensitiveAttributes();
}
