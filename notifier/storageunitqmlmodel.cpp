#include "storageunitqmlmodel.h"

#include "udisks2wrapper.h"

#include <QDebug>
#include <QProcess>


/*
 * Constructor
 */
StorageUnitQmlModel::StorageUnitQmlModel()
{
  qDebug() << "StorageUnitQmlModel created !";
  UDisks2Wrapper* udisks2 = UDisks2Wrapper::getInstance();

  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));
  storageUnits = udisks2 -> listStorageUnits();

  monitor();

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(monitor()));
  timer -> start(10000);
}



/*
 * Destructor
 */
StorageUnitQmlModel::~StorageUnitQmlModel()
{
  timer -> stop();
  delete timer;

  //free the wrapper instance
  UDisks2Wrapper::freeInstance();

  qDebug() << "StorageUnitQmlModel destructed !";
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
  qDebug() << "StorageUnitQmlModel::monitor";

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

  foreach(StorageUnit* unit, units) {
    if(unit -> isFailing()) {
      localFailing = true;
    }
  }

  if(hasFailing != localFailing) {
    qDebug() << "StorageMonitor: Changing failing status to " << localFailing;
    emit updateGlobalHealthStatus(localFailing);
  }

  hasFailing = localFailing;
}



/*
 *
 */
void StorageUnitQmlModel::openApp(const QString& unitPath)
{
  qDebug() << "Request to open the app for unit " << unitPath;
  QStringList params;
  params << unitPath;
  QProcess::startDetached("diskmonitor", params);
}
