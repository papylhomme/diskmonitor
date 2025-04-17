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


 #include "atadrive.h"

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
AtaDrive::AtaDrive(QDBusObjectPath objectPath, QString device) : Drive(objectPath, device)
{

}



/*
 * Destructor
 */
AtaDrive::~AtaDrive()
{
 
}
 


/*
 * Test if SMART is supported on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSupported
 */
bool AtaDrive::isSmartSupported() const
{
  return this -> smartSupported;
}



/*
 * Test if SMART is enabled on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartEnabled
 */
bool AtaDrive::isSmartEnabled() const
{
  return this -> smartEnabled;
}



/*
 * Get the remaining percentage of the running self test, or -1 if unknown
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSelftestPercentRemaining
 */
int AtaDrive::getSelfTestPercentRemaining() const
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
const QString& AtaDrive::getSelfTestStatus() const
{
  return this -> selfTestStatus;
}



/*
 * Get the cached list of SMART attributes for the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-method-org-freedesktop-UDisks2-Drive-Ata.SmartGetAttributes
 */
const AtaSmartAttributesList& AtaDrive::getSMARTAttributes() const
{
  return this -> attributes;
}



/*
 * Update the cached property and SMART attributes of this Drive
 */
 void AtaDrive::update()
{
  attributes.clear();

  /*
   * retrieve SMART properties from the ATA_IFACE
   */
   QDBusInterface* ataIface = UDisks2Wrapper::instance() -> ataIface(objectPath);
   this -> smartSupported = getBoolProperty(ataIface, "SmartSupported");
   this -> smartEnabled = getBoolProperty(ataIface, "SmartEnabled");
 
   if(this -> smartSupported && this -> smartEnabled) {
     this -> failing = getBoolProperty(ataIface, "SmartFailing");
     this -> failingStatusKnown = true;
 
 
     QDBusReply<AtaSmartAttributesList> res = ataIface -> call("SmartGetAttributes", QVariantMap());
     if(!res.isValid())
       qCritical() << "Error calling SmartGetAttributes for drive '" << getPath() << "':" << res.error();
     else
       attributes = res.value();
 
     this -> selfTestStatus = getStringProperty(ataIface, "SmartSelftestStatus");
     this -> selfTestPercentRemaining = getIntProperty(ataIface, "SmartSelftestPercentRemaining");
 
   } else {
     this -> failingStatusKnown = false;
   }
 
   delete ataIface;

   Drive::update();
}
 