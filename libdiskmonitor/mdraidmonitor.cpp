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

#include "mdraidmonitor.h"


/*
 * Constructor
 */
MDRaidMonitor::MDRaidMonitor()
{

}



/*
 * Destructor
 */
MDRaidMonitor::~MDRaidMonitor()
{

}



/*
 * Process the given mdraid unit to detect problems and failures
 */
HealthStatus::Status MDRaidMonitor::process(MDRaid* mdraid)
{
  HealthStatus status;

  if(mdraid -> getDegraded() > 0)
    status = HealthStatus::Failing;
  else
    status = HealthStatus::Healthy;

  foreach(MDRaidMember member, mdraid -> getMembers())
    if(member.healthStatus >= HealthStatus::Warning)
      status.updateIfGreater(HealthStatus::Warning);

  return status.getStatus();
}



/*
 * Process the given MDRaidMember to detected problems and failures
 */
HealthStatus::Status MDRaidMonitor::processMember(MDRaid* /*mdraid*/, const MDRaidMember& member)
{
  if(member.state.contains("faulty"))
    return HealthStatus::Failing;

  else if(member.numReadErrors > 0)
    return HealthStatus::Warning;

  else
    return HealthStatus::Healthy;
}

