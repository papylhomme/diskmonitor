import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Layouts 1.1
import org.papylhomme.diskmonitor 0.1 as DiskMonitor


PlasmaComponents.ListItem {
  id: storageUnitItem
  enabled: true


  RowLayout {
    id: layout
    anchors.left: parent.left
    anchors.right: parent.right

  
    PlasmaCore.IconItem {
      id: unitIcon
      Layout.maximumWidth: 16
      Layout.maximumHeight: 16
      source: icon
    }

  

    PlasmaComponents.Label {
      id: unitLabel
      Layout.fillWidth: true
      text: { plasmoid.configuration.includeDriveId ? device + " (" + name + ")" : device; }
      width: parent.width
      elide: Text.ElideRight
      color: { (failing & failingKnown) ? "red": PlasmaCore.ColorScope.textColor; }
    }


    PlasmaCore.IconItem {
      Layout.maximumWidth: 16
      Layout.maximumHeight: 16
      source: { failingKnown ? (failing? iconProvider.failing : iconProvider.healthy) : iconProvider.unknown; }
    }
  }


  onClicked: {
    myStorageModel.openApp(path);
  }

}
