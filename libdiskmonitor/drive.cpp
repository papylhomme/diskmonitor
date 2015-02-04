#include "drive.h"

#include "udisks2wrapper.h"

#include <QDebug>


//API doc at http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.Drive.Ata.html

/*
 *
 */
Drive::Drive(QDBusObjectPath objectPath, QString device, bool hasATAIface) : StorageUnit(objectPath, device)
{
  this -> hasATAIface = hasATAIface;
  update();
}



/*
 *
 */
Drive::~Drive()
{

}



/*
 *
 */
bool Drive::isSmartSupported()
{
  return this -> smartSupported;
}



/*
 *
 */
bool Drive::isSmartEnabled()
{
  return this -> smartEnabled;
}



/*
 *
 */
bool Drive::isRemovable()
{
  return this -> removable;
}



/*
 *
 */
SmartAttributesList Drive::getAttributes()
{
  return this -> attributes;
}



/*
 *
 */
void Drive::update()
{
  attributes.clear();

  QDBusInterface* driveIface = UDisks2Wrapper::getInstance() -> driveIface(objectPath);
  this -> removable = getBoolProperty(driveIface, "Removable");
  delete driveIface;

  //Skip smart properties if ATA_IFACE is not present
  if(!hasATAIface) {
    this -> failingStatusKnown = false;
    return;
  }

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

  } else {
    this -> failingStatusKnown = false;
  }

  delete ataIface;
}



/*
  QDBusInterface drive_iface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_DRIVE_IFACE, QDBusConnection::systemBus());

  qDebug() << "Drive Properties for drive at " << objectPath.path();
  qDebug() << drive_iface.property("Vendor");
  qDebug() << drive_iface.property("Model");
  qDebug() << drive_iface.property("Serial");
  qDebug() << drive_iface.property("Id");
  qDebug() << drive_iface.property("MediaCompatibility");
  qDebug() << drive_iface.property("MediaCompatibility").toList().size();
  qDebug() << drive_iface.property("Removable");
  qDebug() << drive_iface.property("Ejectable");


  QDBusInterface ata_iface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());

  qDebug() << "ATA Properties for drive at " << objectPath.path();
  qDebug() << ata_iface.property("SmartSupported");
  qDebug() << ata_iface.property("SmartEnabled");
  qDebug() << ata_iface.property("SmartUpdated");
  qDebug() << ata_iface.property("SmartFailing");
  qDebug() << ata_iface.property("SmartPowerOnSeconds");
  qDebug() << ata_iface.property("SmartTemperature");
  qDebug() << ata_iface.property("SmartNumAttributesFailing");
  qDebug() << ata_iface.property("SmartNumAttributesFailedInThePast");
  qDebug() << ata_iface.property("SmartNumBadSectors");
  qDebug() << ata_iface.property("SmartSelfTestStatus");
  qDebug() << ata_iface.property("SmartSelfPercentRemaining");
*/
