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
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents

Item {
  id: monitoringPage
  width: parent.width
  height: parent.height

  property alias cfg_refreshTimeout: refreshTimeout.value
  property alias cfg_notifyEnabled: notifyEnabled.checked

  ColumnLayout {
    anchors.left: parent.left
    anchors.right: parent.right

    QtControls.GroupBox {
      Layout.fillWidth: true
      Layout.fillHeight: true
      title: i18n("General")
      flat: true

      ColumnLayout {
        spacing: 20

        RowLayout {
          anchors.top: parent.top
          anchors.topMargin: 10
  
          PlasmaComponents.Label {
            text: i18n("Refresh timeout")
          }
  
  
          QtControls.SpinBox {
            id: refreshTimeout
            minimumValue: 1
            maximumValue: 240
            suffix: i18nc("abbreviation for minutes", " min.")
            horizontalAlignment: Qt.AlignRight
          }
        }

        QtControls.CheckBox {
          id: notifyEnabled
          text: i18n("Notify health status change")
        }
      }

    }
  }

  Component.onCompleted: {
    refreshTimeout.value = plasmoid.configuration.refreshTimeout;
    notifyEnabled.checked = plasmoid.configuration.notifyEnabled;
  }

}
