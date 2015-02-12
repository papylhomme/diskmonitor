import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents

Item {

  property bool isFailing;

  PlasmaCore.IconItem {
    source: parent.isFailing ? "face-sick" : "face-cool";
    anchors.right: healthLabel.left;
    anchors.verticalCenter: parent.verticalCenter;
  }

  PlasmaComponents.Label {
    id: healthLabel;

    text: parent.isFailing ? "Failing" : "Healthy";
    color: parent.isFailing ? "red": PlasmaCore.ColorScope.textColor;
    font.weight : parent.isFailing ? Font.Bold : theme.defaultFont.weight;
    anchors.right: parent.right;
    anchors.verticalCenter: parent.verticalCenter;
  }

}
