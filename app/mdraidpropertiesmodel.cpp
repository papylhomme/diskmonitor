#include "mdraidpropertiesmodel.h"

#include <KLocalizedString>

#include <QFont>

#include "humanize.h"


/*
 * Constructor
 */
MDRaidPropertiesModel::MDRaidPropertiesModel()
{
  headerLabels << i18n("UUID")
               << i18n("Level")
               << i18n("Devices")
               << i18n("Size")
               << i18n("Sync action")
               << i18n("Sync remaining time")
               << i18n("Sync completed");
}



/*
 * Destructor
 */
MDRaidPropertiesModel::~MDRaidPropertiesModel()
{

}



/*
 * Retrieve the MDRaid associated to the model. Can be NULL
 */
MDRaid* MDRaidPropertiesModel::getMDRaid() const
{
  return (MDRaid*) this -> unit;
}



/*
 * Get the number of rows contained in the model's data. Always 1
 */
int MDRaidPropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return 1;
}


/*
 * Get the number of column of the model
 */
int MDRaidPropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant MDRaidPropertiesModel::data(const QModelIndex& index, int role) const
{
  MDRaid* mdraid = getMDRaid();

  if(!index.isValid() || index.row() != 0 || mdraid == NULL)
    return QVariant();


  if(role == Qt::DisplayRole) {
    switch(index.column()) {
      case 0: return QVariant(mdraid -> getUUID()); break;
      case 1: return QVariant(mdraid -> getLevel()); break;
      case 2: return QVariant(mdraid -> getNumDevices()); break;
      case 3: return QVariant(Humanize::size(mdraid -> getSize())); break;
      case 4: return QVariant(mdraid -> getSyncAction()); break;
      case 5: return QVariant(Humanize::duration(mdraid -> getSyncRemainingTime(), "us", "s")); break;
      case 6: return QVariant(Humanize::percentage(mdraid -> getSyncCompleted())); break;
      default: return QVariant(); break;
    }

  } else if(role == Qt::ToolTipRole) {
    switch(index.column()) {
      case 3: return QVariant(i18n("Raw value:") + " " + QString::number(mdraid -> getSize())); break;
      case 5: return QVariant(i18n("Raw value:") + " " + QString::number(mdraid -> getSyncRemainingTime())); break;
      case 6: return QVariant(i18n("Raw value:") + " " + QString::number(mdraid -> getSyncCompleted())); break;
      default: return QVariant(); break;
    }
  }

  return QVariant();
}



/*
 * Handle the headers of the model
 */
QVariant MDRaidPropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
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


