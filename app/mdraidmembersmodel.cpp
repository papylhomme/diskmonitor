#include "mdraidmembersmodel.h"

#include <QFont>
#include <QColor>
#include <QBrush>


/*
 * Constructor
 */
MDRaidMembersModel::MDRaidMembersModel()
{
  headerLabels << "Block device" << "Slot" << "State" << "Read errors";
}



/*
 * Destructor
 */
MDRaidMembersModel::~MDRaidMembersModel()
{

}



/*
 * Retrieve the MDRaid associated to the model. Can be NULL
 */
MDRaid* MDRaidMembersModel::getMDRaid() const
{
  return (MDRaid*) this -> unit;
}



/*
 * Handler when StorageUnitPropertiesModel refresh the underlying unit
 */
void MDRaidMembersModel::updateInternalState()
{
  MDRaid* mdraid = getMDRaid();

  if(mdraid != NULL)
    members = mdraid -> getMembers();
  else
    members.clear();
}



/*
 * Get the number of rows contained in the model's data. Always 1
 */
int MDRaidMembersModel::rowCount(const QModelIndex& /*index*/) const
{
  return members.size();
}


/*
 * Get the number of column of the model
 */
int MDRaidMembersModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant MDRaidMembersModel::data(const QModelIndex& index, int role) const
{
  MDRaid* mdraid = getMDRaid();

  if(!index.isValid() || mdraid == NULL)
    return QVariant();

  MDRaidMember member = members.at(index.row());

  // Handle background colors
  if(role == Qt::BackgroundRole) {

    //set the row background to red if device is faulty
    if(member.state.indexOf("faulty") >= 0) {
      QBrush brush(QColor("red"));
      return QVariant(brush);

    //set the row background to orange if read errors is positive
    } else if(member.numReadErrors > 0) {
      QBrush brush(QColor("orange"));
      return QVariant(brush);

    } else {
      return QVariant();
    }

  } else if(role == Qt::DisplayRole) {
    switch(index.column()) {
      case 0: return QVariant(member.block.path()); break;
      case 1: return QVariant(member.slot); break;
      case 2: return QVariant(member.state.join(", ")); break;
      case 3: return QVariant(member.numReadErrors); break;
      default: return QVariant(); break;
    }

  }

  return QVariant();
}



/*
 * Handle the headers of the model
 */
QVariant MDRaidMembersModel::headerData(int section, Qt::Orientation orientation, int role) const
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


