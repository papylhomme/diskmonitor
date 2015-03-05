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


import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.papylhomme.diskmonitor 0.1 as DiskMonitor

Item {
  id: mainWindow

  Plasmoid.toolTipMainText: i18n("DisKMonitor")
  Plasmoid.toolTipSubText: i18n("Everything looks healthy.")
  Plasmoid.icon: iconProvider.healthy
  Plasmoid.status: PlasmaCore.Types.PassiveStatus


  IconProvider {
    id: iconProvider
  }

  DiskMonitor.StorageUnitMonitor {
    id: monitor
    refreshTimeout: plasmoid.configuration.refreshTimeout
    notifyEnabled: plasmoid.configuration.notifyEnabled
    onStatusChanged: { updateTray(); }

    iconHealthy: iconProvider.healthy;
    iconFailing: iconProvider.failing;
    iconWarning: iconProvider.warning;
  }


  Plasmoid.compactRepresentation: CompactRepresentation { }
  Plasmoid.fullRepresentation: PopupDialog {
    id: dialogItem
    focus: true
    anchors.fill: parent

    storageModel: monitor.model
  }


  function action_refresh() {
    monitor.monitor();
  }


  function action_openapp() {
    monitor.openApp();
  }


  function updateTray() {
    if(monitor.failing) {
      mainWindow.Plasmoid.status = PlasmaCore.Types.NeedsAttentionStatus;
      mainWindow.Plasmoid.icon = iconProvider.failing;
      mainWindow.Plasmoid.toolTipSubText = monitor.status;
    } else {
      mainWindow.Plasmoid.status = PlasmaCore.Types.PassiveStatus;
      mainWindow.Plasmoid.icon = iconProvider.healthy;
      mainWindow.Plasmoid.toolTipSubText = monitor.status;
    }
  }



  Component.onCompleted: {
    updateTray();
    plasmoid.setAction("refresh", i18n("Refresh"));
    plasmoid.setAction("openapp", i18n("Open application"));
  }


  //handle this as config change isn't correctly propagated
  //to Plasmoid.icon 
  Plasmoid.onUserConfiguringChanged: {
    updateTray();
  }

}
