#include "drivepropertiesmodel.h"

#include <QFont>
#include <QBrush>
#include <QColor>


/*
 *
 */
DrivePropertiesModel::DrivePropertiesModel()
{
  headerLabels << "Id" << "Name" << "Flags" << "Value" << "Worst" << "Threshold" << "Pretty" << "Pretty Unit";
}



/*
 *
 */
DrivePropertiesModel::~DrivePropertiesModel()
{

}



/*
 *
 */
Drive* DrivePropertiesModel::getDrive() const
{
  return (Drive*) this -> unit;
}



/*
 * Handler when StorageUnitPropertiesModel refresh the underlying unit
 */
void DrivePropertiesModel::updateInternalState()
{
  Drive* drive = getDrive();

  if(drive != NULL)
    attributes = drive -> getAttributes();
  else
    attributes.clear();
}



/*
 *
 */
int DrivePropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return attributes.size();
}


/*
 *
 */
int DrivePropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 *
 */
QVariant DrivePropertiesModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid() || unit == NULL)
    return QVariant();

  SmartAttribute attr = attributes.at(index.row());

  if(role == Qt::BackgroundRole) {
    //set the row background to red if value < threshold
    if(attr.value <= attr.threshold) {
      QBrush brush(QColor("red"));
      return QVariant(brush);

    //TODO: use orange to mark non 0 sensitive attribute (eg bad sectors)
    //} else if(attr.pretty != 0 && sensitiveAttributes.contains(attr.id) {
    } else {
      return QVariant();
    }
  }


  if(role == Qt::DisplayRole) {
    //TODO format pretty/pretty_unit
    switch(index.column()) {
    case 0: return QVariant(attr.id); break;
    case 1: return QVariant(attr.name); break;
    case 2: return QVariant(attr.flags); break;
    case 3: return QVariant(attr.value); break;
    case 4: return QVariant(attr.worst); break;
    case 5: return QVariant(attr.threshold); break;
    case 6: return QVariant(attr.pretty); break;
    case 7: return QVariant(attr.pretty_unit); break;
    default: return QVariant(); break;
    }
  }

  return QVariant();
}



/*
 *
 */
QVariant DrivePropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation != Qt::Horizontal)
    return QVariant();

  if(role == Qt::DisplayRole) {
      return QVariant(headerLabels.at(section));

  } else if(role == Qt::FontRole) {
    QFont font;
    font.setBold(true);
    return QVariant(font);
  }

  return QVariant();
}

