#ifndef STORAGEUNITPROPERTIESMODEL_H
#define STORAGEUNITPROPERTIESMODEL_H

#include <QAbstractTableModel>

#include "storageunit.h"

class StorageUnitPropertiesModel : public QAbstractTableModel
{
  Q_OBJECT

public:
    StorageUnitPropertiesModel();
    ~StorageUnitPropertiesModel();

    void setStorageUnit(StorageUnit* unit);
    StorageUnit* getStorageUnit();

    void refreshAll();

protected:
    StorageUnit* unit;
    virtual void updateInternalState() { }

public slots:
    void storageUnitRemoved(StorageUnit* unit);
};

#endif // STORAGEUNITPROPERTIESMODEL_H
