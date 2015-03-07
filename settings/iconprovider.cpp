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


#include "iconprovider.h"

#include "diskmonitor_settings.h"


using namespace Settings;



/*
 * Constructor
 */
IconProvider::IconProvider(QObject *parent) : QObject(parent)
{
  connect(DiskMonitorSettings::self(), SIGNAL(configChanged()), this, SLOT(configChanged()));
}


/*
 * Destructor
 */
IconProvider::~IconProvider()
{

}



/*
 * Get the healthy status icon name
 */
QString IconProvider::healthy() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-cool";
    case DiskMonitor::IconMode::Dialogs: return "dialog-ok";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::healthyIcon();
    default: return "face-cool";
  }
}



/*
 * Get the failing status icon name
 */
QString IconProvider::failing() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-sick";
    case DiskMonitor::IconMode::Dialogs: return "dialog-error";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::failingIcon();
    default: return "face-sick";
  }
}



/*
 * Get the warning status icon name
 */
QString IconProvider::warning() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-angry";
    case DiskMonitor::IconMode::Dialogs: return "dialog-warning";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::warningIcon();
    default: return "face-angry";
  }
}


/*
 * Get the unknown status icon name
 */
QString IconProvider::unknown() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-confused";
    case DiskMonitor::IconMode::Dialogs: return "unknown";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::unknownIcon();
    default: return "face-confused";
  }
}



/*
 * Get the health icon for the given healthStatus
 */
QString IconProvider::iconForSatus(HealthStatus::Status healthStatus) const
{
  switch(healthStatus) {
    case HealthStatus::Failing:
      return failing();
      break;
    case HealthStatus::Warning:
      return warning();
      break;
    case HealthStatus::Healthy:
      return healthy();
    default:
      return unknown();
  }
}



/*
 * Handle config change
 */
void IconProvider::configChanged()
{
  emit healthyChanged();
  emit failingChanged();
  emit unknownChanged();
}
