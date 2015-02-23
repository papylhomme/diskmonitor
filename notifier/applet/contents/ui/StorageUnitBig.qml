import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Layouts 1.1
import org.papylhomme.diskmonitor 0.1 as DiskMonitor


PlasmaComponents.ListItem {
  id: storageUnitItem;
  enabled: true;


  RowLayout {
    id: layout;
    anchors.left: parent.left;
    anchors.right: parent.right;

  
    PlasmaCore.IconItem {
      id: unitIcon;
      source: icon;
      height: col.height;
    }

  
    Column {
      id: col;
      Layout.fillWidth: true;
      Layout.minimumWidth: deviceLabel.paintedWidth;

      PlasmaComponents.Label {
        id: unitLabel;
        text: name;
        height: paintedHeight;
        width: parent.width;
        elide: Text.ElideRight;
        font.weight: Font.Bold;
        color: (failing & failingKnown) ? plasmoid.configuration.errorColor : PlasmaCore.ColorScope.textColor;
      }
    
      PlasmaComponents.Label {
        id: deviceLabel;
        text: device;
        height: paintedHeight;
        width: parent.width;
        elide: Text.ElideRight;
        color: (failing & failingKnown) ? plasmoid.configuration.errorColor : PlasmaCore.ColorScope.textColor;
      }
    }


    PlasmaCore.IconItem {
      height: col.height;
      source: failingKnown ? (failing? iconProvider.failing : iconProvider.healthy) : iconProvider.unknown;
    }
  }


  onClicked: {
    myStorageModel.openApp(path);
  }

}
