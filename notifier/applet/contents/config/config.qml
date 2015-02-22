import QtQuick 2.3

import org.kde.plasma.configuration 2.0

ConfigModel {
  ConfigCategory {
    name: i18n("Monitoring")
    icon: "diskmonitor"
    source: "configMonitoring.qml"
  }

  ConfigCategory {
    name: i18n("Appearance")
    icon: "preferences-desktop-color"
    source: "configAppearance.qml"
  }
}
