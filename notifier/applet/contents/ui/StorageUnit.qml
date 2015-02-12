import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents


PlasmaComponents.ListItem {

  PlasmaCore.IconItem {
    id: unitIcon;

    source: icon;
    anchors.left: parent.left;
    anchors.verticalCenter: parent.verticalCenter;
  }

  PlasmaComponents.Label {
    id: unitLabel;

    text: name;
    font.weight: Font.Bold;
    anchors.left: unitIcon.right;
    anchors.bottomMargin: 0;
  }

  PlasmaComponents.Label {
    id: deviceLabel;

    text: device;
    anchors.left: unitLabel.left;
    anchors.top: unitLabel.baseline;
    anchors.topMargin: 0;
  }

  HealthStatus {
    id: healthStatus;
    isFailing: failing;

    anchors.left: unitLabel.right;
    anchors.right: parent.right;
    anchors.verticalCenter: parent.verticalCenter;
  }

}
