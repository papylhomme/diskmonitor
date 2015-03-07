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



#include "iconsprovider.h"


#include <QDebug>


/*
 * Constructor
 */
IconsProvider::IconsProvider() : QObject()
{

}



/*
 * Destructor
 */
IconsProvider::~IconsProvider()
{

}



/*
 * Get the icon for the given healthStatus
 */
QString IconsProvider::iconForStatus(int healthStatus) const
{
  switch(healthStatus) {
    case HealthStatus::Failing: return iconFailing(); break;
    case HealthStatus::Warning: return iconWarning(); break;
    case HealthStatus::Healthy: return iconHealthy(); break;
    default: return iconUnknown(); break;
  }
}



/*
 * Get the iconUnknown value
 */
const QString& IconsProvider::iconUnknown() const
{
  return unknownIcon;
}



/*
 * Get the iconHealthy value
 */
const QString& IconsProvider::iconHealthy() const
{
  return healthyIcon;
}



/*
 * Get the iconWarning value
 */
const QString& IconsProvider::iconWarning() const
{
  return warningIcon;
}



/*
 * Get the iconFailing value
 */
const QString& IconsProvider::iconFailing() const
{
  return failingIcon;
}



/*
 * Set the iconUnknown value
 */
void IconsProvider::setIconUnknown(const QString& unknownIcon)
{
  this -> unknownIcon = unknownIcon;
  emit iconUnknownChanged();
}



/*
 * Set the iconHealthy value
 */
void IconsProvider::setIconHealthy(const QString& healthyIcon)
{
  this -> healthyIcon = healthyIcon;
  emit iconHealthyChanged();
}



/*
 * Set the iconWarning value
 */
void IconsProvider::setIconWarning(const QString& warningIcon)
{
  this -> warningIcon = warningIcon;
  emit iconWarningChanged();
}



/*
 * Set the iconFailing value
 */
void IconsProvider::setIconFailing(const QString& failingIcon)
{
  this -> failingIcon = failingIcon;
  emit iconFailingChanged();
}
