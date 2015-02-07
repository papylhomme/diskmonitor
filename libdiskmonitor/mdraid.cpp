#include "mdraid.h"

#include "udisks2wrapper.h"

#include <QDebug>


/*
 * Initialize a new MDRaid
 *
 * @param objectPath The DBus object path to the UDisks2 node represented by this mdraid
 * @param device A string identifying the underlying Linux device (/dev/mdX)
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html
 */
MDRaid::MDRaid(QDBusObjectPath objectPath, QString device) : StorageUnit(objectPath, device)
{
  update();
}


/*
 * Destructor
 */
MDRaid::~MDRaid()
{

}



/*
 * Update the cached property of this MDRaid
 */
void MDRaid::update()
{
  QDBusInterface* raidIface = UDisks2Wrapper::getInstance() -> mdraidIface(objectPath);

  this -> failing = getBoolProperty(raidIface, "Degraded");
  //only set failingStatusKnown if DBus access hasn't failed
  this -> failingStatusKnown = !raidIface -> lastError().isValid();

  this -> name = getStringProperty(raidIface, "Name");
  this -> uuid = getStringProperty(raidIface, "UUID");
  this -> level = getStringProperty(raidIface, "Level");
  this -> numDevices = getIntProperty(raidIface, "NumDevices");
  this -> size = getIntProperty(raidIface, "Size");
  this -> syncAction = getStringProperty(raidIface, "SyncAction");
  this -> syncCompleted = getDoubleProperty(raidIface, "SyncCompleted");
  this -> syncRemainingTime = getIntProperty(raidIface, "SyncRemainingTime");

  QDBusInterface* propIface = UDisks2Wrapper::getInstance() -> propertiesIface(objectPath);

  //handle ActiveDevices properties using DBus Properties interface as a direct read fails
  members.clear();
  QDBusMessage reply = propIface -> call("Get", UDISKS2_MDRAID_IFACE, "ActiveDevices");
  QVariant v = reply.arguments().first();
  QDBusArgument arg = v.value<QDBusVariant>().variant().value<QDBusArgument>();

  arg.beginArray();
  while(!arg.atEnd()) {
    MDRaidMember m;
    arg >> m;
    members << m;
  }

  delete raidIface;
}




/******************
 *                *
 *     Getters    *
 *                *
 *****************/


/*
 * Get the number of devices participating on the raid array
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.NumDevices
 */
int MDRaid::getNumDevices() const
{
  return this -> numDevices;
}



/*
 * Get the size of the raid array, 0 if unknown
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.Size
 */
int MDRaid::getSize() const
{
  return this -> size;
}



/*
 * Get the remaining time (in milliseconds) to finish the current sync operation.
 * Return 0 if the amount of time is unknown or if there is no sync operation in progress
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.SyncRemainingTime
 */
int MDRaid::getSyncRemainingTime() const
{
  return this -> syncRemainingTime;
}



/*
 * Get the proportion of sync completed, between 0 and 1.
 * Return 0 if no sync operation is in progress
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.SyncCompleted
 */
double MDRaid::getSyncCompleted() const
{
  return this -> syncCompleted;
}



/*
 * Get the UUID of the raid array
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.UUID
 */
const QString& MDRaid::getUUID() const
{
  return this -> uuid;
}



/*
 * Get the raid level of the array (raid0, raid1, ...)
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.Level
 */
const QString& MDRaid::getLevel() const
{
  return this -> level;
}



/*
 * Get the current sync action on the raid array. Can be 'check', 'repair' or 'idle' if there
 * is no current sync action. Can be empty if the raid array if not running or if there is no
 * redundancy
 *
 * http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html#gdbus-property-org-freedesktop-UDisks2-MDRaid.SyncAction
 */
const QString& MDRaid::getSyncAction() const
{
  return this -> syncAction;
}



/*
 * Get a list of the raid array members;
 */
const MDRaidMemberList&MDRaid::getMembers() const
{
  return this -> members;
}
