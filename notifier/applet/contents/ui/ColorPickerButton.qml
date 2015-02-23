import QtQuick 2.0
import QtQuick.Dialogs 1.0
import org.kde.plasma.components 2.0 as PlasmaComponents

PlasmaComponents.Button {
  property alias color: rec.color

  ColorDialog {
    id: colorDialog
    title: i18n("Please choose a color")

    onAccepted: {
        rec.color = colorDialog.color
        Qt.quit()
    }

    onRejected: {
        Qt.quit()
    }
  }


  Rectangle {
    id: rec
    anchors.fill: parent
    anchors.margins: 3
  }

  onClicked: {
    colorDialog.open();
  }
}

