import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore

MouseArea {
  id: panelIconWidget;

  anchors.fill: parent;
  onClicked: plasmoid.expanded = !plasmoid.expanded;

  PlasmaCore.IconItem {
    id: statusIcon;
    anchors.fill: parent;
    source: "diskmonitor";
  }
}

