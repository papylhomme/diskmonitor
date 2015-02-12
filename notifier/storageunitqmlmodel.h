#ifndef STORAGEUNITQMLMODEL_H
#define STORAGEUNITQMLMODEL_H

#include <QAbstractListModel>

#include "storageunit.h"

class StorageUnitQmlModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum AnimalRoles {
    NameRole = Qt::UserRole + 1,
    DeviceRole,
    FailingRole,
    IconRole
  };

  StorageUnitQmlModel();
  ~StorageUnitQmlModel();

  virtual QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
  QList<StorageUnit*> storageUnits;

  QString getIconForUnit(StorageUnit* unit) const;

private slots:
    void storageUnitAdded(StorageUnit* drive);
    void storageUnitRemoved(StorageUnit* path);
};

#endif // STORAGEUNITQMLMODEL_H
