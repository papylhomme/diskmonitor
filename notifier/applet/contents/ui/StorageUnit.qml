import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Layouts 1.1


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


    PlasmaCore.IconItem {
      source: failing ? "face-sick" : "face-cool";
    }

    PlasmaComponents.Label {
      id: healthLabel;

      text: failing ? "Failing" : "Healthy";
      color: failing ? "red": PlasmaCore.ColorScope.textColor;
      font.weight : failing ? Font.Bold : theme.defaultFont.weight;
    }
  }


  onClicked: {
    myStorageModel.openApp(path);
  }

}
