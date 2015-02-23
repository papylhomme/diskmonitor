import QtQuick 2.0
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.platformcomponents 2.0

PlasmaComponents.Button {
  property alias icon: button.iconSource

  id: button

  IconDialog {
    id: iconDialog
  }

  onClicked: {
    button.iconSource = iconDialog.openDialog();
  }

}

