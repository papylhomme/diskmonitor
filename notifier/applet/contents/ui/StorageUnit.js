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


function getTextColor() {
  if(failing & failingKnown)
    return plasmoid.configuration.errorColor;
  else if(hasWarnings)
    return plasmoid.configuration.warningColor;
  else
    return theme.textColor; 
}


function getStatusIcon() {
  if(!failingKnown)
    return iconProvider.unknown;
  else if(failing)
    return iconProvider.failing;
  else if(hasWarnings)
    return iconProvider.warning;
  else
    return iconProvider.healthy;
}


function getDeviceString() {
  if(plasmoid.configuration.smallDeviceName)
    return device.split("/").pop();
  else
    return device;
}


function getStorageUnitText() {
  if(plasmoid.configuration.includeDriveId)
    return getDeviceString() + " (" + name + ")"
  else
    return getDeviceString();
}

