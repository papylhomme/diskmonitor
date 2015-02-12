import QtQuick 2.3
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import QtQuick.Layouts 1.1

Item {
    id: mainWindow;

    Plasmoid.toolTipMainText: i18n("DisKMonitor");
    Plasmoid.toolTipSubText: i18n("Everything look healthy");
    Plasmoid.icon: "face-cool";
    //Plasmoid.status: PlasmaCore.Types.NeedsAttentionStatus;
    //Plasmoid.status: PlasmaCore.Types.RequireAttentionStatus;
    Plasmoid.status: PlasmaCore.Types.PassiveStatus;
    Plasmoid.associatedApplication: "diskmonitor";

    Plasmoid.compactRepresentation: CompactRepresentation { }
    Plasmoid.fullRepresentation: PopupDialog {
        id: dialogItem;

        anchors.fill: parent;
        anchors.margins: 20;
        focus: true;
    }
}
