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

  
    PlasmaComponents.Label {
      id: unitLabel
      Layout.fillWidth: true
      width: parent.width
      elide: Text.ElideRight
      color: { (failing & failingKnown) ? plasmoid.configuration.errorColor : PlasmaCore.ColorScope.textColor; }
      text: {
        if(plasmoid.configuration.smallDeviceName)
          var dev = device.split("/").pop();
        else
          var dev = device;

        if(plasmoid.configuration.includeDriveId)
          return dev + " (" + name + ")"
        else
          return dev;
        }
    }
  }


  onClicked: {
    myStorageModel.openApp(path);
  }

}
