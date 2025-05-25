/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2025 Michaël Lhomme <papylhomme@gmail.com>            *
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


 #include "nvmedrive.h"

 #include "udisks2wrapper.h"
 
 #include <QDebug>
 
 

/*
 * Initialize a new ATA Drive
 *
 * @param objectPath The DBus object path to the UDisks2 node represented by this drive
 * @param device A string identifying the underlying Linux device (/dev/sdX)
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html
 */
NvmeDrive::NvmeDrive(QDBusObjectPath objectPath, QString device) : Drive(objectPath, device)
{

}



/*
 * Destructor
 */
NvmeDrive::~NvmeDrive()
{
 
}
 


/*
 * Test if SMART is supported on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSupported
 */
bool NvmeDrive::isSmartSupported() const
{
  return this -> smartSupported;
}



/*
 * Test if SMART is enabled on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartEnabled
 */
bool NvmeDrive::isSmartEnabled() const
{
  return this -> smartEnabled;
}



/*
 * Get the remaining percentage of the running self test, or -1 if unknown
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSelftestPercentRemaining
 */
int NvmeDrive::getSelfTestPercentRemaining() const
{
  return this -> selfTestPercentRemaining;
}



/*
 * Get the status of the last (or running) self test
 *
 * success:  Last self-test was a success (or never ran).
 * aborted:  Last self-test was aborted.
 * interrupted:  Last self-test was interrupted.
 * fatal:  Last self-test did not complete.
 * error_unknown:  Last self-test failed (Unknown).
 * error_electrical:  Last self-test failed (Electrical).
 * error_servo:  Last self-test failed (Servo).
 * error_read:  Last self-test failed (Read).
 * error_handling:  Last self-test failed (Damage).
 * inprogress:  Self-test is currently in progress.
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSelftestStatus
 */
const QString& NvmeDrive::getSelfTestStatus() const
{
  return this -> selfTestStatus;
}



/*
 * Get the cached list of SMART attributes for the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-method-org-freedesktop-UDisks2-Drive-Ata.SmartGetAttributes
 */
const NvmeSmartAttributes& NvmeDrive::getSMARTAttributes() const
{
  return this -> attributes;
}



/*
 * Update the cached property and SMART attributes of this Drive
 */
 void NvmeDrive::update()
{
  attributes.clear();

  /*
   * retrieve SMART properties from the NVME_IFACE
   */
  QDBusInterface* nvmeIface = UDisks2Wrapper::instance() -> nvmeIface(objectPath);
 
  this -> selfTestStatus = getStringProperty(nvmeIface, "SmartSelftestStatus");
  this -> selfTestPercentRemaining = getIntProperty(nvmeIface, "SmartSelftestPercentRemaining");

  QStringList criticalWarnings = getProperty(nvmeIface, "SmartCriticalWarning").toStringList();
  this -> failingStatusKnown = true;
  this -> failing = !criticalWarnings.empty();
 
  QDBusReply<NvmeSmartAttributes> res = nvmeIface -> call("SmartGetAttributes", QVariantMap());
  if(!res.isValid())
    qCritical() << "Error calling SmartGetAttributes for drive '" << getPath() << "':" << res.error();
  else {
    attributes = res.value();
    attributes.insert("SmartCriticalWarning", criticalWarnings);
    attributes.insert("SmartPowerOnHours", getProperty(nvmeIface, "SmartPowerOnHours"));
    attributes.insert("SmartTemperature", getProperty(nvmeIface, "SmartTemperature"));
  }

  delete nvmeIface;

  Drive::update();
}
 