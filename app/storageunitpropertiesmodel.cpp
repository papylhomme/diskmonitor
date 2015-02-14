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

  if(this -> unit != NULL)
    disconnect(this -> unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdate(StorageUnit*)));

  this -> unit = unit;

  if(this -> unit != NULL)
    connect(this -> unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdate(StorageUnit*)));


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
  if(this -> unit != NULL && this -> unit -> getObjectPath() == unit -> getObjectPath()) {
    disconnect(this -> unit, SIGNAL(updated(StorageUnit*)), this, SLOT(storageUnitUpdate(StorageUnit*)));
    setStorageUnit(NULL);
  }
}



/*
 * Handle storage unit updated
 */
void StorageUnitPropertiesModel::storageUnitUpdate(StorageUnit* /*unit*/)
{
  beginResetModel();
  updateInternalState();
  endResetModel();
}



/*
 * Refresh the model's internal data
 */
void StorageUnitPropertiesModel::refreshAll()
{
  if(unit != NULL)
    unit -> update();
}

