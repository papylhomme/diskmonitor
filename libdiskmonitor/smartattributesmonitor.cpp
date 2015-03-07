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

#include "smartattributesmonitor.h"


/*
 * Empty constructor
 */
SMARTAttributesMonitor::SMARTAttributesMonitor() : QObject()
{
}



/*
 * Construct a new SMARTAttributesMonitor with a given list of sensitive attributes
 */
SMARTAttributesMonitor::SMARTAttributesMonitor(const QList<int>& attrs)
{
  this -> attributes = QList<int>(attrs);
}



/*
 * Destructor
 */
SMARTAttributesMonitor::~SMARTAttributesMonitor()
{

}



/*
 * Process a SmartAttribute to extract his HealthStatus
 */
HealthStatus::Status SMARTAttributesMonitor::process(const SmartAttribute& attr)
{
  if(attr.value <= attr.threshold)
    return HealthStatus::Failing;
  else if(!attributes.contains(attr.id))
    return HealthStatus::Unknown;
  else if(attr.pretty != 0)
    return HealthStatus::Warning;
  else
    return HealthStatus::Healthy;
}

