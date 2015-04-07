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
import QtQuick.Layouts 1.1
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.papylhomme.diskmonitor 0.1 as DiskMonitor
 
 
FocusScope {

  property var storageModel

  PlasmaExtras.ScrollArea {
    id: scrollView

    anchors.fill: parent

    ListView {
      id: storageUnitView

      anchors.fill: parent
      clip: true
      model: storageModel
      currentIndex: -1
      boundsBehavior: Flickable.StopAtBounds
      delegate: Component {
        id: delegateComponent

        Loader {
          anchors.left: parent.left
          anchors.right: parent.right
          source: {
            if(plasmoid.configuration.layoutSmall)
              return "StorageUnitSmall.qml";
            else if(plasmoid.configuration.layoutMinimalist)
              return "StorageUnitMinimalist.qml";
            else if(plasmoid.configuration.layoutIconsOnly)
              return "StorageUnitIcons.qml";
            else
              return "StorageUnitBig.qml";
          }
        }
      }
    }
  }
}
