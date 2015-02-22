import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.papylhomme.diskmonitor 0.1 as DiskMonitor

Item {
  id: mainWindow;

  Plasmoid.toolTipMainText: i18n("DisKMonitor");
  Plasmoid.toolTipSubText: i18n("Everything look healthy");
  Plasmoid.icon: iconProvider.healthy;
  //Plasmoid.status: PlasmaCore.Types.NeedsAttentionStatus;
  //Plasmoid.status: PlasmaCore.Types.RequireAttentionStatus;
  Plasmoid.status: PlasmaCore.Types.PassiveStatus;
  Plasmoid.associatedApplication: "diskmonitor";



  DiskMonitor.IconProvider {
    id: iconProvider;

    onHealthyChanged: updateTray();
    onFailingChanged: updateTray();
    onUnknownChanged: updateTray();
  }

  DiskMonitor.StorageUnitQmlModel {
    id: myStorageModel;
    refreshTimeout: plasmoid.configuration.refreshTimeout;
    onStatusChanged: updateTray();
  }

  Plasmoid.compactRepresentation: CompactRepresentation { }
  Plasmoid.fullRepresentation: PopupDialog {
    id: dialogItem;

    storageModel: myStorageModel;

    anchors.fill: parent;
    focus: true;
  }


  function action_refresh() {
    myStorageModel.refresh();
  }


  function action_openapp() {
    myStorageModel.openApp("");
  }


  function updateTray() {
    if(myStorageModel.failing) {
      //mainWindow.Plasmoid.status = PlasmaCore.Types.RequireAttentionStatus;
      mainWindow.Plasmoid.status = 3;
      mainWindow.Plasmoid.icon = iconProvider.failing;
      mainWindow.Plasmoid.toolTipSubText = myStorageModel.status;
    } else {
      //mainWindow.Plasmoid.status = PlasmaCore.Types.PassiveStatus;
      mainWindow.Plasmoid.status = 1;
      mainWindow.Plasmoid.icon = iconProvider.healthy;
      mainWindow.Plasmoid.toolTipSubText = myStorageModel.status;
    }
  }



  Component.onCompleted: {
    updateTray();
    plasmoid.setAction("refresh", i18n("Refresh"));
    plasmoid.setAction("openapp", i18n("Open application"));
  }

}
