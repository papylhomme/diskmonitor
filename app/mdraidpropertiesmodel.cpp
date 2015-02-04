#include "mdraidpropertiesmodel.h"


/*
 *
 */
MDRaidPropertiesModel::MDRaidPropertiesModel()
{
  names << "UUID" << "Level" << "Devices number" <<
           "Size" << "Sync action" << "Sync completed" <<
           "Sync remaining time";
}



/*
 *
 */
MDRaidPropertiesModel::~MDRaidPropertiesModel()
{

}



/*
 *
 */
void MDRaidPropertiesModel::updateMDRaid(MDRaid* raid)
{
  beginResetModel();
  this -> mdraid = raid;
  endResetModel();
}




/*
 *
 */
MDRaid* MDRaidPropertiesModel::getMDRaid()
{
  return this -> mdraid;
}



/*
 *
 */
void MDRaidPropertiesModel::refreshAll()
{
  if(mdraid != NULL) {
    beginResetModel();
    mdraid -> update();
    endResetModel();
  }
}



/*
 *
 */
int MDRaidPropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return names.size();
}


/*
 *
 */
int MDRaidPropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return 2;
}



/*
 *
 */
QVariant MDRaidPropertiesModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid())
    return QVariant();

  if(role == Qt::DisplayRole) {
    if(index.column() == 0)
      return names[index.row()];

    else if(index.column() == 1 && mdraid != NULL) {
      switch(index.row()) {
        case 0: return QVariant(mdraid -> getUUID()); break;
        case 1: return QVariant(mdraid -> getLevel()); break;
        case 2: return QVariant(mdraid -> getNumDevices()); break;
        case 3: return QVariant(mdraid -> getSize()); break;
        case 4: return QVariant(mdraid -> getSyncAction()); break;
        case 5: return QVariant(mdraid -> getSyncCompleted()); break;
        case 6: return QVariant(mdraid -> getSyncRemainingTime()); break;
      }
    }
  }

  return QVariant();
}

