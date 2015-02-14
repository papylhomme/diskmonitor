import QtQuick 2.3
import QtQuick.Layouts 1.1
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.papylhomme.diskmonitor 0.1 as DiskMonitor
 
 
FocusScope {

  property var storageModel;

  Toolbar {
    id: toolbar

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
  }

  PlasmaExtras.ScrollArea {
    id: scrollView;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.top: toolbar.bottom;

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
