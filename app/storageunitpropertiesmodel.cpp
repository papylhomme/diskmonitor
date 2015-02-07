#include "storageunitpropertiesmodel.h"


#include "udisks2wrapper.h"


/*
 * Constructor. Connect to the UDisks2Wrapper::storageUnitRemoved() signal
 * to ensure consistency
 */
StorageUnitPropertiesModel::StorageUnitPropertiesModel()
{
  connect(UDisks2Wrapper::getInstance(), SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));
}



/*
 * Destructor
 */
StorageUnitPropertiesModel::~StorageUnitPropertiesModel()
{

}



/*
 * Update the model's storage unit, refreshing the model's internal data
 */
void StorageUnitPropertiesModel::setStorageUnit(StorageUnit* unit)
{
  beginResetModel();
  this -> unit = unit;
  updateInternalState();
  endResetModel();
}



/*
 * Retrieve the associated StorageUnit. Can be NULL
 */
StorageUnit*StorageUnitPropertiesModel::getStorageUnit()
{
  return this -> unit;
}



/*
 * Handle removal of the model's underlying StorageUnit
 */
void StorageUnitPropertiesModel::storageUnitRemoved(StorageUnit* unit)
{
  if(this -> unit != NULL && this -> unit -> getObjectPath() == unit -> getObjectPath())
    setStorageUnit(NULL);
}



/*
 * Refresh the model's internal data
 */
void StorageUnitPropertiesModel::refreshAll()
{
  if(unit != NULL) {
    beginResetModel();
    unit -> update();
    updateInternalState();
    endResetModel();
  }
}

