#ifndef STORAGEUNITMODEL_H
#define STORAGEUNITMODEL_H

#include <QAbstractListModel>

#include "drive.h"

#include "iconprovider.h"

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
    bool inhibitUpdate = false;
    Settings::IconProvider iconProvider;
    QList<StorageUnit*> storageUnits;

    void init();

private slots:
    void storageUnitAdded(StorageUnit* unit);
    void storageUnitRemoved(StorageUnit* unit);
    void storageUnitUpdated(StorageUnit* unit);
};

#endif // STORAGEUNITMODEL_H
