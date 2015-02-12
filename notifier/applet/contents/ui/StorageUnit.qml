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
    }

  
    Column {
      Layout.fillWidth: true;

      PlasmaComponents.Label {
        id: unitLabel;
        text: name;
        font.weight: Font.Bold;
        height: paintedHeight;
      }
    
      PlasmaComponents.Label {
        id: deviceLabel;
        text: device;
        height: paintedHeight;
      }
    }


    PlasmaComponents.Label {
      id: healthLabel;

      text: failingKnown ? (failing? i18n("Failing") : i18n("Healthy")) : i18n("Unknown");
      color: (failing & failingKnown) ? "red": PlasmaCore.ColorScope.textColor;
      font.weight : (failing & failingKnown) ? Font.Bold : theme.defaultFont.weight;
    }


    PlasmaCore.IconItem {
      source: failingKnown ? (failing? iconProvider.failing : iconProvider.healthy) : iconProvider.unknown;
    }
  }


  onClicked: {
    myStorageModel.openApp(path);
  }

}
