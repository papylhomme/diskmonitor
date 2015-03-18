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

#include "drivemonitor.h"


/*
 * Empty constructor
 */
DriveMonitor::DriveMonitor() : QObject()
{
}



/*
 * Construct a new SMARTAttributesMonitor with a given list of sensitive attributes
 */
DriveMonitor::DriveMonitor(const QList<int>& attrs)
{
  this -> sensitiveAttributes = QList<int>(attrs);
}



/*
 * Destructor
 */
DriveMonitor::~DriveMonitor()
{

}



/*
 * Process a SmartAttribute to extract his HealthStatus
 */
HealthStatus::Status DriveMonitor::process(Drive* drive)
{
  HealthStatus status;

  if(drive -> isSmartFailing())
    status = HealthStatus::Failing;

  else if(drive -> isSmartSupported() && drive -> isSmartEnabled())
    status = HealthStatus::Healthy;

  if(!drive -> isSelfTestStatusHealthy())
    status.updateIfGreater(HealthStatus::Warning);

  foreach(const SmartAttribute& attr, drive -> getSMARTAttributes())
    if(attr.healthStatus >= HealthStatus::Warning)
      status.updateIfGreater(HealthStatus::Warning);

  return status.getStatus();
}



/*
 *
 */
HealthStatus::Status DriveMonitor::processAttributes(Drive* /*drive*/, const SmartAttribute& attr)
{
  if(attr.value <= attr.threshold)
    return HealthStatus::Failing;
  else if(!sensitiveAttributes.contains(attr.id))
    return HealthStatus::Unknown;
  else if(attr.pretty != 0)
    return HealthStatus::Warning;
  else
    return HealthStatus::Healthy;
}

