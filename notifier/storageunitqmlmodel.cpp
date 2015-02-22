#include "storageunitqmlmodel.h"

#include <KNotification>
#include <QProcess>
#include <QDebug>


#include "udisks2wrapper.h"
#include "configdialog.h"
#include "appearance.h"
#include "smart.h"
#include "applet.h"




/*
 * Constructor
 */
StorageUnitQmlModel::StorageUnitQmlModel()
{
  UDisks2Wrapper* udisks2 = UDisks2Wrapper::instance();
  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));

  storageUnits = udisks2 -> listStorageUnits();
  monitor();

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(monitor()));
  timer -> start(timeout * 60 * 1000);
}



/*
 * Destructor
 */
StorageUnitQmlModel::~StorageUnitQmlModel()
{
  timer -> stop();
  delete timer;

  qDebug() << "StorageUnitQmlModel destructed !";
}



/*
 * Test if there is failing units
 */
bool StorageUnitQmlModel::failing() const
{
  return hasFailing;
}



/*
 * Get a message describing the current status
 */
QString StorageUnitQmlModel::status() const
{
  if(!hasFailing)
    return i18n("Everything looks healthy.");
  else {
    QString details;

    foreach(StorageUnit* unit, failingUnits)
      details = "<br/><i>" + unit -> getName() + " (" + unit -> getDevice() + ")</i>";

    return i18n("The following storage units are in failing state:") + details;
  }
}



/*
 * Get the refresh timeout value
 */
int StorageUnitQmlModel::refreshTimeout() const
{
  return timeout;
}



/*
 * Set the refresh timeout value. Calling this method
 * will emit refreshTimeoutChanged(newTimeout)
 */
void StorageUnitQmlModel::setRefreshTimeout(int timeout) {
  this -> timeout = timeout;
  this -> timer -> stop();
  this -> timer -> start(timeout * 60 * 1000);
  emit refreshTimeoutChanged(timeout);
  qDebug() << "StorageUnitQmlModel refresh timeout changed to " << timeout;
}



/*
 * Return a list of available roles for this model
 */
QHash<int, QByteArray> StorageUnitQmlModel::roleNames() const
{
  QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
  roles[NameRole] = "name";
  roles[IconRole] = "icon";
  roles[DeviceRole] = "device";
  roles[FailingRole] = "failing";
  roles[FailingKnownRole] = "failingKnown";
  roles[PathRole] = "path";
  return roles;
}



/*
 * Get the number of rows in the model
 */
int StorageUnitQmlModel::rowCount(const QModelIndex& /*parent*/) const
{
  return storageUnits.size();
}



/*
 * Get the data for the specified index and role
 */
QVariant StorageUnitQmlModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid())
    return QVariant();

  StorageUnit* unit = storageUnits.at(index.row());

  switch(role) {
    case NameRole: return QVariant(unit -> getShortName()); break;
    case IconRole: return QVariant(getIconForUnit(unit)); break;
    case DeviceRole: return QVariant(unit -> getDevice()); break;
    case PathRole: return QVariant(unit -> getPath()); break;
    case FailingRole: return QVariant(unit -> isFailing()); break;
    case FailingKnownRole: return QVariant(unit -> isFailingStatusKnown()); break;
    default: return QVariant(); break;
  }

  return QVariant();
}



/*
 * Retrieve an icon name for the given StorageUnit
 */
QString StorageUnitQmlModel::getIconForUnit(StorageUnit* unit) const
{
  QString icon;
  if(unit -> isMDRaid())
    icon = "drive-harddisk";
  else if(unit -> isDrive() && ((Drive*) unit) -> isRemovable())
    icon = "drive-removable-media";
  else
    icon = "drive-harddisk";

  return icon;
}



/*
 * Handle StorageUnit added
 */
void StorageUnitQmlModel::storageUnitAdded(StorageUnit* unit)
{
  int idx = storageUnits.size();

  beginInsertRows(QModelIndex(), idx, idx);
  storageUnits.append(unit);
  endInsertRows();

  //refresh the status with the new unit
  processUnit(unit);
}



/*
 * Handle StorageUnit removed
 */
void StorageUnitQmlModel::storageUnitRemoved(StorageUnit* unit)
{
  int idx = storageUnits.indexOf(unit);

  beginRemoveRows(QModelIndex(), idx, idx);
  storageUnits.removeAt(idx);
  endRemoveRows();

  //refresh status for the remaining units
  processUnits(storageUnits);
}



/*
 * Monitor entry point ; list available StorageUnits and test them
 * for problems
 */
void StorageUnitQmlModel::monitor() {
  qDebug() << "StorageUnitQmlModel::monitor (" << UDisks2Wrapper::instance() << ")";

  beginResetModel();
  foreach(StorageUnit* unit, storageUnits) {
    unit -> update();
  }
  endResetModel();

  processUnits(storageUnits);
}



/*
 * Convenience wrapper around StorageUnitQmlModel::processUnits()
 */
void StorageUnitQmlModel::processUnit(StorageUnit* unit)
{
  QList<StorageUnit*> units;
  units << unit;
  processUnits(units);
}



/*
 * Update the current general health status with the given storage units
 */
void StorageUnitQmlModel::processUnits(const QList<StorageUnit*>& units)
{
  bool localFailing = false;
  failingUnits.clear();

  //test each unit
  foreach(StorageUnit* unit, units) {
    if(unit -> isFailing()) {
      localFailing = true;
      failingUnits << unit;
    }
  }


  //Status changed, notify the user
  if(hasFailing != localFailing) {
    qDebug() << "StorageMonitor: Changing failing status to " << localFailing;
    hasFailing = localFailing;
    emit statusChanged();

    KNotification::event(hasFailing ? "failing" : "healthy",
                         hasFailing ? i18n("Storage units failing") : i18n("Storage units are back to healthy status"),
                         status(),
                         hasFailing ? iconProvider.failing() : iconProvider.healthy(),
                         NULL,
                         KNotification::Persistent,
                         "diskmonitor"
                         );
  }
}



/*
 * Slot to open the main DisKMonitor application
 *
 * @param unitPath The DBus path to the unit to display
 */
void StorageUnitQmlModel::openApp(const QString& unitPath)
{
  qDebug() << "Request to open the app for unit " << unitPath;
  QStringList params;
  params << unitPath;
  QProcess::startDetached("diskmonitor", params);
}



/*
 * Refresh the model
 */
void StorageUnitQmlModel::refresh()
{
  monitor();
}



/*
 * Show settings dialog
 */
void StorageUnitQmlModel::showSettings()
{
  Settings::ConfigDialog::showDialog(NULL, true);
}
