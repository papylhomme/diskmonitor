/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/


#include "configdialog.h"


#include "diskmonitor_settings.h"

#include "appearance.h"
#include "smart.h"


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
bool ConfigDialog::showDialog(QWidget* parent)
{
  DiskMonitorSettings::self() -> load();

  ConfigDialog* dialog = static_cast<ConfigDialog*>(exists("settings"));
  if(dialog)
    delete dialog;

  dialog = new ConfigDialog(parent);
  dialog -> setFaceType(KPageDialog::List);
  dialog -> addPage(new Appearance(dialog), i18n("Appearance"), "preferences-desktop-icons", i18n("Appearance options"));
  dialog -> addPage(new SMART(dialog), i18n("S.M.A.R.T"), "drive-harddisk", i18n("S.M.A.R.T options") );

  return KConfigDialog::showDialog("settings");
}


