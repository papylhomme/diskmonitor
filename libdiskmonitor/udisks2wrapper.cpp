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


#include "udisks2wrapper.h"


#include "drive.h"
#include "mdraid.h"


/*
 * Singleton instance
 */
Q_GLOBAL_STATIC(UDisks2Wrapper, myUDisks2WrapperInstance)



/*
 * Initialize the DBus metatypes
 */
void initQDbusMetaTypes()
{
  qRegisterMetaType<ManagedObjectList>("ManagedObjectList");
  qDBusRegisterMetaType<ManagedObjectList>();

  qRegisterMetaType<InterfaceList>("InterfaceList");
  qDBusRegisterMetaType<InterfaceList>();

  qRegisterMetaType<SmartAttribute>("SmartAttribute");
  qDBusRegisterMetaType<SmartAttribute>();

  qRegisterMetaType<SmartAttributesList>("SmartAttributesList");
  qDBusRegisterMetaType<SmartAttributesList>();

  qRegisterMetaType<MDRaidMember>("MDRaidMember");
  qDBusRegisterMetaType<MDRaidMember>();

  qRegisterMetaType<MDRaidMemberList>("MDRaidMemberList");
  qDBusRegisterMetaType<MDRaidMemberList>();
}



/*
 * Marshall the SmartAttribute data into a D-Bus argument
 */
QDBusArgument &operator<<(QDBusArgument &argument, const SmartAttribute& smartAttribue)
{
    argument.beginStructure();
    argument << smartAttribue.id;
    argument << smartAttribue.name;
    argument << smartAttribue.flags;
    argument << smartAttribue.value;
    argument << smartAttribue.worst;
    argument << smartAttribue.threshold;
    argument << smartAttribue.pretty;
    argument << smartAttribue.pretty_unit;
    argument << smartAttribue.expansion;
    argument.endStructure();

    return argument;
}



/*
 * Retrieve the SmartAttribute data from the D-Bus argument
 */
const QDBusArgument &operator>>(const QDBusArgument &argument, SmartAttribute& smartAttribue)
{
    argument.beginStructure();
    argument >> smartAttribue.id;
    argument >> smartAttribue.name;
    argument >> smartAttribue.flags;
    argument >> smartAttribue.value;
    argument >> smartAttribue.worst;
    argument >> smartAttribue.threshold;
    argument >> smartAttribue.pretty;
    argument >> smartAttribue.pretty_unit;
    argument >> smartAttribue.expansion;
    argument.endStructure();

    return argument;
}



/*
 * Marshall the MDRaidMember data into a D-Bus argument
 */
QDBusArgument &operator<<(QDBusArgument &argument, const MDRaidMember& raidMember)
{
    argument.beginStructure();
    argument << raidMember.block;
    argument << raidMember.slot;
    argument << raidMember.state;
    argument << raidMember.numReadErrors;
    argument << raidMember.expansion;
    argument.endStructure();

    return argument;
}



/*
 * Retrieve the MDRaidMember data from the D-Bus argument
 */
const QDBusArgument &operator>>(const QDBusArgument &argument, MDRaidMember& raidMember)
{
    argument.beginStructure();
    argument >> raidMember.block;
    argument >> raidMember.slot;
    argument >> raidMember.state;
    argument >> raidMember.numReadErrors;
    argument >> raidMember.expansion;
    argument.endStructure();

    return argument;
}




/*
 * Retrieve an instance of UDisks2Wrapper. ATM not thread-safe
 */
UDisks2Wrapper* UDisks2Wrapper::instance() {
  return myUDisks2WrapperInstance;
}



/*
 * UDisks2Wrapper constructor. Set the connection to UDisks2 to handle device hotplugging
 */
UDisks2Wrapper::UDisks2Wrapper() : QObject()
{
  initQDbusMetaTypes();


  addDriveMonitor(new DriveMonitor());
  addMDRaidMonitor(new MDRaidMonitor());

  //connection to UDisks2 signals
  bool connected;

  connected = QDBusConnection::systemBus().connect(UDISKS2_SERVICE, UDISKS2_PATH, UDISKS2_OBJECT_IFACE, "InterfacesAdded",
              this, SLOT(interfacesAdded(QDBusObjectPath, InterfaceList)));
  if(!connected)
    qWarning() << "Unable to connect to InterfacesAdded signal, won't handle device insertion !";

  connected = QDBusConnection::systemBus().connect(UDISKS2_SERVICE, UDISKS2_PATH, UDISKS2_OBJECT_IFACE, "InterfacesRemoved",
              this, SLOT(interfacesRemoved(QDBusObjectPath, QStringList)));
  if(!connected)
    qWarning() << "Unable to connect to InterfacesRemoved signal, won't handle device removal !";
}



/*
 * Initialize the internal list of StorageUnit from UDisks2
 */
void UDisks2Wrapper::initialize()
{
  //call the manager to retrieve a list of nodes
  QDBusInterface objManagerIface(UDISKS2_SERVICE, UDISKS2_PATH, UDISKS2_OBJECT_IFACE, QDBusConnection::systemBus());
  QDBusReply<ManagedObjectList> res = objManagerIface.call("GetManagedObjects");

  if(!res.isValid()) {
    qCritical() << "Error while retrieving UDisks2 objects ! " << res .error();
    //TODO ? exception to handle in UI and display error to user ?
  }

  ManagedObjectList objects = res.value();


  //loop over the result to extract existing raid arrays and drives.
  foreach(QDBusObjectPath objectPath, objects.keys()) {
    StorageUnit* newUnit = createNewUnitFromBlockDevice(objects[objectPath]);

    if(newUnit != NULL)
      units[newUnit -> getObjectPath()] = newUnit;
  }

  initialized = true;
}



/*
 * Destructor
 */
UDisks2Wrapper::~UDisks2Wrapper()
{
  foreach(StorageUnit* unit, units.values())
    delete unit;
  units.clear();

  foreach(DriveMonitor* monitor, driveMonitors.values())
    delete monitor;
  driveMonitors.clear();
}



/*
 * Get the internal cached list of StorageUnit.
 *
 * The wrapper use lazy initialization, as a result this method can result
 * in call to DBus the first time it is called
 */
QList<StorageUnit*> UDisks2Wrapper::listStorageUnits()
{
  if(!initialized)
    initialize();

  return units.values();
}



/*
 * Get a DBus Properties interface for the given node
 *
 * @param objectPath The DBus path identifying the node
 */
QDBusInterface*UDisks2Wrapper::propertiesIface(QDBusObjectPath objectPath) const
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), DBUS_PROPERTIES_IFACE, QDBusConnection::systemBus());
}



/*
 * Get a UDISKS2 Drive interface for the given node
 *
 * @param objectPath The DBus path identifying the node
 */
QDBusInterface* UDisks2Wrapper::driveIface(QDBusObjectPath objectPath) const
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_DRIVE_IFACE, QDBusConnection::systemBus());

}



/*
 * Get a UDISKS2 Drive_ATA interface for the given node
 *
 * @param objectPath The DBus path identifying the node
 */
QDBusInterface* UDisks2Wrapper::ataIface(QDBusObjectPath objectPath) const
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());
}



/*
 * Get a UDISKS2 MDRaid interface for the given node
 *
 * @param objectPath The DBus path identifying the node
 */
QDBusInterface*UDisks2Wrapper::mdraidIface(QDBusObjectPath objectPath) const
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_MDRAID_IFACE, QDBusConnection::systemBus());
}



/*
 * Add a new SMART attributes monitor for the given id
 */
void UDisks2Wrapper::addDriveMonitor(DriveMonitor* monitor, const QString& id)
{
  if(this -> driveMonitors[id] != NULL)
    delete this -> driveMonitors[id];

  this -> driveMonitors[id] = monitor;

  //refresh drive(s) to take new monitor into account
  foreach(StorageUnit* unit, units.values()) {
    if(unit -> isDrive() && (id.isEmpty() || id == unit -> getId()))
      unit -> update();
  }
}



/*
 * Get a SMART attributes monitor for the given id
 */
DriveMonitor* UDisks2Wrapper::getDriveMonitor(const QString& id)
{
  if(driveMonitors.contains(id))
    return driveMonitors[id];
  else
    return driveMonitors[QString()];
}



/*
 * Add a new MDRaidMonitor for the given MDRaid id
 */
void UDisks2Wrapper::addMDRaidMonitor(MDRaidMonitor* monitor, const QString& id)
{
  if(this -> mdraidMonitors[id] != NULL)
    delete this -> mdraidMonitors[id];

  this -> mdraidMonitors[id] = monitor;

  //refresh mdraid(s) to take new monitor into account
  foreach(StorageUnit* unit, units.values()) {
    if(unit -> isMDRaid() && (id.isEmpty() || id == unit -> getId()))
      unit -> update();
  }

}



/*
 * Get a MDRAidMonitor attributes monitor for the given id
 */
MDRaidMonitor*UDisks2Wrapper::getMDRaidMonitor(const QString& id)
{
  if(mdraidMonitors.contains(id))
    return mdraidMonitors[id];
  else
    return mdraidMonitors[QString()];
}



/*
 * Start a scrubbing operation on the given raid array (sync action = 'check')
 *
 * @param mdraid The raid array to test
 */
void UDisks2Wrapper::startMDRaidScrubbing(MDRaid* mdraid) const
{
  QDBusInterface mdraid_iface(UDISKS2_SERVICE, mdraid -> getPath(), UDISKS2_MDRAID_IFACE, QDBusConnection::systemBus());

  qDebug() << "Request scrubbing on MDRaid '" << mdraid -> getPath() << "'";
  QDBusReply<void> res = mdraid_iface.call("RequestSyncAction", "check", QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to scrub MDRaid '" << mdraid -> getPath() << "' : " << res.error();
}



/*
 * Cancel a running operation on the given raid array (sync action = 'idle')
 *
 * @param mdraid The raid array
 */

void UDisks2Wrapper::cancelMDRaidScrubbing(MDRaid* mdraid) const
{
  QDBusInterface mdraid_iface(UDISKS2_SERVICE, mdraid -> getPath(), UDISKS2_MDRAID_IFACE, QDBusConnection::systemBus());

  QString currentOperation = mdraid_iface.property("RequestSyncAction").toString();
  if(currentOperation != "check") {
    qWarning() << "Can't cancel operation '" << currentOperation << "' on MDRaid '" << mdraid -> getPath() << "': aborting";
    return;
  }

  qDebug() << "Request cancelation of scrubbing on MDRaid '" << mdraid -> getPath() << "'";
  QDBusReply<void> res = mdraid_iface.call("RequestSyncAction", "idle", QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to cancel scrubbing on MDRaid '" << mdraid -> getPath() << "' : " << res.error();
}



/*
 * Enable SMART on the given drive
 *
 * @param drive The drive for which to enable SMART
 */
void UDisks2Wrapper::enableSMART(Drive* drive) const
{
  QDBusInterface ata_iface(UDISKS2_SERVICE, drive -> getPath(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());

  qDebug() << "Request to enable SMART on Drive '" << drive -> getPath() << "'";
  QDBusReply<void> res = ata_iface.call("SmartSetEnabled", true, QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to enable SMART on Drive '" << drive -> getPath() << "' : " << res.error();
}



/*
 * Start a SMART SelfTest on the given drive
 *
 * @param drive The drive to test
 * @param type The type of SelfTest to run
 */
void UDisks2Wrapper::startSMARTSelfTest(Drive* drive, SMARTSelfTestType type) const
{
  QString strType;
  switch(type) {
    case ShortSelfTest: strType = "short"; break;
    case ExtendedSelfTest: strType = "extended"; break;
    case ConveyanceSelfTest: strType = "conveyance"; break;
    default: strType = "short"; break;
  }

  QDBusInterface ata_iface(UDISKS2_SERVICE, drive -> getPath(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());

  qDebug() << "Request " << strType << " selftest on Drive '" << drive -> getPath() << "'";
  QDBusReply<void> res = ata_iface.call("SmartSelftestStart", strType, QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to start SMART SelfTest on drive '" << drive -> getPath() << "' : " << res.error();
}



/*
 * Cancel a running SMART SelfTest on the given drive
 *
 * @param drive The drive to test
 */
void UDisks2Wrapper::cancelSMARTSelfTest(Drive* drive) const
{
  QDBusInterface ata_iface(UDISKS2_SERVICE, drive -> getPath(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());

  qDebug() << "Request cancelation of selftest on Drive '" << drive -> getPath() << "'";
  QDBusReply<void> res = ata_iface.call("SmartSelftestAbort", QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to cancel SMART SelfTest on drive '" << drive -> getPath() << "' : " << res.error();

}



/*
 * Handle UDisks2 "InterfacesAdded" signal to update the internal list of StorageUnit
 *
 * @param objectPath The node being updated
 * @param interfaces A map of interfaces being added
 */
void UDisks2Wrapper::interfacesAdded(const QDBusObjectPath& objectPath, const InterfaceList& interfaces)
{
  qDebug() << "UDisks2Wrapper => New interfaces added to path '" << objectPath.path() << "'";

  StorageUnit* newUnit = createNewUnitFromBlockDevice(interfaces);
  if(newUnit != NULL) {
    units[newUnit -> getObjectPath()] = newUnit;
    emit storageUnitAdded(newUnit);
  }
}



/*
 * Handle UDisks2 "InterfacesRemoved" signal to update the internal list of StorageUnit
 *
 * @param objectPath The node being updated
 * @param interfaces A map of interfaces being added
 */
void UDisks2Wrapper::interfacesRemoved(const QDBusObjectPath& objectPath, const QStringList& /*interfaces*/)
{
  qDebug() << "UDisks2Wrapper => Interfaces removed from path '" << objectPath.path() << "'";

  if(objectPath.path().startsWith(UDISKS2_DRIVES_PATH) ||
     objectPath.path().startsWith(UDISKS2_MDRAIDS_PATH)) {

    emit storageUnitRemoved(units[objectPath]);
    StorageUnit* u = units.take(objectPath);
    delete u;
  }
}




/*
 * Create a new unit from a block device node
 *
 * @param interfaces A list of node interfaces
 *
 * here we select block devices (and not directly raid or drive nodes) in order to
 * retrieve the associated Linux device name (/dev/sdX, /dev/mdX)
 */
StorageUnit* UDisks2Wrapper::createNewUnitFromBlockDevice(const InterfaceList& interfaces) const
{
  if(!interfaces[UDISKS2_BLOCK_IFACE].empty()) {
    QDBusObjectPath drivePath = interfaces[UDISKS2_BLOCK_IFACE]["Drive"].value<QDBusObjectPath>();
    if(drivePath.path().size() > 1 && !units.contains(drivePath)) {
      return new Drive(drivePath,
                       interfaces[UDISKS2_BLOCK_IFACE]["Device"].toString(),
                       hasATAIface(drivePath));
    }

    QDBusObjectPath mdraidPath = interfaces[UDISKS2_BLOCK_IFACE]["MDRaid"].value<QDBusObjectPath>();
    if(mdraidPath.path().size() > 1 && !units.contains(mdraidPath)) {
      return new MDRaid(mdraidPath, interfaces[UDISKS2_BLOCK_IFACE]["Device"].toString());
    }
  }

  return NULL;
}



/*
 * Test the presence of the ATA interface on the given path
 */
bool UDisks2Wrapper::hasATAIface(QDBusObjectPath objectPath) const
{
  QDBusInterface ataIface (UDISKS2_SERVICE, objectPath.path(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());
  ataIface.property("SmartSupported");

  return !ataIface.lastError().isValid();
}

