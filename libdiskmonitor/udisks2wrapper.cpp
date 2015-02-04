#include "udisks2wrapper.h"


#include "drive.h"
#include "mdraid.h"


/*
 * Singleton instance
 */
UDisks2Wrapper* UDisks2Wrapper::instance = NULL;



/*
 *
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
 *
 */
UDisks2Wrapper* UDisks2Wrapper::getInstance() {
  if(UDisks2Wrapper::instance == NULL)
    UDisks2Wrapper::instance = new UDisks2Wrapper();

  return UDisks2Wrapper::instance;
}



/*
 *
 */
UDisks2Wrapper::UDisks2Wrapper() : QObject()
{
  initQDbusMetaTypes();


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
 *
 */
void UDisks2Wrapper::initialize()
{
  //init internal storage units list
  QDBusInterface objManagerIface(UDISKS2_SERVICE, UDISKS2_PATH, UDISKS2_OBJECT_IFACE, QDBusConnection::systemBus());
  QDBusReply<ManagedObjectList> res = objManagerIface.call("GetManagedObjects");

  if(!res.isValid()) {
    qCritical() << "Error while retrieving UDisks2 objects ! " << res .error();
    //TODO ? exception to handle in UI and display error to user ?
  }

  ManagedObjectList objects = res.value();

  foreach(QDBusObjectPath objectPath, objects.keys()) {
    if(!objects[objectPath][UDISKS2_BLOCK_IFACE].empty()) {
      QDBusObjectPath drivePath = objects[objectPath][UDISKS2_BLOCK_IFACE]["Drive"].value<QDBusObjectPath>();
      if(drivePath.path().size() > 1 && !units.contains(drivePath)) {
        units[drivePath] = new Drive(drivePath,
                                     objects[objectPath][UDISKS2_BLOCK_IFACE]["Device"].toString(),
                                     !objects[drivePath][UDISKS2_ATA_IFACE].empty());
      }

      QDBusObjectPath mdraidPath = objects[objectPath][UDISKS2_BLOCK_IFACE]["MDRaid"].value<QDBusObjectPath>();
      if(mdraidPath.path().size() > 1 && !units.contains(mdraidPath)) {
        units[mdraidPath] = new MDRaid(mdraidPath, objects[objectPath][UDISKS2_BLOCK_IFACE]["Device"].toString());
      }
    }
  }

  initialized = true;
}



/*
 *
 */
UDisks2Wrapper::~UDisks2Wrapper()
{

}



/*
 *
 */
QList<StorageUnit*> UDisks2Wrapper::listStorageUnits()
{
  if(!initialized)
    initialize();

  return units.values();
}



/*
 *
 */
QDBusInterface* UDisks2Wrapper::driveIface(QDBusObjectPath objectPath)
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_DRIVE_IFACE, QDBusConnection::systemBus());

}



/*
 *
 */
QDBusInterface* UDisks2Wrapper::ataIface(QDBusObjectPath objectPath)
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_ATA_IFACE, QDBusConnection::systemBus());
}



/*
 *
 */
QDBusInterface*UDisks2Wrapper::mdraidIface(QDBusObjectPath objectPath)
{
  return new QDBusInterface(UDISKS2_SERVICE, objectPath.path(), UDISKS2_MDRAID_IFACE, QDBusConnection::systemBus());
}



/*
 *
 */
void UDisks2Wrapper::startMDRaidScrubbing(MDRaid* mdraid)
{
  QDBusInterface mdraid_iface(UDISKS2_SERVICE, mdraid -> getPath(), UDISKS2_MDRAID_IFACE, QDBusConnection::systemBus());

  qDebug() << "Request scrubbing on MDRaid '" << mdraid -> getPath() << "'";
  QDBusReply<void> res = mdraid_iface.call("RequestSyncAction", "check", QVariantMap());

  if(!res.isValid())
    qWarning() << "Error sending request to scrub MDRaid '" << mdraid -> getPath() << "' : " << res.error();
}



/*
 *
 */
void UDisks2Wrapper::startDriveSelfTest(Drive* drive)
{
  qDebug() << "TODO: implement UDisks2Wrapper::startDriveSelfTest";
}



/*
 *
 */
void UDisks2Wrapper::interfacesAdded(const QDBusObjectPath& objectPath, const InterfaceList& interfaces)
{
  qDebug() << "UDisks2Wrapper => New interfaces added to path '" << objectPath.path() << "'";

  if(!interfaces[UDISKS2_BLOCK_IFACE].empty()) {
    QDBusObjectPath drivePath = interfaces[UDISKS2_BLOCK_IFACE]["Drive"].value<QDBusObjectPath>();
    if(drivePath.path().size() > 1 && !units.contains(drivePath)) {
      units[drivePath] = new Drive(drivePath,
                                   interfaces[UDISKS2_BLOCK_IFACE]["Device"].toString(),
                                   !interfaces[UDISKS2_ATA_IFACE].empty());
      emit storageUnitAdded(units[drivePath]);
    }

    QDBusObjectPath mdraidPath = interfaces[UDISKS2_BLOCK_IFACE]["MDRaid"].value<QDBusObjectPath>();
    if(mdraidPath.path().size() > 1 && !units.contains(mdraidPath)) {
      units[mdraidPath] = new MDRaid(mdraidPath, interfaces[UDISKS2_BLOCK_IFACE]["Device"].toString());
      emit storageUnitAdded(units[mdraidPath]);
    }
  }
}



/*
 *
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
