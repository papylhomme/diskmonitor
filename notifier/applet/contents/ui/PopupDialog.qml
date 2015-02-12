import QtQuick 2.3
import QtQuick.Layouts 1.1
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.papylhomme.diskmonitor 0.1 as DiskMonitor
 
 
FocusScope {

  DiskMonitor.StorageUnitQmlModel {
    id: storageModel;
  }

  PlasmaExtras.ScrollArea {
    id: scrollView;

    anchors.fill: parent;

    ListView {
      id: storageUnitView;

      anchors.fill: parent;
      clip: true;
      model: storageModel;
      currentIndex: -1;
      boundsBehavior: Flickable.StopAtBounds;
      delegate: StorageUnit { }
    }
  }
}
