#include "storagedatamodel.h"

#include "udisks2wrapper.h"

#include <QPixmap>
#include <kiconloader.h>


/*
 *
 */
StorageDataModel::StorageDataModel()
{
  refresh();

  UDisks2Wrapper* udisks2 = UDisks2Wrapper::getInstance();
  connect(udisks2, SIGNAL(storageUnitAdded(StorageUnit*)), this, SLOT(storageUnitAdded(StorageUnit*)));
  connect(udisks2, SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));
}



/*
 *
 */
StorageDataModel::~StorageDataModel()
{

}



/*
 *
 */
void StorageDataModel::refresh() {
  UDisks2Wrapper* udisks2 = UDisks2Wrapper::getInstance();

  beginResetModel();

  storageUnits.clear();
  QList<StorageUnit*> units = udisks2 -> listStorageUnits();

  foreach(StorageUnit* u, units) {
    storageUnits.append(u);
  }

  endResetModel();
}



/*
 *
 */
int StorageDataModel::rowCount(const QModelIndex&) const
{
  return storageUnits.size();
}



/*
 *
 */
QVariant StorageDataModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid())
    return QVariant();

  StorageUnit* u = storageUnits[index.row()];

  if(role == Qt::DisplayRole) {
    return QVariant(u -> getName());

  } else if(role == Qt::ToolTipRole) {
    return QVariant(u -> getName());

  } else if(role == Qt::DecorationRole) {

    //define health status overlay
    QStringList overlays;
    if(!u -> isFailingStatusKnown())
      overlays.append("face-confused");
    else if(u -> isFailing())
      overlays.append("face-sick");
    else
      overlays.append("face-cool");

    //define icon
    QString icon;
    if(u -> isMDRaid())
      icon = "drive-harddisk";
    else if(u -> isDrive() && ((Drive*) u) -> isRemovable())
      icon = "drive-removable-media";
    else
      icon = "drive-harddisk";

    return QVariant(KIconLoader::global() -> loadIcon(icon, KIconLoader::Desktop, 64, KIconLoader::DefaultState, overlays));

  } else if(role == Qt::UserRole) {
    QVariant v;
    v.setValue(u);
    return v;
  }


  return QVariant();
}



/*
 *
 */
void StorageDataModel::storageUnitAdded(StorageUnit* unit)
{
  int idx = storageUnits.size();

  beginInsertRows(QModelIndex(), idx, idx);
  storageUnits.append(unit);
  endInsertRows();
}



/*
 *
 */
void StorageDataModel::storageUnitRemoved(StorageUnit* unit)
{
  int idx = storageUnits.indexOf(unit);

  beginRemoveRows(QModelIndex(), idx, idx);
  storageUnits.removeAt(idx);
  endRemoveRows();
}
