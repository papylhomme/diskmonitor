#include "mdraid.h"

#include "udisks2wrapper.h"

#include <QDebug>


//UDisks2 API doc at http://udisks.freedesktop.org/docs/latest/gdbus-org.freedesktop.UDisks2.MDRaid.html

/*
 *
 */
MDRaid::MDRaid(QDBusObjectPath objectPath, QString device) : StorageUnit(objectPath, device)
{
  update();
}


/*
 *
 */
MDRaid::~MDRaid()
{

}



/*
 *
 */
void MDRaid::update()
{
  QDBusInterface* raidIface = UDisks2Wrapper::getInstance() -> mdraidIface(objectPath);

  this -> failing = getBoolProperty(raidIface, "Degraded");
  this -> name = getStringProperty(raidIface,"Name");
  this -> uuid = getStringProperty(raidIface,"UUID");
  this -> level = getStringProperty(raidIface,"Level");
  this -> numDevices = getIntProperty(raidIface,"NumDevices");
  this -> size = getIntProperty(raidIface,"Size");
  this -> syncAction = getStringProperty(raidIface,"SyncAction");
  this -> syncCompleted = getDoubleProperty(raidIface,"SyncCompleted");
  this -> syncRemainingTime = getIntProperty(raidIface,"SyncRemainingTime");

  //TODO: handle property ActiveDevices => a(oiasta{sv})

  //TODO: only set failingStatusKnown if DBus access hasn't failed
  this -> failingStatusKnown = true;

  delete raidIface;
}




/******************
 *                *
 *     Getters    *
 *                *
 *****************/


/*
 *
 */
int MDRaid::getNumDevices()
{
  return this -> numDevices;
}



/*
 *
 */
int MDRaid::getSize()
{
  return this -> size;
}



/*
 *
 */
int MDRaid::getSyncRemainingTime()
{
  return this -> syncRemainingTime;
}



/*
 *
 */
double MDRaid::getSyncCompleted()
{
  return this -> syncCompleted;
}



/*
 *
 */
QString MDRaid::getUUID()
{
  return this -> uuid;
}



/*
 *
 */
QString MDRaid::getLevel()
{
  return this -> level;
}



/*
 *
 */
QString MDRaid::getSyncAction()
{
  return this -> syncAction;
}
