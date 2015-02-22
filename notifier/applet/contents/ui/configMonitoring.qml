import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Layouts 1.1
import org.kde.plasma.components 2.0 as PlasmaComponents

Item {
  id: monitoringPage
  width: parent.width
  height: parent.height

  property alias cfg_refreshTimeout: refreshTimeout.value

  ColumnLayout {

    QtControls.GroupBox {
      Layout.fillWidth: true
      Layout.fillHeight: true
      title: i18n("General")
      flat: true

      RowLayout {
        PlasmaComponents.Label {
          text: "Refresh timeout"
        }


        QtControls.SpinBox {
          id: refreshTimeout
         minimumValue: 1
          maximumValue: 240
        }
      }

    }
  }

  Component.onCompleted: {
    refreshTimeout.value = plasmoid.configuration.refreshTimeout;
  }

}
