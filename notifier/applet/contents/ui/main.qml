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


  Component.onCompleted: updateTray();


  function updateTray() {
    if(myStorageModel.failing) {
      //mainWindow.Plasmoid.status = PlasmaCore.Types.RequireAttentionStatus;
      mainWindow.Plasmoid.status = 3;
      mainWindow.Plasmoid.icon = iconProvider.failing;
      mainWindow.Plasmoid.toolTipSubText = i18n("At least one storage unit is failing !");
    } else {
      //mainWindow.Plasmoid.status = PlasmaCore.Types.PassiveStatus;
      mainWindow.Plasmoid.status = 1;
      mainWindow.Plasmoid.icon = iconProvider.healthy;
      mainWindow.Plasmoid.toolTipSubText = i18n("Everything looks healthy");
    }
  }



  DiskMonitor.IconProvider {
    id: iconProvider;
  }

  DiskMonitor.StorageUnitQmlModel {
    id: myStorageModel;
    onFailingChanged: updateTray();
  }

  Plasmoid.compactRepresentation: CompactRepresentation { }
  Plasmoid.fullRepresentation: PopupDialog {
    id: dialogItem;

    storageModel: myStorageModel;

    anchors.fill: parent;
    anchors.margins: 20;
    focus: true;
  }

}
