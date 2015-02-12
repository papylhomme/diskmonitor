#include "storageunitqmlmodel.h"

#include "udisks2wrapper.h"

#include <QDebug>


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
}



/*
 * Destructor
 */
StorageUnitQmlModel::~StorageUnitQmlModel()
{
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
    case FailingRole: return QVariant(unit -> isFailingStatusKnown() && unit -> isFailing()); break;
    default: return QVariant(); break;
  }

  return QVariant();
}



/*
 * Retrieve an icon name for the given StorageUnit
 */
QString StorageUnitQmlModel::getIconForUnit(StorageUnit* /*unit*/) const
{
  return "drive-harddisk";
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
}
