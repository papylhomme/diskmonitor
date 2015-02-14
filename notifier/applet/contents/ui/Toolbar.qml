import QtQuick 2.3
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents


RowLayout {

  Item {
    Layout.fillWidth: true;
  }

  PlasmaComponents.ToolButton {
    id: refreshButton;
    iconSource: "view-refresh";

    onClicked: {
      myStorageModel.refresh();
    }
  }


  PlasmaComponents.ToolButton {
    id: openSettingsButton;
    iconSource: "configure";

    onClicked: {
      myStorageModel.showSettings();
    }
  }

}
