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


import QtQuick 2.0

Item {

  property string healthy: {
    if(plasmoid.configuration.iconsFaces)
      return "face-cool";
    else if(plasmoid.configuration.iconsDialog)
      return "dialog-ok";
    else
      return plasmoid.configuration.iconHealthy; 
  }

  property string failing: {
    if(plasmoid.configuration.iconsFaces)
      return "face-sick";
    else if(plasmoid.configuration.iconsDialog)
      return "dialog-error";
    else
      return plasmoid.configuration.iconFailing; 
  }

  property string warning: {
    if(plasmoid.configuration.iconsFaces)
      return "face-angry";
    else if(plasmoid.configuration.iconsDialog)
      return "dialog-warning";
    else
      return plasmoid.configuration.iconWarning; 
  }

  property string unknown: {
    if(plasmoid.configuration.iconsFaces)
      return "face-confused";
    else if(plasmoid.configuration.iconsDialog)
      return "unknown";
    else
      return plasmoid.configuration.iconUnknown; 
  }


}

