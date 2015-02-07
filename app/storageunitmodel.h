#ifndef STORAGEUNITMODEL_H
#define STORAGEUNITMODEL_H

#include <QAbstractListModel>
#include <QMap>

#include "drive.h"

class StorageUnitModel : public QAbstractListModel
{
  Q_OBJECT

public:
    StorageUnitModel();
    ~StorageUnitModel();

    virtual int rowCount(const QModelIndex& index) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void refresh();

private:
    QList<StorageUnit*> storageUnits;

private slots:
    void storageUnitAdded(StorageUnit* drive);
    void storageUnitRemoved(StorageUnit* path);
};

#endif // STORAGEUNITMODEL_H
