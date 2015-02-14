#ifndef STORAGEUNITPROPERTIESMODEL_H
#define STORAGEUNITPROPERTIESMODEL_H

#include <QAbstractTableModel>

#include "storageunit.h"


/*
 * Base class to implement Qt models for a storage unit.
 *
 * Handle unit removal from backend and update of the internal state
 */
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
    StorageUnit* unit = NULL;
    virtual void updateInternalState() { }

public slots:
    void storageUnitRemoved(StorageUnit* unit);

private slots:
    void storageUnitUpdate(StorageUnit* unit);
};

#endif // STORAGEUNITPROPERTIESMODEL_H
