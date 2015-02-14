#ifndef MDRAIDPROPERTIESMODEL_H
#define MDRAIDPROPERTIESMODEL_H

#include "storageunitpropertiesmodel.h"
#include "mdraid.h"


/*
 * A Qt model to display raid attributes in a table
 */
class MDRaidPropertiesModel : public StorageUnitPropertiesModel
{
  Q_OBJECT

public:
  MDRaidPropertiesModel();
  ~MDRaidPropertiesModel();

  MDRaid* getMDRaid() const;


  virtual int rowCount(const QModelIndex& index) const;
  virtual int columnCount(const QModelIndex& index) const;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
  QStringList headerLabels;
};

#endif // MDRAIDPROPERTIESMODEL_H
