#include "storageunit.h"

#include <QDebug>



/*
 *
 */
StorageUnit::StorageUnit(QDBusObjectPath objectPath, QString device) : QObject()
{
  this -> objectPath = objectPath;
  this -> device = device;
  this -> name = objectPath.path().split("/").last();
}



/*
 *
 */
StorageUnit::StorageUnit() : QObject()
{
  qCritical() << "Should not be called ! Only required by QMETA_TYPE (TODO: do something about it ?)";
}



/*
 *
 */
StorageUnit::StorageUnit(const StorageUnit& other) : QObject()
{
  this -> objectPath = other.objectPath;
  this -> device = other.device;
  this -> name = other.objectPath.path().split("/").last();
}




/*
 *
 */
StorageUnit::~StorageUnit()
{

}



/*
 *
 */
QDBusObjectPath StorageUnit::getObjectPath()
{
  return this -> objectPath;
}



/*
 *
 */
QString StorageUnit::getPath()
{
  return this -> objectPath.path();
}



/*
 *
 */
QString StorageUnit::getDevice()
{
  return this -> device;
}



/*
 *
 */
QString StorageUnit::getName()
{
  return this -> name;
}



/*
 *
 */
bool StorageUnit::isFailing()
{
  return this -> failing;
}



/*
 *
 */
bool StorageUnit::isFailingStatusKnown()
{
  return this -> failingStatusKnown;
}



/*
 *
 */
QVariant StorageUnit::getProperty(QDBusInterface* iface, const char* name)
{
  QVariant prop = iface -> property(name);
  if(!prop.isValid())
    qCritical() << "Unable to read property '" << name <<
                "' from interface '" << iface -> interface() << "': " <<
                iface -> lastError();

  return prop;
}



/*
 *
 */
bool StorageUnit::getBoolProperty(QDBusInterface* iface, const char* name)
{
  return getProperty(iface, name).toBool();
}



/*
 *
 */
int StorageUnit::getIntProperty(QDBusInterface* iface, const char* name)
{
  return getProperty(iface, name).toInt();
}



/*
 *
 */
double StorageUnit::getDoubleProperty(QDBusInterface* iface, const char* name)
{
  return getProperty(iface, name).toDouble();
}



/*
 *
 */
QString StorageUnit::getStringProperty(QDBusInterface* iface, const char* name)
{
  return getProperty(iface, name).toString();
}




