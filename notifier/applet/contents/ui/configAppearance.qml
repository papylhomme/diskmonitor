import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Layouts 1.1

Item {
  id: appearancePage
  width: parent.width
  height: parent.height

  property alias cfg_layoutSmall: layoutSmall.checked
  property alias cfg_layoutBig: layoutBig.checked

  ColumnLayout {
    QtControls.GroupBox {
      Layout.fillWidth: true
      Layout.fillHeight: true
      title: i18n("Layout")
      flat: true

      ColumnLayout {
 
        QtControls.ExclusiveGroup { id: layoutType }
 
        QtControls.RadioButton {
          id: layoutBig
          text: i18n("Big layout")
          exclusiveGroup: layoutType
        }
 
        QtControls.RadioButton {
          id: layoutSmall
          text: i18n("Small layout")
          exclusiveGroup: layoutType
        }
      }
    }
  }

  Component.onCompleted: {
    if (plasmoid.configuration.layoutBig) {
        layoutBig.checked = true;
    } else {
        layoutSmall.checked = true;
    }
  }

}
