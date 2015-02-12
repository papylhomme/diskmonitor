#include "drive.h"

#include "udisks2wrapper.h"

#include <QDebug>



/*
 * Initialize a new Drive
 *
 * @param objectPath The DBus object path to the UDisks2 node represented by this drive
 * @param device A string identifying the underlying Linux device (/dev/sdX)
 * @param hasATAIface boolean to set if the drive has the UDisks2 ATA interface present
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.html
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html
 */
Drive::Drive(QDBusObjectPath objectPath, QString device, bool hasATAIface) : StorageUnit(objectPath, device)
{
  this -> hasATAIface = hasATAIface;
  update();
}



/*
 * Destructor
 */
Drive::~Drive()
{

}



/*
 * Test if this is a removable drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.html#gdbus-property-org-freedesktop-UDisks2-Drive.Removable
 */
bool Drive::isRemovable() const
{
  return this -> removable;
}



/*
 * Test if SMART is supported on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSupported
 */
bool Drive::isSmartSupported() const
{
  return this -> smartSupported;
}



/*
 * Test if SMART is enabled on the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartEnabled
 */
bool Drive::isSmartEnabled() const
{
  return this -> smartEnabled;
}



/*
 * Get the remaining percentage of the running self test, or -1 if unknown
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-property-org-freedesktop-UDisks2-Drive-Ata.SmartSelftestPercentRemaining
 */
int Drive::getSelfTestPercentRemaining() const
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
const QString& Drive::getSelfTestStatus() const
{
  return this -> selfTestStatus;
}



/*
 * Get the cached list of SMART attributes for the drive
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html#gdbus-method-org-freedesktop-UDisks2-Drive-Ata.SmartGetAttributes
 */
const SmartAttributesList& Drive::getSMARTAttributes() const
{
  return this -> attributes;
}



/*
 * Update the cached property and SMART attributes of this Drive
 */
void Drive::update()
{
  attributes.clear();


  //retrieve general properties from the DRIVE_IFACE
  QDBusInterface* driveIface = UDisks2Wrapper::getInstance() -> driveIface(objectPath);
  this -> removable = getBoolProperty(driveIface, "Removable");
  this -> shortName = getStringProperty(driveIface, "Model");
  delete driveIface;

  //Skip smart properties if ATA_IFACE is not present
  if(!hasATAIface) {
    this -> failingStatusKnown = false;
    return;
  }


  //retrieve SMART properties from the ATA_IFACE
  QDBusInterface* ataIface = UDisks2Wrapper::getInstance() -> ataIface(objectPath);
  this -> smartSupported = getBoolProperty(ataIface, "SmartSupported");
  this -> smartEnabled = getBoolProperty(ataIface, "SmartEnabled");

  if(this -> smartSupported && this -> smartEnabled) {
    this -> failing = getBoolProperty(ataIface, "SmartFailing");
    this -> failingStatusKnown = true;


    QDBusReply<SmartAttributesList> res = ataIface -> call("SmartGetAttributes", QVariantMap());
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
}
