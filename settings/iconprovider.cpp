#include "iconprovider.h"

#include "diskmonitor_settings.h"

/*
 * Constructor
 */
IconProvider::IconProvider(QObject *parent) : QObject(parent)
{

}


/*
 * Destructor
 */
IconProvider::~IconProvider()
{

}



/*
 * Get the healthy status icon name
 */
QString IconProvider::healthy() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-cool";
    case DiskMonitor::IconMode::Dialogs: return "dialog-ok";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::healthyIcon();
    default: return "face-cool";
  }
}



/*
 * Get the failing status icon name
 */
QString IconProvider::failing() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-sick";
    case DiskMonitor::IconMode::Dialogs: return "dialog-error";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::failingIcon();
    default: return "face-sick";
  }
}



/*
 * Get the unknown status icon name
 */
QString IconProvider::unknown() const
{
  switch(DiskMonitorSettings::iconMode()) {
    case DiskMonitor::IconMode::Emotes: return "face-confused";
    case DiskMonitor::IconMode::Dialogs: return "unknown";
    case DiskMonitor::IconMode::Custom: return DiskMonitorSettings::unknownIcon();
    default: return "face-confused";
  }
}
