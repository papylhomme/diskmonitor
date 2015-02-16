#include "configdialog.h"


#include "diskmonitor_settings.h"

#include "appearance.h"
#include "smart.h"
#include "applet.h"


using namespace Settings;



/*
 * Constructor
 */
ConfigDialog::ConfigDialog(QWidget* parent) : KConfigDialog(parent, "settings", DiskMonitorSettings::self())
{

}



/*
 * Destructor
 */
ConfigDialog::~ConfigDialog()
{

}



/*
 * Update and show the config dialog
 */
bool ConfigDialog::showDialog(QWidget* parent, bool appletConfig)
{
  DiskMonitorSettings::self() -> load();

  ConfigDialog* dialog = (ConfigDialog*) exists("settings");
  if(dialog)
    delete dialog;

  dialog = new ConfigDialog(parent);
  dialog -> setFaceType(KPageDialog::List);
  dialog -> addPage(new Appearance(dialog), i18n("Appearance"), "preferences-desktop-icons", i18n("Appearance options"));
  dialog -> addPage(new SMART(dialog), i18n("S.M.A.R.T"), "drive-harddisk", i18n("S.M.A.R.T options") );

  if(appletConfig)
    dialog -> addPage(new Settings::Applet(dialog), i18n("Applet"), "preferences-desktop-plasma", i18n("Applet options"));

  return KConfigDialog::showDialog("settings");
}


