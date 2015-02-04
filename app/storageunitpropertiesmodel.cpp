#include "storageunitpropertiesmodel.h"


#include "udisks2wrapper.h"


/*
 *
 */
StorageUnitPropertiesModel::StorageUnitPropertiesModel()
{
  connect(UDisks2Wrapper::getInstance(), SIGNAL(storageUnitRemoved(StorageUnit*)), this, SLOT(storageUnitRemoved(StorageUnit*)));
}



/*
 *
 */
StorageUnitPropertiesModel::~StorageUnitPropertiesModel()
{

}



/*
 *
 */
void StorageUnitPropertiesModel::updateStorageUnit(StorageUnit* unit)
{
  beginResetModel();
  this -> unit = unit;
  updateInternalState();
  endResetModel();
}



/*
 *
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
    updateStorageUnit(NULL);
}



/*
 *
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

